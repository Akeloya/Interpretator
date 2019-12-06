#include "funct_analisis.h"
#include "body_analisis.h"
#include "expression_analisis.h"

void funct_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head)
{
	lexem_list  *p = (*lex_head);

	bool exit = FALSE;

	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(peek_condition(*stack_head) == I_FUNCT_ANALISIS)
				{
					if(strcmp(p->lexem.name,"int") == 0 || strcmp(p->lexem.name,"double") == 0 || strcmp(p->lexem.name,"char") == 0 || strcmp("void",p->lexem.name) == 0)
					{
						push_condition(I_IDENTIFIC,stack_head);
						break;
					}
					move_to_err_list(I_ERR_AFTER_BLOCK,p->lexem.line_pos,er_head);
					break;
				}
				break;
			}
		case(I_IDENTIFIC):
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					push_condition(I_BRACKET_OPEN,stack_head);
					break;
				}
				else
				{
					move_to_err_list(I_UNEXTENDED,p->lexem.line_pos,er_head);
					break;
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(peek_condition(*stack_head) == I_BRACKET_OPEN)
				{
					pop_condition(stack_head);
					push_condition(I_PARAMETERS,stack_head);
					parameters_analisis(&p,er_head,stack_head);
					pop_condition(stack_head);
				}
				break;
			}
		case(I_BLOCK_OPEN):
			{
				push_condition(I_BODY,stack_head);
				block_analisis(&p,er_head,stack_head,I_BLOCK_CLOSE);
				pop_condition(stack_head);
				if(p->next == 0)
					exit = TRUE;
				break;
			}
		case(I_BLOCK_CLOSE):
			{
				exit = TRUE;
				break;
			}
		default:
			{
				move_to_err_list(I_UNEXTENDED,p->lexem.line_pos,er_head);
				break;
			}
		}
		if(p!=0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}


void parameters_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;
	
	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(peek_condition(*stack_head) == I_CONST_WORD)
				{
					pop_condition(stack_head);
					push_condition(I_IDENTIFIC,stack_head);
				}
				else
				{
					move_to_err_list(I_UNEXTENDED_C_W,p->lexem.line_pos,er_head);
				}
				break;
			}
		case(I_IDENTIFIC):
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					if(p->lexem.type_data == I_INTEGER || p->lexem.type_data == I_DOUBLE || p->lexem.type_data == I_CHAR)
					{
						move_to_err_list(I_ERR_IN_IDENTIFIC,p->lexem.line_pos,er_head);
					}
				}
				else
				{
					move_to_err_list(I_UNEXTENDED_ID,p->lexem.line_pos,er_head);
				}
				break;
			}
		case(I_BRACKET_CLOSE):
			{
				if(peek_condition(*stack_head) == I_PARAMETERS)
				{
					exit = TRUE;
					break;
				}
				else
				{
					if(peek_condition(*stack_head) != I_CONST_WORD)
						move_to_err_list(I_UNEXTENDED_BRACK,p->lexem.line_pos,er_head);
					else
						pop_condition(stack_head);
					exit = TRUE;
					break;
				}
			}
		case(I_COMMA):
			{
				if(peek_condition(*stack_head) == I_PARAMETERS)
				{
					push_condition(I_CONST_WORD,stack_head);
				}
				else
				{
					move_to_err_list(I_UNEXTENDED_COMMA,p->lexem.line_pos,er_head);
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(peek_condition(*stack_head) == I_PARAMETERS)
				{
					push_condition(I_CONST_WORD,stack_head);
				}
				break;
			}
		default:
			{
				break;
			}
		}
		if(!exit && p!=0)
			p = p->next;
	}
	(*lex_head) = p;
}

void funct_inline_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;

	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_IDENTIFIC):
			{
				if(peek_condition(*stack_head) == I_FUNCT_ANALISIS)
				{
					push_condition(I_BRACKET_OPEN,stack_head);
					break;
				}
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					//push_condition(I_DECLARATION,stack_head);
					if(p->next->lexem.type != I_BRACKET_CLOSE)
					{
						push_condition(I_EXPRESSION,stack_head);
						expression_analisis(&p,er_head,stack_head,I_BRACKET_CLOSE);
						pop_condition(stack_head);
						if(p->lexem.type == I_BRACKET_CLOSE)
						{
							push_condition(I_SEMICOLON,stack_head);
							break;
						}
					}
					else
					{
						push_condition(I_COMMA,stack_head);
						break;
					}
					//pop_condition(stack_head);
					push_condition(I_IDENTIFIC,stack_head);
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(peek_condition(*stack_head) == I_BRACKET_OPEN)
				{
					pop_condition(stack_head);
					push_condition(I_IDENTIFIC,stack_head);
				}
				else
				{
					printf("asdfbvasfbv");
				}
				break;
			}
		case(I_COMMA):
			{
				if(peek_condition(*stack_head) == I_COMMA)
				{
					pop_condition(stack_head);
					push_condition(I_IDENTIFIC,stack_head);
					break;
				}
				printf("sdg");
				break;
			}
		case(I_BRACKET_CLOSE):
			{
				if(peek_condition(*stack_head) == I_COMMA)
				{
					pop_condition(stack_head);
					push_condition(I_SEMICOLON,stack_head);
					break;
				}
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					push_condition(I_SEMICOLON,stack_head);
					move_to_err_list(I_NO_FUNCT_PARAM,p->lexem.line_pos,er_head);
					break;
				}
				printf("zfg");
				break;
			}
		case(I_STRING):
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					push_condition(I_COMMA,stack_head);
					break;
				}
				printf("zsdfg");
				break;
			}
		case(I_SEMICOLON):
			{
				if(peek_condition(*stack_head) == I_SEMICOLON)
				{
					pop_condition(stack_head);
					exit = TRUE;
					break;
				}
				else
				{
					printf("asfglhg");
				}
			}
		default:
			{
				move_to_err_list(I_ILLEGAL_EXPRES,p->lexem.line_pos,er_head);
				break;
			}
		}
		if(p!=0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}