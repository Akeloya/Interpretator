#include "while_analisis.h"
#include "expression_analisis.h"
#include "body_analisis.h"
#include "if_analisis.h"
#include "funct_analisis.h"

using namespace Interpreter::Collections;

void while_analisis(lexem_list **lex_head,errors_list** er_head,Stack<int>* stack)
{
	lexem_list *p = (*lex_head);
	
	bool exit = FALSE;

	while(p!= 0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(stack->Peek() == I_WHILE)
				{
					stack->Push(I_BRACKET_OPEN);
					break;
				}
				if(stack->Peek() == I_BLOCK_OPEN)
				{
					stack->Pop();
					if(strcmp("if",p->lexem.name) == 0)
					{
						stack->Push(I_IF);
						if_analisis(&p,er_head,stack);
						stack->Pop();
						if(stack->Peek() == I_WHILE)
							exit = TRUE;
						break;
					}
					if(strcmp("while",p->lexem.name) == 0)
					{
						stack->Push(I_WHILE);
						while_analisis(&p,er_head,stack);
						stack->Pop();
						if(stack->Peek() == I_WHILE)
							exit = TRUE;
						break;
					}
					if(strcmp("return",p->lexem.name) == 0)
					{
						stack->Push(I_RETURN);
						return_analisis(&p,er_head,stack);
						stack->Pop();
					}
					break;
				}
				printf("while");
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(stack->Peek() == I_BRACKET_OPEN)
				{
					stack->Pop();
					stack->Push(I_EXPRESSION);
					break;
				}
				if(stack->Peek() == I_EXPRESSION)
				{
					bool_expression_analisis(&p,er_head,stack);
					stack->Pop();
					stack->Push(I_BLOCK_OPEN);
					break;
				}
				printf("while");
				break;
			}
		case(I_BRACKET_CLOSE):
			{
				if(stack->Peek() == I_BRACKET_CLOSE)
				{
					stack->Pop();
					stack->Push(I_BLOCK_OPEN);
					break;
				}
				printf("while");
				break;
			}
		case(I_IDENTIFIC):
			{
				if(stack->Peek() == I_EXPRESSION)
				{
					bool_expression_analisis(&p,er_head,stack);
					stack->Pop();
					stack->Push(I_BLOCK_OPEN);
					break;
				}
				if(stack->Peek() == I_BODY)
				{
					block_analisis(&p,er_head,stack,I_BLOCK_CLOSE);
					stack->Pop();
					exit = TRUE;
					break;
				}
				if(stack->Peek() == I_BLOCK_OPEN)
				{
					stack->Pop();
					if(p->next->lexem.type == I_BRACKET_OPEN)
					{
						stack->Push(I_FUNCT_ANALISIS);
						funct_inline_analisis(&p,er_head,stack);
						stack->Pop();
						exit = TRUE;
						break;
					}
				}
				printf("while");
				break;
			}
		case(I_BLOCK_OPEN):
			{
				if(stack->Peek() == I_BLOCK_OPEN)
				{
					stack->Pop();
					stack->Push(I_BODY);
					block_analisis(&p,er_head,stack,I_BLOCK_CLOSE);
					stack->Pop();
					exit = TRUE;
					break;
				}
				printf("while");
				break;
			}
		default:
			{
				printf("while");
				break;
			}
		}
		if(p != 0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}