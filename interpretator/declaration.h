#pragma once

#include "Common.h"
#include "Errors.h"
#include "condition_stack.h"
#include "Stack.h"
#include "list.h"

using namespace Interpreter::Collections;

void declaration_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack);

void assignment_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack);
