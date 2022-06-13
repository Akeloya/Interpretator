#pragma once

#include "Errors.h"
#include "list.h"
#include "Stack.h"
#include "Lexem.h"

using namespace Interpreter::Collections;

void if_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack);
