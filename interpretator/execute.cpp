#include "execute.h"
#include "list.h"
#include "i_string.h"

using namespace std;

void struct_execute(execute ** root,lexem_list** lex_head,errors_list **er_head)
{
	lexem_list *p = (*lex_head);
	
	execute *s_root = 0;
	if(!read_root(root,&p))
	{
		move_to_err_list(I_NO_MAIN,p->lexem.line_pos-1,er_head);
		move_to_err_list(I_DESTORY,p->lexem.line_pos-1,er_head);
		move_to_err_list(I_FATAL_ER_EXECUT,0,er_head);
		return;
	}
	
	s_root = *root;

	while(p!=0)
	{
		switch(p->lexem.type)
		{
			case(I_IDENTIFIC):
				{
					if(p->next->lexem.type == I_ASSIGNMENT)
					{
						read_assignment(root,&p);
						break;
					}
					if(p->next->lexem.type == I_BRACKET_OPEN)
					{
						read_function(root,&p);
						break;
					}
					if(p->next->lexem.type == I_INC_PLUS || p->next->lexem.type == I_INC_MINUS)
					{
					}
					break;
				}
			case(I_CONST_WORD):
				{
					if(strcmp("int",p->lexem.name) == 0 || strcmp("double",p->lexem.name) == 0 || strcmp("char",p->lexem.name) == 0)
					{
						read_declaration(root,&p);
						break;
					}
					if(strcmp("if",p->lexem.name) == 0)
					{
						read_if(root,&p);
						break;
					}
					if(strcmp("while",p->lexem.name) == 0)
					{
						read_while(root,&p);
						break;
					}
					if(strcmp("return",p->lexem.name) == 0)
					{
						read_return(root,&p);
						break;
					}
				}
			case(I_INC_PLUS):
				{
					break;
				}
			case(I_INC_MINUS):
				{
					break;
				}
		}
		p = p->next;
	}
	(*root) = s_root;
}

int read_root(execute ** root,lexem_list ** lex_head)
{
	lexem_list *p = (*lex_head);

	while( p->lexem.type != I_BLOCK_OPEN )
	{
		if(strcmp(p->lexem.name,"main") == 0)
		{
			p->lexem.type_data = I_VOID;
			(*root) = (execute*)malloc(sizeof(execute));
			(*root)->next = 0;
			(*root)->type = I_ROOT;
			lexem_list* l = (lexem_list*)malloc(sizeof(lexem_list));
			l->lexem = p->lexem;
			l->next = 0;
			(*root)->address = l;
			p = p->next;

			if(p->next->lexem.type != I_BRACKET_CLOSE)
				{
					lexem_list *s = l;
					while(p->lexem.type != I_BRACKET_CLOSE)
					{
						if(p->lexem.type == I_IDENTIFIC)
						{
							lexem_list * q = (lexem_list*)malloc(sizeof(lexem_list));
							q->lexem = p->lexem;
							if(strcmp("int",p->prew->lexem.name) == 0)
								q->lexem.type_data = I_INTEGER;
							if(strcmp("double",p->prew->lexem.name) == 0)
								q->lexem.type_data = I_DOUBLE;
							if(strcmp("char",p->prew->lexem.name) == 0)
								q->lexem.type_data = I_CHAR;
							q->next = 0;
							s->next = q;
							s = q;
						}
						p = p->next;
					}
					lexem_list *q = (lexem_list*)(*root)->address;
				}
		}
		else
		{
			if(strcmp("main",p->next->lexem.name) == 0)
			{
				if(strcmp("int",p->lexem.name) == 0)
					p->next->lexem.type_data = I_INTEGER;

				if(strcmp("double",p->lexem.name) == 0)
					p->next->lexem.type_data = I_DOUBLE;

				if(strcmp("char",p->lexem.name) == 0)
					p->next->lexem.type_data = I_CHAR;

				if(strcmp("void",p->lexem.name) == 0)
					p->next->lexem.type_data = I_VOID;
				p = p->next;
				
				(*root) = (execute*)malloc(sizeof(execute));
				(*root)->next = 0;
				(*root)->type = I_ROOT;
				lexem_list *l = (lexem_list*)malloc(sizeof(lexem_list));
				l->lexem = p->lexem;
				l->next = 0;
				p = p->next;
				(*root)->address = l;
				//
				if(p->next->lexem.type != I_BRACKET_CLOSE)
				{
					lexem_list *s = l;
					while(p->lexem.type != I_BRACKET_CLOSE)
					{
						if(p->lexem.type == I_IDENTIFIC)
						{
							lexem_list * q = (lexem_list*)malloc(sizeof(lexem_list));
							q->lexem = p->lexem;
							if(strcmp("int",p->prew->lexem.name) == 0)
								q->lexem.type_data = I_INTEGER;
							if(strcmp("double",p->prew->lexem.name) == 0)
								q->lexem.type_data = I_DOUBLE;
							if(strcmp("char",p->prew->lexem.name) == 0)
								q->lexem.type_data = I_CHAR;
							q->next = 0;
							s->next = q;
							s = q;
						}
						p = p->next;
					}
					//lexem_list *q = (lexem_list*)(*root)->address;
				}
				(*lex_head) = p;
				return TRUE;
			}
			else
				return FALSE;
		}
		p = p->next;
	}
	(*lex_head) = p;
	return TRUE;
}

lexem_list* read_expression(lexem_list** lex_head)
{
	lexem_list* p =(*lex_head);
	
	//item *root = (item*)malloc(sizeof(item));
	
	lexem_list *head = 0,*stack = (lexem_list*)malloc(sizeof(lexem_list));

	stack->next = 0;
	stack->prew = 0;

	//root->left = 0;
	//root->right = 0;

	while(p->lexem.type != I_SEMICOLON && !(p->lexem.type >= I_LOW && p->lexem.type <=I_AND) && p->lexem.type != I_COMMA)
	{
		if(p->lexem.type == I_IDENTIFIC)
			move_to_list(p->lexem,&head);
		if((p->lexem.type >= I_PERCENT && p->lexem.type <= I_DIVISION) || p->lexem.type == I_BRACKET_OPEN || p->lexem.type == I_BRACKET_CLOSE || p->lexem.type == I_INC_PLUS || p->lexem.type == I_INC_MINUS)
		{
			if(p->lexem.type == I_BRACKET_OPEN)
				push_expres(p->lexem,&stack);
			if(p->lexem.type == I_BRACKET_CLOSE)
			{
				while(stack && stack->lexem.type!= I_BRACKET_OPEN)
					move_to_list(pop_expres(&stack),&head);
				pop_expres(&stack);//delete '('
			}
			if(p->lexem.type ==I_PLUS || p->lexem.type == I_MINUS || p->lexem.type == I_DIVISION || p->lexem.type == I_MULTIPLYING || p->lexem.type == I_INC_PLUS || p->lexem.type == I_INC_MINUS || p->lexem.type == I_PERCENT)
			{
				if(getprior(p->lexem)<=getprior(stack->lexem))
				{
					move_to_list(pop_expres(&stack),&head);
					push_expres(p->lexem,&stack);
				}
				else
					push_expres(p->lexem,&stack);
			}
		}
		p = p->next;
	}
	
	for(lexem_list *s=stack;s->next!=0;s=s->next)
	{
		move_to_list(s->lexem,&head);
	}
	
	for(;head->prew!=0;head = head->prew);
	//for(s = head;s!=0;s = s->next)
	//	printf("%s",s->lexem.name);
	//printf("\n");
	(*lex_head) = p;
	return head;
}

void push_expres(Lexem lexem,lexem_list **stack)
{
	lexem_list *p = (lexem_list*)malloc(sizeof(lexem_list));
	p->lexem = lexem;
	p->next = (*stack);
	p->prew = 0;
	(*stack) = p;
}

Lexem pop_expres(lexem_list ** stack)
{
	Lexem lexem;
	lexem.type = 0;

	if(*stack == 0)
	{
		printf("fatal error executing!");
		return lexem;
	}
	lexem = (*stack)->lexem;
	lexem_list *p = (*stack);
	(*stack) = (*stack)->next;
	free(p);
	return lexem;
}

int getprior(Lexem lexem)
{
	if(strcmp(lexem.name,"+") == 0)
		return 1;
	if(strcmp(lexem.name,"-") == 0)
		return 1;
	if(strcmp(lexem.name,"*") == 0)
		return 2;
	if(strcmp(lexem.name,"/") == 0)
		return 2;
	if(strcmp(lexem.name,"%") == 0)
		return 2;
	if(strcmp(lexem.name,"(") == 0)
		return 0;
	if(strcmp(lexem.name,")") == 0)
		return 0;
	if(strcmp(lexem.name,"++") == 0)
		return 1;
	if(strcmp(lexem.name,"--") == 0)
		return 1;
	if(strcmp(lexem.name,">") == 0)
		return 2;
	if(strcmp(lexem.name,"<") == 0)
		return 2;
	if(strcmp(lexem.name,"==") == 0)
		return 2;
	if(strcmp(lexem.name,">=") == 0)
		return 2;
	if(strcmp(lexem.name,"<=") == 0)
		return 2;
	if(strcmp(lexem.name,"!=") == 0)
		return 2;
	if(strcmp(lexem.name,"||") == 0)
		return 3;
	if(strcmp(lexem.name,"&&") == 0)
		return 3;
	return -1;
}

Lexem count_expres(lexem_list **lex_head,varible_list *vl)
{
	lexem_list* p = (*lex_head);
	lexem_list* f = p;
	Lexem r;
	if(p->next !=0)
		while(p!=0 && p->lexem.type != I_SEMICOLON)
		{
			if(p->lexem.type >= I_PERCENT && p->lexem.type <= I_DIVISION)
			{
				lexem_list *f1 = p,*f2 = p->prew,*f3 = p->prew->prew;
				lexem_list *q = (lexem_list*)malloc(sizeof(lexem_list));
				Lexem m;
				if(!(f2->lexem.name[0] >='0' && f2->lexem.name[0] <='9') && f2->lexem.name[0] != 39)
					f2->lexem = *in_var_list(vl,f2->lexem);
				if(!(f3->lexem.name[0] >='0' && f3->lexem.name[0] <='9') && f3->lexem.name[0] != 39)
					f3->lexem = *in_var_list(vl,f3->lexem);
				m = count((*f3).lexem,(*f2).lexem,(*f1).lexem);
				q->next = p->next;
				if(p->next!=0)
					p->next->prew = q;
				q->prew = f3->prew;
				q->lexem = m;
				q->lexem.name[0] = '0';
				q->lexem.name[1] = 0;
				free(f1);
				free(f2);
				free(f3);
				p = q;
				if(p->next == 0)
					break;
			}
			if(p->lexem.type == I_INC_PLUS || p->lexem.type == I_INC_MINUS)
			{
				lexem_list *f1 = p,*f2 = p->prew,*f3 = p->prew->prew;
				lexem_list *q = (lexem_list*)malloc(sizeof(lexem_list));
				if(!(f2->lexem.name[0] >='0' && f2->lexem.name[0] <='9') && f2->lexem.name[0] != 39)
					f2->lexem = *in_var_list(vl,f2->lexem);
				switch(f2->lexem.type)
				{
				case(I_INTEGER):
					{
						q->lexem.Idata = f2->lexem.Idata+1;
						break;
					}
				case(I_DOUBLE):
					{
						q->lexem.Ddata = f2->lexem.Ddata+1;
						break;
					}
				case(I_CHAR):
					{
						q->lexem.Cdata = f2->lexem.Cdata+1;
						break;
					}
				}
			}
			p = p->next;
		}
	else
	{
		if(!(p->lexem.name[0] >='0' && p->lexem.name[0] <='9') && p->lexem.name[0] !=39)
			p->lexem = *in_var_list(vl,p->lexem);
	}
	r = p->lexem;
	(*lex_head) = p;
	return r;
}

void read_return(execute ** root,lexem_list ** lex_head)
{
	_return * ret = (_return*) malloc(sizeof(_return));
	
	lexem_list *p = (*lex_head);
	
	ret->lexem = p->lexem;
	
	p = p->next;
	
	ret->next = (lexem_list*)read_expression(&p);

	execute *r = (execute*)malloc(sizeof(execute));
	
	r->address = ret;
	
	r->next = 0;

	r->type = I_RETURN;
	
	(*root)->next = r;
	
	(*root) = r;
	
	(*lex_head) = p;
}

void read_declaration(execute ** root,lexem_list ** lex_head)
{
	declaration *dec = (declaration*)malloc(sizeof(declaration));

	lexem_list *p = (*lex_head);

	execute * e_dec = (execute*)malloc(sizeof(execute));

	dec->index.lexem = p->lexem;

	e_dec->type = I_DECLARATION;

	e_dec->address = (declaration*)dec;

	e_dec->next = 0;

	(*root)->next = e_dec;

	(*root) = e_dec;

	while(p->lexem.type != I_SEMICOLON)
	{
		if(p->lexem.type == I_IDENTIFIC)
		{
			if(p->next->lexem.type != I_COMMA && p->next->lexem.type != I_SEMICOLON)
			{
				declaration *q = (declaration*)malloc(sizeof(declaration));
				q->index.lexem = p->next->lexem;
				q->index.left = &p->lexem;
				p = p->next->next;
				q->index.right = read_expression(&p);
				q->next = 0;
				dec->next = q;
				dec = q;
				if(p->lexem.type == I_SEMICOLON)
					break;
			}
			else
			{
				declaration *q = (declaration*)malloc(sizeof(declaration));
				q->next = 0;
				q->index.lexem = p->lexem;
				dec->next = q;
				dec = q;
				if(p->lexem.type == I_SEMICOLON)
					break;
			}
		}
		p = p->next;
	}
	(*lex_head) = p;
}

void read_assignment(execute ** root,lexem_list ** lex_head)
{
	execute *r = (execute*)malloc(sizeof(execute));

	item * t = (item*)malloc(sizeof(item));
	
	t->lexem = (*lex_head)->next->lexem;

	t->left = &(*lex_head)->lexem;

	(*lex_head) = (*lex_head)->next->next;

	t->right = read_expression(lex_head);

	r->address = t;

	r->type = I_ASSIGNMENT;

	r->next = 0;

	(*root)->next = r;

	(*root) = r;
}

void read_function(execute ** root,lexem_list ** lex_head)
{
	lexem_list *p = (*lex_head);

	execute *r = (execute*)malloc(sizeof(execute));

	r->type = I_FUNCT_INLINE;

	(*root)->next = r;
	
	r->next = 0;

	for_inline_funct * f = (for_inline_funct*)malloc(sizeof(for_inline_funct));

	f->name = &(p->lexem);

	param* par = (param*)malloc(sizeof(param));

	par->next = 0;
	par->nParam = 0;

	f->param = par;

	param *w = par;

	p = p->next;

	(*root) = r;

	r->address = f;

	while(p->lexem.type!= I_SEMICOLON)
	{
		if(p->lexem.type == I_IDENTIFIC)
		{
			//if(p->next->lexem.type != I_BRACKET_CLOSE)
			lexem_list* s = prepare_to_read(p);
			s = read_expression(&s);
			while(p->lexem.type != I_COMMA && p->lexem.type != I_SEMICOLON)
				p = p->next;
			par->nParam = s;
			if(p->lexem.type == I_COMMA)
			{
				par->next = (param*)malloc(sizeof(param));
				par = par->next;
				par->next = 0;
				par->nParam = 0;
			}
			if(p->lexem.type == I_SEMICOLON)
				break;
		}
		if(p->lexem.type == I_STRING)
		{
			par->nParam = p;
			p = p->next;
			if(p->lexem.type == I_COMMA)
			{
				par->next = (param*)malloc(sizeof(param));
				par = par->next;
				par->next = 0;
				par->nParam = 0;
			}
		}
		p = p->next;
	}
	(*lex_head) = p;
}

void read_if(execute ** root,lexem_list ** lex_head)
{
	lexem_list *p = (*lex_head);

	execute *r = (execute*)malloc(sizeof(execute));

	_if * i = (_if*)malloc(sizeof(_if));

	r->type = I_IF;

	r->next = 0;

	(*root)->next = r;

	(*root) = r;

	r->address = i;

	p = p->next->next;

	lexem_list *b = 0;

	while(1)
	{
		if(p->lexem.type == I_BRACKET_CLOSE)
			if(p->next->lexem.type == I_IDENTIFIC || p->next->lexem.type == I_CONST_WORD || p->next->lexem.type == I_BLOCK_OPEN)
				break;
		if(b == 0)
		{
			b = (lexem_list*)malloc(sizeof(lexem_list));
			b->lexem = p->lexem;
			b->next = 0;
			b->prew = 0;
		}
		else
		{
			lexem_list* q = (lexem_list*)malloc(sizeof(lexem_list));
			q->lexem = p->lexem;
			b->next = q;
			q->prew = b;
			q->next = 0;
			b = q;
		}
		p = p->next;
	}
	for(;b->prew!=0;b = b->prew);
	i->boolean = update_bool_param(b);
	//i->boolean = b;
/*
	while(p->lexem.type != I_BRACKET_CLOSE)
	{
		if(p->lexem.type == I_IDENTIFIC || p->lexem.type == I_BRACKET_OPEN)
		{
			if(p->next->lexem.type != I_BRACKET_CLOSE)
			{
				lex->next = read_expression(&p);
				while(lex->next!=0)
					lex = lex->next;
			}
			else
			{
				lexem_list* q = (lexem_list*)malloc(sizeof(lexem_list));
				lex->next = q;
				q->next = 0;
				q->lexem = p->lexem;
				lex = p;
			}
		}
		if(p->lexem.type >= I_LOW && p->lexem.type <= I_AND)
		{
			lexem_list* q = (lexem_list*)malloc(sizeof(lexem_list));
			lex->next = q;
			q->next = 0;
			q->lexem = p->lexem;
			lex = q;
		}
		p = p->next;
	}*/
	//lexem_list* f = i->boolean;
//	i->boolean = i->boolean->next;
//	free(f);
	p = p->next;
	if(p->lexem.type == I_BLOCK_OPEN)
	{
		i->body_type = BLOCK;
		i->True = read_block(&p);
		if(strcmp(p->next->lexem.name,"else") == 0)
			p = p->next;
	}
	else
	{
		int type = 0;
		i->True = line(&p,&type);
		i->body_type = type;
	}
	if(strcmp("else",p->next->lexem.name) == 0)
	{
		p = p->next->next;
		if(p->lexem.type == I_BLOCK_OPEN)
		{
			i->else_type = BLOCK;
			i->False = read_block(&p);
		}
		else
		{
			int type = 0;
			i->False = line(&p,&type);
			i->else_type = type;
		}
	}
	else
		i->else_type = 0;
	(*lex_head) = p;
}

void read_while(execute ** root,lexem_list ** lex_head)
{
	lexem_list *p = (*lex_head);

	execute *r = (execute*)malloc(sizeof(execute));

	_while * w = (_while*)malloc(sizeof(_while));

	r->type = I_WHILE;

	r->next = 0;

	(*root)->next = r;

	(*root) = r;

	r->address = w;

	p = p->next->next;

	lexem_list *b = 0;

	while(1)
	{
		if(p->lexem.type == I_BRACKET_CLOSE)
			if(p->next->lexem.type == I_IDENTIFIC || p->next->lexem.type == I_CONST_WORD || p->next->lexem.type == I_BLOCK_OPEN)
				break;
		if(b == 0)
		{
			b = (lexem_list*)malloc(sizeof(lexem_list));
			b->lexem = p->lexem;
			b->next = 0;
			b->prew = 0;
		}
		else
		{
			lexem_list* q = (lexem_list*)malloc(sizeof(lexem_list));
			q->lexem = p->lexem;
			b->next = q;
			q->prew = b;
			q->next = 0;
			b = q;
		}
		p = p->next;
	}
	for(;b->prew!=0;b = b->prew);
	w->boolean = update_bool_param(b);
	p = p->next;
	if(p->lexem.type == I_BLOCK_OPEN)
	{
		w->body_type = BLOCK;
		w->body = read_block(&p);
	}
	else
	{
		int type = 0;
		w->body = line(&p,&type);
		w->body_type = type;
	}
	(*lex_head) = p;
}

execute* read_block(lexem_list ** lex_head)
{
	lexem_list * p = (*lex_head);

	execute *root = (execute*)malloc(sizeof(execute));

	root->next = 0;
	root->type = 0;
	root->address = 0;

	execute *s_root = root,*free_ = root;
	
	while(p->lexem.type != I_BLOCK_CLOSE)
	{
		switch(p->lexem.type)
		{
			case(I_IDENTIFIC):
				{
					if(p->next->lexem.type == I_ASSIGNMENT)
					{
						read_assignment(&root,&p);
						break;
					}
					if(p->next->lexem.type == I_BRACKET_OPEN)
					{
						read_function(&root,&p);
						break;
					}
					if(p->next->lexem.type == I_INC_PLUS || p->next->lexem.type == I_INC_MINUS)
					{
					}
					break;
				}
			case(I_CONST_WORD):
				{
					if(strcmp("int",p->lexem.name) == 0 || strcmp("double",p->lexem.name) == 0 || strcmp("char",p->lexem.name) == 0)
					{
						read_declaration(&root,&p);
						break;
					}
					if(strcmp("if",p->lexem.name) == 0)
					{
						read_if(&root,&p);
						break;
					}
					if(strcmp("while",p->lexem.name) == 0)
					{
						read_while(&root,&p);
						break;
					}
					if(strcmp("return",p->lexem.name) == 0)
					{
						read_return(&root,&p);
						break;
					}
				}
			case(I_INC_PLUS):
				{
					break;
				}
			case(I_INC_MINUS):
				{
					break;
				}
		}
		p = p->next;
	}
	(*lex_head) = p;
	s_root = s_root->next;
	free(free_);
	return s_root;
}

execute * line(lexem_list **lex_head,int *type)
{
	execute *root = (execute *)malloc(sizeof(execute));
	lexem_list *p = (*lex_head);
	switch(p->lexem.type)
	{
	case(I_IDENTIFIC):
		{
			if(p->next->lexem.type == I_ASSIGNMENT)
			{
				read_assignment(&root,&p);
				*type = I_ASSIGNMENT;
				break;
			}
			if(p->next->lexem.type == I_BRACKET_OPEN)
			{
				read_function(&root,&p);
				*type = I_FUNCT_INLINE;
				break;
			}
			if(p->next->lexem.type == I_INC_PLUS || p->next->lexem.type == I_INC_MINUS)
			{
				root->address = read_expression(&p);
				*type = I_EXPRESSION;
				break;
			}
			printf("execute line");
			break;
		}
	case(I_CONST_WORD):
		{
			if(strcmp("return",p->lexem.name) == 0)
			{
				read_return(&root,&p);
				*type = I_RETURN;
				break;
			}
			if(strcmp("while",p->lexem.name) == 0)
			{
				read_while(&root,&p);
				*type = I_WHILE;
				break;
			}
			if(strcmp("if",p->lexem.name) == 0)
			{
				read_if(&root,&p);
				*type = I_IF;
				break;
			}
			printf("execute line");
		}
	case(I_INC_PLUS):
		{
			root->address = read_expression(&p);
			*type = I_EXPRESSION;
			break;
		}
	case(I_INC_MINUS):
		{
			root->address = read_expression(&p);
			*type = I_EXPRESSION;
			break;
		}
	default:
		{
			printf("execute line");
		}
	}
	(*lex_head) = p;
	return root;
}

int do_execute(execute *root,errors_list **er_head,errors_list **war_head,_lists **list)
{
	execute *r = root;
	while(r!=0)
	{
		switch(r->type)
		{
		case(I_ROOT):
			{
				if(root->address != 0)
				{
					lexem_list *p = (lexem_list*)root->address;
					p = p->next;
					while(p!=0)
					{
						add_to_var_list(&(*list)->vList,p->lexem,0);
						p = p->next;
					}
					break;
				}
				break;
			}
		case(I_FUNCT_INLINE):
			{
				for_inline_funct* f = (for_inline_funct*)r->address;
				Lexem* l = (Lexem*)f->name;
				param *par = (param*)f->param;
				if(strcmp("printf",l->name) == 0)
				{
					while(par!=0)
					{
						if(par->nParam->lexem.type == I_IDENTIFIC)
						{
							lexem_list* p = (lexem_list*)par->nParam;
							while(p!=0)
							{
								Lexem *q = in_var_list((*list)->vList,p->lexem);
								if(!q  && p->lexem.name[0] !='\'')
								{
									move_to_err_list(I_UNKNOWBLE_ID,p->lexem.line_pos,er_head);
									return FALSE;
								}
								if(p->lexem.name[0] !='\'')
									count_expres(&p,(*list)->vList);
								switch(p->lexem.type_data)
								{
								case(I_INTEGER):
									{
										cout<<p->lexem.Idata;
										break;
									}
								case(I_DOUBLE):
									{
										cout<<p->lexem.Ddata;
										break;
									}
								case(I_CHAR):
									{
										cout<<p->lexem.Cdata;
										break;
									}
								}
								p = p->next;
							}
						}
						else
						{
							char *h = update_string(par->nParam->lexem.name);
							cout<<h;
							free(h);
						}
						par = par->next;
					}
					break;
				}
				if(strcmp("scanf",l->name) == 0)
				{
					while(par!=0)
						{
							Lexem *p = in_var_list((*list)->vList,par->nParam->lexem);
							if(p == 0)
							{
								move_to_err_list(I_DESTORY,par->nParam->lexem.line_pos,er_head);
								return FALSE;
							}
							switch(p->type_data)
							{
							case(I_INTEGER):
								{
									cin>>p->Idata;
									break;
								}
							case(I_DOUBLE):
								{
									cin>>p->Ddata;
									break;
								}
							case(I_CHAR):
								{
									cin>>p->Cdata;
									break;
								}
							}
							par = par->next;
						}
				}
				break;
			}
		case(I_DECLARATION):
			{
				declaration *d = (declaration*)r->address;
				Lexem p = d->index.lexem;
				d = d->next;
				int tl = 0;
				if(strcmp("int",p.name) == 0)
					tl = I_INTEGER;
				if(strcmp("double",p.name) == 0)
					tl = I_DOUBLE;
				if(strcmp("char",p.name) == 0)
					tl = I_CHAR;
				
				while(d!=0)
				{
					if(d->index.lexem.type == I_ASSIGNMENT)
					{
						add_to_var_list(&(*list)->vList,*(Lexem*)d->index.left,tl);
						Lexem* q = in_var_list((*list)->vList,*(Lexem*)d->index.left);
						lexem_list *m = (lexem_list*)(d->index.right);
						assignment(q,count_expres(&m,(*list)->vList));
					}
					else
					{
						add_to_var_list(&(*list)->vList,d->index.lexem,tl);
					}
					d = d->next;
				}
				break;
			}
		case(I_ASSIGNMENT):
			{
				item * i = (item*)r->address;
				Lexem* left = (Lexem*)i->left;
				lexem_list* right = (lexem_list*)i->right;
				lexem_list* r2 = 0;
				while(right!=0)
				{
					if(r2 ==0)
					{
						r2 = (lexem_list*)malloc(sizeof(lexem_list));
						r2->lexem = right->lexem;
						r2->next = 0;
						r2->prew = 0;
					}
					else
					{
						lexem_list* q = (lexem_list*)malloc(sizeof(lexem_list));
						q->lexem = right->lexem;
						r2->next = q;
						q->prew = r2;
						q->next = 0;
						r2 = q;
					}
					right = right->next;
				}
				for(;r2->prew!=0;r2 = r2->prew);
				assignment(in_var_list((*list)->vList,*left),count_expres(&r2,(*list)->vList));
				free(r2);
				break;
			}
		case(I_EXPRESSION):
			{
				//printf("expression\n");
				break;
			}
		case(I_WHILE):
			{
				_while* w = (_while*)r->address;
				while(check_bool_express((lexem_list*)w->boolean,(*list)->vList))
				{
					do_execute((execute*)w->body,er_head,war_head,list);
				}
				break;
			}
		case(I_IF):
			{
				_if *f = (_if*)r->address;
				if(check_bool_express((lexem_list*)f->boolean,(*list)->vList))
				{
					do_execute((execute*)f->True,er_head,war_head,list);
				}
				else
				{
					do_execute((execute*)f->False,er_head,war_head,list);
				}
				break;
			}
		case(I_RETURN):
			{
				_return * t = (_return*)r->address;
				lexem_list* l = (lexem_list*)t->next;
				Lexem m = count_expres(&l,(*list)->vList);
				cout<<"programm returned: ";
				switch(m.type_data)
				{
				case(I_INTEGER):
					{
						cout<<m.Idata;
						break;
					}
				case(I_DOUBLE):
					{
						cout<<m.Ddata;
						break;
					}
				case(I_CHAR):
					{
						cout<<m.Cdata;
						break;
					}
				default:
					{
						cout<<"minack osel:))))))";
						break;
					}
				}
				return TRUE;
			}
		default:
			printf("unknowble error\n");
				break;
		}
		r = r->next;
	}
	return TRUE;
}

bool add_to_var_list(varible_list** vl,Lexem lexem,int type)
{
	if(*vl == 0)
	{
		(*vl) = (varible_list*) malloc(sizeof(varible_list));
		(*vl)->lexem = lexem;
		if(type != 0)
			(*vl)->lexem.type_data = type;
		(*vl)->next = 0;
		(*vl)->prew = 0;
	}
	else
	{
		varible_list* q = (varible_list*)malloc(sizeof(varible_list));
		q->lexem = lexem;
		q->next = (*vl);
		(*vl)->prew = q;
		(*vl) = q;
		if(type != 0)
			(*vl)->lexem.type_data = type;
	}
	return TRUE;
}

bool add_to_funct_list(funct_list** fl,Lexem *lex_head,int nParam)
{
	return TRUE;
}

Lexem* in_var_list(varible_list* vl,Lexem lexem)
{
	if(vl != 0)
	{
		varible_list * p= vl;
		Lexem *q;
		while(p!=0)
		{
			if(strcmp(p->lexem.name,lexem.name) == 0)
			{
				q = &(p->lexem);
				return q;
			}
			p = p->next;
		}
	}
	return 0;
}

bool in_funct_list(funct_list* fl,Lexem lexem)
{
	return FALSE;
}

bool remove_from_var_list(varible_list** vl,Lexem lexem)
{
	return TRUE;
}

bool remove_from_funct_list(funct_list** fl)
{
	return TRUE;
}


void last_checkout(execute *root,errors_list **er_head,errors_list **war_head,_lists **list)
{
	execute *r = root;
	int return_type = 0;
	bool Return = FALSE;
	while(r!=0)
	{
		switch(r->type)
		{
		case(I_ROOT):
			{
				if(root->address != 0)
				{
					lexem_list *p = (lexem_list*)root->address;
					return_type = p->lexem.type_data;
					p = p->next;
					while(p!=0)
					{
						if(!in_var_list((*list)->vList,p->lexem))
							add_to_var_list(&(*list)->vList,p->lexem,0);
						else
						{
							move_to_err_list(I_REDEFINITION,p->lexem.line_pos,er_head);
							return;
						}
						p = p->next;
					}
					break;
				}
				//printf("\nroot\n");
				break;
			}
		case(I_FUNCT_INLINE):
			{
				for_inline_funct* f = (for_inline_funct*)r->address;
				Lexem* l = (Lexem*)f->name;
				param *par = (param*)f->param;
				if(strcmp("scanf",l->name) == 0)
				{
					while(par!=0)
					{
						if(par->nParam->lexem.type == I_STRING)
							move_to_err_list(I_ERR_IN_F_PARAM,par->nParam->lexem.line_pos,er_head);
						if(par->nParam->lexem.type == I_IDENTIFIC)
						{
							lexem_list* a = par->nParam;
							while(a!=0)
							{
								if(!in_var_list((*list)->vList,a->lexem) && !(a->lexem.type >= I_PERCENT && a->lexem.type <= I_INC_PLUS) && a->lexem.type != I_SEMICOLON)
									move_to_err_list(I_UNKNOWBLE_ID,a->lexem.line_pos,er_head);
								a = a->next;
							}
						}
						par = par->next;
					}
				}
				if(strcmp("printf",l->name) == 0)
				{
					while(par!=0)
					{
						if(par->nParam->lexem.type == I_IDENTIFIC)
						{
							lexem_list* a = par->nParam;
							while(a!=0)
							{
								if(!in_var_list((*list)->vList,a->lexem) && !(a->lexem.type >= I_PERCENT && a->lexem.type <= I_INC_PLUS) && a->lexem.type != I_SEMICOLON && a->lexem.name[0] !='\'')
									move_to_err_list(I_UNKNOWBLE_ID,a->lexem.line_pos,er_head);
								a = a->next;
							}
						}
						par = par->next;
					}
				}
				//printf("%s %s",l->name,"function\n");
				break;
			}
		case(I_DECLARATION):
			{
				declaration *d = (declaration*)r->address;
				Lexem p = d->index.lexem;
				d = d->next;
				int tl = 0;
				if(strcmp("int",p.name) == 0)
					tl = I_INTEGER;
				if(strcmp("double",p.name) == 0)
					tl = I_DOUBLE;
				if(strcmp("char",p.name) == 0)
					tl = I_CHAR;
				while(d!=0)
				{
					if(d->index.lexem.type == I_ASSIGNMENT)
					{
						int t = type_expression((lexem_list*)d->index.right);
						if(!check_expression((lexem_list*)d->index.right,(*list)->vList,er_head))
						{
							move_to_err_list(I_UNKNOWBLE_ID,d->index.lexem.line_pos,er_head);
							return;
						}
						else
						{
							if(!in_var_list((*list)->vList,d->index.lexem))
								add_to_var_list(&(*list)->vList,*(Lexem*)d->index.left,tl);
							else
							{
								move_to_err_list(I_REDEFINITION,d->index.lexem.line_pos,er_head);
								return;
							}
						}
						if(tl != t)
							move_to_err_list(I_W_IDENTIFICATION,d->index.lexem.line_pos,war_head);
					}
					else
					{
						if(!in_var_list((*list)->vList,d->index.lexem))
							add_to_var_list(&(*list)->vList,d->index.lexem,tl);
						else
						{
							move_to_err_list(I_REDEFINITION,d->index.lexem.line_pos,er_head);
							return;
						}
						move_to_err_list(I_NO_INDEFINED,d->index.lexem.line_pos,war_head);
					}
					d = d->next;
				}
				break;
			}
		case(I_ASSIGNMENT):
			{
				item * i = (item*)r->address;
				Lexem* l = (Lexem*)i->left;
				lexem_list* q = (lexem_list*)i->right;
				int type = l->type_data;
				
				if(!in_var_list((*list)->vList,*l))
				{
					move_to_err_list(I_UNKNOWBLE_ID,q->lexem.line_pos,er_head);
					return;
				}
				while(q!=0)
				{
					if(!in_var_list((*list)->vList,q->lexem) && !(q->lexem.type >= I_PERCENT && q->lexem.type <= I_INC_MINUS) && !(q->lexem.name[0] >= '0' && q->lexem.name[0]<='9'))
					{
						move_to_err_list(I_UNKNOWBLE_ID,q->lexem.line_pos,er_head);
					}
					q = q->next;
				}
				q = (lexem_list*)i->right;
				if(type != type_expression(q))
					move_to_err_list(I_W_IDENTIFICATION,q->lexem.line_pos,war_head);
				break;
			}
		case(I_EXPRESSION):
			{
				lexem_list* p = (lexem_list*)r->address;
				printf("expression\n");
				break;
			}
		case(I_WHILE):
			{
				_while * w = (_while*)r->address;
				lexem_list* p = w->boolean;
				while(p!=0)
				{
					if(!(p->lexem.name[0] >= '0' && p->lexem.name[0]<='9') && !(p->lexem.type >= I_LOW && p->lexem.type <= I_AND) && !(p->lexem.type >= I_PERCENT && p->lexem.type <= I_INC_MINUS))
						if(!in_var_list((*list)->vList,p->lexem))
						{
							move_to_err_list(I_UNKNOWBLE_ID,p->lexem.line_pos,er_head);
						}
					p = p->next;
				}
				last_block_checkout((execute*)w->body,er_head,war_head,list,return_type);
				//printf("while\n");
				break;
			}
		case(I_IF):
			{
				_if * i = (_if*)r->address;
				lexem_list* p = i->boolean;
				while(p!=0)
				{
					if(!(p->lexem.name[0] >= '0' && p->lexem.name[0]<='9') && !(p->lexem.type >= I_LOW && p->lexem.type <= I_AND) && !(p->lexem.type >= I_PERCENT && p->lexem.type <= I_INC_MINUS))
						if(!in_var_list((*list)->vList,p->lexem))
						{
							move_to_err_list(I_UNKNOWBLE_ID,p->lexem.line_pos,er_head);
						}
					p = p->next;
				}
				last_block_checkout((execute*)i->True,er_head,war_head,list,return_type);
				if(i->False=0)
					last_block_checkout((execute*)i->False,er_head,war_head,list,return_type);
				//printf("if\n");
				break;
			}
		case(I_RETURN):
			{
				_return * ret = (_return*)(r->address);
				lexem_list *q = (lexem_list*)ret->next;
				lexem_list *q1 = q;
				if(!Return)
				{	
					if(return_type != I_VOID)
					{
						while(q!=0)
						{
							if(!in_var_list((*list)->vList,q->lexem) && !(q->lexem.type >= I_PERCENT && q->lexem.type <= I_INC_MINUS) && !(q->lexem.name[0] >= '0' && q->lexem.name[0] <= '9') && q->lexem.name[0] != 39)
							{
								move_to_err_list(I_UNKNOWBLE_ID,q->lexem.line_pos,er_head);
								return;
							}
							q = q->next;
						}
						if(return_type != type_expression(q1))
							move_to_err_list(I_W_RETURN_DATA,q1->lexem.line_pos,war_head);
						Return = TRUE;
						//printf("return\n");
					}
					else
						move_to_err_list(I_ERR_VOID_FUNCT,q->lexem.line_pos,er_head);
				}
				else
				{
					if(return_type == I_VOID)
						move_to_err_list(I_ERR_VOID_FUNCT,q->lexem.line_pos,er_head);
					move_to_err_list(I_W_ONE_RETURN,q->lexem.line_pos,war_head);
				}
				break;
			}
		default:
			printf("unknowble error in last checkout\n");
				return;
		}
		r = r->next;
	}
	return;
}


int type_expression(lexem_list *lex_head)
{
	if(lex_head == 0)
		return 0;
	int type = lex_head->lexem.type_data;
	while(lex_head!=0)
	{
		switch(lex_head->lexem.type_data)
		{
		case(I_INTEGER):
			if(type != I_INTEGER)
				return 0;
			break;
		case(I_CHAR):
			if(type != I_CHAR)
				return 0;
			break;
		case(I_DOUBLE):
			if(type != I_DOUBLE)
				return 0;
			break;
		}
		lex_head = lex_head->next;
	}
	return type;
}

bool check_expression(lexem_list * p,varible_list* l,errors_list** er_head)
{
	while(p!=0)
	{
		if(p->lexem.type == I_IDENTIFIC && !(p->lexem.name[0]>='0' && p->lexem.name[0]<='9') && p->lexem.name[0] != 39)
			if(!in_var_list(l,p->lexem))
			{
				move_to_err_list(I_UNKNOWBLE_ID,p->lexem.line_pos,er_head);
				return FALSE;
			}
		p = p->next;
	}
	return TRUE;
}

void assignment(Lexem *lex1,Lexem lex2)
{
	switch(lex1->type_data)
	{
	case(I_INTEGER):
		{
			switch(lex2.type_data)
			{
				case(I_INTEGER):
					{
						lex1->Idata = lex2.Idata;
						break;
					}
				case(I_DOUBLE):
					{
						lex1->Idata = (int)lex2.Ddata;
						break;
					}
				case(I_CHAR):
					{
						lex1->Idata = (int)lex2.Cdata;
						break;
					}
			}
			break;
		}
	case(I_DOUBLE):
		{
			switch(lex2.type_data)
			{
				case(I_INTEGER):
					{
						lex1->Ddata = (double)lex2.Idata;
						break;
					}
				case(I_DOUBLE):
					{
						lex1->Ddata = lex2.Ddata;
						break;
					}
				case(I_CHAR):
					{
						lex1->Ddata = (double)lex2.Cdata;
						break;
					}
			}
			break;
		}
	case(I_CHAR):
		{
			switch(lex2.type_data)
			{
				case(I_INTEGER):
					{
						lex1->Cdata = (char)lex2.Idata;
						break;
					}
				case(I_DOUBLE):
					{
						lex1->Cdata = (char)lex2.Cdata;
						break;
					}
				case(I_CHAR):
					{
						lex1->Cdata = lex2.Cdata;
						break;
					}
			}
			break;
		}
	default:
		printf("error assignment");
	}
}

Lexem count(Lexem operand1,Lexem operand2,Lexem _operator)//��� ��������� ������������ ������ ��������
{
	Lexem l;
	switch(_operator.type)
	{
	case(I_PLUS):
		{
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata + operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata + (int)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata + (int)operand2.Cdata;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Ddata + (double)operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Idata + operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Ddata + (double)operand2.Cdata;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata + (char)operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata + (char)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata + operand2.Cdata;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_MINUS):
		{
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata - operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata - (int)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata - (int)operand2.Cdata;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Ddata - (double)operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Idata - operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Ddata - (double)operand2.Cdata;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata - (char)operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata - (char)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata - operand2.Cdata;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_DIVISION):
		{
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata / operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata / (int)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata / (int)operand2.Cdata;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Ddata / (double)operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Idata / operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Ddata / (double)operand2.Cdata;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata / (char)operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata / (char)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata / operand2.Cdata;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_PERCENT):
		{
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata % operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata % (int)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata % (int)operand2.Cdata;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = double(int(operand1.Ddata) % operand2.Idata);
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = double(int(operand1.Ddata) % (int)operand2.Ddata);
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = double(int(operand1.Ddata) % (int)operand2.Cdata);
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata % (char)operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata % (char)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata % operand2.Cdata;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_MULTIPLYING):
		{
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata * operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata * (int)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_INTEGER;
							l.Idata = operand1.Idata * (int)operand2.Cdata;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Ddata * (double)operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Idata * operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_DOUBLE;
							l.Ddata = operand1.Ddata * (double)operand2.Cdata;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata * (char)operand2.Idata;
							break;
						}
					case(I_DOUBLE):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata * (char)operand2.Ddata;
							break;
						}
					case(I_CHAR):
						{
							l.type_data = I_CHAR;
							l.Cdata = operand1.Cdata * operand2.Cdata;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_LOW):
		{
			l.type_data = I_BOOL;
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Idata < operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Idata < operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Idata < operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Ddata < operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Ddata < operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Ddata < operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Cdata < operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Cdata < operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Cdata < operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_BIGGER):
		{
			l.type_data = I_BOOL;
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Idata > operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Idata > operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Idata > operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Ddata > operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Ddata > operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Ddata > operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Cdata > operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Cdata > operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Cdata > operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_NOT_LOWER):
		{
			l.type_data = I_BOOL;
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Idata >= operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Idata >= operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Idata >= operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Ddata >= operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Ddata >= operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Ddata >= operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Cdata >= operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Cdata >= operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Cdata >= operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_NOT_BIGGER):
		{
			l.type_data = I_BOOL;
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Idata <= operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Idata <= operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Idata <= operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Ddata <= operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Ddata <= operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Ddata <= operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Cdata <= operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Cdata <= operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Cdata <= operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_EQUAL):
		{
			l.type_data = I_BOOL;
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Idata == operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Idata == operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Idata == operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Ddata == operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Ddata == operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Ddata == operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Cdata == operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Cdata == operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Cdata == operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_NOT_EQUAL):
		{
			l.type_data = I_BOOL;
			switch(operand1.type_data)
			{
			case(I_INTEGER):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Idata != operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Idata != operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Idata != operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_DOUBLE):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Ddata != operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Ddata != operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Ddata != operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			case(I_CHAR):
				{
					switch(operand2.type_data)
					{
					case(I_INTEGER):
						{
							if(operand1.Cdata != operand2.Idata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_DOUBLE):
						{
							if(operand1.Cdata != operand2.Ddata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					case(I_CHAR):
						{
							if(operand1.Cdata != operand2.Cdata)
								l.Idata = TRUE;
							else
								l.Idata = FALSE;
							break;
						}
					}
					break;
				}
			}
			break;
		}
	case(I_AND):
		{
			l.type_data = I_BOOL;
			if(operand1.Idata && operand2.Idata)
				l.Idata = TRUE;
			else
				l.Idata = FALSE;
		}
	case(I_OR):
		{
			l.type_data = I_BOOL;
			if(operand1.Idata || operand2.Idata)
				l.Idata = TRUE;
			else
				l.Idata = FALSE;
		}
	}
	return l;
}

void last_block_checkout(execute *root,errors_list **er_head,errors_list **war_head,_lists **list,int return_type)
{
	bool Return = FALSE;
	execute *r = root;
	while(r!=0)
	{
		switch(r->type)
		{
		case(I_FUNCT_INLINE):
			{
				for_inline_funct* f = (for_inline_funct*)r->address;
				Lexem* l = (Lexem*)f->name;
				param *par = (param*)f->param;
				if(strcmp("scanf",l->name) == 0)
				{
					while(par!=0)
					{
						if(par->nParam->lexem.type == I_STRING)
							move_to_err_list(I_ERR_IN_F_PARAM,par->nParam->lexem.line_pos,er_head);
						if(par->nParam->lexem.type == I_IDENTIFIC)
						{
							lexem_list* a = par->nParam;
							while(a!=0)
							{
								if(!in_var_list((*list)->vList,a->lexem) && !(a->lexem.type >= I_PERCENT && a->lexem.type <= I_INC_PLUS) && a->lexem.type != I_SEMICOLON)
									move_to_err_list(I_UNKNOWBLE_ID,a->lexem.line_pos,er_head);
								a = a->next;
							}
						}
						par = par->next;
					}
				}
				if(strcmp("printf",l->name) == 0)
				{
					while(par!=0)
					{
						if(par->nParam->lexem.type == I_IDENTIFIC)
						{
							lexem_list* a = par->nParam;
							while(a!=0)
							{
								if(!in_var_list((*list)->vList,a->lexem) && !(a->lexem.type >= I_PERCENT && a->lexem.type <= I_INC_PLUS) && a->lexem.type != I_SEMICOLON)
									move_to_err_list(I_UNKNOWBLE_ID,a->lexem.line_pos,er_head);
								a = a->next;
							}
						}
						par = par->next;
					}
				}
				//printf("%s %s",l->name,"function in block\n");
				break;
			}
		case(I_DECLARATION):
			{
				declaration *d = (declaration*)r->address;
				Lexem p = d->index.lexem;
				d = d->next;
				int tl = 0;
				if(strcmp("int",p.name) == 0)
					tl = I_INTEGER;
				if(strcmp("double",p.name) == 0)
					tl = I_DOUBLE;
				if(strcmp("char",p.name) == 0)
					tl = I_CHAR;
				while(d!=0)
				{
					if(d->index.lexem.type == I_ASSIGNMENT)
					{
						int t = type_expression((lexem_list*)d->index.right);
						if(!check_expression((lexem_list*)d->index.right,(*list)->vList,er_head))
						{
							move_to_err_list(I_UNKNOWBLE_ID,d->index.lexem.line_pos,er_head);
							return;
						}
						else
						{
							if(!in_var_list((*list)->vList,d->index.lexem))
								add_to_var_list(&(*list)->vList,*(Lexem*)d->index.left,tl);
							else
							{
								move_to_err_list(I_REDEFINITION,d->index.lexem.line_pos,er_head);
								return;
							}
						}
						if(tl != t)
							move_to_err_list(I_W_IDENTIFICATION,d->index.lexem.line_pos,war_head);
					}
					else
					{
						if(!in_var_list((*list)->vList,d->index.lexem))
							add_to_var_list(&(*list)->vList,d->index.lexem,tl);
						else
						{
							move_to_err_list(I_REDEFINITION,d->index.lexem.line_pos,er_head);
							return;
						}
						move_to_err_list(I_NO_INDEFINED,d->index.lexem.line_pos,war_head);
					}
					d = d->next;
				}
				break;
			}
		case(I_ASSIGNMENT):
			{
				item * i = (item*)r->address;
				Lexem* l = (Lexem*)i->left;
				lexem_list* q = (lexem_list*)i->right;
				
				if(!in_var_list((*list)->vList,*l))
				{
					move_to_err_list(I_UNKNOWBLE_ID,q->lexem.line_pos,er_head);
					return;
				}
				Lexem *t = in_var_list((*list)->vList,*l);
				int type = t->type_data;
				while(q!=0)
				{
					if(!in_var_list((*list)->vList,q->lexem) && !(q->lexem.type >= I_PERCENT && q->lexem.type <= I_INC_MINUS) && !(q->lexem.name[0] >='0' && q->lexem.name[0] <= '9') && q->lexem.name[0] != 39)
					{
						move_to_err_list(I_UNKNOWBLE_ID,q->lexem.line_pos,er_head);
					}
					q = q->next;
				}
				q = (lexem_list*)i->right;
				if(type != type_expression(q))
					move_to_err_list(I_W_IDENTIFICATION,q->lexem.line_pos,war_head);
				break;
			}
		case(I_EXPRESSION):
			{
				lexem_list* p = (lexem_list*)r->address;
				//printf("expression\n");
				break;
			}
		case(I_WHILE):
			{
				_while * w = (_while*)r->address;
				lexem_list* p = (lexem_list*)w->boolean;
				while(p!=0)
				{
					if(!(p->lexem.name[0] >= '0' && p->lexem.name[0]<='9') && !(p->lexem.type >= I_LOW && p->lexem.type <= I_AND) && !(p->lexem.type >= I_PERCENT && p->lexem.type <= I_INC_MINUS))
						if(!in_var_list((*list)->vList,p->lexem))
						{
							move_to_err_list(I_UNKNOWBLE_ID,p->lexem.line_pos,er_head);
						}
					p = p->next;
				}
				last_block_checkout((execute*)w->body,er_head,war_head,list,return_type);
				//printf("while\n");
				break;
			}
		case(I_IF):
			{
				_if * i = (_if*)r->address;
				lexem_list* p = (lexem_list*)i->boolean;
				while(p!=0)
				{
					if(!(p->lexem.name[0] >= '0' && p->lexem.name[0]<='9') && !(p->lexem.type >= I_LOW && p->lexem.type <= I_AND) && !(p->lexem.type >= I_PERCENT && p->lexem.type <= I_INC_MINUS))
						if(!in_var_list((*list)->vList,p->lexem))
						{
							move_to_err_list(I_UNKNOWBLE_ID,p->lexem.line_pos,er_head);
						}
					p = p->next;
				}
				last_block_checkout((execute*)i->True,er_head,war_head,list,return_type);
				if(i->False=0)
					last_block_checkout((execute*)i->False,er_head,war_head,list,return_type);
				//printf("\tif in block\n");
				break;
			}
		case(I_RETURN):
			{
				_return * ret = (_return*)(r->address);
				lexem_list *q = (lexem_list*)ret->next;
				lexem_list *q1 = q;
				if(!Return)
				{	
					while(q!=0)
					{
						if(!in_var_list((*list)->vList,q->lexem) && !(q->lexem.type >= I_PERCENT && q->lexem.type <= I_INC_MINUS) && !(q->lexem.name[0] >= '0' && q->lexem.name[0] <= '9') && q->lexem.name[0] != 39)
						{
							move_to_err_list(I_UNKNOWBLE_ID,q->lexem.line_pos,er_head);
							return;
						}
						q = q->next;
					}
					if(return_type != type_expression(q1))
						move_to_err_list(I_W_RETURN_DATA,q->lexem.line_pos,war_head);
					Return = TRUE;
					printf("\treturn\n");
				}
				else
				{
					move_to_err_list(I_W_ONE_RETURN,q->lexem.line_pos,war_head);
				}
				break;
			}
		default:
			printf("unknowble error in last checkout\n");
				return;
		}
		r = r->next;
	}
}

lexem_list* prepare_to_read(lexem_list *p)
{
	lexem_list* s = 0;
	while(p->next->lexem.type != I_SEMICOLON && p->lexem.type != I_COMMA)
	{
		if(s == 0)
		{
			s = (lexem_list*)malloc(sizeof(lexem_list));
			s->lexem = p->lexem;
			s->prew = 0;
			s->next = 0;
		}
		else
		{
			lexem_list* q = (lexem_list*)malloc(sizeof(lexem_list));
			q->prew = s;
			s->next = q;
			q->lexem = p->lexem;
			q->next = 0;
			s = q;
		}
		p = p->next;
	}
	s->next = (lexem_list*)malloc(sizeof(lexem_list));
	s->next->lexem.type = I_SEMICOLON;
	s->next->next = 0;
	s->next->prew = s;
	while(s->prew != 0)
		s = s->prew;
	return s;
}

bool check_bool_express(lexem_list* p,varible_list *vl)
{
	if(p->next == 0)
	{
		if(p->lexem.name[0]>='0' && p->lexem.name[0] <='9')
		{
			switch(p->lexem.type_data)
			{
			case(I_INTEGER):
				{
					if(!p->lexem.Idata)
						return FALSE;
					else
						return TRUE;
					break;
				}
			case(I_DOUBLE):
				{
					if(!p->lexem.Ddata)
						return FALSE;
					else
						return TRUE;
					break;
				}
			case(I_CHAR):
				{
					if(!p->lexem.Cdata)
						return FALSE;
					else
						return TRUE;
					break;
				}
			default:
				cout<<"minak osel:)))))))))))"<<endl;
				return TRUE;
			}
		}
		else
		{
			Lexem *q = in_var_list(vl,p->lexem);
			switch(q->type_data)
			{
			case(I_INTEGER):
				{
					if(!q->Idata)
						return FALSE;
					else
						return TRUE;
					break;
				}
			case(I_DOUBLE):
				{
					if(!q->Ddata)
						return FALSE;
					else
						return TRUE;
					break;
				}
			case(I_CHAR):
				{
					if(!q->Cdata)
						return FALSE;
					else
						return TRUE;
					break;
				}
			default:
				cout<<"minak osel:)))))))))))"<<endl;
				return TRUE;
			}
		}
	}
	lexem_list* r2 = 0;
	while(p!=0)
	{
		if(r2 ==0)
		{
			r2 = (lexem_list*)malloc(sizeof(lexem_list));
			r2->lexem = p->lexem;
			r2->next = 0;
			r2->prew = 0;
		}
		else
		{
			lexem_list* q = (lexem_list*)malloc(sizeof(lexem_list));
			q->lexem = p->lexem;
			r2->next = q;
			q->prew = r2;
			q->next = 0;
			r2 = q;
		}
		p = p->next;
	}
	for(;r2->prew!=0;r2 = r2->prew);
	while(r2!=0)
	{
		if(r2->lexem.type >= I_PERCENT && r2->lexem.type <= I_DIVISION)
			{
				lexem_list *f1 = r2,*f2 = r2->prew,*f3 = r2->prew->prew;
				lexem_list *q = (lexem_list*)malloc(sizeof(lexem_list));
				Lexem m;
				if(!(f2->lexem.name[0] >='0' && f2->lexem.name[0] <='9') && f2->lexem.name[0] != 39)
					f2->lexem = *in_var_list(vl,f2->lexem);
				if(!(f3->lexem.name[0] >='0' && f3->lexem.name[0] <='9') && f3->lexem.name[0] != 39)
					f3->lexem = *in_var_list(vl,f3->lexem);
				m = count((*f3).lexem,(*f2).lexem,(*f1).lexem);
				q->next = r2->next;
				if(r2->next!=0)
					r2->next->prew = q;
				q->prew = f3->prew;
				q->lexem = m;
				q->lexem.name[0] = '0';
				q->lexem.name[1] = 0;
				free(f1);
				free(f2);
				free(f3);
				r2 = q;
				if(r2->next == 0)
					break;
			}
			if(r2->lexem.type == I_INC_PLUS || r2->lexem.type == I_INC_MINUS)
			{
				lexem_list *f1 = r2,*f2 = r2->prew,*f3 = r2->prew->prew;
				lexem_list *q = (lexem_list*)malloc(sizeof(lexem_list));
				if(!(f2->lexem.name[0] >='0' && f2->lexem.name[0] <='9') && f2->lexem.name[0] != 39)
					f2->lexem = *in_var_list(vl,f2->lexem);
				switch(f2->lexem.type)
				{
				case(I_INTEGER):
					{
						q->lexem.Idata = f2->lexem.Idata+1;
						break;
					}
				case(I_DOUBLE):
					{
						q->lexem.Ddata = f2->lexem.Ddata+1;
						break;
					}
				case(I_CHAR):
					{
						q->lexem.Cdata = f2->lexem.Cdata+1;
						break;
					}
				}
			}
			if(r2->lexem.type >= I_LOW && r2->lexem.type <= I_NOT_BIGGER)
			{
				lexem_list *f1 = r2,*f2 = r2->prew,*f3 = r2->prew->prew;
				lexem_list *q = (lexem_list*)malloc(sizeof(lexem_list));
				Lexem m;
				if(!(f2->lexem.name[0] >='0' && f2->lexem.name[0] <='9') && f2->lexem.name[0] != 39 && r2->lexem.type != I_BOOL)
					f2->lexem = *in_var_list(vl,f2->lexem);
				if(!(f3->lexem.name[0] >='0' && f3->lexem.name[0] <='9') && f3->lexem.name[0] != 39 && r2->lexem.type != I_BOOL)
					f3->lexem = *in_var_list(vl,f3->lexem);
				m = count((*f3).lexem,(*f2).lexem,(*f1).lexem);
				q->next = r2->next;
				if(r2->next!=0)
					r2->next->prew = q;
				q->prew = f3->prew;
				q->lexem = m;
				q->lexem.name[0] = '0';
				q->lexem.name[1] = 0;
				free(f1);
				free(f2);
				free(f3);
				r2 = q;
				if(r2->next == 0)
					break;
			}
			if(r2->lexem.type == I_AND || r2->lexem.type == I_OR)
			{
			}
		r2 = r2->next;
	}
	if(r2->lexem.Idata)
		return TRUE;
	return FALSE;
}

lexem_list* update_bool_param(lexem_list *p)
{
	lexem_list *head = 0,*stack = (lexem_list*)malloc(sizeof(lexem_list));

	stack->next = 0;
	stack->prew = 0;

	//root->left = 0;
	//root->right = 0;

	while(p!=0)
	{
		if(p->lexem.type == I_IDENTIFIC)
			move_to_list(p->lexem,&head);
		if((p->lexem.type >= I_PERCENT && p->lexem.type <= I_DIVISION) || p->lexem.type == I_BRACKET_OPEN || p->lexem.type == I_BRACKET_CLOSE || p->lexem.type == I_INC_PLUS || p->lexem.type == I_INC_MINUS || (p->lexem.type >= I_LOW && p->lexem.type <= I_AND))
		{
			if(p->lexem.type == I_BRACKET_OPEN)
				push_expres(p->lexem,&stack);
			if(p->lexem.type == I_BRACKET_CLOSE)
			{
				while(stack && stack->lexem.type!= I_BRACKET_OPEN)
					move_to_list(pop_expres(&stack),&head);
				pop_expres(&stack);//delete '('
			}
			if(p->lexem.type ==I_PLUS || p->lexem.type == I_MINUS || p->lexem.type == I_DIVISION || p->lexem.type == I_MULTIPLYING || p->lexem.type == I_INC_PLUS || p->lexem.type == I_INC_MINUS || (p->lexem.type >= I_LOW && p->lexem.type <= I_AND) || p->lexem.type == I_PERCENT)
			{
				if(getprior(p->lexem)<=getprior(stack->lexem))
				{
					move_to_list(pop_expres(&stack),&head);
					push_expres(p->lexem,&stack);
				}
				else
					push_expres(p->lexem,&stack);
			}
		}
		p = p->next;
	}
	
	for(lexem_list *s=stack;s->next!=0;s=s->next)
	{
		move_to_list(s->lexem,&head);
	}
	
	for(;head->prew!=0;head = head->prew);
	return head;
}