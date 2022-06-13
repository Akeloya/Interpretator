#include "funct_analisis.h"
#include "body_analisis.h"
#include "expression_analisis.h"
#include "stack.h"
#include "list.h"
#include "Errors.h"

using namespace Interpreter::Collections;

void funct_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack)
{
	lexem_list  *p = (*lex_head);

	bool exit = false;

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
					er_head->Add(Error(I_ERR_AFTER_BLOCK,p->lexem.line_pos));
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
					er_head->Add(Error(I_UNEXTENDED,p->lexem.line_pos));
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
					exit = true;
				break;
			}
		case(I_BLOCK_CLOSE):
			{
				exit = true;
				break;
			}
		default:
			{
				er_head->Add(Error(I_UNEXTENDED,p->lexem.line_pos));
				break;
			}
		}
		if(p!=0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}


void parameters_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack)
{
	lexem_list *p = (*lex_head);

	bool exit = false;
	
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
					er_head->Add(Error(I_UNEXTENDED_C_W,p->lexem.line_pos));
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
						er_head->Add(Error(I_ERR_IN_IDENTIFIC,p->lexem.line_pos));
					}
				}
				else
				{
					er_head->Add(Error(I_UNEXTENDED_ID,p->lexem.line_pos));
				}
				break;
			}
		case(I_BRACKET_CLOSE):
			{
				if(stack->Peek() == I_PARAMETERS)
				{
					exit = true;
					break;
				}
				else
				{
					if (stack->Peek() != I_CONST_WORD)
						er_head->Add(Error(I_UNEXTENDED_BRACK, p->lexem.line_pos));
					else
						stack->Pop();
					exit = true;
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
					er_head->Add(Error(I_UNEXTENDED_COMMA,p->lexem.line_pos));
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

void funct_inline_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack)
{
	lexem_list *p = (*lex_head);

	bool exit = false;

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
					er_head->Add(Error(I_NO_FUNCT_PARAM,p->lexem.line_pos));
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
					exit = true;
					break;
				}
				else
				{
					//printf("asfglhg");
				}
			}
		default:
			{
				er_head->Add(Error(I_ILLEGAL_EXPRES,p->lexem.line_pos));
				break;
			}
		}
		if(p!=0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}