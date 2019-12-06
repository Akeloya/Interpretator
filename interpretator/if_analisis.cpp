#include "if_analisis.h"
#include "expression_analisis.h"
#include "body_analisis.h"
#include "funct_analisis.h"
#include "declaration.h"
#include "while_analisis.h"


void if_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;

	while(p != 0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(peek_condition(*stack_head) == I_IF)
				{
					if(strcmp("if",p->lexem.name) == 0)
					{
						push_condition(I_BRACKET_OPEN,stack_head);
						break;
					}
					if(strcmp("else",p->lexem.name) == 0)
					{
						push_condition(I_BLOCK_OPEN,stack_head);
						break;
					}
				}
				if(peek_condition(*stack_head) == I_BLOCK_OPEN)
				{
					pop_condition(stack_head);
					if(strcmp("if",p->lexem.name) == 0)
					{
						push_condition(I_IF,stack_head);
						if_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
						if(peek_condition(*stack_head) == I_IF)
						{
							exit = TRUE;
						}
						break;
					}
					if(strcmp("while",p->lexem.name) == 0)
					{
						push_condition(I_WHILE,stack_head);
						while_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
						if(peek_condition(*stack_head) == I_IF)
							exit = TRUE;
						break;
					}
					if(strcmp("return",p->lexem.name) == 0)
					{
						push_condition(I_RETURN,stack_head);
						return_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
					}
				}
				printf("ifasefasf");
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(peek_condition(*stack_head) == I_BRACKET_OPEN)
				{
					pop_condition(stack_head);
					push_condition(I_EXPRESSION,stack_head);
					break;
				}
				printf("ifasdgfasdvg");
				break;
			}
		case(I_BRACKET_CLOSE):
			{
				if(peek_condition(*stack_head) == I_EXPRESSION)
				{
					pop_condition(stack_head);
					break;
				}
				printf("ifasdf");
				break;
			}
		case(I_BLOCK_OPEN):
			{
				if(peek_condition(*stack_head) == I_BLOCK_OPEN)
				{
					pop_condition(stack_head);
					push_condition(I_BODY,stack_head);
					block_analisis(&p,er_head,stack_head,I_BLOCK_CLOSE);
					if(p!=0 && p->next!=0 && strcmp(p->next->lexem.name,"else") != 0)
						exit = TRUE;
					pop_condition(stack_head);
					break;
				}
				printf("ifasdfgasdfg");
				break;
			}
		case(I_IDENTIFIC):
			{
				if(peek_condition(*stack_head) == I_EXPRESSION)
				{
					bool_expression_analisis(&p,er_head,stack_head);
					pop_condition(stack_head);
					push_condition(I_BLOCK_OPEN,stack_head);
				}
				else
				{
					if(peek_condition(*stack_head) == I_BLOCK_OPEN)
					{
						pop_condition(stack_head);
						if(p->next!=0 && p->next->lexem.type == I_ASSIGNMENT)
						{
							push_condition(I_ASSIGNMENT,stack_head);
							assignment_analisis(&p,er_head,stack_head);
							pop_condition(stack_head);
							if(p->next!=0 && strcmp(p->next->lexem.name,"else") != 0)
								exit = TRUE;
							break;
						}
						if(p->next!=0 && p->next->lexem.type == I_BRACKET_OPEN)
						{
							push_condition(I_FUNCT_ANALISIS,stack_head);
							funct_inline_analisis(&p,er_head,stack_head);
							pop_condition(stack_head);
							if(p!=0 && p->next!=0 && strcmp(p->next->lexem.name,"else") != 0)
								exit = TRUE;
							break;
						}
						printf("ifasvasdv");
					}
				}
				break;
			}
		default:
			{
				printf("ifasdvasdfasdvasdfasdf");
				break;
			}
		}
		if(p != 0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}