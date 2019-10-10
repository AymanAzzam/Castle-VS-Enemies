#pragma once

template<typename T>
class Node {
protected:
	T data;
	Node<T>* next;
public:
	Node();
	Node(const T& d, Node<T>* p = nullptr);
	void setData(const T& d);
	void setNext(Node<T>* p = nullptr);
	T& getData();
	Node<T>* getNext() const;
};

template<typename T>
Node<T>::Node()
{
	next = nullptr;
}

template<typename T>
Node<T>::Node(const T& d, Node<T>* p)
{
	setNext(p);
	setData(d);
}

template<typename T>
void Node<T>::setData(const T& d)
{
	data = d;
}

template<typename T>
void Node<T>::setNext(Node<T>* p)
{
	next = p;
}

template<typename T>
T& Node<T>::getData()
{
	return data;
}

template<typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

template<typename T>
Node<T>*& advance(Node<T>*& p) {
	if (p)
		p = p->getNext();
	return p;
}

////////////////////////////////////////////////

template<typename T>
class cmp {
public:
	static bool less(const T& b1, const T& b2) {
		return b1 < b2;
	}
	static bool more(const T& b1, const T& b2) {
		return b1 > b2;
	}
};

template<typename T>
class cmp<T*> {
public:
	static bool less(const T* b1, const T* b2) {
		return cmp<T>::less(*b1, *b2);
	}
	static bool more(const T* b1, const T* b2) {
		return cmp<T>::more(*b1, *b2);
	}
};
