#pragma once

namespace Interpreter {
	namespace Collections {

		template<typename T>
		class Stack
		{
		private:
			struct stackItem {
			public:
				stackItem* next;
				T Value;
			};
			stackItem* _stack;
			int _depth;
		public:
			Stack();
			void Push(T);
			T Pop();
			T Peek();
			T Take(int takenDepth);
			int Depth();
			~Stack();
		};
	}
}
