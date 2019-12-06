#ifndef LEXEM_ANALISIS_H
#define LEXEM_ANALISIS_H

#include "main.h"

int lexem_analysis(FILE *fin,lexem_list **lex_head,struct errors_list **er_head);

void modificate(lexem_list **lex_head);

int type_lexem(char* lxm);

void get_value(Lexem *lexem);


void lex_analisis(FILE *,lexem_list **lex_head,struct errors_list **er_head);
int lexem_analisis(char *lexem,int line_pos,lexem_list **lex_head,struct errors_list **er_head);

#endif