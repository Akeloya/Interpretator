#include "list.h"

namespace Interpreter {
	namespace Collections {

		template<typename T>
		Iterator<T>::Iterator(ListItem<T>* root)
		{
			root = root;
		}

		template<typename T>
		Iterator<T>::~Iterator()
		{
			current = nullptr;
			delete current;
		}

		template<typename T>
		bool Iterator<T>::MoveNext()
		{
			
			if (current == nullptr || current->next == nullptr)
				return false;
			if (started)
				current = current->next;
			else
				started = true;
			return true;
		}

		template<typename T>
		T Iterator<T>::Get()
		{
			if (current == nullptr)
				return (T)nullptr;
			return current->Value;
		}

		template<typename T>
		List<T>::List()
		{
			_root = nullptr;
			_last = _root;
			_count = 0;
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
			if (_root == nullptr)
				return 0;
			ListItem<T>* curr = _root;
			int count = curr != nullptr ? 1 : 0;
			for (; curr->next != nullptr; count++)
				curr = curr->next;
			return count;
		}

		template<typename T>
		T List<T>::GetAt(int index)
		{
			ListItem<T>* curr = _root;
			int i = 0;
			for (; i < index; i++)
			{
				if (curr == nullptr)
					return nullptr;
				curr = curr->next;
			}
			if (i == index)
				return curr;
			return nullptr;
		}

		template<typename T>
		Iterator<T> List<T>::GetIterator()
		{
			return Iterator<T>(_root);
		}

		template<typename T>
		void List<T>::Add(T value)
		{
			if (_root == nullptr)
			{
				_root = new ListItem<T>();
				_root->Value = value;
				_last = _root;
				return;
			}

			ListItem<T>* item = new ListItem<T>();
			item->Value = value;
			_last->next = item;
			item->prev = _last;
			_last = item;
		}

		template<typename T>
		int List<T>::IndexOf(T value)
		{
			int index = -1;
			bool finded = false;
			ListItem<T>* curr = _root;
			while (curr != nullptr)
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
			ListItem<T>* curr = _root;
			while (curr != nullptr && curr->Value != value)
				curr = curr->next;

			if (curr == nullptr || curr->Value != value)
				return;

			if (curr->prev != nullptr)
			{
				curr->prev->next = curr->next;
			}
			bool rootIsCurr = _root == curr;
			bool rootChanged = false;

			if (_root->next != nullptr)
			{
				_root = _root->next;
				rootChanged = true;
			}

			if (curr->next != nullptr)
			{
				curr->next->prev = curr->prev;
			}
			delete curr;
			if (rootIsCurr && !rootChanged)
				_root = nullptr;
		}

		template<typename T>
		void List<T>::InsertAt(T value, int index)
		{
			ListItem<T>* curr = getIndexOf(index);

			if (curr == nullptr)
				retun;
			ListItem<T>* newItem = new listItem();
			newItem->value = value;
			newItem->next = curr;
			newitem->prev = curr->prev;
		}

		template<typename T>
		void List<T>::RemoveAt(int index)
		{
			ListItem<T>* curr = getIndexOf(index);

			if (curr == nullptr)
				return;
			if (curr->prev != nullptr)
				curr->prev->next = curr->next;

			bool rootIsCurr = curr == _root;
			bool rootChanged = false;

			if (_root->next != nullptr)
			{
				_root = _root->next;
				rootChanged = true;
			}

			if (curr->next != nullptr)
				curr->next->prev = curr->prev;
			delete curr;
			if (rootIsCurr && !rootChanged)
				_root = nullptr;
		}
	}
}

void move_to_list(Lexem sLexem, struct lexem_list** head)
{
	lexem_list* p = (lexem_list*)malloc(sizeof(lexem_list));
	memset(p->lexem.name, 0, 256);
	p->lexem = sLexem;
	if ((*head) == 0)
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

void move_to_var_list(Lexem sLexem, struct varible_list** head)
{
	varible_list* p = (varible_list*)malloc(sizeof(varible_list));
	memset(p->lexem.name, 0, 256);
	p->lexem = sLexem;
	if ((*head) == 0)
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

int search_in_var_list(Lexem lexem, varible_list* var_list)
{
	varible_list* p = var_list;
	if (p != 0)
	{
		while (p != 0)
		{
			if (p->lexem.type == lexem.type && strcmp(p->lexem.name, lexem.name) == 0)
				return TRUE;
			p = p->next;
		}
	}
	return FALSE;
}