# Heterogeneous-Container

A C++ console application which implements a **heterogeneous container**, whose elements
can be a **stack, doubly linked list or queue**. A **linked list** is used to present the container. 

Features of the heterogeneous container:
-  Reading and parsing information from a file and then storing it in an appropriate container
(creating new containers and storing them in the heteroeneous one);
-  Adding or removing elements;
-  Checking if an element is present in some container of heterogeneous container;
-  Adding an element to the container with the smallest size;
-  Checking if container contains a specific element, which is defined by **using Condition = bool (*)(T const&)**;
-  Filtering the container - again is used **Condition**;
-  Sorting all subcontainers;
-  Iterating the container using iterators;
-  Serialization;
-  Printing some information about all consisting subcontainers;
