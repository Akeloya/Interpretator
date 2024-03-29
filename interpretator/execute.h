#pragma once

#include "Lexem.h"
#include "Errors.h"
#include "list.h"
#include "Common.h"

using namespace Interpreter::Collections;

void struct_execute(execute ** root,lexem_list** lex_head,List<Error>*er_head);

execute* read_instruction(lexem_list ** p);

lexem_list* read_expression(lexem_list** lex_head);

Lexem pop_expres(lexem_list ** stack);

void push_expres(Lexem lexem,lexem_list **stack);

void subtree(item* left,item *site,item** root,bool pos);

void modificate_expres(lexem_list **lex_head,bool root);

void infix(item *root);

int read_root(execute ** root,lexem_list ** p);

void read_return(execute ** root,lexem_list ** lex_head);

void read_declaration(execute ** root,lexem_list ** lex_head);

void read_assignment(execute ** root,lexem_list ** lex_head);

void read_function(execute ** root,lexem_list ** lex_head);

void read_while(execute ** root,lexem_list ** lex_head);

void read_if(execute ** root,lexem_list ** lex_head);

execute* read_block(lexem_list ** lex_head);

execute * line(lexem_list **lex_head,int *type);

void last_checkout(execute *root,List<Error>*er_head,List<Error>*war_head,_lists **list);

void last_block_checkout(execute *root,List<Error>* er_head,List<Error>* war_head,_lists **list,int return_type);

int do_execute(execute *root,List<Error>*er_head,List<Error>*war_head,_lists **list);

bool add_to_var_list(lexem_list** vl,Lexem lexem,int type);

Lexem* in_var_list(lexem_list* vl,Lexem lexem);

bool add_to_funct_list(funct_list** fl,Lexem *lex_head,int nParam);

int type_expression(lexem_list *lex_head);

bool check_expression(lexem_list * p,lexem_list* l,List<Error>* er_head);

void assignment(Lexem *lex1,Lexem lex2);

Lexem count_expres(lexem_list **lex_head,lexem_list *vl);

Lexem count(Lexem operand1,Lexem operand2,Lexem _operator);

lexem_list* prepare_to_read(lexem_list *p);

bool check_bool_express(lexem_list* p,lexem_list *vl);

lexem_list* update_bool_param(lexem_list *p);
