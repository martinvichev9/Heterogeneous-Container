#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

template<class T>
using Condition = bool(*)(const T&);

template<class T>
struct StackElement
{
	T data;
	StackElement<T>* next;
	StackElement(const T& _data, StackElement<T>* _next = nullptr)
		:data(_data), next(_next) {}
};

template<class T>
class Stack 
{
public:
	Stack();
	Stack(const Stack<T>&);
	Stack<T>&  operator= (const Stack<T>&);
	~Stack();

	bool empty() const;
	unsigned size() const;
	T top() const;
	void pop();
	void push(const T&);

	std::vector<T> storeElems() const;
	void sort();
	void filter(Condition<T>);
	bool search(Condition<T>) const;
	std::string label() const;
	bool member(const T&) const;
	void print() const;
protected:
	StackElement<T>* last;
private:
	void copy(StackElement<T>*);
	void clear();
};

template<class T>
Stack<T>::Stack() : last(nullptr) {}

template<class T>
Stack<T>::Stack(const Stack<T>& other)
{
	last = nullptr;
	copy(other.last);
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	if (this != &other)
	{
		clear();
		copy(other.last);
	}
	return *this;
}

template<class T>
Stack<T>::~Stack()
{
	clear();
}

template<class T>
bool Stack<T>::empty() const
{
	return last == nullptr;
}

template<class T>
T Stack<T>::top() const
{
	if (empty())
	{
		std::cerr << "No top for an empty stack!!\n";
		return T();
	}
	return last->data;
}

template<class T>
unsigned Stack<T>::size() const
{
	if (empty())
		return 0;
	unsigned counter = 0;
	StackElement<T>* crr = last;
	while (crr != nullptr)
	{
		crr = crr->next;
		++counter;
	}
	return counter;
}

template<class T>
void Stack<T>::pop()
{
	if (empty())
	{
		std::cerr << "No pop for an empty stack!!\n";
		return;
	}
	StackElement<T>* crr = last;
	last = last->next;
	delete crr;
}

template<class T>
void Stack<T>::push(const T& el)
{
	StackElement<T>* crr = new StackElement<T>(el);
	crr->next = last;
	last = crr;
}

template<class T>
void Stack<T>::clear()
{
	while (!empty())
		pop();
}

template<class T>
void Stack<T>::copy(StackElement<T>* other)
{
	if (other == nullptr)
		return;
	copy(other->next);
	push(other->data);
}

template<class T>
bool Stack<T>::member(const T& x) const
{
	StackElement<T>* crr = last;
	while (crr != nullptr)
	{
		if (crr->data == x)
			return true;
		crr = crr->next;
	}
	return false;
}

template<class T>
void Stack<T>::print() const
{
	if (empty())
	{
		std::cout << "An empty cointainer!!\n" << std::endl;
		return;
	}
	std::cout << "Data structure: Stack\n";
	std::cout << "Size: " << size() << std::endl;
	std::cout << "Elements: ";
	StackElement<T>* crr = last;
	while (crr != nullptr)
	{
		std::cout << crr->data << " ";
		crr = crr->next;
	}
	std::cout << std::endl << std::endl;
}

template<class T>
std::string Stack<T>::label() const
{
	std::string label = "Stack";
	return label;
}

template<class T>
bool Stack<T>::search(Condition<T> pred) const
{
	StackElement<T>* crr = last;
	while (crr != nullptr)
	{
		if (pred(crr->data))
			return true;
		crr = crr->next;
	}
	return false;
}

template <class T>
void Stack<T>::filter(Condition<T> cond)
{
	StackElement<T>* crr = last;
	StackElement<T>* prev = last;
	//if there are elements which satisfy 'cond' and are on the firsts positions
	while (cond(crr->data))
	{
		crr = crr->next;
		prev = prev->next;
		pop();
	}
	while (crr != nullptr)
	{
		while (crr != nullptr && !cond(crr->data))
		{
			prev = crr;
			crr = crr->next;
		}
		//if there is no such element
		if (crr == nullptr)
			return;
		StackElement<T>* toDelete = crr;
		prev->next = crr->next;
		crr = crr->next;
		delete toDelete;
	}
}

template<class T>
void Stack<T>::sort()
{
	std::map<int, int> m;
	StackElement<T>* crr = last;
	while (crr != nullptr)
	{
		m[crr->data]++;
		crr = crr->next;
	}
	clear();
	for (std::map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
	{
		while ((*it).second > 1)
		{
			push((*it).first);
			--(*it).second;
		}
		push((*it).first);
	}
}

template<class T>
std::vector<T> Stack<T>::storeElems() const
{
	const StackElement<T>* crr = last;
	std::vector<T> elems;
	while (crr)
	{
		elems.push_back(crr->data);
		crr = crr->next;
	}
	return elems;
}

#endif // !STACK_HPP
