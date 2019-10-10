#pragma once
#include "Node.h"

template <typename T>
class Queue {
	Node<T>* front;
	Node<T>* rear;
public:
	Queue();
	Queue(Queue<T>& q);
	void push(const T& data);
	T pop();
	bool empty() const;
	T peek() const;		// peeks at the front element
	void clear();		// removes all elements in the list
	~Queue();
};

template<typename T>
Queue<T>::Queue()
{
	rear = front = nullptr;
}

template<typename T>
Queue<T>::Queue(Queue<T>& q)
{
	rear = front = nullptr;
	Node<T>* ptr = q.front;
	while (ptr) {
		push(ptr->getData());
		advance(ptr);
	}
}

template<typename T>
void Queue<T>::push(const T & data)
{
	Node<T>* tmp = new Node<T>(data);
	if (!front)
		front = tmp;
	else
		rear->setNext(tmp);
	rear = tmp;
}

template<typename T>
T Queue<T>::pop()
{
	if (!front)
		return T();
	Node<T>* tmp = front;
	T data = tmp->getData();
	advance(front);
	delete tmp;
	return data;
}

template<typename T>
bool Queue<T>::empty() const
{
	return !front;
}

template<typename T>
T Queue<T>::peek() const
{
	if (!front)
		return T();
	T data = front->getData();
	return data;
}

template<typename T>
void Queue<T>::clear()
{
	Node<T>* ptr = front;
	while (ptr) {
		Node<T>* tmp = ptr;
		advance(ptr);
		delete tmp;
	}
	rear = front = nullptr;
}

template<typename T>
Queue<T>::~Queue()
{
	clear();
}
