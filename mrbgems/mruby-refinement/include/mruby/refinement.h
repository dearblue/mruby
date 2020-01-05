/**
** @file mruby/refinement.h - the Ruby's refinements feature
**
** See Copyright Notice in mruby.h
*/

#ifndef MRUBY_REFILEMENT_H
#define MRUBY_REFILEMENT_H

#include <mruby.h>

#ifndef MRB_USE_REFINEMENT
# error mruby-refinement need 'MRB_USE_REFINEMENT' in your build configuration
#endif

/**
 * The Ruby's refinements feature for mruby
 */
MRB_BEGIN_DECL

struct RClass;

/**
 * Define a refinement module.
 *
 * You can define a method from C for a refinement module that will be the return value.
 *
 *      !!!c
 *      struct RClass *translator = mrb_define_module(mrb, "Translator");
 *      struct RClass *refine_str = mrb_define_refinement(mrb, translator, mrb->string_class);
 *      mrb_define_method(mrb, refine_str, "to_klingon", to_klingon, MRB_ARGS_ANY());
 *      mrb_define_method(mrb, refine_str, "to_namekians", to_namekians, MRB_ARGS_ANY());
 *
 * The Code by C above is approximately equal to the code by the following Ruby:
 *
 *      !!!ruby
 *      module Translator
 *        refine String do
 *          def to_klingon(*args)
 *            ...
 *          end
 *
 *          def to_namekians(*args)
 *            ...
 *          end
 *        end
 *      end
 *
 * @param mrb The current mruby state.
 * @param outer The outer module for the refinements.
 * @param target The target class / module.
 * @return [struct RClass *] Reference to the newly refinement module.
 */
MRB_API struct RClass *mrb_define_refinement(mrb_state *mrb, struct RClass *outer, struct RClass *target);

MRB_END_DECL

#endif /* MRUBY_REFINEMENT_H */
