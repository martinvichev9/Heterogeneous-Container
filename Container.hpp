#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "LinkedList.hpp"
#include "Stack.hpp"
#include "DoublyLinkedList.hpp"
#include "Queue.hpp"
#include <iomanip>

template<class T>
class Container
{
public:
	
	virtual void insert(const T&) = 0;			
	virtual void remove() = 0;						
    virtual bool member(const T&) const = 0;
	virtual bool search(Condition<T>) const = 0;
	virtual unsigned size() const = 0;
	virtual void addMin(const T&) = 0;			//adds in a container with the smallest size
	virtual void filter(Condition<T>) = 0;
	virtual void sort() = 0;
	virtual std::vector<T> elems() const = 0;
	virtual std::string label() const = 0;
	virtual void print() const = 0;
	virtual ~Container() {}
	
};

template<class T>
class ListContainer : public LinkedList<Container<T>*>
{
public:
	
	bool isMember(const T& elem) const
	{
		for (LinkedList<Container<T>*>::Iterator it = begin(); it != end(); ++it)
		{
			if ((*it)->member(elem))
				return true;
		}
		return false;
	}
	void minAdd(const T& elem)
	{
		unsigned minSize = INT_MAX;
		for (LinkedList<Container<T>*>::Iterator it = begin(); it != end(); ++it)
		{
			if ((*it)->size() < minSize)
				minSize = (*it)->size();
		}
		for (LinkedList<Container<T>*>::Iterator it = begin(); it != end(); ++it)
		{
			if ((*it)->size() == minSize)
			{
				(*it)->insert(elem);
				//return; =>> if we don't want to insert an element to all 
				//containers with the smallest size
			}
		}
	}
	bool searchPred(Condition<T> pred) const
	{
		for (LinkedList<Container<T>*>::Iterator it = begin(); it != end(); ++it)
		{
			if ((*it)->search(pred))
				return true;
		}
		return false;
	}
	unsigned size()const
	{
		return LinkedList<Container<T>*>::size();
	}
	void sort()
	{
		for (LinkedList<Container<T>*>::Iterator it = begin(); it != end(); ++it)
		{
			(*it)->sort();
		}
	}
	void print() const
	{
		std::cout << "Heterogeneous linked list with " << size() << " containers\n" << std::endl;
		std::cout <<std::setw(30)<< "Containters:\n" << std::endl;

		for (LinkedList<Container<T>*>::Iterator it = this->begin(); it != this->end(); ++it)
		{
			(*it)->print();
		}
	
	}
	void readFromFile(std::ifstream& readFile)
	{
		std::string label;
		int values;

		//reads size of Container
		readFile >> values;
		while (readFile >> label)
		{
			if (label == "Queue")
			{
				Container<T>* q = new NewQueue<T>;
				while (readFile.peek() != '\n' && readFile.peek() != EOF)
				{
					readFile >> values;
					q->insert(values);
				}
				push_back(q);
			}
			else if (label == "Stack")
			{
				Container<T>* st = new NewStack<T>;
				while (readFile.peek() != '\n' && readFile.peek() != EOF)
				{
					readFile >> values;
					st->insert(values);
				}
				push_back(st);
			}
			if (label == "DoublyLinkedList")
			{
				Container<T>* dll = new NewDoublyLinkedList<T>;
				while (readFile.peek() != '\n' &&  readFile.peek() != EOF)
				{
					readFile >> values;
					dll->insert(values);
				}
				push_back(dll);
			}
		}
	}
	void saveToFile(std::ofstream& writeFile)
	{
		writeFile << this->size() << '\n';
		for (LinkedList<Container<T>*>::Iterator it = begin(); it != end(); ++it)
		{
			std::vector<T> elems = (*it)->elems();
			writeFile << (*it)->label() << " ";
			for (int i = 0; i < elems.size(); ++i)
			{
				writeFile << elems[i] << " ";
			}
			writeFile << '\n';
		}
	}
	~ListContainer()
	{
		for (LinkedList<Container<T>*>::Iterator it = this->begin(); it != this->end(); ++it)
		{
			delete (*it);
		}
	}

};

template<class T>
class NewStack : public Stack<T>, public Container<T>
{
public:
	
	void insert(const T& elem)
	{
		Stack<T>::push(elem);
	}
	void addMin(const T& elem)
	{
		Stack<T>::push(elem);
	}
	void remove()
	{
		Stack<T>::pop();
	}
	void filter(Condition<T> cond)
	{
		Stack<T>::filter(cond);
	}
	bool member(const T& elem) const
	{
		return Stack<T>::member(elem);
	}
	bool search(Condition<T> pred) const
	{
		return Stack<T>::search(pred);
	}
	unsigned size() const
	{
		return Stack<T>::size();
	}
	std::string label() const
	{
		return Stack<T>::label();
	}
	void sort()
	{
		Stack<T>::sort();
	}
	void print() const
	{
		Stack<T> temp(*this);
		temp.print();
	}
	std::vector<T> elems() const
	{
		return Stack<T>::storeElems();
	}

};

template<class T>
class NewQueue : public Queue<T>, public Container<T>
{
public:
	
	void insert(const T& elem)
	{
		Queue<T>::push(elem);
	}
	void addMin(const T& elem)
	{
		Queue<T>::push(elem);
	}
	void remove()
	{
		Queue<T>::pop();
	}
	void filter(Condition<T> cond)
	{
		Queue<T>::filter(cond);
	}
	bool member(const T& elem) const
	{
		return Queue<T>::member(elem);
	}
	bool search(Condition<T> pred) const
	{
		return Queue<T>::search(pred);
	}
	std::string label() const
	{
		return Queue<T>::label();
	}
	unsigned size() const
	{
		return Queue<T>::size();
	}
	void sort()
	{
		Queue<T>::sort();
	}
	void print() const
	{
		Queue<T> qu(*this);
		qu.print();
	}
	std::vector<T> elems() const
	{
		return Queue<T>::storeElems();
	}

};

template<class T>
class NewDoublyLinkedList : public DoublyLinkedList<T>, public Container<T>
{
	void insert(const T& elem)
	{
		DoublyLinkedList<T>::push_back(elem);
	}
	void addMin(const T& elem)
	{
		DoublyLinkedList<T>::push_front(elem);
	}
	void remove()
	{
		DoublyLinkedList<T>::pop_front();
		//also can pop element with pop_back()
	}
	void filter(Condition<T> cond)
	{
		DoublyLinkedList<T>::filter(cond);
	}
	bool member(const T& elem) const
	{
		return DoublyLinkedList<T>::member(elem);
	}
	bool search(Condition<T> pred) const
	{
		return DoublyLinkedList<T>::search(pred);
	}
	std::string label() const
	{
		return DoublyLinkedList<T>::label();
	}
	unsigned size() const
	{
		return DoublyLinkedList<T>::size();
	}
	void sort()
	{
		DoublyLinkedList<T>::sort();
	}
	void print() const
	{
		DoublyLinkedList<T>::print();
	}
	std::vector<T> elems() const
	{
		return DoublyLinkedList<T>::storeElems();
	}

};

#endif // !CONTAINER_HPP