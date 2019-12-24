#pragma once

#include "main.h"
#include "hand_errors.h"
#include "condition_stack.h"
#include "list.h"
#include "Stack.h"

void if_analisis(lexem_list **lex_head,errors_list** er_head,Stack<int>* stack);
