#ifndef BODY_ANALISIS_H
#define BODY_ANALISIS_H

#include "main.h"
#include "hand_errors.h"
#include "condition_stack.h"

void block_analisis(lexem_list ** lex_head,errors_list ** er_head,c_stack **stack_head,int exit_code);

#endif