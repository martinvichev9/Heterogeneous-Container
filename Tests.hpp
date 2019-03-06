#ifndef TEST_HPP
#define TEST_HPP

#include "Stack.hpp"
#include "Queue.hpp"
#include "DoublyLinkedList.hpp"
#include "LinkedList.hpp"
#include "Container.hpp"
#include <assert.h>

template<class T>
bool greaterThanHundred(const T& num)
{
	return num > 100;
}
bool even(const int& num)
{
	return (num % 2 == 0);
}
bool e(const int& num, Condition<int> pred)
{
	return pred(num);
}
bool greaterThanFive(const int& num)
{
	return num > 5;
}
bool lessThanFive(const int& num)
{
	return num < 5;
}

void testStack()
{
	Stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	st.push(6);

	assert(st.top() == 6);
	assert(st.size() == 6);
	assert(st.empty() == false);

	st.pop();
	st.pop();
	assert(st.top() == 4);
	assert(st.size() == 4);

	st.push(78);
	assert(st.top() == 78);
	assert(st.size() == 5);

	Stack<int> s = st;
	assert(s.empty() != true);
	assert(s.top() == 78);

	Stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);

	stack = st;

	assert(stack.top() == 78);
	assert(stack.size() == 5);

	assert(stack.member(78));
	assert(!stack.member(-100));
	assert(stack.label() == "Stack");

}

void testQueue()
{
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	Queue<int> qu;

	assert(q.size() == 4);
	assert(q.front() == 1);
	assert(q.back() == 4);
	assert(qu.empty());

	qu = q;

	assert(qu.size() == 4);
	assert(qu.front() == 1);
	assert(qu.back() == 4);
	assert(!qu.empty());
	qu.push(17);
	qu.pop();

	assert(qu.size() == 4);
	assert(qu.front() == 2);
	assert(qu.back() == 17);
	assert(!qu.empty());

	while (!qu.empty())
	{
		qu.pop();
	}

	assert(qu.size() == 0);
	qu.push(3);
	assert(qu.front() == 3);
	assert(qu.size() == 1);
	assert(qu.label() == "Queue");

}

void testDoublyLinkedList()
{
	DoublyLinkedList<int> ls;
	assert(ls.empty());

	ls.push_back(1);
	ls.push_back(2);
	ls.push_back(3);
	ls.push_back(4);
	ls.push_back(5);
	ls.push_back(6);

	assert(ls.size() == 6);
	assert(ls.back() == 6);
	assert(ls.front() == 1);

	ls.pop_back();
	assert(ls.size() == 5);
	assert(ls.front() == 1);
	assert(ls.back() == 5);

	ls.pop_front();
	assert(ls.size() == 4);
	assert(ls.front() == 2);
	assert(ls.back() == 5);

	ls.remove(2);
	assert(ls.back() == 5);

	ls.remove(16);

	assert(!ls.empty());
	ls.insert(9, 0);
	assert(ls.front() == 9);
	ls.insert(16, 4);
	assert(ls.back() == 16);

	DoublyLinkedList<int> crr = ls;
	assert(!crr.empty());
	assert(crr.front() == 9);
	assert(crr.back() == 16);

}

void testLinkedList()
{
	LinkedList<int> l;
	l.push_front(1);
	l.push_back(2);

	assert(l.size() == 2);
	assert(l.front() == 1);

	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	l.push_back(7);
	l.push_back(8);
	l.push_front(-100);
	assert(l.size() == 9);
	assert(l.front() == -100);
	assert(l.empty() != true);

	l.pop_front();
	l.pop_front();
	l.pop_front();
	l.pop_front();

	assert(l.size() == 5);

	LinkedList<int> ls = l;

	assert(!l.empty());
	assert(l.front() == 4);

}

void testContainer()
{
	
	LinkedList<Container<int>*> l;
	Container<int>* st = new NewStack<int>;
	for (int i = 0; i < 10; ++i)
	{
		st->insert(i);
	}
	l.push_back(st);


	Container<int>* q = new NewQueue<int>;
	for (int i = 10; i <= 20; ++i)
	{
		q->insert(i);
	}
	l.push_back(q);

	assert(l.size() == 2);
	assert(l.front()->size() == 10);
	assert(l.front()->member(4));
	assert(!l.front()->member(10));
	assert(l.front()->label() == "Stack");

	l.pop_front();

	assert(l.front() == q);
}

void testFilters()
{
	Stack<int> st;
	Queue<int> q;
	DoublyLinkedList<int> dll;

	for (int i = 0; i <= 10; ++i)
	{
		st.push(i);
		dll.push_back(i);
		q.push(i);
	}

	st.filter(greaterThanHundred);
	assert(st.size() == 11);
	st.filter(greaterThanFive);
	assert(st.size() == 6);

	q.filter(greaterThanHundred);
	assert(q.size() == 11);

	dll.filter(even);
	assert(dll.size() == 5);
	dll.filter(lessThanFive);
	assert(dll.size() == 3);

}

void testSort()
{

	Stack<int> st;
	st.push(3);
	st.push(1);
	st.push(4);
	st.push(2);
	st.push(5);

	st.sort();

	Queue<int> q;
	q.push(3);
	q.push(2);
	q.push(5);
	q.push(4);
	q.push(1);

	q.sort();

	DoublyLinkedList<int> dll;
	dll.push_front(4);
	dll.push_front(5);
	dll.push_front(2);
	dll.push_front(1);
	dll.push_back(3);

	dll.sort();

	for (int i = 1; i <= 5; ++i) {
		assert(st.top() == 6 - i && q.front() == i && dll.front() == i);	
		st.pop();
		q.pop();
		dll.pop_front();
	}

}

void tests()
{
	testContainer();
	testLinkedList();
	testStack();
	testDoublyLinkedList();
	testQueue();
	testFilters();
	testSort();

}

#endif // !TEST_HPP
