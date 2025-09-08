//
// Created by mscheman on 9/8/25.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "utils.h"

TEMPLATE_T struct DoublyLinkedList {
	// Constructor
	explicit DoublyLinkedList(T CREF value = T());
	DoublyLinkedList(DoublyLinkedList CREF src);
	DoublyLinkedList REF operator = (DoublyLinkedList CREF rhs);

	// Methods
	size_t				size() const;
	DoublyLinkedList*	last();
	DoublyLinkedList*	first();
	void				addFront(DoublyLinkedList *node);
	void				addBack(DoublyLinkedList *node);

	// Attributes
	T					value;
	DoublyLinkedList	*next;
	DoublyLinkedList	*prev;
};

// Constructors
TEMPLATE_T DoublyLinkedList<T>::DoublyLinkedList(T CREF value) {
	next = 0;
	prev = 0;
}

TEMPLATE_T DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList CREF src) {
	*this = src;
}

TEMPLATE_T DoublyLinkedList<T> REF DoublyLinkedList<T>::operator = (DoublyLinkedList CREF rhs) {
	if (this == &rhs) {
		value = rhs.value;
		next = rhs.next;
		prev = rhs.prev;
	}
	return (*this);
}

// Methods
TEMPLATE_T size_t DoublyLinkedList<T>::size() const {
	if (next)
		return 1 + next->size();
	return 1;
}

TEMPLATE_T DoublyLinkedList<T>* DoublyLinkedList<T>::last() {
	if (next)
		return next->last();
	return this;
}

TEMPLATE_T DoublyLinkedList<T>* DoublyLinkedList<T>::first() {
	if (prev)
		return prev->last();
	return this;
}

TEMPLATE_T void DoublyLinkedList<T>::addFront(DoublyLinkedList *node) {
	if (prev)
		return prev.addFront(node);
	prev = node;
	node->next = this;
}

TEMPLATE_T void DoublyLinkedList<T>::addBack(DoublyLinkedList *node) {
	if (next)
		return next->addBack(node);
	next = node;
	node->prev = this;
}

#endif //DOUBLYLINKEDLIST_H
