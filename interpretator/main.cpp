#include "main.h"
//#include "iostream"
#include "lexem_analisis.h"
#include "hand_errors.h"
#include "condition_stack.h"
#include "syntax_analisis.h"
#include <conio.h>
#include "execute.h"
#include "Stack.h"
#include "Stack.cpp"

using namespace std;

int main(int argv,char *argc[])
{
	FILE* fin = 0;
	char c = 0;
	lexem_list *lex_head = 0;

	Stack<int> *stack = new Stack<int>();

	errors_list * er_head = 0;

	errors_list * war_head = 0;
	
	varible_list* var_list = 0;
	
	execute *root = 0;
	
	_lists *list = (_lists*)malloc(sizeof(_lists));

	char name[50];

	bool errors = FALSE;

	int i = 1;
	
	list->vList = 0;
	list->fList = 0;

	try
	{
		if(argv >1)
		{
			int i=1;
			for(;argc[i];i++)
			{
				cout<<i<<": "<<argc[i]<<endl;
			}
			cout<<"enter number of file:"<<endl;
			cin>>i;
			if(i<argv && i!=0)
			{
				fin = fopen(argc[i],"r");
				strcpy(name,argc[i]);
			}
			else
				cout<<"error in number of file"<<endl;
		}
		else
		{
			char name1[20];
			cin>>name1;
			strcpy(name,name1);
			fin = fopen(name1,"r");
		}
		if(!fin)
		{
			cout<<"no such file!"<<endl;
			return 0;
		}
		cout<<endl;
		int l = 0;
		cout<<++l<<": ";
		while((c = fgetc(fin)) != EOF)
		{	
			cout<<c;
			if(c == '\n')
				cout<<++l<<": ";
		}
		cout<<endl<<endl;
	
		fseek(fin,SEEK_CUR-1,SEEK_SET);
		lex_analisis(fin,&lex_head,&er_head);

		if(!lex_head)
		{
			cout<<"no programm!"<<endl;
			fclose(fin);
			return 0;
		}
		stack->Push(I_PROGRAMM);
	
		syntax_analisis(lex_head,stack,&var_list,&er_head);
	
		if(stack->Peek() == I_PROGRAMM)
		{
			stack->Pop();
			cout<<"syntax analisys secces."<<endl;
		}
		else
		{
			cout<<"compile not secces."<<endl;
		}
		if(!er_head)
		{
			//cout<<"no errors."<<endl;
			struct_execute(&root,&lex_head,&er_head);
			if(!er_head)
			{
				last_checkout(root,&er_head,&war_head,&list);
				free(list->vList);
				list->vList = 0;
				if(war_head)
				{
					cout<<endl<<"<----------------------------------->"<<endl;
					char err[256];
					for(war_head;war_head->next!=0;war_head = war_head->next);
					for(errors_list *p= war_head;p!=0;p = p->prew)
					{
						get_error_string(p->type,p->lise_pos,err);
						cout<<i++<<": "<<err<<endl;
					}
					cout<<endl<<"<----------------------------------->"<<endl;
				}
				if(!er_head)
				{
					varible_list* p = list->vList;
					cout<<"no errors."<<endl;
					cout<<endl<<"<----------------------------------->"<<endl;
					cout<<"compile secces."<<endl;
					if(!do_execute(root,&er_head,&war_head,&list))
					{
						errors = TRUE;
					}
				}
				else
					errors = TRUE;
			}
			else
				errors = TRUE;
		}
		else
			errors = TRUE;

		if(errors)
		{
			cout<<endl<<"<----------------------------------->"<<endl;
			char err[256];
			for(er_head;er_head->next!=0;er_head = er_head->next);
			for(errors_list *p= er_head;p!=0;p = p->prew)
			{
				get_error_string(p->type,p->lise_pos,err);
				cout<<i++<<": "<<err<<endl;
			}
			cout<<endl<<"<----------------------------------->"<<endl;
			cout<<"\nError executing "<<name<<endl;
			getch();
			return 0;
		}

		if(lex_head)
			free(lex_head);
		if(er_head)
			free(er_head);
		if(list)
			free(list);
		if(root)
			free(root);
	//	if(stack_head)
	//		free(stack_head);
		fclose(fin);
		if(!errors)
			cout<<"\nprogramm executed correctly. Press any key to continue..."<<endl;
		getch();
	}
	catch(char* ex)
	{
		cout<<ex<<endl;	
		stack->~Stack();
	}
	return 0;
}