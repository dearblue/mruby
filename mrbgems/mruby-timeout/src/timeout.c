#include <mruby.h>
#include <mruby/array.h>
#include <mruby/data.h>
#include <mruby/error.h>
#include <mruby/numeric.h>
#include <mruby/variable.h>
#include <string.h>
#include <time.h>

#define NAME_TIMEOUT_MANAGER    "timeout-manager"
#define ID_TIMEOUT_MANAGER      mrb_intern_lit(mrb, NAME_TIMEOUT_MANAGER)
#define NAME_TIMEOUT_EXTRA      "timeout-extra"
#define ID_TIMEOUT_EXTRA        mrb_intern_lit(mrb, NAME_TIMEOUT_EXTRA)

#define TIMEOUT_TAG_FIELD       0
#define TIMEOUT_FIELD_IN_ENTRIES 1

#define TIMEOUT_SET_EXTRA(m, x, e, f, v) \
  mrb_ary_set(m, x, TIMEOUT_FIELD_IN_ENTRIES * (e) + (f), v)

#define TIMEOUT_GET_EXTRA(m, x, e, f) \
  mrb_ary_get(m, x, TIMEOUT_FIELD_IN_ENTRIES * (e) + (f))

#define TIMEOUT_ENTRY_MINIMUM   4
#define TIMEOUT_ENTRY_MAXIMUM   1000
#define TIMEOUT_ENTRY_DEFAULT   20

#ifdef MRB_TIMEOUT_ENTRY_MAX
# if MRB_TIMEOUT_ENTRY_MAX >= TIMEOUT_ENTRY_MINIMUM && MRB_TIMEOUT_ENTRY_MAX < TIMEOUT_ENTRY_MAXIMUM
#  define TIMEOUT_ENTRY_MAX     MRB_TIMEOUT_ENTRY_MAX
# else
#  define TIMEOUT_ENTRY_MAX     TIMEOUT_ENTRY_DEFAULT
# endif
#else
# define TIMEOUT_ENTRY_MAX      TIMEOUT_ENTRY_DEFAULT
#endif

struct mrb_timeout_entry {
  mrb_bool activate : 1;
  int64_t alerm;
};

struct mrb_timeout_manager {
  struct mrb_timeout_entry *entries;
  int64_t next_alerm;
};

static void
mrb_timeout_free(mrb_state *mrb, void *ptr)
{
  if (ptr) {
    struct mrb_timeout_manager *m = (struct mrb_timeout_manager *)ptr;
    struct mrb_timeout_entry *e = m->entries;

    mrb_free(mrb, e);
    mrb_free(mrb, m);
  }
}

static const mrb_data_type mrb_timeout_type = { "timeout", mrb_timeout_free };

static mrb_value mrb_s_regist_timeout(mrb_state *mrb, mrb_value mod);
static mrb_value mrb_s_unregist_timeout(mrb_state *mrb, mrb_value mod);

static void
get_timeout_extra(mrb_state *mrb, mrb_value *extra, mrb_ssize *nentry)
{
  *extra = mrb_gv_get(mrb, ID_TIMEOUT_EXTRA);
  *nentry = RARRAY_LEN(*extra) / TIMEOUT_FIELD_IN_ENTRIES;
}

static void
get_timeout_data(mrb_state *mrb, struct mrb_timeout_manager **m, mrb_value *extra, mrb_ssize *nentry)
{
  mrb_value tom = mrb_gv_get(mrb, ID_TIMEOUT_MANAGER);
  *m = (struct mrb_timeout_manager *)mrb_data_get_ptr(mrb, tom, &mrb_timeout_type);
  get_timeout_extra(mrb, extra, nentry);
}

#if defined(_WIN32)
# include <windows.h>

static int64_t
timeout_get_tick(void)
{
  return (int64_t)timeGetTime();
}
#else
# if defined(__unix__) || defined(__MACH__)
#  if defined(CLOCK_UPTIME_FAST)
#   define MRB_CLOCK_ID CLOCK_UPTIME_FAST
#  elif defined(CLOCK_UPTIME)
#   define MRB_CLOCK_ID CLOCK_UPTIME
#  elif defined(CLOCK_MONOTONIC_FAST)
#   define MRB_CLOCK_ID CLOCK_MONOTONIC_FAST
#  elif defined(CLOCK_MONOTONIC)
#   define MRB_CLOCK_ID CLOCK_MONOTONIC
#  else
#   define MRB_CLOCK_ID CLOCK_REALTIME
#  endif
#  define GETTIME(ts) clock_gettime(MRB_CLOCK_ID, ts)
# else
#  ifndef TIME_UTC
#   error Need 'timespec_get()' defined in C11
#  endif
#  define GETTIME(ts) timespec_get(&ts, TIME_UTC)
# endif

static int64_t
timeout_get_tick(void)
{
  struct timespec ts = { 0 };
  GETTIME(&ts);
  ts.tv_nsec += 500000; /* ミリ秒以下を四捨五入 */
  return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}
#endif

static int64_t
timeout_convert_to_msec(mrb_state *mrb, mrb_value msec)
{
  switch (mrb_type(msec)) {
    default:
      msec = mrb_funcall_argv(mrb, msec, mrb_intern_lit(mrb, "to_i"), 0, NULL);
      mrb_check_type(mrb, msec, MRB_TT_FIXNUM);
      /* fall through */
    case MRB_TT_FIXNUM: {
      int64_t n = (int64_t)mrb_fixnum(msec);
      if (n < 0) goto wrong;
      return n;
    }
#ifndef MRB_WITHOUT_FLOAT
    case MRB_TT_FLOAT: {
      mrb_float n = mrb_float(msec);
      if (n < 0 || n > INT64_MAX) goto wrong;
      return n;
    }
#endif
  }

wrong:
  mrb_raise(mrb, E_RANGE_ERROR, "timeout seconds too huge (or negative)");
  return 0; /* not reached */
}

static mrb_value
mrb_s_regist_timeout(mrb_state *mrb, mrb_value mod)
{
  /*
   * call-seq:
   *  _regist_timeout(msec) -> tag
   *
   * This is internal document. It's trying to avoid being documented.
   *
   * <tt>tag</tt> は、識別子として扱われる RBreak オブジェクトです。
   * RBreak::proc に呼び出し元のブロックオブジェクトが格納されます。
   * RBreak::value にはtagとして生成された自分自身が格納されます。
   * タイムアウト時のコールスタックは、シングルトンクラスのインスタンス変数"@backtrace"に格納されます。
   */

  mrb_value extra, tagcont;
  struct RBreak *tag;
  struct RProc *caller;
  mrb_ssize nentry;
  struct mrb_timeout_manager *m;
  struct mrb_timeout_entry *e;
  int64_t msec;

  mrb_value msecv;
  mrb_get_args(mrb, "o", &msecv);
  msec = timeout_convert_to_msec(mrb, msecv);

  if (!mrb->c || !mrb->c->ci || mrb->c->ci <= mrb->c->cibase ||
      (caller = mrb->c->ci[-1].proc) == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "caller is not in ruby");
    caller = NULL; /* not reached */
  }

  get_timeout_data(mrb, &m, &extra, &nentry);
  if (nentry >= TIMEOUT_ENTRY_MAX) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "reached limitation for timeout entries");
  }

  m->entries = (struct mrb_timeout_entry *)mrb_realloc(mrb, m->entries, sizeof(struct mrb_timeout_entry) * (nentry + 1));
  e = &m->entries[nentry];
  e->alerm = msec + timeout_get_tick();
  e->activate = TRUE;

  tagcont = mrb_obj_value(mrb_obj_alloc(mrb, MRB_TT_ARRAY, mrb->object_class));
  tag = (struct RBreak*)mrb_obj_alloc(mrb, MRB_TT_BREAK, mrb->object_class);
  mrb_ary_push(mrb, tagcont, mrb_obj_value(tag));
  mrb_break_proc_set(tag, caller);
  mrb_break_value_set(tag, tagcont);
  TIMEOUT_SET_EXTRA(mrb, extra, nentry, TIMEOUT_TAG_FIELD, tagcont);

  if (nentry == 0 || e->alerm < m->next_alerm) {
    m->next_alerm = e->alerm;
  }

  return tagcont;
}

static struct mrb_timeout_entry *
lookup_timeout_entry_by_tag(struct mrb_timeout_manager *m, const mrb_value *xe, mrb_ssize nentry, const struct RObject *tag)
{
  struct mrb_timeout_entry *e = m->entries;

  for (; nentry > 0; nentry --, xe ++, e ++) {
    if (mrb_obj_ptr(*xe) == tag) {
      return e;
    }
  }

  return NULL;
}

static mrb_value
mrb_s_unregist_timeout(mrb_state *mrb, mrb_value mod)
{
  mrb_value extra;
  mrb_ssize nentry;
  struct mrb_timeout_manager *m;
  struct mrb_timeout_entry *e;

  mrb_value tag;
  mrb_get_args(mrb, "o", &tag);

  if (mrb_nil_p(tag)) return mrb_nil_value();
  mrb_check_type(mrb, tag, MRB_TT_ARRAY);
  mrb_check_type(mrb, mrb_ary_ref(mrb, tag, 0), MRB_TT_BREAK);

  get_timeout_data(mrb, &m, &extra, &nentry);
  e = lookup_timeout_entry_by_tag(m, RARRAY_PTR(extra), nentry, (struct RObject *)mrb_ptr(tag));

  if (e) {
    intptr_t index = e - m->entries;

    e->activate = FALSE;
    mrb_ary_splice(mrb, extra, index * TIMEOUT_FIELD_IN_ENTRIES, TIMEOUT_FIELD_IN_ENTRIES, mrb_undef_value());
    nentry --;
    memmove(e, e + 1, sizeof(*e) * (nentry - index));
    m->entries = (struct mrb_timeout_entry*)mrb_realloc(mrb, m->entries, sizeof(*e) * nentry);

    e = m->entries;
    if (e) {
      int64_t next_alerm = INT64_MAX;

      for (; nentry > 0; nentry --, e ++) {
        if (e->activate && e->alerm < next_alerm) {
          next_alerm = e->alerm;
        }
      }

      m->next_alerm = next_alerm;
    }
  }

  return mrb_nil_value();
}

static mrb_interrupt_func mrb_timeout_interrupt;

static uint32_t
mrb_timeout_interrupt(mrb_state *mrb, void *udata, uint32_t flags)
{
  struct mrb_timeout_manager *m = (struct mrb_timeout_manager *)udata;
  int64_t time = timeout_get_tick();

  if (m->entries && time >= m->next_alerm) {
    int64_t next_alerm = INT64_MAX;
    struct mrb_timeout_entry *e, *tope;
    mrb_ssize i;

    mrb_value extra;
    mrb_ssize nentry;
    get_timeout_extra(mrb, &extra, &nentry);

    e = m->entries + nentry - 1;
    tope = NULL;
    for (i = nentry; i > 0; i --, e --) {
      if (e->activate) {
        if (time >= e->alerm) {
          e->activate = FALSE;
          tope = e;
        }
        else if (e->alerm < next_alerm) {
          next_alerm = e->alerm;
        }
      }
    }

    if (tope) {
      mrb_value tag = RARRAY_PTR(extra)[tope - m->entries];
      mrb_value stag = mrb_singleton_class(mrb, tag);
      mrb_iv_set(mrb, stag, mrb_intern_lit(mrb, "@backtrace"), mrb_get_backtrace(mrb));
      mrb_check_type(mrb, tag, MRB_TT_ARRAY);
      tag = mrb_ary_ref(mrb, tag, 0);
      mrb_check_type(mrb, tag, MRB_TT_BREAK);
      m->next_alerm = next_alerm;
      mrb_exc_raise(mrb, tag);
    }
  }

  return MRB_INTERRUPT_KEEP;
}

void
mrb_mruby_timeout_gem_init(mrb_state* mrb)
{
  struct RClass *timeout;
  struct RData *rdata;

  rdata = mrb_data_object_alloc(mrb, mrb->object_class, NULL, &mrb_timeout_type);
  rdata->data = mrb_calloc(mrb, 1, sizeof(struct mrb_timeout_manager));
  mrb_gv_set(mrb, ID_TIMEOUT_MANAGER, mrb_obj_value(rdata));
  mrb_interrupt_regist(mrb, mrb_timeout_interrupt, rdata->data);
  mrb_gv_set(mrb, ID_TIMEOUT_EXTRA, mrb_ary_new(mrb));

  timeout = mrb_define_module(mrb, "Timeout");
  mrb_define_class_method(mrb, timeout, "_regist_timeout", mrb_s_regist_timeout, MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb, timeout, "_unregist_timeout", mrb_s_unregist_timeout, MRB_ARGS_REQ(1));
}

void
mrb_mruby_timeout_gem_final(mrb_state* mrb)
{
  mrb_value m = mrb_gv_get(mrb, ID_TIMEOUT_MANAGER);
  void *p = mrb_data_check_get_ptr(mrb, m, &mrb_timeout_type);

  if (p) {
    struct RData *d = RDATA(m);
    mrb_timeout_free(mrb, d->data);
    d->data = NULL;
    d->type = NULL;
  }

  mrb_interrupt_unregist(mrb, mrb_timeout_interrupt);
}
