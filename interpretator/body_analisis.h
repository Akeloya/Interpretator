#pragma once

#include "Common.h"
#include "Errors.h"
#include "condition_stack.h"
#include "Stack.h"
#include "list.h"
#include "declaration.h"
#include "if_analisis.h"
#include "expression_analisis.h"
#include "funct_analisis.h"
#include "while_analisis.h"

//using namespace Interpreter::Collections;

void block_analisis(lexem_list ** lex_head, Interpreter::Collections::List<Error>* er_head, Interpreter::Collections::Stack<int>* stack,int exit_code);
