#include "pch.h"
#include "CppUnitTest.h"
#include "../interpretator/Stack.h"
#include "../interpretator/Stack.cpp"
#include "../interpretator/list.h"
#include "../interpretator/list.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Interpreter::Collections;

namespace TestInterpreteter
{
	TEST_CLASS(TestInterpreteter)
	{
	public:
		
		TEST_METHOD(TestStack)
		{
			Stack<int>* stack = new Stack<int>();
			for (int i = 0; i < 1000; i++)
				stack->Push(i);
			stack->~Stack();
			stack = new Stack<int>();
			for (int i = 0; i < 1000; i++)
				stack->Push(i);
			Assert::AreEqual(1000, stack->Depth());
			Assert::AreEqual(10, stack->Take(989));
			for (int i = 999; i >= 0; i--)
			{
				Assert::AreEqual(i, stack->Peek());
				stack->Pop();
			}
			stack->~Stack();
		}

		TEST_METHOD(TestList)
		{
			List<int>* list = new List<int>();
			for (int i = 0; i < 1000; i++)
				list->Add(i);
			for (int i = 0; i < 1000; i++)
				Assert::AreEqual(i, list->IndexOf(i));
			Assert::AreEqual(1000, list->Count());
			for (int i = 0; i < 1000; i++)
				list->Remove(i);
			Assert::AreEqual(0, list->Count());
			for (int i = 0; i < 100; i++)
				list->Add(i);
			Assert::AreEqual(100, list->Count());
			for (int i = 0; i < 100; i++)
				list->RemoveAt(0);
			Assert::AreEqual(0, list->Count());
			for (int i = 0; i < 1000; i++)
				list->Add(i);
			Assert::AreEqual(1000, list->Count());
			
			Iterator<int> iterator = list->GetIterator();

			int check = 0;
			while (iterator.MoveNext()) 
			{
				Assert::AreEqual(check++, iterator.Get());
			} 
			for (Iterator<int> it = list->GetIterator(); it.MoveNext();) 
			{
				Assert::AreEqual(check++, iterator.Get());
			}
			list->~List();
		}
	};
}
