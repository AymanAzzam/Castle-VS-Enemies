#pragma once
#include "Node.h"
template<typename T>
class List {
protected:
	Node<T>* head;
	Node<T>* tail;
	Node<T>* ref;		// a reference to the current element
	int size;		// number of elements in the list;
	void reset();		// returns all data members to default values
	template <typename F>
	Node<T>** mSort(Node<T>** arr, int n, F fn);	// merge sort called by public member fn sort()
public:
	List();
	void push(const T& d);
	T& pop();
	int getSize() const;		// returns the size of the list
	void merge(List<T>& l2);		// merges 2 sorted lists, afterwards: the 1st list contains elements of both lists and the 2nd list is empty
	void append(List<T>& l2);		// appends the 2nd list at the end if the first, afterwards: the 1st list contains elements of both lists and the 2nd list is empty
	void sort(bool asc = true);		// sorts the list
	void begin();		// sets the ref to first element (head)
	bool end() const;		// checks whether the ref has reached the end of the list
	T& get();		// returns the current element pointed to by the ref
	void clear();		// removes all elements in the list
	void operator++();		// sets the ref to the next item
	void operator++(int);		// sets the ref to the next item
	~List();
};

template<typename T>
void List<T>::reset()
{
	ref = tail = head = nullptr;
	size = 0;
}

template<typename T>
List<T>::List()
{
	reset();
}

template<typename T>
void List<T>::push(const T & d)
{
	Node<T>* tmp = new Node<T>(d);
	if (!head) {
		tail = head = tmp;
		++size;
		begin();
		return;
	}
	tail->setNext(tmp);
	advance(tail);
	++size;
}

template<typename T>
T& List<T>::pop()
{
	if (!head || !ref) {
		T obj = T();
		return obj;
	}
	if (ref == head) {
		Node<T>* tmp = head;
		T data = tmp->getData();
		if (size == 1) {
			reset();
			delete tmp;
			return data;
		}
		advance(ref);
		advance(head);
		--size;
		delete tmp;
		return data;
	}
	if (ref == tail) {
		Node<T>* tmp = tail;
		T data = tmp->getData();
		Node<T>* ptr = head;
		while (ptr->getNext() != tail)
			advance(ptr);
		ptr->setNext(nullptr);
		ref = tail = ptr;
		--size;
		delete tmp;
		return data;
	}
	Node<T>* ptr = head;
	while (ptr->getNext() != ref)
		advance(ptr);
	ptr->setNext(ref->getNext());
	T data = ref->getData();
	delete ref;
	ref = ptr;
	--size;
	return data;
}

template<typename T>
int List<T>::getSize() const
{
	return size;
}

template<typename T>
void List<T>::merge(List<T>& l2)
{
	size += l2.size;
	if (!l2.head)
		return;
	if (!head) {
		head = l2.head;
		tail = l2.tail;
		l2.reset();
		return;
	}
	Node<T>* ptr1 = head;
	Node<T>* ptr2 = l2.head;
	if (cmp<T>::less((ptr1->getData()), (ptr2->getData())))
		advance(ptr1);
	else {
		head = ptr2;
		advance(ptr2);
	}
	Node<T>* newPtr = head;
	while (ptr1&&ptr2) {
		if (cmp<T>::less((ptr1->getData()), (ptr2->getData()))) {
			newPtr->setNext(ptr1);
			advance(ptr1);
		}
		else {
			newPtr->setNext(ptr2);
			advance(ptr2);
		}
		advance(newPtr);
	}
	if (ptr1)
		newPtr->setNext(ptr1);
	if (ptr2)
		newPtr->setNext(ptr2);
	l2.reset();
}

template<typename T>
void List<T>::append(List<T>& l2)
{
	if (!l2.head)
		return;
	if (!head) {
		head = l2.head;
		tail = l2.tail;
		begin();
		size = l2.size;
		l2.reset();
		return;
	}
	tail->setNext(l2.head);
	size += l2.size;
	l2.reset();
}

template<typename T>
void List<T>::sort(bool asc)
{
	if (!head)
		return;
	Node<T>** arr = new Node<T>*[size];
	Node<T>* ptr = head;
	int i = 0;
	while (ptr) {
		arr[i++] = ptr;
		advance(ptr);
	}
	if (asc)
		arr = mSort(arr, size, cmp<T>::less);
	else
		arr = mSort(arr, size, cmp<T>::more);
	head = arr[0];
	for (int i = 1; i < size; i++) {
		arr[i - 1]->setNext(arr[i]);
	}
	tail = arr[size - 1];
	arr[size - 1]->setNext(nullptr);
	begin();
	delete[] arr;
}

template<typename T>
template<typename F>
Node<T>** List<T>::mSort(Node<T>** arr, int n, F fn)
{
	if (n == 1)
		return arr;
	int m1 = n / 2;
	int m2 = n - m1;
	Node<T>** arr1 = mSort(arr, m1, fn);
	Node<T>** arr2 = mSort(arr + m1, m2, fn);
	Node<T>** ar = new Node<T>*[n];
	int i, j, k;
	i = j = k = 0;
	while (i < m1 && j < m2) {
		if (fn(arr1[i]->getData(), arr2[j]->getData()))
			ar[k++] = arr1[i++];
		else
			ar[k++] = arr2[j++];
	}
	while (i < m1)
		ar[k++] = arr1[i++];
	while (j < m2)
		ar[k++] = arr2[j++];
	for (int i = 0; i < n; i++)
		arr[i] = ar[i];
	delete[] ar;
	return arr;
}

template<typename T>
void List<T>::begin()
{
	ref = head;
}

template<typename T>
bool List<T>::end() const
{
	return !ref;
}

template<typename T>
T& List<T>::get()
{
	if (!head || !ref) {
		T obj = T();
		return obj;
	}
	return ref->getData();
}

template<typename T>
void List<T>::clear()
{
	Node<T>* ptr = head;
	while (ptr) {
		Node<T>* tmp = ptr;
		advance(ptr);
		delete tmp;
	}
	reset();
}

template<typename T>
void List<T>::operator++()
{
	advance(ref);
}

template<typename T>
void List<T>::operator++(int)
{
	advance(ref);
}

template<typename T>
List<T>::~List()
{
	clear();
}
