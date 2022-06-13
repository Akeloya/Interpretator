#pragma once

namespace Interpreter {
	namespace Collections {

		template<typename T>
		struct ListItem {
			ListItem* next = nullptr;
			ListItem* prev = nullptr;
			T* Value = nullptr;
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
			T* Get();
		};

		template<typename T>
		class List {
		private:
			int _count;

			ListItem<T>* _root;
			ListItem<T>* _last;
			ListItem<T>* getIndexOf(int index) {
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
			void RemoveAt(const int index);
			void InsertAt(T value, const int index);
			int IndexOf(T value);
			int Count();
			T GetAt(const int index);
			Iterator<T> GetIterator();
			~List();
		};
	}
}