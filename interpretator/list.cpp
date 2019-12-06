#include "list.h"

void move_to_list(Lexem sLexem,struct lexem_list **head)
{
	lexem_list * p =(lexem_list*)malloc(sizeof(lexem_list));
	memset(p->lexem.name,0,256);
	p->lexem = sLexem;
	if((*head) == 0)
	{
		p->prew = (*head);
		p->next = 0;
		(*head) = (lexem_list*)malloc(sizeof(lexem_list));
		(*head) = p;
	}
	else
	{
		p->prew = (*head);
		(*head)->next = p;
		(*head) = p;
		(*head)->next = 0;
	}
}

void move_to_var_list(Lexem sLexem,struct varible_list **head)
{
	varible_list * p =(varible_list*)malloc(sizeof(varible_list));
	memset(p->lexem.name,0,256);
	p->lexem = sLexem;
	if((*head) == 0)
	{
		p->prew = (*head);
		p->next = 0;
		(*head) = (varible_list*)malloc(sizeof(varible_list));
		(*head) = p;
	}
	else
	{
		p->prew = (*head);
		(*head)->next = p;
		(*head) = p;
		(*head)->next = 0;
	}
}

int search_in_var_list(Lexem lexem,varible_list *var_list)
{
	varible_list* p = var_list;
	if(p!=0)
	{
		while(p!=0)
		{
			if(p->lexem.type == lexem.type && strcmp(p->lexem.name,lexem.name) == 0)
				return TRUE;
			p = p->next;
		}
	}
	return FALSE;
}