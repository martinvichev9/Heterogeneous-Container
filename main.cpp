#include <iostream>
#include <fstream>
#include "Stack.hpp"
#include "Queue.hpp"
#include "DoublyLinkedList.hpp"
#include "LinkedList.hpp"
#include "Container.hpp"
#include "Tests.hpp"


int main()
{
	std::ifstream file("resources/txt.txt");
	ListContainer<int> ls;
	ls.readFromFile(file);

	for (ListContainer<int>::Iterator it = ls.begin(); it != ls.end(); ++it)
	{
		(*it)->print();
	}

	std::ofstream out("resources/newContainer.txt");
	ls.saveToFile(out);
	
	tests();

	return 0;
}