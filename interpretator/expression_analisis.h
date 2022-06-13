#pragma once

#include "Common.h"
#include "Errors.h"
#include "condition_stack.h"
#include "Stack.h"
#include "list.h"

using namespace Interpreter::Collections;

void expression_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack,int exit_code);

void bool_expression_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack);

void return_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack);

