#include "Stack.h"

template<typename T>
Stack<T>::Stack()
{
	_stack = new stackItem();
	_stack->next = nullptr;
	_depth = 0;
}

template<typename T>
void Stack<T>::Push(T value)
{
	stackItem* item = new stackItem();
	item->next = nullptr;
	item->Value = value;
	if (_stack == nullptr)
	{
		_stack = item;
	}
	else
	{
		item->next = _stack;
		_stack = item;
	}
	_depth++;
}

template<typename T>
T Stack<T>::Pop()
{
	if (_stack == nullptr)
		return (T)nullptr;
	stackItem* result = _stack;
	_stack = _stack->next;
	T resultValue = result->Value;
	delete result;
	_depth--;
	return resultValue;
}

template<typename T>
T Stack<T>::Peek()
{
	if (_stack == nullptr)
		return (T)nullptr;
	return _stack->Value;
}

template<typename T>
T Stack<T>::Take(int takenDepth)
{
	if (takenDepth > _depth)
		return (T)nullptr;
	stackItem* curr = _stack;
	for (int i = 0; i < _depth; i++)
		curr = curr->next;
	return curr->Value;
}

template<typename T>
int Stack<T>::Depth()
{
	return _depth;
}

template<typename T>
Stack<T>::~Stack()
{
	for (; Depth() > 0;)
		Pop();
	delete _stack;
	_stack = nullptr;
}