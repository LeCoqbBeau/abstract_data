//
// Created by mscheman on 10/15/25.
//

#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

#include ".helper/iterator.h"

template<class T, class Allocator>
class ft::list<T, Allocator>::const_iterator : public ft::iterator<bidirectional_iterator_tag, value_type> {
	public:
		// Shadowing ft::iterator::reference because I need it :3
		typedef value_type CREF	reference;
		typedef value_type*		pointer;

		// Constructor
		const_iterator(_node node = 0) : _currentNode(node) {};
		const_iterator(const_iterator CREF rhs) : _currentNode(rhs._currentNode) {};
		const_iterator(iterator CREF rhs) : _currentNode(rhs._currentNode) {}
		~const_iterator() {};

		// In/Equality Operator
		bool operator == (const_iterator CREF rhs) const { return this->_currentNode == rhs._currentNode; }
		bool operator != (const_iterator CREF rhs) const { return this->_currentNode != rhs._currentNode; }

		// Dereference Operator
		const_reference operator  * () { return _currentNode->value; }
		const_pointer	operator -> () { return &(operator*()); }

		// Shift Operators
		const_iterator REF operator ++ () { _currentNode = _currentNode->next; return *this; }
		const_iterator operator ++ (int) { const_iterator tmp = *this; _currentNode = _currentNode->next; return tmp; }
		const_iterator REF operator -- () { _currentNode = _currentNode->prev; return *this; }
		const_iterator operator -- (int) { const_iterator tmp = *this; _currentNode = _currentNode->prev; return tmp; }

		// Attributes
		_node	_currentNode;
};

template<class T, class Allocator>
class ft::list<T, Allocator>::iterator : public const_iterator {
	public:
		// Constructor
		iterator(_node node = 0) : const_iterator(node) {}
		iterator(iterator CREF rhs) : const_iterator(0) { *this = rhs; }
		~iterator() {}

		// Dereference Operator
		reference operator * () { return this->_currentNode->value; }
		pointer	operator  -> () { return &(operator*()); }

		// Shift Operators
		iterator REF operator ++ () { this->_currentNode = this->_currentNode->next; return *this; }
		iterator operator ++ (int) { iterator tmp = *this; this->_currentNode = this->_currentNode->next; return tmp; }
		iterator REF operator -- () { this->_currentNode = this->_currentNode->prev; return *this; }
		iterator operator -- (int) { iterator tmp = *this; this->_currentNode = this->_currentNode->prev; return tmp; }
};

#endif //LIST_ITERATOR_HPP
