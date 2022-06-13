#include "expression_analisis.h"
#include "Stack.h"
#include "Stack.cpp"
#include "list.h"

using namespace Interpreter::Collections;

void expression_analisis(lexem_list **lex_head,List<Error>* er_head,Stack<int>* stack, int exit_code)
{
	lexem_list *p = (*lex_head);

	bool exit = false;

	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_IDENTIFIC):
			{
				if(stack->Peek() == I_EXPRESSION)
				{
					stack->Push(I_OPERATOR);
					break;
				}
				if(stack->Peek() == I_IDENTIFIC)
				{
					stack->Pop();
					stack->Push(I_OPERATOR);
					break;
				}
				if(stack->Peek() == I_OPERATOR)
				{
					if(p->lexem.line_pos != p->prew->lexem.line_pos)
					{
						//3 указателя было
						if(stack->Take(4) == I_IF)
						{
							stack->Pop();
							stack->Pop();
							stack->Push(I_EXIT);
							stack->Push(I_EXPRESSION);
							er_head->Add(Error(I_NO_CLOSE_BRACKET,p->prew->lexem.line_pos));
							(*lex_head) = p->prew;
							return;
						}
						else
						{
							stack->Pop();
							stack->Push(I_EXIT);
							er_head->Add(Error(I_UNEXTENDED_ID,p->lexem.line_pos));
							return;
						}
						break;
					}
					er_head->Add(Error(I_ERR_IN_EXPRESION,p->lexem.line_pos));
					break;
				}
				//move_to_err_list
				break;
			}
		case(I_SEMICOLON):
			{
				if(stack->Peek() == I_OPERATOR)
				{
					stack->Pop();
					exit = true;
				}
				else
				{
					while(stack->Peek() != I_EXPRESSION)
					{
						switch(stack->Peek())
						{
						case(I_BRACKET_CLOSE):
							{
								er_head->Add(Error(I_NO_BRACKET_CLOSE,p->lexem.line_pos));
								break;
							}
						}
						stack->Pop();
					}
					exit = true;
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(stack->Peek() == I_IDENTIFIC)
				{
					stack->Pop();
					stack->Push(I_BRACKET_CLOSE);
					stack->Push(I_IDENTIFIC);
					break;
				}
				else
				{
					if(stack->Peek() == I_EXPRESSION)
					{
						stack->Push(I_BRACKET_CLOSE);
						stack->Push(I_IDENTIFIC);
						break;
					}
					printf("svas");
				}
				break;
			}
		case(I_BRACKET_CLOSE):
			{
				if(stack->Peek() == I_OPERATOR)
				{
					stack->Pop();
					if(stack->Peek() == I_BRACKET_CLOSE)
					{
						stack->Pop();
						stack->Push(I_OPERATOR);
						break;
					}
					else
					{
						if(exit_code != I_BRACKET_CLOSE)
							er_head->Add(Error(I_SF_BRACKET_CLOSE,p->lexem.line_pos));
						else
							exit = true;
						break;
					}
				}
				else
				{
					printf("expression error");
					break;
				}
			}
		case(I_INC_PLUS):
			{
				if(stack->Peek() == I_EXPRESSION || stack->Peek() == I_IDENTIFIC)
				{
					if(stack->Peek() == I_EXPRESSION)
						stack->Push(I_IDENTIFIC);
					break;
				}
				else
				{
					if(stack->Peek() == I_OPERATOR)
					{
						stack->Pop();
						if(p->next!=0)
							if(p->next->lexem.type != I_BRACKET_CLOSE && p->next->lexem.type != I_COMMA && p->next->lexem.type && I_SEMICOLON && !(p->next->lexem.type >= I_LOW && p->next->lexem.type <= I_DIVISION))
							{
								er_head->Add(Error(I_ILLEGAL_EXPRES,p->lexem.line_pos));
							}
							else
							{
								if(p->next->lexem.type == I_BRACKET_CLOSE)
								{
									stack->Push(I_OPERATOR);
									break;
								}
								else
								{
									er_head->Add(Error(I_NEED_L_VALUE,p->lexem.line_pos));
									break;
									//printf("sfzfbvzxf\n");
								}
							}
						break;
					}
					printf("expres svdsav\n");
				}
				break;
			}
		case(I_INC_MINUS):
			{
				if(stack->Peek() == I_EXPRESSION || stack->Peek() == I_IDENTIFIC)
				{
					if(stack->Peek() == I_EXPRESSION)
						stack->Push(I_IDENTIFIC);
					break;
				}
				else
				{
					if(stack->Peek() == I_OPERATOR)
					{
						stack->Pop();
						if(p->next!=0)
							if(p->next->lexem.type != I_BRACKET_CLOSE && p->next->lexem.type != I_COMMA && p->next->lexem.type && I_SEMICOLON && !(p->next->lexem.type >= I_LOW && p->next->lexem.type <= I_DIVISION))
							{
								er_head->Add(Error(I_ILLEGAL_EXPRES,p->lexem.line_pos));
							}
							else
							{
								if(p->next->lexem.type == I_BRACKET_CLOSE)
								{
									stack->Push(I_OPERATOR);
									break;
								}
								else
								{
									er_head->Add(Error(I_NEED_L_VALUE,p->lexem.line_pos));
									break;
									//printf("sfzfbvzxf\n");
								}
							}
						break;
					}
					printf("expres svdsav\n");
				}
				break;
				break;
			}
		default:
			{
				if(p->lexem.type >= I_PERCENT && p->lexem.type <= I_DIVISION)
				{
					if(stack->Peek() == I_OPERATOR)
					{
						stack->Pop();
						stack->Push(I_IDENTIFIC);
						break;
					}
					else
					{
						er_head->Add(Error(I_NO_IDENTIFICATOR,p->lexem.line_pos));
					}
				}
				else
				{
					if(p->lexem.type >= I_LOW && p->lexem.line_pos <= I_AND)
					{
						int check = stack->Take(4);//3 ссылки от корня
						if(check == I_IF || check == I_WHILE)
						{
							if(check == I_IF)
							{
								stack->Pop();
								exit = true;
								break;
							}
							else
							{
								if(p->lexem.type != I_BLOCK_OPEN)
								{
									stack->Pop();
									exit = true;
									break;
								}
								else
								{
									stack->Pop();
									stack->Push(I_EXIT);
									stack->Push(I_EXIT);
									er_head->Add(Error(I_NO_BRACKET_CLOSE,p->lexem.line_pos));
									(*lex_head) = p->prew;
									return;
								}
							}
						}
						else
						{
							if(stack->Peek() == I_OPERATOR)
								stack->Pop();
							int check = stack->Take(3);//2 ссылки было
							if(check != I_DECLARATION)
							{
								if(stack->Take(2) != I_FUNCT_ANALISIS)
								{
									er_head->Add(Error(I_NO_SEMICOLON,p->lexem.line_pos));
									er_head->Add(Error(I_ERR_IN_EXPRESION,p->lexem.line_pos));
									exit = true;
									break;
								}
								else
								{
									exit = true;
									break;
								}
							}
							else
							{
								exit = true;
								break;
							}
						}
					}
					printf("fbvasfbv");
				}
			}
		}
		if(p!=0 && !exit)
			p = p->next;
	}
	while(stack->Peek() != I_EXPRESSION)
	{
		switch(stack->Peek())
		{
		case(I_BRACKET_CLOSE):
			{
				er_head->Add(Error(I_NO_BRACKET_CLOSE,p->lexem.line_pos));
				break;
			}
		}
		stack->Pop();
	}
	(*lex_head) = p;
}

void bool_expression_analisis(lexem_list **lex_head,List<Error>* er_head, Stack<int>* stack)
{
	bool oper = false,exit = false;
	lexem_list *p = (*lex_head);
	if(p->lexem.type == I_IDENTIFIC && p->next!=0 && p->next->lexem.type == I_BRACKET_CLOSE)
	{
		if(p->lexem.name[0] != 39 && p->lexem.name[0] != '"')
		{
			p = p->next;
			(*lex_head) = p;
			return;
		}
		er_head->Add(Error(I_ERR_BOOL_EXPRES,p->lexem.line_pos));
	}
	while(p!=0 && p->lexem.type != I_BRACKET_CLOSE && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_IDENTIFIC):
			{
				if(stack->Peek() == I_EXPRESSION)
				{
					stack->Push(I_EXPRESSION);
					expression_analisis(&p,er_head,stack,I_BRACKET_CLOSE);
					stack->Pop();
					if(p->lexem.type >= I_LOW && p->lexem.type <= I_NOT_BIGGER)
					{
						if(!oper)
							oper = true;
						else
						{
							er_head->Add(Error(I_ERR_IN_BOOL_OPER1,p->lexem.line_pos));
						}
						break;
					}
					if(p->lexem.type == I_AND || p->lexem.type == I_OR)
					{
						if(oper)
							oper = false;
						else
						{
							er_head->Add(Error(I_ERR_IN_BOOL_OPER2,p->lexem.line_pos));
						}
						break;
					}
					if(p->lexem.type == I_BRACKET_CLOSE)
						exit = true;
					if(stack->Peek() == I_EXIT)
					{
						stack->Pop();
						exit = true;
					}
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				stack->Push(I_EXPRESSION);
				expression_analisis(&p,er_head,stack,0);
				stack->Pop();
				if(p->lexem.type >= I_LOW && p->lexem.type <= I_NOT_BIGGER)
					{
						if(!oper)
							oper = true;
						else
						{
							er_head->Add(Error(I_ERR_IN_BOOL_OPER1,p->lexem.line_pos));
						}
						break;
					}
					if(p->lexem.type == I_AND || p->lexem.type == I_OR)
					{
						if(oper)
							oper = false;
						else
						{
							er_head->Add(Error(I_ERR_IN_BOOL_OPER2,p->lexem.line_pos));
						}
						break;
					}
					if(p->lexem.type == I_BRACKET_CLOSE)
						exit = true;
				break;
			}
		default:
			{
				if(p->lexem.type >= I_LOW && p->lexem.type <= I_NOT_BIGGER)
				{
					break;
				}
				if(p->lexem.type == I_AND || p->lexem.type == I_OR)
				{
					break;
				}
				break;
			}
		}
		if(p!=0 && !exit)
			p = p->next;
	}
	if(!oper)
	{
		er_head->Add(Error(I_UNCOMPLETED_EXPR,p->lexem.line_pos));
	}
	(*lex_head) = p;
}

void return_analisis(lexem_list** lex_head, List<Error>* er_head, Stack<int>* stack)
{
	lexem_list* p = (*lex_head);

	bool exit = false;

	while (p != 0 && p->lexem.type != I_SEMICOLON)
	{
		switch (p->lexem.type)
		{
		case(I_CONST_WORD):
		{
			if (stack->Peek() == I_RETURN)
			{
				stack->Push(I_IDENTIFIC);
			}
			break;
		}
		default:
		{
			if (stack->Peek() == I_IDENTIFIC)
			{
				if (p->lexem.type == I_IDENTIFIC || p->lexem.type == I_INC_PLUS || p->lexem.type == I_INC_MINUS || p->lexem.type == I_BRACKET_OPEN)
				{
					stack->Pop();
					stack->Push(I_EXPRESSION);
					expression_analisis(&p, er_head, stack, I_SEMICOLON);
					stack->Pop();
					if (p->lexem.type == I_SEMICOLON)
					{
						exit = true;
					}
					else
					{
						er_head->Add(Error(I_ERR_IN_END_LINE, p->lexem.line_pos));
						exit = true;
					}
				}
				else
					er_head->Add(Error(I_ILLEGAL_EXPRES, p->lexem.line_pos));
			}
			break;
		}
		}
		if (p != 0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}