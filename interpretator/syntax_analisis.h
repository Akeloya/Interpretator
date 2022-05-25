#pragma once

#include "main.h"
#include "hand_errors.h"
#include "condition_stack.h"
#include "Stack.h"

using namespace Interpreter::Collections;

int syntax_analisis(lexem_list *lex_head,Stack<int>* stack,lexem_list **var_list,errors_list** er_head);

