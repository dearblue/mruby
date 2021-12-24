/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 7 "mrbgems/mruby-compiler/core/parse.y"

#undef PARSER_DEBUG
#ifdef PARSER_DEBUG
# define YYDEBUG 1
#endif
#define YYSTACK_USE_ALLOCA 1

#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>
#include <mruby/error.h>
#include <mruby/throw.h>
#include <mruby/string.h>
#include <mruby/dump.h>
#include <mruby/presym.h>
#include "node.h"

#define YYLEX_PARAM p

typedef mrb_ast_node node;
typedef struct mrb_parser_state parser_state;
typedef struct mrb_parser_heredoc_info parser_heredoc_info;

static int yyparse(parser_state *p);
static int yylex(void *lval, parser_state *p);
static void yyerror(parser_state *p, const char *s);
static void yywarning(parser_state *p, const char *s);
static void backref_error(parser_state *p, node *n);
static void void_expr_error(parser_state *p, node *n);
static void tokadd(parser_state *p, int32_t c);

#define identchar(c) (ISALNUM(c) || (c) == '_' || !ISASCII(c))

typedef unsigned int stack_type;

#define BITSTACK_PUSH(stack, n) ((stack) = ((stack)<<1)|((n)&1))
#define BITSTACK_POP(stack)     ((stack) = (stack) >> 1)
#define BITSTACK_LEXPOP(stack)  ((stack) = ((stack) >> 1) | ((stack) & 1))
#define BITSTACK_SET_P(stack)   ((stack)&1)

#define COND_PUSH(n)    BITSTACK_PUSH(p->cond_stack, (n))
#define COND_POP()      BITSTACK_POP(p->cond_stack)
#define COND_LEXPOP()   BITSTACK_LEXPOP(p->cond_stack)
#define COND_P()        BITSTACK_SET_P(p->cond_stack)

#define CMDARG_PUSH(n)  BITSTACK_PUSH(p->cmdarg_stack, (n))
#define CMDARG_POP()    BITSTACK_POP(p->cmdarg_stack)
#define CMDARG_LEXPOP() BITSTACK_LEXPOP(p->cmdarg_stack)
#define CMDARG_P()      BITSTACK_SET_P(p->cmdarg_stack)

#define SET_LINENO(c,n) ((c)->lineno = (n))
#define NODE_LINENO(c,n) do {\
  if (n) {\
     (c)->filename_index = (n)->filename_index;\
     (c)->lineno = (n)->lineno;\
  }\
} while (0)

#define sym(x) ((mrb_sym)(intptr_t)(x))
#define nsym(x) ((node*)(intptr_t)(x))
#define nint(x) ((node*)(intptr_t)(x))
#define intn(x) ((int)(intptr_t)(x))
#define typen(x) ((enum node_type)(intptr_t)(x))

#define NUM_SUFFIX_R   (1<<0)
#define NUM_SUFFIX_I   (1<<1)

static inline mrb_sym
intern_cstr_gen(parser_state *p, const char *s)
{
  return mrb_intern_cstr(p->mrb, s);
}
#define intern_cstr(s) intern_cstr_gen(p,(s))

static inline mrb_sym
intern_gen(parser_state *p, const char *s, size_t len)
{
  return mrb_intern(p->mrb, s, len);
}
#define intern(s,len) intern_gen(p,(s),(len))

#define intern_op(op) MRB_OPSYM_2(p->mrb, op)

static void
cons_free_gen(parser_state *p, node *cons)
{
  cons->cdr = p->cells;
  p->cells = cons;
}
#define cons_free(c) cons_free_gen(p, (c))

static void*
parser_palloc(parser_state *p, size_t size)
{
  void *m = mrb_pool_alloc(p->pool, size);

  if (!m) {
    MRB_THROW(p->mrb->jmp);
  }
  return m;
}

static node*
cons_gen(parser_state *p, node *car, node *cdr)
{
  node *c;

  if (p->cells) {
    c = p->cells;
    p->cells = p->cells->cdr;
  }
  else {
    c = (node *)parser_palloc(p, sizeof(mrb_ast_node));
  }

  c->car = car;
  c->cdr = cdr;
  c->lineno = p->lineno;
  c->filename_index = p->current_filename_index;
  /* beginning of next partial file; need to point the previous file */
  if (p->lineno == 0 && p->current_filename_index > 0) {
    c->filename_index-- ;
  }
  return c;
}
#define cons(a,b) cons_gen(p,(a),(b))

static node*
list1_gen(parser_state *p, node *a)
{
  return cons(a, 0);
}
#define list1(a) list1_gen(p, (a))

static node*
list2_gen(parser_state *p, node *a, node *b)
{
  return cons(a, cons(b,0));
}
#define list2(a,b) list2_gen(p, (a),(b))

static node*
list3_gen(parser_state *p, node *a, node *b, node *c)
{
  return cons(a, cons(b, cons(c,0)));
}
#define list3(a,b,c) list3_gen(p, (a),(b),(c))

static node*
list4_gen(parser_state *p, node *a, node *b, node *c, node *d)
{
  return cons(a, cons(b, cons(c, cons(d, 0))));
}
#define list4(a,b,c,d) list4_gen(p, (a),(b),(c),(d))

static node*
list5_gen(parser_state *p, node *a, node *b, node *c, node *d, node *e)
{
  return cons(a, cons(b, cons(c, cons(d, cons(e, 0)))));
}
#define list5(a,b,c,d,e) list5_gen(p, (a),(b),(c),(d),(e))

static node*
list6_gen(parser_state *p, node *a, node *b, node *c, node *d, node *e, node *f)
{
  return cons(a, cons(b, cons(c, cons(d, cons(e, cons(f, 0))))));
}
#define list6(a,b,c,d,e,f) list6_gen(p, (a),(b),(c),(d),(e),(f))

static node*
append_gen(parser_state *p, node *a, node *b)
{
  node *c = a;

  if (!a) return b;
  if (!b) return a;
  while (c->cdr) {
    c = c->cdr;
  }
  c->cdr = b;
  return a;
}
#define append(a,b) append_gen(p,(a),(b))
#define push(a,b) append_gen(p,(a),list1(b))

static char*
parser_strndup(parser_state *p, const char *s, size_t len)
{
  char *b = (char *)parser_palloc(p, len+1);

  memcpy(b, s, len);
  b[len] = '\0';
  return b;
}
#undef strndup
#define strndup(s,len) parser_strndup(p, s, len)

static char*
parser_strdup(parser_state *p, const char *s)
{
  return parser_strndup(p, s, strlen(s));
}
#undef strdup
#define strdup(s) parser_strdup(p, s)

static void
dump_int(uint16_t i, char *s)
{
  char *p = s;
  char *t = s;

  while (i > 0) {
    *p++ = (i % 10)+'0';
    i /= 10;
  }
  if (p == s) *p++ = '0';
  *p = 0;
  p--;  /* point the last char */
  while (t < p) {
    char c = *t;
    *t++ = *p;
    *p-- = c;
  }
}

/* xxx ----------------------------- */

static node*
local_switch(parser_state *p)
{
  node *prev = p->locals;

  p->locals = cons(0, 0);
  return prev;
}

static void
local_resume(parser_state *p, node *prev)
{
  p->locals = prev;
}

static void
local_nest(parser_state *p)
{
  p->locals = cons(0, p->locals);
}

static void
local_unnest(parser_state *p)
{
  if (p->locals) {
    p->locals = p->locals->cdr;
  }
}

static mrb_bool
local_var_p(parser_state *p, mrb_sym sym)
{
  const struct RProc *u;
  node *l = p->locals;

  while (l) {
    node *n = l->car;
    while (n) {
      if (sym(n->car) == sym) return TRUE;
      n = n->cdr;
    }
    l = l->cdr;
  }

  u = p->upper;
  while (u && !MRB_PROC_CFUNC_P(u)) {
    const struct mrb_irep *ir = MRB_PROC_IREP(u);
    const mrb_sym *v = ir->lv;
    int i;

    if (v) {
      for (i=0; i+1 < ir->nlocals; i++) {
        if (v[i] == sym) return TRUE;
      }
    }
    if (MRB_PROC_SCOPE_P(u)) break;
    u = u->upper;
  }
  return FALSE;
}

static void
local_add_f(parser_state *p, mrb_sym sym)
{
  if (p->locals) {
    node *n = p->locals->car;
    while (n) {
      if (sym(n->car) == sym) {
        mrb_int len;
        const char* name = mrb_sym_name_len(p->mrb, sym, &len);
        if (len > 0 && name[0] != '_') {
          yyerror(p, "duplicated argument name");
          return;
        }
      }
      n = n->cdr;
    }
    p->locals->car = push(p->locals->car, nsym(sym));
  }
}

static void
local_add(parser_state *p, mrb_sym sym)
{
  if (!local_var_p(p, sym)) {
    local_add_f(p, sym);
  }
}

static void
local_add_blk(parser_state *p, mrb_sym blk)
{
  /* allocate register for block */
  local_add_f(p, blk ? blk : intern_op(and));
}

static void
local_add_kw(parser_state *p, mrb_sym kwd)
{
  /* allocate register for keywords hash */
  local_add_f(p, kwd ? kwd : intern_op(pow));
}

static node*
locals_node(parser_state *p)
{
  return p->locals ? p->locals->car : NULL;
}

static void
nvars_nest(parser_state *p)
{
  p->nvars = cons(nint(0), p->nvars);
}

static void
nvars_block(parser_state *p)
{
  p->nvars = cons(nint(-2), p->nvars);
}

static void
nvars_unnest(parser_state *p)
{
  p->nvars = p->nvars->cdr;
}

/* (:scope (vars..) (prog...)) */
static node*
new_scope(parser_state *p, node *body)
{
  return cons((node*)NODE_SCOPE, cons(locals_node(p), body));
}

/* (:begin prog...) */
static node*
new_begin(parser_state *p, node *body)
{
  if (body) {
    return list2((node*)NODE_BEGIN, body);
  }
  return cons((node*)NODE_BEGIN, 0);
}

#define newline_node(n) (n)

/* (:rescue body rescue else) */
static node*
new_rescue(parser_state *p, node *body, node *resq, node *els)
{
  return list4((node*)NODE_RESCUE, body, resq, els);
}

static node*
new_mod_rescue(parser_state *p, node *body, node *resq)
{
  return new_rescue(p, body, list1(list3(0, 0, resq)), 0);
}

/* (:ensure body ensure) */
static node*
new_ensure(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_ENSURE, cons(a, cons(0, b)));
}

/* (:nil) */
static node*
new_nil(parser_state *p)
{
  return list1((node*)NODE_NIL);
}

/* (:true) */
static node*
new_true(parser_state *p)
{
  return list1((node*)NODE_TRUE);
}

/* (:false) */
static node*
new_false(parser_state *p)
{
  return list1((node*)NODE_FALSE);
}

/* (:alias new old) */
static node*
new_alias(parser_state *p, mrb_sym a, mrb_sym b)
{
  return cons((node*)NODE_ALIAS, cons(nsym(a), nsym(b)));
}

/* (:if cond then else) */
static node*
new_if(parser_state *p, node *a, node *b, node *c)
{
  void_expr_error(p, a);
  return list4((node*)NODE_IF, a, b, c);
}

/* (:unless cond then else) */
static node*
new_unless(parser_state *p, node *a, node *b, node *c)
{
  void_expr_error(p, a);
  return list4((node*)NODE_IF, a, c, b);
}

/* (:while cond body) */
static node*
new_while(parser_state *p, node *a, node *b)
{
  void_expr_error(p, a);
  return cons((node*)NODE_WHILE, cons(a, b));
}

/* (:until cond body) */
static node*
new_until(parser_state *p, node *a, node *b)
{
  void_expr_error(p, a);
  return cons((node*)NODE_UNTIL, cons(a, b));
}

/* (:for var obj body) */
static node*
new_for(parser_state *p, node *v, node *o, node *b)
{
  void_expr_error(p, o);
  return list4((node*)NODE_FOR, v, o, b);
}

/* (:case a ((when ...) body) ((when...) body)) */
static node*
new_case(parser_state *p, node *a, node *b)
{
  node *n = list2((node*)NODE_CASE, a);
  node *n2 = n;

  void_expr_error(p, a);
  while (n2->cdr) {
    n2 = n2->cdr;
  }
  n2->cdr = b;
  return n;
}

/* (:postexe a) */
static node*
new_postexe(parser_state *p, node *a)
{
  return cons((node*)NODE_POSTEXE, a);
}

/* (:self) */
static node*
new_self(parser_state *p)
{
  return list1((node*)NODE_SELF);
}

/* (:call a b c) */
static node*
new_call(parser_state *p, node *a, mrb_sym b, node *c, int pass)
{
  node *n = list4(nint(pass?NODE_CALL:NODE_SCALL), a, nsym(b), c);
  void_expr_error(p, a);
  NODE_LINENO(n, a);
  return n;
}

/* (:fcall self mid args) */
static node*
new_fcall(parser_state *p, mrb_sym b, node *c)
{
  node *n = list4((node*)NODE_FCALL, 0, nsym(b), c);
  NODE_LINENO(n, c);
  return n;
}

/* (a b . c) */
static node*
new_callargs(parser_state *p, node *a, node *b, node *c)
{
  return cons(a, cons(b, c));
}

/* (:super . c) */
static node*
new_super(parser_state *p, node *c)
{
  return cons((node*)NODE_SUPER, c);
}

/* (:zsuper) */
static node*
new_zsuper(parser_state *p)
{
  return cons((node*)NODE_ZSUPER, 0);
}

/* (:yield . c) */
static node*
new_yield(parser_state *p, node *c)
{
  if (c) {
    if (c->cdr) {
      if (c->cdr->cdr) {
        yyerror(p, "both block arg and actual block given");
      }
      if (c->cdr->car) {
        return cons((node*)NODE_YIELD, push(c->car, c->cdr->car));
      }
    }
    return cons((node*)NODE_YIELD, c->car);
  }
  return cons((node*)NODE_YIELD, 0);
}

/* (:return . c) */
static node*
new_return(parser_state *p, node *c)
{
  return cons((node*)NODE_RETURN, c);
}

/* (:break . c) */
static node*
new_break(parser_state *p, node *c)
{
  return cons((node*)NODE_BREAK, c);
}

/* (:next . c) */
static node*
new_next(parser_state *p, node *c)
{
  return cons((node*)NODE_NEXT, c);
}

/* (:redo) */
static node*
new_redo(parser_state *p)
{
  return list1((node*)NODE_REDO);
}

/* (:retry) */
static node*
new_retry(parser_state *p)
{
  return list1((node*)NODE_RETRY);
}

/* (:dot2 a b) */
static node*
new_dot2(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_DOT2, cons(a, b));
}

/* (:dot3 a b) */
static node*
new_dot3(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_DOT3, cons(a, b));
}

/* (:colon2 b c) */
static node*
new_colon2(parser_state *p, node *b, mrb_sym c)
{
  void_expr_error(p, b);
  return cons((node*)NODE_COLON2, cons(b, nsym(c)));
}

/* (:colon3 . c) */
static node*
new_colon3(parser_state *p, mrb_sym c)
{
  return cons((node*)NODE_COLON3, nsym(c));
}

/* (:and a b) */
static node*
new_and(parser_state *p, node *a, node *b)
{
  void_expr_error(p, a);
  return cons((node*)NODE_AND, cons(a, b));
}

/* (:or a b) */
static node*
new_or(parser_state *p, node *a, node *b)
{
  void_expr_error(p, a);
  return cons((node*)NODE_OR, cons(a, b));
}

/* (:array a...) */
static node*
new_array(parser_state *p, node *a)
{
  return cons((node*)NODE_ARRAY, a);
}

/* (:splat . a) */
static node*
new_splat(parser_state *p, node *a)
{
  void_expr_error(p, a);
  return cons((node*)NODE_SPLAT, a);
}

/* (:hash (k . v) (k . v)...) */
static node*
new_hash(parser_state *p, node *a)
{
  return cons((node*)NODE_HASH, a);
}

/* (:kw_hash (k . v) (k . v)...) */
static node*
new_kw_hash(parser_state *p, node *a)
{
  return cons((node*)NODE_KW_HASH, a);
}

/* (:sym . a) */
static node*
new_sym(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_SYM, nsym(sym));
}

static mrb_sym
new_strsym(parser_state *p, node* str)
{
  const char *s = (const char*)str->cdr->car;
  size_t len = (size_t)str->cdr->cdr;

  return mrb_intern(p->mrb, s, len);
}

/* (:lvar . a) */
static node*
new_lvar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_LVAR, nsym(sym));
}

/* (:gvar . a) */
static node*
new_gvar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_GVAR, nsym(sym));
}

/* (:ivar . a) */
static node*
new_ivar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_IVAR, nsym(sym));
}

/* (:cvar . a) */
static node*
new_cvar(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_CVAR, nsym(sym));
}

/* (:nvar . a) */
static node*
new_nvar(parser_state *p, int num)
{
  int nvars = intn(p->nvars->car);

  p->nvars->car = nint(nvars > num ? nvars : num);
  return cons((node*)NODE_NVAR, nint(num));
}

/* (:const . a) */
static node*
new_const(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_CONST, nsym(sym));
}

/* (:undef a...) */
static node*
new_undef(parser_state *p, mrb_sym sym)
{
  return list2((node*)NODE_UNDEF, nsym(sym));
}

/* (:class class super body) */
static node*
new_class(parser_state *p, node *c, node *s, node *b)
{
  void_expr_error(p, s);
  return list4((node*)NODE_CLASS, c, s, cons(locals_node(p), b));
}

/* (:sclass obj body) */
static node*
new_sclass(parser_state *p, node *o, node *b)
{
  void_expr_error(p, o);
  return list3((node*)NODE_SCLASS, o, cons(locals_node(p), b));
}

/* (:module module body) */
static node*
new_module(parser_state *p, node *m, node *b)
{
  return list3((node*)NODE_MODULE, m, cons(locals_node(p), b));
}

/* (:def m lv (arg . body)) */
static node*
new_def(parser_state *p, mrb_sym m, node *a, node *b)
{
  return list5((node*)NODE_DEF, nsym(m), 0, a, b);
}

static void
defn_setup(parser_state *p, node *d, node *a, node *b)
{
  node *n = d->cdr->cdr;

  n->car = locals_node(p);
  p->cmdarg_stack = intn(n->cdr->car);
  n->cdr->car = a;
  local_resume(p, n->cdr->cdr->car);
  n->cdr->cdr->car = b;
}

/* (:sdef obj m lv (arg . body)) */
static node*
new_sdef(parser_state *p, node *o, mrb_sym m, node *a, node *b)
{
  void_expr_error(p, o);
  return list6((node*)NODE_SDEF, o, nsym(m), 0, a, b);
}

static void
defs_setup(parser_state *p, node *d, node *a, node *b)
{
  node *n = d->cdr->cdr->cdr;

  n->car = locals_node(p);
  p->cmdarg_stack = intn(n->cdr->car);
  n->cdr->car = a;
  local_resume(p, n->cdr->cdr->car);
  n->cdr->cdr->car = b;
}

/* (:arg . sym) */
static node*
new_arg(parser_state *p, mrb_sym sym)
{
  return cons((node*)NODE_ARG, nsym(sym));
}

static void
local_add_margs(parser_state *p, node *n)
{
  while (n) {
    if (typen(n->car->car) == NODE_MASGN) {
      node *t = n->car->cdr->cdr;

      n->car->cdr->cdr = NULL;
      while (t) {
        local_add_f(p, sym(t->car));
        t = t->cdr;
      }
      local_add_margs(p, n->car->cdr->car->car);
      local_add_margs(p, n->car->cdr->car->cdr->cdr->car);
    }
    n = n->cdr;
  }
}

static void
local_add_lv(parser_state *p, node *lv)
{
  while (lv) {
    local_add_f(p, sym(lv->car));
    lv = lv->cdr;
  }
}

/* (m o r m2 tail) */
/* m: (a b c) */
/* o: ((a . e1) (b . e2)) */
/* r: a */
/* m2: (a b c) */
/* b: a */
static node*
new_args(parser_state *p, node *m, node *opt, mrb_sym rest, node *m2, node *tail)
{
  node *n;

  local_add_margs(p, m);
  local_add_margs(p, m2);
  n = cons(m2, tail);
  n = cons(nsym(rest), n);
  n = cons(opt, n);
  while (opt) {
    /* opt: (sym . (opt . lv)) -> (sym . opt) */
    local_add_lv(p, opt->car->cdr->cdr);
    opt->car->cdr = opt->car->cdr->car;
    opt = opt->cdr;
  }
  return cons(m, n);
}

/* (:args_tail keywords rest_keywords_sym block_sym) */
static node*
new_args_tail(parser_state *p, node *kws, node *kwrest, mrb_sym blk)
{
  node *k;

  if (kws || kwrest) {
    local_add_kw(p, (kwrest && kwrest->cdr)? sym(kwrest->cdr) : 0);
  }

  local_add_blk(p, blk);

  /* allocate register for keywords arguments */
  /* order is for Proc#parameters */
  for (k = kws; k; k = k->cdr) {
    if (!k->car->cdr->cdr->car) { /* allocate required keywords */
      local_add_f(p, sym(k->car->cdr->car));
    }
  }
  for (k = kws; k; k = k->cdr) {
    if (k->car->cdr->cdr->car) { /* allocate keywords with default */
      local_add_lv(p, k->car->cdr->cdr->car->cdr);
      k->car->cdr->cdr->car = k->car->cdr->cdr->car->car;
      local_add_f(p, sym(k->car->cdr->car));
    }
  }

  return list4((node*)NODE_ARGS_TAIL, kws, kwrest, nsym(blk));
}

/* (:kw_arg kw_sym def_arg) */
static node*
new_kw_arg(parser_state *p, mrb_sym kw, node *def_arg)
{
  mrb_assert(kw);
  return list3((node*)NODE_KW_ARG, nsym(kw), def_arg);
}

/* (:kw_rest_args . a) */
static node*
new_kw_rest_args(parser_state *p, node *a)
{
  return cons((node*)NODE_KW_REST_ARGS, a);
}

static node*
new_args_dots(parser_state *p, node *m)
{
  mrb_sym r = intern_op(mul);
  mrb_sym k = intern_op(pow);
  mrb_sym b = intern_op(and);
  local_add_f(p, r);
  return new_args(p, m, 0, r, 0,
                  new_args_tail(p, 0, new_kw_rest_args(p, nsym(k)), b));
}

/* (:block_arg . a) */
static node*
new_block_arg(parser_state *p, node *a)
{
  return cons((node*)NODE_BLOCK_ARG, a);
}

static node*
setup_numparams(parser_state *p, node *a)
{
  int nvars = intn(p->nvars->car);
  if (nvars > 0) {
    int i;
    mrb_sym sym;
    // m || opt || rest || tail
    if (a && (a->car || (a->cdr && a->cdr->car) || (a->cdr->cdr && a->cdr->cdr->car) || (a->cdr->cdr->cdr->cdr && a->cdr->cdr->cdr->cdr->car))) {
      yyerror(p, "ordinary parameter is defined");
    }
    else if (p->locals) {
      /* p->locals should not be NULL unless error happens before the point */
      node* args = 0;
      for (i = nvars; i > 0; i--) {
        char buf[3];

        buf[0] = '_';
        buf[1] = i+'0';
        buf[2] = '\0';
        sym = intern_cstr(buf);
        args = cons(new_arg(p, sym), args);
        p->locals->car = cons(nsym(sym), p->locals->car);
      }
      a = new_args(p, args, 0, 0, 0, 0);
    }
  }
  return a;
}

/* (:block arg body) */
static node*
new_block(parser_state *p, node *a, node *b)
{
  a = setup_numparams(p, a);
  return list4((node*)NODE_BLOCK, locals_node(p), a, b);
}

/* (:lambda arg body) */
static node*
new_lambda(parser_state *p, node *a, node *b)
{
  return list4((node*)NODE_LAMBDA, locals_node(p), a, b);
}

/* (:asgn lhs rhs) */
static node*
new_asgn(parser_state *p, node *a, node *b)
{
  void_expr_error(p, b);
  return cons((node*)NODE_ASGN, cons(a, b));
}

/* (:masgn mlhs=(pre rest post)  mrhs) */
static node*
new_masgn(parser_state *p, node *a, node *b)
{
  void_expr_error(p, b);
  return cons((node*)NODE_MASGN, cons(a, b));
}

/* (:masgn mlhs mrhs) no check */
static node*
new_masgn_param(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_MASGN, cons(a, b));
}

/* (:asgn lhs rhs) */
static node*
new_op_asgn(parser_state *p, node *a, mrb_sym op, node *b)
{
  void_expr_error(p, b);
  return list4((node*)NODE_OP_ASGN, a, nsym(op), b);
}

static node*
new_imaginary(parser_state *p, node *imaginary)
{
  return new_call(p, new_const(p, MRB_SYM_2(p->mrb, Kernel)), MRB_SYM_2(p->mrb, Complex),
                  new_callargs(p, list2(list3((node*)NODE_INT, (node*)strdup("0"), nint(10)), imaginary), 0, 0), 1);
}

static node*
new_rational(parser_state *p, node *rational)
{
  return new_call(p, new_const(p, MRB_SYM_2(p->mrb, Kernel)), MRB_SYM_2(p->mrb, Rational), new_callargs(p, list1(rational), 0, 0), 1);
}

/* (:int . i) */
static node*
new_int(parser_state *p, const char *s, int base, int suffix)
{
  node* result = list3((node*)NODE_INT, (node*)strdup(s), nint(base));
  if (suffix & NUM_SUFFIX_R) {
    result = new_rational(p, result);
  }
  if (suffix & NUM_SUFFIX_I) {
    result = new_imaginary(p, result);
  }
  return result;
}

#ifndef MRB_NO_FLOAT
/* (:float . i) */
static node*
new_float(parser_state *p, const char *s, int suffix)
{
  node* result = cons((node*)NODE_FLOAT, (node*)strdup(s));
  if (suffix & NUM_SUFFIX_R) {
    result = new_rational(p, result);
  }
  if (suffix & NUM_SUFFIX_I) {
    result = new_imaginary(p, result);
  }
  return result;
}
#endif

/* (:str . (s . len)) */
static node*
new_str(parser_state *p, const char *s, size_t len)
{
  return cons((node*)NODE_STR, cons((node*)strndup(s, len), nint(len)));
}

/* (:dstr . a) */
static node*
new_dstr(parser_state *p, node *a)
{
  return cons((node*)NODE_DSTR, a);
}

static int
string_node_p(node *n)
{
  return (int)(typen(n->car) == NODE_STR);
}

static node*
composite_string_node(parser_state *p, node *a, node *b)
{
  size_t newlen = (size_t)a->cdr + (size_t)b->cdr;
  char *str = (char*)mrb_pool_realloc(p->pool, a->car, (size_t)a->cdr + 1, newlen + 1);
  memcpy(str + (size_t)a->cdr, b->car, (size_t)b->cdr);
  str[newlen] = '\0';
  a->car = (node*)str;
  a->cdr = (node*)newlen;
  cons_free(b);
  return a;
}

static node*
concat_string(parser_state *p, node *a, node *b)
{
  if (string_node_p(a)) {
    if (string_node_p(b)) {
      /* a == NODE_STR && b == NODE_STR */
      composite_string_node(p, a->cdr, b->cdr);
      cons_free(b);
      return a;
    }
    else {
      /* a == NODE_STR && b == NODE_DSTR */

      if (string_node_p(b->cdr->car)) {
        /* a == NODE_STR && b->[NODE_STR, ...] */
        composite_string_node(p, a->cdr, b->cdr->car->cdr);
        cons_free(b->cdr->car);
        b->cdr->car = a;
        return b;
      }
    }
  }
  else {
    node *c; /* last node of a */
    for (c = a; c->cdr != NULL; c = c->cdr) ;

    if (string_node_p(b)) {
      /* a == NODE_DSTR && b == NODE_STR */
      if (string_node_p(c->car)) {
        /* a->[..., NODE_STR] && b == NODE_STR */
        composite_string_node(p, c->car->cdr, b->cdr);
        cons_free(b);
        return a;
      }

      push(a, b);
      return a;
    }
    else {
      /* a == NODE_DSTR && b == NODE_DSTR */
      if (string_node_p(c->car) && string_node_p(b->cdr->car)) {
        /* a->[..., NODE_STR] && b->[NODE_STR, ...] */
        node *d = b->cdr;
        cons_free(b);
        composite_string_node(p, c->car->cdr, d->car->cdr);
        cons_free(d->car);
        c->cdr = d->cdr;
        cons_free(d);
        return a;
      }
      else {
        c->cdr = b->cdr;
        cons_free(b);
        return a;
      }
    }
  }

  return new_dstr(p, list2(a, b));
}

/* (:str . (s . len)) */
static node*
new_xstr(parser_state *p, const char *s, int len)
{
  return cons((node*)NODE_XSTR, cons((node*)strndup(s, len), nint(len)));
}

/* (:xstr . a) */
static node*
new_dxstr(parser_state *p, node *a)
{
  return cons((node*)NODE_DXSTR, a);
}

/* (:dsym . a) */
static node*
new_dsym(parser_state *p, node *a)
{
  return cons((node*)NODE_DSYM, a);
}

/* (:regx . (s . (opt . enc))) */
static node*
new_regx(parser_state *p, const char *p1, const char* p2, const char* p3)
{
  return cons((node*)NODE_REGX, cons((node*)p1, cons((node*)p2, (node*)p3)));
}

/* (:dregx . (a . b)) */
static node*
new_dregx(parser_state *p, node *a, node *b)
{
  return cons((node*)NODE_DREGX, cons(a, b));
}

/* (:backref . n) */
static node*
new_back_ref(parser_state *p, int n)
{
  return cons((node*)NODE_BACK_REF, nint(n));
}

/* (:nthref . n) */
static node*
new_nth_ref(parser_state *p, int n)
{
  return cons((node*)NODE_NTH_REF, nint(n));
}

/* (:heredoc . a) */
static node*
new_heredoc(parser_state *p)
{
  parser_heredoc_info *inf = (parser_heredoc_info *)parser_palloc(p, sizeof(parser_heredoc_info));
  return cons((node*)NODE_HEREDOC, (node*)inf);
}

static void
new_bv(parser_state *p, mrb_sym id)
{
}

static node*
new_literal_delim(parser_state *p)
{
  return cons((node*)NODE_LITERAL_DELIM, 0);
}

/* (:words . a) */
static node*
new_words(parser_state *p, node *a)
{
  return cons((node*)NODE_WORDS, a);
}

/* (:symbols . a) */
static node*
new_symbols(parser_state *p, node *a)
{
  return cons((node*)NODE_SYMBOLS, a);
}

/* xxx ----------------------------- */

/* (:call a op) */
static node*
call_uni_op(parser_state *p, node *recv, const char *m)
{
  void_expr_error(p, recv);
  return new_call(p, recv, intern_cstr(m), 0, 1);
}

/* (:call a op b) */
static node*
call_bin_op(parser_state *p, node *recv, const char *m, node *arg1)
{
  return new_call(p, recv, intern_cstr(m), new_callargs(p, list1(arg1), 0, 0), 1);
}

static void
args_with_block(parser_state *p, node *a, node *b)
{
  if (b) {
    if (a->cdr && a->cdr->cdr) {
      yyerror(p, "both block arg and actual block given");
    }
    a->cdr->cdr = b;
  }
}

static void
endless_method_name(parser_state *p, node *defn)
{
  mrb_sym sym = sym(defn->cdr->car);
  mrb_int len;
  const char *name = mrb_sym_name_len(p->mrb, sym, &len);

  if (len > 1 && name[len-1] == '=') {
    for (int i=0; i<len-1; i++) {
      if (!identchar(name[i])) return;
    }
    yyerror(p, "setter method cannot be defined by endless method definition");
  }
}

static void
call_with_block(parser_state *p, node *a, node *b)
{
  node *n;

  switch (typen(a->car)) {
  case NODE_SUPER:
  case NODE_ZSUPER:
    if (!a->cdr) a->cdr = new_callargs(p, 0, 0, b);
    else args_with_block(p, a->cdr, b);
    break;
  case NODE_CALL:
  case NODE_FCALL:
  case NODE_SCALL:
    /* (NODE_CALL recv mid (args kw . blk)) */
    n = a->cdr->cdr->cdr; /* (args kw . blk) */
    if (!n->car) n->car = new_callargs(p, 0, 0, b);
    else args_with_block(p, n->car, b);
    break;
  default:
    break;
  }
}

static node*
new_negate(parser_state *p, node *n)
{
  return cons((node*)NODE_NEGATE, n);
}

static node*
cond(node *n)
{
  return n;
}

static node*
ret_args(parser_state *p, node *n)
{
  if (n->cdr->cdr) {
    yyerror(p, "block argument should not be given");
    return NULL;
  }
  if (!n->car) return NULL;
  if (!n->car->cdr) return n->car->car;
  return new_array(p, n->car);
}

static void
assignable(parser_state *p, node *lhs)
{
  if (intn(lhs->car) == NODE_LVAR) {
    local_add(p, sym(lhs->cdr));
  }
}

static node*
var_reference(parser_state *p, node *lhs)
{
  node *n;

  if (intn(lhs->car) == NODE_LVAR) {
    if (!local_var_p(p, sym(lhs->cdr))) {
      n = new_fcall(p, sym(lhs->cdr), 0);
      cons_free(lhs);
      return n;
    }
  }

  return lhs;
}

static node*
label_reference(parser_state *p, mrb_sym sym)
{
  const char *name = mrb_sym_name(p->mrb, sym);
  node *n;

  if (local_var_p(p, sym)) {
    n = new_lvar(p, sym);
  }
  else if (ISUPPER(name[0])) {
    n = new_const(p, sym);
  }
  else {
    n = new_fcall(p, sym, 0);
  }
  return n;
}

typedef enum mrb_string_type  string_type;

static node*
new_strterm(parser_state *p, string_type type, int term, int paren)
{
  return cons(nint(type), cons(nint(0), cons(nint(paren), nint(term))));
}

static void
end_strterm(parser_state *p)
{
  cons_free(p->lex_strterm->cdr->cdr);
  cons_free(p->lex_strterm->cdr);
  cons_free(p->lex_strterm);
  p->lex_strterm = NULL;
}

static parser_heredoc_info *
parsing_heredoc_inf(parser_state *p)
{
  node *nd = p->parsing_heredoc;
  if (nd == NULL)
    return NULL;
  /* mrb_assert(nd->car->car == NODE_HEREDOC); */
  return (parser_heredoc_info*)nd->car->cdr;
}

static void
heredoc_treat_nextline(parser_state *p)
{
  if (p->heredocs_from_nextline == NULL)
    return;
  if (p->parsing_heredoc == NULL) {
    node *n;
    p->parsing_heredoc = p->heredocs_from_nextline;
    p->lex_strterm_before_heredoc = p->lex_strterm;
    p->lex_strterm = new_strterm(p, parsing_heredoc_inf(p)->type, 0, 0);
    n = p->all_heredocs;
    if (n) {
      while (n->cdr)
        n = n->cdr;
      n->cdr = p->parsing_heredoc;
    }
    else {
      p->all_heredocs = p->parsing_heredoc;
    }
  }
  else {
    node *n, *m;
    m = p->heredocs_from_nextline;
    while (m->cdr)
      m = m->cdr;
    n = p->all_heredocs;
    mrb_assert(n != NULL);
    if (n == p->parsing_heredoc) {
      m->cdr = n;
      p->all_heredocs = p->heredocs_from_nextline;
      p->parsing_heredoc = p->heredocs_from_nextline;
    }
    else {
      while (n->cdr != p->parsing_heredoc) {
        n = n->cdr;
        mrb_assert(n != NULL);
      }
      m->cdr = n->cdr;
      n->cdr = p->heredocs_from_nextline;
      p->parsing_heredoc = p->heredocs_from_nextline;
    }
  }
  p->heredocs_from_nextline = NULL;
}

static void
heredoc_end(parser_state *p)
{
  p->parsing_heredoc = p->parsing_heredoc->cdr;
  if (p->parsing_heredoc == NULL) {
    p->lstate = EXPR_BEG;
    end_strterm(p);
    p->lex_strterm = p->lex_strterm_before_heredoc;
    p->lex_strterm_before_heredoc = NULL;
  }
  else {
    /* next heredoc */
    p->lex_strterm->car = nint(parsing_heredoc_inf(p)->type);
  }
}
#define is_strterm_type(p,str_func) (intn((p)->lex_strterm->car) & (str_func))

/* xxx ----------------------------- */


#line 1504 "mrbgems/mruby-compiler/core/y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    keyword_class = 258,
    keyword_module = 259,
    keyword_def = 260,
    keyword_begin = 261,
    keyword_if = 262,
    keyword_unless = 263,
    keyword_while = 264,
    keyword_until = 265,
    keyword_for = 266,
    keyword_undef = 267,
    keyword_rescue = 268,
    keyword_ensure = 269,
    keyword_end = 270,
    keyword_then = 271,
    keyword_elsif = 272,
    keyword_else = 273,
    keyword_case = 274,
    keyword_when = 275,
    keyword_break = 276,
    keyword_next = 277,
    keyword_redo = 278,
    keyword_retry = 279,
    keyword_in = 280,
    keyword_do = 281,
    keyword_do_cond = 282,
    keyword_do_block = 283,
    keyword_do_LAMBDA = 284,
    keyword_return = 285,
    keyword_yield = 286,
    keyword_super = 287,
    keyword_self = 288,
    keyword_nil = 289,
    keyword_true = 290,
    keyword_false = 291,
    keyword_and = 292,
    keyword_or = 293,
    keyword_not = 294,
    modifier_if = 295,
    modifier_unless = 296,
    modifier_while = 297,
    modifier_until = 298,
    modifier_rescue = 299,
    keyword_alias = 300,
    keyword_BEGIN = 301,
    keyword_END = 302,
    keyword__LINE__ = 303,
    keyword__FILE__ = 304,
    keyword__ENCODING__ = 305,
    tIDENTIFIER = 306,
    tFID = 307,
    tGVAR = 308,
    tIVAR = 309,
    tCONSTANT = 310,
    tCVAR = 311,
    tLABEL_TAG = 312,
    tINTEGER = 313,
    tFLOAT = 314,
    tCHAR = 315,
    tXSTRING = 316,
    tREGEXP = 317,
    tSTRING = 318,
    tSTRING_PART = 319,
    tSTRING_MID = 320,
    tNTH_REF = 321,
    tBACK_REF = 322,
    tREGEXP_END = 323,
    tNUMPARAM = 324,
    tUPLUS = 325,
    tUMINUS = 326,
    tCMP = 327,
    tEQ = 328,
    tEQQ = 329,
    tNEQ = 330,
    tGEQ = 331,
    tLEQ = 332,
    tANDOP = 333,
    tOROP = 334,
    tMATCH = 335,
    tNMATCH = 336,
    tDOT2 = 337,
    tDOT3 = 338,
    tBDOT2 = 339,
    tBDOT3 = 340,
    tAREF = 341,
    tASET = 342,
    tLSHFT = 343,
    tRSHFT = 344,
    tCOLON2 = 345,
    tCOLON3 = 346,
    tOP_ASGN = 347,
    tASSOC = 348,
    tLPAREN = 349,
    tLPAREN_ARG = 350,
    tRPAREN = 351,
    tLBRACK = 352,
    tLBRACE = 353,
    tLBRACE_ARG = 354,
    tSTAR = 355,
    tPOW = 356,
    tDSTAR = 357,
    tAMPER = 358,
    tLAMBDA = 359,
    tANDDOT = 360,
    tSYMBEG = 361,
    tSTRING_BEG = 362,
    tXSTRING_BEG = 363,
    tSTRING_DVAR = 364,
    tREGEXP_BEG = 365,
    tWORDS_BEG = 366,
    tSYMBOLS_BEG = 367,
    tLAMBEG = 368,
    tHEREDOC_BEG = 369,
    tHEREDOC_END = 370,
    tLITERAL_DELIM = 371,
    tHD_LITERAL_DELIM = 372,
    tHD_STRING_PART = 373,
    tHD_STRING_MID = 374,
    tLOWEST = 375,
    tUMINUS_NUM = 376,
    tLAST_TOKEN = 377
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 1446 "mrbgems/mruby-compiler/core/parse.y"

    node *nd;
    mrb_sym id;
    int num;
    stack_type stack;
    const struct vtable *vars;

#line 1684 "mrbgems/mruby-compiler/core/y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (parser_state *p);





#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   13387

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  149
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  175
/* YYNRULES -- Number of rules.  */
#define YYNRULES  612
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1077

#define YYUNDEFTOK  2
#define YYMAXUTOK   377


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     148,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   135,     2,     2,     2,   133,   128,     2,
     144,   145,   131,   129,   142,   130,   147,   132,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   123,   146,
     125,   121,   124,   122,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   140,     2,   141,   127,     2,   143,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   138,   126,   139,   136,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   134,   137
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,  1617,  1617,  1617,  1628,  1634,  1638,  1643,  1647,  1653,
    1655,  1654,  1668,  1695,  1701,  1705,  1710,  1714,  1720,  1720,
    1724,  1728,  1732,  1736,  1740,  1744,  1748,  1753,  1754,  1758,
    1762,  1766,  1770,  1776,  1779,  1783,  1787,  1791,  1795,  1799,
    1804,  1808,  1817,  1826,  1835,  1844,  1851,  1852,  1856,  1860,
    1861,  1865,  1869,  1873,  1877,  1881,  1891,  1890,  1905,  1914,
    1915,  1918,  1919,  1926,  1925,  1940,  1944,  1949,  1953,  1958,
    1962,  1967,  1971,  1975,  1979,  1983,  1989,  1993,  1999,  2000,
    2006,  2010,  2014,  2018,  2022,  2026,  2030,  2034,  2038,  2042,
    2048,  2049,  2055,  2059,  2065,  2069,  2075,  2079,  2083,  2087,
    2091,  2095,  2101,  2107,  2114,  2118,  2122,  2126,  2130,  2134,
    2140,  2146,  2151,  2157,  2161,  2164,  2168,  2172,  2179,  2180,
    2181,  2182,  2187,  2194,  2195,  2198,  2202,  2202,  2208,  2209,
    2210,  2211,  2212,  2213,  2214,  2215,  2216,  2217,  2218,  2219,
    2220,  2221,  2222,  2223,  2224,  2225,  2226,  2227,  2228,  2229,
    2230,  2231,  2232,  2233,  2234,  2235,  2236,  2237,  2240,  2240,
    2240,  2241,  2241,  2242,  2242,  2242,  2243,  2243,  2243,  2243,
    2244,  2244,  2244,  2245,  2245,  2245,  2246,  2246,  2246,  2246,
    2247,  2247,  2247,  2247,  2248,  2248,  2248,  2248,  2249,  2249,
    2249,  2249,  2250,  2250,  2250,  2250,  2251,  2251,  2254,  2258,
    2262,  2266,  2270,  2274,  2278,  2283,  2288,  2293,  2297,  2301,
    2305,  2309,  2313,  2317,  2321,  2325,  2329,  2333,  2337,  2341,
    2345,  2349,  2353,  2357,  2361,  2365,  2369,  2373,  2377,  2381,
    2385,  2389,  2393,  2397,  2401,  2405,  2409,  2413,  2417,  2421,
    2425,  2429,  2433,  2437,  2441,  2450,  2459,  2468,  2477,  2483,
    2484,  2489,  2493,  2500,  2504,  2511,  2515,  2524,  2541,  2542,
    2545,  2546,  2547,  2552,  2557,  2564,  2570,  2575,  2580,  2585,
    2592,  2592,  2603,  2607,  2613,  2617,  2623,  2626,  2632,  2637,
    2642,  2648,  2653,  2657,  2663,  2664,  2665,  2666,  2667,  2668,
    2669,  2670,  2674,  2679,  2678,  2690,  2694,  2689,  2699,  2699,
    2703,  2707,  2711,  2715,  2720,  2725,  2729,  2733,  2737,  2741,
    2745,  2746,  2752,  2758,  2751,  2770,  2778,  2786,  2786,  2786,
    2793,  2793,  2793,  2800,  2806,  2811,  2813,  2810,  2822,  2820,
    2838,  2843,  2836,  2860,  2858,  2874,  2884,  2895,  2899,  2903,
    2907,  2913,  2920,  2921,  2922,  2925,  2926,  2929,  2930,  2938,
    2939,  2945,  2949,  2952,  2956,  2960,  2964,  2968,  2972,  2976,
    2980,  2984,  2990,  2994,  2998,  3002,  3008,  3013,  3018,  3022,
    3026,  3030,  3034,  3038,  3042,  3046,  3050,  3054,  3058,  3062,
    3066,  3070,  3074,  3080,  3085,  3092,  3092,  3096,  3101,  3108,
    3112,  3118,  3119,  3122,  3127,  3130,  3134,  3140,  3144,  3151,
    3150,  3165,  3175,  3179,  3184,  3191,  3195,  3199,  3203,  3207,
    3211,  3215,  3219,  3223,  3230,  3229,  3244,  3243,  3259,  3267,
    3276,  3279,  3286,  3289,  3293,  3294,  3297,  3301,  3304,  3308,
    3311,  3312,  3313,  3314,  3317,  3318,  3324,  3325,  3326,  3330,
    3343,  3344,  3350,  3355,  3354,  3365,  3369,  3375,  3379,  3392,
    3396,  3402,  3405,  3406,  3409,  3415,  3421,  3422,  3425,  3432,
    3431,  3445,  3449,  3463,  3468,  3482,  3488,  3489,  3490,  3491,
    3492,  3496,  3502,  3506,  3516,  3517,  3518,  3522,  3528,  3532,
    3536,  3540,  3544,  3550,  3554,  3560,  3564,  3568,  3572,  3576,
    3580,  3588,  3595,  3601,  3602,  3606,  3610,  3609,  3626,  3627,
    3630,  3636,  3640,  3646,  3647,  3651,  3655,  3661,  3667,  3673,
    3680,  3686,  3693,  3697,  3703,  3707,  3713,  3714,  3717,  3721,
    3727,  3731,  3735,  3739,  3745,  3750,  3755,  3759,  3763,  3767,
    3771,  3775,  3779,  3783,  3787,  3791,  3795,  3799,  3803,  3807,
    3812,  3818,  3823,  3828,  3833,  3838,  3845,  3849,  3856,  3861,
    3860,  3871,  3875,  3881,  3889,  3897,  3905,  3909,  3915,  3919,
    3925,  3926,  3929,  3934,  3941,  3942,  3945,  3949,  3955,  3959,
    3965,  3970,  3970,  3995,  3996,  4002,  4007,  4013,  4019,  4024,
    4028,  4038,  4045,  4046,  4047,  4050,  4051,  4052,  4053,  4056,
    4057,  4058,  4061,  4062,  4065,  4069,  4075,  4076,  4082,  4083,
    4086,  4087,  4090,  4093,  4094,  4095,  4098,  4099,  4102,  4107,
    4110,  4111,  4115
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "keyword_class", "keyword_module",
  "keyword_def", "keyword_begin", "keyword_if", "keyword_unless",
  "keyword_while", "keyword_until", "keyword_for", "keyword_undef",
  "keyword_rescue", "keyword_ensure", "keyword_end", "keyword_then",
  "keyword_elsif", "keyword_else", "keyword_case", "keyword_when",
  "keyword_break", "keyword_next", "keyword_redo", "keyword_retry",
  "keyword_in", "keyword_do", "keyword_do_cond", "keyword_do_block",
  "keyword_do_LAMBDA", "keyword_return", "keyword_yield", "keyword_super",
  "keyword_self", "keyword_nil", "keyword_true", "keyword_false",
  "keyword_and", "keyword_or", "keyword_not", "modifier_if",
  "modifier_unless", "modifier_while", "modifier_until", "modifier_rescue",
  "keyword_alias", "keyword_BEGIN", "keyword_END", "keyword__LINE__",
  "keyword__FILE__", "keyword__ENCODING__", "\"local variable or method\"",
  "\"method\"", "\"global variable\"", "\"instance variable\"",
  "\"constant\"", "\"class variable\"", "\"label\"", "\"integer literal\"",
  "\"float literal\"", "\"character literal\"", "tXSTRING", "tREGEXP",
  "tSTRING", "tSTRING_PART", "tSTRING_MID", "tNTH_REF", "tBACK_REF",
  "tREGEXP_END", "\"numbered parameter\"", "\"unary plus\"",
  "\"unary minus\"", "\"<=>\"", "\"==\"", "\"===\"", "\"!=\"", "\">=\"",
  "\"<=\"", "\"&&\"", "\"||\"", "\"=~\"", "\"!~\"", "\"..\"", "\"...\"",
  "tBDOT2", "tBDOT3", "tAREF", "tASET", "\"<<\"", "\">>\"", "\"::\"",
  "tCOLON3", "tOP_ASGN", "\"=>\"", "tLPAREN", "\"(\"", "\")\"", "\"[\"",
  "tLBRACE", "\"{\"", "\"*\"", "tPOW", "\"**\"", "\"&\"", "\"->\"",
  "\"&.\"", "\"symbol\"", "\"string literal\"", "tXSTRING_BEG",
  "tSTRING_DVAR", "tREGEXP_BEG", "tWORDS_BEG", "tSYMBOLS_BEG", "tLAMBEG",
  "\"here document\"", "tHEREDOC_END", "tLITERAL_DELIM",
  "tHD_LITERAL_DELIM", "tHD_STRING_PART", "tHD_STRING_MID", "tLOWEST",
  "'='", "'?'", "':'", "'>'", "'<'", "'|'", "'^'", "'&'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "tUMINUS_NUM", "'!'", "'~'", "tLAST_TOKEN", "'{'",
  "'}'", "'['", "']'", "','", "'`'", "'('", "')'", "';'", "'.'", "'\\n'",
  "$accept", "program", "$@1", "top_compstmt", "top_stmts", "top_stmt",
  "@2", "bodystmt", "compstmt", "stmts", "stmt", "$@3", "command_asgn",
  "command_rhs", "expr", "defn_head", "defs_head", "$@4", "expr_value",
  "command_call", "block_command", "cmd_brace_block", "$@5", "command",
  "mlhs", "mlhs_inner", "mlhs_basic", "mlhs_item", "mlhs_list",
  "mlhs_post", "mlhs_node", "lhs", "cname", "cpath", "fname", "fsym",
  "undef_list", "$@6", "op", "reswords", "arg", "aref_args", "arg_rhs",
  "paren_args", "opt_paren_args", "opt_call_args", "call_args",
  "command_args", "@7", "block_arg", "opt_block_arg", "comma", "args",
  "mrhs", "primary", "@8", "@9", "$@10", "$@11", "@12", "@13", "$@14",
  "$@15", "$@16", "$@17", "$@18", "$@19", "@20", "@21", "@22", "@23",
  "primary_value", "then", "do", "if_tail", "opt_else", "for_var",
  "f_margs", "block_args_tail", "opt_block_args_tail", "block_param",
  "opt_block_param", "block_param_def", "$@24", "opt_bv_decl", "bv_decls",
  "bvar", "f_larglist", "lambda_body", "do_block", "$@25", "block_call",
  "method_call", "brace_block", "@26", "@27", "case_body", "cases",
  "opt_rescue", "exc_list", "exc_var", "opt_ensure", "literal", "string",
  "string_fragment", "string_rep", "string_interp", "@28", "xstring",
  "regexp", "heredoc", "heredoc_bodies", "heredoc_body",
  "heredoc_string_rep", "heredoc_string_interp", "@29", "words", "symbol",
  "basic_symbol", "sym", "symbols", "numeric", "variable", "var_lhs",
  "var_ref", "backref", "superclass", "$@30", "f_opt_arglist_paren",
  "f_arglist_paren", "f_arglist", "f_label", "f_kw", "f_block_kw",
  "f_block_kwarg", "f_kwarg", "kwrest_mark", "f_kwrest", "args_tail",
  "opt_args_tail", "f_args", "f_bad_arg", "f_norm_arg", "f_arg_item",
  "@31", "f_arg", "f_opt_asgn", "f_opt", "f_block_opt", "f_block_optarg",
  "f_optarg", "restarg_mark", "f_rest_arg", "blkarg_mark", "f_block_arg",
  "opt_f_block_arg", "singleton", "$@32", "assoc_list", "assocs", "assoc",
  "operation", "operation2", "operation3", "dot_or_colon", "call_op",
  "call_op2", "opt_terms", "opt_nl", "rparen", "trailer", "term", "nl",
  "terms", "none", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,    61,    63,    58,    62,    60,   124,    94,    38,    43,
      45,    42,    47,    37,   376,    33,   126,   377,   123,   125,
      91,    93,    44,    96,    40,    41,    59,    46,    10
};
# endif

#define YYPACT_NINF (-865)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-613)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -865,   141,  3686,  -865,  8674, 10798, 11140,  6982,  -865, 10444,
   10444,  -865,  -865, 10912,  8164,  6598,  8910,  8910,  -865,  -865,
    8910,  4343,  3935,  -865,  -865,  -865,  -865,    96,  8164,  -865,
      39,  -865,  -865,  -865,  7124,  3799,  -865,  -865,  7266,  -865,
    -865,  -865,  -865,  -865,  -865,  -865,   145, 10562, 10562, 10562,
   10562,   140,  5857,  1267,  9382,  9736,  8446,  -865,  7882,   904,
     335,   393,  1098,  1184,  -865,   287, 10680, 10562,  -865,  1179,
    -865,  1356,  -865,   382,  1301,  1301,  -865,  -865,   221,    89,
    -865,   117, 11026,  -865,   186, 13068,   124,   134,    56,   100,
    -865,   314,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,
    -865,    51,   248,  -865,   251,    36,  -865,  -865,  -865,  -865,
    -865,   207,   207,    96,   623,   946,  -865, 10444,   239,  5976,
     415,  1435,  1435,  -865,   258,  -865,   323,  -865,  -865,    36,
    -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,
    -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,
    -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,    23,    44,
      52,    57,  -865,  -865,  -865,  -865,  -865,  -865,    72,    76,
     157,   182,  -865,   190,  -865,  -865,  -865,  -865,  -865,  -865,
    -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,
    -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,
    -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,   203,
    5035,   321,   382,  1301,  1301,   102,   268, 13192,   497,   233,
     305,   316,   102, 10444, 10444,   669,   360,  -865,  -865,   712,
     378,    58,    74,  -865,  -865,  -865,  -865,  -865,  -865,  -865,
    -865,  -865,  8023,  -865,  -865,   299,  -865,  -865,  -865,  -865,
    -865,  -865,  1179,  -865,   213,  -865,   427,  -865,  -865,  1179,
    4071, 10562, 10562, 10562, 10562,  -865, 13130,  -865,  -865,   337,
     399,   337,  -865,  -865,  -865,  9028,  -865,  -865,  -865,  8910,
    -865,  -865,  -865,  6598,  6836,  -865,   355,  6095,  -865,   785,
     410, 13254, 13254,   461,  8792,  5857,   370,  1179,  1356,  1179,
     416,  -865,  8792,  1179,   414,  1324,  1324,  -865, 13130,   422,
    1324,  -865,   526, 11254,   441,   813,   924,   941,  1610,  -865,
    -865,  -865,  -865,  1212,  -865,  -865,  -865,  -865,  -865,  -865,
     315,  1247,  -865,  -865,   776,  -865,   553,  -865,  1252,  -865,
    1255,   491,   492,  -865,  -865,  -865,  -865,  6360, 10444, 10444,
   10444, 10444,  8792, 10444, 10444,    47,  -865,  -865,  -865,  -865,
    -865,  1179,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  1963,
     473,   477,  5035, 10562,  -865,   462,   561,   479,  -865,  1179,
    -865,  -865,  -865,   484, 10562,  -865,   485,   568,   494,   583,
    -865,  -865,   487,  5035,  -865,  -865,  9854,  -865,  5857,  8560,
     498,  9854, 10562, 10562, 10562, 10562, 10562, 10562, 10562, 10562,
   10562, 10562, 10562, 10562, 10562, 10562,   592, 10562, 10562, 10562,
   10562, 10562, 10562, 10562, 10562, 10562, 10562, 10562, 10562,  2428,
    -865,  8910,  -865,  3143,  -865,  -865, 12650,  -865,  -865,  -865,
    -865, 10680, 10680,  -865,   562,  -865,   382,  -865,   999,  -865,
    -865,  -865,  -865,  -865,  -865, 11532,  8910, 11618,  5035, 10444,
    -865,  -865,  -865,   641,   655,   344,   558,   566,  -865,  5181,
     682, 10562, 11704,  8910, 11790, 10562, 10562,  5473,   167,   167,
     103, 11876,  8910, 11962,  -865,   636,  -865,  6095,   427,  -865,
    -865,  9972,   685,  -865, 10562, 13192, 13192, 13192, 10562,  -865,
    -865,  9146,  -865, 10562,  -865,  9500,  6717,   559,  1179,   337,
     337,  -865,  -865,   759,   564,  -865,  -865,  -865,  8164,  5592,
     563, 11704, 11790, 10562,  1356,  1179,  -865,  -865,  6479,   569,
    1356,  -865,  -865,  9618,  -865,  1179,  9736,  -865,  -865,  -865,
     999,   117, 11254,  -865, 11254, 12048,  8910, 12134,  2259,  -865,
    -865,   570,  -865,  1259,  6095,   315,  -865,  -865,  -865,  -865,
    -865,  -865,  -865, 10562, 10562,  -865,  -865,  -865,  -865,  -865,
    -865,  -865,  -865,  -865,  -865,  -865,  1236,  1179,  1179,   576,
   10680,   688, 13192,    54,  -865,  -865,  -865,   198,  -865,  -865,
    2093,  -865, 13192,  2259,  -865,  -865,  1289,  -865,  -865, 10680,
     704,    43, 10562,  -865, 12784,   337,  -865,  1179, 11254,   581,
    -865,  -865,  -865,   680,   614,  2039,  -865,  -865,  1018,   348,
    3042,  3042,  3042,  3042,  1617,  1617,  3376,  2927,  3042,  3042,
   13254, 13254,  1153,  1153,  -865,   410, 13192,  1617,  1617,  1278,
    1278,  1426,   234,   234,   410,   410,   410,  4479,  7622,  4751,
    7740,  -865,   207,  -865,   597,   337,   509,  -865,   589,  -865,
    -865,  4207,  -865,  -865,  1791,    43,    43,  -865,  2539,  -865,
    -865,  -865,  -865,  -865,  1179, 10444,  5035,   963,   777,  -865,
     207,   599,   207,   729,   759,  8305,  -865, 10090,   732,  -865,
   10562, 10562,   466,  -865,  7384,  7503,   606,   397,   405,   732,
    -865,  -865,  -865,  -865,    71,    86,   615,   111,   112, 10444,
    8164,   621,   747, 13192,   639,  -865, 13192, 13192,  1089, 10562,
   13130,  -865,   337, 13192,  -865,  -865,  -865,  -865,  9264,  9500,
    -865,  -865,  -865,   632,  -865,  -865,    33,  1356,  1179,  1324,
     498,  -865,   963,   777,   631,  1051,  1134,  -865,    95,  2259,
    -865,   637,  -865,   410,   410,  -865,   901,  1179,   635,  -865,
    -865,  2153,   734,  3255,  -865,   722,  -865,   479,  -865,  1179,
    -865,  -865,   644,   646,   647,  -865,   649,   722,   647,   749,
   12722,  -865,  -865,  2259,  5035,  -865,  -865, 12855, 10208,  -865,
    -865, 11254,  8792, 10680, 10562, 12220,  8910, 12306,   869, 10680,
   10680,  -865,   562,   609,  9146, 10680, 10680,  -865,   562,   100,
     221,  5035,  6095,    43,  -865,  1179,   780,  -865,  -865,  -865,
    -865, 12784,  -865,   705,  -865,  5738,   789,  -865, 10444,   795,
    -865, 10562, 10562,   408, 10562, 10562,   800,  6241,  6241,   115,
     167,  -865,  -865,  -865, 10326,  5327, 13192,  -865,  6717,   337,
    -865,  -865,  -865,   495,   673,  1380,  5035,  6095,  -865,  -865,
    1579,   681,  -865,  1454,  1179, 10562, 10562,  -865,  -865,  2259,
    -865,  1289,  -865,  1289,  -865,  1289,  -865,  -865, 10562, 10562,
    -865,  -865,  -865, 11368,  -865,   683,   479,   689, 11368,  -865,
     693,   696,  -865,   807, 10562, 12926,  -865,  -865, 13192,  4615,
    4887,   708,   412,   442, 10562, 10562,  -865,  -865,  -865,  -865,
    -865, 10680,  -865,  -865,  -865,  -865,  -865,  -865,  -865,   835,
     718,  6095,  5035,  -865,  -865, 11482,   102,  -865,  -865,  6241,
    -865,  -865,   102,  -865, 10562,  -865,   843,   846,  -865, 13192,
     294,  -865,  9500,  -865,  1517,   848,   730,   731,  1579,  1118,
    -865, 13192, 13192,   647,   739,   647,   647, 13192, 13192,   750,
     760,   832,  1019,    54,  -865,  -865,  1746,  -865,  1019,  2259,
    -865,  1289,  -865,  -865, 12997,   475, 13192, 13192,  -865,  -865,
    -865,  -865,   755,   880,   842,  -865,  1046,   924,   941,  5035,
    -865,  5181,  -865,  -865,  6241,  -865,  -865,  -865,  -865,   770,
    -865,  -865,  -865,  -865,  1579,   731,  1579,   774,  -865,  1289,
    -865,  -865,  -865,  -865,  -865,  -865, 12392,  -865,   479,    54,
    -865,  -865,   778,   781,   792,  -865,   794,   792,  -865,  -865,
     999, 12478,  8910, 12564,   655,   466,   887,  1517,  1089,   731,
    1579,   647,   783,   797,  -865,  2259,  -865,  1289,  -865,  1289,
    -865,  1289,  -865,  -865,   963,   777,   801,   160,   753,  -865,
    -865,  -865,  -865,   731,  -865,   792,   804,   792,   792,   495,
    -865,  1289,  -865,  -865,  -865,   792,  -865
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     0,   293,     0,
       0,   317,   320,     0,     0,   598,   337,   338,   339,   340,
     305,   270,   270,   487,   486,   488,   489,   600,     0,    10,
       0,   491,   490,   492,   478,   584,   480,   479,   482,   481,
     474,   475,   436,   437,   493,   494,   291,     0,     0,     0,
       0,     0,     0,   295,   612,   612,    88,   312,     0,     0,
       0,     0,     0,     0,   451,     0,     0,     0,     3,   598,
       6,     9,    27,    33,   540,   540,    49,    60,    59,     0,
      76,     0,    80,    90,     0,    54,   248,     0,    61,   310,
     284,   285,   434,   286,   287,   288,   432,   431,   463,   433,
     430,   485,     0,   289,   290,   270,     5,     8,   337,   338,
     305,   612,   412,     0,   113,   114,   291,     0,     0,     0,
       0,   540,   540,   116,   495,   341,     0,   485,   290,     0,
     333,   168,   178,   169,   165,   194,   195,   196,   197,   176,
     191,   184,   174,   173,   189,   172,   171,   167,   192,   166,
     179,   183,   185,   177,   170,   186,   193,   188,   187,   180,
     190,   175,   164,   182,   181,   163,   161,   162,   158,   159,
     160,   118,   120,   119,   153,   154,   131,   132,   133,   140,
     137,   139,   134,   135,   155,   156,   141,   142,   146,   149,
     150,   136,   138,   128,   129,   130,   143,   144,   145,   147,
     148,   151,   152,   157,   571,    55,   121,   122,   570,     0,
       0,     0,    58,   540,   540,     0,     0,    54,     0,   485,
       0,   290,     0,     0,     0,   112,     0,   352,   351,     0,
       0,   485,   290,   187,   180,   190,   175,   158,   159,   160,
     118,   119,     0,   123,   125,    20,   124,   454,   459,   458,
     606,   608,   598,   609,     0,   456,     0,   610,   607,   599,
     582,     0,     0,   273,     0,   265,   277,    74,   269,   612,
     434,   612,   575,    75,    73,   612,   259,   306,    72,     0,
     258,   411,    71,   598,     0,    18,     0,     0,   221,     0,
     222,   209,   212,   302,     0,     0,     0,   598,    15,   598,
      78,    14,     0,   598,     0,   603,   603,   249,     0,     0,
     603,   573,     0,     0,    86,     0,    96,   103,   540,   468,
     467,   469,   470,     0,   466,   465,   438,   443,   442,   445,
       0,     0,   440,   447,     0,   449,     0,   461,     0,   472,
       0,   476,   477,    53,   236,   237,     4,   599,     0,     0,
       0,     0,     0,     0,     0,   547,   543,   542,   541,   544,
     545,     0,   549,   561,   516,   517,   565,   564,   560,   540,
       0,   503,     0,   509,   514,   612,   519,   612,   539,     0,
     546,   548,   551,   525,     0,   558,   525,   563,   525,   567,
     523,   499,     0,     0,   399,   401,     0,    92,     0,    84,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   208,   211,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     595,   612,   594,     0,   597,   596,     0,   416,   414,   311,
     435,     0,     0,   405,    65,   309,   330,   113,   114,   115,
     476,   477,   503,   496,   328,     0,   612,     0,     0,     0,
     593,   592,    56,     0,   612,   302,     0,     0,   343,     0,
     342,     0,     0,   612,     0,     0,     0,     0,     0,     0,
     302,     0,   612,     0,   325,     0,   126,     0,     0,   455,
     457,     0,     0,   611,   579,   278,   581,   272,     0,   600,
     266,     0,   275,     0,   267,     0,   598,     0,   598,   612,
     612,   260,   271,   598,     0,   308,    52,   601,     0,     0,
       0,     0,     0,     0,    17,   598,   300,    13,   599,    77,
     296,   299,   303,   605,   250,   604,   605,   252,   304,   574,
     102,    94,     0,    89,     0,     0,   612,     0,   540,   313,
     396,   525,   471,     0,     0,   446,   452,   439,   441,   448,
     450,   462,   473,     0,     0,     7,    21,    22,    23,    24,
      25,    50,    51,   507,   553,   506,     0,   598,   598,   525,
       0,     0,   508,     0,   521,   569,   518,     0,   522,   504,
       0,   532,   554,     0,   535,   562,     0,   537,   566,     0,
       0,   612,     0,    28,    30,     0,    31,   598,     0,    82,
      93,    48,    34,    46,     0,   253,   198,    29,     0,   290,
     226,   231,   232,   233,   228,   230,   240,   241,   234,   235,
     207,   210,   238,   239,    32,   218,   600,   227,   229,   223,
     224,   225,   213,   214,   215,   216,   217,   585,   590,   586,
     591,   410,   270,   408,     0,   612,   585,   587,   586,   588,
     409,   270,   585,   586,   270,   612,   612,    35,   253,   199,
      45,   206,    63,    66,     0,     0,     0,   113,   114,   117,
       0,     0,   612,     0,   598,     0,   294,   612,   612,   422,
       0,     0,   612,   344,   589,   301,     0,   585,   586,   612,
     346,   318,   345,   321,   589,   301,     0,   585,   586,     0,
       0,     0,     0,   277,     0,   324,   578,   577,   276,     0,
     279,   274,   612,   580,   576,   257,   255,   261,   262,   264,
     307,   602,    19,     0,    26,   205,    79,    16,   598,   603,
      95,    87,    99,   101,     0,    98,   100,   600,     0,     0,
     464,     0,   453,   219,   220,   547,   360,   598,   353,   502,
     500,     0,    41,   244,   335,     0,   515,   612,   568,     0,
     524,   552,   525,   525,   525,   559,   525,   547,   525,    43,
     246,   336,   387,   385,     0,   384,   383,   283,     0,    91,
      85,     0,     0,     0,     0,     0,   612,     0,     0,     0,
       0,   407,    69,   413,   262,     0,     0,   406,    67,   402,
      62,     0,     0,   612,   331,     0,     0,   413,   334,   572,
      57,   423,   424,   612,   425,     0,   612,   349,     0,     0,
     347,     0,     0,   413,     0,     0,     0,     0,     0,   413,
       0,   127,   460,   323,     0,     0,   280,   268,   598,   612,
      11,   297,   251,    97,     0,   389,     0,     0,   314,   444,
       0,   358,   550,     0,   598,     0,     0,   520,   505,     0,
     528,     0,   530,     0,   536,     0,   533,   538,     0,     0,
     382,   600,   600,   511,   512,   612,   612,   367,     0,   556,
     367,   367,   365,     0,     0,   281,    83,    47,   254,   585,
     586,     0,   585,   586,     0,     0,    40,   203,    39,   204,
      70,     0,    37,   201,    38,   202,    68,   403,   404,     0,
       0,     0,     0,   497,   329,     0,     0,   427,   350,     0,
      12,   429,     0,   315,     0,   316,     0,     0,   326,   279,
     612,   256,   263,   395,     0,     0,     0,   361,     0,   356,
     501,    42,   245,   525,   525,   525,   525,    44,   247,     0,
       0,     0,   510,     0,   363,   364,   367,   375,   555,     0,
     378,     0,   380,   400,   282,   413,   243,   242,    36,   200,
     417,   415,     0,     0,     0,   426,     0,   104,   111,     0,
     428,     0,   319,   322,     0,   419,   420,   418,   393,   600,
     391,   394,   398,   397,     0,   359,     0,   354,   529,     0,
     526,   531,   534,   388,   386,   302,     0,   513,   612,     0,
     366,   373,   367,   367,   367,   557,   367,   367,    64,   332,
     110,     0,   612,     0,   612,   612,     0,     0,   390,   357,
       0,   525,   589,   301,   362,     0,   370,     0,   372,     0,
     379,     0,   376,   381,   107,   109,     0,   585,   586,   421,
     348,   327,   392,   355,   527,   367,   367,   367,   367,   105,
     371,     0,   368,   374,   377,   367,   369
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -865,  -865,  -865,   403,  -865,    41,  -865,  -233,   137,  -865,
      40,  -865,   -60,  -215,   560,  1421,  1889,  -865,    20,   -57,
    -865,  -657,  -865,    30,   934,  -211,   -19,   -50,  -286,  -443,
      -8,  2634,   -61,   942,     9,   -17,  -865,  -865,    42,  -865,
    1196,  -865,   503,    73,  -141,  -365,    99,    -7,  -865,  -440,
    -240,  -157,   147,  -363,    97,  -865,  -865,  -865,  -865,  -865,
    -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,  -865,
    -865,     8,  -200,  -450,   -76,  -620,  -865,  -865,   178,   154,
    -865,  -536,  -865,  -865,  -309,  -865,   -74,  -865,  -865,   155,
    -865,  -865,  -865,   -88,  -865,  -865,  -452,  -865,   -68,  -865,
    -865,  -865,  -865,  -865,   -14,    26,  -148,  -865,  -865,  -865,
    -865,  -865,  -259,  -865,   717,  -865,  -865,  -865,     6,  -865,
    -865,  -865,  2469,  2735,   966,  2054,  -865,  -865,   -16,   458,
      22,  -633,   398,    27,  -865,  -865,  -865,   302,    84,  -126,
    -249,  -864,  -681,  -438,  -865,    29,  -650,  -542,  -838,    17,
    -527,  -865,  -338,  -865,   181,  -340,  -865,  -865,  -865,    38,
    -429,   656,  -351,  -865,  -865,   -80,  -865,    66,   -23,   557,
    -267,   327,  -258,   -64,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    68,    69,    70,   286,   463,   464,   297,
     298,   518,    72,   612,    73,   213,   214,   685,   215,    76,
      77,   673,   813,    78,    79,   299,    80,    81,    82,   543,
      83,   216,   123,   124,   243,   244,   245,   710,   650,   207,
      85,   304,   616,   651,   277,   507,   508,   278,   279,   268,
     500,   536,   655,   606,    86,   210,   302,   738,   303,   318,
     748,   223,   837,   224,   838,   709,   994,   676,   674,   922,
     458,   289,   469,   701,   829,   830,   230,   757,  1020,   967,
     881,   784,   785,   882,   854,   999,  1000,   549,   858,   395,
     601,    88,    89,   445,   666,   665,   492,   997,   688,   823,
     926,   930,    90,    91,    92,   331,   332,   554,    93,    94,
      95,   555,   253,   254,   255,   487,    96,    97,    98,   325,
      99,   100,   219,   220,   103,   221,   454,   675,   370,   371,
     372,   373,   374,   884,   885,   375,   376,   377,   770,   591,
     379,   380,   381,   382,   576,   383,   384,   385,   889,   890,
     386,   387,   388,   389,   390,   584,   209,   459,   309,   510,
     272,   129,   680,   653,   462,   457,   436,   514,   855,   515,
     534,   257,   258,   259,   301
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     106,   439,   270,   270,   284,   347,   270,   433,   435,   343,
      87,   285,    87,   126,   126,   282,   205,   218,   218,   280,
     246,   229,   477,   218,   218,   218,   517,   542,   218,   703,
     222,   504,   400,   300,   246,   252,   712,   588,   617,   537,
     270,   270,    71,   539,    71,   107,   265,   265,   314,   206,
     265,   775,   307,   311,   271,   271,   206,   449,   271,   392,
      87,   721,   437,   772,   315,   721,   654,   324,   826,   550,
     206,   556,   391,   391,   218,   861,   724,   440,   652,   836,
    1001,   256,   661,  -104,   525,   664,   334,   336,   338,   340,
     315,   681,   306,   310,   276,   281,  -107,   393,   444,  -111,
     206,   741,   125,   125,   573,   765,   682,   724,   696,   280,
     125,  -109,   501,  -487,   505,   267,   273,   706,   468,   274,
     578,   652,   782,   661,   856,   218,   437,    87,  -110,   811,
     812,  1025,   682,   888,  -486,   346,  -106,  -108,   474,   581,
    -105,     3,  -488,  -483,   393,   910,   434,  -489,   533,   483,
     883,   916,   771,   125,   -77,   364,   365,   366,   378,   378,
     600,   430,  -491,   269,   269,   790,  -490,   269,   574,   783,
    -487,   682,  -104,  1001,   438,   -91,  -106,   287,   443,   125,
     275,   744,   367,   558,   276,   281,   558,   607,   558,   296,
     558,  -486,   558,   -96,   700,   293,   682,   466,   467,  -488,
     -96,   305,   443,   432,  -489,   378,   378,  1025,   857,   522,
     396,   391,   391,   -99,  -341,  -585,  -103,   247,    87,  -491,
     248,   249,   772,  -490,   429,   683,   667,   670,  -101,  -341,
    -586,   218,   218,   528,   772,   547,   393,  -484,   438,   430,
     283,   535,   535,   478,   479,  -102,   535,  -492,   250,   394,
     251,   324,   773,   -98,  -100,   776,   296,   -97,   542,   397,
     594,   270,   597,   541,  -341,   270,  -112,   502,  1007,   502,
     504,  -341,  -478,   511,   431,  -106,   300,   921,  -106,  -106,
    -482,   432,   247,   218,   206,   248,   249,   218,   721,   721,
     447,   218,   218,   460,   448,    87,   752,   378,   378,   747,
     724,   366,    87,    87,  -492,   265,  -106,   401,  -106,   265,
      87,   771,   825,   250,   491,   251,   888,   271,   488,   888,
     995,   315,   542,   771,   822,  -483,   367,   775,   489,  -478,
     883,   248,   249,   883,   524,   417,   883,  -482,   883,   603,
     441,   611,   530,   442,   613,   341,   342,   551,   896,   553,
     461,   275,   728,   729,  -104,    87,   218,   218,   218,   218,
      87,   218,   218,   527,   721,   426,   427,   428,   566,   567,
     568,   569,  -111,   585,    42,   585,   465,    43,   512,   300,
      87,   611,   611,   453,   613,   613,   883,    71,   565,   471,
     938,   609,   570,  -103,   679,   888,   333,   475,   579,   327,
     328,    87,   378,   484,   218,   558,    87,   315,   476,   618,
     125,   773,   883,   455,   883,   480,   883,   270,   883,   353,
     354,    59,   509,   773,   520,   771,   269,   867,   430,   511,
     247,   901,   296,   248,   249,   771,   523,  -111,   883,   218,
     442,   486,   270,   816,   652,   891,   661,   491,   788,   618,
     618,   329,   330,   378,   511,   335,   503,   327,   328,   270,
     517,   265,   689,   456,   218,  -110,    87,   218,   270,  -111,
     432,   511,   852,   450,   451,   659,   718,    87,   659,   499,
     511,   218,   847,   828,   825,    87,   265,   270,   996,   834,
     218,   270,   740,   519,   541,    87,   125,   835,   804,   659,
     934,   732,   721,   265,   805,   542,   660,   502,   502,   329,
     330,   417,   265,   724,   845,   526,   659,   106,  -106,   270,
     807,  -413,   270,   809,   246,   659,  -108,    87,   771,  -105,
     660,   954,   270,  -106,   806,   296,    87,   -76,   797,   722,
     517,   807,   470,   605,   511,   964,   965,   660,   605,   470,
     315,   893,   315,   523,   218,   532,   660,   844,   541,    71,
     206,   538,    87,  -108,   659,   505,   771,   911,   737,   212,
     212,   739,   959,   960,   727,   212,   265,   551,   919,   452,
     452,   540,  -110,   544,   906,  -413,   493,   472,   218,   659,
     912,   914,   563,   564,   580,   660,  -105,   517,  -498,   786,
    -413,   805,   430,  -102,   583,   758,   692,   218,   599,   847,
     762,   771,   586,   798,   699,   560,   315,   327,   328,   595,
     660,   587,   774,   945,   711,   778,   590,   593,  1023,   779,
    -106,  1026,   378,  -413,   598,  -413,   596,   473,   714,   125,
     610,   125,  -413,   634,   432,   802,   870,   872,   874,  -582,
     876,   -98,   877,   502,   808,   468,   686,   810,   105,   280,
     105,   672,   280,   786,   786,   105,   105,  1056,   687,   329,
     330,   105,   105,   105,   493,   535,   105,   446,  1044,   690,
     280,   806,   682,   218,    87,   824,   827,   691,   575,   983,
     827,   751,   942,   841,   820,   815,   978,   827,   693,   552,
     715,   911,   734,   764,   726,   125,   589,  1066,   105,   731,
    -108,   -91,   749,  -478,   270,   270,   246,   218,   761,   781,
     502,   917,   105,   791,   792,   801,   989,   206,  -478,   840,
    -105,  -100,   991,   611,   276,   793,   613,   276,   803,   611,
     817,   541,   613,   908,   818,   611,   611,   833,   613,   613,
     825,   -97,   206,   801,   247,   276,   839,   248,   249,  -291,
     842,  -582,   843,  -478,   768,   585,   849,  -582,   768,  -108,
    -478,   850,   853,   105,  -291,   105,   859,   863,   865,   573,
     517,   499,   270,   212,   212,   250,   869,   251,   871,   873,
     270,   875,    87,   878,   511,   924,   353,   354,   925,   315,
      87,   618,   481,   929,   218,   702,   702,   618,   218,  -291,
     933,   786,   887,   618,   618,   935,  -291,   430,   943,    87,
      87,   927,   973,   948,   931,   963,   265,  1008,  1010,  1011,
    1012,   966,   897,    87,   605,   969,   218,   559,   971,   659,
     327,   328,   849,   513,   516,    87,    87,   502,   932,   975,
     980,   611,   482,    87,   613,   493,   529,   981,   992,   432,
     531,   993,   493,  1002,    87,    87,   105,  -301,  -108,  1003,
     660,  -108,  -108,  1004,   247,   521,  1013,   248,   249,   105,
     105,  1009,  -301,   585,   585,   767,  1014,  1015,   125,   947,
     430,   962,   329,   330,  1028,  1029,   968,  1030,   953,  -108,
     955,  -108,  1061,   545,   956,   250,  1033,   251,   212,   212,
     212,   212,  1037,   571,   572,  1064,  1040,  -301,   430,   618,
    1045,  -586,   733,  1047,  -301,   473,   904,  -585,   270,    87,
      87,   105,   432,   986,  1049,   105,  1051,    87,   827,   105,
     105,  -586,  1069,   105,   669,   671,  1071,   227,   130,   920,
     105,   105,   755,   546,   356,   357,   358,   359,   105,  1060,
     432,   880,   928,  1062,   892,   918,  1059,   326,   327,   328,
     360,   490,  -583,   208,   936,   937,  1038,  1005,   669,   671,
     125,   766,   940,  1022,   247,   125,     0,   248,   249,  -589,
    1017,     0,   905,     0,   946,     0,     0,    87,  1024,    87,
    1027,   814,    87,   105,   105,   105,   105,   105,   105,   105,
     105,     0,     0,     0,  -485,     0,   585,   251,   270,   684,
     329,   330,   125,     0,     0,     0,   735,     0,   105,  -485,
     511,  -290,   689,   827,     0,  1039,  -482,     0,  1041,     0,
     218,   470,     0,   860,   970,   972,  -290,     0,     0,   105,
       0,  -482,   105,  -589,   105,     0,     0,   105,   982,     0,
       0,     0,   265,   725,  -485,     0,   990,     0,  -589,  1063,
     730,  -485,     0,     0,  1065,   659,  1067,  -585,     0,     0,
    1068,  -290,   736,     0,  -583,   886,  -482,   105,  -290,  -302,
    -583,     0,     0,  -482,     0,     0,   868,   105,   105,     0,
    1075,  -589,     0,  -589,  -302,     0,   660,  -585,   795,  1016,
    -589,     0,   105,     0,   105,   105,     0,     0,     0,     0,
    1021,     0,     0,   430,   430,   105,  1034,     0,  1035,   105,
       0,  1036,     0,   105,   759,   760,  1031,     0,   105,  -302,
       0,  -585,   923,   105,   768,     0,  -302,   892,     0,     0,
     892,   430,   892,     0,     0,     0,  -585,     0,   796,   456,
    -586,   337,   327,   328,   789,   432,   432,   702,     0,   755,
       0,   356,   357,   358,   359,   105,  1046,  1048,  1050,     0,
    1052,  1053,     0,     0,   105,     0,  1032,   360,     0,  -585,
       0,  -585,     0,   432,     0,  -585,     0,     0,  -585,     0,
     892,     0,   105,     0,   247,   217,   217,   248,   249,     0,
     105,   217,   266,   266,   329,   330,   266,     0,     0,  1070,
    1072,  1073,  1074,     0,  -586,     0,   892,     0,   892,  1076,
     892,     0,   892,     0,     0,   212,   105,   251,     0,  -586,
       0,   819,     0,   288,   290,   291,   292,   339,   327,   328,
     266,   308,   892,   470,   417,   105,     0,     0,     0,   470,
    1006,     0,   344,   345,     0,  1018,     0,     0,   886,   212,
       0,   886,  -586,   886,  -586,   552,   327,   328,  -586,     0,
       0,  -586,   424,   425,   426,   427,   428,   755,     0,   356,
     357,   358,   359,     0,   247,   851,     0,   248,   249,     0,
     329,   330,   907,   909,     0,   360,     0,     0,   913,   915,
     557,   327,   328,   217,   862,   561,   327,   328,   562,   327,
     328,   886,   750,   327,   328,   250,     0,   251,   329,   330,
     362,   105,   105,     0,   907,   909,   756,   913,   915,     0,
     777,     0,   356,   357,   358,   359,     0,   886,     0,   886,
       0,   886,   355,   886,   356,   357,   358,   359,   360,     0,
       0,     0,     0,   329,   330,   105,   414,   415,   329,   330,
     360,   329,   330,   886,     0,   329,   330,     0,     0,   417,
       0,     0,  -298,   362,   361,  -298,  -298,     0,   212,     0,
     364,   365,   366,     0,     0,   362,   348,   349,   350,   351,
     352,   363,   364,   365,   366,   941,   423,   424,   425,   426,
     427,   428,  -298,  -298,   979,  -298,     0,   367,     0,   217,
     217,   950,  -612,    74,     0,    74,   121,   121,     0,   367,
       0,     0,   368,     0,   121,     0,     0,   979,     0,   247,
     105,     0,   248,   249,     0,   369,     0,     0,   105,   105,
       0,     0,   105,     0,     0,   105,   105,   495,   496,   497,
     344,   105,   105,     0,     0,     0,   499,   105,   105,     0,
     250,   266,   251,    74,     0,   266,     0,   121,     0,   217,
     217,   105,     0,     0,   105,     0,   355,     0,   356,   357,
     358,   359,     0,   105,   105,   247,     0,     0,   248,   249,
       0,   105,     0,   121,   360,   755,     0,   356,   357,   358,
     359,     0,   105,   105,   414,   415,     0,     0,   361,     0,
       0,     0,     0,   360,     0,     0,   944,   417,   251,   362,
       0,     0,     0,     0,     0,   363,   364,   365,   366,     0,
      74,     0,     0,     0,   217,   217,   217,   217,   362,   217,
     217,     0,     0,     0,   949,   424,   425,   426,   427,   428,
       0,     0,     0,   367,     0,     0,   368,   105,   998,   582,
     356,   357,   358,   359,     0,     0,     0,   105,   105,   369,
     592,     0,     0,     0,     0,   105,   360,     0,     0,     0,
       0,     0,   604,     0,     0,     0,     0,   615,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   631,
     632,   633,     0,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   645,   646,     0,     0,   266,     0,     0,
     755,    74,   356,   357,   358,   359,     0,   668,   668,     0,
       0,     0,     0,     0,     0,   105,     0,   105,   360,     0,
     105,     0,   266,     0,     0,   217,     0,     0,     0,     0,
       0,   355,     0,   356,   357,   358,   359,   668,     0,   266,
       0,   668,   668,   362,     0,     0,     0,     0,   266,   360,
       0,     0,     0,     0,     0,     0,     0,   713,   105,     0,
     716,     0,     0,     0,   717,     0,     0,   720,     0,   723,
       0,   308,   292,     0,   362,   414,   415,     0,    74,     0,
     363,   364,   365,   366,     0,    74,    74,     0,   417,   668,
       0,     0,     0,    74,     0,     0,     0,     0,     0,   720,
       0,     0,   308,     0,   121,     0,     0,     0,   367,     0,
       0,   368,   266,   421,   422,   423,   424,   425,   426,   427,
     428,     0,     0,     0,   548,     0,     0,     0,     0,   753,
     754,     0,     0,     0,     0,     0,     0,     0,    74,     0,
       0,     0,     0,    74,     0,     0,   763,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -612,     0,    74,     0,   780,     0,   355,   787,   356,
     357,   358,   359,     0,  -612,  -612,  -612,  -612,  -612,  -612,
       0,  -612,     0,     0,    74,   360,     0,  -612,  -612,    74,
     121,     0,    74,     0,     0,     0,     0,     0,  -612,  -612,
       0,  -612,  -612,  -612,  -612,  -612,     0,     0,     0,     0,
     362,     0,     0,     0,     0,     0,   363,   364,   365,   366,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    74,    74,     0,     0,     0,     0,     0,     0,
       0,   217,     0,     0,   367,     0,     0,   368,     0,    74,
       0,  -612,     0,   821,     0,     0,   763,   780,  1019,     0,
      74,    75,     0,    75,   122,   122,  -612,     0,    74,     0,
       0,     0,   122,     0,     0,   217,  -612,     0,    74,  -612,
    -612,     0,     0,     0,     0,   846,     0,     0,     0,     0,
       0,     0,     0,     0,   720,   308,     0,     0,     0,  -612,
    -612,     0,     0,     0,     0,   275,  -612,  -612,  -612,  -612,
      74,    75,     0,     0,     0,   122,     0,     0,     0,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   121,     0,   121,     0,     0,     0,     0,
       0,   122,     0,     0,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,   895,     0,     0,     0,     0,   668,
     898,     0,   266,     0,     0,   668,   668,     0,     0,     0,
     720,   668,   668,     0,     0,     0,     0,     0,    75,     0,
       0,     0,     0,     0,   355,     0,   356,   357,   358,   359,
       0,     0,     0,     0,   217,     0,     0,   668,   668,   121,
     668,   668,   360,     0,     0,     0,     0,     0,     0,     0,
     939,     0,     0,     0,   292,     0,     0,     0,   577,     0,
       0,     0,     0,     0,     0,     0,   104,   362,   104,   128,
     128,   951,   952,   363,   364,   365,   366,   232,     0,     0,
       0,     0,     0,     0,   957,   958,     0,     0,     0,     0,
       0,     0,     0,   794,     0,     0,     0,     0,     0,     0,
     974,   367,     0,     0,   368,     0,     0,    74,     0,    75,
     976,   977,     0,     0,     0,     0,   104,   668,     0,     0,
     317,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,     0,     0,     0,     0,   414,   415,     0,
     668,     0,     0,     0,     0,     0,   317,     0,   308,     0,
     417,     0,     0,     0,   355,     0,   356,   357,   358,   359,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   418,   360,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   104,     0,     0,    75,     0,   769,     0,
       0,  -277,     0,    75,    75,     0,     0,   362,     0,     0,
       0,    75,     0,   363,   364,   365,   366,     0,     0,     0,
       0,     0,   122,     0,   355,    74,   356,   357,   358,   359,
       0,     0,   121,    74,    74,     0,     0,     0,     0,     0,
      74,   367,   360,     0,   368,     0,    74,    74,   266,     0,
       0,     0,    74,    74,     0,     0,    75,     0,   864,     0,
       0,    75,     0,     0,     0,     0,    74,   362,     0,     0,
       0,     0,     0,   363,   364,   365,   366,     0,    74,    74,
       0,    75,     0,     0,   104,     0,    74,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    74,    74,     0,
       0,   367,    75,     0,   368,     0,     0,    75,   122,     0,
      75,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,     0,     0,     0,     0,   121,
     355,     0,   356,   357,   358,   359,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   360,     0,
      75,    75,    74,     0,     0,     0,     0,     0,     0,     0,
       0,   104,    74,    74,     0,     0,   121,    75,   104,   104,
      74,     0,     0,   362,     0,     0,   104,     0,    75,   363,
     364,   365,   366,     0,     0,     0,    75,   317,     0,     0,
       0,     0,     0,     0,     0,     0,    75,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   367,     0,     0,
     368,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,     0,     0,     0,     0,   104,     0,    75,     0,
      74,     0,    74,     0,     0,    74,     0,    75,     0,     0,
       0,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,   122,     0,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    75,     0,     0,     0,   104,     0,     0,
       0,     0,   104,   317,     0,   619,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   101,     0,   101,   127,   127,   127,     0,     0,   647,
     648,     0,   231,   649,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   619,   619,   122,   174,   175,
     176,   177,   178,   179,   180,   181,     0,     0,   182,   183,
       0,     0,   104,     0,   184,   185,   186,   187,     0,     0,
       0,   101,     0,   104,     0,   316,     0,     0,   188,   189,
     190,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   316,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,     0,   201,   202,    75,     0,     0,     0,     0,
       0,   203,   275,   104,     0,     0,     0,     0,     0,     0,
       0,     0,   104,   794,     0,     0,     0,     0,   101,     0,
       0,     0,     0,     0,     0,     0,   317,     0,   317,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   104,     0,
       0,   402,   403,   404,   405,   406,   407,   408,   409,   410,
     411,   412,   413,     0,     0,     0,     0,   414,   415,     0,
       0,     0,     0,     0,     0,     0,    84,     0,    84,     0,
     417,     0,     0,     0,     0,     0,     0,   228,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   418,   317,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,    75,     0,     0,     0,     0,     0,   101,
     122,    75,    75,     0,     0,     0,    84,     0,    75,     0,
       0,     0,     0,     0,    75,    75,     0,     0,     0,     0,
      75,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,    75,     0,     0,
     104,     0,     0,     0,    75,     0,     0,   102,     0,   102,
       0,     0,     0,     0,     0,    75,    75,     0,     0,     0,
       0,     0,     0,    84,     0,     0,   101,     0,     0,     0,
       0,     0,     0,   101,   101,     0,     0,     0,     0,     0,
       0,   101,   122,     0,     0,     0,     0,   122,     0,     0,
       0,     0,   316,     0,     0,     0,     0,   102,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,    75,     0,     0,   122,     0,   101,     0,    75,     0,
       0,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   104,     0,
       0,   101,     0,     0,    84,   317,   104,   619,     0,     0,
       0,     0,     0,   619,   102,     0,     0,     0,     0,   619,
     619,     0,   101,     0,     0,   104,   104,   101,   316,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,   104,
      75,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,   104,   104,     0,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     104,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    84,     0,     0,     0,     0,     0,   101,    84,    84,
       0,     0,     0,     0,     0,     0,    84,   128,   101,     0,
       0,     0,   128,     0,     0,   102,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,     0,
       0,     0,     0,     0,     0,   619,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104,   104,     0,     0,   988,
       0,    84,     0,   104,     0,     0,    84,     0,   101,     0,
       0,     0,     0,     0,     0,     0,     0,   101,     0,   402,
     403,   404,   405,   406,   407,   408,    84,   410,   411,     0,
       0,   316,     0,   316,     0,   414,   415,     0,     0,     0,
       0,     0,   102,   101,     0,     0,     0,    84,   417,   102,
     102,     0,    84,     0,     0,   614,     0,   102,     0,     0,
       0,     0,     0,   104,     0,   104,     0,     0,   104,     0,
       0,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   614,   614,   316,     0,     0,
       0,     0,   102,     0,     0,     0,     0,   102,     0,     0,
       0,     0,    84,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    84,     0,     0,     0,   102,     0,     0,
       0,    84,     0,     0,  -613,  -613,  -613,  -613,   406,   407,
       0,    84,  -613,  -613,     0,     0,     0,     0,   102,     0,
     414,   415,     0,   102,     0,     0,   102,     0,     0,     0,
       0,     0,     0,   417,     0,   101,     0,     0,     0,     0,
       0,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,    84,     0,     0,     0,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   102,   102,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    84,     0,
       0,     0,     0,   102,   656,   657,     0,     0,   658,     0,
       0,     0,     0,     0,   102,     0,     0,     0,     0,     0,
       0,     0,   102,   174,   175,   176,   177,   178,   179,   180,
     181,     0,   102,   182,   183,     0,     0,     0,     0,   184,
     185,   186,   187,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   188,   189,   190,     0,     0,     0,     0,
       0,     0,     0,   101,   102,     0,     0,     0,     0,     0,
     316,   101,     0,   102,     0,     0,     0,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,     0,   201,   202,
     101,   101,     0,     0,     0,     0,   203,   275,     0,   102,
       0,     0,     0,     0,   101,     0,     0,     0,     0,   866,
       0,     0,     0,     0,     0,     0,   101,   101,     0,     0,
      84,     0,     0,     0,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,   101,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,     0,
       0,     0,     0,   414,   415,     0,     0,     0,     0,     0,
       0,     0,   127,     0,     0,     0,   417,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   418,     0,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,     0,
     101,   101,     0,     0,   987,     0,     0,     0,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   102,     0,     0,     0,     0,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,    84,   614,     0,     0,
       0,     0,     0,   614,     0,     0,     0,     0,     0,   614,
     614,     0,     0,     0,     0,    84,    84,     0,   402,   403,
     404,   405,   406,   407,     0,     0,   410,   411,   101,    84,
     101,     0,     0,   101,   414,   415,     0,     0,     0,     0,
       0,    84,    84,     0,     0,     0,     0,   417,     0,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      84,    84,     0,     0,     0,     0,     0,     0,     0,     0,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   102,
       0,     0,     0,     0,     0,     0,     0,   102,   102,     0,
       0,     0,     0,     0,   102,     0,     0,     0,     0,     0,
     102,   102,     0,     0,     0,   614,   102,   102,     0,     0,
       0,     0,     0,     0,     0,    84,    84,     0,     0,   985,
     102,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,   102,   102,     0,     0,     0,     0,     0,     0,
     102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   102,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    84,     0,    84,     0,     0,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   102,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   102,   102,     0,     0,
       0,     0,     0,     0,   102,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -612,     4,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,     0,     0,     0,     0,    15,     0,    16,    17,    18,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,     0,   102,    27,   102,     0,     0,   102,
       0,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,    51,     0,     0,
      52,    53,     0,    54,    55,     0,    56,     0,     0,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,  -292,
      64,  -612,     0,     0,  -612,  -612,     0,     0,     0,     0,
       0,     0,  -292,  -292,  -292,  -292,  -292,  -292,     0,  -292,
      65,    66,    67,     0,     0,     0,  -292,  -292,  -292,     0,
       0,     0,  -612,     0,  -612,     0,  -292,  -292,     0,  -292,
    -292,  -292,  -292,  -292,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -292,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,
    -292,  -292,  -292,     0,     0,     0,     0,  -292,  -292,  -292,
       0,     0,  -292,     0,     0,     0,     0,     0,  -292,     0,
    -292,     0,     0,     0,  -292,     0,     0,     0,     0,     0,
       0,     0,  -292,     0,  -292,     0,     0,  -292,  -292,     0,
       0,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,
    -292,  -292,  -292,     0,     0,  -412,     0,     0,  -292,  -292,
    -292,  -292,     0,     0,  -292,  -292,  -292,  -292,  -412,  -412,
    -412,  -412,  -412,  -412,     0,  -412,     0,     0,     0,     0,
       0,  -412,  -412,  -412,     0,     0,     0,     0,     0,     0,
       0,     0,  -412,  -412,     0,  -412,  -412,  -412,  -412,  -412,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -412,  -412,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,     0,
       0,     0,     0,  -412,  -412,  -412,     0,     0,  -412,     0,
       0,     0,     0,     0,  -412,     0,  -412,     0,     0,     0,
    -412,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -412,     0,     0,  -412,  -412,     0,     0,  -412,     0,  -412,
    -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,  -412,     0,
       0,  -478,     0,  -412,  -412,  -412,  -412,  -412,     0,   275,
    -412,  -412,  -412,  -412,  -478,  -478,  -478,  -478,  -478,  -478,
       0,  -478,     0,     0,     0,     0,     0,     0,  -478,  -478,
       0,     0,     0,     0,     0,     0,     0,     0,  -478,  -478,
       0,  -478,  -478,  -478,  -478,  -478,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   494,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -478,  -478,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,     0,     0,     0,     0,  -478,
    -478,  -478,     0,  -478,  -478,     0,     0,     0,     0,     0,
    -478,     0,  -478,     0,     0,     0,  -478,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -478,     0,     0,  -478,
    -478,     0,  -478,  -478,     0,  -478,  -478,  -478,  -478,  -478,
    -478,  -478,  -478,  -478,  -478,     0,     0,  -612,     0,     0,
    -478,  -478,  -478,  -478,     0,     0,  -478,  -478,  -478,  -478,
    -612,  -612,  -612,  -612,  -612,  -612,     0,  -612,     0,     0,
       0,     0,     0,  -612,  -612,  -612,     0,     0,     0,     0,
       0,     0,     0,     0,  -612,  -612,     0,  -612,  -612,  -612,
    -612,  -612,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -612,
    -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,
    -612,     0,     0,     0,     0,  -612,  -612,  -612,     0,     0,
    -612,     0,     0,     0,     0,     0,  -612,     0,  -612,     0,
       0,     0,  -612,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -612,     0,     0,  -612,  -612,     0,     0,  -612,
       0,  -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,
    -612,     0,     0,  -612,     0,  -612,  -612,  -612,  -612,  -612,
       0,   275,  -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,
    -612,  -612,     0,  -612,     0,     0,     0,     0,     0,     0,
    -612,  -612,     0,     0,     0,     0,     0,     0,     0,     0,
    -612,  -612,     0,  -612,  -612,  -612,  -612,  -612,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -612,  -612,  -612,  -612,  -612,
    -612,  -612,  -612,  -612,  -612,  -612,  -612,     0,     0,     0,
       0,  -612,  -612,  -612,     0,     0,  -612,     0,     0,     0,
       0,     0,  -612,     0,  -612,     0,     0,     0,  -612,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -612,     0,
       0,  -612,  -612,     0,     0,  -612,     0,  -612,  -612,  -612,
    -612,  -612,  -612,  -612,  -612,  -612,  -612,     0,     0,  -589,
       0,     0,  -612,  -612,  -612,  -612,     0,   275,  -612,  -612,
    -612,  -612,  -589,  -589,  -589,     0,  -589,  -589,     0,  -589,
       0,     0,     0,     0,     0,  -589,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -589,  -589,     0,  -589,
    -589,  -589,  -589,  -589,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -589,  -589,  -589,  -589,  -589,  -589,  -589,  -589,  -589,
    -589,  -589,  -589,     0,     0,     0,     0,  -589,  -589,  -589,
       0,   799,  -589,     0,     0,     0,     0,     0,     0,     0,
    -589,     0,     0,     0,  -589,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -589,     0,     0,  -589,  -589,     0,
    -107,  -589,     0,  -589,  -589,  -589,  -589,  -589,  -589,  -589,
    -589,  -589,  -589,     0,     0,  -589,     0,  -589,  -589,  -589,
       0,   -99,     0,     0,  -589,  -589,  -589,  -589,  -589,  -589,
    -589,     0,  -589,  -589,     0,  -589,     0,     0,     0,     0,
       0,  -589,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -589,  -589,     0,  -589,  -589,  -589,  -589,  -589,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -589,  -589,  -589,
    -589,  -589,  -589,  -589,  -589,  -589,  -589,  -589,  -589,     0,
       0,     0,     0,  -589,  -589,  -589,     0,   799,  -589,     0,
       0,     0,     0,     0,     0,     0,  -589,     0,     0,     0,
    -589,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -589,     0,     0,  -589,  -589,     0,  -107,  -589,     0,  -589,
    -589,  -589,  -589,  -589,  -589,  -589,  -589,  -589,  -589,     0,
       0,  -301,     0,  -589,  -589,  -589,     0,  -589,     0,     0,
    -589,  -589,  -589,  -589,  -301,  -301,  -301,     0,  -301,  -301,
       0,  -301,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -301,  -301,
       0,  -301,  -301,  -301,  -301,  -301,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -301,  -301,  -301,  -301,  -301,  -301,  -301,
    -301,  -301,  -301,  -301,  -301,     0,     0,     0,     0,  -301,
    -301,  -301,     0,   800,  -301,     0,     0,     0,     0,     0,
       0,     0,  -301,     0,     0,     0,  -301,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -301,     0,     0,  -301,
    -301,     0,  -109,  -301,     0,  -301,  -301,  -301,  -301,  -301,
    -301,  -301,  -301,  -301,  -301,     0,     0,  -301,     0,     0,
    -301,  -301,     0,  -101,     0,     0,  -301,  -301,  -301,  -301,
    -301,  -301,  -301,     0,  -301,  -301,     0,  -301,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -301,  -301,     0,  -301,  -301,  -301,
    -301,  -301,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -301,
    -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,
    -301,     0,     0,     0,     0,  -301,  -301,  -301,     0,   800,
    -301,     0,     0,     0,     0,     0,     0,     0,  -301,     0,
       0,     0,  -301,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -301,     0,     0,  -301,  -301,     0,  -109,  -301,
       0,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,
    -301,     0,     0,     0,     0,     0,  -301,  -301,     0,  -301,
       0,     0,  -301,  -301,  -301,  -301,   294,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,  -612,  -612,
    -612,     0,     0,  -612,    15,     0,    16,    17,    18,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,     0,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,    42,     0,     0,    43,     0,
       0,    44,    45,     0,    46,    47,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,    51,     0,     0,    52,
      53,     0,    54,    55,     0,    56,     0,     0,     0,    57,
       0,    58,    59,    60,     0,    61,    62,    63,     0,    64,
    -612,     0,     0,  -612,  -612,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -612,   294,  -612,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,  -612,     0,  -612,  -612,
      15,     0,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,     0,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,    42,     0,     0,    43,     0,     0,    44,    45,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,    51,     0,     0,    52,    53,     0,    54,    55,
       0,    56,     0,     0,     0,    57,     0,    58,    59,    60,
       0,    61,    62,    63,     0,    64,  -612,     0,     0,  -612,
    -612,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -612,   294,  -612,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,  -612,     0,     0,  -612,    15,  -612,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,     0,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,    42,     0,     0,
      43,     0,     0,    44,    45,     0,    46,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,    51,     0,
       0,    52,    53,     0,    54,    55,     0,    56,     0,     0,
       0,    57,     0,    58,    59,    60,     0,    61,    62,    63,
       0,    64,  -612,     0,     0,  -612,  -612,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,    66,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -612,   294,  -612,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,     0,     0,  -612,     0,
       0,  -612,    15,     0,    16,    17,    18,    19,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,     0,    28,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
       0,    40,    41,    42,     0,     0,    43,     0,     0,    44,
      45,     0,    46,    47,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,    51,     0,     0,    52,    53,     0,
      54,    55,     0,    56,     0,     0,     0,    57,     0,    58,
      59,    60,     0,    61,    62,    63,     0,    64,  -612,     0,
       0,  -612,  -612,     4,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,    65,    66,    67,
       0,    15,     0,    16,    17,    18,    19,     0,     0,  -612,
       0,  -612,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,    51,     0,     0,    52,    53,     0,    54,
      55,     0,    56,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,  -612,     0,     0,
    -612,  -612,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    66,    67,     0,
       0,  -612,     0,     0,     0,     0,     0,     0,  -612,   294,
    -612,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,     0,  -612,  -612,     0,     0,     0,    15,     0,    16,
      17,    18,    19,     0,     0,     0,     0,     0,    20,    21,
      22,    23,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,     0,    28,     0,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,    51,
       0,     0,    52,    53,     0,    54,    55,     0,    56,     0,
       0,     0,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,  -612,     0,     0,  -612,  -612,   294,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,    65,    66,    67,     0,    15,     0,    16,    17,
      18,    19,     0,     0,  -612,     0,  -612,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,     0,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,    42,     0,     0,
      43,     0,     0,    44,    45,     0,    46,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,    51,     0,
       0,   295,    53,     0,    54,    55,     0,    56,     0,     0,
       0,    57,     0,    58,    59,    60,     0,    61,    62,    63,
       0,    64,  -612,     0,     0,  -612,  -612,   294,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,     0,
       0,    65,    66,    67,     0,    15,     0,    16,    17,    18,
      19,     0,  -612,  -612,     0,  -612,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,     0,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,    51,     0,     0,
      52,    53,     0,    54,    55,     0,    56,     0,     0,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,  -612,     0,     0,  -612,  -612,   294,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,     0,     0,
      65,    66,    67,     0,    15,     0,    16,    17,    18,    19,
       0,  -612,  -612,     0,  -612,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,     0,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     0,    40,    41,    42,     0,     0,    43,     0,
       0,    44,    45,     0,    46,    47,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,    51,     0,     0,    52,
      53,     0,    54,    55,     0,    56,     0,     0,     0,    57,
       0,    58,    59,    60,     0,    61,    62,    63,     0,    64,
    -612,     0,     0,  -612,  -612,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,     0,     0,  -612,     0,     0,     0,     0,     0,
       0,  -612,   294,  -612,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,  -612,     0,     0,     0,
      15,     0,    16,    17,    18,    19,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,    28,     0,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,     0,    40,
      41,    42,     0,     0,    43,     0,     0,    44,    45,     0,
      46,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,    51,     0,     0,    52,    53,     0,    54,    55,
       0,    56,     0,     0,     0,    57,     0,    58,    59,    60,
       0,    61,    62,    63,     0,    64,  -612,     0,     0,  -612,
    -612,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,     0,     0,    65,    66,    67,     0,    15,
       0,    16,    17,    18,    19,     0,     0,  -612,     0,  -612,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,    51,     0,     0,    52,    53,     0,    54,    55,     0,
      56,     0,     0,     0,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,   247,     0,     0,   248,   249,
       0,     0,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,     0,     0,    65,    66,    67,     0,    15,     0,
      16,    17,    18,    19,     0,     0,   250,     0,   251,    20,
      21,    22,    23,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,     0,    28,     0,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,     0,    40,    41,    42,
       0,     0,    43,     0,     0,    44,    45,     0,    46,    47,
      48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
      51,     0,     0,    52,    53,     0,    54,    55,     0,    56,
       0,     0,     0,    57,     0,    58,    59,    60,     0,    61,
      62,    63,     0,    64,   247,     0,     0,   248,   249,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,    65,    66,    67,     0,    15,     0,    16,
      17,    18,    19,     0,     0,   250,     0,   251,    20,    21,
      22,    23,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,   211,
       0,     0,   119,    53,     0,    54,    55,     0,     0,     0,
       0,     0,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,   247,     0,     0,   248,   249,     0,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,    65,    66,    67,     0,    15,     0,   108,   109,
      18,    19,     0,     0,   250,     0,   251,   110,   111,   112,
      23,    24,    25,    26,     0,     0,   113,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    32,    33,    34,    35,
      36,    37,    38,    39,     0,    40,    41,    42,     0,     0,
      43,     0,     0,    44,    45,     0,    46,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,   211,     0,
       0,   119,    53,     0,    54,    55,     0,     0,     0,     0,
       0,    57,     0,    58,    59,    60,     0,    61,    62,    63,
       0,    64,   247,     0,     0,   248,   249,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,    65,   264,    67,     0,    15,     0,    16,    17,    18,
      19,     0,     0,   250,     0,   251,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,   211,     0,     0,
     119,    53,     0,    54,    55,     0,     0,     0,     0,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,   247,     0,     0,   248,   249,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,    67,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   251,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,     0,
       0,     0,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,     0,     0,     0,     0,     0,   165,   166,   167,
     168,   169,   170,   171,   172,    36,    37,   173,    39,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     0,   182,   183,     0,     0,     0,     0,   184,   185,
     186,   187,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   189,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,   201,   202,     0,
       0,     0,     0,     0,     0,   203,   204,  -582,  -582,  -582,
    -582,  -582,  -582,  -582,  -582,  -582,     0,     0,     0,     0,
       0,     0,     0,  -582,     0,  -582,  -582,  -582,  -582,     0,
    -582,     0,     0,     0,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,     0,     0,  -582,     0,     0,     0,     0,     0,     0,
       0,     0,  -582,  -582,  -582,  -582,  -582,  -582,  -582,  -582,
    -582,     0,  -582,  -582,  -582,     0,     0,  -582,     0,     0,
    -582,  -582,     0,  -582,  -582,  -582,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -582,  -582,
       0,     0,     0,     0,     0,  -582,     0,     0,  -582,  -582,
       0,  -582,  -582,     0,  -582,     0,  -582,  -582,  -582,     0,
    -582,  -582,  -582,     0,  -582,  -582,  -582,     0,  -582,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -582,  -582,
    -582,     0,  -582,     0,     0,     0,     0,     0,  -582,  -583,
    -583,  -583,  -583,  -583,  -583,  -583,  -583,  -583,     0,     0,
       0,     0,     0,     0,     0,  -583,     0,  -583,  -583,  -583,
    -583,     0,  -583,     0,     0,     0,  -583,  -583,  -583,  -583,
    -583,  -583,  -583,     0,     0,  -583,     0,     0,     0,     0,
       0,     0,     0,     0,  -583,  -583,  -583,  -583,  -583,  -583,
    -583,  -583,  -583,     0,  -583,  -583,  -583,     0,     0,  -583,
       0,     0,  -583,  -583,     0,  -583,  -583,  -583,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -583,  -583,     0,     0,     0,     0,     0,  -583,     0,     0,
    -583,  -583,     0,  -583,  -583,     0,  -583,     0,  -583,  -583,
    -583,     0,  -583,  -583,  -583,     0,  -583,  -583,  -583,     0,
    -583,     0,     0,     0,     0,     0,     0,  -585,  -585,  -585,
    -585,  -585,  -585,  -585,  -585,  -585,     0,     0,     0,     0,
    -583,  -583,  -583,  -585,  -583,  -585,  -585,  -585,  -585,     0,
    -583,     0,     0,     0,  -585,  -585,  -585,  -585,  -585,  -585,
    -585,     0,     0,  -585,     0,     0,     0,     0,     0,     0,
       0,     0,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,
    -585,     0,  -585,  -585,  -585,     0,     0,  -585,     0,     0,
    -585,  -585,     0,  -585,  -585,  -585,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -585,  -585,
       0,     0,     0,     0,     0,  -585,   831,     0,  -585,  -585,
       0,  -585,  -585,     0,  -585,     0,  -585,  -585,  -585,     0,
    -585,  -585,  -585,     0,  -585,  -585,  -585,     0,  -585,     0,
       0,     0,     0,     0,     0,  -107,  -586,  -586,  -586,  -586,
    -586,  -586,  -586,  -586,  -586,     0,     0,     0,  -585,  -585,
    -585,     0,  -586,     0,  -586,  -586,  -586,  -586,  -585,     0,
       0,     0,     0,  -586,  -586,  -586,  -586,  -586,  -586,  -586,
       0,     0,  -586,     0,     0,     0,     0,     0,     0,     0,
       0,  -586,  -586,  -586,  -586,  -586,  -586,  -586,  -586,  -586,
       0,  -586,  -586,  -586,     0,     0,  -586,     0,     0,  -586,
    -586,     0,  -586,  -586,  -586,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -586,  -586,     0,
       0,     0,     0,     0,  -586,   832,     0,  -586,  -586,     0,
    -586,  -586,     0,  -586,     0,  -586,  -586,  -586,     0,  -586,
    -586,  -586,     0,  -586,  -586,  -586,     0,  -586,     0,     0,
       0,     0,     0,     0,  -109,  -587,  -587,  -587,  -587,  -587,
    -587,  -587,  -587,  -587,     0,     0,     0,  -586,  -586,  -586,
       0,  -587,     0,  -587,  -587,  -587,  -587,  -586,     0,     0,
       0,     0,  -587,  -587,  -587,  -587,  -587,  -587,  -587,     0,
       0,  -587,     0,     0,     0,     0,     0,     0,     0,     0,
    -587,  -587,  -587,  -587,  -587,  -587,  -587,  -587,  -587,     0,
    -587,  -587,  -587,     0,     0,  -587,     0,     0,  -587,  -587,
       0,  -587,  -587,  -587,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -587,  -587,     0,     0,
       0,     0,     0,  -587,     0,     0,  -587,  -587,     0,  -587,
    -587,     0,  -587,     0,  -587,  -587,  -587,     0,  -587,  -587,
    -587,     0,  -587,  -587,  -587,     0,  -587,     0,     0,     0,
       0,     0,     0,  -588,  -588,  -588,  -588,  -588,  -588,  -588,
    -588,  -588,     0,     0,     0,     0,  -587,  -587,  -587,  -588,
       0,  -588,  -588,  -588,  -588,     0,  -587,     0,     0,     0,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,     0,     0,  -588,
       0,     0,     0,     0,     0,     0,     0,     0,  -588,  -588,
    -588,  -588,  -588,  -588,  -588,  -588,  -588,     0,  -588,  -588,
    -588,     0,     0,  -588,     0,     0,  -588,  -588,     0,  -588,
    -588,  -588,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -588,  -588,     0,     0,     0,     0,
       0,  -588,     0,     0,  -588,  -588,     0,  -588,  -588,     0,
    -588,     0,  -588,  -588,  -588,     0,  -588,  -588,  -588,     0,
    -588,  -588,  -588,     0,  -588,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -588,  -588,  -588,     0,     0,     0,
       0,     0,     0,     0,  -588,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,     0,
       0,     0,   155,   156,   157,   233,   234,   235,   236,   162,
     163,   164,     0,     0,     0,     0,     0,   165,   166,   167,
     237,   238,   239,   240,   172,   319,   320,   241,   321,     0,
       0,     0,     0,     0,     0,   322,     0,     0,     0,     0,
       0,     0,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     0,   182,   183,     0,     0,     0,     0,   184,   185,
     186,   187,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   189,   190,     0,     0,     0,     0,   323,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,   201,   202,     0,
       0,     0,     0,     0,     0,   203,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
       0,     0,     0,   155,   156,   157,   233,   234,   235,   236,
     162,   163,   164,     0,     0,     0,     0,     0,   165,   166,
     167,   237,   238,   239,   240,   172,   319,   320,   241,   321,
       0,     0,     0,     0,     0,     0,   322,     0,     0,     0,
       0,     0,     0,   174,   175,   176,   177,   178,   179,   180,
     181,     0,     0,   182,   183,     0,     0,     0,     0,   184,
     185,   186,   187,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   188,   189,   190,     0,     0,     0,     0,
     485,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,     0,   201,   202,
       0,     0,     0,     0,     0,     0,   203,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,     0,     0,     0,   155,   156,   157,   233,   234,   235,
     236,   162,   163,   164,     0,     0,     0,     0,     0,   165,
     166,   167,   237,   238,   239,   240,   172,     0,     0,   241,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   174,   175,   176,   177,   178,   179,
     180,   181,     0,     0,   182,   183,     0,     0,     0,     0,
     184,   185,   186,   187,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,   189,   190,     0,     0,     0,
     242,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,   201,
     202,     0,     0,     0,     0,     0,     0,   203,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,     0,     0,     0,   155,   156,   157,   233,   234,
     235,   236,   162,   163,   164,     0,     0,     0,     0,     0,
     165,   166,   167,   237,   238,   239,   240,   172,     0,     0,
     241,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   174,   175,   176,   177,   178,
     179,   180,   181,     0,     0,   182,   183,     0,     0,     0,
       0,   184,   185,   186,   187,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   188,   189,   190,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,     0,
     201,   202,     0,     0,     0,     0,     0,     0,   203,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,     0,    15,     0,   108,   109,    18,
      19,     0,     0,     0,     0,     0,   110,   111,   112,    23,
      24,    25,    26,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   312,     0,     0,
     119,    53,     0,    54,    55,     0,     0,     0,     0,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,    15,
     120,   108,   109,    18,    19,     0,     0,     0,   313,     0,
     110,   111,   112,    23,    24,    25,    26,     0,     0,   113,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   312,     0,     0,   119,    53,     0,    54,    55,     0,
       0,     0,     0,     0,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,     0,
       0,     0,     0,    15,   120,    16,    17,    18,    19,     0,
       0,     0,   608,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,    46,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,    51,     0,     0,    52,    53,
       0,    54,    55,     0,    56,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,     0,    65,    66,
      67,    15,     0,    16,    17,    18,    19,     0,     0,     0,
       0,     0,    20,    21,    22,    23,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,     0,    28,     0,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,    51,     0,     0,    52,    53,     0,    54,
      55,     0,    56,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,    65,    66,    67,    15,
       0,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,   113,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
      33,   260,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,   211,     0,     0,   119,    53,     0,    54,    55,     0,
     261,     0,   262,   263,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,    65,   264,    67,    15,     0,    16,
      17,    18,    19,     0,     0,     0,     0,     0,    20,    21,
      22,    23,    24,    25,    26,     0,     0,   113,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,   260,
      35,    36,    37,    38,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,   506,     0,     0,     0,     0,     0,   211,
       0,     0,   119,    53,     0,    54,    55,     0,   261,     0,
     262,   263,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,    65,   264,    67,    15,     0,   108,   109,    18,
      19,     0,     0,     0,     0,     0,   110,   111,   112,    23,
      24,    25,    26,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,    33,   260,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,   211,     0,     0,
     119,    53,     0,    54,    55,     0,   719,     0,   262,   263,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
      65,   264,    67,    15,     0,   108,   109,    18,    19,     0,
       0,     0,     0,     0,   110,   111,   112,    23,    24,    25,
      26,     0,     0,   113,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,    33,   260,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,    46,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,   848,
       0,     0,     0,     0,     0,   211,     0,     0,   119,    53,
       0,    54,    55,     0,   719,     0,   262,   263,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,    65,   264,
      67,    15,     0,   108,   109,    18,    19,     0,     0,     0,
       0,     0,   110,   111,   112,    23,    24,    25,    26,     0,
       0,   113,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    32,    33,   260,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,   211,     0,     0,   119,    53,     0,    54,
      55,     0,   261,     0,   262,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,    65,   264,    67,    15,
       0,   108,   109,    18,    19,     0,     0,     0,     0,     0,
     110,   111,   112,    23,    24,    25,    26,     0,     0,   113,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
      33,   260,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,   211,     0,     0,   119,    53,     0,    54,    55,     0,
       0,     0,   262,   263,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,    65,   264,    67,    15,     0,   108,
     109,    18,    19,     0,     0,     0,     0,     0,   110,   111,
     112,    23,    24,    25,    26,     0,     0,   113,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,   260,
      35,    36,    37,    38,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,   211,
       0,     0,   119,    53,     0,    54,    55,     0,   719,     0,
     262,     0,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,    65,   264,    67,    15,     0,   108,   109,    18,
      19,     0,     0,     0,     0,     0,   110,   111,   112,    23,
      24,    25,    26,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,    33,   260,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,   211,     0,     0,
     119,    53,     0,    54,    55,     0,     0,     0,   262,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
      65,   264,    67,    15,     0,    16,    17,    18,    19,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,   113,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,    46,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,   211,     0,     0,   119,    53,
       0,    54,    55,     0,   602,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,    65,   264,
      67,    15,     0,   108,   109,    18,    19,     0,     0,     0,
       0,     0,   110,   111,   112,    23,    24,    25,    26,     0,
       0,   113,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,   211,     0,     0,   119,    53,     0,    54,
      55,     0,   261,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,    65,   264,    67,    15,
       0,   108,   109,    18,    19,     0,     0,     0,     0,     0,
     110,   111,   112,    23,    24,    25,    26,     0,     0,   113,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,   211,     0,     0,   119,    53,     0,    54,    55,     0,
     602,     0,     0,     0,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,    65,   264,    67,    15,     0,   108,
     109,    18,    19,     0,     0,     0,     0,     0,   110,   111,
     112,    23,    24,    25,    26,     0,     0,   113,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,    46,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,     0,     0,     0,     0,     0,   211,
       0,     0,   119,    53,     0,    54,    55,     0,   894,     0,
       0,     0,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,    65,   264,    67,    15,     0,   108,   109,    18,
      19,     0,     0,     0,     0,     0,   110,   111,   112,    23,
      24,    25,    26,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,   211,     0,     0,
     119,    53,     0,    54,    55,     0,   719,     0,     0,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
      65,   264,    67,    15,     0,    16,    17,    18,    19,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,    46,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,     0,     0,     0,   211,     0,     0,   119,    53,
       0,    54,    55,     0,     0,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,    65,    66,
      67,    15,     0,   108,   109,    18,    19,     0,     0,     0,
       0,     0,   110,   111,   112,    23,    24,    25,    26,     0,
       0,   113,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,     0,     0,
       0,     0,     0,   211,     0,     0,   119,    53,     0,    54,
      55,     0,     0,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,    65,   264,    67,    15,
       0,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,   113,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
      33,    34,    35,    36,    37,    38,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,     0,     0,     0,     0,
       0,   211,     0,     0,   119,    53,     0,    54,    55,     0,
       0,     0,     0,     0,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,    65,   264,    67,    15,     0,   108,
     109,    18,    19,     0,     0,     0,     0,     0,   110,   111,
     112,    23,    24,    25,    26,     0,     0,   113,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,   114,
      35,    36,    37,   115,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,     0,     0,   118,
       0,     0,   119,    53,     0,    54,    55,     0,     0,     0,
       0,     0,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,     0,     0,
       0,    15,   120,   108,   109,    18,    19,     0,     0,     0,
       0,     0,   110,   111,   112,    23,    24,    25,    26,     0,
       0,   113,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,   225,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   226,     0,     0,    52,    53,     0,    54,
      55,     0,    56,     0,     0,     0,    57,     0,    58,    59,
      60,     0,    61,    62,    63,     0,    64,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,     0,    15,   120,   108,   109,    18,
      19,     0,     0,     0,     0,     0,   110,   111,   112,    23,
      24,    25,    26,     0,     0,   113,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,    33,    34,    35,    36,
      37,    38,    39,     0,    40,    41,    42,     0,     0,    43,
       0,     0,    44,    45,     0,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   312,     0,     0,
     398,    53,     0,    54,    55,     0,   399,     0,     0,     0,
      57,     0,    58,    59,    60,     0,    61,    62,    63,     0,
      64,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,     0,     0,     0,     0,    15,
     120,   108,   109,    18,    19,     0,     0,     0,     0,     0,
     110,   111,   112,    23,    24,    25,    26,     0,     0,   113,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
      33,   114,    35,    36,    37,   115,    39,     0,    40,    41,
      42,     0,     0,    43,     0,     0,    44,    45,     0,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   118,     0,     0,   119,    53,     0,    54,    55,     0,
       0,     0,     0,     0,    57,     0,    58,    59,    60,     0,
      61,    62,    63,     0,    64,     0,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,     0,
       0,     0,     0,    15,   120,   108,   109,    18,    19,     0,
       0,     0,     0,     0,   110,   111,   112,    23,    24,    25,
      26,     0,     0,   113,     0,     0,     0,     0,     0,     0,
       0,     0,    31,    32,    33,    34,    35,    36,    37,    38,
      39,     0,    40,    41,    42,     0,     0,    43,     0,     0,
      44,    45,     0,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   312,     0,     0,   398,    53,
       0,    54,    55,     0,     0,     0,     0,     0,    57,     0,
      58,    59,    60,     0,    61,    62,    63,     0,    64,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,     0,     0,     0,     0,     0,    15,   120,   108,
     109,    18,    19,     0,     0,     0,     0,     0,   110,   111,
     112,    23,    24,    25,    26,     0,     0,   113,     0,     0,
       0,     0,     0,     0,     0,     0,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     0,    40,    41,    42,     0,
       0,    43,     0,     0,    44,    45,     0,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   961,
       0,     0,   119,    53,     0,    54,    55,     0,     0,     0,
       0,     0,    57,     0,    58,    59,    60,     0,    61,    62,
      63,     0,    64,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,     0,     0,
       0,    15,   120,   108,   109,    18,    19,     0,     0,     0,
       0,     0,   110,   111,   112,    23,    24,    25,    26,     0,
       0,   113,     0,     0,     0,     0,     0,     0,     0,     0,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     0,
      40,    41,    42,     0,     0,    43,     0,     0,    44,    45,
       0,   225,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   984,     0,     0,   119,    53,     0,    54,
      55,     0,     0,   677,   648,     0,    57,   678,    58,    59,
      60,     0,    61,    62,    63,     0,    64,     0,     0,     0,
       0,     0,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     0,   182,   183,     0,     0,   120,     0,   184,   185,
     186,   187,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   189,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,   201,   202,   662,
     657,     0,     0,   663,     0,   203,   275,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   174,   175,
     176,   177,   178,   179,   180,   181,     0,     0,   182,   183,
       0,     0,     0,     0,   184,   185,   186,   187,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,   189,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,     0,   201,   202,   694,   648,     0,     0,   695,
       0,   203,   275,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   174,   175,   176,   177,   178,   179,
     180,   181,     0,     0,   182,   183,     0,     0,     0,     0,
     184,   185,   186,   187,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,   189,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,   201,
     202,   697,   657,     0,     0,   698,     0,   203,   275,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     174,   175,   176,   177,   178,   179,   180,   181,     0,     0,
     182,   183,     0,     0,     0,     0,   184,   185,   186,   187,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,   189,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,     0,   201,   202,   704,   648,     0,
       0,   705,     0,   203,   275,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   174,   175,   176,   177,
     178,   179,   180,   181,     0,     0,   182,   183,     0,     0,
       0,     0,   184,   185,   186,   187,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   188,   189,   190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       0,   201,   202,   707,   657,     0,     0,   708,     0,   203,
     275,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     0,   182,   183,     0,     0,     0,     0,   184,   185,
     186,   187,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   189,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,   201,   202,   742,
     648,     0,     0,   743,     0,   203,   275,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   174,   175,
     176,   177,   178,   179,   180,   181,     0,     0,   182,   183,
       0,     0,     0,     0,   184,   185,   186,   187,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,   189,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,     0,   201,   202,   745,   657,     0,     0,   746,
       0,   203,   275,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   174,   175,   176,   177,   178,   179,
     180,   181,     0,     0,   182,   183,     0,     0,     0,     0,
     184,   185,   186,   187,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,   189,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,   201,
     202,   899,   648,     0,     0,   900,     0,   203,   275,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     174,   175,   176,   177,   178,   179,   180,   181,     0,     0,
     182,   183,     0,     0,     0,     0,   184,   185,   186,   187,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,   189,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,     0,   201,   202,   902,   657,     0,
       0,   903,     0,   203,   275,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   174,   175,   176,   177,
     178,   179,   180,   181,     0,     0,   182,   183,     0,     0,
       0,     0,   184,   185,   186,   187,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   188,   189,   190,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       0,   201,   202,  1042,   648,     0,     0,  1043,     0,   203,
     275,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   174,   175,   176,   177,   178,   179,   180,   181,
       0,     0,   182,   183,     0,     0,     0,     0,   184,   185,
     186,   187,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   189,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,     0,   201,   202,  1054,
     648,     0,     0,  1055,     0,   203,   275,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   174,   175,
     176,   177,   178,   179,   180,   181,     0,     0,   182,   183,
       0,     0,     0,     0,   184,   185,   186,   187,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,   189,
     190,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,     0,   201,   202,  1057,   657,     0,     0,  1058,
       0,   203,   275,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   174,   175,   176,   177,   178,   179,
     180,   181,     0,     0,   182,   183,     0,     0,     0,     0,
     184,   185,   186,   187,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,   189,   190,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,     0,   201,
     202,   662,   657,     0,     0,   663,     0,   203,   275,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     174,   175,   176,   177,   178,   179,   180,   181,     0,     0,
     182,   183,     0,     0,     0,     0,   184,   185,   186,   187,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,   189,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   879,     0,     0,     0,
       0,     0,     0,     0,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,     0,   201,   202,     0,     0,     0,
       0,     0,     0,   203,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,     0,     0,     0,     0,
     414,   415,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   417,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   418,     0,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,     0,     0,
       0,     0,   414,   415,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   417,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   418,     0,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428,     0,     0,
       0,     0,     0,     0,     0,     0,  -277,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,     0,
       0,     0,     0,   414,   415,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   417,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   418,     0,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,     0,
       0,     0,     0,     0,     0,     0,     0,  -278,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
       0,     0,     0,     0,   414,   415,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   417,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   418,     0,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   428,
       0,     0,     0,     0,     0,     0,     0,     0,  -279,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,     0,     0,     0,     0,   414,   415,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   417,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   418,
       0,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,     0,     0,     0,     0,     0,     0,     0,     0,  -280,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,     0,     0,     0,     0,   414,   415,     0,     0,
       0,   416,     0,     0,     0,     0,     0,     0,     0,   417,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     418,     0,   419,   420,   421,   422,   423,   424,   425,   426,
     427,   428,   402,   403,   404,   405,   406,   407,   408,   409,
     410,   411,   412,   413,     0,     0,     0,     0,   414,   415,
       0,     0,     0,   498,     0,     0,     0,     0,     0,     0,
       0,   417,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   418,     0,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   402,   403,   404,   405,   406,   407,
     408,   409,   410,   411,   412,   413,     0,     0,     0,     0,
     414,   415,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   417,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   418,     0,   419,   420,   421,   422,
     423,   424,   425,   426,   427,   428,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,  -613,  -613,     0,     0,
       0,     0,   414,   415,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   417,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   419,   420,
     421,   422,   423,   424,   425,   426,   427,   428
};

static const yytype_int16 yycheck[] =
{
       2,    89,    16,    17,    27,    69,    20,    87,    88,    66,
       2,    28,     4,     5,     6,    22,     7,     9,    10,    21,
      14,    13,   222,    15,    16,    17,   284,   313,    20,   479,
      10,   271,    82,    52,    28,    15,   488,   377,   401,   306,
      54,    55,     2,   310,     4,     4,    16,    17,    56,     7,
      20,   593,    54,    55,    16,    17,    14,   118,    20,    75,
      52,   501,    26,   590,    56,   505,   431,    58,   688,   318,
      28,   330,    74,    75,    66,   756,   505,    91,   429,   699,
     944,    15,   433,    25,   295,   436,    60,    61,    62,    63,
      82,   456,    54,    55,    21,    22,    25,    75,   105,    25,
      58,   544,     5,     6,    57,    51,   457,   536,   473,   111,
      13,    25,   269,    90,   271,    16,    17,   482,    16,    20,
     369,   472,    79,   474,    29,   117,    26,   119,    25,   665,
     666,   969,   483,   783,    90,    69,    25,    25,   218,   372,
      25,     0,    90,    92,   122,   802,    90,    90,   305,   229,
     783,   808,   590,    56,   121,   101,   102,   103,    74,    75,
     393,   105,    90,    16,    17,   608,    90,    20,   121,   126,
     147,   522,   121,  1037,   138,   142,    16,   138,   105,    82,
     144,   546,   128,   331,   111,   112,   334,   398,   336,    52,
     338,   147,   340,   142,    27,    55,   547,   213,   214,   147,
     142,    54,   129,   147,   147,   121,   122,  1045,   113,   289,
     121,   213,   214,   142,    90,   144,   142,   115,   210,   147,
     118,   119,   749,   147,    90,   458,   441,   442,   142,   105,
     144,   223,   224,   297,   761,   315,   214,    92,   138,   105,
     144,   305,   306,   223,   224,   142,   310,    90,   146,    28,
     148,   242,   590,   142,   142,   593,   119,   142,   544,   142,
     386,   275,   388,   313,   140,   279,   121,   269,   949,   271,
     510,   147,    90,   275,   140,   115,   295,   813,   118,   119,
      90,   147,   115,   275,   242,   118,   119,   279,   728,   729,
      51,   283,   284,    90,    55,   287,   555,   213,   214,   548,
     729,   103,   294,   295,   147,   275,   146,   121,   148,   279,
     302,   749,    18,   146,    20,   148,   966,   279,   252,   969,
     940,   313,   608,   761,   687,    92,   128,   869,   115,   147,
     963,   118,   119,   966,   294,   101,   969,   147,   971,   396,
      92,   401,   302,    92,   401,    58,    59,   318,   791,   323,
     147,   144,   509,   510,   121,   347,   348,   349,   350,   351,
     352,   353,   354,   297,   804,   131,   132,   133,   348,   349,
     350,   351,   121,   375,    60,   377,    55,    63,   279,   398,
     372,   441,   442,   125,   441,   442,  1019,   347,   347,   121,
     840,   399,   352,   142,   455,  1045,    61,    92,   369,    64,
      65,   393,   318,    25,   396,   553,   398,   399,    92,   401,
     313,   749,  1045,    90,  1047,    55,  1049,   431,  1051,    37,
      38,   107,   275,   761,   287,   863,   279,   767,   105,   431,
     115,   796,   295,   118,   119,   873,    92,   121,  1071,   431,
      92,   142,   456,   676,   795,   783,   797,    20,   605,   441,
     442,   116,   117,   369,   456,    62,    57,    64,    65,   473,
     718,   431,   464,   140,   456,   121,   458,   459,   482,   121,
     147,   473,   739,    58,    59,   433,   499,   469,   436,   142,
     482,   473,   722,    17,    18,   477,   456,   501,   940,    92,
     482,   505,   542,   138,   544,   487,   399,    92,   655,   457,
      92,   518,   942,   473,    92,   791,   433,   509,   510,   116,
     117,   101,   482,   942,   714,   145,   474,   519,   121,   533,
     661,    26,   536,   664,   518,   483,   121,   519,   966,   121,
     457,   869,   546,   121,    92,   398,   528,   121,   618,   501,
     798,   682,   215,   396,   546,   885,   886,   474,   401,   222,
     542,   784,   544,    92,   546,   141,   483,   714,   608,   519,
     518,   139,   554,   121,   522,   722,  1004,    92,   528,     9,
      10,   533,   881,   882,   508,    15,   546,   548,   811,   121,
     122,    55,   121,   142,   799,    90,   259,    90,   580,   547,
     805,   806,   101,   101,   121,   522,   121,   855,   121,   601,
     105,    92,   105,   142,   142,   576,   469,   599,   121,   849,
     580,  1049,    51,   636,   477,    62,   608,    64,    65,    51,
     547,   142,   593,   856,   487,   596,   142,   142,   966,   599,
     121,   969,   548,   138,    51,   140,   142,   140,   491,   542,
     142,   544,   147,    51,   147,   652,   772,   773,   774,    26,
     776,   142,   778,   655,   661,    16,    15,   664,     2,   661,
       4,    99,   664,   665,   666,     9,    10,  1032,    13,   116,
     117,    15,    16,    17,   347,   739,    20,   117,  1018,   121,
     682,    92,  1033,   675,   676,   687,   688,   121,   361,   922,
     692,   554,   849,   710,   685,   675,   911,   699,    16,    63,
      15,    92,   139,    15,   145,   608,   379,  1045,    52,   145,
     121,   142,   142,    90,   728,   729,   710,   709,   142,    15,
     722,   809,    66,   142,    44,   652,   926,   685,   105,   709,
     121,   142,   932,   793,   661,   121,   793,   664,   141,   799,
     141,   791,   799,   800,    15,   805,   806,   141,   805,   806,
      18,   142,   710,   680,   115,   682,   141,   118,   119,    90,
     139,   138,    15,   140,   583,   767,   728,   144,   587,    16,
     147,   139,   141,   117,   105,   119,   139,   142,    44,    57,
    1038,   142,   796,   223,   224,   146,   142,   148,   142,   142,
     804,   142,   784,    44,   796,    15,    37,    38,    93,   791,
     792,   793,    90,    14,   796,   478,   479,   799,   800,   140,
      15,   813,   783,   805,   806,    15,   147,   105,   145,   811,
     812,   823,    15,   142,   826,   142,   796,   953,   954,   955,
     956,   142,   792,   825,   687,   142,   828,    61,   142,   797,
      64,    65,   804,   283,   284,   837,   838,   849,   828,   141,
      15,   911,   140,   845,   911,   528,   299,   139,    15,   147,
     303,    15,   535,    15,   856,   857,   210,    90,   115,   139,
     797,   118,   119,   142,   115,    90,   126,   118,   119,   223,
     224,   142,   105,   885,   886,   583,   126,    55,   791,   860,
     105,   883,   116,   117,   139,    15,   888,    55,   869,   146,
     871,   148,    15,    90,   875,   146,   986,   148,   348,   349,
     350,   351,   142,   353,   354,  1041,   142,   140,   105,   911,
     142,   144,   519,   142,   147,   140,    57,   144,   942,   921,
     922,   275,   147,   925,   142,   279,   142,   929,   940,   283,
     284,   144,   141,   287,   441,   442,   142,    13,     6,   812,
     294,   295,    51,   140,    53,    54,    55,    56,   302,  1035,
     147,   783,   825,  1037,   783,   810,  1034,    63,    64,    65,
      69,   254,    26,     7,   837,   838,   999,   948,   475,   476,
     883,   583,   845,   966,   115,   888,    -1,   118,   119,    26,
     963,    -1,   123,    -1,   857,    -1,    -1,   989,   969,   991,
     971,   674,   994,   347,   348,   349,   350,   351,   352,   353,
     354,    -1,    -1,    -1,    90,    -1,  1018,   148,  1032,   459,
     116,   117,   925,    -1,    -1,    -1,   523,    -1,   372,   105,
    1032,    90,  1034,  1035,    -1,  1006,    90,    -1,  1009,    -1,
    1032,   714,    -1,   142,   890,   891,   105,    -1,    -1,   393,
      -1,   105,   396,    90,   398,    -1,    -1,   401,   921,    -1,
      -1,    -1,  1032,   506,   140,    -1,   929,    -1,   105,  1040,
     513,   147,    -1,    -1,  1045,  1033,  1047,    26,    -1,    -1,
    1051,   140,   525,    -1,   138,   783,   140,   431,   147,    90,
     144,    -1,    -1,   147,    -1,    -1,   769,   441,   442,    -1,
    1071,   138,    -1,   140,   105,    -1,  1033,   144,    90,    90,
     147,    -1,   456,    -1,   458,   459,    -1,    -1,    -1,    -1,
     966,    -1,    -1,   105,   105,   469,   989,    -1,   991,   473,
      -1,   994,    -1,   477,   577,   578,    90,    -1,   482,   140,
      -1,    90,   815,   487,   963,    -1,   147,   966,    -1,    -1,
     969,   105,   971,    -1,    -1,    -1,   105,    -1,   140,   140,
      26,    63,    64,    65,   607,   147,   147,   840,    -1,    51,
      -1,    53,    54,    55,    56,   519,  1022,  1023,  1024,    -1,
    1026,  1027,    -1,    -1,   528,    -1,   140,    69,    -1,   138,
      -1,   140,    -1,   147,    -1,   144,    -1,    -1,   147,    -1,
    1019,    -1,   546,    -1,   115,     9,    10,   118,   119,    -1,
     554,    15,    16,    17,   116,   117,    20,    -1,    -1,  1065,
    1066,  1067,  1068,    -1,    90,    -1,  1045,    -1,  1047,  1075,
    1049,    -1,  1051,    -1,    -1,   675,   580,   148,    -1,   105,
      -1,   684,    -1,    47,    48,    49,    50,    63,    64,    65,
      54,    55,  1071,   926,   101,   599,    -1,    -1,    -1,   932,
     142,    -1,    66,    67,    -1,   963,    -1,    -1,   966,   709,
      -1,   969,   138,   971,   140,    63,    64,    65,   144,    -1,
      -1,   147,   129,   130,   131,   132,   133,    51,    -1,    53,
      54,    55,    56,    -1,   115,   738,    -1,   118,   119,    -1,
     116,   117,   799,   800,    -1,    69,    -1,    -1,   805,   806,
      63,    64,    65,   117,   757,    63,    64,    65,    63,    64,
      65,  1019,    63,    64,    65,   146,    -1,   148,   116,   117,
      94,   675,   676,    -1,   831,   832,   100,   834,   835,    -1,
      51,    -1,    53,    54,    55,    56,    -1,  1045,    -1,  1047,
      -1,  1049,    51,  1051,    53,    54,    55,    56,    69,    -1,
      -1,    -1,    -1,   116,   117,   709,    88,    89,   116,   117,
      69,   116,   117,  1071,    -1,   116,   117,    -1,    -1,   101,
      -1,    -1,   115,    94,    83,   118,   119,    -1,   828,    -1,
     101,   102,   103,    -1,    -1,    94,    40,    41,    42,    43,
      44,   100,   101,   102,   103,   848,   128,   129,   130,   131,
     132,   133,   145,   146,   911,   148,    -1,   128,    -1,   223,
     224,   864,   121,     2,    -1,     4,     5,     6,    -1,   128,
      -1,    -1,   131,    -1,    13,    -1,    -1,   934,    -1,   115,
     784,    -1,   118,   119,    -1,   144,    -1,    -1,   792,   793,
      -1,    -1,   796,    -1,    -1,   799,   800,   261,   262,   263,
     264,   805,   806,    -1,    -1,    -1,   142,   811,   812,    -1,
     146,   275,   148,    52,    -1,   279,    -1,    56,    -1,   283,
     284,   825,    -1,    -1,   828,    -1,    51,    -1,    53,    54,
      55,    56,    -1,   837,   838,   115,    -1,    -1,   118,   119,
      -1,   845,    -1,    82,    69,    51,    -1,    53,    54,    55,
      56,    -1,   856,   857,    88,    89,    -1,    -1,    83,    -1,
      -1,    -1,    -1,    69,    -1,    -1,   146,   101,   148,    94,
      -1,    -1,    -1,    -1,    -1,   100,   101,   102,   103,    -1,
     119,    -1,    -1,    -1,   348,   349,   350,   351,    94,   353,
     354,    -1,    -1,    -1,   100,   129,   130,   131,   132,   133,
      -1,    -1,    -1,   128,    -1,    -1,   131,   911,    51,   373,
      53,    54,    55,    56,    -1,    -1,    -1,   921,   922,   144,
     384,    -1,    -1,    -1,    -1,   929,    69,    -1,    -1,    -1,
      -1,    -1,   396,    -1,    -1,    -1,    -1,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,    -1,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,    -1,    -1,   431,    -1,    -1,
      51,   210,    53,    54,    55,    56,    -1,   441,   442,    -1,
      -1,    -1,    -1,    -1,    -1,   989,    -1,   991,    69,    -1,
     994,    -1,   456,    -1,    -1,   459,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    53,    54,    55,    56,   471,    -1,   473,
      -1,   475,   476,    94,    -1,    -1,    -1,    -1,   482,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   491,  1032,    -1,
     494,    -1,    -1,    -1,   498,    -1,    -1,   501,    -1,   503,
      -1,   505,   506,    -1,    94,    88,    89,    -1,   287,    -1,
     100,   101,   102,   103,    -1,   294,   295,    -1,   101,   523,
      -1,    -1,    -1,   302,    -1,    -1,    -1,    -1,    -1,   533,
      -1,    -1,   536,    -1,   313,    -1,    -1,    -1,   128,    -1,
      -1,   131,   546,   126,   127,   128,   129,   130,   131,   132,
     133,    -1,    -1,    -1,   144,    -1,    -1,    -1,    -1,   563,
     564,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   347,    -1,
      -1,    -1,    -1,   352,    -1,    -1,   580,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     0,    -1,   372,    -1,   599,    -1,    51,   602,    53,
      54,    55,    56,    -1,    13,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,   393,    69,    -1,    26,    27,   398,
     399,    -1,   401,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      94,    -1,    -1,    -1,    -1,    -1,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   441,   442,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   675,    -1,    -1,   128,    -1,    -1,   131,    -1,   458,
      -1,    90,    -1,   687,    -1,    -1,   690,   691,   142,    -1,
     469,     2,    -1,     4,     5,     6,   105,    -1,   477,    -1,
      -1,    -1,    13,    -1,    -1,   709,   115,    -1,   487,   118,
     119,    -1,    -1,    -1,    -1,   719,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   728,   729,    -1,    -1,    -1,   138,
     139,    -1,    -1,    -1,    -1,   144,   145,   146,   147,   148,
     519,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,   528,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   542,    -1,   544,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    -1,   554,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   788,    -1,    -1,    -1,    -1,   793,
     794,    -1,   796,    -1,    -1,   799,   800,    -1,    -1,    -1,
     804,   805,   806,    -1,    -1,    -1,    -1,    -1,   119,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,   828,    -1,    -1,   831,   832,   608,
     834,   835,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     844,    -1,    -1,    -1,   848,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     2,    94,     4,     5,
       6,   865,   866,   100,   101,   102,   103,    13,    -1,    -1,
      -1,    -1,    -1,    -1,   878,   879,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
     894,   128,    -1,    -1,   131,    -1,    -1,   676,    -1,   210,
     904,   905,    -1,    -1,    -1,    -1,    52,   911,    -1,    -1,
      56,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    88,    89,    -1,
     934,    -1,    -1,    -1,    -1,    -1,    82,    -1,   942,    -1,
     101,    -1,    -1,    -1,    51,    -1,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   122,    69,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   119,    -1,    -1,   287,    -1,    85,    -1,
      -1,   142,    -1,   294,   295,    -1,    -1,    94,    -1,    -1,
      -1,   302,    -1,   100,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,   313,    -1,    51,   784,    53,    54,    55,    56,
      -1,    -1,   791,   792,   793,    -1,    -1,    -1,    -1,    -1,
     799,   128,    69,    -1,   131,    -1,   805,   806,  1032,    -1,
      -1,    -1,   811,   812,    -1,    -1,   347,    -1,    85,    -1,
      -1,   352,    -1,    -1,    -1,    -1,   825,    94,    -1,    -1,
      -1,    -1,    -1,   100,   101,   102,   103,    -1,   837,   838,
      -1,   372,    -1,    -1,   210,    -1,   845,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   856,   857,    -1,
      -1,   128,   393,    -1,   131,    -1,    -1,   398,   399,    -1,
     401,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   883,    -1,    -1,    -1,    -1,   888,
      51,    -1,    53,    54,    55,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    -1,
     441,   442,   911,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   287,   921,   922,    -1,    -1,   925,   458,   294,   295,
     929,    -1,    -1,    94,    -1,    -1,   302,    -1,   469,   100,
     101,   102,   103,    -1,    -1,    -1,   477,   313,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   487,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,
     131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   347,    -1,    -1,    -1,    -1,   352,    -1,   519,    -1,
     989,    -1,   991,    -1,    -1,   994,    -1,   528,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   372,    -1,    -1,    -1,
      -1,   542,    -1,   544,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   554,    -1,    -1,    -1,   393,    -1,    -1,
      -1,    -1,   398,   399,    -1,   401,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     2,    -1,     4,     5,     6,     7,    -1,    -1,    51,
      52,    -1,    13,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   441,   442,   608,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    80,    81,
      -1,    -1,   458,    -1,    86,    87,    88,    89,    -1,    -1,
      -1,    52,    -1,   469,    -1,    56,    -1,    -1,   100,   101,
     102,   477,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   487,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    82,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,    -1,   135,   136,   676,    -1,    -1,    -1,    -1,
      -1,   143,   144,   519,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   528,    44,    -1,    -1,    -1,    -1,   119,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   542,    -1,   544,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   554,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     2,    -1,     4,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   122,   608,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   784,    -1,    -1,    -1,    -1,    -1,   210,
     791,   792,   793,    -1,    -1,    -1,    52,    -1,   799,    -1,
      -1,    -1,    -1,    -1,   805,   806,    -1,    -1,    -1,    -1,
     811,   812,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   825,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   837,   838,    -1,    -1,
     676,    -1,    -1,    -1,   845,    -1,    -1,     2,    -1,     4,
      -1,    -1,    -1,    -1,    -1,   856,   857,    -1,    -1,    -1,
      -1,    -1,    -1,   119,    -1,    -1,   287,    -1,    -1,    -1,
      -1,    -1,    -1,   294,   295,    -1,    -1,    -1,    -1,    -1,
      -1,   302,   883,    -1,    -1,    -1,    -1,   888,    -1,    -1,
      -1,    -1,   313,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     911,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     921,   922,    -1,    -1,   925,    -1,   347,    -1,   929,    -1,
      -1,   352,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   784,    -1,
      -1,   372,    -1,    -1,   210,   791,   792,   793,    -1,    -1,
      -1,    -1,    -1,   799,   119,    -1,    -1,    -1,    -1,   805,
     806,    -1,   393,    -1,    -1,   811,   812,   398,   399,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   989,   825,
     991,    -1,    -1,   994,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   837,   838,    -1,    -1,    -1,    -1,    -1,    -1,   845,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     856,   857,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   287,    -1,    -1,    -1,    -1,    -1,   458,   294,   295,
      -1,    -1,    -1,    -1,    -1,    -1,   302,   883,   469,    -1,
      -1,    -1,   888,    -1,    -1,   210,   477,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   487,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   911,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   921,   922,    -1,    -1,   925,
      -1,   347,    -1,   929,    -1,    -1,   352,    -1,   519,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   528,    -1,    72,
      73,    74,    75,    76,    77,    78,   372,    80,    81,    -1,
      -1,   542,    -1,   544,    -1,    88,    89,    -1,    -1,    -1,
      -1,    -1,   287,   554,    -1,    -1,    -1,   393,   101,   294,
     295,    -1,   398,    -1,    -1,   401,    -1,   302,    -1,    -1,
      -1,    -1,    -1,   989,    -1,   991,    -1,    -1,   994,    -1,
      -1,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   441,   442,   608,    -1,    -1,
      -1,    -1,   347,    -1,    -1,    -1,    -1,   352,    -1,    -1,
      -1,    -1,   458,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   469,    -1,    -1,    -1,   372,    -1,    -1,
      -1,   477,    -1,    -1,    72,    73,    74,    75,    76,    77,
      -1,   487,    80,    81,    -1,    -1,    -1,    -1,   393,    -1,
      88,    89,    -1,   398,    -1,    -1,   401,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,   676,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   519,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   528,    -1,    -1,    -1,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   441,   442,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   554,    -1,
      -1,    -1,    -1,   458,    51,    52,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,   469,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   477,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,   487,    80,    81,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,   101,   102,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   784,   519,    -1,    -1,    -1,    -1,    -1,
     791,   792,    -1,   528,    -1,    -1,    -1,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,    -1,   135,   136,
     811,   812,    -1,    -1,    -1,    -1,   143,   144,    -1,   554,
      -1,    -1,    -1,    -1,   825,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,   837,   838,    -1,    -1,
     676,    -1,    -1,    -1,   845,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   856,   857,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   883,    -1,    -1,    -1,   101,   888,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,    -1,
     921,   922,    -1,    -1,   925,    -1,    -1,    -1,   929,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   676,    -1,    -1,    -1,    -1,    -1,    -1,   784,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   792,   793,    -1,    -1,
      -1,    -1,    -1,   799,    -1,    -1,    -1,    -1,    -1,   805,
     806,    -1,    -1,    -1,    -1,   811,   812,    -1,    72,    73,
      74,    75,    76,    77,    -1,    -1,    80,    81,   989,   825,
     991,    -1,    -1,   994,    88,    89,    -1,    -1,    -1,    -1,
      -1,   837,   838,    -1,    -1,    -1,    -1,   101,    -1,   845,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     856,   857,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   784,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   792,   793,    -1,
      -1,    -1,    -1,    -1,   799,    -1,    -1,    -1,    -1,    -1,
     805,   806,    -1,    -1,    -1,   911,   811,   812,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   921,   922,    -1,    -1,   925,
     825,    -1,    -1,   929,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   837,   838,    -1,    -1,    -1,    -1,    -1,    -1,
     845,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   856,   857,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   989,    -1,   991,    -1,    -1,   994,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   911,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   921,   922,    -1,    -1,
      -1,    -1,    -1,    -1,   929,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     0,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,   989,    39,   991,    -1,    -1,   994,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    97,    98,    -1,   100,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,     0,
     114,   115,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    13,    14,    15,    16,    17,    18,    -1,    20,
     134,   135,   136,    -1,    -1,    -1,    27,    28,    29,    -1,
      -1,    -1,   146,    -1,   148,    -1,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    88,    89,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,    -1,
     101,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   113,    -1,   115,    -1,    -1,   118,   119,    -1,
      -1,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,    -1,    -1,     0,    -1,    -1,   139,   140,
     141,   142,    -1,    -1,   145,   146,   147,   148,    13,    14,
      15,    16,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    88,    89,    90,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    99,    -1,   101,    -1,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     115,    -1,    -1,   118,   119,    -1,    -1,   122,    -1,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,    -1,
      -1,     0,    -1,   138,   139,   140,   141,   142,    -1,   144,
     145,   146,   147,   148,    13,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    88,
      89,    90,    -1,    92,    93,    -1,    -1,    -1,    -1,    -1,
      99,    -1,   101,    -1,    -1,    -1,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,    -1,   118,
     119,    -1,   121,   122,    -1,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,    -1,    -1,     0,    -1,    -1,
     139,   140,   141,   142,    -1,    -1,   145,   146,   147,   148,
      13,    14,    15,    16,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    88,    89,    90,    -1,    -1,
      93,    -1,    -1,    -1,    -1,    -1,    99,    -1,   101,    -1,
      -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   115,    -1,    -1,   118,   119,    -1,    -1,   122,
      -1,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,    -1,    -1,     0,    -1,   138,   139,   140,   141,   142,
      -1,   144,   145,   146,   147,   148,    13,    14,    15,    16,
      17,    18,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    88,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    99,    -1,   101,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,
      -1,   118,   119,    -1,    -1,   122,    -1,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,    -1,    -1,     0,
      -1,    -1,   139,   140,   141,   142,    -1,   144,   145,   146,
     147,   148,    13,    14,    15,    -1,    17,    18,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    -1,    -1,    88,    89,    90,
      -1,    92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     101,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   115,    -1,    -1,   118,   119,    -1,
     121,   122,    -1,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,    -1,    -1,     0,    -1,   138,   139,   140,
      -1,   142,    -1,    -1,   145,   146,   147,   148,    13,    14,
      15,    -1,    17,    18,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    88,    89,    90,    -1,    92,    93,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     115,    -1,    -1,   118,   119,    -1,   121,   122,    -1,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,    -1,
      -1,     0,    -1,   138,   139,   140,    -1,   142,    -1,    -1,
     145,   146,   147,   148,    13,    14,    15,    -1,    17,    18,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    88,
      89,    90,    -1,    92,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   101,    -1,    -1,    -1,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   115,    -1,    -1,   118,
     119,    -1,   121,   122,    -1,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,    -1,    -1,     0,    -1,    -1,
     139,   140,    -1,   142,    -1,    -1,   145,   146,   147,   148,
      13,    14,    15,    -1,    17,    18,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    88,    89,    90,    -1,    92,
      93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   115,    -1,    -1,   118,   119,    -1,   121,   122,
      -1,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,    -1,   139,   140,    -1,   142,
      -1,    -1,   145,   146,   147,   148,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    -1,    -1,    18,    19,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    71,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,
      95,    -1,    97,    98,    -1,   100,    -1,    -1,    -1,   104,
      -1,   106,   107,   108,    -1,   110,   111,   112,    -1,   114,
     115,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   134,
     135,   136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   146,     1,   148,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    15,    -1,    17,    18,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,
      -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,
      -1,   100,    -1,    -1,    -1,   104,    -1,   106,   107,   108,
      -1,   110,   111,   112,    -1,   114,   115,    -1,    -1,   118,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   134,   135,   136,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   146,     1,   148,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    15,    -1,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      -1,    94,    95,    -1,    97,    98,    -1,   100,    -1,    -1,
      -1,   104,    -1,   106,   107,   108,    -1,   110,   111,   112,
      -1,   114,   115,    -1,    -1,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   134,   135,   136,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   146,     1,   148,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    -1,    -1,    15,    -1,
      -1,    18,    19,    -1,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    -1,    91,    -1,    -1,    94,    95,    -1,
      97,    98,    -1,   100,    -1,    -1,    -1,   104,    -1,   106,
     107,   108,    -1,   110,   111,   112,    -1,   114,   115,    -1,
      -1,   118,   119,     1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,   134,   135,   136,
      -1,    19,    -1,    21,    22,    23,    24,    -1,    -1,   146,
      -1,   148,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,
      98,    -1,   100,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,   115,    -1,    -1,
     118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   134,   135,   136,    -1,
      -1,   139,    -1,    -1,    -1,    -1,    -1,    -1,   146,     1,
     148,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    14,    15,    -1,    -1,    -1,    19,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    94,    95,    -1,    97,    98,    -1,   100,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,   115,    -1,    -1,   118,   119,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,   134,   135,   136,    -1,    19,    -1,    21,    22,
      23,    24,    -1,    -1,   146,    -1,   148,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      -1,    94,    95,    -1,    97,    98,    -1,   100,    -1,    -1,
      -1,   104,    -1,   106,   107,   108,    -1,   110,   111,   112,
      -1,   114,   115,    -1,    -1,   118,   119,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,   134,   135,   136,    -1,    19,    -1,    21,    22,    23,
      24,    -1,   145,   146,    -1,   148,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    97,    98,    -1,   100,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,    -1,    -1,   118,   119,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    -1,
     134,   135,   136,    -1,    19,    -1,    21,    22,    23,    24,
      -1,   145,   146,    -1,   148,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,
      -1,    66,    67,    -1,    69,    70,    71,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,
      95,    -1,    97,    98,    -1,   100,    -1,    -1,    -1,   104,
      -1,   106,   107,   108,    -1,   110,   111,   112,    -1,   114,
     115,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   134,
     135,   136,    -1,    -1,   139,    -1,    -1,    -1,    -1,    -1,
      -1,   146,     1,   148,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    15,    -1,    -1,    -1,
      19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,    58,
      59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,
      69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,
      -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,
      -1,   100,    -1,    -1,    -1,   104,    -1,   106,   107,   108,
      -1,   110,   111,   112,    -1,   114,   115,    -1,    -1,   118,
     119,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,   134,   135,   136,    -1,    19,
      -1,    21,    22,    23,    24,    -1,    -1,   146,    -1,   148,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,    -1,
     100,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,   115,    -1,    -1,   118,   119,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,   134,   135,   136,    -1,    19,    -1,
      21,    22,    23,    24,    -1,    -1,   146,    -1,   148,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    58,    59,    60,
      -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,
      71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,
      91,    -1,    -1,    94,    95,    -1,    97,    98,    -1,   100,
      -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,
     111,   112,    -1,   114,   115,    -1,    -1,   118,   119,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,   134,   135,   136,    -1,    19,    -1,    21,
      22,    23,    24,    -1,    -1,   146,    -1,   148,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    94,    95,    -1,    97,    98,    -1,    -1,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,   115,    -1,    -1,   118,   119,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,   134,   135,   136,    -1,    19,    -1,    21,    22,
      23,    24,    -1,    -1,   146,    -1,   148,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    58,    59,    60,    -1,    -1,
      63,    -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,
      -1,    94,    95,    -1,    97,    98,    -1,    -1,    -1,    -1,
      -1,   104,    -1,   106,   107,   108,    -1,   110,   111,   112,
      -1,   114,   115,    -1,    -1,   118,   119,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,   134,   135,   136,    -1,    19,    -1,    21,    22,    23,
      24,    -1,    -1,   146,    -1,   148,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    97,    98,    -1,    -1,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,   115,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     134,   135,   136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    -1,   135,   136,    -1,
      -1,    -1,    -1,    -1,    -1,   143,   144,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    -1,    21,    22,    23,    24,    -1,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,    95,
      -1,    97,    98,    -1,   100,    -1,   102,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   134,   135,
     136,    -1,   138,    -1,    -1,    -1,    -1,    -1,   144,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    22,    23,
      24,    -1,    26,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    97,    98,    -1,   100,    -1,   102,   103,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
     134,   135,   136,    19,   138,    21,    22,    23,    24,    -1,
     144,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    91,    92,    -1,    94,    95,
      -1,    97,    98,    -1,   100,    -1,   102,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,   121,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,   134,   135,
     136,    -1,    19,    -1,    21,    22,    23,    24,   144,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,
      67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    -1,    -1,    91,    92,    -1,    94,    95,    -1,
      97,    98,    -1,   100,    -1,   102,   103,   104,    -1,   106,
     107,   108,    -1,   110,   111,   112,    -1,   114,    -1,    -1,
      -1,    -1,    -1,    -1,   121,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,   134,   135,   136,
      -1,    19,    -1,    21,    22,    23,    24,   144,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,
      98,    -1,   100,    -1,   102,   103,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,   134,   135,   136,    19,
      -1,    21,    22,    23,    24,    -1,   144,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,    -1,
     100,    -1,   102,   103,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   134,   135,   136,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   144,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,   102,    -1,    -1,    -1,    -1,   107,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    -1,   135,   136,    -1,
      -1,    -1,    -1,    -1,    -1,   143,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   100,   101,   102,    -1,    -1,    -1,    -1,
     107,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,    -1,   135,   136,
      -1,    -1,    -1,    -1,    -1,    -1,   143,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,   101,   102,    -1,    -1,    -1,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,    -1,   135,
     136,    -1,    -1,    -1,    -1,    -1,    -1,   143,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   100,   101,   102,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,    -1,
     135,   136,    -1,    -1,    -1,    -1,    -1,    -1,   143,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    97,    98,    -1,    -1,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
     134,    21,    22,    23,    24,    -1,    -1,    -1,   142,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,    -1,
      -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    19,   134,    21,    22,    23,    24,    -1,
      -1,    -1,   142,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,    95,
      -1,    97,    98,    -1,   100,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    -1,    -1,   134,   135,
     136,    19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,
      98,    -1,   100,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,   134,   135,   136,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,    -1,
     100,    -1,   102,   103,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,   134,   135,   136,    19,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    94,    95,    -1,    97,    98,    -1,   100,    -1,
     102,   103,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,   134,   135,   136,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    97,    98,    -1,   100,    -1,   102,   103,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
     134,   135,   136,    19,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,    95,
      -1,    97,    98,    -1,   100,    -1,   102,   103,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,   134,   135,
     136,    19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,
      98,    -1,   100,    -1,   102,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,   134,   135,   136,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,    -1,
      -1,    -1,   102,   103,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,   134,   135,   136,    19,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    94,    95,    -1,    97,    98,    -1,   100,    -1,
     102,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,   134,   135,   136,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    97,    98,    -1,    -1,    -1,   102,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
     134,   135,   136,    19,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,    95,
      -1,    97,    98,    -1,   100,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,   134,   135,
     136,    19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,
      98,    -1,   100,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,   134,   135,   136,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,    -1,
     100,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,   134,   135,   136,    19,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    94,    95,    -1,    97,    98,    -1,   100,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,   134,   135,   136,    19,    -1,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    85,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    97,    98,    -1,   100,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
     134,   135,   136,    19,    -1,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    70,    71,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,    95,
      -1,    97,    98,    -1,    -1,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,   134,   135,
     136,    19,    -1,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,
      98,    -1,    -1,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,   134,   135,   136,    19,
      -1,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      70,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,    -1,
      -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,   134,   135,   136,    19,    -1,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    -1,    91,
      -1,    -1,    94,    95,    -1,    97,    98,    -1,    -1,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,   134,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,
      98,    -1,   100,    -1,    -1,    -1,   104,    -1,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,   134,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    -1,    58,    59,    60,    -1,    -1,    63,
      -1,    -1,    66,    67,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,
      94,    95,    -1,    97,    98,    -1,   100,    -1,    -1,    -1,
     104,    -1,   106,   107,   108,    -1,   110,   111,   112,    -1,
     114,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
     134,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    -1,    63,    -1,    -1,    66,    67,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    91,    -1,    -1,    94,    95,    -1,    97,    98,    -1,
      -1,    -1,    -1,    -1,   104,    -1,   106,   107,   108,    -1,
     110,   111,   112,    -1,   114,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,   134,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    -1,    58,    59,    60,    -1,    -1,    63,    -1,    -1,
      66,    67,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    -1,    -1,    94,    95,
      -1,    97,    98,    -1,    -1,    -1,    -1,    -1,   104,    -1,
     106,   107,   108,    -1,   110,   111,   112,    -1,   114,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,   134,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    58,    59,    60,    -1,
      -1,    63,    -1,    -1,    66,    67,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,
      -1,    -1,    94,    95,    -1,    97,    98,    -1,    -1,    -1,
      -1,    -1,   104,    -1,   106,   107,   108,    -1,   110,   111,
     112,    -1,   114,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,   134,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    -1,
      58,    59,    60,    -1,    -1,    63,    -1,    -1,    66,    67,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    -1,    -1,    94,    95,    -1,    97,
      98,    -1,    -1,    51,    52,    -1,   104,    55,   106,   107,
     108,    -1,   110,   111,   112,    -1,   114,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    80,    81,    -1,    -1,   134,    -1,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    -1,   135,   136,    51,
      52,    -1,    -1,    55,    -1,   143,   144,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    80,    81,
      -1,    -1,    -1,    -1,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,    -1,   135,   136,    51,    52,    -1,    -1,    55,
      -1,   143,   144,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,   101,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,    -1,   135,
     136,    51,    52,    -1,    -1,    55,    -1,   143,   144,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    77,    -1,    -1,
      80,    81,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,    -1,   135,   136,    51,    52,    -1,
      -1,    55,    -1,   143,   144,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,   101,   102,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
      -1,   135,   136,    51,    52,    -1,    -1,    55,    -1,   143,
     144,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    -1,   135,   136,    51,
      52,    -1,    -1,    55,    -1,   143,   144,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    80,    81,
      -1,    -1,    -1,    -1,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,    -1,   135,   136,    51,    52,    -1,    -1,    55,
      -1,   143,   144,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,   101,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,    -1,   135,
     136,    51,    52,    -1,    -1,    55,    -1,   143,   144,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    77,    -1,    -1,
      80,    81,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,    -1,   135,   136,    51,    52,    -1,
      -1,    55,    -1,   143,   144,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    77,    -1,    -1,    80,    81,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,   101,   102,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
      -1,   135,   136,    51,    52,    -1,    -1,    55,    -1,   143,
     144,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    77,
      -1,    -1,    80,    81,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,   101,   102,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    -1,   135,   136,    51,
      52,    -1,    -1,    55,    -1,   143,   144,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    77,    -1,    -1,    80,    81,
      -1,    -1,    -1,    -1,    86,    87,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,   101,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,    -1,   135,   136,    51,    52,    -1,    -1,    55,
      -1,   143,   144,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    -1,    -1,    80,    81,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,   101,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,    -1,   135,
     136,    51,    52,    -1,    -1,    55,    -1,   143,   144,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    77,    -1,    -1,
      80,    81,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,    -1,   135,   136,    -1,    -1,    -1,
      -1,    -1,    -1,   143,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    -1,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    -1,    -1,
      -1,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   142,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    -1,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    -1,    -1,    -1,    88,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    -1,    -1,    88,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,
      -1,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    -1,    -1,    -1,    88,    89,    -1,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   101,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    -1,    -1,    -1,    -1,    88,    89,
      -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,
      88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    -1,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    -1,    -1,
      -1,    -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   150,   151,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    19,    21,    22,    23,    24,
      30,    31,    32,    33,    34,    35,    36,    39,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      58,    59,    60,    63,    66,    67,    69,    70,    71,    84,
      85,    91,    94,    95,    97,    98,   100,   104,   106,   107,
     108,   110,   111,   112,   114,   134,   135,   136,   152,   153,
     154,   159,   161,   163,   164,   165,   168,   169,   172,   173,
     175,   176,   177,   179,   180,   189,   203,   220,   240,   241,
     251,   252,   253,   257,   258,   259,   265,   266,   267,   269,
     270,   271,   272,   273,   274,   310,   323,   154,    21,    22,
      30,    31,    32,    39,    51,    55,    69,    88,    91,    94,
     134,   164,   165,   181,   182,   203,   220,   271,   274,   310,
     182,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    45,    46,    47,    48,    49,
      50,    51,    52,    55,    70,    71,    72,    73,    74,    75,
      76,    77,    80,    81,    86,    87,    88,    89,   100,   101,
     102,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   135,   136,   143,   144,   183,   187,   188,   273,   305,
     204,    91,   163,   164,   165,   167,   180,   189,   220,   271,
     272,   274,   167,   210,   212,    69,    91,   173,   180,   220,
     225,   271,   274,    33,    34,    35,    36,    48,    49,    50,
      51,    55,   106,   183,   184,   185,   267,   115,   118,   119,
     146,   148,   167,   261,   262,   263,   316,   320,   321,   322,
      51,   100,   102,   103,   135,   172,   189,   195,   198,   201,
     253,   308,   309,   195,   195,   144,   192,   193,   196,   197,
     323,   192,   196,   144,   317,   184,   155,   138,   189,   220,
     189,   189,   189,    55,     1,    94,   157,   158,   159,   174,
     175,   323,   205,   207,   190,   201,   308,   323,   189,   307,
     308,   323,    91,   142,   179,   220,   271,   274,   208,    53,
      54,    56,    63,   107,   183,   268,    63,    64,    65,   116,
     117,   254,   255,    61,   254,    62,   254,    63,   254,    63,
     254,    58,    59,   168,   189,   189,   316,   322,    40,    41,
      42,    43,    44,    37,    38,    51,    53,    54,    55,    56,
      69,    83,    94,   100,   101,   102,   103,   128,   131,   144,
     277,   278,   279,   280,   281,   284,   285,   286,   287,   289,
     290,   291,   292,   294,   295,   296,   299,   300,   301,   302,
     303,   323,   277,   279,    28,   238,   121,   142,    94,   100,
     176,   121,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    88,    89,    93,   101,   122,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,    90,
     105,   140,   147,   314,    90,   314,   315,    26,   138,   242,
     253,    92,    92,   192,   196,   242,   163,    51,    55,   181,
      58,    59,   278,   125,   275,    90,   140,   314,   219,   306,
      90,   147,   313,   156,   157,    55,   277,   277,    16,   221,
     320,   121,    90,   140,   314,    92,    92,   221,   167,   167,
      55,    90,   140,   314,    25,   107,   142,   264,   316,   115,
     263,    20,   245,   320,    57,   189,   189,   189,    93,   142,
     199,   200,   323,    57,   199,   200,    85,   194,   195,   201,
     308,   323,   195,   163,   316,   318,   163,   321,   160,   138,
     157,    90,   314,    92,   159,   174,   145,   316,   322,   318,
     159,   318,   141,   200,   319,   322,   200,   319,   139,   319,
      55,   176,   177,   178,   142,    90,   140,   314,   144,   236,
     289,   294,    63,   254,   256,   260,   261,    63,   255,    61,
      62,    63,    63,   101,   101,   154,   167,   167,   167,   167,
     159,   163,   163,    57,   121,   320,   293,    85,   289,   294,
     121,   156,   189,   142,   304,   323,    51,   142,   304,   320,
     142,   288,   189,   142,   288,    51,   142,   288,    51,   121,
     156,   239,   100,   168,   189,   201,   202,   174,   142,   179,
     142,   161,   162,   168,   180,   189,   191,   202,   220,   274,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,    51,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,    51,    52,    55,
     187,   192,   311,   312,   194,   201,    51,    52,    55,   187,
     192,   311,    51,    55,   311,   244,   243,   162,   189,   191,
     162,   191,    99,   170,   217,   276,   216,    51,    55,   181,
     311,   194,   311,   156,   163,   166,    15,    13,   247,   323,
     121,   121,   157,    16,    51,    55,   194,    51,    55,   157,
      27,   222,   320,   222,    51,    55,   194,    51,    55,   214,
     186,   157,   245,   189,   201,    15,   189,   189,   317,   100,
     189,   198,   308,   189,   309,   318,   145,   316,   200,   200,
     318,   145,   184,   152,   139,   191,   318,   159,   206,   308,
     176,   178,    51,    55,   194,    51,    55,   289,   209,   142,
      63,   157,   261,   189,   189,    51,   100,   226,   294,   318,
     318,   142,   172,   189,    15,    51,   281,   286,   303,    85,
     287,   292,   299,   301,   294,   296,   301,    51,   294,   172,
     189,    15,    79,   126,   230,   231,   323,   189,   200,   318,
     178,   142,    44,   121,    44,    90,   140,   314,   317,    92,
      92,   192,   196,   141,   200,    92,    92,   193,   196,   193,
     196,   230,   230,   171,   320,   167,   156,   141,    15,   318,
     183,   189,   202,   248,   323,    18,   224,   323,    17,   223,
     224,    92,    92,   141,    92,    92,   224,   211,   213,   141,
     167,   184,   139,    15,   200,   221,   189,   199,    85,   308,
     139,   318,   319,   141,   233,   317,    29,   113,   237,   139,
     142,   291,   318,   142,    85,    44,    44,   304,   320,   142,
     288,   142,   288,   142,   288,   142,   288,   288,    44,    44,
     227,   229,   232,   280,   282,   283,   286,   294,   295,   297,
     298,   301,   303,   156,   100,   189,   178,   159,   189,    51,
      55,   194,    51,    55,    57,   123,   162,   191,   168,   191,
     170,    92,   162,   191,   162,   191,   170,   242,   238,   156,
     157,   230,   218,   320,    15,    93,   249,   323,   157,    14,
     250,   323,   167,    15,    92,    15,   157,   157,   222,   189,
     157,   318,   200,   145,   146,   156,   157,   294,   142,   100,
     318,   189,   189,   294,   301,   294,   294,   189,   189,   233,
     233,    91,   220,   142,   304,   304,   142,   228,   220,   142,
     228,   142,   228,    15,   189,   141,   189,   189,   162,   191,
      15,   139,   157,   156,    91,   180,   220,   271,   274,   221,
     157,   221,    15,    15,   215,   224,   245,   246,    51,   234,
     235,   290,    15,   139,   142,   294,   142,   291,   288,   142,
     288,   288,   288,   126,   126,    55,    90,   282,   286,   142,
     227,   228,   298,   301,   294,   297,   301,   294,   139,    15,
      55,    90,   140,   314,   157,   157,   157,   142,   317,   294,
     142,   294,    51,    55,   304,   142,   228,   142,   228,   142,
     228,   142,   228,   228,    51,    55,   194,    51,    55,   247,
     223,    15,   235,   294,   288,   294,   301,   294,   294,   141,
     228,   142,   228,   228,   228,   294,   228
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   149,   151,   150,   152,   153,   153,   153,   153,   154,
     155,   154,   156,   157,   158,   158,   158,   158,   160,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   161,   161,   161,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   162,   162,   162,   163,
     163,   163,   163,   163,   163,   164,   166,   165,   167,   168,
     168,   169,   169,   171,   170,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   173,   173,   174,   174,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     176,   176,   177,   177,   178,   178,   179,   179,   179,   179,
     179,   179,   179,   179,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   181,   181,   182,   182,   182,   183,   183,
     183,   183,   183,   184,   184,   185,   186,   185,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   190,
     190,   190,   190,   191,   191,   192,   192,   192,   193,   193,
     194,   194,   194,   194,   194,   195,   195,   195,   195,   195,
     197,   196,   198,   198,   199,   199,   200,   201,   201,   201,
     201,   202,   202,   202,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   204,   203,   205,   206,   203,   207,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   208,   209,   203,   203,   203,   210,   211,   203,
     212,   213,   203,   203,   203,   214,   215,   203,   216,   203,
     217,   218,   203,   219,   203,   203,   203,   203,   203,   203,
     203,   220,   221,   221,   221,   222,   222,   223,   223,   224,
     224,   225,   225,   226,   226,   226,   226,   226,   226,   226,
     226,   226,   227,   227,   227,   227,   228,   228,   229,   229,
     229,   229,   229,   229,   229,   229,   229,   229,   229,   229,
     229,   229,   229,   230,   230,   232,   231,   231,   231,   233,
     233,   234,   234,   235,   235,   236,   236,   237,   237,   239,
     238,   240,   240,   240,   240,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   243,   242,   244,   242,   245,   246,
     246,   247,   247,   248,   248,   248,   249,   249,   250,   250,
     251,   251,   251,   251,   252,   252,   253,   253,   253,   253,
     254,   254,   255,   256,   255,   255,   255,   257,   257,   258,
     258,   259,   260,   260,   261,   261,   262,   262,   263,   264,
     263,   265,   265,   266,   266,   267,   268,   268,   268,   268,
     268,   268,   269,   269,   270,   270,   270,   270,   271,   271,
     271,   271,   271,   272,   272,   273,   273,   273,   273,   273,
     273,   273,   273,   274,   274,   275,   276,   275,   277,   277,
     278,   278,   278,   279,   279,   279,   279,   280,   281,   281,
     282,   282,   283,   283,   284,   284,   285,   285,   286,   286,
     287,   287,   287,   287,   288,   288,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   290,   290,   290,   290,   290,   291,   291,   292,   293,
     292,   294,   294,   295,   296,   297,   298,   298,   299,   299,
     300,   300,   301,   301,   302,   302,   303,   303,   304,   304,
     305,   306,   305,   307,   307,   308,   308,   309,   309,   309,
     309,   309,   310,   310,   310,   311,   311,   311,   311,   312,
     312,   312,   313,   313,   314,   314,   315,   315,   316,   316,
     317,   317,   318,   319,   319,   319,   320,   320,   321,   321,
     322,   322,   323
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     3,     2,     1,
       0,     5,     4,     2,     1,     1,     3,     2,     0,     4,
       2,     3,     3,     3,     3,     3,     4,     1,     3,     3,
       3,     3,     3,     1,     3,     3,     6,     5,     5,     5,
       5,     4,     6,     4,     6,     3,     1,     3,     1,     1,
       3,     3,     3,     2,     1,     2,     0,     5,     1,     1,
       1,     1,     4,     0,     5,     2,     3,     4,     5,     4,
       5,     2,     2,     2,     2,     2,     1,     3,     1,     3,
       1,     2,     3,     5,     2,     4,     2,     4,     1,     3,
       1,     3,     2,     3,     1,     2,     1,     4,     3,     3,
       3,     3,     2,     1,     1,     4,     3,     3,     3,     3,
       2,     1,     1,     1,     1,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       6,     5,     5,     5,     5,     4,     3,     3,     2,     2,
       3,     2,     2,     3,     3,     3,     3,     3,     3,     4,
       4,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     3,     3,
       3,     3,     6,     6,     4,     6,     4,     6,     1,     1,
       2,     4,     2,     1,     3,     3,     5,     3,     1,     1,
       1,     2,     2,     4,     2,     1,     2,     2,     4,     1,
       0,     2,     2,     1,     2,     1,     2,     1,     2,     3,
       4,     3,     4,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     0,     5,     0,     3,
       3,     3,     2,     3,     3,     1,     2,     4,     3,     2,
       1,     2,     0,     0,     5,     6,     6,     0,     0,     7,
       0,     0,     7,     5,     4,     0,     0,     9,     0,     6,
       0,     0,     8,     0,     5,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     5,     1,
       2,     1,     1,     1,     4,     6,     3,     5,     2,     4,
       1,     3,     4,     2,     2,     1,     2,     0,     6,     8,
       4,     6,     4,     3,     6,     2,     4,     6,     2,     4,
       2,     4,     1,     1,     1,     0,     4,     1,     4,     1,
       4,     1,     3,     1,     1,     4,     1,     3,     3,     0,
       5,     2,     4,     5,     5,     2,     4,     4,     3,     3,
       3,     2,     1,     4,     0,     5,     0,     5,     5,     1,
       1,     6,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     2,     3,
       1,     2,     1,     0,     4,     1,     2,     2,     3,     2,
       3,     1,     1,     2,     1,     2,     1,     2,     1,     0,
       4,     2,     3,     1,     4,     2,     1,     1,     1,     1,
       1,     2,     2,     3,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     0,     4,     1,     1,
       3,     5,     3,     1,     2,     4,     2,     2,     2,     1,
       2,     1,     1,     3,     1,     3,     1,     1,     2,     1,
       4,     2,     2,     1,     2,     0,     6,     8,     4,     6,
       4,     6,     2,     4,     6,     2,     4,     2,     4,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     3,     2,     2,     2,     1,     3,     1,     3,
       1,     1,     2,     1,     1,     1,     2,     1,     2,     1,
       1,     0,     4,     1,     2,     1,     3,     3,     3,     2,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       0,     2,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (p, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, p); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, parser_state *p)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (p);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, parser_state *p)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, p);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, parser_state *p)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , p);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, p); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, parser_state *p)
{
  YYUSE (yyvaluep);
  YYUSE (p);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (parser_state *p)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, p);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 1617 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_BEG;
                      if (!p->locals) p->locals = cons(0,0);
                    }
#line 6153 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 3:
#line 1622 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->tree = new_scope(p, (yyvsp[0].nd));
                      NODE_LINENO(p->tree, (yyvsp[0].nd));
                    }
#line 6162 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 4:
#line 1629 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 6170 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 5:
#line 1635 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 6178 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 6:
#line 1639 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_begin(p, (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 6187 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 7:
#line 1644 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), newline_node((yyvsp[0].nd)));
                    }
#line 6195 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 8:
#line 1648 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 6203 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 10:
#line 1655 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = local_switch(p);
                      nvars_block(p);
                    }
#line 6212 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 11:
#line 1660 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "BEGIN not supported");
                      local_resume(p, (yyvsp[-3].nd));
                      nvars_unnest(p);
                      (yyval.nd) = 0;
                    }
#line 6223 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 12:
#line 1672 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if ((yyvsp[-2].nd)) {
                        (yyval.nd) = new_rescue(p, (yyvsp[-3].nd), (yyvsp[-2].nd), (yyvsp[-1].nd));
                        NODE_LINENO((yyval.nd), (yyvsp[-3].nd));
                      }
                      else if ((yyvsp[-1].nd)) {
                        yywarning(p, "else without rescue is useless");
                        (yyval.nd) = push((yyvsp[-3].nd), (yyvsp[-1].nd));
                      }
                      else {
                        (yyval.nd) = (yyvsp[-3].nd);
                      }
                      if ((yyvsp[0].nd)) {
                        if ((yyval.nd)) {
                          (yyval.nd) = new_ensure(p, (yyval.nd), (yyvsp[0].nd));
                        }
                        else {
                          (yyval.nd) = push((yyvsp[0].nd), new_nil(p));
                        }
                      }
                    }
#line 6249 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 13:
#line 1696 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 6257 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 14:
#line 1702 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 6265 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 15:
#line 1706 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_begin(p, (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 6274 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 16:
#line 1711 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), newline_node((yyvsp[0].nd)));
                    }
#line 6282 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 17:
#line 1715 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_begin(p, (yyvsp[0].nd));
                    }
#line 6290 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 18:
#line 1720 "mrbgems/mruby-compiler/core/parse.y"
                                     {p->lstate = EXPR_FNAME;}
#line 6296 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 19:
#line 1721 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_alias(p, (yyvsp[-2].id), (yyvsp[0].id));
                    }
#line 6304 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 20:
#line 1725 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 6312 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 21:
#line 1729 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd), 0);
                    }
#line 6320 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 22:
#line 1733 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_unless(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd), 0);
                    }
#line 6328 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 23:
#line 1737 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_while(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd));
                    }
#line 6336 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 24:
#line 1741 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_until(p, cond((yyvsp[0].nd)), (yyvsp[-2].nd));
                    }
#line 6344 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 25:
#line 1745 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6352 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 26:
#line 1749 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "END not supported");
                      (yyval.nd) = new_postexe(p, (yyvsp[-1].nd));
                    }
#line 6361 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 28:
#line 1755 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6369 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 29:
#line 1759 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), new_array(p, (yyvsp[0].nd)));
                    }
#line 6377 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 30:
#line 1763 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6385 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 31:
#line 1767 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-2].nd), new_array(p, (yyvsp[0].nd)));
                    }
#line 6393 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 32:
#line 1771 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *lhs = new_lvar(p, (yyvsp[0].id));
                      assignable(p, lhs);
                      (yyval.nd) = new_asgn(p, lhs, (yyvsp[-2].nd));
                    }
#line 6403 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 34:
#line 1780 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6411 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 35:
#line 1784 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, (yyvsp[-2].nd), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6419 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 36:
#line 1788 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-5].nd), intern_op(aref), (yyvsp[-3].nd), '.'), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6427 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 37:
#line 1792 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6435 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 38:
#line 1796 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6443 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 39:
#line 1800 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "constant re-assignment");
                      (yyval.nd) = 0;
                    }
#line 6452 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 40:
#line 1805 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, tCOLON2), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6460 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 41:
#line 1809 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      endless_method_name(p, (yyvsp[-3].nd));
                      void_expr_error(p, (yyvsp[0].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 6473 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 42:
#line 1818 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-5].nd);
                      endless_method_name(p, (yyvsp[-5].nd));
                      void_expr_error(p, (yyvsp[-2].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-4].nd), new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd)));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 6486 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 43:
#line 1827 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      void_expr_error(p, (yyvsp[0].nd));
                      defs_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 6499 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 44:
#line 1836 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-5].nd);
                      void_expr_error(p, (yyvsp[-2].nd));
                      defs_setup(p, (yyval.nd), (yyvsp[-4].nd), new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd)));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 6512 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 45:
#line 1845 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      backref_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 6521 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 47:
#line 1853 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6529 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 50:
#line 1862 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_and(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6537 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 51:
#line 1866 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_or(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6545 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 52:
#line 1870 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "!");
                    }
#line 6553 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 53:
#line 1874 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "!");
                    }
#line 6561 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 55:
#line 1882 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_def(p, (yyvsp[0].id), nint(p->cmdarg_stack), local_switch(p));
                      p->cmdarg_stack = 0;
                      p->in_def++;
                      nvars_block(p);
                    }
#line 6572 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 56:
#line 1891 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_FNAME;
                    }
#line 6580 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 57:
#line 1895 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_sdef(p, (yyvsp[-3].nd), (yyvsp[0].id), nint(p->cmdarg_stack), local_switch(p));
                      p->cmdarg_stack = 0;
                      p->in_def++;
                      p->in_single++;
                      nvars_block(p);
                      p->lstate = EXPR_ENDFN; /* force for args */
                    }
#line 6593 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 58:
#line 1906 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (!(yyvsp[0].nd)) (yyval.nd) = new_nil(p);
                      else {
                        (yyval.nd) = (yyvsp[0].nd);
                      }
                    }
#line 6604 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 62:
#line 1920 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 6612 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 63:
#line 1926 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      nvars_nest(p);
                    }
#line 6621 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 64:
#line 1933 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block(p, (yyvsp[-2].nd), (yyvsp[-1].nd));
                      local_unnest(p);
                      nvars_unnest(p);
                    }
#line 6631 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 65:
#line 1941 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 6639 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 66:
#line 1945 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      args_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = new_fcall(p, (yyvsp[-2].id), (yyvsp[-1].nd));
                    }
#line 6648 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 67:
#line 1950 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 6656 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 68:
#line 1954 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      args_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), (yyvsp[-3].num));
                   }
#line 6665 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 69:
#line 1959 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), tCOLON2);
                    }
#line 6673 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 70:
#line 1963 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      args_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), tCOLON2);
                    }
#line 6682 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 71:
#line 1968 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_super(p, (yyvsp[0].nd));
                    }
#line 6690 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 72:
#line 1972 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_yield(p, (yyvsp[0].nd));
                    }
#line 6698 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 73:
#line 1976 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_return(p, ret_args(p, (yyvsp[0].nd)));
                    }
#line 6706 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 74:
#line 1980 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_break(p, ret_args(p, (yyvsp[0].nd)));
                    }
#line 6714 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 75:
#line 1984 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_next(p, ret_args(p, (yyvsp[0].nd)));
                    }
#line 6722 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 76:
#line 1990 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 6730 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 77:
#line 1994 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 6738 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 79:
#line 2001 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 6746 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 80:
#line 2007 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 6754 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 81:
#line 2011 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(push((yyvsp[-1].nd),(yyvsp[0].nd)));
                    }
#line 6762 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 82:
#line 2015 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list2((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6770 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 83:
#line 2019 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-4].nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6778 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 84:
#line 2023 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list2((yyvsp[-1].nd), new_nil(p));
                    }
#line 6786 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 85:
#line 2027 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-3].nd), new_nil(p), (yyvsp[0].nd));
                    }
#line 6794 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 86:
#line 2031 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list2(0, (yyvsp[0].nd));
                    }
#line 6802 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 87:
#line 2035 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 6810 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 88:
#line 2039 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list2(0, new_nil(p));
                    }
#line 6818 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 89:
#line 2043 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, new_nil(p), (yyvsp[0].nd));
                    }
#line 6826 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 91:
#line 2050 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_masgn(p, (yyvsp[-1].nd), NULL);
                    }
#line 6834 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 92:
#line 2056 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[-1].nd));
                    }
#line 6842 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 93:
#line 2060 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[-1].nd));
                    }
#line 6850 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 94:
#line 2066 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 6858 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 95:
#line 2070 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 6866 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 96:
#line 2076 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      assignable(p, (yyvsp[0].nd));
                    }
#line 6874 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 97:
#line 2080 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), intern_op(aref), (yyvsp[-1].nd), '.');
                    }
#line 6882 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 98:
#line 2084 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 6890 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 99:
#line 2088 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, tCOLON2);
                    }
#line 6898 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 100:
#line 2092 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 6906 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 101:
#line 2096 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "dynamic constant assignment");
                      (yyval.nd) = new_colon2(p, (yyvsp[-2].nd), (yyvsp[0].id));
                    }
#line 6916 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 102:
#line 2102 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "dynamic constant assignment");
                      (yyval.nd) = new_colon3(p, (yyvsp[0].id));
                    }
#line 6926 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 103:
#line 2108 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      backref_error(p, (yyvsp[0].nd));
                      (yyval.nd) = 0;
                    }
#line 6935 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 104:
#line 2115 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      assignable(p, (yyvsp[0].nd));
                    }
#line 6943 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 105:
#line 2119 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), intern_op(aref), (yyvsp[-1].nd), '.');
                    }
#line 6951 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 106:
#line 2123 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 6959 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 107:
#line 2127 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, tCOLON2);
                    }
#line 6967 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 108:
#line 2131 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, (yyvsp[-1].num));
                    }
#line 6975 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 109:
#line 2135 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "dynamic constant assignment");
                      (yyval.nd) = new_colon2(p, (yyvsp[-2].nd), (yyvsp[0].id));
                    }
#line 6985 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 110:
#line 2141 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "dynamic constant assignment");
                      (yyval.nd) = new_colon3(p, (yyvsp[0].id));
                    }
#line 6995 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 111:
#line 2147 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      backref_error(p, (yyvsp[0].nd));
                      (yyval.nd) = 0;
                    }
#line 7004 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 112:
#line 2152 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "can't assign to numbered parameter");
                    }
#line 7012 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 113:
#line 2158 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "class/module name must be CONSTANT");
                    }
#line 7020 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 115:
#line 2165 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(nint(1), nsym((yyvsp[0].id)));
                    }
#line 7028 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 116:
#line 2169 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(nint(0), nsym((yyvsp[0].id)));
                    }
#line 7036 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 117:
#line 2173 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = cons((yyvsp[-2].nd), nsym((yyvsp[0].id)));
                    }
#line 7045 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 121:
#line 2183 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_ENDFN;
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 7054 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 122:
#line 2188 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_ENDFN;
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 7063 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 125:
#line 2199 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_undef(p, (yyvsp[0].id));
                    }
#line 7071 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 126:
#line 2202 "mrbgems/mruby-compiler/core/parse.y"
                                 {p->lstate = EXPR_FNAME;}
#line 7077 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 127:
#line 2203 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-3].nd), nsym((yyvsp[0].id)));
                    }
#line 7085 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 128:
#line 2208 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(or);     }
#line 7091 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 129:
#line 2209 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(xor);    }
#line 7097 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 130:
#line 2210 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(and);    }
#line 7103 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 131:
#line 2211 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(cmp);    }
#line 7109 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 132:
#line 2212 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(eq);     }
#line 7115 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 133:
#line 2213 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(eqq);    }
#line 7121 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 134:
#line 2214 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(match);  }
#line 7127 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 135:
#line 2215 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(nmatch); }
#line 7133 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 136:
#line 2216 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(gt);     }
#line 7139 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 137:
#line 2217 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(ge);     }
#line 7145 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 138:
#line 2218 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(lt);     }
#line 7151 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 139:
#line 2219 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(le);     }
#line 7157 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 140:
#line 2220 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(neq);    }
#line 7163 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 141:
#line 2221 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(lshift); }
#line 7169 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 142:
#line 2222 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(rshift); }
#line 7175 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 143:
#line 2223 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(add);    }
#line 7181 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 144:
#line 2224 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(sub);    }
#line 7187 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 145:
#line 2225 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(mul);    }
#line 7193 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 146:
#line 2226 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(mul);    }
#line 7199 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 147:
#line 2227 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(div);    }
#line 7205 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 148:
#line 2228 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(mod);    }
#line 7211 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 149:
#line 2229 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(pow);    }
#line 7217 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 150:
#line 2230 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(pow);    }
#line 7223 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 151:
#line 2231 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(not);    }
#line 7229 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 152:
#line 2232 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(neg);    }
#line 7235 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 153:
#line 2233 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(plus);   }
#line 7241 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 154:
#line 2234 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(minus);  }
#line 7247 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 155:
#line 2235 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(aref);   }
#line 7253 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 156:
#line 2236 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(aset);   }
#line 7259 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 157:
#line 2237 "mrbgems/mruby-compiler/core/parse.y"
                                { (yyval.id) = intern_op(tick);   }
#line 7265 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 198:
#line 2255 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_asgn(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7273 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 199:
#line 2259 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, (yyvsp[-2].nd), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7281 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 200:
#line 2263 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-5].nd), intern_op(aref), (yyvsp[-3].nd), '.'), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7289 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 201:
#line 2267 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7297 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 202:
#line 2271 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, (yyvsp[-3].num)), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7305 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 203:
#line 2275 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_op_asgn(p, new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), 0, tCOLON2), (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 7313 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 204:
#line 2279 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "constant re-assignment");
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 7322 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 205:
#line 2284 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "constant re-assignment");
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 7331 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 206:
#line 2289 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      backref_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = new_begin(p, 0);
                    }
#line 7340 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 207:
#line 2294 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot2(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7348 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 208:
#line 2298 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot2(p, (yyvsp[-1].nd), new_nil(p));
                    }
#line 7356 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 209:
#line 2302 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot2(p, new_nil(p), (yyvsp[0].nd));
                    }
#line 7364 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 210:
#line 2306 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot3(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7372 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 211:
#line 2310 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot3(p, (yyvsp[-1].nd), new_nil(p));
                    }
#line 7380 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 212:
#line 2314 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dot3(p, new_nil(p), (yyvsp[0].nd));
                    }
#line 7388 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 213:
#line 2318 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "+", (yyvsp[0].nd));
                    }
#line 7396 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 214:
#line 2322 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "-", (yyvsp[0].nd));
                    }
#line 7404 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 215:
#line 2326 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "*", (yyvsp[0].nd));
                    }
#line 7412 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 216:
#line 2330 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "/", (yyvsp[0].nd));
                    }
#line 7420 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 217:
#line 2334 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "%", (yyvsp[0].nd));
                    }
#line 7428 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 218:
#line 2338 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "**", (yyvsp[0].nd));
                    }
#line 7436 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 219:
#line 2342 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, call_bin_op(p, (yyvsp[-2].nd), "**", (yyvsp[0].nd)));
                    }
#line 7444 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 220:
#line 2346 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, call_bin_op(p, (yyvsp[-2].nd), "**", (yyvsp[0].nd)));
                    }
#line 7452 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 221:
#line 2350 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, (yyvsp[0].nd), "+@");
                    }
#line 7460 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 222:
#line 2354 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, (yyvsp[0].nd));
                    }
#line 7468 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 223:
#line 2358 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "|", (yyvsp[0].nd));
                    }
#line 7476 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 224:
#line 2362 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "^", (yyvsp[0].nd));
                    }
#line 7484 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 225:
#line 2366 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "&", (yyvsp[0].nd));
                    }
#line 7492 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 226:
#line 2370 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<=>", (yyvsp[0].nd));
                    }
#line 7500 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 227:
#line 2374 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), ">", (yyvsp[0].nd));
                    }
#line 7508 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 228:
#line 2378 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), ">=", (yyvsp[0].nd));
                    }
#line 7516 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 229:
#line 2382 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<", (yyvsp[0].nd));
                    }
#line 7524 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 230:
#line 2386 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<=", (yyvsp[0].nd));
                    }
#line 7532 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 231:
#line 2390 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "==", (yyvsp[0].nd));
                    }
#line 7540 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 232:
#line 2394 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "===", (yyvsp[0].nd));
                    }
#line 7548 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 233:
#line 2398 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "!=", (yyvsp[0].nd));
                    }
#line 7556 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 234:
#line 2402 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "=~", (yyvsp[0].nd));
                    }
#line 7564 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 235:
#line 2406 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "!~", (yyvsp[0].nd));
                    }
#line 7572 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 236:
#line 2410 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "!");
                    }
#line 7580 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 237:
#line 2414 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[0].nd)), "~");
                    }
#line 7588 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 238:
#line 2418 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), "<<", (yyvsp[0].nd));
                    }
#line 7596 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 239:
#line 2422 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_bin_op(p, (yyvsp[-2].nd), ">>", (yyvsp[0].nd));
                    }
#line 7604 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 240:
#line 2426 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_and(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7612 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 241:
#line 2430 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_or(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7620 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 242:
#line 2434 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-5].nd)), (yyvsp[-3].nd), (yyvsp[0].nd));
                    }
#line 7628 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 243:
#line 2438 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-5].nd)), (yyvsp[-3].nd), (yyvsp[0].nd));
                    }
#line 7636 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 244:
#line 2442 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      endless_method_name(p, (yyvsp[-3].nd));
                      void_expr_error(p, (yyvsp[0].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 7649 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 245:
#line 2451 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-5].nd);
                      endless_method_name(p, (yyvsp[-5].nd));
                      void_expr_error(p, (yyvsp[-2].nd));
                      defn_setup(p, (yyval.nd), (yyvsp[-4].nd), new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd)));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 7662 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 246:
#line 2460 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      void_expr_error(p, (yyvsp[0].nd));
                      defs_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[0].nd));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 7675 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 247:
#line 2469 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-5].nd);
                      void_expr_error(p, (yyvsp[-2].nd));
                      defs_setup(p, (yyval.nd), (yyvsp[-4].nd), new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd)));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 7688 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 248:
#line 2478 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7696 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 250:
#line 2485 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 7705 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 251:
#line 2490 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-3].nd), new_hash(p, (yyvsp[-1].nd)));
                    }
#line 7713 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 252:
#line 2494 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(new_kw_hash(p, (yyvsp[-1].nd)), 0);
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 7722 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 253:
#line 2501 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7730 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 254:
#line 2505 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[-2].nd));
                      (yyval.nd) = new_mod_rescue(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7739 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 255:
#line 2512 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 7747 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 256:
#line 2516 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      mrb_sym r = intern_op(mul);
                      mrb_sym k = intern_op(pow);
                      mrb_sym b = intern_op(and);
                      (yyval.nd) = new_callargs(p, push((yyvsp[-3].nd), new_splat(p, new_lvar(p, r))),
                                        new_kw_hash(p, list1(cons(new_kw_rest_args(p, 0), new_lvar(p, k)))),
                                        new_block_arg(p, new_lvar(p, b)));
                    }
#line 7760 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 257:
#line 2525 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      mrb_sym r = intern_op(mul);
                      mrb_sym k = intern_op(pow);
                      mrb_sym b = intern_op(and);
                      if (local_var_p(p, r) && local_var_p(p, k) && local_var_p(p, b)) {
                        (yyval.nd) = new_callargs(p, list1(new_splat(p, new_lvar(p, r))),
                                          new_kw_hash(p, list1(cons(new_kw_rest_args(p, 0), new_lvar(p, k)))),
                                          new_block_arg(p, new_lvar(p, b)));
                      }
                      else {
                        yyerror(p, "unexpected argument forwarding ...");
                        (yyval.nd) = 0;
                      }
                    }
#line 7779 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 262:
#line 2548 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p,(yyvsp[-1].nd),0,0);
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 7788 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 263:
#line 2553 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p,(yyvsp[-3].nd),new_kw_hash(p,(yyvsp[-1].nd)),0);
                      NODE_LINENO((yyval.nd), (yyvsp[-3].nd));
                    }
#line 7797 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 264:
#line 2558 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p,0,new_kw_hash(p,(yyvsp[-1].nd)),0);
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 7806 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 265:
#line 2565 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = new_callargs(p, list1((yyvsp[0].nd)), 0, 0);
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 7816 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 266:
#line 2571 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p, (yyvsp[-1].nd), 0, (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 7825 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 267:
#line 2576 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p, 0, new_kw_hash(p, (yyvsp[-1].nd)), (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 7834 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 268:
#line 2581 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p, (yyvsp[-3].nd), new_kw_hash(p, (yyvsp[-1].nd)), (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-3].nd));
                    }
#line 7843 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 269:
#line 2586 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_callargs(p, 0, 0, (yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 7852 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 270:
#line 2592 "mrbgems/mruby-compiler/core/parse.y"
                   {
                      (yyval.stack) = p->cmdarg_stack;
                      CMDARG_PUSH(1);
                    }
#line 7861 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 271:
#line 2597 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->cmdarg_stack = (yyvsp[-1].stack);
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7870 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 272:
#line 2604 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block_arg(p, (yyvsp[0].nd));
                    }
#line 7878 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 273:
#line 2608 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block_arg(p, 0);
                    }
#line 7886 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 274:
#line 2614 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 7894 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 275:
#line 2618 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 7902 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 277:
#line 2627 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = list1((yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 7912 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 278:
#line 2633 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(new_splat(p, (yyvsp[0].nd)));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 7921 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 279:
#line 2638 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7930 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 280:
#line 2643 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-3].nd), new_splat(p, (yyvsp[0].nd)));
                    }
#line 7938 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 281:
#line 2649 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 7947 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 282:
#line 2654 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-3].nd), new_splat(p, (yyvsp[0].nd)));
                    }
#line 7955 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 283:
#line 2658 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(new_splat(p, (yyvsp[0].nd)));
                    }
#line 7963 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 291:
#line 2671 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_nvar(p, (yyvsp[0].num));
                    }
#line 7971 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 292:
#line 2675 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, (yyvsp[0].id), 0);
                    }
#line 7979 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 293:
#line 2679 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 7988 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 294:
#line 2685 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->cmdarg_stack = (yyvsp[-2].stack);
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 7997 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 295:
#line 2690 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 8006 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 296:
#line 2694 "mrbgems/mruby-compiler/core/parse.y"
                       {p->lstate = EXPR_ENDARG;}
#line 8012 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 297:
#line 2695 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->cmdarg_stack = (yyvsp[-3].stack);
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 8021 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 298:
#line 2699 "mrbgems/mruby-compiler/core/parse.y"
                              {p->lstate = EXPR_ENDARG;}
#line 8027 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 299:
#line 2700 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_nil(p);
                    }
#line 8035 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 300:
#line 2704 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8043 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 301:
#line 2708 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_colon2(p, (yyvsp[-2].nd), (yyvsp[0].id));
                    }
#line 8051 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 302:
#line 2712 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_colon3(p, (yyvsp[0].id));
                    }
#line 8059 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 303:
#line 2716 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_array(p, (yyvsp[-1].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 8068 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 304:
#line 2721 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_hash(p, (yyvsp[-1].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[-1].nd));
                    }
#line 8077 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 305:
#line 2726 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_return(p, 0);
                    }
#line 8085 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 306:
#line 2730 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_yield(p, (yyvsp[0].nd));
                    }
#line 8093 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 307:
#line 2734 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, cond((yyvsp[-1].nd)), "!");
                    }
#line 8101 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 308:
#line 2738 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = call_uni_op(p, new_nil(p), "!");
                    }
#line 8109 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 309:
#line 2742 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, (yyvsp[-1].id), new_callargs(p, 0, 0, (yyvsp[0].nd)));
                    }
#line 8117 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 311:
#line 2747 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      call_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8126 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 312:
#line 2752 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      (yyval.num) = p->lpar_beg;
                      p->lpar_beg = ++p->paren_nest;
                    }
#line 8136 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 313:
#line 2758 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.stack) = p->cmdarg_stack;
                      p->cmdarg_stack = 0;
                    }
#line 8145 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 314:
#line 2763 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lpar_beg = (yyvsp[-3].num);
                      (yyval.nd) = new_lambda(p, (yyvsp[-2].nd), (yyvsp[0].nd));
                      local_unnest(p);
                      p->cmdarg_stack = (yyvsp[-1].stack);
                      CMDARG_LEXPOP();
                    }
#line 8157 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 315:
#line 2774 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-4].nd)), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-5].num));
                    }
#line 8166 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 316:
#line 2782 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_unless(p, cond((yyvsp[-4].nd)), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-5].num));
                    }
#line 8175 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 317:
#line 2786 "mrbgems/mruby-compiler/core/parse.y"
                                {COND_PUSH(1);}
#line 8181 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 318:
#line 2786 "mrbgems/mruby-compiler/core/parse.y"
                                                              {COND_POP();}
#line 8187 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 319:
#line 2789 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_while(p, cond((yyvsp[-4].nd)), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-6].num));
                    }
#line 8196 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 320:
#line 2793 "mrbgems/mruby-compiler/core/parse.y"
                                {COND_PUSH(1);}
#line 8202 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 321:
#line 2793 "mrbgems/mruby-compiler/core/parse.y"
                                                              {COND_POP();}
#line 8208 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 322:
#line 2796 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_until(p, cond((yyvsp[-4].nd)), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-6].num));
                    }
#line 8217 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 323:
#line 2803 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_case(p, (yyvsp[-3].nd), (yyvsp[-1].nd));
                    }
#line 8225 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 324:
#line 2807 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_case(p, 0, (yyvsp[-1].nd));
                    }
#line 8233 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 325:
#line 2811 "mrbgems/mruby-compiler/core/parse.y"
                  {COND_PUSH(1);}
#line 8239 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 326:
#line 2813 "mrbgems/mruby-compiler/core/parse.y"
                  {COND_POP();}
#line 8245 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 327:
#line 2816 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_for(p, (yyvsp[-7].nd), (yyvsp[-4].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-8].num));
                    }
#line 8254 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 328:
#line 2822 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "class definition in method body");
                      (yyval.nd) = local_switch(p);
                      nvars_block(p);
                    }
#line 8265 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 329:
#line 2830 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_class(p, (yyvsp[-4].nd), (yyvsp[-3].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-5].num));
                      local_resume(p, (yyvsp[-2].nd));
                      nvars_unnest(p);
                    }
#line 8276 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 330:
#line 2838 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.num) = p->in_def;
                      p->in_def = 0;
                    }
#line 8285 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 331:
#line 2843 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(local_switch(p), nint(p->in_single));
                      nvars_block(p);
                      p->in_single = 0;
                    }
#line 8295 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 332:
#line 2850 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_sclass(p, (yyvsp[-5].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-7].num));
                      local_resume(p, (yyvsp[-2].nd)->car);
                      nvars_unnest(p);
                      p->in_def = (yyvsp[-4].num);
                      p->in_single = intn((yyvsp[-2].nd)->cdr);
                    }
#line 8308 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 333:
#line 2860 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (p->in_def || p->in_single)
                        yyerror(p, "module definition in method body");
                      (yyval.nd) = local_switch(p);
                      nvars_block(p);
                    }
#line 8319 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 334:
#line 2868 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_module(p, (yyvsp[-3].nd), (yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-4].num));
                      local_resume(p, (yyvsp[-2].nd));
                      nvars_unnest(p);
                    }
#line 8330 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 335:
#line 2878 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      defn_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      nvars_unnest(p);
                      p->in_def--;
                    }
#line 8341 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 336:
#line 2888 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-3].nd);
                      defs_setup(p, (yyval.nd), (yyvsp[-2].nd), (yyvsp[-1].nd));
                      nvars_unnest(p);
                      p->in_def--;
                      p->in_single--;
                    }
#line 8353 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 337:
#line 2896 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_break(p, 0);
                    }
#line 8361 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 338:
#line 2900 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_next(p, 0);
                    }
#line 8369 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 339:
#line 2904 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_redo(p);
                    }
#line 8377 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 340:
#line 2908 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_retry(p);
                    }
#line 8385 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 341:
#line 2914 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
                    }
#line 8394 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 348:
#line 2933 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_if(p, cond((yyvsp[-3].nd)), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8402 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 350:
#line 2940 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8410 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 351:
#line 2946 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(list1((yyvsp[0].nd)));
                    }
#line 8418 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 353:
#line 2953 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[0].nd),0,0);
                    }
#line 8426 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 354:
#line 2957 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-3].nd), new_arg(p, (yyvsp[0].id)), 0);
                    }
#line 8434 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 355:
#line 2961 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-5].nd), new_arg(p, (yyvsp[-2].id)), (yyvsp[0].nd));
                    }
#line 8442 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 356:
#line 2965 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-2].nd), nint(-1), 0);
                    }
#line 8450 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 357:
#line 2969 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3((yyvsp[-4].nd), nint(-1), (yyvsp[0].nd));
                    }
#line 8458 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 358:
#line 2973 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, new_arg(p, (yyvsp[0].id)), 0);
                    }
#line 8466 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 359:
#line 2977 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, new_arg(p, (yyvsp[-2].id)), (yyvsp[0].nd));
                    }
#line 8474 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 360:
#line 2981 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, nint(-1), 0);
                    }
#line 8482 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 361:
#line 2985 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list3(0, nint(-1), (yyvsp[0].nd));
                    }
#line 8490 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 362:
#line 2991 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, (yyvsp[-3].nd), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 8498 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 363:
#line 2995 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, (yyvsp[-1].nd), 0, (yyvsp[0].id));
                    }
#line 8506 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 364:
#line 2999 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 8514 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 365:
#line 3003 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, 0, (yyvsp[0].id));
                    }
#line 8522 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 366:
#line 3009 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8530 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 367:
#line 3013 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, 0, 0);
                    }
#line 8538 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 368:
#line 3019 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 8546 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 369:
#line 3023 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-7].nd), (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8554 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 370:
#line 3027 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), (yyvsp[-1].nd), 0, 0, (yyvsp[0].nd));
                    }
#line 8562 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 371:
#line 3031 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8570 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 372:
#line 3035 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), 0, (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 8578 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 373:
#line 3039 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-2].nd), 0, 0, 0, (yyvsp[0].nd));
                    }
#line 8586 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 374:
#line 3043 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8594 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 375:
#line 3047 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-1].nd), 0, 0, 0, (yyvsp[0].nd));
                    }
#line 8602 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 376:
#line 3051 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 8610 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 377:
#line 3055 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8618 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 378:
#line 3059 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-1].nd), 0, 0, (yyvsp[0].nd));
                    }
#line 8626 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 379:
#line 3063 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8634 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 380:
#line 3067 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 8642 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 381:
#line 3071 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8650 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 382:
#line 3075 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, 0, 0, (yyvsp[0].nd));
                    }
#line 8658 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 383:
#line 3081 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_blk(p, 0);
                      (yyval.nd) = 0;
                    }
#line 8667 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 384:
#line 3086 "mrbgems/mruby-compiler/core/parse.y"
                   {
                      p->cmd_start = TRUE;
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8676 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 385:
#line 3092 "mrbgems/mruby-compiler/core/parse.y"
                      {local_add_blk(p, 0);}
#line 8682 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 386:
#line 3093 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 8690 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 387:
#line 3097 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_blk(p, 0);
                      (yyval.nd) = 0;
                    }
#line 8699 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 388:
#line 3102 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 8707 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 389:
#line 3109 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 8715 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 390:
#line 3113 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 8723 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 393:
#line 3123 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, (yyvsp[0].id));
                      new_bv(p, (yyvsp[0].id));
                    }
#line 8732 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 395:
#line 3131 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-2].nd);
                    }
#line 8740 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 396:
#line 3135 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8748 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 397:
#line 3141 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8756 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 398:
#line 3145 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8764 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 399:
#line 3151 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      nvars_nest(p);
                    }
#line 8773 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 400:
#line 3158 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block(p,(yyvsp[-2].nd),(yyvsp[-1].nd));
                      local_unnest(p);
                      nvars_unnest(p);
                    }
#line 8783 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 401:
#line 3166 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if (typen((yyvsp[-1].nd)->car) == NODE_YIELD) {
                        yyerror(p, "block given to yield");
                      }
                      else {
                        call_with_block(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                      }
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 8797 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 402:
#line 3176 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 8805 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 403:
#line 3180 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), (yyvsp[-3].num));
                      call_with_block(p, (yyval.nd), (yyvsp[0].nd));
                    }
#line 8814 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 404:
#line 3185 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-4].nd), (yyvsp[-2].id), (yyvsp[-1].nd), (yyvsp[-3].num));
                      call_with_block(p, (yyval.nd), (yyvsp[0].nd));
                    }
#line 8823 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 405:
#line 3192 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, (yyvsp[-1].id), (yyvsp[0].nd));
                    }
#line 8831 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 406:
#line 3196 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), (yyvsp[-2].num));
                    }
#line 8839 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 407:
#line 3200 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), (yyvsp[-1].id), (yyvsp[0].nd), tCOLON2);
                    }
#line 8847 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 408:
#line 3204 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), (yyvsp[0].id), 0, tCOLON2);
                    }
#line 8855 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 409:
#line 3208 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), MRB_SYM_2(p->mrb, call), (yyvsp[0].nd), (yyvsp[-1].num));
                    }
#line 8863 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 410:
#line 3212 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-2].nd), MRB_SYM_2(p->mrb, call), (yyvsp[0].nd), tCOLON2);
                    }
#line 8871 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 411:
#line 3216 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_super(p, (yyvsp[0].nd));
                    }
#line 8879 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 412:
#line 3220 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_zsuper(p);
                    }
#line 8887 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 413:
#line 3224 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_call(p, (yyvsp[-3].nd), intern_op(aref), (yyvsp[-1].nd), '.');
                    }
#line 8895 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 414:
#line 3230 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      nvars_nest(p);
                      (yyval.num) = p->lineno;
                    }
#line 8905 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 415:
#line 3237 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block(p,(yyvsp[-2].nd),(yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-3].num));
                      local_unnest(p);
                      nvars_unnest(p);
                    }
#line 8916 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 416:
#line 3244 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                      nvars_nest(p);
                      (yyval.num) = p->lineno;
                    }
#line 8926 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 417:
#line 3251 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_block(p,(yyvsp[-2].nd),(yyvsp[-1].nd));
                      SET_LINENO((yyval.nd), (yyvsp[-3].num));
                      local_unnest(p);
                      nvars_unnest(p);
                    }
#line 8937 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 418:
#line 3262 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(cons((yyvsp[-3].nd), (yyvsp[-1].nd)), (yyvsp[0].nd));
                    }
#line 8945 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 419:
#line 3268 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if ((yyvsp[0].nd)) {
                        (yyval.nd) = cons(cons(0, (yyvsp[0].nd)), 0);
                      }
                      else {
                        (yyval.nd) = 0;
                      }
                    }
#line 8958 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 421:
#line 3282 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(list3((yyvsp[-4].nd), (yyvsp[-3].nd), (yyvsp[-1].nd)));
                      if ((yyvsp[0].nd)) (yyval.nd) = append((yyval.nd), (yyvsp[0].nd));
                    }
#line 8967 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 423:
#line 3290 "mrbgems/mruby-compiler/core/parse.y"
                    {
                        (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 8975 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 426:
#line 3298 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8983 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 428:
#line 3305 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 8991 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 435:
#line 3319 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = concat_string(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 8999 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 438:
#line 3327 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 9007 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 439:
#line 3331 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *n = (yyvsp[-1].nd);
                      if (intn((yyvsp[0].nd)->cdr->cdr) > 0) {
                        n = push(n, (yyvsp[0].nd));
                      }
                      else {
                        cons_free((yyvsp[0].nd));
                      }
                      (yyval.nd) = new_dstr(p, n);
                    }
#line 9022 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 441:
#line 3345 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = append((yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9030 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 442:
#line 3351 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 9038 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 443:
#line 3355 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = p->lex_strterm;
                      p->lex_strterm = NULL;
                    }
#line 9047 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 444:
#line 3361 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lex_strterm = (yyvsp[-2].nd);
                      (yyval.nd) = list2((yyvsp[-3].nd), (yyvsp[-1].nd));
                    }
#line 9056 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 445:
#line 3366 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(new_literal_delim(p));
                    }
#line 9064 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 446:
#line 3370 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1(new_literal_delim(p));
                    }
#line 9072 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 447:
#line 3376 "mrbgems/mruby-compiler/core/parse.y"
                    {
                        (yyval.nd) = (yyvsp[0].nd);
                    }
#line 9080 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 448:
#line 3380 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *n = (yyvsp[-1].nd);
                      if (intn((yyvsp[0].nd)->cdr->cdr) > 0) {
                        n = push(n, (yyvsp[0].nd));
                      }
                      else {
                        cons_free((yyvsp[0].nd));
                      }
                      (yyval.nd) = new_dxstr(p, n);
                    }
#line 9095 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 449:
#line 3393 "mrbgems/mruby-compiler/core/parse.y"
                    {
                        (yyval.nd) = (yyvsp[0].nd);
                    }
#line 9103 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 450:
#line 3397 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_dregx(p, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9111 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 454:
#line 3410 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      parser_heredoc_info * inf = parsing_heredoc_inf(p);
                      inf->doc = push(inf->doc, new_str(p, "", 0));
                      heredoc_end(p);
                    }
#line 9121 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 455:
#line 3416 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      heredoc_end(p);
                    }
#line 9129 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 458:
#line 3426 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      parser_heredoc_info * inf = parsing_heredoc_inf(p);
                      inf->doc = push(inf->doc, (yyvsp[0].nd));
                      heredoc_treat_nextline(p);
                    }
#line 9139 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 459:
#line 3432 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = p->lex_strterm;
                      p->lex_strterm = NULL;
                    }
#line 9148 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 460:
#line 3438 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      parser_heredoc_info * inf = parsing_heredoc_inf(p);
                      p->lex_strterm = (yyvsp[-2].nd);
                      inf->doc = push(push(inf->doc, (yyvsp[-3].nd)), (yyvsp[-1].nd));
                    }
#line 9158 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 461:
#line 3446 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_words(p, list1((yyvsp[0].nd)));
                    }
#line 9166 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 462:
#line 3450 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *n = (yyvsp[-1].nd);
                      if (intn((yyvsp[0].nd)->cdr->cdr) > 0) {
                        n = push(n, (yyvsp[0].nd));
                      }
                      else {
                        cons_free((yyvsp[0].nd));
                      }
                      (yyval.nd) = new_words(p, n);
                    }
#line 9181 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 463:
#line 3464 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_ENDARG;
                      (yyval.nd) = new_sym(p, (yyvsp[0].id));
                    }
#line 9190 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 464:
#line 3469 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *n = (yyvsp[-1].nd);
                      p->lstate = EXPR_ENDARG;
                      if (intn((yyvsp[0].nd)->cdr->cdr) > 0) {
                        n = push(n, (yyvsp[0].nd));
                      }
                      else {
                        cons_free((yyvsp[0].nd));
                      }
                      (yyval.nd) = new_dsym(p, new_dstr(p, n));
                    }
#line 9206 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 465:
#line 3483 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 9214 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 470:
#line 3493 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = new_strsym(p, (yyvsp[0].nd));
                    }
#line 9222 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 471:
#line 3497 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = new_strsym(p, (yyvsp[0].nd));
                    }
#line 9230 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 472:
#line 3503 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_symbols(p, list1((yyvsp[0].nd)));
                    }
#line 9238 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 473:
#line 3507 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      node *n = (yyvsp[-1].nd);
                      if (intn((yyvsp[0].nd)->cdr->cdr) > 0) {
                        n = push(n, (yyvsp[0].nd));
                      }
                      (yyval.nd) = new_symbols(p, n);
                    }
#line 9250 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 476:
#line 3519 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, (yyvsp[0].nd));
                    }
#line 9258 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 477:
#line 3523 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_negate(p, (yyvsp[0].nd));
                    }
#line 9266 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 478:
#line 3529 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_lvar(p, (yyvsp[0].id));
                    }
#line 9274 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 479:
#line 3533 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_ivar(p, (yyvsp[0].id));
                    }
#line 9282 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 480:
#line 3537 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_gvar(p, (yyvsp[0].id));
                    }
#line 9290 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 481:
#line 3541 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_cvar(p, (yyvsp[0].id));
                    }
#line 9298 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 482:
#line 3545 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_const(p, (yyvsp[0].id));
                    }
#line 9306 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 483:
#line 3551 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      assignable(p, (yyvsp[0].nd));
                    }
#line 9314 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 484:
#line 3555 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "can't assign to numbered parameter");
                    }
#line 9322 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 485:
#line 3561 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = var_reference(p, (yyvsp[0].nd));
                    }
#line 9330 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 486:
#line 3565 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_nil(p);
                    }
#line 9338 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 487:
#line 3569 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_self(p);
                    }
#line 9346 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 488:
#line 3573 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_true(p);
                    }
#line 9354 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 489:
#line 3577 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_false(p);
                    }
#line 9362 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 490:
#line 3581 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      const char *fn = mrb_sym_name_len(p->mrb, p->filename_sym, NULL);
                      if (!fn) {
                        fn = "(null)";
                      }
                      (yyval.nd) = new_str(p, fn, strlen(fn));
                    }
#line 9374 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 491:
#line 3589 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      char buf[16];

                      dump_int(p->lineno, buf);
                      (yyval.nd) = new_int(p, buf, 10, 0);
                    }
#line 9385 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 492:
#line 3596 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_fcall(p, MRB_SYM_2(p->mrb, __ENCODING__), 0);
                    }
#line 9393 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 495:
#line 3606 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 9401 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 496:
#line 3610 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lstate = EXPR_BEG;
                      p->cmd_start = TRUE;
                    }
#line 9410 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 497:
#line 3615 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 9418 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 500:
#line 3631 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                      p->lstate = EXPR_BEG;
                      p->cmd_start = TRUE;
                    }
#line 9428 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 501:
#line 3637 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_dots(p, (yyvsp[-3].nd));
                    }
#line 9436 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 502:
#line 3641 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_dots(p, 0);
                    }
#line 9444 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 504:
#line 3648 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 9452 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 505:
#line 3652 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_dots(p, (yyvsp[-3].nd));
                    }
#line 9460 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 506:
#line 3656 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_dots(p, 0);
                    }
#line 9468 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 507:
#line 3662 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_nest(p);
                    }
#line 9476 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 508:
#line 3668 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = new_kw_arg(p, (yyvsp[-1].id), cons((yyvsp[0].nd), locals_node(p)));
                      local_unnest(p);
                    }
#line 9486 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 509:
#line 3674 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_kw_arg(p, (yyvsp[0].id), 0);
                      local_unnest(p);
                    }
#line 9495 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 510:
#line 3681 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = new_kw_arg(p, (yyvsp[-1].id), cons((yyvsp[0].nd), locals_node(p)));
                      local_unnest(p);
                    }
#line 9505 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 511:
#line 3687 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_kw_arg(p, (yyvsp[0].id), 0);
                      local_unnest(p);
                    }
#line 9514 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 512:
#line 3694 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 9522 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 513:
#line 3698 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 9530 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 514:
#line 3704 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 9538 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 515:
#line 3708 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 9546 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 518:
#line 3718 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_kw_rest_args(p, nsym((yyvsp[0].id)));
                    }
#line 9554 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 519:
#line 3722 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_kw_rest_args(p, 0);
                    }
#line 9562 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 520:
#line 3728 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, (yyvsp[-3].nd), (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 9570 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 521:
#line 3732 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, (yyvsp[-1].nd), 0, (yyvsp[0].id));
                    }
#line 9578 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 522:
#line 3736 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, (yyvsp[-1].nd), (yyvsp[0].id));
                    }
#line 9586 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 523:
#line 3740 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, 0, (yyvsp[0].id));
                    }
#line 9594 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 524:
#line 3746 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                    }
#line 9602 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 525:
#line 3750 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args_tail(p, 0, 0, 0);
                    }
#line 9610 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 526:
#line 3756 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 9618 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 527:
#line 3760 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-7].nd), (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9626 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 528:
#line 3764 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), (yyvsp[-1].nd), 0, 0, (yyvsp[0].nd));
                    }
#line 9634 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 529:
#line 3768 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9642 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 530:
#line 3772 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-3].nd), 0, (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 9650 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 531:
#line 3776 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-5].nd), 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9658 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 532:
#line 3780 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, (yyvsp[-1].nd), 0, 0, 0, (yyvsp[0].nd));
                    }
#line 9666 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 533:
#line 3784 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 9674 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 534:
#line 3788 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-5].nd), (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9682 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 535:
#line 3792 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-1].nd), 0, 0, (yyvsp[0].nd));
                    }
#line 9690 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 536:
#line 3796 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, (yyvsp[-3].nd), 0, (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9698 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 537:
#line 3800 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-1].id), 0, (yyvsp[0].nd));
                    }
#line 9706 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 538:
#line 3804 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, (yyvsp[-3].id), (yyvsp[-1].nd), (yyvsp[0].nd));
                    }
#line 9714 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 539:
#line 3808 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_args(p, 0, 0, 0, 0, (yyvsp[0].nd));
                    }
#line 9722 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 540:
#line 3812 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, intern_op(and));
                      (yyval.nd) = new_args(p, 0, 0, 0, 0, 0);
                    }
#line 9731 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 541:
#line 3819 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "formal argument cannot be a constant");
                      (yyval.nd) = 0;
                    }
#line 9740 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 542:
#line 3824 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "formal argument cannot be an instance variable");
                      (yyval.nd) = 0;
                    }
#line 9749 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 543:
#line 3829 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "formal argument cannot be a global variable");
                      (yyval.nd) = 0;
                    }
#line 9758 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 544:
#line 3834 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "formal argument cannot be a class variable");
                      (yyval.nd) = 0;
                    }
#line 9767 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 545:
#line 3839 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      yyerror(p, "formal argument cannot be a numbered parameter");
                      (yyval.nd) = 0;
                    }
#line 9776 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 546:
#line 3846 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = 0;
                    }
#line 9784 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 547:
#line 3850 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, (yyvsp[0].id));
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 9793 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 548:
#line 3857 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_arg(p, (yyvsp[0].id));
                    }
#line 9801 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 549:
#line 3861 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = local_switch(p);
                    }
#line 9809 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 550:
#line 3865 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = new_masgn_param(p, (yyvsp[-1].nd), p->locals->car);
                      local_resume(p, (yyvsp[-2].nd));
                    }
#line 9818 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 551:
#line 3872 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 9826 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 552:
#line 3876 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 9834 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 553:
#line 3882 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, (yyvsp[-1].id));
                      local_nest(p);
                      (yyval.id) = (yyvsp[-1].id);
                    }
#line 9844 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 554:
#line 3890 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons(nsym((yyvsp[-1].id)), cons((yyvsp[0].nd), locals_node(p)));
                      local_unnest(p);
                    }
#line 9854 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 555:
#line 3898 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons(nsym((yyvsp[-1].id)), cons((yyvsp[0].nd), locals_node(p)));
                      local_unnest(p);
                    }
#line 9864 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 556:
#line 3906 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 9872 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 557:
#line 3910 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 9880 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 558:
#line 3916 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                    }
#line 9888 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 559:
#line 3920 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 9896 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 562:
#line 3930 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      local_add_f(p, (yyvsp[0].id));
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 9905 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 563:
#line 3935 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = intern_op(mul);
                      local_add_f(p, (yyval.id));
                    }
#line 9914 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 566:
#line 3946 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 9922 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 567:
#line 3950 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = intern_op(and);
                    }
#line 9930 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 568:
#line 3956 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = (yyvsp[0].id);
                    }
#line 9938 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 569:
#line 3960 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.id) = 0;
                    }
#line 9946 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 570:
#line 3966 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[0].nd);
                      if (!(yyval.nd)) (yyval.nd) = new_nil(p);
                    }
#line 9955 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 571:
#line 3970 "mrbgems/mruby-compiler/core/parse.y"
                      {p->lstate = EXPR_BEG;}
#line 9961 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 572:
#line 3971 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      if ((yyvsp[-1].nd) == 0) {
                        yyerror(p, "can't define singleton method for ().");
                      }
                      else {
                        switch (typen((yyvsp[-1].nd)->car)) {
                        case NODE_STR:
                        case NODE_DSTR:
                        case NODE_XSTR:
                        case NODE_DXSTR:
                        case NODE_DREGX:
                        case NODE_MATCH:
                        case NODE_FLOAT:
                        case NODE_ARRAY:
                        case NODE_HEREDOC:
                          yyerror(p, "can't define singleton method for literals");
                        default:
                          break;
                        }
                      }
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 9988 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 574:
#line 3997 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = (yyvsp[-1].nd);
                    }
#line 9996 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 575:
#line 4003 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = list1((yyvsp[0].nd));
                      NODE_LINENO((yyval.nd), (yyvsp[0].nd));
                    }
#line 10005 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 576:
#line 4008 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = push((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 10013 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 577:
#line 4014 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[-2].nd));
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons((yyvsp[-2].nd), (yyvsp[0].nd));
                    }
#line 10023 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 578:
#line 4020 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons(new_sym(p, (yyvsp[-2].id)), (yyvsp[0].nd));
                    }
#line 10032 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 579:
#line 4025 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = cons(new_sym(p, (yyvsp[-1].id)), label_reference(p, (yyvsp[-1].id)));
                    }
#line 10040 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 580:
#line 4029 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      if (typen((yyvsp[-2].nd)->car) == NODE_DSTR) {
                        (yyval.nd) = cons(new_dsym(p, (yyvsp[-2].nd)), (yyvsp[0].nd));
                      }
                      else {
                        (yyval.nd) = cons(new_sym(p, new_strsym(p, (yyvsp[-2].nd))), (yyvsp[0].nd));
                      }
                    }
#line 10054 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 581:
#line 4039 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      void_expr_error(p, (yyvsp[0].nd));
                      (yyval.nd) = cons(new_kw_rest_args(p, 0), (yyvsp[0].nd));
                    }
#line 10063 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 594:
#line 4066 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.num) = '.';
                    }
#line 10071 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 595:
#line 4070 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.num) = 0;
                    }
#line 10079 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 597:
#line 4077 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.num) = tCOLON2;
                    }
#line 10087 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 606:
#line 4098 "mrbgems/mruby-compiler/core/parse.y"
                      {yyerrok;}
#line 10093 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 608:
#line 4103 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      p->lineno += (yyvsp[0].num);
                      p->column = 0;
                    }
#line 10102 "mrbgems/mruby-compiler/core/y.tab.c"
    break;

  case 612:
#line 4115 "mrbgems/mruby-compiler/core/parse.y"
                    {
                      (yyval.nd) = 0;
                    }
#line 10110 "mrbgems/mruby-compiler/core/y.tab.c"
    break;


#line 10114 "mrbgems/mruby-compiler/core/y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (p, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (p, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, p);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, p);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (p, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, p);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, p);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 4119 "mrbgems/mruby-compiler/core/parse.y"

#define pylval  (*((YYSTYPE*)(p->ylval)))

static void
yyerror(parser_state *p, const char *s)
{
  char* c;
  size_t n;

  if (! p->capture_errors) {
#ifndef MRB_NO_STDIO
    if (p->filename_sym) {
      const char *filename = mrb_sym_name_len(p->mrb, p->filename_sym, NULL);
      fprintf(stderr, "%s:%d:%d: %s\n", filename, p->lineno, p->column, s);
    }
    else {
      fprintf(stderr, "line %d:%d: %s\n", p->lineno, p->column, s);
    }
#endif
  }
  else if (p->nerr < sizeof(p->error_buffer) / sizeof(p->error_buffer[0])) {
    n = strlen(s);
    c = (char *)parser_palloc(p, n + 1);
    memcpy(c, s, n + 1);
    p->error_buffer[p->nerr].message = c;
    p->error_buffer[p->nerr].lineno = p->lineno;
    p->error_buffer[p->nerr].column = p->column;
  }
  p->nerr++;
}

static void
yyerror_c(parser_state *p, const char *msg, char c)
{
  char buf[256];

  strncpy(buf, msg, sizeof(buf) - 2);
  buf[sizeof(buf) - 2] = '\0';
  strncat(buf, &c, 1);
  yyerror(p, buf);
}

static void
yywarning(parser_state *p, const char *s)
{
  char* c;
  size_t n;

  if (! p->capture_errors) {
#ifndef MRB_NO_STDIO
    if (p->filename_sym) {
      const char *filename = mrb_sym_name_len(p->mrb, p->filename_sym, NULL);
      fprintf(stderr, "%s:%d:%d: warning: %s\n", filename, p->lineno, p->column, s);
    }
    else {
      fprintf(stderr, "line %d:%d: warning: %s\n", p->lineno, p->column, s);
    }
#endif
  }
  else if (p->nwarn < sizeof(p->warn_buffer) / sizeof(p->warn_buffer[0])) {
    n = strlen(s);
    c = (char *)parser_palloc(p, n + 1);
    memcpy(c, s, n + 1);
    p->warn_buffer[p->nwarn].message = c;
    p->warn_buffer[p->nwarn].lineno = p->lineno;
    p->warn_buffer[p->nwarn].column = p->column;
  }
  p->nwarn++;
}

static void
yywarning_s(parser_state *p, const char *msg, const char *s)
{
  char buf[256];

  strncpy(buf, msg, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';
  strncat(buf, ": ", sizeof(buf) - strlen(buf) - 1);
  strncat(buf, s, sizeof(buf) - strlen(buf) - 1);
  yywarning(p, buf);
}

static void
backref_error(parser_state *p, node *n)
{
  int c;

  c = intn(n->car);

  if (c == NODE_NTH_REF) {
    yyerror_c(p, "can't set variable $", (char)intn(n->cdr)+'0');
  }
  else if (c == NODE_BACK_REF) {
    yyerror_c(p, "can't set variable $", (char)intn(n->cdr));
  }
  else {
    mrb_bug(p->mrb, "Internal error in backref_error() : n=>car == %d", c);
  }
}

static void
void_expr_error(parser_state *p, node *n)
{
  int c;

  if (n == NULL) return;
  c = intn(n->car);
  switch (c) {
  case NODE_BREAK:
  case NODE_RETURN:
  case NODE_NEXT:
  case NODE_REDO:
  case NODE_RETRY:
    yyerror(p, "void value expression");
    break;
  case NODE_AND:
  case NODE_OR:
    if (n->cdr) {
      void_expr_error(p, n->cdr->car);
      void_expr_error(p, n->cdr->cdr);
    }
    break;
  case NODE_BEGIN:
    if (n->cdr) {
      while (n->cdr) {
        n = n->cdr;
      }
      void_expr_error(p, n->car);
    }
    break;
  default:
    break;
  }
}

static void pushback(parser_state *p, int c);
static mrb_bool peeks(parser_state *p, const char *s);
static mrb_bool skips(parser_state *p, const char *s);

static inline int
nextc0(parser_state *p)
{
  int c;

  if (p->s && p->s < p->send) {
    c = (unsigned char)*p->s++;
  }
  else {
#ifndef MRB_NO_STDIO
    if (p->f) {
      c = fgetc(p->f);
      if (feof(p->f)) return -1;
    }
    else
#endif
      return -1;
  }
  return c;
}

static inline int
nextc(parser_state *p)
{
  int c;

  if (p->pb) {
    node *tmp;

    c = intn(p->pb->car);
    tmp = p->pb;
    p->pb = p->pb->cdr;
    cons_free(tmp);
  }
  else {
    c = nextc0(p);
    if (c < 0) goto eof;
  }
  if (c >= 0) {
    p->column++;
  }
  if (c == '\r') {
    const int lf = nextc0(p);
    if (lf == '\n') {
      return '\n';
    }
    if (lf > 0) pushback(p, lf);
  }
  return c;

  eof:
  if (!p->cxt) return -1;
  else {
    if (p->cxt->partial_hook(p) < 0)
      return -1;                /* end of program(s) */
    return -2;                  /* end of a file in the program files */
  }
}

static void
pushback(parser_state *p, int c)
{
  if (c >= 0) {
    p->column--;
  }
  p->pb = cons(nint(c), p->pb);
}

static void
skip(parser_state *p, char term)
{
  int c;

  for (;;) {
    c = nextc(p);
    if (c < 0) break;
    if (c == term) break;
  }
}

static int
peekc_n(parser_state *p, int n)
{
  node *list = 0;
  int c0;

  do {
    c0 = nextc(p);
    if (c0 == -1) return c0;    /* do not skip partial EOF */
    if (c0 >= 0) --p->column;
    list = push(list, nint(c0));
  } while(n--);
  if (p->pb) {
    p->pb = append(list, p->pb);
  }
  else {
    p->pb = list;
  }
  return c0;
}

static mrb_bool
peek_n(parser_state *p, int c, int n)
{
  return peekc_n(p, n) == c && c >= 0;
}
#define peek(p,c) peek_n((p), (c), 0)

static mrb_bool
peeks(parser_state *p, const char *s)
{
  size_t len = strlen(s);

#ifndef MRB_NO_STDIO
  if (p->f) {
    int n = 0;
    while (*s) {
      if (!peek_n(p, *s++, n++)) return FALSE;
    }
    return TRUE;
  }
  else
#endif
    if (p->s && p->s + len <= p->send) {
      if (memcmp(p->s, s, len) == 0) return TRUE;
    }
  return FALSE;
}

static mrb_bool
skips(parser_state *p, const char *s)
{
  int c;

  for (;;) {
    /* skip until first char */
    for (;;) {
      c = nextc(p);
      if (c < 0) return FALSE;
      if (c == '\n') {
        p->lineno++;
        p->column = 0;
      }
      if (c == *s) break;
    }
    s++;
    if (peeks(p, s)) {
      size_t len = strlen(s);

      while (len--) {
        if (nextc(p) == '\n') {
          p->lineno++;
          p->column = 0;
        }
      }
      return TRUE;
    }
    else{
      s--;
    }
  }
  return FALSE;
}


static int
newtok(parser_state *p)
{
  if (p->tokbuf != p->buf) {
    mrb_free(p->mrb, p->tokbuf);
    p->tokbuf = p->buf;
    p->tsiz = MRB_PARSER_TOKBUF_SIZE;
  }
  p->tidx = 0;
  return p->column - 1;
}

static void
tokadd(parser_state *p, int32_t c)
{
  char utf8[4];
  int i, len;

  /* mrb_assert(-0x10FFFF <= c && c <= 0xFF); */
  if (c >= 0) {
    /* Single byte from source or non-Unicode escape */
    utf8[0] = (char)c;
    len = 1;
  }
  else {
    /* Unicode character */
    c = -c;
    if (c < 0x80) {
      utf8[0] = (char)c;
      len = 1;
    }
    else if (c < 0x800) {
      utf8[0] = (char)(0xC0 | (c >> 6));
      utf8[1] = (char)(0x80 | (c & 0x3F));
      len = 2;
    }
    else if (c < 0x10000) {
      utf8[0] = (char)(0xE0 |  (c >> 12)        );
      utf8[1] = (char)(0x80 | ((c >>  6) & 0x3F));
      utf8[2] = (char)(0x80 | ( c        & 0x3F));
      len = 3;
    }
    else {
      utf8[0] = (char)(0xF0 |  (c >> 18)        );
      utf8[1] = (char)(0x80 | ((c >> 12) & 0x3F));
      utf8[2] = (char)(0x80 | ((c >>  6) & 0x3F));
      utf8[3] = (char)(0x80 | ( c        & 0x3F));
      len = 4;
    }
  }
  if (p->tidx+len >= p->tsiz) {
    if (p->tsiz >= MRB_PARSER_TOKBUF_MAX) {
      p->tidx += len;
      return;
    }
    p->tsiz *= 2;
    if (p->tokbuf == p->buf) {
      p->tokbuf = (char*)mrb_malloc(p->mrb, p->tsiz);
      memcpy(p->tokbuf, p->buf, MRB_PARSER_TOKBUF_SIZE);
    }
    else {
      p->tokbuf = (char*)mrb_realloc(p->mrb, p->tokbuf, p->tsiz);
    }
  }
  for (i = 0; i < len; i++) {
    p->tokbuf[p->tidx++] = utf8[i];
  }
}

static int
toklast(parser_state *p)
{
  return p->tokbuf[p->tidx-1];
}

static void
tokfix(parser_state *p)
{
  if (p->tidx >= MRB_PARSER_TOKBUF_MAX) {
    p->tidx = MRB_PARSER_TOKBUF_MAX-1;
    yyerror(p, "string too long (truncated)");
  }
  p->tokbuf[p->tidx] = '\0';
}

static const char*
tok(parser_state *p)
{
  return p->tokbuf;
}

static int
toklen(parser_state *p)
{
  return p->tidx;
}

#define IS_ARG() (p->lstate == EXPR_ARG || p->lstate == EXPR_CMDARG)
#define IS_END() (p->lstate == EXPR_END || p->lstate == EXPR_ENDARG || p->lstate == EXPR_ENDFN)
#define IS_BEG() (p->lstate == EXPR_BEG || p->lstate == EXPR_MID || p->lstate == EXPR_VALUE || p->lstate == EXPR_CLASS)
#define IS_SPCARG(c) (IS_ARG() && space_seen && !ISSPACE(c))
#define IS_LABEL_POSSIBLE() ((p->lstate == EXPR_BEG && !cmd_state) || IS_ARG())
#define IS_LABEL_SUFFIX(n) (peek_n(p, ':',(n)) && !peek_n(p, ':', (n)+1))

static int32_t
scan_oct(const int *start, int len, int *retlen)
{
  const int *s = start;
  int32_t retval = 0;

  /* mrb_assert(len <= 3) */
  while (len-- && *s >= '0' && *s <= '7') {
    retval <<= 3;
    retval |= *s++ - '0';
  }
  *retlen = (int)(s - start);

  return retval;
}

static int32_t
scan_hex(parser_state *p, const int *start, int len, int *retlen)
{
  static const char hexdigit[] = "0123456789abcdef0123456789ABCDEF";
  const int *s = start;
  uint32_t retval = 0;
  char *tmp;

  /* mrb_assert(len <= 8) */
  while (len-- && *s && (tmp = (char*)strchr(hexdigit, *s))) {
    retval <<= 4;
    retval |= (tmp - hexdigit) & 15;
    s++;
  }
  *retlen = (int)(s - start);

  return (int32_t)retval;
}

static int32_t
read_escape_unicode(parser_state *p, int limit)
{
  int buf[9];
  int i;
  int32_t hex;

  /* Look for opening brace */
  i = 0;
  buf[0] = nextc(p);
  if (buf[0] < 0) {
  eof:
    yyerror(p, "invalid escape character syntax");
    return -1;
  }
  if (ISXDIGIT(buf[0])) {
    /* \uxxxx form */
    for (i=1; i<limit; i++) {
      buf[i] = nextc(p);
      if (buf[i] < 0) goto eof;
      if (!ISXDIGIT(buf[i])) {
        pushback(p, buf[i]);
        break;
      }
    }
  }
  else {
    pushback(p, buf[0]);
  }
  hex = scan_hex(p, buf, i, &i);
  if (i == 0 || hex > 0x10FFFF || (hex & 0xFFFFF800) == 0xD800) {
    yyerror(p, "invalid Unicode code point");
    return -1;
  }
  return hex;
}

/* Return negative to indicate Unicode code point */
static int32_t
read_escape(parser_state *p)
{
  int32_t c;

  switch (c = nextc(p)) {
  case '\\':/* Backslash */
    return c;

  case 'n':/* newline */
    return '\n';

  case 't':/* horizontal tab */
    return '\t';

  case 'r':/* carriage-return */
    return '\r';

  case 'f':/* form-feed */
    return '\f';

  case 'v':/* vertical tab */
    return '\13';

  case 'a':/* alarm(bell) */
    return '\007';

  case 'e':/* escape */
    return 033;

  case '0': case '1': case '2': case '3': /* octal constant */
  case '4': case '5': case '6': case '7':
  {
    int buf[3];
    int i;

    buf[0] = c;
    for (i=1; i<3; i++) {
      buf[i] = nextc(p);
      if (buf[i] < 0) goto eof;
      if (buf[i] < '0' || '7' < buf[i]) {
        pushback(p, buf[i]);
        break;
      }
    }
    c = scan_oct(buf, i, &i);
  }
  return c;

  case 'x':     /* hex constant */
  {
    int buf[2];
    int i;

    for (i=0; i<2; i++) {
      buf[i] = nextc(p);
      if (buf[i] < 0) goto eof;
      if (!ISXDIGIT(buf[i])) {
        pushback(p, buf[i]);
        break;
      }
    }
    if (i == 0) {
      yyerror(p, "invalid hex escape");
      return -1;
    }
    return scan_hex(p, buf, i, &i);
  }

  case 'u':     /* Unicode */
    if (peek(p, '{')) {
      /* \u{xxxxxxxx} form */
      nextc(p);
      c = read_escape_unicode(p, 8);
      if (c < 0) return 0;
      if (nextc(p) != '}') goto eof;
    }
    else {
      c = read_escape_unicode(p, 4);
      if (c < 0) return 0;
    }
  return -c;

  case 'b':/* backspace */
    return '\010';

  case 's':/* space */
    return ' ';

  case 'M':
    if ((c = nextc(p)) != '-') {
      yyerror(p, "Invalid escape character syntax");
      pushback(p, c);
      return '\0';
    }
    if ((c = nextc(p)) == '\\') {
      return read_escape(p) | 0x80;
    }
    else if (c < 0) goto eof;
    else {
      return ((c & 0xff) | 0x80);
    }

  case 'C':
    if ((c = nextc(p)) != '-') {
      yyerror(p, "Invalid escape character syntax");
      pushback(p, c);
      return '\0';
    }
  case 'c':
    if ((c = nextc(p))== '\\') {
      c = read_escape(p);
    }
    else if (c == '?')
      return 0177;
    else if (c < 0) goto eof;
    return c & 0x9f;

    eof:
  case -1:
  case -2:                      /* end of a file */
    yyerror(p, "Invalid escape character syntax");
    return '\0';

  default:
    return c;
  }
}

static void
heredoc_count_indent(parser_heredoc_info *hinf, const char *str, size_t len, size_t spaces, size_t *offset)
{
  size_t indent = 0;
  *offset = 0;
  for (size_t i = 0; i < len; i++) {
    size_t size;
    if (str[i] == '\n')
      break;
    else if (str[i] == '\t')
      size = 8;
    else if (ISSPACE(str[i]))
      size = 1;
    else
      break;
    size_t nindent = indent + size;
    if (nindent > spaces || nindent > hinf->indent)
      break;
    indent = nindent;
    *offset += 1;
  }
}

static void
heredoc_remove_indent(parser_state *p, parser_heredoc_info *hinf)
{
  if (!hinf->remove_indent || hinf->indent == 0)
    return;
  node *indented, *n, *pair, *escaped, *nspaces;
  const char *str;
  size_t len, spaces, offset, start, end;
  indented = hinf->indented;
  while (indented) {
    n = indented->car;
    pair = n->car;
    str = (char*)pair->car;
    len = (size_t)pair->cdr;
    escaped = n->cdr->car;
    nspaces = n->cdr->cdr;
    if (escaped) {
      char *newstr = strndup(str, len);
      size_t newlen = 0;
      start = 0;
      while (start < len) {
        end = escaped ? (size_t)escaped->car : len;
        if (end > len) end = len;
        spaces = (size_t)nspaces->car;
        size_t esclen = end - start;
        heredoc_count_indent(hinf, str + start, esclen, spaces, &offset);
        esclen -= offset;
        memcpy(newstr + newlen, str + start + offset, esclen);
        newlen += esclen;
        start = end;
        if (escaped)
          escaped = escaped->cdr;
        nspaces = nspaces->cdr;
      }
      if (newlen < len)
        newstr[newlen] = '\0';
      pair->car = (node*)newstr;
      pair->cdr = (node*)newlen;
    } else {
      spaces = (size_t)nspaces->car;
      heredoc_count_indent(hinf, str, len, spaces, &offset);
      pair->car = (node*)(str + offset);
      pair->cdr = (node*)(len - offset);
    }
    indented = indented->cdr;
  }
}

static void
heredoc_push_indented(parser_state *p, parser_heredoc_info *hinf, node *pair, node *escaped, node *nspaces, mrb_bool empty_line)
{
  hinf->indented = push(hinf->indented, cons(pair, cons(escaped, nspaces)));
  while (nspaces) {
    size_t tspaces = (size_t)nspaces->car;
    if ((hinf->indent == ~0U || tspaces < hinf->indent) && !empty_line)
      hinf->indent = tspaces;
    nspaces = nspaces->cdr;
  }
}

static int
parse_string(parser_state *p)
{
  int c;
  string_type type = (string_type)(intptr_t)p->lex_strterm->car;
  int nest_level = intn(p->lex_strterm->cdr->car);
  int beg = intn(p->lex_strterm->cdr->cdr->car);
  int end = intn(p->lex_strterm->cdr->cdr->cdr);
  parser_heredoc_info *hinf = (type & STR_FUNC_HEREDOC) ? parsing_heredoc_inf(p) : NULL;

  mrb_bool unindent = hinf && hinf->remove_indent;
  mrb_bool head = hinf && hinf->line_head;
  mrb_bool empty = TRUE;
  size_t spaces = 0;
  size_t pos = -1;
  node *escaped = NULL;
  node *nspaces = NULL;

  if (beg == 0) beg = -3;       /* should never happen */
  if (end == 0) end = -3;
  newtok(p);
  while ((c = nextc(p)) != end || nest_level != 0) {
    pos++;
    if (hinf && (c == '\n' || c < 0)) {
      mrb_bool line_head;
      tokadd(p, '\n');
      tokfix(p);
      p->lineno++;
      p->column = 0;
      line_head = hinf->line_head;
      hinf->line_head = TRUE;
      if (line_head) {
        /* check whether end of heredoc */
        const char *s = tok(p);
        int len = toklen(p);
        if (hinf->allow_indent) {
          while (ISSPACE(*s) && len > 0) {
            ++s;
            --len;
          }
        }
        if ((len-1 == hinf->term_len) && (strncmp(s, hinf->term, len-1) == 0)) {
          heredoc_remove_indent(p, hinf);
          return tHEREDOC_END;
        }
      }
      if (c < 0) {
        char buf[256];
        const char s1[] = "can't find heredoc delimiter \"";
        const char s2[] = "\" anywhere before EOF";

        if (sizeof(s1)+sizeof(s2)+strlen(hinf->term)+1 >= sizeof(buf)) {
          yyerror(p, "can't find heredoc delimiter anywhere before EOF");
        } else {
          strcpy(buf, s1);
          strcat(buf, hinf->term);
          strcat(buf, s2);
          yyerror(p, buf);
        }
        return 0;
      }
      node *nd = new_str(p, tok(p), toklen(p));
      pylval.nd = nd;
      if (unindent && head) {
        nspaces = push(nspaces, nint(spaces));
        heredoc_push_indented(p, hinf, nd->cdr, escaped, nspaces, empty && line_head);
      }
      return tHD_STRING_MID;
    }
    if (unindent && empty) {
      if (c == '\t')
        spaces += 8;
      else if (ISSPACE(c))
        ++spaces;
      else
        empty = FALSE;
    }
    if (c < 0) {
      yyerror(p, "unterminated string meets end of file");
      return 0;
    }
    else if (c == beg) {
      nest_level++;
      p->lex_strterm->cdr->car = nint(nest_level);
    }
    else if (c == end) {
      nest_level--;
      p->lex_strterm->cdr->car = nint(nest_level);
    }
    else if (c == '\\') {
      c = nextc(p);
      if (type & STR_FUNC_EXPAND) {
        if (c == end || c == beg) {
          tokadd(p, c);
        }
        else if (c == '\n') {
          p->lineno++;
          p->column = 0;
          if (unindent) {
            nspaces = push(nspaces, nint(spaces));
            escaped = push(escaped, nint(pos));
            pos--;
            empty = TRUE;
            spaces = 0;
          }
          if (type & STR_FUNC_ARRAY) {
            tokadd(p, '\n');
          }
        }
        else if (type & STR_FUNC_REGEXP) {
          tokadd(p, '\\');
          tokadd(p, c);
        }
        else if (c == 'u' && peek(p, '{')) {
          /* \u{xxxx xxxx xxxx} form */
          nextc(p);
          while (1) {
            do c = nextc(p); while (ISSPACE(c));
            if (c == '}') break;
            pushback(p, c);
            c = read_escape_unicode(p, 8);
            if (c < 0) break;
            tokadd(p, -c);
          }
          if (hinf)
            hinf->line_head = FALSE;
        }
        else {
          pushback(p, c);
          tokadd(p, read_escape(p));
          if (hinf)
            hinf->line_head = FALSE;
        }
      }
      else {
        if (c != beg && c != end) {
          if (c == '\n') {
            p->lineno++;
            p->column = 0;
          }
          if (!(c == '\\' || ((type & STR_FUNC_ARRAY) && ISSPACE(c)))) {
            tokadd(p, '\\');
          }
        }
        tokadd(p, c);
      }
      continue;
    }
    else if ((c == '#') && (type & STR_FUNC_EXPAND)) {
      c = nextc(p);
      if (c == '{') {
        tokfix(p);
        p->lstate = EXPR_BEG;
        p->cmd_start = TRUE;
        node *nd = new_str(p, tok(p), toklen(p));
        pylval.nd = nd;
        if (hinf) {
          if (unindent && head) {
            nspaces = push(nspaces, nint(spaces));
            heredoc_push_indented(p, hinf, nd->cdr, escaped, nspaces, FALSE);
          }
          hinf->line_head = FALSE;
          return tHD_STRING_PART;
        }
        return tSTRING_PART;
      }
      tokadd(p, '#');
      pushback(p, c);
      continue;
    }
    if ((type & STR_FUNC_ARRAY) && ISSPACE(c)) {
      if (toklen(p) == 0) {
        do {
          if (c == '\n') {
            p->lineno++;
            p->column = 0;
            heredoc_treat_nextline(p);
            if (p->parsing_heredoc != NULL) {
              return tHD_LITERAL_DELIM;
            }
          }
          c = nextc(p);
        } while (ISSPACE(c));
        pushback(p, c);
        return tLITERAL_DELIM;
      }
      else {
        pushback(p, c);
        tokfix(p);
        pylval.nd = new_str(p, tok(p), toklen(p));
        return tSTRING_MID;
      }
    }
    if (c == '\n') {
      p->lineno++;
      p->column = 0;
    }
    tokadd(p, c);
  }

  tokfix(p);
  p->lstate = EXPR_ENDARG;
  end_strterm(p);

  if (type & STR_FUNC_XQUOTE) {
    pylval.nd = new_xstr(p, tok(p), toklen(p));
    return tXSTRING;
  }

  if (type & STR_FUNC_REGEXP) {
    int f = 0;
    int re_opt;
    char *s = strndup(tok(p), toklen(p));
    char flags[3];
    char *flag = flags;
    char enc = '\0';
    char *encp;
    char *dup;

    newtok(p);
    while (re_opt = nextc(p), re_opt >= 0 && ISALPHA(re_opt)) {
      switch (re_opt) {
      case 'i': f |= 1; break;
      case 'x': f |= 2; break;
      case 'm': f |= 4; break;
      case 'u': f |= 16; break;
      case 'n': f |= 32; break;
      case 'o': break;
      default: tokadd(p, re_opt); break;
      }
    }
    pushback(p, re_opt);
    if (toklen(p)) {
      char msg[128];

      strcpy(msg, "unknown regexp option");
      tokfix(p);
      if (toklen(p) > 1) {
        strcat(msg, "s");
      }
      strcat(msg, " - ");
      strncat(msg, tok(p), sizeof(msg) - strlen(msg) - 1);
      yyerror(p, msg);
    }
    if (f != 0) {
      if (f & 1) *flag++ = 'i';
      if (f & 2) *flag++ = 'x';
      if (f & 4) *flag++ = 'm';
      if (f & 16) enc = 'u';
      if (f & 32) enc = 'n';
    }
    if (flag > flags) {
      dup = strndup(flags, (size_t)(flag - flags));
    }
    else {
      dup = NULL;
    }
    if (enc) {
      encp = strndup(&enc, 1);
    }
    else {
      encp = NULL;
    }
    pylval.nd = new_regx(p, s, dup, encp);

    return tREGEXP;
  }
  pylval.nd = new_str(p, tok(p), toklen(p));

  return tSTRING;
}

static int
number_literal_suffix(parser_state *p)
{
  int c, result = 0;
  node *list = 0;
  int column = p->column;
  int mask = NUM_SUFFIX_R|NUM_SUFFIX_I;

  while ((c = nextc(p)) != -1) {
    list = push(list, nint(c));

    if ((mask & NUM_SUFFIX_I) && c == 'i') {
      result |= (mask & NUM_SUFFIX_I);
      mask &= ~NUM_SUFFIX_I;
      /* r after i, rational of complex is disallowed */
      mask &= ~NUM_SUFFIX_R;
      continue;
    }
    if ((mask & NUM_SUFFIX_R) && c == 'r') {
      result |= (mask & NUM_SUFFIX_R);
      mask &= ~NUM_SUFFIX_R;
      continue;
    }
    if (!ISASCII(c) || ISALPHA(c) || c == '_') {
      p->column = column;
      if (p->pb) {
        p->pb = append(list, p->pb);
      }
      else {
        p->pb = list;
      }
      return 0;
    }
    pushback(p, c);
    break;
  }
  return result;
}

static int
heredoc_identifier(parser_state *p)
{
  int c;
  int type = str_heredoc;
  mrb_bool indent = FALSE;
  mrb_bool squiggly = FALSE;
  mrb_bool quote = FALSE;
  node *newnode;
  parser_heredoc_info *info;

  c = nextc(p);
  if (ISSPACE(c) || c == '=') {
    pushback(p, c);
    return 0;
  }
  if (c == '-' || c == '~') {
    if (c == '-')
      indent = TRUE;
    if (c == '~')
      squiggly = TRUE;
    c = nextc(p);
  }
  if (c == '\'' || c == '"') {
    int term = c;
    if (c == '\'')
      quote = TRUE;
    newtok(p);
    while ((c = nextc(p)) >= 0 && c != term) {
      if (c == '\n') {
        c = -1;
        break;
      }
      tokadd(p, c);
    }
    if (c < 0) {
      yyerror(p, "unterminated here document identifier");
      return 0;
    }
  }
  else {
    if (c < 0) {
      return 0;                 /* missing here document identifier */
    }
    if (! identchar(c)) {
      pushback(p, c);
      if (indent) pushback(p, '-');
      if (squiggly) pushback(p, '~');
      return 0;
    }
    newtok(p);
    do {
      tokadd(p, c);
    } while ((c = nextc(p)) >= 0 && identchar(c));
    pushback(p, c);
  }
  tokfix(p);
  newnode = new_heredoc(p);
  info = (parser_heredoc_info*)newnode->cdr;
  info->term = strndup(tok(p), toklen(p));
  info->term_len = toklen(p);
  if (! quote)
    type |= STR_FUNC_EXPAND;
  info->type = (string_type)type;
  info->allow_indent = indent || squiggly;
  info->remove_indent = squiggly;
  info->indent = ~0U;
  info->indented = NULL;
  info->line_head = TRUE;
  info->doc = NULL;
  p->heredocs_from_nextline = push(p->heredocs_from_nextline, newnode);
  p->lstate = EXPR_END;

  pylval.nd = newnode;
  return tHEREDOC_BEG;
}

static int
arg_ambiguous(parser_state *p)
{
  yywarning(p, "ambiguous first argument; put parentheses or even spaces");
  return 1;
}

#include "lex.def"

static int
parser_yylex(parser_state *p)
{
  int32_t c;
  int nlines = 1;
  int space_seen = 0;
  int cmd_state;
  enum mrb_lex_state_enum last_state;
  int token_column;

  if (p->lex_strterm) {
    if (is_strterm_type(p, STR_FUNC_HEREDOC)) {
      if (p->parsing_heredoc != NULL)
        return parse_string(p);
    }
    else
      return parse_string(p);
  }
  cmd_state = p->cmd_start;
  p->cmd_start = FALSE;
  retry:
  last_state = p->lstate;
  switch (c = nextc(p)) {
  case '\004':  /* ^D */
  case '\032':  /* ^Z */
  case '\0':    /* NUL */
  case -1:      /* end of script. */
    if (p->heredocs_from_nextline)
      goto maybe_heredoc;
    return 0;

  /* white spaces */
  case ' ': case '\t': case '\f': case '\r':
  case '\13':   /* '\v' */
    space_seen = 1;
    goto retry;

  case '#':     /* it's a comment */
    skip(p, '\n');
    /* fall through */
  case -2:      /* end of a file */
  case '\n':
  maybe_heredoc:
    heredoc_treat_nextline(p);
    p->column = 0;
    switch (p->lstate) {
    case EXPR_BEG:
    case EXPR_FNAME:
    case EXPR_DOT:
    case EXPR_CLASS:
    case EXPR_VALUE:
      p->lineno++;
      if (p->parsing_heredoc != NULL) {
        if (p->lex_strterm) {
          return parse_string(p);
        }
      }
      goto retry;
    default:
      break;
    }
    if (p->parsing_heredoc != NULL) {
      pylval.num = nlines;
      return '\n';
    }
    while ((c = nextc(p))) {
      switch (c) {
      case ' ': case '\t': case '\f': case '\r':
      case '\13': /* '\v' */
        space_seen = 1;
        break;
      case '#': /* comment as a whitespace */
        skip(p, '\n');
        nlines++;
        break;
      case '.':
        if (!peek(p, '.')) {
          pushback(p, '.');
          p->lineno+=nlines; nlines=1;
          goto retry;
        }
        pushback(p, c);
        goto normal_newline;
      case '&':
        if (peek(p, '.')) {
          pushback(p, '&');
          p->lineno+=nlines; nlines=1;
          goto retry;
        }
        pushback(p, c);
        goto normal_newline;
      case -1:                  /* EOF */
      case -2:                  /* end of a file */
        goto normal_newline;
      default:
        pushback(p, c);
        goto normal_newline;
      }
    }
  normal_newline:
    p->cmd_start = TRUE;
    p->lstate = EXPR_BEG;
    pylval.num = nlines;
    return '\n';

  case '*':
    if ((c = nextc(p)) == '*') {
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(pow);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      if (IS_SPCARG(c)) {
        yywarning(p, "'**' interpreted as argument prefix");
        c = tDSTAR;
      }
      else if (IS_BEG()) {
        c = tDSTAR;
      }
      else {
        c = tPOW; /* "**", "argument prefix" */
      }
    }
    else {
      if (c == '=') {
        pylval.id = intern_op(mul);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      if (IS_SPCARG(c)) {
        yywarning(p, "'*' interpreted as argument prefix");
        c = tSTAR;
      }
      else if (IS_BEG()) {
        c = tSTAR;
      }
      else {
        c = '*';
      }
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return c;

  case '!':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
        return '!';
      }
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if (c == '=') {
      return tNEQ;
    }
    if (c == '~') {
      return tNMATCH;
    }
    pushback(p, c);
    return '!';

  case '=':
    if (p->column == 1) {
      static const char begin[] = "begin";
      static const char end[] = "\n=end";
      if (peeks(p, begin)) {
        c = peekc_n(p, sizeof(begin)-1);
        if (c < 0 || ISSPACE(c)) {
          do {
            if (!skips(p, end)) {
              yyerror(p, "embedded document meets end of file");
              return 0;
            }
            c = nextc(p);
          } while (!(c < 0 || ISSPACE(c)));
          if (c != '\n') skip(p, '\n');
          p->lineno+=nlines; nlines=1;
          p->column = 0;
          goto retry;
        }
      }
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if ((c = nextc(p)) == '=') {
      if ((c = nextc(p)) == '=') {
        return tEQQ;
      }
      pushback(p, c);
      return tEQ;
    }
    if (c == '~') {
      return tMATCH;
    }
    else if (c == '>') {
      return tASSOC;
    }
    pushback(p, c);
    return '=';

  case '<':
    c = nextc(p);
    if (c == '<' &&
        p->lstate != EXPR_DOT &&
        p->lstate != EXPR_CLASS &&
        !IS_END() &&
        (!IS_ARG() || space_seen)) {
      int token = heredoc_identifier(p);
      if (token)
        return token;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
      if (p->lstate == EXPR_CLASS) {
        p->cmd_start = TRUE;
      }
    }
    if (c == '=') {
      if ((c = nextc(p)) == '>') {
        return tCMP;
      }
      pushback(p, c);
      return tLEQ;
    }
    if (c == '<') {
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(lshift);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tLSHFT;
    }
    pushback(p, c);
    return '<';

  case '>':
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    if ((c = nextc(p)) == '=') {
      return tGEQ;
    }
    if (c == '>') {
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(rshift);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tRSHFT;
    }
    pushback(p, c);
    return '>';

  case '"':
    p->lex_strterm = new_strterm(p, str_dquote, '"', 0);
    return tSTRING_BEG;

  case '\'':
    p->lex_strterm = new_strterm(p, str_squote, '\'', 0);
    return parse_string(p);

  case '`':
    if (p->lstate == EXPR_FNAME) {
      p->lstate = EXPR_ENDFN;
      return '`';
    }
    if (p->lstate == EXPR_DOT) {
      if (cmd_state)
        p->lstate = EXPR_CMDARG;
      else
        p->lstate = EXPR_ARG;
      return '`';
    }
    p->lex_strterm = new_strterm(p, str_xquote, '`', 0);
    return tXSTRING_BEG;

  case '?':
    if (IS_END()) {
      p->lstate = EXPR_VALUE;
      return '?';
    }
    c = nextc(p);
    if (c < 0) {
      yyerror(p, "incomplete character syntax");
      return 0;
    }
    if (ISSPACE(c)) {
      if (!IS_ARG()) {
        int c2;
        switch (c) {
        case ' ':
          c2 = 's';
          break;
        case '\n':
          c2 = 'n';
          break;
        case '\t':
          c2 = 't';
          break;
        case '\v':
          c2 = 'v';
          break;
        case '\r':
          c2 = 'r';
          break;
        case '\f':
          c2 = 'f';
          break;
        default:
          c2 = 0;
          break;
        }
        if (c2) {
          char buf[256];
          char cc[] = { (char)c2, '\0' };

          strcpy(buf, "invalid character syntax; use ?\\");
          strncat(buf, cc, 2);
          yyerror(p, buf);
        }
      }
      ternary:
      pushback(p, c);
      p->lstate = EXPR_VALUE;
      return '?';
    }
    newtok(p);
    /* need support UTF-8 if configured */
    if ((ISALNUM(c) || c == '_')) {
      int c2 = nextc(p);
      pushback(p, c2);
      if ((ISALNUM(c2) || c2 == '_')) {
        goto ternary;
      }
    }
    if (c == '\\') {
      c = read_escape(p);
      tokadd(p, c);
    }
    else {
      tokadd(p, c);
    }
    tokfix(p);
    pylval.nd = new_str(p, tok(p), toklen(p));
    p->lstate = EXPR_ENDARG;
    return tCHAR;

  case '&':
    if ((c = nextc(p)) == '&') {
      p->lstate = EXPR_BEG;
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(andand);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tANDOP;
    }
    else if (c == '.') {
      p->lstate = EXPR_DOT;
      return tANDDOT;
    }
    else if (c == '=') {
      pylval.id = intern_op(and);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    pushback(p, c);
    if (IS_SPCARG(c)) {
      yywarning(p, "'&' interpreted as argument prefix");
      c = tAMPER;
    }
    else if (IS_BEG()) {
      c = tAMPER;
    }
    else {
      c = '&';
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return c;

  case '|':
    if ((c = nextc(p)) == '|') {
      p->lstate = EXPR_BEG;
      if ((c = nextc(p)) == '=') {
        pylval.id = intern_op(oror);
        p->lstate = EXPR_BEG;
        return tOP_ASGN;
      }
      pushback(p, c);
      return tOROP;
    }
    if (c == '=') {
      pylval.id = intern_op(or);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '|';

  case '+':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
        return tUPLUS;
      }
      pushback(p, c);
      return '+';
    }
    if (c == '=') {
      pylval.id = intern_op(add);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous(p))) {
      p->lstate = EXPR_BEG;
      pushback(p, c);
      if (c >= 0 && ISDIGIT(c)) {
        c = '+';
        goto start_num;
      }
      return tUPLUS;
    }
    p->lstate = EXPR_BEG;
    pushback(p, c);
    return '+';

  case '-':
    c = nextc(p);
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      if (c == '@') {
        return tUMINUS;
      }
      pushback(p, c);
      return '-';
    }
    if (c == '=') {
      pylval.id = intern_op(sub);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (c == '>') {
      p->lstate = EXPR_ENDFN;
      return tLAMBDA;
    }
    if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous(p))) {
      p->lstate = EXPR_BEG;
      pushback(p, c);
      if (c >= 0 && ISDIGIT(c)) {
        return tUMINUS_NUM;
      }
      return tUMINUS;
    }
    p->lstate = EXPR_BEG;
    pushback(p, c);
    return '-';

  case '.':
    {
      int is_beg = IS_BEG();
      p->lstate = EXPR_MID;
      if ((c = nextc(p)) == '.') {
        if ((c = nextc(p)) == '.') {
          return is_beg ? tBDOT3 : tDOT3;
        }
        pushback(p, c);
        return is_beg ? tBDOT2 : tDOT2;
      }
      pushback(p, c);
      p->lstate = EXPR_BEG;
      if (c >= 0 && ISDIGIT(c)) {
        yyerror(p, "no .<digit> floating literal anymore; put 0 before dot");
      }
      p->lstate = EXPR_DOT;
      return '.';
    }

    start_num:
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  {
    int is_float, seen_point, seen_e, nondigit;
    int suffix = 0;

    is_float = seen_point = seen_e = nondigit = 0;
    p->lstate = EXPR_ENDARG;
    newtok(p);
    if (c == '-' || c == '+') {
      tokadd(p, c);
      c = nextc(p);
    }
    if (c == '0') {
#define no_digits() do {yyerror(p,"numeric literal without digits"); return 0;} while (0)
      int start = toklen(p);
      c = nextc(p);
      if (c == 'x' || c == 'X') {
        /* hexadecimal */
        c = nextc(p);
        if (c >= 0 && ISXDIGIT(c)) {
          do {
            if (c == '_') {
              if (nondigit) break;
              nondigit = c;
              continue;
            }
            if (!ISXDIGIT(c)) break;
            nondigit = 0;
            tokadd(p, tolower(c));
          } while ((c = nextc(p)) >= 0);
        }
        pushback(p, c);
        tokfix(p);
        if (toklen(p) == start) {
          no_digits();
        }
        else if (nondigit) goto trailing_uc;
        suffix = number_literal_suffix(p);
        pylval.nd = new_int(p, tok(p), 16, suffix);
        return tINTEGER;
      }
      if (c == 'b' || c == 'B') {
        /* binary */
        c = nextc(p);
        if (c == '0' || c == '1') {
          do {
            if (c == '_') {
              if (nondigit) break;
              nondigit = c;
              continue;
            }
            if (c != '0' && c != '1') break;
            nondigit = 0;
            tokadd(p, c);
          } while ((c = nextc(p)) >= 0);
        }
        pushback(p, c);
        tokfix(p);
        if (toklen(p) == start) {
          no_digits();
        }
        else if (nondigit) goto trailing_uc;
        suffix = number_literal_suffix(p);
        pylval.nd = new_int(p, tok(p), 2, suffix);
        return tINTEGER;
      }
      if (c == 'd' || c == 'D') {
        /* decimal */
        c = nextc(p);
        if (c >= 0 && ISDIGIT(c)) {
          do {
            if (c == '_') {
              if (nondigit) break;
              nondigit = c;
              continue;
            }
            if (!ISDIGIT(c)) break;
            nondigit = 0;
            tokadd(p, c);
          } while ((c = nextc(p)) >= 0);
        }
        pushback(p, c);
        tokfix(p);
        if (toklen(p) == start) {
          no_digits();
        }
        else if (nondigit) goto trailing_uc;
        suffix = number_literal_suffix(p);
        pylval.nd = new_int(p, tok(p), 10, suffix);
        return tINTEGER;
      }
      if (c == '_') {
        /* 0_0 */
        goto octal_number;
      }
      if (c == 'o' || c == 'O') {
        /* prefixed octal */
        c = nextc(p);
        if (c < 0 || c == '_' || !ISDIGIT(c)) {
          no_digits();
        }
      }
      if (c >= '0' && c <= '7') {
        /* octal */
        octal_number:
        do {
          if (c == '_') {
            if (nondigit) break;
            nondigit = c;
            continue;
          }
          if (c < '0' || c > '9') break;
          if (c > '7') goto invalid_octal;
          nondigit = 0;
          tokadd(p, c);
        } while ((c = nextc(p)) >= 0);

        if (toklen(p) > start) {
          pushback(p, c);
          tokfix(p);
          if (nondigit) goto trailing_uc;
          suffix = number_literal_suffix(p);
          pylval.nd = new_int(p, tok(p), 8, suffix);
          return tINTEGER;
        }
        if (nondigit) {
          pushback(p, c);
          goto trailing_uc;
        }
      }
      if (c > '7' && c <= '9') {
        invalid_octal:
        yyerror(p, "Invalid octal digit");
      }
      else if (c == '.' || c == 'e' || c == 'E') {
        tokadd(p, '0');
      }
      else {
        pushback(p, c);
        suffix = number_literal_suffix(p);
        pylval.nd = new_int(p, "0", 10, suffix);
        return tINTEGER;
      }
    }

    for (;;) {
      switch (c) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        nondigit = 0;
        tokadd(p, c);
        break;

      case '.':
        if (nondigit) goto trailing_uc;
        if (seen_point || seen_e) {
          goto decode_num;
        }
        else {
          int c0 = nextc(p);
          if (c0 < 0 || !ISDIGIT(c0)) {
            pushback(p, c0);
            goto decode_num;
          }
          c = c0;
        }
        tokadd(p, '.');
        tokadd(p, c);
        is_float++;
        seen_point++;
        nondigit = 0;
        break;

      case 'e':
      case 'E':
        if (nondigit) {
          pushback(p, c);
          c = nondigit;
          goto decode_num;
        }
        if (seen_e) {
          goto decode_num;
        }
        tokadd(p, c);
        seen_e++;
        is_float++;
        nondigit = c;
        c = nextc(p);
        if (c != '-' && c != '+') continue;
        tokadd(p, c);
        nondigit = c;
        break;

      case '_':       /* '_' in number just ignored */
        if (nondigit) goto decode_num;
        nondigit = c;
        break;

      default:
        goto decode_num;
      }
      c = nextc(p);
    }

    decode_num:
    pushback(p, c);
    if (nondigit) {
      trailing_uc:
      yyerror_c(p, "trailing non digit in number: ", (char)nondigit);
    }
    tokfix(p);
    if (is_float) {
#ifdef MRB_NO_FLOAT
      yywarning_s(p, "floating-point numbers are not supported", tok(p));
      pylval.nd = new_int(p, "0", 10, 0);
      return tINTEGER;
#else
      double d;
      char *endp;

      errno = 0;
      d = mrb_float_read(tok(p), &endp);
      if (d == 0 && endp == tok(p)) {
        yywarning_s(p, "corrupted float value", tok(p));
      }
      else if (errno == ERANGE) {
        yywarning_s(p, "float out of range", tok(p));
        errno = 0;
      }
      suffix = number_literal_suffix(p);
      if (seen_e && (suffix & NUM_SUFFIX_R)) {
        pushback(p, 'r');
        suffix &= ~NUM_SUFFIX_R;
      }
      pylval.nd = new_float(p, tok(p), suffix);
      return tFLOAT;
#endif
    }
    suffix = number_literal_suffix(p);
    pylval.nd = new_int(p, tok(p), 10, suffix);
    return tINTEGER;
  }

  case ')':
  case ']':
    p->paren_nest--;
    /* fall through */
  case '}':
    COND_LEXPOP();
    CMDARG_LEXPOP();
    if (c == ')')
      p->lstate = EXPR_ENDFN;
    else
      p->lstate = EXPR_END;
    return c;

  case ':':
    c = nextc(p);
    if (c == ':') {
      if (IS_BEG() || p->lstate == EXPR_CLASS || IS_SPCARG(-1)) {
        p->lstate = EXPR_BEG;
        return tCOLON3;
      }
      p->lstate = EXPR_DOT;
      return tCOLON2;
    }
    if (!space_seen && IS_END()) {
      pushback(p, c);
      p->lstate = EXPR_BEG;
      return tLABEL_TAG;
    }
    if (IS_END() || ISSPACE(c) || c == '#') {
      pushback(p, c);
      p->lstate = EXPR_BEG;
      return ':';
    }
    pushback(p, c);
    p->lstate = EXPR_FNAME;
    return tSYMBEG;

  case '/':
    if (IS_BEG()) {
      p->lex_strterm = new_strterm(p, str_regexp, '/', 0);
      return tREGEXP_BEG;
    }
    if ((c = nextc(p)) == '=') {
      pylval.id = intern_op(div);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    pushback(p, c);
    if (IS_SPCARG(c)) {
      p->lex_strterm = new_strterm(p, str_regexp, '/', 0);
      return tREGEXP_BEG;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return '/';

  case '^':
    if ((c = nextc(p)) == '=') {
      pylval.id = intern_op(xor);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '^';

  case ';':
    p->lstate = EXPR_BEG;
    return ';';

  case ',':
    p->lstate = EXPR_BEG;
    return ',';

  case '~':
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      if ((c = nextc(p)) != '@') {
        pushback(p, c);
      }
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    return '~';

  case '(':
    if (IS_BEG()) {
      c = tLPAREN;
    }
    else if (IS_SPCARG(-1)) {
      c = tLPAREN_ARG;
    }
    else if (p->lstate == EXPR_END && space_seen) {
      c = tLPAREN_ARG;
    }
    p->paren_nest++;
    COND_PUSH(0);
    CMDARG_PUSH(0);
    p->lstate = EXPR_BEG;
    return c;

  case '[':
    p->paren_nest++;
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
      p->paren_nest--;
      if ((c = nextc(p)) == ']') {
        if ((c = nextc(p)) == '=') {
          return tASET;
        }
        pushback(p, c);
        return tAREF;
      }
      pushback(p, c);
      return '[';
    }
    else if (IS_BEG()) {
      c = tLBRACK;
    }
    else if (IS_ARG() && space_seen) {
      c = tLBRACK;
    }
    p->lstate = EXPR_BEG;
    COND_PUSH(0);
    CMDARG_PUSH(0);
    return c;

  case '{':
    if (p->lpar_beg && p->lpar_beg == p->paren_nest) {
      p->lstate = EXPR_BEG;
      p->lpar_beg = 0;
      p->paren_nest--;
      COND_PUSH(0);
      CMDARG_PUSH(0);
      return tLAMBEG;
    }
    if (IS_ARG() || p->lstate == EXPR_END || p->lstate == EXPR_ENDFN)
      c = '{';          /* block (primary) */
    else if (p->lstate == EXPR_ENDARG)
      c = tLBRACE_ARG;  /* block (expr) */
    else
      c = tLBRACE;      /* hash */
    COND_PUSH(0);
    CMDARG_PUSH(0);
    p->lstate = EXPR_BEG;
    return c;

  case '\\':
    c = nextc(p);
    if (c == '\n') {
      p->lineno+=nlines; nlines=1;
      p->column = 0;
      space_seen = 1;
      goto retry; /* skip \\n */
    }
    pushback(p, c);
    return '\\';

  case '%':
    if (IS_BEG()) {
      int term;
      int paren;

      c = nextc(p);
      quotation:
      if (c < 0 || !ISALNUM(c)) {
        term = c;
        c = 'Q';
      }
      else {
        term = nextc(p);
        if (ISALNUM(term)) {
          yyerror(p, "unknown type of %string");
          return 0;
        }
      }
      if (c < 0 || term < 0) {
        yyerror(p, "unterminated quoted string meets end of file");
        return 0;
      }
      paren = term;
      if (term == '(') term = ')';
      else if (term == '[') term = ']';
      else if (term == '{') term = '}';
      else if (term == '<') term = '>';
      else paren = 0;

      switch (c) {
      case 'Q':
        p->lex_strterm = new_strterm(p, str_dquote, term, paren);
        return tSTRING_BEG;

      case 'q':
        p->lex_strterm = new_strterm(p, str_squote, term, paren);
        return parse_string(p);

      case 'W':
        p->lex_strterm = new_strterm(p, str_dword, term, paren);
        return tWORDS_BEG;

      case 'w':
        p->lex_strterm = new_strterm(p, str_sword, term, paren);
        return tWORDS_BEG;

      case 'x':
        p->lex_strterm = new_strterm(p, str_xquote, term, paren);
        return tXSTRING_BEG;

      case 'r':
        p->lex_strterm = new_strterm(p, str_regexp, term, paren);
        return tREGEXP_BEG;

      case 's':
        p->lex_strterm = new_strterm(p, str_ssym, term, paren);
        return tSYMBEG;

      case 'I':
        p->lex_strterm = new_strterm(p, str_dsymbols, term, paren);
        return tSYMBOLS_BEG;

      case 'i':
        p->lex_strterm = new_strterm(p, str_ssymbols, term, paren);
        return tSYMBOLS_BEG;

      default:
        yyerror(p, "unknown type of %string");
        return 0;
      }
    }
    if ((c = nextc(p)) == '=') {
      pylval.id = intern_op(mod);
      p->lstate = EXPR_BEG;
      return tOP_ASGN;
    }
    if (IS_SPCARG(c)) {
      goto quotation;
    }
    if (p->lstate == EXPR_FNAME || p->lstate == EXPR_DOT) {
      p->lstate = EXPR_ARG;
    }
    else {
      p->lstate = EXPR_BEG;
    }
    pushback(p, c);
    return '%';

  case '$':
    p->lstate = EXPR_END;
    token_column = newtok(p);
    c = nextc(p);
    if (c < 0) {
      yyerror(p, "incomplete global variable syntax");
      return 0;
    }
    switch (c) {
    case '_':     /* $_: last read line string */
      c = nextc(p);
      if (c >= 0 && identchar(c)) { /* if there is more after _ it is a variable */
        tokadd(p, '$');
        tokadd(p, c);
        break;
      }
      pushback(p, c);
      c = '_';
      /* fall through */
    case '~':     /* $~: match-data */
    case '*':     /* $*: argv */
    case '$':     /* $$: pid */
    case '?':     /* $?: last status */
    case '!':     /* $!: error string */
    case '@':     /* $@: error position */
    case '/':     /* $/: input record separator */
    case '\\':    /* $\: output record separator */
    case ';':     /* $;: field separator */
    case ',':     /* $,: output field separator */
    case '.':     /* $.: last read line number */
    case '=':     /* $=: ignorecase */
    case ':':     /* $:: load path */
    case '<':     /* $<: reading filename */
    case '>':     /* $>: default output handle */
    case '\"':    /* $": already loaded files */
      tokadd(p, '$');
      tokadd(p, c);
      tokfix(p);
      pylval.id = intern(tok(p), toklen(p));
      return tGVAR;

    case '-':
      tokadd(p, '$');
      tokadd(p, c);
      c = nextc(p);
      pushback(p, c);
      gvar:
      tokfix(p);
      pylval.id = intern(tok(p), toklen(p));
      return tGVAR;

    case '&':     /* $&: last match */
    case '`':     /* $`: string before last match */
    case '\'':    /* $': string after last match */
    case '+':     /* $+: string matches last pattern */
      if (last_state == EXPR_FNAME) {
        tokadd(p, '$');
        tokadd(p, c);
        goto gvar;
      }
      pylval.nd = new_back_ref(p, c);
      return tBACK_REF;

    case '1': case '2': case '3':
    case '4': case '5': case '6':
    case '7': case '8': case '9':
      do {
        tokadd(p, c);
        c = nextc(p);
      } while (c >= 0 && ISDIGIT(c));
      pushback(p, c);
      if (last_state == EXPR_FNAME) goto gvar;
      tokfix(p);
      {
        mrb_int n = mrb_int_read(tok(p), NULL, NULL);
        if (n > INT32_MAX) {
          yywarning(p, "capture group index too big; always nil");
          return keyword_nil;
        }
        pylval.nd = new_nth_ref(p, (int)n);
      }
      return tNTH_REF;

    default:
      if (!identchar(c)) {
        pushback(p,  c);
        return '$';
      }
      /* fall through */
    case '0':
      tokadd(p, '$');
    }
    break;

    case '@':
      c = nextc(p);
      token_column = newtok(p);
      tokadd(p, '@');
      if (c == '@') {
        tokadd(p, '@');
        c = nextc(p);
      }
      if (c < 0) {
        if (p->tidx == 1) {
          yyerror(p, "incomplete instance variable syntax");
        }
        else {
          yyerror(p, "incomplete class variable syntax");
        }
        return 0;
      }
      else if (ISDIGIT(c)) {
        if (p->tidx == 1) {
          yyerror_c(p, "wrong instance variable name: @", c);
        }
        else {
          yyerror_c(p, "wrong class variable name: @@", c);
        }
        return 0;
      }
      if (!identchar(c)) {
        pushback(p, c);
        return '@';
      }
      break;

    case '_':
      token_column = newtok(p);
      break;

    default:
      if (!identchar(c)) {
        char buf[36];
        const char s[] = "Invalid char in expression: 0x";
        const char hexdigits[] = "0123456789ABCDEF";

        strcpy(buf, s);
        buf[sizeof(s)-1] = hexdigits[(c & 0xf0) >> 4];
        buf[sizeof(s)]   = hexdigits[(c & 0x0f)];
        buf[sizeof(s)+1] = 0;
        yyerror(p, buf);
        goto retry;
      }

      token_column = newtok(p);
      break;
  }

  do {
    tokadd(p, c);
    c = nextc(p);
    if (c < 0) break;
  } while (identchar(c));
  if (token_column == 0 && toklen(p) == 7 && (c < 0 || c == '\n') &&
      strncmp(tok(p), "__END__", toklen(p)) == 0)
    return -1;

  switch (tok(p)[0]) {
  case '@': case '$':
    pushback(p, c);
    break;
  default:
    if ((c == '!' || c == '?') && !peek(p, '=')) {
      tokadd(p, c);
    }
    else {
      pushback(p, c);
    }
  }
  tokfix(p);
  {
    int result = 0;

    switch (tok(p)[0]) {
    case '$':
      p->lstate = EXPR_END;
      result = tGVAR;
      break;
    case '@':
      p->lstate = EXPR_END;
      if (tok(p)[1] == '@')
        result = tCVAR;
      else
        result = tIVAR;
      break;

    case '_':
      if (p->lstate != EXPR_FNAME && toklen(p) == 2 && ISDIGIT(tok(p)[1]) && p->nvars) {
        int n = tok(p)[1] - '0';
        int nvar;

        if (n > 0) {
          node *nvars = p->nvars->cdr;

          while (nvars) {
            nvar = intn(nvars->car);
            if (nvar == -2) break; /* top of the scope */
            if (nvar > 0) {
              yywarning(p, "numbered parameter used in outer block");
              break;
            }
            nvars->car = nint(-1);
            nvars = nvars->cdr;
          }
          nvar = intn(p->nvars->car);
          if (nvar == -1) {
            yywarning(p, "numbered parameter used in inner block");
          }
          if (nvar >= -1) {
            pylval.num = n;
            p->lstate = EXPR_END;
            return tNUMPARAM;
          }
          else {
            yywarning(p, "identifier for numbered parameter; consider another name");
          }
        }
      }
      /* fall through */
    default:
      if (toklast(p) == '!' || toklast(p) == '?') {
        result = tFID;
      }
      else {
        if (p->lstate == EXPR_FNAME) {
          if ((c = nextc(p)) == '=' && !peek(p, '~') && !peek(p, '>') &&
              (!peek(p, '=') || (peek_n(p, '>', 1)))) {
            result = tIDENTIFIER;
            tokadd(p, c);
            tokfix(p);
          }
          else {
            pushback(p, c);
          }
          if ((c = nextc(p)) == '=' && !peek(p, '~') && !peek(p, '>') &&
              (!peek(p, '=') || (peek_n(p, '>', 1)))) {
            result = tIDENTIFIER;
            tokadd(p, c);
            tokfix(p);
          }
          else {
            pushback(p, c);
          }
        }
        if (result == 0 && ISUPPER(tok(p)[0])) {
          result = tCONSTANT;
        }
        else {
          result = tIDENTIFIER;
        }
      }

      if (IS_LABEL_POSSIBLE()) {
        if (IS_LABEL_SUFFIX(0)) {
          p->lstate = EXPR_END;
          tokfix(p);
          pylval.id = intern(tok(p), toklen(p));
          return tIDENTIFIER;
        }
      }
      if (p->lstate != EXPR_DOT) {
        const struct kwtable *kw;

        /* See if it is a reserved word.  */
        kw = mrb_reserved_word(tok(p), toklen(p));
        if (kw) {
          enum mrb_lex_state_enum state = p->lstate;
          pylval.num = p->lineno;
          p->lstate = kw->state;
          if (state == EXPR_FNAME) {
            pylval.id = intern_cstr(kw->name);
            return kw->id[0];
          }
          if (p->lstate == EXPR_BEG) {
            p->cmd_start = TRUE;
          }
          if (kw->id[0] == keyword_do) {
            if (p->lpar_beg && p->lpar_beg == p->paren_nest) {
              p->lpar_beg = 0;
              p->paren_nest--;
              return keyword_do_LAMBDA;
            }
            if (COND_P()) return keyword_do_cond;
            if (CMDARG_P() && state != EXPR_CMDARG)
              return keyword_do_block;
            if (state == EXPR_ENDARG || state == EXPR_BEG)
              return keyword_do_block;
            return keyword_do;
          }
          if (state == EXPR_BEG || state == EXPR_VALUE)
            return kw->id[0];
          else {
            if (kw->id[0] != kw->id[1])
              p->lstate = EXPR_BEG;
            return kw->id[1];
          }
        }
      }

      if (IS_BEG() || p->lstate == EXPR_DOT || IS_ARG()) {
        if (cmd_state) {
          p->lstate = EXPR_CMDARG;
        }
        else {
          p->lstate = EXPR_ARG;
        }
      }
      else if (p->lstate == EXPR_FNAME) {
        p->lstate = EXPR_ENDFN;
      }
      else {
        p->lstate = EXPR_END;
      }
    }
    {
      mrb_sym ident = intern(tok(p), toklen(p));

      pylval.id = ident;
      if (last_state != EXPR_DOT && ISLOWER(tok(p)[0]) && local_var_p(p, ident)) {
        p->lstate = EXPR_END;
      }
    }
    return result;
  }
}

static int
yylex(void *lval, parser_state *p)
{
  p->ylval = lval;
  return parser_yylex(p);
}

static void
parser_init_cxt(parser_state *p, mrbc_context *cxt)
{
  if (!cxt) return;
  if (cxt->filename) mrb_parser_set_filename(p, cxt->filename);
  if (cxt->lineno) p->lineno = cxt->lineno;
  if (cxt->syms) {
    int i;

    p->locals = cons(0,0);
    for (i=0; i<cxt->slen; i++) {
      local_add_f(p, cxt->syms[i]);
    }
  }
  p->capture_errors = cxt->capture_errors;
  p->no_optimize = cxt->no_optimize;
  p->no_ext_ops = cxt->no_ext_ops;
  p->upper = cxt->upper;
  if (cxt->partial_hook) {
    p->cxt = cxt;
  }
}

static void
parser_update_cxt(parser_state *p, mrbc_context *cxt)
{
  node *n, *n0;
  int i = 0;

  if (!cxt) return;
  if (!p->tree) return;
  if (intn(p->tree->car) != NODE_SCOPE) return;
  n0 = n = p->tree->cdr->car;
  while (n) {
    i++;
    n = n->cdr;
  }
  cxt->syms = (mrb_sym *)mrb_realloc(p->mrb, cxt->syms, i*sizeof(mrb_sym));
  cxt->slen = i;
  for (i=0, n=n0; n; i++,n=n->cdr) {
    cxt->syms[i] = sym(n->car);
  }
}

void mrb_codedump_all(mrb_state*, struct RProc*);
void mrb_parser_dump(mrb_state *mrb, node *tree, int offset);

MRB_API void
mrb_parser_parse(parser_state *p, mrbc_context *c)
{
  struct mrb_jmpbuf buf1;
  struct mrb_jmpbuf *prev = p->mrb->jmp;
  p->mrb->jmp = &buf1;

  MRB_TRY(p->mrb->jmp) {
    int n = 1;

    p->cmd_start = TRUE;
    p->in_def = p->in_single = 0;
    p->nerr = p->nwarn = 0;
    p->lex_strterm = NULL;
    parser_init_cxt(p, c);

    n = yyparse(p);
    if (n != 0 || p->nerr > 0) {
      p->tree = 0;
      p->mrb->jmp = prev;
      return;
    }
    parser_update_cxt(p, c);
    if (c && c->dump_result) {
      mrb_parser_dump(p->mrb, p->tree, 0);
    }
  }
  MRB_CATCH(p->mrb->jmp) {
    p->nerr++;
    if (p->mrb->exc == NULL) {
      yyerror(p, "memory allocation error");
      p->nerr++;
      p->tree = 0;
    }
  }
  MRB_END_EXC(p->jmp);
  p->mrb->jmp = prev;
}

MRB_API parser_state*
mrb_parser_new(mrb_state *mrb)
{
  mrb_pool *pool;
  parser_state *p;
  static const parser_state parser_state_zero = { 0 };

  pool = mrb_pool_open(mrb);
  if (!pool) return NULL;
  p = (parser_state *)mrb_pool_alloc(pool, sizeof(parser_state));
  if (!p) return NULL;

  *p = parser_state_zero;
  p->mrb = mrb;
  p->pool = pool;

  p->s = p->send = NULL;
#ifndef MRB_NO_STDIO
  p->f = NULL;
#endif

  p->cmd_start = TRUE;
  p->in_def = p->in_single = 0;

  p->capture_errors = FALSE;
  p->lineno = 1;
  p->column = 0;
#if defined(PARSER_TEST) || defined(PARSER_DEBUG)
  yydebug = 1;
#endif
  p->tsiz = MRB_PARSER_TOKBUF_SIZE;
  p->tokbuf = p->buf;

  p->lex_strterm = NULL;
  p->all_heredocs = p->parsing_heredoc = NULL;
  p->lex_strterm_before_heredoc = NULL;

  p->current_filename_index = -1;
  p->filename_table = NULL;
  p->filename_table_length = 0;

  return p;
}

MRB_API void
mrb_parser_free(parser_state *p) {
  if (p->tokbuf != p->buf) {
    mrb_free(p->mrb, p->tokbuf);
  }
  mrb_pool_close(p->pool);
}

MRB_API mrbc_context*
mrbc_context_new(mrb_state *mrb)
{
  return (mrbc_context *)mrb_calloc(mrb, 1, sizeof(mrbc_context));
}

MRB_API void
mrbc_context_free(mrb_state *mrb, mrbc_context *cxt)
{
  mrb_free(mrb, cxt->filename);
  mrb_free(mrb, cxt->syms);
  mrb_free(mrb, cxt);
}

MRB_API const char*
mrbc_filename(mrb_state *mrb, mrbc_context *c, const char *s)
{
  if (s) {
    size_t len = strlen(s);
    char *p = (char *)mrb_malloc(mrb, len + 1);

    memcpy(p, s, len + 1);
    if (c->filename) {
      mrb_free(mrb, c->filename);
    }
    c->filename = p;
  }
  return c->filename;
}

MRB_API void
mrbc_partial_hook(mrb_state *mrb, mrbc_context *c, int (*func)(struct mrb_parser_state*), void *data)
{
  c->partial_hook = func;
  c->partial_data = data;
}

MRB_API void
mrbc_cleanup_local_variables(mrb_state *mrb, mrbc_context *c)
{
  if (c->syms) {
    mrb_free(mrb, c->syms);
    c->syms = NULL;
    c->slen = 0;
  }
}

MRB_API void
mrb_parser_set_filename(struct mrb_parser_state *p, const char *f)
{
  mrb_sym sym;
  uint16_t i;
  mrb_sym* new_table;

  sym = mrb_intern_cstr(p->mrb, f);
  p->filename_sym = sym;
  p->lineno = (p->filename_table_length > 0)? 0 : 1;

  for (i = 0; i < p->filename_table_length; ++i) {
    if (p->filename_table[i] == sym) {
      p->current_filename_index = i;
      return;
    }
  }

  if (p->filename_table_length == UINT16_MAX) {
    yyerror(p, "too many files to compile");
    return;
  }
  p->current_filename_index = p->filename_table_length++;

  new_table = (mrb_sym*)parser_palloc(p, sizeof(mrb_sym) * p->filename_table_length);
  if (p->filename_table) {
    memmove(new_table, p->filename_table, sizeof(mrb_sym) * p->current_filename_index);
  }
  p->filename_table = new_table;
  p->filename_table[p->filename_table_length - 1] = sym;
}

MRB_API mrb_sym
mrb_parser_get_filename(struct mrb_parser_state* p, uint16_t idx) {
  if (idx >= p->filename_table_length) return 0;
  else {
    return p->filename_table[idx];
  }
}

#ifndef MRB_NO_STDIO
static struct mrb_parser_state *
mrb_parse_file_continue(mrb_state *mrb, FILE *f, const void *prebuf, size_t prebufsize, mrbc_context *c)
{
  parser_state *p;

  p = mrb_parser_new(mrb);
  if (!p) return NULL;
  if (prebuf) {
    p->s = (const char *)prebuf;
    p->send = (const char *)prebuf + prebufsize;
  }
  else {
    p->s = p->send = NULL;
  }
  p->f = f;

  mrb_parser_parse(p, c);
  return p;
}

MRB_API parser_state*
mrb_parse_file(mrb_state *mrb, FILE *f, mrbc_context *c)
{
  return mrb_parse_file_continue(mrb, f, NULL, 0, c);
}
#endif

MRB_API parser_state*
mrb_parse_nstring(mrb_state *mrb, const char *s, size_t len, mrbc_context *c)
{
  parser_state *p;

  p = mrb_parser_new(mrb);
  if (!p) return NULL;
  p->s = s;
  p->send = s + len;

  mrb_parser_parse(p, c);
  return p;
}

MRB_API parser_state*
mrb_parse_string(mrb_state *mrb, const char *s, mrbc_context *c)
{
  return mrb_parse_nstring(mrb, s, strlen(s), c);
}

MRB_API mrb_value
mrb_load_exec(mrb_state *mrb, struct mrb_parser_state *p, mrbc_context *c)
{
  struct RClass *target = mrb->object_class;
  struct RProc *proc;
  mrb_value v;
  mrb_int keep = 0;

  if (!p) {
    return mrb_undef_value();
  }
  if (!p->tree || p->nerr) {
    if (c) c->parser_nerr = p->nerr;
    if (p->capture_errors) {
      char buf[256];

      strcpy(buf, "line ");
      dump_int(p->error_buffer[0].lineno, buf+5);
      strcat(buf, ": ");
      strncat(buf, p->error_buffer[0].message, sizeof(buf) - strlen(buf) - 1);
      mrb->exc = mrb_obj_ptr(mrb_exc_new(mrb, E_SYNTAX_ERROR, buf, strlen(buf)));
      mrb_parser_free(p);
      return mrb_undef_value();
    }
    else {
      if (mrb->exc == NULL) {
        mrb->exc = mrb_obj_ptr(mrb_exc_new_lit(mrb, E_SYNTAX_ERROR, "syntax error"));
      }
      mrb_parser_free(p);
      return mrb_undef_value();
    }
  }
  proc = mrb_generate_code(mrb, p);
  mrb_parser_free(p);
  if (proc == NULL) {
    if (mrb->exc == NULL) {
      mrb->exc = mrb_obj_ptr(mrb_exc_new_lit(mrb, E_SCRIPT_ERROR, "codegen error"));
    }
    return mrb_undef_value();
  }
  if (c) {
    if (c->dump_result) mrb_codedump_all(mrb, proc);
    if (c->no_exec) return mrb_obj_value(proc);
    if (c->target_class) {
      target = c->target_class;
    }
    if (c->keep_lv) {
      keep = c->slen + 1;
    }
    else {
      c->keep_lv = TRUE;
    }
  }
  MRB_PROC_SET_TARGET_CLASS(proc, target);
  if (mrb->c->ci) {
    mrb_vm_ci_target_class_set(mrb->c->ci, target);
  }
  v = mrb_top_run(mrb, proc, mrb_top_self(mrb), keep);
  if (mrb->exc) return mrb_nil_value();
  return v;
}

#ifndef MRB_NO_STDIO
MRB_API mrb_value
mrb_load_file_cxt(mrb_state *mrb, FILE *f, mrbc_context *c)
{
  return mrb_load_exec(mrb, mrb_parse_file(mrb, f, c), c);
}

MRB_API mrb_value
mrb_load_file(mrb_state *mrb, FILE *f)
{
  return mrb_load_file_cxt(mrb, f, NULL);
}

#define DETECT_SIZE 64

/*
 * In order to be recognized as a `.mrb` file, the following three points must be satisfied:
 * - File starts with "RITE"
 * - At least `sizeof(struct rite_binary_header)` bytes can be read
 * - `NUL` is included in the first 64 bytes of the file
 */
MRB_API mrb_value
mrb_load_detect_file_cxt(mrb_state *mrb, FILE *fp, mrbc_context *c)
{
  union {
    char b[DETECT_SIZE];
    struct rite_binary_header h;
  } leading;
  size_t bufsize;

  if (mrb == NULL || fp == NULL) {
    return mrb_nil_value();
  }

  bufsize = fread(leading.b, sizeof(char), sizeof(leading), fp);
  if (bufsize < sizeof(leading.h) ||
      memcmp(leading.h.binary_ident, RITE_BINARY_IDENT, sizeof(leading.h.binary_ident)) != 0 ||
      memchr(leading.b, '\0', bufsize) == NULL) {
    return mrb_load_exec(mrb, mrb_parse_file_continue(mrb, fp, leading.b, bufsize, c), c);
  }
  else {
    size_t binsize;
    uint8_t *bin;
    mrb_value bin_obj = mrb_nil_value(); /* temporary string object */
    mrb_value result;

    binsize = bin_to_uint32(leading.h.binary_size);
    bin_obj = mrb_str_new(mrb, NULL, binsize);
    bin = (uint8_t *)RSTRING_PTR(bin_obj);
    memcpy(bin, leading.b, bufsize);
    if (binsize > bufsize &&
        fread(bin + bufsize, binsize - bufsize, 1, fp) == 0) {
      binsize = bufsize;
      /* The error is reported by mrb_load_irep_buf_cxt() */
    }

    result = mrb_load_irep_buf_cxt(mrb, bin, binsize, c);
    if (mrb_string_p(bin_obj)) mrb_str_resize(mrb, bin_obj, 0);
    return result;
  }
}
#endif

MRB_API mrb_value
mrb_load_nstring_cxt(mrb_state *mrb, const char *s, size_t len, mrbc_context *c)
{
  return mrb_load_exec(mrb, mrb_parse_nstring(mrb, s, len, c), c);
}

MRB_API mrb_value
mrb_load_nstring(mrb_state *mrb, const char *s, size_t len)
{
  return mrb_load_nstring_cxt(mrb, s, len, NULL);
}

MRB_API mrb_value
mrb_load_string_cxt(mrb_state *mrb, const char *s, mrbc_context *c)
{
  return mrb_load_nstring_cxt(mrb, s, strlen(s), c);
}

MRB_API mrb_value
mrb_load_string(mrb_state *mrb, const char *s)
{
  return mrb_load_string_cxt(mrb, s, NULL);
}

#ifndef MRB_NO_STDIO

static void
dump_prefix(node *tree, int offset)
{
  printf("%05d ", tree->lineno);
  while (offset--) {
    putc(' ', stdout);
    putc(' ', stdout);
  }
}

static void
dump_recur(mrb_state *mrb, node *tree, int offset)
{
  while (tree) {
    mrb_parser_dump(mrb, tree->car, offset);
    tree = tree->cdr;
  }
}

static void
dump_args(mrb_state *mrb, node *n, int offset)
{
  if (n->car) {
    dump_prefix(n, offset+1);
    printf("mandatory args:\n");
    dump_recur(mrb, n->car, offset+2);
  }
  n = n->cdr;
  if (n->car) {
    dump_prefix(n, offset+1);
    printf("optional args:\n");
    {
      node *n2 = n->car;

      while (n2) {
        dump_prefix(n2, offset+2);
        printf("%s=\n", mrb_sym_name(mrb, sym(n2->car->car)));
        mrb_parser_dump(mrb, n2->car->cdr, offset+3);
        n2 = n2->cdr;
      }
    }
  }
  n = n->cdr;
  if (n->car) {
    mrb_sym rest = sym(n->car);

    dump_prefix(n, offset+1);
    if (rest == MRB_OPSYM(mul))
      printf("rest=*\n");
    else
      printf("rest=*%s\n", mrb_sym_name(mrb, rest));
  }
  n = n->cdr;
  if (n->car) {
    dump_prefix(n, offset+1);
    printf("post mandatory args:\n");
    dump_recur(mrb, n->car, offset+2);
  }

  n = n->cdr;
  if (n) {
    mrb_assert(intn(n->car) == NODE_ARGS_TAIL);
    mrb_parser_dump(mrb, n, offset);
  }
}

/*
 * This function restores the GC arena on return.
 * For this reason, if a process that further generates an object is
 * performed at the caller, the string pointer returned as the return
 * value may become invalid.
 */
static const char*
str_dump(mrb_state *mrb, const char *str, int len)
{
  int ai = mrb_gc_arena_save(mrb);
  mrb_value s;
# if INT_MAX > MRB_INT_MAX / 4
  /* check maximum length with "\xNN" character */
  if (len > MRB_INT_MAX / 4) {
    len = MRB_INT_MAX / 4;
  }
# endif
  s = mrb_str_new(mrb, str, (mrb_int)len);
  s = mrb_str_dump(mrb, s);
  mrb_gc_arena_restore(mrb, ai);
  return RSTRING_PTR(s);
}
#endif

void
mrb_parser_dump(mrb_state *mrb, node *tree, int offset)
{
#ifndef MRB_NO_STDIO
  int nodetype;

  if (!tree) return;
  again:
  dump_prefix(tree, offset);
  nodetype = intn(tree->car);
  tree = tree->cdr;
  switch (nodetype) {
  case NODE_BEGIN:
    printf("NODE_BEGIN:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_RESCUE:
    printf("NODE_RESCUE:\n");
    if (tree->car) {
      dump_prefix(tree, offset+1);
      printf("body:\n");
      mrb_parser_dump(mrb, tree->car, offset+2);
    }
    tree = tree->cdr;
    if (tree->car) {
      node *n2 = tree->car;

      dump_prefix(n2, offset+1);
      printf("rescue:\n");
      while (n2) {
        node *n3 = n2->car;
        if (n3->car) {
          dump_prefix(n2, offset+2);
          printf("handle classes:\n");
          dump_recur(mrb, n3->car, offset+3);
        }
        if (n3->cdr->car) {
          dump_prefix(n3, offset+2);
          printf("exc_var:\n");
          mrb_parser_dump(mrb, n3->cdr->car, offset+3);
        }
        if (n3->cdr->cdr->car) {
          dump_prefix(n3, offset+2);
          printf("rescue body:\n");
          mrb_parser_dump(mrb, n3->cdr->cdr->car, offset+3);
        }
        n2 = n2->cdr;
      }
    }
    tree = tree->cdr;
    if (tree->car) {
      dump_prefix(tree, offset+1);
      printf("else:\n");
      mrb_parser_dump(mrb, tree->car, offset+2);
    }
    break;

  case NODE_ENSURE:
    printf("NODE_ENSURE:\n");
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("ensure:\n");
    mrb_parser_dump(mrb, tree->cdr->cdr, offset+2);
    break;

  case NODE_LAMBDA:
    printf("NODE_LAMBDA:\n");
    dump_prefix(tree, offset);
    goto block;

  case NODE_BLOCK:
    block:
    printf("NODE_BLOCK:\n");
    tree = tree->cdr;
    if (tree->car) {
      dump_args(mrb, tree->car, offset+1);
    }
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr->car, offset+2);
    break;

  case NODE_IF:
    printf("NODE_IF:\n");
    dump_prefix(tree, offset+1);
    printf("cond:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("then:\n");
    mrb_parser_dump(mrb, tree->cdr->car, offset+2);
    if (tree->cdr->cdr->car) {
      dump_prefix(tree, offset+1);
      printf("else:\n");
      mrb_parser_dump(mrb, tree->cdr->cdr->car, offset+2);
    }
    break;

  case NODE_AND:
    printf("NODE_AND:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    mrb_parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_OR:
    printf("NODE_OR:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    mrb_parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_CASE:
    printf("NODE_CASE:\n");
    if (tree->car) {
      mrb_parser_dump(mrb, tree->car, offset+1);
    }
    tree = tree->cdr;
    while (tree) {
      dump_prefix(tree, offset+1);
      printf("case:\n");
      dump_recur(mrb, tree->car->car, offset+2);
      dump_prefix(tree, offset+1);
      printf("body:\n");
      mrb_parser_dump(mrb, tree->car->cdr, offset+2);
      tree = tree->cdr;
    }
    break;

  case NODE_WHILE:
    printf("NODE_WHILE:\n");
    dump_prefix(tree, offset+1);
    printf("cond:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_UNTIL:
    printf("NODE_UNTIL:\n");
    dump_prefix(tree, offset+1);
    printf("cond:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_FOR:
    printf("NODE_FOR:\n");
    dump_prefix(tree, offset+1);
    printf("var:\n");
    {
      node *n2 = tree->car;

      if (n2->car) {
        dump_prefix(n2, offset+2);
        printf("pre:\n");
        dump_recur(mrb, n2->car, offset+3);
      }
      n2 = n2->cdr;
      if (n2) {
        if (n2->car) {
          dump_prefix(n2, offset+2);
          printf("rest:\n");
          mrb_parser_dump(mrb, n2->car, offset+3);
        }
        n2 = n2->cdr;
        if (n2) {
          if (n2->car) {
            dump_prefix(n2, offset+2);
            printf("post:\n");
            dump_recur(mrb, n2->car, offset+3);
          }
        }
      }
    }
    tree = tree->cdr;
    dump_prefix(tree, offset+1);
    printf("in:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    tree = tree->cdr;
    dump_prefix(tree, offset+1);
    printf("do:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    break;

  case NODE_SCOPE:
    printf("NODE_SCOPE:\n");
    {
      node *n2 = tree->car;
      mrb_bool first_lval = TRUE;

      if (n2 && (n2->car || n2->cdr)) {
        dump_prefix(n2, offset+1);
        printf("local variables:\n");
        dump_prefix(n2, offset+2);
        while (n2) {
          if (n2->car) {
            if (!first_lval) printf(", ");
            printf("%s", mrb_sym_name(mrb, sym(n2->car)));
            first_lval = FALSE;
          }
          n2 = n2->cdr;
        }
        printf("\n");
      }
    }
    tree = tree->cdr;
    offset++;
    goto again;

  case NODE_FCALL:
  case NODE_CALL:
  case NODE_SCALL:
    switch (nodetype) {
    case NODE_FCALL:
      printf("NODE_FCALL:\n"); break;
    case NODE_CALL:
      printf("NODE_CALL(.):\n"); break;
    case NODE_SCALL:
      printf("NODE_SCALL(&.):\n"); break;
    default:
      break;
    }
    mrb_parser_dump(mrb, tree->car, offset+1);
    dump_prefix(tree, offset+1);
    printf("method='%s' (%d)\n",
        mrb_sym_dump(mrb, sym(tree->cdr->car)),
        intn(tree->cdr->car));
    tree = tree->cdr->cdr->car;
    if (tree) {
      dump_prefix(tree, offset+1);
      printf("args:\n");
      dump_recur(mrb, tree->car, offset+2);
      if (tree->cdr) {
        if (tree->cdr->car) {
          dump_prefix(tree, offset+1);
          printf("kwargs:\n");
          mrb_parser_dump(mrb, tree->cdr->car, offset+2);
        }
        if (tree->cdr->cdr) {
          dump_prefix(tree, offset+1);
          printf("block:\n");
          mrb_parser_dump(mrb, tree->cdr->cdr, offset+2);
        }
      }
    }
    break;

  case NODE_DOT2:
    printf("NODE_DOT2:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    mrb_parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_DOT3:
    printf("NODE_DOT3:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    mrb_parser_dump(mrb, tree->cdr, offset+1);
    break;

  case NODE_COLON2:
    printf("NODE_COLON2:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    dump_prefix(tree, offset+1);
    printf("::%s\n", mrb_sym_name(mrb, sym(tree->cdr)));
    break;

  case NODE_COLON3:
    printf("NODE_COLON3: ::%s\n", mrb_sym_name(mrb, sym(tree)));
    break;

  case NODE_ARRAY:
    printf("NODE_ARRAY:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_HASH:
    printf("NODE_HASH:\n");
    while (tree) {
      dump_prefix(tree, offset+1);
      printf("key:\n");
      mrb_parser_dump(mrb, tree->car->car, offset+2);
      dump_prefix(tree, offset+1);
      printf("value:\n");
      mrb_parser_dump(mrb, tree->car->cdr, offset+2);
      tree = tree->cdr;
    }
    break;

  case NODE_KW_HASH:
    printf("NODE_KW_HASH:\n");
    while (tree) {
      dump_prefix(tree, offset+1);
      printf("key:\n");
      mrb_parser_dump(mrb, tree->car->car, offset+2);
      dump_prefix(tree, offset+1);
      printf("value:\n");
      mrb_parser_dump(mrb, tree->car->cdr, offset+2);
      tree = tree->cdr;
    }
    break;

  case NODE_SPLAT:
    printf("NODE_SPLAT:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_ASGN:
    printf("NODE_ASGN:\n");
    dump_prefix(tree, offset+1);
    printf("lhs:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    dump_prefix(tree, offset+1);
    printf("rhs:\n");
    mrb_parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_MASGN:
    printf("NODE_MASGN:\n");
    dump_prefix(tree, offset+1);
    printf("mlhs:\n");
    {
      node *n2 = tree->car;

      if (n2->car) {
        dump_prefix(tree, offset+2);
        printf("pre:\n");
        dump_recur(mrb, n2->car, offset+3);
      }
      n2 = n2->cdr;
      if (n2) {
        if (n2->car) {
          dump_prefix(n2, offset+2);
          printf("rest:\n");
          if (n2->car == nint(-1)) {
            dump_prefix(n2, offset+2);
            printf("(empty)\n");
          }
          else {
            mrb_parser_dump(mrb, n2->car, offset+3);
          }
        }
        n2 = n2->cdr;
        if (n2) {
          if (n2->car) {
            dump_prefix(n2, offset+2);
            printf("post:\n");
            dump_recur(mrb, n2->car, offset+3);
          }
        }
      }
    }
    dump_prefix(tree, offset+1);
    printf("rhs:\n");
    mrb_parser_dump(mrb, tree->cdr, offset+2);
    break;

  case NODE_OP_ASGN:
    printf("NODE_OP_ASGN:\n");
    dump_prefix(tree, offset+1);
    printf("lhs:\n");
    mrb_parser_dump(mrb, tree->car, offset+2);
    tree = tree->cdr;
    dump_prefix(tree, offset+1);
    printf("op='%s' (%d)\n", mrb_sym_name(mrb, sym(tree->car)), intn(tree->car));
    tree = tree->cdr;
    mrb_parser_dump(mrb, tree->car, offset+1);
    break;

  case NODE_SUPER:
    printf("NODE_SUPER:\n");
    if (tree) {
      dump_prefix(tree, offset+1);
      printf("args:\n");
      dump_recur(mrb, tree->car, offset+2);
      if (tree->cdr) {
        dump_prefix(tree, offset+1);
        printf("block:\n");
        mrb_parser_dump(mrb, tree->cdr, offset+2);
      }
    }
    break;

  case NODE_ZSUPER:
    printf("NODE_ZSUPER:\n");
    if (tree) {
      dump_prefix(tree, offset+1);
      printf("args:\n");
      dump_recur(mrb, tree->car, offset+2);
      if (tree->cdr) {
        dump_prefix(tree, offset+1);
        printf("block:\n");
        mrb_parser_dump(mrb, tree->cdr, offset+2);
      }
    }
    break;

  case NODE_RETURN:
    printf("NODE_RETURN:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_YIELD:
    printf("NODE_YIELD:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_BREAK:
    printf("NODE_BREAK:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_NEXT:
    printf("NODE_NEXT:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_REDO:
    printf("NODE_REDO\n");
    break;

  case NODE_RETRY:
    printf("NODE_RETRY\n");
    break;

  case NODE_LVAR:
    printf("NODE_LVAR %s\n", mrb_sym_name(mrb, sym(tree)));
    break;

  case NODE_GVAR:
    printf("NODE_GVAR %s\n", mrb_sym_name(mrb, sym(tree)));
    break;

  case NODE_IVAR:
    printf("NODE_IVAR %s\n", mrb_sym_name(mrb, sym(tree)));
    break;

  case NODE_CVAR:
    printf("NODE_CVAR %s\n", mrb_sym_name(mrb, sym(tree)));
    break;

  case NODE_NVAR:
    printf("NODE_NVAR %d\n", intn(tree));
    break;

  case NODE_CONST:
    printf("NODE_CONST %s\n", mrb_sym_name(mrb, sym(tree)));
    break;

  case NODE_MATCH:
    printf("NODE_MATCH:\n");
    dump_prefix(tree, offset + 1);
    printf("lhs:\n");
    mrb_parser_dump(mrb, tree->car, offset + 2);
    dump_prefix(tree, offset + 1);
    printf("rhs:\n");
    mrb_parser_dump(mrb, tree->cdr, offset + 2);
    break;

  case NODE_BACK_REF:
    printf("NODE_BACK_REF: $%c\n", intn(tree));
    break;

  case NODE_NTH_REF:
    printf("NODE_NTH_REF: $%d\n", intn(tree));
    break;

  case NODE_ARG:
    printf("NODE_ARG %s\n", mrb_sym_name(mrb, sym(tree)));
    break;

  case NODE_BLOCK_ARG:
    printf("NODE_BLOCK_ARG:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_INT:
    printf("NODE_INT %s base %d\n", (char*)tree->car, intn(tree->cdr->car));
    break;

  case NODE_FLOAT:
    printf("NODE_FLOAT %s\n", (char*)tree);
    break;

  case NODE_NEGATE:
    printf("NODE_NEGATE:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_STR:
    printf("NODE_STR %s len %d\n", str_dump(mrb, (char*)tree->car, intn(tree->cdr)), intn(tree->cdr));
    break;

  case NODE_DSTR:
    printf("NODE_DSTR:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_XSTR:
    printf("NODE_XSTR %s len %d\n", str_dump(mrb, (char*)tree->car, intn(tree->cdr)), intn(tree->cdr));
    break;

  case NODE_DXSTR:
    printf("NODE_DXSTR:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_REGX:
    printf("NODE_REGX /%s/%s\n", (char*)tree->car, (char*)tree->cdr);
    break;

  case NODE_DREGX:
    printf("NODE_DREGX:\n");
    dump_recur(mrb, tree->car, offset+1);
    dump_prefix(tree, offset);
    printf("tail: %s\n", (char*)tree->cdr->cdr->car);
    if (tree->cdr->cdr->cdr->car) {
      dump_prefix(tree, offset);
      printf("opt: %s\n", (char*)tree->cdr->cdr->cdr->car);
    }
    if (tree->cdr->cdr->cdr->cdr) {
      dump_prefix(tree, offset);
      printf("enc: %s\n", (char*)tree->cdr->cdr->cdr->cdr);
    }
    break;

  case NODE_SYM:
    printf("NODE_SYM :%s (%d)\n", mrb_sym_dump(mrb, sym(tree)),
           intn(tree));
    break;

  case NODE_DSYM:
    printf("NODE_DSYM:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_WORDS:
    printf("NODE_WORDS:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_SYMBOLS:
    printf("NODE_SYMBOLS:\n");
    dump_recur(mrb, tree, offset+1);
    break;

  case NODE_LITERAL_DELIM:
    printf("NODE_LITERAL_DELIM\n");
    break;

  case NODE_SELF:
    printf("NODE_SELF\n");
    break;

  case NODE_NIL:
    printf("NODE_NIL\n");
    break;

  case NODE_TRUE:
    printf("NODE_TRUE\n");
    break;

  case NODE_FALSE:
    printf("NODE_FALSE\n");
    break;

  case NODE_ALIAS:
    printf("NODE_ALIAS %s %s:\n",
        mrb_sym_dump(mrb, sym(tree->car)),
        mrb_sym_dump(mrb, sym(tree->cdr)));
    break;

  case NODE_UNDEF:
    printf("NODE_UNDEF");
    {
      node *t = tree;
      while (t) {
        printf(" %s", mrb_sym_dump(mrb, sym(t->car)));
        t = t->cdr;
      }
    }
    printf(":\n");
    break;

  case NODE_CLASS:
    printf("NODE_CLASS:\n");
    if (tree->car->car == nint(0)) {
      dump_prefix(tree, offset+1);
      printf(":%s\n", mrb_sym_name(mrb, sym(tree->car->cdr)));
    }
    else if (tree->car->car == nint(1)) {
      dump_prefix(tree, offset+1);
      printf("::%s\n", mrb_sym_name(mrb, sym(tree->car->cdr)));
    }
    else {
      mrb_parser_dump(mrb, tree->car->car, offset+1);
      dump_prefix(tree, offset+1);
      printf("::%s\n", mrb_sym_name(mrb, sym(tree->car->cdr)));
    }
    if (tree->cdr->car) {
      dump_prefix(tree, offset+1);
      printf("super:\n");
      mrb_parser_dump(mrb, tree->cdr->car, offset+2);
    }
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr->cdr->car->cdr, offset+2);
    break;

  case NODE_MODULE:
    printf("NODE_MODULE:\n");
    if (tree->car->car == nint(0)) {
      dump_prefix(tree, offset+1);
      printf(":%s\n", mrb_sym_name(mrb, sym(tree->car->cdr)));
    }
    else if (tree->car->car == nint(1)) {
      dump_prefix(tree, offset+1);
      printf("::%s\n", mrb_sym_name(mrb, sym(tree->car->cdr)));
    }
    else {
      mrb_parser_dump(mrb, tree->car->car, offset+1);
      dump_prefix(tree, offset+1);
      printf("::%s\n", mrb_sym_name(mrb, sym(tree->car->cdr)));
    }
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr->car->cdr, offset+2);
    break;

  case NODE_SCLASS:
    printf("NODE_SCLASS:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    dump_prefix(tree, offset+1);
    printf("body:\n");
    mrb_parser_dump(mrb, tree->cdr->car->cdr, offset+2);
    break;

  case NODE_DEF:
    printf("NODE_DEF:\n");
    dump_prefix(tree, offset+1);
    printf("%s\n", mrb_sym_dump(mrb, sym(tree->car)));
    tree = tree->cdr;
    {
      node *n2 = tree->car;
      mrb_bool first_lval = TRUE;

      if (n2 && (n2->car || n2->cdr)) {
        dump_prefix(n2, offset+1);
        printf("local variables:\n");
        dump_prefix(n2, offset+2);
        while (n2) {
          if (n2->car) {
            if (!first_lval) printf(", ");
            printf("%s", mrb_sym_name(mrb, sym(n2->car)));
            first_lval = FALSE;
          }
          n2 = n2->cdr;
        }
        printf("\n");
      }
    }
    tree = tree->cdr;
    if (tree->car) {
      dump_args(mrb, tree->car, offset);
    }
    mrb_parser_dump(mrb, tree->cdr->car, offset+1);
    break;

  case NODE_SDEF:
    printf("NODE_SDEF:\n");
    mrb_parser_dump(mrb, tree->car, offset+1);
    tree = tree->cdr;
    dump_prefix(tree, offset+1);
    printf(":%s\n", mrb_sym_dump(mrb, sym(tree->car)));
    tree = tree->cdr->cdr;
    if (tree->car) {
      dump_args(mrb, tree->car, offset+1);
    }
    tree = tree->cdr;
    mrb_parser_dump(mrb, tree->car, offset+1);
    break;

  case NODE_POSTEXE:
    printf("NODE_POSTEXE:\n");
    mrb_parser_dump(mrb, tree, offset+1);
    break;

  case NODE_HEREDOC:
    printf("NODE_HEREDOC (<<%s):\n", ((parser_heredoc_info*)tree)->term);
    dump_recur(mrb, ((parser_heredoc_info*)tree)->doc, offset+1);
    break;

  case NODE_ARGS_TAIL:
    printf("NODE_ARGS_TAIL:\n");
    {
      node *kws = tree->car;

      while (kws) {
        mrb_parser_dump(mrb, kws->car, offset+1);
        kws = kws->cdr;
      }
    }
    tree = tree->cdr;
    if (tree->car) {
      mrb_assert(intn(tree->car->car) == NODE_KW_REST_ARGS);
      mrb_parser_dump(mrb, tree->car, offset+1);
    }
    tree = tree->cdr;
    if (tree->car) {
      dump_prefix(tree, offset+1);
      printf("block='%s'\n", mrb_sym_name(mrb, sym(tree->car)));
    }
    break;

  case NODE_KW_ARG:
    printf("NODE_KW_ARG %s:\n", mrb_sym_name(mrb, sym(tree->car)));
    mrb_parser_dump(mrb, tree->cdr->car, offset + 1);
    break;

  case NODE_KW_REST_ARGS:
    if (tree)
      printf("NODE_KW_REST_ARGS %s\n", mrb_sym_name(mrb, sym(tree)));
    else
      printf("NODE_KW_REST_ARGS\n");
    break;

  default:
    printf("node type: %d (0x%x)\n", nodetype, (unsigned)nodetype);
    break;
  }
#endif
}

typedef mrb_bool mrb_parser_foreach_top_variable_func(mrb_state *mrb, mrb_sym sym, void *user);
void mrb_parser_foreach_top_variable(mrb_state *mrb, struct mrb_parser_state *p, mrb_parser_foreach_top_variable_func *func, void *user);

void
mrb_parser_foreach_top_variable(mrb_state *mrb, struct mrb_parser_state *p, mrb_parser_foreach_top_variable_func *func, void *user)
{
  const mrb_ast_node *n = p->tree;
  if ((intptr_t)n->car == NODE_SCOPE) {
    n = n->cdr->car;
    for (; n; n = n->cdr) {
      mrb_sym sym = sym(n->car);
      if (sym && !func(mrb, sym, user)) break;
    }
  }
}
