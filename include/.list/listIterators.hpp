//
// Created by mscheman on 10/15/25.
//

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include ".helper/iterator.h"

template<class T, class Allocator>
class ft::list<T, Allocator>::iterator : public ft::iterator<bidirectional_iterator_tag, value_type> {
	public:
		// Constructor
		iterator(_node node = 0) : _currentNode(node) {};
		iterator(iterator CREF rhs) : _currentNode(0) { *this = rhs; };
		~iterator() {};

		// In/Equality Operator
		bool operator == (iterator CREF rhs) { return this->_currentNode == rhs._currentNode; }
		bool operator != (iterator CREF rhs) { return this->_currentNode != rhs._currentNode; }

		// Dereference Operator
		reference operator * () { return _currentNode->value; }
		pointer	operator  -> () { return &(operator*()); }

		// Shift Operators
		iterator REF operator ++ () { _currentNode = _currentNode->next; return *this; }
		iterator operator ++ (int) { iterator tmp = *this; _currentNode = _currentNode->next; return tmp; }
		iterator REF operator -- () { _currentNode = _currentNode->prev; return *this; }
		iterator operator -- (int) { iterator tmp = *this; _currentNode = _currentNode->prev; return tmp; }
		iterator REF operator + (size_t i) { while (i--) _currentNode = _currentNode->next; return *this; }
		iterator REF operator - (size_t i) { while (i--) _currentNode = _currentNode->prev; return *this; }

		// Attributes
		_node	_currentNode;
};

template<class T, class Allocator>
class ft::list<T, Allocator>::const_iterator : public ft::iterator<bidirectional_iterator_tag, const value_type> {
	public:
		// Constructor
		const_iterator(_node node = 0) : _currentNode(node) {};
		const_iterator(const_iterator CREF rhs) : _currentNode(rhs._currentNode) {};
		const_iterator(iterator CREF rhs) : _currentNode(rhs._currentNode) {}
		~const_iterator() {};

		// In/Equality Operator
		bool operator == (const_iterator CREF rhs) { return this->_currentNode == rhs._currentNode; }
		bool operator != (const_iterator CREF rhs) { return this->_currentNode != rhs._currentNode; }

		// Dereference Operator
		reference operator * () { return _currentNode->value; }
		pointer	operator  -> () { return &(operator*()); }

		// Shift Operators
		const_iterator REF operator ++ () { _currentNode = _currentNode->next; return *this; }
		const_iterator operator ++ (int) { const_iterator tmp = *this; _currentNode = _currentNode->next; return tmp; }
		const_iterator REF operator -- () { _currentNode = _currentNode->prev; return *this; }
		const_iterator operator -- (int) { const_iterator tmp = *this; _currentNode = _currentNode->prev; return tmp; }
		const_iterator REF operator + (size_t i) { while (i--) _currentNode = _currentNode->next; return *this; }
		const_iterator REF operator - (size_t i) { while (i--) _currentNode = _currentNode->prev; return *this; }

		// Attributes
		_node	_currentNode;
};

#endif //ITERATOR_HPP
