#pragma once

#include "main.h"
#include "hand_errors.h"
#include "condition_stack.h"
#include "Stack.h"

using namespace Interpreter::Collections;

void declaration_analisis(lexem_list **lex_head,errors_list** er_head,Stack<int>* stack);

void assignment_analisis(lexem_list **lex_head,errors_list ** er_head,Stack<int>* stack);
