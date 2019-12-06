#ifndef HAND_ERRORS_H
#define HAND_ERRORS_H

#include "main.h"

struct errors_list
{
	int lise_pos;
	int type;
	errors_list *next;
	errors_list *prew;
};

char* get_error_string(int error,int line_pos,char* err);

void move_to_err_list(int type,int line_pos,struct errors_list **head);

#endif