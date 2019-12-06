#ifndef FUNCT_ANALISIS_H
#define FUNCT_ANALISIS_H

#include "main.h"
#include "hand_errors.h"
#include "condition_stack.h"


void funct_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head);

void funct_inline_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head);

void parameters_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head);

#endif