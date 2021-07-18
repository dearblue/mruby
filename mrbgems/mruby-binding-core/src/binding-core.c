#include <mruby.h>
#include <mruby/array.h>
#include <mruby/hash.h>
#include <mruby/proc.h>
#include <mruby/variable.h>
#include <mruby/presym.h>
#include <mruby/opcode.h>
#include <mruby/debug.h>

void mrb_proc_merge_lvar(mrb_state *mrb, mrb_irep *irep, struct REnv *env, int num, const mrb_sym *lv, const mrb_value *stack);
mrb_value mrb_proc_local_variables(mrb_state *mrb, const struct RProc *proc);
const struct RProc *mrb_proc_get_caller(mrb_state *mrb, struct REnv **env);

static mrb_int
binding_extract_pc(mrb_state *mrb, mrb_value binding)
{
  mrb_value obj = mrb_iv_get(mrb, binding, MRB_SYM(pc));
  if (mrb_nil_p(obj)) {
    return -1;
  }
  else {
    mrb_check_type(mrb, obj, MRB_TT_INTEGER);
    return mrb_int(mrb, obj);
  }
}

const struct RProc *
mrb_binding_extract_proc(mrb_state *mrb, mrb_value binding)
{
  mrb_value obj = mrb_iv_get(mrb, binding, MRB_SYM(proc));
  mrb_check_type(mrb, obj, MRB_TT_PROC);
  return mrb_proc_ptr(obj);
}

struct REnv *
mrb_binding_extract_env(mrb_state *mrb, mrb_value binding)
{
  mrb_value obj = mrb_iv_get(mrb, binding, MRB_SYM(env));
  if (mrb_nil_p(obj)) {
    return NULL;
  }
  else {
    mrb_check_type(mrb, obj, MRB_TT_ENV);
    return (struct REnv *)mrb_obj_ptr(obj);
  }
}

static void
binding_type_ensure(mrb_state *mrb, mrb_value obj)
{
  if (!mrb_obj_is_kind_of(mrb, obj, mrb_class_get_id(mrb, MRB_SYM(Binding)))) {
    mrb_raise(mrb, E_TYPE_ERROR, "not a binding");
  }
}

static mrb_irep*
lvspace_irep_new(mrb_state *mrb, int nlocals)
{
  static const mrb_code iseq_dummy[] = { OP_RETURN, 0 };

  mrb_irep *irep = mrb_add_irep(mrb);
  irep->flags = MRB_ISEQ_NO_FREE;
  irep->iseq = iseq_dummy;
  irep->ilen = sizeof(iseq_dummy) / sizeof(iseq_dummy[0]);
  irep->lv = (mrb_sym*)mrb_calloc(mrb, nlocals, sizeof(mrb_sym)); /* initial allocation for dummy */
  irep->nlocals = nlocals;
  irep->nregs = nlocals;
  return irep;
}

static mrb_value
binding_initialize_copy(mrb_state *mrb, mrb_value binding)
{
  struct {
    mrb_value obj, proc, env;
    struct RProc *procp;
    struct REnv *envp;
  } src;
  mrb_get_args(mrb, "o", &src.obj);
  binding_type_ensure(mrb, src.obj);
  mrb_check_frozen(mrb, mrb_obj_ptr(binding));

  src.proc = mrb_iv_get(mrb, binding, MRB_SYM(proc));
  mrb_assert(mrb_proc_p(src.proc));
  src.procp = mrb_proc_ptr(src.proc);
  mrb_assert(!MRB_PROC_CFUNC_P(src.procp));
  src.env = mrb_iv_get(mrb, binding, MRB_SYM(env));
  mrb_assert(mrb_env_p(src.env));
  src.envp = (struct REnv*)mrb_obj_ptr(src.env);

  struct RProc *lvspace = MRB_OBJ_ALLOC(mrb, MRB_TT_PROC, mrb->proc_class);
  mrb_irep *irep = lvspace_irep_new(mrb, (src.procp->body.irep->nlocals > 0 ? src.procp->body.irep->nlocals : 1));
  lvspace->body.irep = irep;
  lvspace->upper = src.procp->upper;
  memcpy((mrb_sym*)irep->lv, src.procp->body.irep->lv, irep->nlocals * sizeof(mrb_sym));
  if (src.procp->e.env) {
    lvspace->e.env = src.procp->e.env;
    lvspace->flags |= MRB_PROC_ENVSET;
  }

  struct REnv *env = MRB_OBJ_ALLOC(mrb, MRB_TT_ENV, NULL);
  mrb_value *stacks = (mrb_value*)mrb_calloc(mrb, MRB_ENV_LEN(src.envp) + 1, sizeof(mrb_value));
  env->cxt = src.envp->cxt;
  env->mid = src.envp->mid;
  env->stack = stacks;
  memcpy(env->stack, src.envp->stack, (MRB_ENV_LEN(src.envp) + 1) * sizeof(mrb_value));
  MRB_ENV_SET_LEN(env, MRB_ENV_LEN(src.envp));

  mrb_iv_set(mrb, binding, MRB_SYM(proc), mrb_obj_value(lvspace));
  mrb_iv_set(mrb, binding, MRB_SYM(env), mrb_obj_value(env));

  return binding;
}

static void
binding_local_variable_name_check(mrb_state *mrb, mrb_sym id)
{
  if (id == 0) {
  badname:
    mrb_raisef(mrb, E_NAME_ERROR, "wrong local variable name %!n for binding", id);
  }

  mrb_int len;
  const char *name = mrb_sym_name_len(mrb, id, &len);
  if (len == 0) {
    goto badname;
  }

  if (ISASCII(*name) && !(*name == '_' || ISLOWER(*name))) {
    goto badname;
  }
  len--;
  name++;

  for (; len > 0; len--, name++) {
    if (ISASCII(*name) && !(*name == '_' || ISALNUM(*name))) {
      goto badname;
    }
  }
}

static mrb_value *
binding_local_variable_search(mrb_state *mrb, const struct RProc *proc, struct REnv *env, mrb_sym varname)
{
  binding_local_variable_name_check(mrb, varname);

  while (proc) {
    if (MRB_PROC_CFUNC_P(proc)) break;

    const mrb_irep *irep = proc->body.irep;
    const mrb_sym *lv;
    if (irep && (lv = irep->lv)) {
      for (int i = 0; i + 1 < irep->nlocals; i++, lv++) {
        if (varname == *lv) {
          return (env && MRB_ENV_LEN(env) > i) ? &env->stack[i + 1] : NULL;
        }
      }
    }

    if (MRB_PROC_SCOPE_P(proc)) break;
    env = MRB_PROC_ENV(proc);
    proc = proc->upper;
  }

  return NULL;
}

/*
 * call-seq:
 *  local_variable_defined?(symbol) -> bool
 */
static mrb_value
binding_local_variable_defined_p(mrb_state *mrb, mrb_value self)
{
  mrb_sym varname;
  mrb_get_args(mrb, "n", &varname);

  const struct RProc *proc = mrb_binding_extract_proc(mrb, self);
  struct REnv *env = mrb_binding_extract_env(mrb, self);
  mrb_value *e = binding_local_variable_search(mrb, proc, env, varname);
  if (e) {
    return mrb_true_value();
  }
  else {
    return mrb_false_value();
  }
}

/*
 * call-seq:
 *  local_variable_get(symbol) -> object
 */
static mrb_value
binding_local_variable_get(mrb_state *mrb, mrb_value self)
{
  mrb_sym varname;
  mrb_get_args(mrb, "n", &varname);

  const struct RProc *proc = mrb_binding_extract_proc(mrb, self);
  struct REnv *env = mrb_binding_extract_env(mrb, self);
  mrb_value *e = binding_local_variable_search(mrb, proc, env, varname);
  if (!e) {
    mrb_raisef(mrb, E_NAME_ERROR, "local variable %!n is not defined", varname);
  }

  return *e;
}

static mrb_value
binding_local_variable_set(mrb_state *mrb, mrb_value self)
{
  mrb_sym varname;
  mrb_value obj;
  mrb_get_args(mrb, "no", &varname, &obj);

  const struct RProc *proc = mrb_binding_extract_proc(mrb, self);
  struct REnv *env = mrb_binding_extract_env(mrb, self);
  mrb_value *e = binding_local_variable_search(mrb, proc, env, varname);
  if (e) {
    *e = obj;
  }
  else {
    mrb_proc_merge_lvar(mrb, (mrb_irep*)proc->body.irep, env, 1, &varname, &obj);
  }

  return obj;
}

static mrb_value
binding_local_variables(mrb_state *mrb, mrb_value self)
{
  const struct RProc *proc = mrb_proc_ptr(mrb_iv_get(mrb, self, MRB_SYM(proc)));
  return mrb_proc_local_variables(mrb, proc);
}

static mrb_value
binding_receiver(mrb_state *mrb, mrb_value self)
{
  return mrb_iv_get(mrb, self, MRB_SYM(recv));
}

/*
 * call-seq:
 *  source_location -> [String, Integer]
 */
static mrb_value
binding_source_location(mrb_state *mrb, mrb_value self)
{
  if (mrb_iv_defined(mrb, self, MRB_SYM(source_location))) {
    return mrb_iv_get(mrb, self, MRB_SYM(source_location));
  }

  mrb_value srcloc;
  const struct RProc *proc = mrb_binding_extract_proc(mrb, self);
  if (!proc || MRB_PROC_CFUNC_P(proc) ||
      !proc->upper || MRB_PROC_CFUNC_P(proc->upper)) {
    srcloc = mrb_nil_value();
  }
  else {
    const mrb_irep *irep = proc->upper->body.irep;
    mrb_int pc = binding_extract_pc(mrb, self);
    if (pc < 0) {
      srcloc = mrb_nil_value();
    }
    else {
      const char *fname = mrb_debug_get_filename(mrb, irep, (uint32_t)pc);
      mrb_int fline = mrb_debug_get_line(mrb, irep, (uint32_t)pc);

      if (fname && fline >= 0) {
        srcloc = mrb_assoc_new(mrb, mrb_str_new_cstr(mrb, fname), mrb_fixnum_value(fline));
      }
      else {
        srcloc = mrb_nil_value();
      }
    }
  }

  if (!mrb_frozen_p(mrb_obj_ptr(self))) {
    mrb_iv_set(mrb, self, MRB_SYM(source_location), srcloc);
  }
  return srcloc;
}

mrb_value
mrb_binding_alloc(mrb_state *mrb)
{
  struct RObject *obj = MRB_OBJ_ALLOC(mrb, MRB_TT_OBJECT, mrb_class_get_id(mrb, MRB_SYM(Binding)));
  return mrb_obj_value(obj);
}

struct RProc*
mrb_binding_wrap_lvspace(mrb_state *mrb, const struct RProc *proc, struct REnv **envp)
{
  /*
   * local variable space: It is a space to hold the top-level variable of
   * binding.eval and binding.local_variable_set.
   */

  struct RProc *lvspace = MRB_OBJ_ALLOC(mrb, MRB_TT_PROC, mrb->proc_class);
  lvspace->body.irep = lvspace_irep_new(mrb, 1);
  lvspace->upper = proc;
  if (*envp) {
    lvspace->e.env = *envp;
    lvspace->flags |= MRB_PROC_ENVSET;
  }

  *envp = MRB_OBJ_ALLOC(mrb, MRB_TT_ENV, NULL);
  (*envp)->stack = (mrb_value*)mrb_calloc(mrb, 1, sizeof(mrb_value));
  (*envp)->stack[0] = lvspace->e.env ? lvspace->e.env->stack[0] : mrb_nil_value();
  (*envp)->cxt = lvspace->e.env ? lvspace->e.env->cxt : mrb->c;
  (*envp)->mid = 0;
  (*envp)->flags = MRB_ENV_CLOSED | MRB_ENV_HEAPED;
  MRB_ENV_SET_LEN(*envp, 1);

  return lvspace;
}

static mrb_value
mrb_f_binding(mrb_state *mrb, mrb_value self)
{
  mrb_value binding;
  struct RProc *proc;
  struct REnv *env;

  binding = mrb_binding_alloc(mrb);
  proc = (struct RProc*)mrb_proc_get_caller(mrb, &env);
  if (!env || MRB_PROC_CFUNC_P(proc)) {
    proc = NULL;
    env = NULL;
  }

  if (proc && !MRB_PROC_CFUNC_P(proc)) {
    const mrb_irep *irep = proc->body.irep;
    mrb_iv_set(mrb, binding, MRB_SYM(pc), mrb_fixnum_value(mrb->c->ci[-1].pc - irep->iseq - 1 /* step back */));
  }
  proc = mrb_binding_wrap_lvspace(mrb, proc, &env);
  mrb_iv_set(mrb, binding, MRB_SYM(proc), mrb_obj_value(proc));
  mrb_iv_set(mrb, binding, MRB_SYM(recv), self);
  mrb_iv_set(mrb, binding, MRB_SYM(env), mrb_obj_value(env));
  return binding;
}

void
mrb_mruby_binding_core_gem_init(mrb_state *mrb)
{
  struct RClass *binding = mrb_define_class(mrb, "Binding", mrb->object_class);
  mrb_undef_class_method(mrb, binding, "new");
  mrb_undef_class_method(mrb, binding, "allocate");

  mrb_define_method(mrb, mrb->kernel_module, "binding", mrb_f_binding, MRB_ARGS_NONE());

  mrb_define_method(mrb, binding, "initialize_copy", binding_initialize_copy, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, binding, "local_variable_defined?", binding_local_variable_defined_p, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, binding, "local_variable_get", binding_local_variable_get, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, binding, "local_variable_set", binding_local_variable_set, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, binding, "local_variables", binding_local_variables, MRB_ARGS_NONE());
  mrb_define_method(mrb, binding, "receiver", binding_receiver, MRB_ARGS_NONE());
  mrb_define_method(mrb, binding, "source_location", binding_source_location, MRB_ARGS_NONE());
  mrb_define_method(mrb, binding, "inspect", mrb_any_to_s, MRB_ARGS_NONE());
}

void
mrb_mruby_binding_core_gem_final(mrb_state *mrb)
{
}
