#ifndef EXPRESSION_ANALISIS_H
#define EXPRESSION_ANALISIS_H

#include "main.h"
#include "hand_errors.h"
#include "condition_stack.h"

void expression_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head,int exit_code);

void bool_expression_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head);

void return_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head);

#endif