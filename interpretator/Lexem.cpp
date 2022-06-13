#include "Lexem.h"

void move_to_list(Lexem sLexem, lexem_list** head)
{
	lexem_list* p = new lexem_list();// (lexem_list*)malloc(sizeof(lexem_list));
	memset(p->lexem.name, 0, 256);
	p->lexem = sLexem;
	if ((*head) == 0)
	{
		p->prew = (*head);
		p->next = 0;
		(*head) = new lexem_list();//(lexem_list*)malloc(sizeof(lexem_list));
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

void Lexem::GetValue()
{
	switch (type_data)
	{
	case(I_INTEGER):
	{
		int len = strlen(name);
		int ans = 0;
		int step = 1;
		for (int i = 0; i < len; i++)
		{
			ans += (name[len - 1 - i] - '0') * step;
			step *= 10;
		}
		Idata = ans;
		break;
	}
	case(I_DOUBLE):
	{
		int len = strlen(name);
		double ans = 0;
		double step = 1;
		int k = 0, i = 0;
		for (i = 0; i < len; i++)
			if (name[i] == '.')
				break;
		k = i;
		for (i = 0; i < k; i++)
		{
			ans += (name[k - 1 - i] - '0') * step;
			step *= 10;
		}
		step = 0.1;
		for (i = k + 1; i < len; i++)
		{
			ans += (name[i] - '0') * step;
			step /= 10;
		}
		Ddata = ans;
		break;
	}
	case(I_CHAR):
	{
		Cdata = name[1];
		break;
	}
	}
}
