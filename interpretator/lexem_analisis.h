#ifndef LEXEM_ANALISIS_H
#define LEXEM_ANALISIS_H

#include "main.h"

void modificate(lexem_list **lex_head);
//Получение значения из строки по типу
void get_value(Lexem *lexem);
void lex_analisis(FILE *,lexem_list **lex_head,struct errors_list **er_head);
int GetLexemType(char *lexem,int line_pos,lexem_list **lex_head,struct errors_list **er_head);

#endif