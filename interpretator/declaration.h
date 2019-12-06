#ifndef DECLARETION_H
#define DECLARETION_H

#include "main.h"
#include "hand_errors.h"
#include "condition_stack.h"

void declaration_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head);

void assignment_analisis(lexem_list **lex_head,errors_list ** er_head,c_stack ** stack_head);


#endif