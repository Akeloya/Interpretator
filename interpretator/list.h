#pragma once

#include "main.h"

void move_to_list(Lexem sLexem,lexem_list **head);

void move_to_var_list(Lexem sLexem,struct varible_list **head);

int search_in_var_list(Lexem lexem,varible_list *var_list);


template<typename T>
class List
{
private:
	struct listItem {
	public:
		listItem* next;
		listItem* prev;
		T Value;
	};
	listItem* _root;
	listItem* _last;
	listItem* getIndexOf(int index)
	{
		listItem* curr = _root;
		int cout = 0;
		while (count < index && curr != nullptr)
		{
			curr = curr->next;
			count++;
		}
		return curr;
	}
public:
	List();
	void Add(T value);
	void Remove(T value);
	void RemoveAt(int index);
	void InsertAt(T value, int index);
	int IndexOf(T value);
	int Count();
	~List();
};