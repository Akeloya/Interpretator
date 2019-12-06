#ifndef LIST_H
#define LIST_H

#include "main.h"

void move_to_list(Lexem sLexem,lexem_list **head);

void move_to_var_list(Lexem sLexem,struct varible_list **head);

int search_in_var_list(Lexem lexem,varible_list *var_list);

#endif