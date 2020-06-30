#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../../catch2/catch.hpp"
#include "../MyStack/MyStack/CMyStack.h"
#include <utility>
#include <string>

using namespace std;

TEST_CASE("CMyStack")
{
	SECTION("IsEmpty")
	{
		CMyStack<int> stack;
		REQUIRE(stack.IsStackEmpty());
		stack.Push(1);
		REQUIRE(!stack.IsStackEmpty());
	}
	SECTION("Pop")
	{
		SECTION("not empty")
		{
			SECTION("single element")
			{
				CMyStack<int> stack;
				stack.Push(1);
				REQUIRE(!stack.IsStackEmpty());
				stack.Pop();
				REQUIRE(stack.IsStackEmpty());
			}
			SECTION("few elements")
			{
				CMyStack<int> stack;
				stack.Push(1);
				stack.Push(2);
				stack.Push(3);
				stack.Pop();
				REQUIRE(stack.GetTopElement() == 2);
				stack.Pop();
				REQUIRE(stack.GetTopElement() == 1);
				stack.Pop();
				REQUIRE(stack.IsStackEmpty());
			}
		}
		SECTION("empty")
		{
			CMyStack<int> stack;
			REQUIRE_THROWS(stack.Pop());
		}
	}
	SECTION("Top")
	{
		SECTION("not empty")
		{
			CMyStack<int> stack;
			stack.Push(1);
			REQUIRE(stack.GetTopElement() == 1);
			REQUIRE(!stack.IsStackEmpty());
		}
		SECTION("empty")
		{
			CMyStack<int> stack;
			REQUIRE_THROWS(stack.GetTopElement());
		}
	}
	SECTION("Clear")
	{
		SECTION("not empty")
		{
			SECTION("single element")
			{
				CMyStack<int> stack;
				stack.Push(1);
				stack.Clear();
				REQUIRE(stack.IsStackEmpty());
			}
			SECTION("few elements")
			{
				CMyStack<int> stack;
				stack.Push(1);
				stack.Push(2);
				stack.Push(3);
				stack.Clear();
				REQUIRE(stack.IsStackEmpty());
			}
		}
		SECTION("empty")
		{
			CMyStack<int> stack;
			REQUIRE(stack.IsStackEmpty());
			stack.Clear();
			REQUIRE(stack.IsStackEmpty());
		}
	}
	SECTION("auto expand size")
	{
		CMyStack<int> stack;
		for (int i = 0; i < 34; i++)
		{
			stack.Push(i);
		}
		for (int i = 33; i >= 0; i--)
		{
			REQUIRE(stack.GetTopElement() == i);
			stack.Pop();
		}
	}
	SECTION("copy constructor")
	{
		SECTION("empty")
		{
			CMyStack<int> stack1;

			CMyStack<int> stack2(stack1);

			REQUIRE(stack2.IsStackEmpty());
		}
		SECTION("few elements")
		{
			CMyStack<int> stack1;
			stack1.Push(1);
			stack1.Push(2);

			CMyStack<int> stack2(stack1);

			REQUIRE(!stack2.IsStackEmpty());
			REQUIRE(stack2.GetTopElement() == 2);
			stack2.Pop();
			REQUIRE(stack2.GetTopElement() == 1);
			stack2.Pop();
			REQUIRE(stack2.IsStackEmpty());
		}
	}
	SECTION("copy assignment")
	{
		SECTION("empty")
		{
			CMyStack<int> stack1;
			CMyStack<int> stack2;
			stack2.Push(1);
			REQUIRE(!stack2.IsStackEmpty());

			stack2 = stack1;

			REQUIRE(stack2.IsStackEmpty());
		}
		SECTION("few elements")
		{
			CMyStack<int> stack1;
			CMyStack<int> stack2;
			stack1.Push(1);
			stack1.Push(2);

			stack2 = stack1;

			REQUIRE(!stack2.IsStackEmpty());
			REQUIRE(stack2.GetTopElement() == 2);
			stack2.Pop();
			REQUIRE(stack2.GetTopElement() == 1);
			stack2.Pop();
		}
	}
	SECTION("move assignment")
	{
		CMyStack<int> stack1;
		stack1.Push(1);
		stack1.Push(2);
		CMyStack<int> stack2 = move(stack1);

		REQUIRE(!stack2.IsStackEmpty());
		REQUIRE(stack2.GetTopElement() == 2);
		stack2.Pop();
		REQUIRE(stack2.GetTopElement() == 1);
		stack2.Pop();
	}
	SECTION("move constructor")
	{
		CMyStack<int> stack1;
		stack1.Push(1);
		stack1.Push(2);
		CMyStack<int> stack2(move(stack1));

		REQUIRE(!stack2.IsStackEmpty());
		REQUIRE(stack2.GetTopElement() == 2);
		stack2.Pop();
		REQUIRE(stack2.GetTopElement() == 1);
		stack2.Pop();
	}
	SECTION("pushing strings is acceptable")
	{
		CMyStack<string> stack1;
		stack1.Push("Hello");
		stack1.Push("world");
		CMyStack<string> stack2(move(stack1));

		REQUIRE(!stack2.IsStackEmpty());
		REQUIRE(stack2.GetTopElement() == "world");
		stack2.Pop();
		REQUIRE(stack2.GetTopElement() == "Hello");
		stack2.Pop();
		REQUIRE(stack2.IsStackEmpty());
	}
}