#pragma once

#include "main.h"

void move_to_list(Lexem sLexem,lexem_list **head);

int search_in_var_list(Lexem lexem,lexem_list *var_list);

namespace Interpreter {
	namespace Collections {

		template<typename T>
		struct ListItem {
		public:
			ListItem* next;
			ListItem* prev;
			T Value;
		};

		template<typename T>
		class Iterator {
		private:
			bool started;
			ListItem<T>* current;
		public:
			Iterator(ListItem<T>* root);
			~Iterator();
			bool MoveNext();
			T Get();
		};

		template<typename T>
		class List
		{
		private:
			int _count;
			
			ListItem<T>* _root;
			ListItem<T>* _last;
			ListItem<T>* getIndexOf(int index)
			{
				ListItem<T>* curr = _root;
				int count = 0;
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
			T GetAt(int index);
			Iterator<T> GetIterator();
			~List();
		};		
	}
}