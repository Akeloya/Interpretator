#include "syntax_analisis.h"
#include "list.h"
#include "Lexem.h"
#include "Common.h"
#include "funct_analisis.h"

using namespace Interpreter::Collections;

int syntax_analisis(lexem_list *lex_head,Stack<int>* stack,lexem_list **var_list,List<Error>* er_head)
{
	lexem_list *p = lex_head;
	while(p!=0)
	{
		switch(p->lexem.type)
		{
		case(I_CONST_WORD):
			{
				if(stack->Peek() == I_PROGRAMM)
				{
					if(strcmp("int",p->lexem.name) == 0 || strcmp("double",p->lexem.name) == 0 || strcmp("char",p->lexem.name) == 0 || strcmp("void",p->lexem.name) == 0)
					{
						stack->Push(I_IDENTIFIC);
						break;
					}
					else
					{
						er_head->Add(Error(I_ILLEGAL_EXPRES,p->lexem.line_pos));
						break;
					}
				}
				else
				{
					er_head->Add(Error(I_UNEXTENDED,p->lexem.line_pos));
				}
				break;
			}
		case(I_IDENTIFIC):
			{
				if(stack->Peek() == I_IDENTIFIC)
				{
					stack->Pop();
					if(p->next->lexem.type == I_BRACKET_OPEN)
					{
						p = p->prew;
						stack->Push(I_FUNCT_ANALISIS);
						funct_analisis(&p,er_head,stack);
						stack->Pop();
						break;
					}
					else
					{
						er_head->Add(Error(I_UNEXTENDED,p->lexem.line_pos));
					}
				}
				if(stack->Peek() == I_PROGRAMM)
				{
					if(p->next->lexem.type == I_BRACKET_OPEN)
					{
						p = p->prew;
						stack->Push(I_FUNCT_ANALISIS);
						funct_analisis(&p,er_head,stack);
						stack->Pop();
					}
					else
					{
						er_head->Add(Error(I_UNEXTENDED,p->lexem.line_pos));
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
			if(stack->Peek() == I_PROGRAMM)
				break;
			else
				er_head->Add(Error(I_NO_END_OF_FILE,0));
		}
	}
	return 0;
}