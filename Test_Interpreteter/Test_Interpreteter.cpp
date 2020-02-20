#include "pch.h"
#include "CppUnitTest.h"
#include "../interpretator/Stack.h"
#include "../interpretator/Stack.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestInterpreteter
{
	TEST_CLASS(TestInterpreteter)
	{
	public:
		
		TEST_METHOD(TestMethod1)
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
	};
}
