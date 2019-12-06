#include "expression_analisis.h"

void expression_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head,int exit_code)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;

	while(p!=0 && !exit)
	{
		switch(p->lexem.type)
		{
		case(I_IDENTIFIC):
			{
				if(peek_condition(*stack_head) == I_EXPRESSION)
				{
					push_condition(I_OPERATOR,stack_head);
					break;
				}
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					push_condition(I_OPERATOR,stack_head);
					break;
				}
				if(peek_condition(*stack_head) == I_OPERATOR)
				{
					if(p->lexem.line_pos != p->prew->lexem.line_pos)
					{
						if(peek_condition((*stack_head)->next->next->next) == I_IF)
						{
							pop_condition(stack_head);
							pop_condition(stack_head);
							push_condition(I_EXIT,stack_head);
							push_condition(I_EXPRESSION,stack_head);
							move_to_err_list(I_NO_CLOSE_BRACKET,p->prew->lexem.line_pos,er_head);
							(*lex_head) = p->prew;
							return;
						}
						else
						{
							pop_condition(stack_head);
							push_condition(I_EXIT,stack_head);
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
				if(peek_condition(*stack_head) == I_OPERATOR)
				{
					pop_condition(stack_head);
					exit = TRUE;
				}
				else
				{
					while(peek_condition(*stack_head) != I_EXPRESSION)
					{
						switch(peek_condition(*stack_head))
						{
						case(I_BRACKET_CLOSE):
							{
								move_to_err_list(I_NO_BRACKET_CLOSE,p->lexem.line_pos,er_head);
								break;
							}
						}
						pop_condition(stack_head);
					}
					exit = TRUE;
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					push_condition(I_BRACKET_CLOSE,stack_head);
					push_condition(I_IDENTIFIC,stack_head);
					break;
				}
				else
				{
					if(peek_condition(*stack_head) == I_EXPRESSION)
					{
						push_condition(I_BRACKET_CLOSE,stack_head);
						push_condition(I_IDENTIFIC,stack_head);
						break;
					}
					printf("svas");
				}
				break;
			}
		case(I_BRACKET_CLOSE):
			{
				if(peek_condition(*stack_head) == I_OPERATOR)
				{
					pop_condition(stack_head);
					if(peek_condition(*stack_head) == I_BRACKET_CLOSE)
					{
						pop_condition(stack_head);
						push_condition(I_OPERATOR,stack_head);
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
				if(peek_condition(*stack_head) == I_EXPRESSION || peek_condition(*stack_head) == I_IDENTIFIC)
				{
					if(peek_condition(*stack_head) == I_EXPRESSION)
						push_condition(I_IDENTIFIC,stack_head);
					break;
				}
				else
				{
					if(peek_condition(*stack_head) == I_OPERATOR)
					{
						pop_condition(stack_head);
						if(p->next!=0)
							if(p->next->lexem.type != I_BRACKET_CLOSE && p->next->lexem.type != I_COMMA && p->next->lexem.type && I_SEMICOLON && !(p->next->lexem.type >= I_LOW && p->next->lexem.type <= I_DIVISION))
							{
								move_to_err_list(I_ILLEGAL_EXPRES,p->lexem.line_pos,er_head);
							}
							else
							{
								if(p->next->lexem.type == I_BRACKET_CLOSE)
								{
									push_condition(I_OPERATOR,stack_head);
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
				if(peek_condition(*stack_head) == I_EXPRESSION || peek_condition(*stack_head) == I_IDENTIFIC)
				{
					if(peek_condition(*stack_head) == I_EXPRESSION)
						push_condition(I_IDENTIFIC,stack_head);
					break;
				}
				else
				{
					if(peek_condition(*stack_head) == I_OPERATOR)
					{
						pop_condition(stack_head);
						if(p->next!=0)
							if(p->next->lexem.type != I_BRACKET_CLOSE && p->next->lexem.type != I_COMMA && p->next->lexem.type && I_SEMICOLON && !(p->next->lexem.type >= I_LOW && p->next->lexem.type <= I_DIVISION))
							{
								move_to_err_list(I_ILLEGAL_EXPRES,p->lexem.line_pos,er_head);
							}
							else
							{
								if(p->next->lexem.type == I_BRACKET_CLOSE)
								{
									push_condition(I_OPERATOR,stack_head);
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
					if(peek_condition(*stack_head) == I_OPERATOR)
					{
						pop_condition(stack_head);
						push_condition(I_IDENTIFIC,stack_head);
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
						if(peek_condition((*stack_head)->next->next->next) == I_IF || peek_condition((*stack_head)->next->next->next) == I_WHILE)
						{
							if(peek_condition((*stack_head)->next->next->next) == I_IF)
							{
								pop_condition(stack_head);
								exit = TRUE;
								break;
							}
							else
							{
								if(p->lexem.type != I_BLOCK_OPEN)
								{
									pop_condition(stack_head);
									exit = TRUE;
									break;
								}
								else
								{
									pop_condition(stack_head);
									push_condition(I_EXIT,stack_head);
									push_condition(I_EXIT,stack_head);
									move_to_err_list(I_NO_BRACKET_CLOSE,p->lexem.line_pos,er_head);
									(*lex_head) = p->prew;
									return;
								}
							}
						}
						else
						{
							if(peek_condition(*stack_head) == I_OPERATOR)
								pop_condition(stack_head);
							if(peek_condition((*stack_head)->next->next) != I_DECLARATION)
							{
								if(peek_condition((*stack_head)->next) != I_FUNCT_ANALISIS)
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
	while(peek_condition(*stack_head) != I_EXPRESSION)
	{
		switch(peek_condition(*stack_head))
		{
		case(I_BRACKET_CLOSE):
			{
				move_to_err_list(I_NO_BRACKET_CLOSE,p->lexem.line_pos,er_head);
				break;
			}
		}
		pop_condition(stack_head);
	}
	(*lex_head) = p;
}

void bool_expression_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head)
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
				if(peek_condition(*stack_head) == I_EXPRESSION)
				{
					push_condition(I_EXPRESSION,stack_head);
					expression_analisis(&p,er_head,stack_head,I_BRACKET_CLOSE);
					pop_condition(stack_head);
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
					if(peek_condition(*stack_head) == I_EXIT)
					{
						pop_condition(stack_head);
						exit = TRUE;
					}
				}
				break;
			}
		case(I_BRACKET_OPEN):
			{
				push_condition(I_EXPRESSION,stack_head);
				expression_analisis(&p,er_head,stack_head,0);
				pop_condition(stack_head);
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

void return_analisis(lexem_list **lex_head,errors_list** er_head,c_stack **stack_head)
{
	lexem_list *p = (*lex_head);

	bool exit = FALSE;

	while(p!=0 && p->lexem.type != I_SEMICOLON)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(peek_condition(*stack_head) == I_RETURN)
				{
					push_condition(I_IDENTIFIC,stack_head);
				}
				break;
			}
		default:
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					if(p->lexem.type == I_IDENTIFIC || p->lexem.type == I_INC_PLUS || p->lexem.type == I_INC_MINUS || p->lexem.type == I_BRACKET_OPEN)
					{
						pop_condition(stack_head);
						push_condition(I_EXPRESSION,stack_head);
						expression_analisis(&p,er_head,stack_head,I_SEMICOLON);
						pop_condition(stack_head);
						if(p->lexem.type == I_SEMICOLON)
						{
							exit = TRUE;
						}
						else
						{
							move_to_err_list(I_ERR_IN_END_LINE,p->lexem.line_pos,er_head);
							exit = TRUE;
						}
					}
					else
						move_to_err_list(I_ILLEGAL_EXPRES,p->lexem.line_pos,er_head);
				}
				break;
			}
		}
		if(p!= 0 && !exit)
			p = p->next;
	}
	(*lex_head) = p;
}