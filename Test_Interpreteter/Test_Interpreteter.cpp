#include "pch.h"
#include "CppUnitTest.h"
#include <stdlib.h>
#include "../interpretator/Stack.h"
#include "../interpretator/Stack.cpp"
#include "../interpretator/list.h"
#include "../interpretator/list.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
			{
				list->Add(i);
				Assert::AreEqual(i, list->IndexOf(i));
			}
			Assert::AreEqual(1000, list->Count());

			for (int i = 0; list->Count(); i++)
				list->RemoveAt(0);

			Assert::AreEqual(0, list->Count());
			list->~List();

			list = new List<int>();
			for (int i = 0; i < 100; i++)
			{
				list->Add(i);
				Assert::AreEqual(i, list->IndexOf(i));
			}			
			for (int i = 0; list->Count(); i++)
				list->Remove(i);

			Assert::AreEqual(0, list->Count());
			list->~List();
		}

		TEST_METHOD(TestListRandValue)
		{
			List<int>* list = new List<int>();
			srand(10000);
			for (int i = 0; i < 1000; i++)
			{
				int val = rand();
				list->Add(val);				
				Assert::AreEqual(val, (*list)[i]);
			}
			list->~List();
		}
	};
}
