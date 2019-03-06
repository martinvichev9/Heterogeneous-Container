#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <iostream>
#include <string>
#include <map>
#include <vector>

template<class T>
using Condition = bool(*)(const T&);

template<class T>
struct DoublyLinkedListElem
{
	T data;
	DoublyLinkedListElem *prev, *next;
	DoublyLinkedListElem(const T& _data, DoublyLinkedListElem<T>* _prev = nullptr, DoublyLinkedListElem<T>* _next = nullptr)
		:data(_data), prev(_prev), next(_next) {}
};

template<class T>
class DoublyLinkedList
{
public:
	
	class Iterator
	{
		DoublyLinkedListElem<T>* crr;
	public:
		Iterator(DoublyLinkedListElem<T>* node)
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
		void operator--()
		{
			crr = crr->prev;
		}
		T& operator*()
		{
			return crr->data;
		}
		T operator*() const
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

	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>&);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
	~DoublyLinkedList();

	bool empty() const;
	unsigned size() const;
	T front() const;
	T back() const;
	void push_back(const T&);
	void push_front(const T&);
	void pop_back();
	void pop_front();
	void insert(const T&, unsigned);
	void remove(unsigned);

	std::vector<T> storeElems() const;
	void sort();
	void filter(Condition<T>);
	bool search(Condition<T>) const;
	std::string label() const;
	bool member(const T&) const;
	void print() const;
protected:
	DoublyLinkedListElem<T> *first, *last;
private:
	DoublyLinkedListElem<T>* locate(unsigned) const;
	void copy(const DoublyLinkedList<T>&);
	void clear();
};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() : first(nullptr), last(nullptr) {}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
{
	copy(other);
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();
}

template<class T>
void DoublyLinkedList<T>::copy(const DoublyLinkedList<T>& other)
{
	if (other.first == nullptr)
		return;
	first = nullptr;
	last = nullptr;
	DoublyLinkedListElem<T>* crr = other.first;
	while (crr != nullptr)
	{
		push_back(crr->data);
		crr = crr->next;
	}
}

template<class T>
void DoublyLinkedList<T>::clear()
{
	while (!empty())
		pop_front();			//or pop_back()
}

template<class T>
DoublyLinkedListElem<T>* DoublyLinkedList<T>::locate(unsigned ind) const
{
	DoublyLinkedListElem<T>* crr = first;
	while (crr != nullptr && ind > 0)
	{
		crr = crr->next;
		--ind;
	}
	return crr;
}

template<class T>
bool DoublyLinkedList<T>::empty() const
{
	return first == nullptr;
}

template<class T>
unsigned DoublyLinkedList<T>::size() const
{
	DoublyLinkedListElem<T>* crr = first;
	unsigned counter = 0;
	while (crr != nullptr)
	{
		crr = crr->next;
		++counter;
	}
	return counter;
}

template<class T>
T DoublyLinkedList<T>::front() const
{
	if (empty())
	{
		std::cerr << "Can not taking element from an empty list!!\n";
		return T();
	}
	return first->data;
}

template<class T>
T DoublyLinkedList<T>::back() const
{
	if (empty())
	{
		std::cerr << "Can not taking element from an empty list!!\n";
		return T();
	}
	return last->data;
}

template<class T>
void DoublyLinkedList<T>::push_back(const T& elem)
{
	//if list is empty
	if (empty())
	{
		first = new DoublyLinkedListElem<T>(elem);
		last = first;
		return;
	}
	last->next = new DoublyLinkedListElem<T>(elem);
	last->next->prev = last;
	last = last->next;
}

template<class T>
void DoublyLinkedList<T>::push_front(const T& elem)
{
	DoublyLinkedListElem<T>* _new = new DoublyLinkedListElem<T>(elem);
	//if list is empty
	if (empty())
	{
		first = _new;
		last = first;
		return;
	}
	_new->next = first;
	first->prev = _new;
	first = _new;
}

template<class T>
void DoublyLinkedList<T>::pop_front()
{
	if (empty())
	{
		std::cerr << "Can not removing element from an empty list!!\n";
		return;
	}
	DoublyLinkedListElem<T>* crr = first;
	first = first->next;
	//!!! very important because, if we delete nullptr ... 
	if (first == nullptr)
		last = nullptr;
	else
	{
		//!!! very important too !!!
		first->prev = nullptr;
	}
	delete crr;
}

template<class T>
void DoublyLinkedList<T>::pop_back()
{
	if (empty())
	{
		std::cerr << "Can not removing element from an empty list!!\n";
		return;
	}
	DoublyLinkedListElem<T>* crr = last;
	last = last->prev;
	//!!! very important because, if we delete nullptr ... 
	if (last == nullptr)
		first = nullptr;
	else
	{
		//!!! very important too !!!
		last->next = nullptr;
	}
	delete crr;
}

template<class T>
void DoublyLinkedList<T>::insert(const T& elem, unsigned ind)
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
		DoublyLinkedListElem<T>* crr = locate(ind - 1);
		if (crr == nullptr)
			return;
		DoublyLinkedListElem<T>* _new = new DoublyLinkedListElem<T>(elem);
		crr->next->prev = _new;
		_new->next = crr->next;
		_new->prev = crr;
		crr->next = _new;
	}
}

template<class T>
void DoublyLinkedList<T>::remove(unsigned ind)
{
	if (ind == 0)
	{
		pop_front();
		return;
	}
	else if (ind == (size() - 1))
	{
		pop_back();
		return;
	}
	else
	{
		DoublyLinkedListElem<T>* crr = locate(ind - 1);
		if (crr == nullptr || crr->next == nullptr)
			return;
		DoublyLinkedListElem<T>* toDelete = crr->next;
		crr->next = crr->next->next;
		toDelete->next->prev = crr;
		delete toDelete;
	}
}

template<class T>
bool DoublyLinkedList<T>::member(const T& x) const
{
	DoublyLinkedListElem<T>* crr = first;
	while (crr != nullptr)
	{
		if (crr->data == x)
			return true;
		crr = crr->next;
	}
	return false;
}

template<class T>
void DoublyLinkedList<T>::print() const
{
	if (empty())
	{
		std::cout << "An empty cointainer!!\n" << std::endl;
		return;
	}
	std::cout << "Data structure: Doubly-Linked list\n";
	std::cout << "Size: " << size() << std::endl;
	std::cout << "Elements: ";
	for (DoublyLinkedList<T>::Iterator it = begin(); it != end(); ++it)
	{
		std::cout << (*it) << " ";
	}
	std::cout << std::endl << std::endl;
}

template<class T>
std::string DoublyLinkedList<T>::label() const
{
	return "DoublyLinkedList";
}

template<class T>
bool DoublyLinkedList<T>::search(Condition<T> pred) const
{
	for (DoublyLinkedList<T>::Iterator it = begin(); it != end(); ++it)
	{
		if (pred(*it))
			return true;
	}
	return false;
}

template<class T>
void DoublyLinkedList<T>::filter(Condition<T> cond)
{
	DoublyLinkedListElem<T>* crr = first;
	DoublyLinkedListElem<T>* beforeCrr = first;
	while (cond(crr->data))
	{
		crr = crr->next;
		beforeCrr = beforeCrr->next;
		pop_front();
	}
	while (crr != nullptr)
	{
		while (crr != nullptr && !cond(crr->data))
		{
			beforeCrr = crr;
			crr = crr->next;
		}
		if (crr == nullptr)
			return;
		DoublyLinkedListElem<T>* toDelete = crr;
		beforeCrr->next = crr->next;
		//if the element is last, we cannot access it (crr->next->prev) !!!
		if (crr->next != nullptr)
			crr->next->prev = beforeCrr;
		crr = crr->next;
		delete toDelete;
	}
}

template<class T>
void DoublyLinkedList<T>::sort()
{
	std::map<int, int> m;
	DoublyLinkedListElem<T>* crr = first;
	while (crr != nullptr)
	{
		m[crr->data]++;
		crr = crr->next;
	}
	clear();
	//chose to insert elements with push_front and iterate through reverse_iterator
	for (std::map<int, int>::reverse_iterator it = m.rbegin(); it != m.rend(); ++it)
	{
		while ((*it).second > 1)
		{
			push_front((*it).first);
			--(*it).second;
		}
		push_front((*it).first);
	}
}

template<class T>
std::vector<T> DoublyLinkedList<T>::storeElems() const
{
	std::vector<T> elems;
	for (DoublyLinkedList<T>::Iterator it = begin(); it != end(); ++it)
	{
		elems.push_back((*it));
	}
	return elems;
}

#endif // !DOUBLY_LINKED_LIST
