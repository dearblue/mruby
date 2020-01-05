/**
** @file refine.c
**
** See Copyright Notice in mruby.h
*/

#include <mruby.h>
#include <mruby/refinement.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mruby/proc.h>
#include <mruby/array.h>
#include <mruby/hash.h>
#include <mruby/variable.h>
#include <mruby/presym.h>

static mrb_bool
called_by_method_p(mrb_state *mrb)
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
validate_caller_for_using(mrb_state *mrb)
{
  if (called_by_method_p(mrb)) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "using is not permitted in methods");
  }
}

static void
using_refinements_to_upper(mrb_state *mrb, mrb_callinfo *ci, struct RArray *actrefs)
{
  const struct RProc *proc = ci->proc;

  ci->activated_refinements = actrefs;

  if (proc && !MRB_PROC_SCOPE_P(proc)) {
    mrb_callinfo *cihead = ci - 1;
    mrb_callinfo *cistop = mrb->c->cibase;

    for (; proc; proc = proc->upper) {
      for (ci = cihead; ci - cistop >= 0; ci--) {
        if (ci->proc == proc) {
          ci->activated_refinements = actrefs;
          cihead = ci - 1;
          break;
        }
      }

      if (MRB_PROC_SCOPE_P(proc)) {
        break;
      }
    }
  }
}

static mrb_bool
using_refinement_p(mrb_state *mrb, struct RArray *actrefs, mrb_value mod, mrb_value map)
{
  const mrb_value *refptr = ARY_PTR(actrefs);
  intptr_t reflen = ARY_LEN(actrefs);

  for (; reflen > 0; reflen--, refptr++) {
    if (mrb_obj_eq(mrb, *refptr, map) ||
        mrb_obj_eq(mrb, *refptr, mod)) {
      return TRUE;
    }
  }

  return FALSE;
}

static void
mrb_mod_using(mrb_state *mrb, mrb_value mod)
{
  mrb_sym id_refinements = mrb_intern_lit(mrb, "__refinements__");
  struct mrb_context *c = mrb->c;
  mrb_callinfo *ci = (c->ci > c->cibase ? c->ci - 1 : c->cibase);
  mrb_value map = mod;

  mrb_check_type(mrb, mod, MRB_TT_MODULE);
  validate_caller_for_using(mrb);

  map = mrb_iv_get(mrb, mod, id_refinements);
  if (!mrb_hash_p(map)) {
    map = mod;
  }

  struct RArray *actrefs;
  if (ci->activated_refinements == NULL) {
    actrefs = mrb_ary_ptr(mrb_ary_new(mrb));
  }
  else if (using_refinement_p(mrb, ci->activated_refinements, mod, map)) {
    return;
  }
  else {
    actrefs = mrb_ary_ptr(mrb_obj_clone(mrb, mrb_obj_value(ci->activated_refinements)));
  }

  using_refinements_to_upper(mrb, ci, actrefs);
  mrb_ary_push(mrb, mrb_obj_value(actrefs), map);
}

static mrb_value
mrb_mod_using_m(mrb_state *mrb, mrb_value self)
{
  mrb_value mod;

  mrb_get_args(mrb, "o", &mod);
  mrb_mod_using(mrb, mod);

  return self;
}

static mrb_value
mrb_mod_used_modules_m(mrb_state *mrb, mrb_value self)
{
  const struct mrb_context *c = mrb->c;
  const mrb_callinfo *ci = c->ci;
  struct RArray *refines = (c->cibase < ci) ? ci[-1].activated_refinements : NULL;

  if (!refines) {
    return mrb_ary_new(mrb);
  }

  mrb_value arefs = mrb_obj_dup(mrb, mrb_obj_value(refines));
  refines = mrb_ary_ptr(arefs);
  mrb_ssize off = ARY_LEN(refines) - 1;
  const mrb_value *mod = ARY_PTR(refines) + off;
  const mrb_value key = mrb_symbol_value(MRB_SYM(Module));
  for (; off >= 0; off--, mod--) {
    mrb_value m = *mod;
    if (mrb_hash_p(m)) {
      m = mrb_hash_get(mrb, m, key);
    }
    mrb_ary_set(mrb, arefs, off, m);
  }

  return arefs;
}

static mrb_value
mrb_mod_refine_m(mrb_state *mrb, mrb_value mod)
{
  struct RClass *target;
  mrb_value blk;
  mrb_get_args(mrb, "c&!", &target, &blk);

  struct RClass *refine = mrb_refinement_new(mrb, mrb_class_ptr(mod), target);

  // using mod 相当のもとで blk を実行する必要がある
  //  --> C 空間では考慮しない
  // (ci->attached_refinements + mod) の activated_refinements を一時的にキャッシュする？
  //  --> 同一モジュールスコープ内でたくさん refine するとそれだけ RAM を食うため、導入することが好ましい
  //  --> キャッシュデータはどこに保持する？
  //      --> ci にキャッシュする --> せっかく減らしたのに……
  //      --> ci->activated_refinements->c が保持する --> GC へのインパクトと互換性が心配
  mrb_callinfo *ci = mrb->c->ci;
  if (ci->acc < 0) {
    return mrb_yield_with_class(mrb, blk, 0, NULL, mrb_obj_value(refine), refine);
  }
  else {
    struct RArray *actrefs = ci->activated_refinements;
    if (actrefs) {
      actrefs = mrb_ary_ptr(mrb_obj_dup(mrb, mrb_obj_value(actrefs)));
    }
    else {
      actrefs = mrb_ary_ptr(mrb_ary_new_capa(mrb, 1));
    }
    mrb_ary_push(mrb, mrb_obj_value(actrefs), mod);
    ci->activated_refinements = actrefs;
    mrb_vm_ci_target_class_set(ci, refine);
    return mrb_yield_cont(mrb, blk, mrb_obj_value(refine), 0, NULL);
  }
}

MRB_API struct RClass*
mrb_refinement_new(mrb_state *mrb, struct RClass *container, struct RClass *target)
{
  mrb_sym id_refinements = mrb_intern_lit(mrb, "__refinements__");

  mrb_check_type(mrb, mrb_obj_value(container), MRB_TT_MODULE);
  mrb_check_frozen(mrb, container);

  mrb_value rhash = mrb_obj_iv_get(mrb, (struct RObject*)container, id_refinements);
  if (!mrb_hash_p(rhash)) {
    rhash = mrb_hash_new(mrb);
    mrb_hash_set(mrb, rhash, mrb_symbol_value(MRB_SYM(Module)), mrb_obj_value(container));
    mrb_obj_iv_set(mrb, (struct RObject*)container, id_refinements, rhash);
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
    mrb_hash_set(mrb, rhash, mrb_obj_value(target), mrb_obj_value(rp));
  }

  return rp;
}

void
mrb_mruby_refinement_gem_init(mrb_state *mrb)
{
  struct RClass *mod = mrb->module_class;

  mrb_define_method(mrb, mod, "using", mrb_mod_using_m, MRB_ARGS_REQ(1)); /* Ruby-2.0 feature */
  mrb_define_method(mrb, mod, "refine", mrb_mod_refine_m, MRB_ARGS_REQ(1)); /* Ruby-2.0 feature */

  mrb_define_class_method(mrb, mod, "used_modules", mrb_mod_used_modules_m, MRB_ARGS_NONE()); /* Ruby-2.0 feature */

  mrb_undef_method(mrb, mrb->class_class, "refine");

  mrb_define_singleton_method(mrb, mrb->top_self, "using", mrb_mod_using_m, MRB_ARGS_REQ(1)); /* Ruby-2.0 feature */
}

void
mrb_mruby_refinement_gem_final(mrb_state *mrb)
{
}
