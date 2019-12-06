#ifndef CONDITION_STACK_H
#define CONDITION_STACK_H

#include "main.h"

typedef struct condition_stack
{
	condition_stack* next;
	int condition;
}c_stack;

void push_condition(int n_state,c_stack** stack_head);
int peek_condition(c_stack* stack_head);
int pop_condition(c_stack** stack_head);

#endif