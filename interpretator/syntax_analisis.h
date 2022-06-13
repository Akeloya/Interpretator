#pragma once

#include "Errors.h"
#include "Stack.h"
#include "list.h"
#include "Lexem.h"

using namespace Interpreter::Collections;

int syntax_analisis(lexem_list *lex_head,Stack<int>* stack,lexem_list **var_list,List<Error>* er_head);

