#ifndef IF_ANALISIS_H
#define IF_ANALISIS_H

#include "main.h"
#include "hand_errors.h"
#include "condition_stack.h"
#include "list.h"

void if_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head);

#endif