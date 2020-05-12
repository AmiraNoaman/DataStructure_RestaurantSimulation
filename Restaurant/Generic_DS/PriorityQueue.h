#pragma once
#include "NodePriority.h"

template <typename T>
class PriorityQueue
{
	NodePriority<T>* backPtr;
	NodePriority<T>* frontPtr;
public:
	int count;
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, double P);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	~PriorityQueue();
};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

template <typename T>
bool PriorityQueue<T>::enqueue(const T & newEntry, double P)
{
	NodePriority<T>* newNodePtr = new NodePriority<T>(newEntry, P);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else if (P > frontPtr->getpriority())
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else
	{
		NodePriority <T>* current = frontPtr;
		while (current->getNext() && current->getNext()->getpriority() >= P)
			current = current->getNext();
		newNodePtr->setNext(current->getNext());
		current->setNext(newNodePtr);
	}
	count++;
	return true;
}

template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	NodePriority<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;
}

template <typename T>
bool PriorityQueue<T>::peekFront(T& frntEntry)  const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{}