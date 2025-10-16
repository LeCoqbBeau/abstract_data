//
// Created by mscheman on 10/15/25.
//

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "../iterator.h"

template<class T, class Allocator>
class ft::list<T, Allocator>::iterator : public ft::iterator<bidirectional_iterator_tag, value_type> {
	public:
		// Constructor
		iterator(_node node = 0) : _currentNode(node) {};
		iterator(iterator CREF rhs) : _currentNode(rhs._currentNode) {};
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
		iterator REF operator + (int i) { while (--i) _currentNode = _currentNode->next; return *this; }
		iterator REF operator - (int i) { while (--i) _currentNode = _currentNode->prev; return *this; }

		// Attributes
		_node	_currentNode;
};

#endif //ITERATOR_HPP
