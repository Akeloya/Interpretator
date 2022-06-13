#pragma once

#include "Common.h"
#include "list.h"
#include "Errors.h"
#include "Lexem.h"

using namespace Interpreter::Collections;

void modificate(lexem_list **lex_head);
//Получение значения из строки по типу
void lex_analisis(FILE *,lexem_list **lex_head, List<Error>*er_head);
int GetLexemType(char *lexem,int line_pos,lexem_list **lex_head, List<Error>*er_head);
