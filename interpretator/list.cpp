#include "list.h"

template<typename T>
List<T>::List() 
{
	_root = nullptr;
	_last = _root;
}

template<typename T>
List<T>::~List()
{
	for (int i = 0; i < Count(); i++)
		RemoveAt(0);
	delete _root;
}

template<typename T>
int List<T>::Count()
{
	listItem* curr = _root;
	int count = 0;
	for (; curr->next != nullptr; count++)
		curr = curr->next;
	return count;
}

template<typename T>
T& List<T>::operator[](const int idx)
{
	return getIndexOf(idx)->Value;
}

template<typename T>
void List<T>::Add(T value)
{
	if (_root == nullptr)
	{
		_root = new listItem();
		_root->next = _root->prev = nullptr;
		_root->Value = value;
		_last = _root;
		return;
	}

	listItem* item = new listItem();
	item->Value = value;
	item->next = nullptr;
	_last->next = item;
	item->prev - _last;
	_last = item;
}

template<typename T>
int List<T>::IndexOf(T value)
{
	int index = -1;
	bool finded = false;
	listItem* curr = _root;
	while (curr != _last)
	{
		index++;
		if (curr->Value == value)
		{
			finded = true;
			break;
		}
		curr = curr->next;		
	}
	if (finded)
		return index;
	return -1;
}

template<typename T>
void List<T>::Remove(T value)
{
	listItem* curr = _root;
	while (curr->Value != value && curr != _last)
		curr = curr->next;
	if (curr->Value == value)
	{
		if (curr->prev != nullptr)
		{
			curr->prev->next = curr->next;
		}
		if (curr->next != nullptr)
		{
			curr->next->prev = curr->prev;
		}
		delete curr;
	}
}

template<typename T>
void List<T>::InsertAt(T value, int index)
{
	listItem* curr = getIndexOf(index);

	if (curr == nullptr)
		return;
	listItem* newItem = new listItem();
	newItem->Value = value;
	newItem->next = curr;
	newItem->prev = curr->prev;
}

template<typename T>
void List<T>::RemoveAt(int index)
{
	listItem * curr = getIndexOf(index);

	if (curr == nullptr)
		return;
	if (curr->prev != nullptr)
		curr->prev->next = curr->next;

	if (curr->next != nullptr)
		curr->next->prev = curr->prev;
	delete curr;
}

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