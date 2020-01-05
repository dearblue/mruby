/**
** @file mruby/refinement.h - the refinements feature
**
** See Copyright Notice in mruby.h
*/

#ifndef MRUBY_REFILEMENT_H
#define MRUBY_REFILEMENT_H

#include <mruby.h>

MRB_BEGIN_DECL

/**
 * Create a refinement module.
 *
 * You can define a method from C for the new refinement that will be the return value.
 *
 *      !!!c
 *      struct RClass *translator = mrb_define_module(mrb, "Translator");
 *      struct RClass *refines = mrb_refinement_new(mrb, translator, mrb->string_class);
 *      mrb_define_method(mrb, translator, "to_klingon", to_klingon, MRB_ARGS_ANY());
 *      mrb_define_method(mrb, translator, "to_namekians", to_namekians, MRB_ARGS_ANY());
 *
 * @param mrb The current mruby state.
 * @param container The outer module for the refinements.
 * @param target The target class / module.
 * @return [struct RClass *] Reference to the newly refinement module.
 */
MRB_API struct RClass *mrb_refinement_new(mrb_state *mrb, struct RClass *container, struct RClass *target);

MRB_END_DECL

#endif /* MRUBY_REFINEMENT_H */
