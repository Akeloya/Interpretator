#ifndef WHILE_ANALISIS_H
#define WHILE_ANALISIS_H

#include "main.h"
#include "hand_errors.h"
#include "list.h"
#include "condition_stack.h"

void while_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head);

#endif