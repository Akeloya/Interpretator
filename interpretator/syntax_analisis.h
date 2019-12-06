#ifndef SYNTAX_ANALISIS_H
#define SYNTAX_ANALISIS_H

#include "main.h"
#include "hand_errors.h"
#include "condition_stack.h"

int syntax_analisis(lexem_list *lex_head,c_stack **stack_head,varible_list **var_list,errors_list** er_head);

#endif