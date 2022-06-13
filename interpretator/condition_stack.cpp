#include "condition_stack.h"

void push_condition(int condition,c_stack** stack_head)
{
	if( (*stack_head) == 0 )
	{
		c_stack* p = new c_stack();
		p->next = 0;
		p->condition = condition;
		(*stack_head) = p;
	}
	else
	{
		c_stack* p = new c_stack();
		p->next = (*stack_head);
		p->condition = condition;
		(*stack_head) = p;
	}
}


int peek_condition(c_stack* stack_head)
{
	if(stack_head!=0)
		return stack_head->condition;
	else
		return 0;
}


int pop_condition(c_stack** stack_head)
{
	int condition = 0;
	c_stack *p =(*stack_head);
	if( p != 0 )
	{
		condition = p->condition;
		if(p->next != 0)
		{
			(*stack_head) = (*stack_head)->next;
			delete p;
		}
		else
		{
			(*stack_head)->next = 0;
			delete p;
		}
	}
	return condition;
}