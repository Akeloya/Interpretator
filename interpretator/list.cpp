#include "list.h"

namespace Interpreter {
	namespace Collections {

		template<typename T>
		Iterator<T>::Iterator(ListItem<T>* root)
		{
			started = false;
			current = root;
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
		T* Iterator<T>::Get()
		{
			if (current == nullptr)
				return nullptr;
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
			delete _last;
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
			return Iterator<T>::Iterator(_root);
		}

		template<typename T>
		void List<T>::Add(T value)
		{
			T* copyVar = (T*)malloc(sizeof(T));
			*copyVar = value;
			if (_root == nullptr)
			{
				ListItem<T>* s = new ListItem<T>();
				s->Value = copyVar;
				_root = s;
				_last = s;
				return;
			}

			ListItem<T>* item = new ListItem<T>();
			item->Value = copyVar;
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
				if (*curr->Value == value)
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
			while (curr != nullptr && *curr->Value != value)
				curr = curr->next;

			if (curr == nullptr || *curr->Value != value)
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
			delete curr->Value;
			delete curr;
			if (rootIsCurr && !rootChanged)
				_root = nullptr;
		}

		template<typename T>
		void List<T>::InsertAt(T value, const int index)
		{
			ListItem<T>* curr = getIndexOf(index);

			if (curr == nullptr)
				return;
			ListItem<T>* newItem = new ListItem<T>();
			newItem->value = value;
			newItem->next = curr;
			newItem->prev = curr->prev;
		}

		template<typename T>
		void List<T>::RemoveAt(const int index)
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

			delete curr->Value;
			delete curr;
			if (rootIsCurr && !rootChanged)
				_root = nullptr;
		}
	}
}