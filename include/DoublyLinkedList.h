//
// Created by mscheman on 9/8/25.
//

#ifndef DOUBLYLINKEDLIST_H
# define DOUBLYLINKEDLIST_H

# include "utils.h"

TEMPLATE_T struct DoublyLinkedList {
	// Constructor
	explicit DoublyLinkedList(T CREF value = T());
	DoublyLinkedList(DoublyLinkedList CREF src);
	DoublyLinkedList REF operator = (DoublyLinkedList CREF rhs);

	// Typedefs
	typedef T			value_type;
	typedef T REF		reference;
	typedef T CREF		const_reference;
	typedef	size_t		size_type;

	// Methods
	size_t				size() const throw();
	DoublyLinkedList*	front() throw();
	DoublyLinkedList*	back() throw();
	void				addFront(DoublyLinkedList *node) throw();
	void				addBack(DoublyLinkedList *node) throw();
	void				insertFront(DoublyLinkedList *node) throw();
	void				insertBack(DoublyLinkedList *node) throw();
	void				delFront() throw();
	void				delBack() throw();
	DoublyLinkedList*	clone() const throw();
	DoublyLinkedList*	duplicate() const throw();
	void				clear() const throw();
	void				rclear() const throw();
	void				reserveFront(size_type n, const_reference val = value_type());
	void				reserveBack(size_type n, const_reference val = value_type());
	void				toNext() throw();
	void				toPrev() throw();

	// Attributes
	T					value;
	DoublyLinkedList	*next;
	DoublyLinkedList	*prev;
};

// Constructors
TEMPLATE_T DoublyLinkedList<T>::DoublyLinkedList(T CREF value) {
	this->value = value;
	next = NULL;
	prev = NULL;
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
TEMPLATE_T size_t DoublyLinkedList<T>::size() const throw() {
	if (next)
		return 1 + next->size();
	return 1;
}

TEMPLATE_T DoublyLinkedList<T>* DoublyLinkedList<T>::front() throw() {
	if (prev)
		return prev->front();
	return this;
}

TEMPLATE_T DoublyLinkedList<T>* DoublyLinkedList<T>::back() throw() {
	if (next)
		return next->back();
	return this;
}

TEMPLATE_T void DoublyLinkedList<T>::addFront(DoublyLinkedList *node) throw() {
	if (prev)
		return prev->addFront(node);
	this->prev = node;
	node->next = this;
}

TEMPLATE_T void DoublyLinkedList<T>::addBack(DoublyLinkedList *node) throw() {
	if (next)
		return next->addBack(node);
	this->next = node;
	node->prev = this;
}


TEMPLATE_T void DoublyLinkedList<T>::insertFront(DoublyLinkedList *node) throw() {
	DoublyLinkedList *tmp;

	if (!this->prev)
		return addFront(node);
	tmp = this->prev;
	this->prev = node;
	node->prev = tmp;
	node->next = this;
	tmp->next = node;
}

TEMPLATE_T void DoublyLinkedList<T>::insertBack(DoublyLinkedList* node) throw() {
	DoublyLinkedList *tmp;

	if (!this->next)
		return addBack(node);
	tmp = this->next;
	this->next = node;
	node->next = tmp;
	node->prev = this;
	tmp->prev = node;
}

TEMPLATE_T void DoublyLinkedList<T>::delFront() throw() {
	DoublyLinkedList const* front = prev;

	if (!prev)
		return;
	this->prev = this->prev->prev;
	delete front;
}

TEMPLATE_T void DoublyLinkedList<T>::delBack() throw() {
	DoublyLinkedList const* back = next;

	if (!next)
		return;
	this->next = this->next->next;
	delete back;
}

TEMPLATE_T
DoublyLinkedList<T>* DoublyLinkedList<T>::clone() const throw() {
	DoublyLinkedList *cloned = NULL;

	try {
		cloned = new DoublyLinkedList(*this);
	} catch (...) {}
	return cloned;
}

TEMPLATE_T DoublyLinkedList<T>* DoublyLinkedList<T>::duplicate() const throw() {
	DoublyLinkedList const* it		= this;
	DoublyLinkedList *newNode	= NULL;
	DoublyLinkedList *newPrev	= NULL;

	while (it) {
		newNode = it->clone();
		if (!newNode) {
			if (newPrev) newPrev->rclear();
			return NULL;
		}
		if (newPrev)
			newPrev->next = newNode;
		newNode->prev = newPrev;
		newNode->next = NULL;
		newPrev = newNode;
		it = it->next;
	}
	return newNode->front();
}

TEMPLATE_T void DoublyLinkedList<T>::clear() const throw() {
	if (this->next)
		this->next->clear();
	delete this;
}

TEMPLATE_T void DoublyLinkedList<T>::rclear() const throw() {
	if (this->prev)
		this->prev->clear();
	delete this;
}

TEMPLATE_T void DoublyLinkedList<T>::reserveFront(size_type n, const_reference val) {
	while (n--)
		addFront(new DoublyLinkedList(val));
}

TEMPLATE_T void DoublyLinkedList<T>::reserveBack(size_type n, const_reference val) {
	while (n--)
		addBack(new DoublyLinkedList(val));
}

#endif //DOUBLYLINKEDLIST_H
