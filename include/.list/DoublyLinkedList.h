//
// Created by mscheman on 9/8/25.
//

#ifndef DOUBLYLINKEDLIST_H
# define DOUBLYLINKEDLIST_H

#include ".helper/utils.h"

TEMPLATE_T struct DoublyLinkedList {
	// Constructors
	explicit DoublyLinkedList(T CREF value = T())
		: value(value), next(NULL), prev(NULL) {};
	DoublyLinkedList(DoublyLinkedList CREF src)
		: value(src.value), next(src.next), prev(src.prev) {};

	// Attributes
	T					value;
	DoublyLinkedList	*next;
	DoublyLinkedList	*prev;
};

#endif //DOUBLYLINKEDLIST_H
