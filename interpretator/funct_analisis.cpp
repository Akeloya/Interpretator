#include "funct_analisis.h"
#include "body_analisis.h"
#include "expression_analisis.h"
#include "stack.h"

void funct_analisis(lexem_list **lex_head,errors_list** er_head,Stack<int>* stack)
{
	lexem_list  *p = (*lex_head);

	bool exit = FALSE;

	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(stack->Peek() == I_FUNCT_ANALISIS)
				{
					if(strcmp(p->lexem.name,"int") == 0 || strcmp(p->lexem.name,"double") == 0 || strcmp(p->lexem.name,"char") == 0 || strcmp("void",p->lexem.name) == 0)
					{
						stack->Push(I_IDENTIFIC);
						break;
					}
					move_to_err_list(I_ERR_AFTER_BLOCK,p->lexem.line_pos,er_head);
					break;
				}
				break;
			}
		case(I_IDENTIFIC):
			{
				if(stack->Peek() == I_IDENTIFIC)
				{
					stack->Pop();
					stack->Push(I_BRACKET_OPEN);
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
				if(stack->Peek() == I_BRACKET_OPEN)
				{
					stack->Pop();
					stack->Push(I_PARAMETERS);
					parameters_analisis(&p,er_head,stack);
					stack->Pop();
				}
				break;
			}
		case(I_BLOCK_OPEN):
			{
				stack->Push(I_BODY);
				block_analisis(&p,er_head,stack,I_BLOCK_CLOSE);
				stack->Pop();
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


void parameters_analisis(lexem_list **lex_head,errors_list** er_head,Stack<int>* stack)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;
	
	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(stack->Peek() == I_CONST_WORD)
				{
					stack->Pop();
					stack->Push(I_IDENTIFIC);
				}
				else
				{
					move_to_err_list(I_UNEXTENDED_C_W,p->lexem.line_pos,er_head);
				}
				break;
			}
		case(I_IDENTIFIC):
			{
				if(stack->Peek() == I_IDENTIFIC)
				{
					stack->Pop();
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
				if(stack->Peek() == I_PARAMETERS)
				{
					exit = TRUE;
					break;
				}
				else
				{
					if (stack->Peek() != I_CONST_WORD)
						move_to_err_list(I_UNEXTENDED_BRACK, p->lexem.line_pos, er_head);
					else
						stack->Pop();
					exit = TRUE;
					break;
				}
			}
		case(I_COMMA):
			{
				if(stack->Peek() == I_PARAMETERS)
				{
					stack->Push(I_CONST_WORD);
				}
				else
				{
					move_to_err_list(I_UNEXTENDED_COMMA,p->lexem.line_pos,er_head);
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(stack->Peek() == I_PARAMETERS)
				{
					stack->Push(I_CONST_WORD);
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

void funct_inline_analisis(lexem_list **lex_head,errors_list** er_head,Stack<int>* stack)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;

	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_IDENTIFIC):
			{
				if(stack->Peek() == I_FUNCT_ANALISIS)
				{
					stack->Push(I_BRACKET_OPEN);
					break;
				}
				if(stack->Peek() == I_IDENTIFIC)
				{
					stack->Pop();
					//stack->Push(I_DECLARATION,stack_head);
					if(p->next->lexem.type != I_BRACKET_CLOSE)
					{
						stack->Push(I_EXPRESSION);
						expression_analisis(&p,er_head,stack,I_BRACKET_CLOSE);
						stack->Pop();
						if(p->lexem.type == I_BRACKET_CLOSE)
						{
							stack->Push(I_SEMICOLON);
							break;
						}
					}
					else
					{
						stack->Push(I_COMMA);
						break;
					}
					//stack->Pop()
					stack->Push(I_IDENTIFIC);
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(stack->Peek() == I_BRACKET_OPEN)
				{
					stack->Pop();
					stack->Push(I_IDENTIFIC);
				}
				else
				{
					//printf("asdfbvasfbv");
				}
				break;
			}
		case(I_COMMA):
			{
				if(stack->Peek() == I_COMMA)
				{
					stack->Pop();
					stack->Push(I_IDENTIFIC);
					break;
				}
				//printf("sdg");
				break;
			}
		case(I_BRACKET_CLOSE):
			{
				if(stack->Peek() == I_COMMA)
				{
					stack->Pop();
					stack->Push(I_SEMICOLON);
					break;
				}
				if(stack->Peek() == I_IDENTIFIC)
				{
					stack->Pop();
					stack->Push(I_SEMICOLON);
					move_to_err_list(I_NO_FUNCT_PARAM,p->lexem.line_pos,er_head);
					break;
				}
				//printf("zfg");
				break;
			}
		case(I_STRING):
			{
				if(stack->Peek() == I_IDENTIFIC)
				{
					stack->Pop();
					stack->Push(I_COMMA);
					break;
				}
				//printf("zsdfg");
				break;
			}
		case(I_SEMICOLON):
			{
				if(stack->Peek() == I_SEMICOLON)
				{
					stack->Pop();
					exit = TRUE;
					break;
				}
				else
				{
					//printf("asfglhg");
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