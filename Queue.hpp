#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

template<class T>
using Condition = bool(*)(const T&);

template<class T>
struct QueueElement
{
	T data;
	QueueElement<T>* next;
	QueueElement(const T& _data, QueueElement<T>* _next = nullptr)
		:data(_data), next(_next) {}
};

template<class T>
class Queue 
{
public:
	Queue();
	Queue(const Queue<T>&);
	Queue<T>& operator=(const Queue<T>&);
	~Queue();

	unsigned size() const;
	bool empty() const;
	T front() const;
	T back() const;
	void push(const T&);
	void pop();

	std::vector<T> storeElems() const;
	void sort();
	void filter(Condition<T>);
	bool search(Condition<T>) const;
	std::string label() const;
	bool member(const T&) const;
	void print() const;
protected:
	QueueElement<T> *first, *last;
private:
	void copy(const Queue<T>&);
	void clear();
};

template<class T>
Queue<T>::Queue() :first(nullptr), last(nullptr) {}

template<class T>
Queue<T>::Queue(const Queue<T>& other) : first(nullptr), last(nullptr)
{
	copy(other);
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

template<class T>
Queue<T>::~Queue()
{
	clear();
}

template<class T>
bool Queue<T>::empty() const
{
	return last == nullptr;
}

template<class T>
unsigned Queue<T>::size() const
{
	if (empty())
		return 0;
	QueueElement<T>* crr = first;
	unsigned counter = 0;
	while (crr)
	{
		crr = crr->next;
		++counter;
	}
	return counter;
}

template<class T>
T Queue<T>::front() const
{
	if (empty())
	{
		std::cerr << "No front element for an empty stack!!\n";
		return T();
	}
	return first->data;
}

template<class T>
T Queue<T>::back() const
{
	if (empty())
	{
		std::cerr << "No back element for an empty stack!!\n";
		return T();
	}
	return last->data;
}

template<class T>
void Queue<T>::copy(const Queue<T>& other)
{
	if (other.empty())
		return;
	QueueElement<T>* crr = other.first;
	while (crr != nullptr)
	{
		push(crr->data);
		crr = crr->next;
	}
}

template<class T>
void Queue<T>::clear()
{
	while (!empty())
	{
		pop();
	}
}

template<class T>
void Queue<T>::pop()
{
	if (empty())
	{
		std::cerr << "No pop for an empty queue!!\n";
		return;
	}
	QueueElement<T>* crr = first;
	first = first->next;
	if (first == nullptr)
		last = nullptr;
	delete crr;
}

template<class T>
void Queue<T>::push(const T& el)
{
	QueueElement<T>* crr = new QueueElement<T>(el);
	if (!empty())
		last->next = crr;
	else
		first = crr;
	last = crr;
}

template<class T>
bool Queue<T>::member(const T& x) const
{
	QueueElement<T>* crr = first;
	while (crr != nullptr)
	{
		if (crr->data == x)
			return true;
		crr = crr->next;
	}
	return false;
}

template<class T>
void Queue<T>::print() const
{
	if (empty())
	{
		std::cout << "An empty cointainer!!\n" << std::endl;
		return;
	}
	std::cout << "Data structure: Queue\n";
	std::cout << "Size: " << size() << std::endl;
	std::cout << "Elements: ";
	QueueElement<T>* crr = first;
	while (crr != nullptr)
	{
		std::cout <<crr->data << " ";
		crr = crr->next;
	}
	std::cout << std::endl<<std::endl;
}

template<class T>
std::string Queue<T>::label() const
{
	return "Queue";
}

template<class T>
bool Queue<T>::search(Condition<T> pred) const
{
	QueueElement<T>* crr = first;
	while (crr != nullptr)
	{
		if (pred(crr->data))
			return true;
		crr = crr->next;
	}
	return false;
}

template<class T>
void Queue<T>::filter(Condition<T> cond)
{
	QueueElement<T>* crr = first;
	QueueElement<T>* prev = first;
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
		if (crr == nullptr)
			return;
		QueueElement<T>* toDelete = crr;
		prev->next = crr->next;
		crr = crr->next;
		delete toDelete;
	}
}

template<class T>
void Queue<T>::sort()
{
	std::map<int, int> m;
	QueueElement<T>* crr = first;
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
std::vector<T> Queue<T>::storeElems() const
{
	QueueElement<T>* crr = first;
	std::vector<T> elems;
	while (crr)
	{
		elems.push_back(crr->data);
		crr = crr->next;
	}
	return elems;
}

#endif // !QUEUE_HPP
