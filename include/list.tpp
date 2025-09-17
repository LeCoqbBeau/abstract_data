
#ifndef LIST_TPP
# define LIST_TPP

#include "ftexcept.h"

template <class T, class Allocator>
ft::list<T, Allocator>::list(allocator_type CREF alloc)
	: _frontData(0), _backData(0), _allocator(alloc), _size(0)
{}

template <class T, class Allocator>
ft::list<T, Allocator>::list(size_type n, value_type CREF val, allocator_type CREF alloc)
	: _frontData(0), _backData(0), _allocator(alloc), _size(0)
{
	_assignHelper(n, val);
}

template <class T, class Allocator>
ft::list<T, Allocator>::list(list CREF x) {
	*this = x;
}

template <class T, class Allocator>
ft::list<T, Allocator> REF ft::list<T, Allocator>::operator = (list CREF x) {
	if (this != &x) {
		this->_clearHelper();
		this->_frontData = x._frontData->duplicate();
		if (!this->_frontData)
			throw ft::bad_alloc();
		this->_backData = x._backData;
		this->_allocator = x._allocator;
		this->_size = x._size;
	}
	return *this;
}
template <class T, class Allocator>
ft::list<T, Allocator>::~list() {
	_clearHelper();
}

// Observers
template <class T, class Allocator>
typename ft::list<T, Allocator>::allocator_type ft::list<T, Allocator>::get_allocator() const {
	return _allocator;
}

// Capacity
template <class T, class Allocator>
bool ft::list<T, Allocator>::empty() const {
	return (!_frontData && !_backData);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::size_type ft::list<T, Allocator>::size() const {
	return this->_size;
}

// Element Access
template <class T, class Allocator>
typename ft::list<T, Allocator>::reference ft::list<T, Allocator>::front() {
	return *_frontData->front()->value;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reference ft::list<T, Allocator>::front() const {
	return *_frontData->front()->value;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::reference ft::list<T, Allocator>::back() {
	return *_backData->front()->value;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reference ft::list<T, Allocator>::back() const {
	return *_backData->front()->value;
}

// Modifiers
template <class T, class Allocator>
void ft::list<T, Allocator>::assign(size_type count, value_type CREF value) {
	_clearHelper();
	_assignHelper(count, value);
}

template <class T, class Allocator>
void ft::list<T, Allocator>::push_front(value_type CREF val) {
}

// Private Helper Methods
template <class T, class Allocator>
void ft::list<T, Allocator>::_assignHelper(size_type n, value_type CREF val) {
	_node	nodeIterator;
	pointer	nodeValue;

	if (!n)
		return;
	_size = n;
	nodeValue = NULL;
	nodeIterator = NULL;
	nodeValue = _allocator.allocate(1);
	_allocator.construct(nodeValue, val);
	_frontData = new DoublyLinkedList<pointer>;
	_frontData->value = nodeValue;
	nodeIterator = _frontData;
	while (--n) {
		nodeValue = NULL;
		nodeValue = _allocator.allocate(1);
		_allocator.construct(nodeValue, val);
		nodeIterator->reserveBack(1, nodeValue);
		nodeIterator = nodeIterator->next;
	}
	_backData = _frontData->back();
}

template <class T, class Allocator>
void ft::list<T, Allocator>::_clearHelper() {
	_node	nodeIterator = _frontData;
	_node	nextNode = NULL;
	int i = 0;

	while (nodeIterator) {
		nextNode = nodeIterator->next;
		_allocator.deallocate(nodeIterator->value, 1);
		delete nodeIterator;
		nodeIterator = nextNode;
		++i;
	}
}

#endif