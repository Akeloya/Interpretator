#include "syntax_analisis.h"
#include "funct_analisis.h"


int syntax_analisis(lexem_list *lex_head,c_stack **stack_head,varible_list **var_list,errors_list** er_head)
{
	lexem_list *p = lex_head;
	while(p!=0)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(peek_condition(*stack_head) == I_PROGRAMM)
				{
					if(strcmp("int",p->lexem.name) == 0 || strcmp("double",p->lexem.name) == 0 || strcmp("char",p->lexem.name) == 0 || strcmp("void",p->lexem.name) == 0)
					{
						push_condition(I_IDENTIFIC,stack_head);
						break;
					}
					else
					{
						move_to_err_list(I_ILLEGAL_EXPRES,p->lexem.line_pos,er_head);
						break;
					}
				}
				else
				{
					move_to_err_list(I_UNEXTENDED,p->lexem.line_pos,er_head);
				}
				break;
			}
		case(I_IDENTIFIC):
			{
				if(peek_condition(*stack_head) == I_IDENTIFIC)
				{
					pop_condition(stack_head);
					if(p->next->lexem.type == I_BRACKET_OPEN)
					{
						p = p->prew;
						push_condition(I_FUNCT_ANALISIS,stack_head);
						funct_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
						break;
					}
					else
					{
						move_to_err_list(I_UNEXTENDED,p->lexem.line_pos,er_head);
					}
				}
				if(peek_condition(*stack_head) == I_PROGRAMM)
				{
					if(p->next->lexem.type == I_BRACKET_OPEN)
					{
						p = p->prew;
						push_condition(I_FUNCT_ANALISIS,stack_head);
						funct_analisis(&p,er_head,stack_head);
						pop_condition(stack_head);
					}
					else
					{
						move_to_err_list(I_UNEXTENDED,p->lexem.line_pos,er_head);
					}
				}
				break;
			}
		default:
			{
				break;
			}
		}
		if(p!=0)
			p = p->next;
		else
		{
			if(peek_condition(*stack_head) == I_PROGRAMM)
				break;
			else
				move_to_err_list(I_NO_END_OF_FILE,0,er_head);
		}
	}
	return 0;
}