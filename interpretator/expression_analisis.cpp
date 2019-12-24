#include "expression_analisis.h"
#include "Stack.h"
#include "Stack.cpp"

void expression_analisis(lexem_list **lex_head,errors_list** er_head,Stack<int>* stack, int exit_code)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;

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
							move_to_err_list(I_NO_CLOSE_BRACKET,p->prew->lexem.line_pos,er_head);
							(*lex_head) = p->prew;
							return;
						}
						else
						{
							stack->Pop();
							stack->Push(I_EXIT);
							move_to_err_list(I_UNEXTENDED_ID,p->lexem.line_pos,er_head);
							return;
						}
						break;
					}
					move_to_err_list(I_ERR_IN_EXPRESION,p->lexem.line_pos,er_head);
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
					exit = TRUE;
				}
				else
				{
					while(stack->Peek() != I_EXPRESSION)
					{
						switch(stack->Peek())
						{
						case(I_BRACKET_CLOSE):
							{
								move_to_err_list(I_NO_BRACKET_CLOSE,p->lexem.line_pos,er_head);
								break;
							}
						}
						stack->Pop();
					}
					exit = TRUE;
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
							move_to_err_list(I_SF_BRACKET_CLOSE,p->lexem.line_pos,er_head);
						else
							exit = TRUE;
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
								move_to_err_list(I_ILLEGAL_EXPRES,p->lexem.line_pos,er_head);
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
									move_to_err_list(I_NEED_L_VALUE,p->lexem.line_pos,er_head);
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
								move_to_err_list(I_ILLEGAL_EXPRES,p->lexem.line_pos,er_head);
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
									move_to_err_list(I_NEED_L_VALUE,p->lexem.line_pos,er_head);
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
						move_to_err_list(I_NO_IDENTIFICATOR,p->lexem.line_pos,er_head);
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
								exit = TRUE;
								break;
							}
							else
							{
								if(p->lexem.type != I_BLOCK_OPEN)
								{
									stack->Pop();
									exit = TRUE;
									break;
								}
								else
								{
									stack->Pop();
									stack->Push(I_EXIT);
									stack->Push(I_EXIT);
									move_to_err_list(I_NO_BRACKET_CLOSE,p->lexem.line_pos,er_head);
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
									move_to_err_list(I_NO_SEMICOLON,p->lexem.line_pos,er_head);
									move_to_err_list(I_ERR_IN_EXPRESION,p->lexem.line_pos,er_head);
									exit = TRUE;
									break;
								}
								else
								{
									exit = TRUE;
									break;
								}
							}
							else
							{
								exit = TRUE;
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
				move_to_err_list(I_NO_BRACKET_CLOSE,p->lexem.line_pos,er_head);
				break;
			}
		}
		stack->Pop();
	}
	(*lex_head) = p;
}

void bool_expression_analisis(lexem_list **lex_head,errors_list** er_head,Stack<int>* stack)
{
	bool oper = FALSE,exit = FALSE;
	lexem_list *p = (*lex_head);
	if(p->lexem.type == I_IDENTIFIC && p->next!=0 && p->next->lexem.type == I_BRACKET_CLOSE)
	{
		if(p->lexem.name[0] != 39 && p->lexem.name[0] != '"')
		{
			p = p->next;
			(*lex_head) = p;
			return;
		}
		move_to_err_list(I_ERR_BOOL_EXPRES,p->lexem.line_pos,er_head);
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
							oper = TRUE;
						else
						{
							move_to_err_list(I_ERR_IN_BOOL_OPER1,p->lexem.line_pos,er_head);
						}
						break;
					}
					if(p->lexem.type == I_AND || p->lexem.type == I_OR)
					{
						if(oper)
							oper = FALSE;
						else
						{
							move_to_err_list(I_ERR_IN_BOOL_OPER2,p->lexem.line_pos,er_head);
						}
						break;
					}
					if(p->lexem.type == I_BRACKET_CLOSE)
						exit = TRUE;
					if(stack->Peek() == I_EXIT)
					{
						stack->Pop();
						exit = TRUE;
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
							oper = TRUE;
						else
						{
							move_to_err_list(I_ERR_IN_BOOL_OPER1,p->lexem.line_pos,er_head);
						}
						break;
					}
					if(p->lexem.type == I_AND || p->lexem.type == I_OR)
					{
						if(oper)
							oper = FALSE;
						else
						{
							move_to_err_list(I_ERR_IN_BOOL_OPER2,p->lexem.line_pos,er_head);
						}
						break;
					}
					if(p->lexem.type == I_BRACKET_CLOSE)
						exit = TRUE;
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
		move_to_err_list(I_UNCOMPLETED_EXPR,p->lexem.line_pos,er_head);
	}
	(*lex_head) = p;
}

void return_analisis(lexem_list** lex_head, errors_list** er_head, Stack<int>* stack)
{
	lexem_list* p = (*lex_head);

	bool exit = FALSE;

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
						exit = TRUE;
					}
					else
					{
						move_to_err_list(I_ERR_IN_END_LINE, p->lexem.line_pos, er_head);
						exit = TRUE;
					}
				}
				else
					move_to_err_list(I_ILLEGAL_EXPRES, p->lexem.line_pos, er_head);
			}
			break;
		}
		}
		if (p != 0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}