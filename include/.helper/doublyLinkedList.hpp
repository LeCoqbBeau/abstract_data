//
// Created by mscheman on 2/9/26.
//

#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "ftdef.hpp"
#include "iterator.hpp"


namespace ft { namespace internal {


struct _doublyLinkedListBase {
	// Typedefs
	typedef _doublyLinkedListBase	this_type;

	// Constructor
	explicit _doublyLinkedListBase()
		: mNext(NULL), mPrev(NULL) {}
	_doublyLinkedListBase(this_type CREF rhs)
		: mNext(rhs.mNext), mPrev(rhs.mPrev) {}
	virtual ~_doublyLinkedListBase() {}

	// Accessors
	virtual this_type* REF	next() { return mNext; }
	virtual this_type* CREF	next() const { return mNext; }
	virtual this_type* REF	prev() { return mPrev; }
	virtual this_type* CREF	prev() const { return mPrev; }

	// Attributes
	this_type*	mNext;
	this_type*	mPrev;
};


template <typename T>
struct _doublyLinkedList : _doublyLinkedListBase {
	// Typedefs
	typedef _doublyLinkedList<T>	this_type;
	typedef _doublyLinkedListBase	base_type;

	// Constructors
	explicit _doublyLinkedList(T CREF value)
		: value(value) {};
	_doublyLinkedList(_doublyLinkedList CREF rhs)
		: base_type(rhs), value(rhs.value) {};
	virtual ~_doublyLinkedList() {}

	// Attributes
	T					value;
};
# define FT_DLLNODE(node) dynamic_cast<ft::internal::_doublyLinkedList<T>* >(node)


template <class T, class Ref, class Ptr>
struct _doublyLinkedListIterator
	: public ft::iterator<ft::bidirectional_iterator_tag, T, ft::ptrdiff_t, Ref, Ptr>
{
	// Typedef
	typedef _doublyLinkedListIterator<T, Ref, Ptr>	this_type;
	typedef T										value_type;
	typedef Ref										reference;
	typedef Ptr										pointer;
	typedef ft::ptrdiff_t							difference_type;
	typedef _doublyLinkedListBase					node_type;

	// Constructor
	explicit	_doublyLinkedListIterator(node_type const* node = 0): _currentNode(const_cast<node_type*>(node)) {};
				_doublyLinkedListIterator(_doublyLinkedListIterator<T, T REF, T*> CREF rhs) : _currentNode(rhs._currentNode) {};
				~_doublyLinkedListIterator() {};

	// In/Equality Operator
	template <class U, class URef, class UPtr>
	bool operator	== (_doublyLinkedListIterator<U, URef, UPtr> CREF rhs) { return this->_currentNode == rhs._currentNode; }
	template <class U, class URef, class UPtr>
	bool operator	!= (_doublyLinkedListIterator<U, URef, UPtr> CREF rhs) { return this->_currentNode != rhs._currentNode; }

	// Dereference Operator
	reference	operator  * () { return FT_DLLNODE(_currentNode)->value; }
	pointer		operator -> () { return &(operator*()); }

	// Shift Operators
	this_type REF	operator ++ () { _currentNode = _currentNode->next(); return *this; }
	this_type		operator ++ (int) { this_type tmp = *this; operator++(); return tmp; }
	this_type REF	operator -- () { _currentNode = _currentNode->prev(); return *this; }
	this_type		operator -- (int) { this_type tmp = *this; operator--(); return tmp; }

	// Attributes
	node_type	*_currentNode;
};


} // internal
} // ft


#endif //DOUBLYLINKEDLIST_HPP
