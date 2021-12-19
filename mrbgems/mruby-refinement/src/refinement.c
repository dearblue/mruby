/**
** @file refinement.c
**
** See Copyright Notice in mruby.h
*/

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/hash.h>
#include <mruby/opcode.h>
#include <mruby/presym.h>
#include <mruby/proc.h>
#include <mruby/refinement.h>
#include <mruby/string.h>
#include <mruby/variable.h>

#define ID_refinements MRB_SYM(__refinements__)
#define CINFO_NONE 0 /* from src/vm.c */
#define CINFO_SKIP 1 /* from src/vm.c */
#define CALLER_VM_P(ci) ((ci)->cci == CINFO_NONE || (ci)->cci == CINFO_SKIP)

mrb_value mrb_refinement_yield_with_class(mrb_state *mrb, mrb_value b, mrb_int argc, const mrb_value *argv, mrb_value self, struct RClass *c, struct RArray *actrefs);

static struct RArray *
ary_dup(mrb_state *mrb, struct RArray *orig)
{
  struct RArray *dup = MRB_OBJ_ALLOC(mrb, MRB_TT_ARRAY, mrb->array_class);
  mrb_ary_replace(mrb, mrb_obj_value(dup), mrb_obj_value(orig));
  return dup;
}

static struct RClass *
class_distil(struct RClass *c)
{
  while (c && c->tt == MRB_TT_ICLASS) {
    c = c->c;
  }
  return c;
}

static mrb_bool
method_caller_p(mrb_state *mrb)
{
  struct mrb_context *c = mrb->c;
  mrb_callinfo *ci = c->ci;

  if (ci && ci - c->cibase > 0 && ci[-1].proc) {
    const struct RProc *proc = ci[-1].proc;
    const uint32_t method_flags = MRB_PROC_SCOPE | MRB_PROC_STRICT;

    for (; proc; proc = proc->upper) {
      if ((proc->flags & method_flags) == method_flags) {
        return TRUE;
      }
    }

    return FALSE;
  }
  else {
    return TRUE;
  }
}

static void
refinement_using_check_caller(mrb_state *mrb, mrb_bool on_module)
{
  if (method_caller_p(mrb)) {
    const char *mesg = on_module ? "Module#using is not permitted in methods" :
                                   "main.using is permitted only at toplevel";
    mrb_raise(mrb, E_RUNTIME_ERROR, mesg);
  }
}

static void
refinement_using_to_upper(mrb_state *mrb, mrb_callinfo *ci, struct RArray *actrefs)
{
  const struct RProc *proc = ci->proc;

  mrb_vm_ci_activated_refinements_set(ci, actrefs);

  if (proc && !MRB_PROC_SCOPE_P(proc)) {
    mrb_callinfo *cihead = ci - 1;
    const mrb_callinfo *const cibase = mrb->c->cibase;

    for (; proc; proc = proc->upper) {
      for (ci = cihead; ci - cibase >= 0; ci--) {
        if (ci->proc == proc) {
          mrb_vm_ci_activated_refinements_set(ci, actrefs);
          cihead = ci - 1;
          break;
        }
      }

      if (MRB_PROC_EXTRA_P(proc)) {
        proc->body.extra->attached_refinements = actrefs;
        mrb_field_write_barrier(mrb, (struct RBasic*)proc, (struct RBasic*)actrefs);
      }
      else if (proc->color != MRB_GC_RED && !MRB_PROC_CFUNC_P(proc)) {
        struct mrb_proc_extra *ex = (struct mrb_proc_extra*)mrb_malloc(mrb, sizeof(struct mrb_proc_extra));
        ex->irep = proc->body.irep_direct;
        ex->attached_refinements = actrefs;
        MRB_PROC_SET_EXTRA((struct RProc*)proc, ex);
        mrb_field_write_barrier(mrb, (struct RBasic*)proc, (struct RBasic*)actrefs);
      }

      if (MRB_PROC_SCOPE_P(proc) || MRB_PROC_SEPARATE_REFINEMENTS_P(proc)) {
        break;
      }
    }
  }
}

static int
refinement_using_index(mrb_state *mrb, struct RArray *actrefs, struct RHash *map)
{
  mrb_ssize reflen = ARY_LEN(actrefs);
  const mrb_value *refptr0 = ARY_PTR(actrefs);
  const mrb_value *refptr = refptr0;

  for (; reflen > 0; reflen--, refptr++) {
    mrb_assert(mrb_hash_p(*refptr));
    struct RHash *ptr = mrb_hash_ptr(*refptr);
    if (ptr == map) {
      return refptr - refptr0;
    }
  }

  return -1;
}

static void
refinement_using_insert(mrb_state *mrb, struct RArray *actrefs, struct RClass *modp)
{
  modp = class_distil(modp);
  mrb_value map = mrb_iv_get(mrb, mrb_obj_value(modp), ID_refinements);
  if (mrb_nil_p(map)) return;
  mrb_ensure_hash_type(mrb, map);

  int idx = refinement_using_index(mrb, actrefs, mrb_hash_ptr(map));
  if (idx < 0) {
    mrb_ary_splice(mrb, mrb_obj_value(actrefs), 0, 0, map);
  }
  else {
    mrb_ary_set(mrb, mrb_obj_value(actrefs), idx, map);
  }
}

static void
mrb_mod_using(mrb_state *mrb, mrb_value mod, mrb_bool on_module)
{
  mrb_check_type(mrb, mod, MRB_TT_MODULE);
  refinement_using_check_caller(mrb, on_module);

  struct mrb_context *c = mrb->c;
  mrb_callinfo *ci = (c->ci > c->cibase) ? c->ci - 1 : c->cibase;
  struct RArray *actrefs = mrb_vm_ci_activated_refinements(ci);
  int refm_index;
  if (actrefs == NULL) {
    actrefs = mrb_ary_ptr(mrb_ary_new(mrb));
    refm_index = 0;
  }
  else {
    actrefs = ary_dup(mrb, actrefs);
    mrb_value map = mrb_iv_get(mrb, mod, ID_refinements);
    if (mrb_nil_p(map)) {
      refm_index = -1;
    }
    else {
      mrb_ensure_hash_type(mrb, map);
      refm_index = refinement_using_index(mrb, actrefs, mrb_hash_ptr(map));
    }
    if (refm_index < 0) {
      refm_index = 0;
    }
  }

  struct RClass *m = mrb_class_ptr(mod);
  for (; m; m = m->super) {
    if (m->flags & MRB_FL_CLASS_IS_PREPENDED) {
      ;
    }
    else {
      refinement_using_insert(mrb, actrefs, m);
    }
  }

  refinement_using_to_upper(mrb, ci, actrefs);
}

static mrb_value
mrb_mod_using_m_common(mrb_state *mrb, mrb_value self, mrb_bool on_module)
{
  mrb_value mod;
  mrb_get_args(mrb, "o", &mod);

  mrb_mod_using(mrb, mod, on_module);

  return self;
}

static mrb_value
mrb_mod_using_m(mrb_state *mrb, mrb_value self)
{
  return mrb_mod_using_m_common(mrb, self, TRUE);
}

static mrb_value
mrb_main_using(mrb_state *mrb, mrb_value self)
{
  return mrb_mod_using_m_common(mrb, self, FALSE);
}

static mrb_value
mrb_mod_used_modules_m(mrb_state *mrb, mrb_value self)
{
  const struct mrb_context *c = mrb->c;
  const mrb_callinfo *ci = c->ci;
  struct RArray *actrefs = (ci > c->cibase) ? mrb_vm_ci_activated_refinements(&ci[-1]) : NULL;

  if (!actrefs) {
    return mrb_ary_new(mrb);
  }

  mrb_ssize len = ARY_LEN(actrefs);
  mrb_value result = mrb_ary_new_capa(mrb, len);
  const mrb_value *mod = ARY_PTR(actrefs);
  const mrb_value key = mrb_symbol_value(MRB_SYM(OwnerModule));
  for (; len > 0; len--, mod++) {
    mrb_value m = *mod;
    mrb_ensure_hash_type(mrb, m);
    m = mrb_hash_get(mrb, m, key);
    mrb_check_type(mrb, m, MRB_TT_MODULE);
    mrb_ary_push(mrb, result, m);
  }

  return result;
}

static mrb_value
mrb_mod_refine_m(mrb_state *mrb, mrb_value mod)
{
  struct RClass *target;
  mrb_value blk;
  mrb_get_args(mrb, "c&!", &target, &blk);

  if ((mrb_obj_ptr(blk)->flags & (MRB_PROC_STRICT | MRB_PROC_ORPHAN))) {
    // either it is a indirectly given block; e.g. `refine Object, &->{}`
    mrb_raise(mrb, E_ARGUMENT_ERROR, "can't pass a Proc as a block to Module#refine");
  }

  struct RClass *refine = mrb_define_refinement(mrb, mrb_class_ptr(mod), target);

  // `#module_eval` of mruby-class-ext cannot be used.
  // Because it is necessary to temporarily `using mod` and execute `blk`.
  // But does not consider "refinements" in C space.

  const struct RProc *blkp = mrb_proc_ptr(blk);
  if (MRB_PROC_CFUNC_P(blkp)) {
    mrb_yield_with_class(mrb, blk, 0, NULL, mrb_obj_value(refine), refine);
    return mrb_obj_value(refine);
  }
  else {
    struct RArray *actrefs = MRB_PROC_ATTACHED_REFINEMENTS(blkp);
    if (actrefs) {
      actrefs = ary_dup(mrb, actrefs);
      refinement_using_insert(mrb, actrefs, mrb_class_ptr(mod));
    }
    else {
      mrb_value map = mrb_iv_get(mrb, mod, ID_refinements);
      mrb_ensure_hash_type(mrb, map);
      actrefs = mrb_ary_ptr(mrb_ary_new_from_values(mrb, 1, &map));
    }

    mrb_callinfo *ci = mrb->c->ci;
    if (CALLER_VM_P(ci)) {
      // Make `Module#refine` return the defined `refine` value.
      ci->stack[0] = mrb_obj_value(refine);
      ci->stack++;
      ci->activated_refinements = actrefs;
      ci->u.target_class = refine;
      mrb_yield_cont(mrb, blk, mrb_obj_value(refine), 0, NULL);
      return ci->stack[0];
    }
    else {
      mrb_refinement_yield_with_class(mrb, blk, 0, NULL, mrb_obj_value(refine), refine, actrefs);
      return mrb_obj_value(refine);
    }
  }
}

MRB_API struct RClass *
mrb_define_refinement(mrb_state *mrb, struct RClass *outer, struct RClass *target)
{
  if (target->tt != MRB_TT_CLASS && target->tt != MRB_TT_MODULE && target->tt != MRB_TT_SCLASS) {
    mrb_raise(mrb, E_TYPE_ERROR, "wrong argument type (expected Class or Module)");
  }
  mrb_check_type(mrb, mrb_obj_value(outer), MRB_TT_MODULE);
  mrb_check_frozen(mrb, outer);

  mrb_value rhash = mrb_obj_iv_get(mrb, (struct RObject*)outer, ID_refinements);
  if (!mrb_hash_p(rhash)) {
    rhash = mrb_hash_new(mrb);
    mrb_hash_set(mrb, rhash, mrb_symbol_value(MRB_SYM(OwnerModule)), mrb_obj_value(outer));
    mrb_obj_iv_set(mrb, (struct RObject*)outer, ID_refinements, rhash);
  }

  mrb_value rclass = mrb_hash_fetch(mrb, rhash, mrb_obj_value(target), mrb_nil_value());
  struct RClass *rp;
  if (mrb_type(rclass) == MRB_TT_REFINEMENT) {
    rp = mrb_class_ptr(rclass);
  }
  else {
    rp = mrb_module_new(mrb);
    rp->tt = MRB_TT_REFINEMENT;
    rp->super = target;
    mrb_obj_iv_set(mrb, (struct RObject*)rp, MRB_SYM(__outer__), mrb_obj_value(outer));
    mrb_hash_set(mrb, rhash, mrb_obj_value(target), mrb_obj_value(rp));
  }

  return rp;
}

void
mrb_mruby_refinement_gem_init(mrb_state *mrb)
{
  mrb_define_method(mrb, mrb->module_class, "using", mrb_mod_using_m, MRB_ARGS_REQ(1)); /* Ruby 2.0 feature */
  mrb_define_method(mrb, mrb->module_class, "refine", mrb_mod_refine_m, MRB_ARGS_REQ(1)); /* Ruby 2.0 feature */

  mrb_define_class_method(mrb, mrb->module_class, "used_modules", mrb_mod_used_modules_m, MRB_ARGS_NONE()); /* Ruby 2.0 feature */

  mrb_undef_method(mrb, mrb->class_class, "refine");

  mrb_define_singleton_method(mrb, mrb->top_self, "using", mrb_main_using, MRB_ARGS_REQ(1)); /* Ruby 2.0 feature */
}

void
mrb_mruby_refinement_gem_final(mrb_state *mrb)
{
}
