#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

template<class T>
struct ListElem
{
	T data;
	ListElem<T>* next;
	ListElem(const T& _data, ListElem<T>* _next = nullptr)
		:data(_data), next(_next) {}
};

template<class T>
class LinkedList
{
public:
	
	class Iterator
	{
		ListElem<T>* crr;

	public:
		Iterator(ListElem<T>* node)
		{
			crr = node;
		}
		bool operator!=(const Iterator& other) const
		{
			return !(crr == other.crr);
		}
		bool operator==(const Iterator& other) const
		{
			return crr == other.crr;
		}
		void operator++()
		{
			crr = crr->next;
		}
		T& operator*()
		{
			return crr->data;
		}
		T operator*()const
		{
			return crr->data;
		}

	};

	Iterator begin() const
	{
		return Iterator(first);
	}
	Iterator end() const
	{
		return Iterator(nullptr);
	}

	LinkedList();
	LinkedList(const LinkedList<T>&);
	LinkedList<T>& operator=(const LinkedList<T>&);
	~LinkedList();

	bool empty() const;
	unsigned size() const;
	T front() const;

	void push_front(const T&);
	void pop_front();
	void push_back(const T&);			//used in copy function(singly-linked lists don't have such method)
	void remove(unsigned);
	void insert(const T&, unsigned);

	bool member(const T&) const;
	void print() const;
protected:
	ListElem<T>* first;
private:
	void copy(const LinkedList<T>&);
	void clear();
	ListElem<T>* locate(unsigned) const;
};

template<class T>
LinkedList<T>::LinkedList() :first(nullptr) {}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	copy(other);
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template<class T>
void LinkedList<T>::clear()
{
	while (!empty())
		pop_front();
}

template<class T>
void LinkedList<T>::copy(const LinkedList<T>& other)
{

	if (other.first == nullptr)
		return;
	first = nullptr;
	ListElem<T>* crr = other.first;
	while (crr != nullptr)
	{
		push_back(crr->data);
		crr = crr->next;
	}
}

template<class T>
ListElem<T>* LinkedList<T>::locate(unsigned ind) const
{
	ListElem<T>* crr = first;
	while (crr != nullptr && ind > 0)
	{
		crr = crr->next;
		--ind;
	}
	return crr;
}

template<class T>
bool LinkedList<T>::empty() const
{
	return first == nullptr;
}

template<class T>
unsigned LinkedList<T>::size() const
{
	unsigned counter = 0;
	ListElem<T>* crr = first;
	while (crr != nullptr)
	{
		crr = crr->next;
		++counter;
	}
	return counter;
}

template<class T>
T LinkedList<T>::front() const
{
	if (empty())
	{
		std::cerr << "No front element in an empty list!!\n";
		return T();
	}
	return first->data;
}

template<class T>
void LinkedList<T>::push_front(const T& elem)
{
	first = new ListElem<T>(elem, first);
}

template<class T>
void LinkedList<T>::push_back(const T& elem)
{
	if (empty())
	{
		push_front(elem);
		return;
	}
	ListElem<T>* crr = first;
	while (crr->next != nullptr)
		crr = crr->next;
	crr->next = new ListElem <T>(elem, nullptr);
}

template<class T>
void LinkedList<T>::pop_front()
{
	if (empty())
	{
		std::cerr << "Can not removing first element from an empty list!!\n";
		return;
	}
	ListElem<T>* crr = first;
	first = first->next;
	delete crr;
}

template<class T>
void LinkedList<T>::remove(unsigned ind)
{
	if (ind == 0)
	{
		pop_front();
		return;
	}
	ListElem<T>* crr = locate(ind - 1);
	if (crr == nullptr || crr->next == nullptr)
		return;

	ListElem<T>* toDelete = crr->next;
	crr->next = crr->next->next;
	delete toDelete;
}

template<class T>
void LinkedList<T>::insert(const T& elem, unsigned ind)
{
	if (ind == 0)
	{
		push_front(elem);
		return;
	}
	else if (ind == size())
	{
		push_back(elem);
		return;
	}
	else
	{
		ListElem<T>* crr = locate(ind - 1);
		if (crr == nullptr)
			return;
		ListElem<T>* _new = new ListElem(elem, crr->next);
		crr->next = _new;
	}
}

template<class T>
void LinkedList<T>::print() const
{
	if (empty())
		return;
	ListElem<T>* crr = first;
	while (crr != nullptr)
	{
		std::cout << crr->data << " ";
		crr = crr->next;
	}
	std::cout << std::endl;
}
 
template<class T>
bool LinkedList<T>::member(const T& elem) const
{
	ListElem<T>* crr = first;
	while (crr != nullptr)
	{
		if (crr->data == elem)
			return true;
		crr = crr->next;
	}
	return false;
}

#endif // !LINKED_LIST_HPP
