#include "declaration.h"
//#include "body_analisis.h"
#include "expression_analisis.h"

void declaration_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;

	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(peek_condition(*stack_head) == I_DECLARATION)
				{
					push_condition(I_IDENTIFIC,stack_head);
					break;
				}
				else
				{
					move_to_err_list(I_TYPE_IN_TYPE,p->lexem.line_pos,er_head);
				}
				break;
			}
		case(I_IDENTIFIC):
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					if(p->next != 0)
					{
						if(p->next->lexem.type == I_ASSIGNMENT)
						{
							push_condition(I_ASSIGNMENT,stack_head);
							assignment_analisis(&p,er_head,stack_head);
							pop_condition(stack_head);
							if(p->lexem.type == I_COMMA)
								push_condition(I_IDENTIFIC,stack_head);
							if(p->lexem.type == I_SEMICOLON)
							{
								//push_condition(I_SEMICOLON,stack_head);
								exit = TRUE;
								break;
							}
						}
						else
						{
							if(p->next->lexem.type == I_SEMICOLON)
							{
								push_condition(I_SEMICOLON,stack_head);
								break;
							}
							if(p->next->lexem.type == I_COMMA)
							{
								push_condition(I_IDENTIFIC,stack_head);
								break;
							}
						}
					}
				}
				break;
			}
		case(I_COMMA):
			{
				if(peek_condition(*stack_head) == I_SEMICOLON)
				{
					pop_condition(stack_head);
					push_condition(I_IDENTIFIC,stack_head);
				}
				break;
			}
		case(I_SEMICOLON):
			{
				if(peek_condition(*stack_head) == I_SEMICOLON)
				{
					pop_condition(stack_head);
				}
				else
					move_to_err_list(I_ERR_IN_END_LINE,p->lexem.line_pos,er_head);
				exit = TRUE;
				break;
			}
		default:
			{
				break;
			}
		}
		if(p!=0 && !exit)
			p = p->next;
	}
	if(peek_condition(*stack_head) != I_DECLARATION)
	{
		int cond = 0;
		while((cond = peek_condition(*stack_head)) != I_DECLARATION)
		{
			if(cond == I_SEMICOLON)
				move_to_err_list(I_NO_IDENTIFICATOR,p->lexem.line_pos,er_head);
			pop_condition(stack_head);
		}
	}
	(*lex_head) = p;
}


void assignment_analisis(lexem_list **lex_head,errors_list ** er_head,c_stack ** stack_head)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;

	while(p != 0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_IDENTIFIC):
			{
				if(peek_condition(*stack_head) == I_ASSIGNMENT)
				{
					push_condition(I_ASSIGNMENT,stack_head);
					break;
				}
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					push_condition(I_EXPRESSION,stack_head);
					expression_analisis(&p,er_head,stack_head,I_SEMICOLON);
					exit = TRUE;
					pop_condition(stack_head);
				}
				break;
			}
		case(I_ASSIGNMENT):
			{
				if(peek_condition(*stack_head) == I_ASSIGNMENT)
				{
					pop_condition(stack_head);
					push_condition(I_IDENTIFIC,stack_head);
				}
				break;
			}
		case(I_INC_MINUS):
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					push_condition(I_EXPRESSION,stack_head);
					expression_analisis(&p,er_head,stack_head,I_SEMICOLON);
					exit = TRUE;
					pop_condition(stack_head);
				}
				break;
			}
		case(I_INC_PLUS):
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					push_condition(I_EXPRESSION,stack_head);
					expression_analisis(&p,er_head,stack_head,I_SEMICOLON);
					exit = TRUE;
					pop_condition(stack_head);
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					push_condition(I_EXPRESSION,stack_head);
					expression_analisis(&p,er_head,stack_head,I_SEMICOLON);
					exit = TRUE;
					pop_condition(stack_head);
				}
				break;
			}
		default:
			{
				break;
			}
		}
		if(!exit)
			p = p->next;
	}
	(*lex_head) = p;
}