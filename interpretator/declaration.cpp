#include "declaration.h"
#include "expression_analisis.h"
#include "stack.h"
#include "list.h"

using namespace Interpreter::Collections;

void declaration_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack)
{
	lexem_list *p = (*lex_head);

	bool exit = false;

	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(stack->Peek() == I_DECLARATION)
				{
					stack->Push(I_IDENTIFIC);
					break;
				}
				else
				{
					er_head->Add(Error(I_TYPE_IN_TYPE,p->lexem.line_pos));
					
				}
				break;
			}
		case(I_IDENTIFIC):
			{
				if(stack->Peek() == I_IDENTIFIC)
				{
					stack->Pop();
					if(p->next != 0)
					{
						if(p->next->lexem.type == I_ASSIGNMENT)
						{
							stack->Push(I_ASSIGNMENT);
							assignment_analisis(&p,er_head,stack);
							stack->Pop();
							if(p->lexem.type == I_COMMA)
								stack->Push(I_IDENTIFIC);
							if(p->lexem.type == I_SEMICOLON)
							{
								//stack->Push(I_SEMICOLON,stack_head);
								exit = true;
								break;
							}
						}
						else
						{
							if(p->next->lexem.type == I_SEMICOLON)
							{
								stack->Push(I_SEMICOLON);
								break;
							}
							if(p->next->lexem.type == I_COMMA)
							{
								stack->Push(I_IDENTIFIC);
								break;
							}
						}
					}
				}
				break;
			}
		case(I_COMMA):
			{
				if(stack->Peek() == I_SEMICOLON)
				{
					stack->Pop();
					stack->Push(I_IDENTIFIC);
				}
				break;
			}
		case(I_SEMICOLON):
			{
				if(stack->Peek() == I_SEMICOLON)
				{
					stack->Pop();
				}
				else
					er_head->Add(Error(I_ERR_IN_END_LINE,p->lexem.line_pos));
				exit = true;
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
	if(stack->Peek() != I_DECLARATION)
	{
		int cond = 0;
		while((cond = stack->Peek()) != I_DECLARATION)
		{
			if(cond == I_SEMICOLON)
				er_head->Add(Error(I_NO_IDENTIFICATOR,p->lexem.line_pos));
			stack->Pop();
		}
	}
	(*lex_head) = p;
}


void assignment_analisis(lexem_list** lex_head, List<Error>* er_head, Stack<int>* stack)
{
	lexem_list* p = (*lex_head);

	bool exit = false;

	while (p != 0 && !exit)
	{
		switch (p->lexem.type)
		{
		case(I_IDENTIFIC):
		{
			if (stack->Peek() == I_ASSIGNMENT)
			{
				stack->Push(I_ASSIGNMENT);
				break;
			}
			if (stack->Peek() == I_IDENTIFIC)
			{
				stack->Pop();
				stack->Push(I_EXPRESSION);
				expression_analisis(&p, er_head, stack, I_SEMICOLON);
				exit = true;
				stack->Pop();
			}
			break;
		}
		case(I_ASSIGNMENT):
		{
			if (stack->Peek() == I_ASSIGNMENT)
			{
				stack->Pop();
				stack->Push(I_IDENTIFIC);
			}
			break;
		}
		case(I_INC_MINUS):
		{
			if (stack->Peek() == I_IDENTIFIC)
			{
				stack->Pop();
				stack->Push(I_EXPRESSION);
				expression_analisis(&p, er_head, stack, I_SEMICOLON);
				exit = true;
				stack->Pop();
			}
			break;
		}
		case(I_INC_PLUS):
		{
			if (stack->Peek() == I_IDENTIFIC)
			{
				stack->Pop();
				stack->Push(I_EXPRESSION);
				expression_analisis(&p, er_head, stack, I_SEMICOLON);
				exit = true;
				stack->Pop();
			}
			break;
		}
		case(I_BRACKET_OPEN):
		{
			if (stack->Peek() == I_IDENTIFIC)
			{
				stack->Pop();
				stack->Push(I_EXPRESSION);
				expression_analisis(&p, er_head, stack, I_SEMICOLON);
				exit = true;
				stack->Pop();
			}
			break;
		}
		default:
		{
			break;
		}
		}
		if (!exit)
			p = p->next;
	}
	(*lex_head) = p;
}