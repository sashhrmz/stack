#pragma once

#include "Stack.h"
#include "cassert"


void Test() {
	Stack<int> stack1;
	stack1.Push(1);
	stack1.Push(2);
	stack1.Push(12);
	stack1.Push(176);
	stack1.Push(89);
	stack1.Push(98);
	stack1.Push(34);
	stack1.Push(91);
	stack1.Push(100);
	stack1.Push(6);
	stack1.Push(3);
	stack1.Push(8);

	Stack<int> stack2;
	stack1.Push(8);
	stack1.Push(10);
	stack1.Push(0);
	stack1.Push(1);
	stack1.Push(64);
	stack1.Push(98);
	stack1.Push(211111);
	stack1.Push(82);
	stack1.Push(9877);
	stack1.Push(1289);

	{
		Stack<int> stack3(stack2);

		Stack<int> stack4;
		stack4.Push(1);
		stack4.Push(2);
		stack4.Push(12);
		stack4.Push(176);
		stack4.Push(89);
		stack4.Push(98);
		stack4.Push(34);
		stack4.Push(91);
		stack4.Push(100);
		stack4.Push(6);
		stack4.Push(3);
		stack4.Push(8);
		stack4.Push(8);
		stack4.Push(10);
		stack4.Push(0);
		stack4.Push(1);
		stack4.Push(64);
		stack4.Push(98);
		stack4.Push(211111);
		stack4.Push(82);
		stack4.Push(9877);
		stack4.Push(1289);

		assert(stack1 != stack2);
		assert(stack3 == stack2);
		stack1 += stack2;
		assert(stack4 == stack1);
		for (int i = 0; i < 7; ++i) {
			stack1.Pop();
		}
		Stack<int> stack6(stack1);
		Stack<int> stack7(stack2);
		Stack<int> stack8 = stack1 + stack2;
		assert(stack6 == stack1);
		assert(stack7 == stack2);
		stack1 += stack2;
		assert(stack8 == stack1);
	}

	{
		Stack<int> stack3;
		assert(stack3.IsEmpty() == true);
		assert(stack3.Size() == 0);
		stack3.Push(4);
		assert(stack3.IsEmpty() == false);
		assert(stack3.Size() == 1);
		assert(stack3.Top() == 4);
	}
}
