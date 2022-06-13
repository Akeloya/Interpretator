#pragma once

namespace Interpreter {
	namespace Collections {

		struct ListItem {
			ListItem* next = nullptr;
			ListItem* prev = nullptr;
			void* Value = nullptr;
		};


		template<typename T>
		class Iterator {
		private:
			bool started;
			ListItem* current;
		public:
			Iterator(ListItem* root);
			~Iterator();
			bool MoveNext();
			T* Get();
		};

		template<typename T>
		class List {
		private:
			int _count;

			ListItem* _root;
			ListItem* _last;
			ListItem* getIndexOf(int index) {
				ListItem* curr = _root;
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