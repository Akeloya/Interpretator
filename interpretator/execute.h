#ifndef EXECUTE_H
#define EXECUTE_H

#include "main.h"
#include "hand_errors.h"

void struct_execute(execute ** root,lexem_list** lex_head,errors_list **er_head);

execute* read_instruction(lexem_list ** p);

lexem_list* read_expression(lexem_list** lex_head);

Lexem pop_expres(lexem_list ** stack);

void push_expres(Lexem lexem,lexem_list **stack);

int getprior(Lexem lexem);

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

void last_checkout(execute *root,errors_list **er_head,errors_list **war_head,_lists **list);

void last_block_checkout(execute *root,errors_list **er_head,errors_list **war_head,_lists **list,int return_type);

int do_execute(execute *root,errors_list **er_head,errors_list **war_head,_lists **list);

bool add_to_var_list(varible_list** vl,Lexem lexem,int type);

Lexem* in_var_list(varible_list* vl,Lexem lexem);

bool add_to_funct_list(funct_list** fl,Lexem *lex_head,int nParam);

int type_expression(lexem_list *lex_head);

bool check_expression(lexem_list * p,varible_list* l,errors_list** er_head);

void assignment(Lexem *lex1,Lexem lex2);

Lexem count_expres(lexem_list **lex_head,varible_list *vl);

Lexem count(Lexem operand1,Lexem operand2,Lexem _operator);

lexem_list* prepare_to_read(lexem_list *p);

bool check_bool_express(lexem_list* p,varible_list *vl);

lexem_list* update_bool_param(lexem_list *p);

#endif