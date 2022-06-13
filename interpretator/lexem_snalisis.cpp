#include "lexem_analisis.h"
#include "list.h"
#include "Errors.h"

using namespace Interpreter::Collections;

void modificate(lexem_list **lex_head)
{
	lexem_list *p = (*lex_head);
	lexem_list *q = 0;
	if(p!=0 && p->next!=0)
		p = p->next;
	else
		return;
	while(p!=0)
	{
		if(p->prew->lexem.type == I_PLUS && p->lexem.type == I_PLUS)
		{
			q = p;
			memset(p->prew->lexem.name,0,50);
			p->prew->lexem.name[0] = '+';
			p->prew->lexem.name[1] = '+';
			p->prew->next = p->next;
			p->prew->lexem.type = I_INC_PLUS;
			p = p->prew;
			free(q);
		}
		if(p->prew->lexem.type == I_MINUS && p->lexem.type == I_MINUS)
		{
			q = p;
			memset(p->prew->lexem.name,0,50);
			p->prew->lexem.name[0] = '-';
			p->prew->lexem.name[1] = '-';
			p->prew->next = p->next;
			p->prew->lexem.type = I_INC_MINUS;
			p = p->prew;
			free(q);
		}
		if(p->prew->lexem.type == I_ASSIGNMENT && p->lexem.type == I_ASSIGNMENT)
		{
			q = p;
			memset(p->prew->lexem.name,0,50);
			p->prew->lexem.name[0] = '=';
			p->prew->lexem.name[1] = '=';
			p->prew->next = p->next;
			p->prew->lexem.type = I_EQUAL;
			p = p->prew;
			free(q);
		}
		if(p->prew->lexem.type == I_BIGGER && p->lexem.type == I_ASSIGNMENT)
		{
			q = p;
			memset(p->prew->lexem.name,0,50);
			p->prew->lexem.name[0] = '>';
			p->prew->lexem.name[1] = '=';
			p->prew->next = p->next;
			p->prew->lexem.type = I_NOT_LOWER;
			p = p->prew;
			free(q);
		}
		if(p->prew->lexem.type == I_LOW && p->lexem.type == I_ASSIGNMENT)
		{
			q = p;
			memset(p->prew->lexem.name,0,50);
			p->prew->lexem.name[0] = '<';
			p->prew->lexem.name[1] = '=';
			p->prew->next = p->next;
			p->prew->lexem.type = I_NOT_BIGGER;
			p = p->prew;
			free(q);
		}
		if(p->prew->lexem.type == I_NOT && p->lexem.type == I_ASSIGNMENT)
		{
			q = p;
			memset(p->prew->lexem.name,0,50);
			p->prew->lexem.name[0] = '!';
			p->prew->lexem.name[1] = '=';
			p->prew->next = p->next;
			p->prew->lexem.type = I_NOT_LOWER;
			p = p->prew;
			free(q);
		}
		if(p->prew->lexem.type == I_BIN_AND && p->lexem.type == I_BIN_AND)
		{
			q = p;
			memset(p->prew->lexem.name,0,50);
			p->prew->lexem.name[0] = '&';
			p->prew->lexem.name[1] = '&';
			p->prew->next = p->next;
			p->prew->lexem.type = I_AND;
			p = p->prew;
			free(q);
		}
		if(p->prew->lexem.type == I_BIN_OR && p->lexem.type == I_BIN_OR)
		{
			q = p;
			memset(p->prew->lexem.name,0,50);
			p->prew->lexem.name[0] = '|';
			p->prew->lexem.name[1] = '|';
			p->prew->next = p->next;
			p->prew->lexem.type = I_OR;
			p = p->prew;
			free(q);
		}
		p = p->next;
	}
}
/////////////////////////////////////////////////////////

void lex_analisis(FILE *fin,lexem_list **lex_head, List<Error>*er_head)
{
	int c = 0,i = 0, state = 0;
	char lxm[50];
	char *p = (char*)malloc(50);
	memset(lxm,0,50);
	int line_pos = 1;
	while((c = fgetc(fin)) != -1)
	{
		if(c != '(' && c != ')' && c!= ';' && c != '+' && c != '-' && c!= '=' && c != '>' && c != '<' && c != '*' && c != '/' && c != ',' && c != '{' && c !='}' && c != '!' && c!= '|' && c != '&' && c!= ' ' && c !='\n' && c !='\t')
		{
			lxm[i++] = (char)c;			
			if(c== '"' && state == 0)
				state ^= 1;
			else
				if(state && c == '"')
					state ^= 1;
			if(c == 39)
			{
				if(lxm[0] != 39)
				{
					er_head->Add(Error(I_STRING_ERROR,line_pos));
					return;
				}
				lxm[1] = (char)fgetc(fin);
				if(!(lxm[1] >= 'a' && lxm[0] <='z') && !(lxm[1] >='A' && lxm[0] <= 'Z') && !(lxm[1] >='0' && lxm[1] <= '9'))
				{
					if(lxm[1] != 39)
					{
						er_head->Add(Error(I_ERR_IN_END_LINE,line_pos));
						return;
					}
					else
					{
						er_head->Add(Error(I_ENPTY_CHAR_CONST,line_pos));
						return;
					}
					printf("lexem analisis");
				}
				else
					lxm[2] = (char)fgetc(fin);
				if(lxm[2] != 39)
				{
					er_head->Add(Error(I_NO_INVERED_COMMAS,line_pos));
					return;
				}
			}
		}
		else
		{
			if(state == 0)
			{
				if(lxm[0]!=0)
				{
					strcpy(p,lxm);
					Lexem* new_lexem = new Lexem();

					new_lexem->line_pos = line_pos;
					
					strcpy_s(new_lexem->name,lxm);
					
					new_lexem->type = GetLexemType(p,line_pos,lex_head,er_head);		
					
					new_lexem->type_data = new_lexem->type;

					if(new_lexem->type == I_INTEGER || new_lexem->type == I_DOUBLE || new_lexem->type == I_CHAR)
						new_lexem->type = I_IDENTIFIC;
					
					new_lexem->GetValue();
					
					move_to_list(*new_lexem,lex_head);
					
					memset(lxm,0,50);
					delete new_lexem;
				}
				if(c == '\n')
					line_pos++;
				memset(lxm,0,50);
				i = 0;
				if(c!= ' '&& c !='\n' && c !='\t')
				{
					char b[]={0,0};
					b[0] = c;
					
					Lexem *new_lexem = new Lexem();
				
					new_lexem->line_pos = line_pos;
					
					strcpy_s(new_lexem->name,b);
					
					new_lexem->type = GetLexemType(b,line_pos,lex_head, er_head);
					
					new_lexem->type_data = new_lexem->type;
	//				printf("%s \n",b);
					new_lexem->GetValue();

					move_to_list(*new_lexem,lex_head);

					delete new_lexem;
					memset(lxm,0,50);
				//	printf("%c\n",c);
				}
			}
			else
			{
				lxm[i] = (char)c;
				i++;
			}
		}
	}
	if(lxm[0] != 0)
	{
		//printf("%s\n",lxm);
		strcpy(p,lxm);
		Lexem *new_lexem = new Lexem();

		new_lexem->line_pos = line_pos;
						
		strcpy_s(new_lexem->name,lxm);
						
		new_lexem->type = GetLexemType(p,line_pos,lex_head,er_head);		
						
		new_lexem->type_data = new_lexem->type;
						
		if(new_lexem->type == I_INTEGER || new_lexem->type == I_DOUBLE || new_lexem->type == I_CHAR)
			new_lexem->type = I_IDENTIFIC;
		new_lexem->GetValue();
						
		move_to_list(*new_lexem,lex_head);
						
		memset(lxm,0,50);
		delete new_lexem;
	}
	if((*lex_head)!=0)
		for(;(*lex_head)->prew!=0;(*lex_head) = (*lex_head)->prew);
	modificate(lex_head);
}

int GetLexemType(char *lexem,int line_pos,lexem_list **lex_head, List<Error>*er_head)
{
	int i = strlen(lexem);
	int k = 0;
	int state = 0;
	if(i == 1)
	{
		int c = (int)lexem[0];
		switch(c)
		{
			case('('):
				return I_BRACKET_OPEN;
			case(')'):
				return I_BRACKET_CLOSE;
			case('{'):
				return I_BLOCK_OPEN;
			case('}'):
				return I_BLOCK_CLOSE;
			case('-'):
				return I_MINUS;
			case('+'):
				return I_PLUS;
			case('='):
				return I_ASSIGNMENT;
			case('%'):
				return I_PERCENT;
			case('*'):
				return I_MULTIPLYING;
			case('/'):
				return I_DIVISION;
			case(';'):
				return I_SEMICOLON;
			case(','):
				return I_COMMA;
			case('!'):
				return I_NOT;
			case('>'):
				return I_BIGGER;
			case('<'):
				return I_LOW;
			case('|'):
				return I_BIN_OR;
			case('&'):
				return I_BIN_AND;
			default:
				{
					if(c >= '0' && c<= '9')
						return I_INTEGER;
					else
						if((c>='a' && c<='z') || (c>='A' && c<='Z'))
							return I_IDENTIFIC;
						else
						{
							er_head->Add(Error(I_STRING_ERROR,line_pos));
							return I_IDENTIFIC;
						}
				}
		}
		//определение типа лексемы
	}
	else
	{
		if((lexem[0]>='a' && lexem[0]<='z') || (lexem[0] >= 'A' && lexem[0] <= 'Z'))
		{
			bool l = false;
			while(k<i)
			{
				if((lexem[k]>='a' && lexem[k]<='z') || (lexem[k] >= 'A' && lexem[k] <= 'Z'))
					k++;
				else
				{
					k++;
					if(!l)
						l = true;
					else
					{
						er_head->Add(Error(I_STRING_ERROR,line_pos));
						//printf("\n\n\t\tnerror!\n\n");
						break;
					}
				}
			}
			if(strcmp("int",lexem) == 0)
				return I_CONST_WORD;
			if(strcmp("double",lexem) == 0)
				return I_CONST_WORD;
			if(strcmp("void",lexem) == 0)
				return I_CONST_WORD;
			if(strcmp("char",lexem) == 0)
				return I_CONST_WORD;
			if(strcmp("return",lexem) == 0)
				return I_CONST_WORD;
			if(strcmp("if",lexem) == 0)
				return I_CONST_WORD;
			if(strcmp("while",lexem) == 0)
				return I_CONST_WORD;
			if(strcmp("else",lexem) == 0)
				return I_CONST_WORD;
			return I_IDENTIFIC;
		}
		if(lexem[0] == '"')
			if(lexem[i-1] != '"')
			{
				//printf("\n\n\t\tnerror!\n\n");
				er_head->Add(Error(I_STRING_ERROR,line_pos));
				return I_STRING;
			}
			else
				return I_STRING;
		if(lexem[0] >= '0' && lexem[0] <= '9')
		{
			int d = 0;
			while(k<i)
			{
				if(lexem[k] >= '0' && lexem[k] <= '9')
					k++;
				else
					if(lexem[k] == '.' && k < i - 1)
					{
						k++;
						d = 1;
					}
					else
					{
						er_head->Add(Error(I_STRING_ERROR,line_pos));
						//printf("\n\n\t\tnerror!\n\n");
						break;
					}
			}
			if(d == 1)
					return I_DOUBLE;
				else
					return I_INTEGER;
		}
		if(lexem[0] == 39)
			if(i != 3 || lexem[2] != 39)
			{
				//printf("\n\n\terror!\n");
				er_head->Add(Error(I_STRING_ERROR,line_pos));
				return I_CHAR;
			}
			else
				return I_CHAR;
	}
	return 0;
}