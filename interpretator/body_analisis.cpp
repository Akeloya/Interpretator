#include "body_analisis.h"
#include "declaration.h"
#include "if_analisis.h"
#include "expression_analisis.h"
#include "funct_analisis.h"
#include "while_analisis.h"

void block_analisis(lexem_list ** lex_head,errors_list ** er_head,c_stack **stack_head,int exit_code)
{
	lexem_list* p = (*lex_head);

	bool exit = FALSE;

	if(p->lexem.type == I_BLOCK_OPEN)
		p = p->next;
	if(p==0)
	{
		move_to_err_list(I_DESTORY,0,er_head);
	}
	while(p!=0 && !exit && p->lexem.type != exit_code)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(peek_condition(*stack_head) == I_BODY)
				{
					if(strcmp("int",p->lexem.name) == 0 || strcmp("double",p->lexem.name) == 0 || strcmp("char",p->lexem.name) == 0)
					{
						push_condition(I_DECLARATION,stack_head);
						declaration_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
						break;
					}
					if(strcmp("while",p->lexem.name) == 0)
					{
						push_condition(I_WHILE,stack_head);
						while_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
						break;
					}
					if(strcmp("if",p->lexem.name) == 0)
					{
						push_condition(I_IF,stack_head);
						if_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
						break;
					}
					if(strcmp("return",p->lexem.name) == 0)
					{
						push_condition(I_RETURN,stack_head);
						return_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
						break;
					}
					printf("body");
				}
				break;
			}
		case(I_IDENTIFIC):
			{
				if(peek_condition(*stack_head) == I_BODY)
				{
					if(p->next->lexem.type == I_BRACKET_OPEN)
					{
						push_condition(I_FUNCT_ANALISIS,stack_head);
						funct_inline_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
						break;
					}
					if(p->next->lexem.type == I_ASSIGNMENT)
					{
						push_condition(I_ASSIGNMENT,stack_head);
						assignment_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
						break;
					}
					if(p->next->lexem.type == I_COMMA || p->next->lexem.type == I_SEMICOLON)
					{
						if(peek_condition((*stack_head)->next) == I_ASSIGNMENT)
						{
							exit = TRUE;
							break;
						}
						else
						{
							printf("body_dfb");
							//move_to_err_list(I_UNKNOWBLE,p->lexem.line_pos,er_head);
						}
					}
					if(p->next->lexem.type == I_INC_MINUS || p->next->lexem.type == I_INC_PLUS)
					{
						p = p->next;
						if(p->next !=0 && p->next->lexem.type == I_SEMICOLON)
						{
							p = p->next;
							break;
						}
						else
						{
							printf("bodi inc");
							break;
						}
					}
					move_to_err_list(I_NO_SEMICOLON,p->lexem.line_pos,er_head);
					//printf("body dfkbj");
				}
				break;
			}
		case(I_SEMICOLON):
			{
				break;
			}
		case(I_BLOCK_CLOSE):
			{
				move_to_err_list(I_SF_BLOCK_CLOSE,p->lexem.line_pos,er_head);
				break;
			}
		default:
			{
				if(p->lexem.type == I_INC_PLUS || p->lexem.type == I_INC_MINUS)
				{
					if(p->next!=0 && p->next->lexem.type == I_IDENTIFIC)
					{
						p = p->next;
						if(p->next != 0 && p->next->lexem.type == I_SEMICOLON)
						{
							p = p->next;
							break;
						}
						else
							printf("body asdvas");
					}
					printf("body asdvasdvasdvasdvasdv");
					break;
				}
				move_to_err_list(I_UNEXTENDED,p->lexem.line_pos,er_head);
				break;
			}
		}
		if(p!=0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}