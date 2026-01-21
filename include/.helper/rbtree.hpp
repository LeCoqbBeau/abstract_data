//
// Created by mscheman on 1/21/26.
//

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "algorithm.hpp"
#include "ftdef.hpp"
#include "iterator.hpp"


namespace ft { namespace internal {


# define RBT_BLACK 0
# define RBT_RED 1
# define LEFT 0
# define RIGHT 1
template <typename T>
struct rbtree_node;


template <typename T, typename Ptr, typename Ref>
struct _rbtreeIterator
	: ft::iterator<ft::bidirectional_iterator_tag, T, Ref, Ptr>
{
	// Typedefs
	typedef	_rbtreeIterator<T, Ptr, Ref>								this_type;
	typedef _rbtreeIterator<T, T*, T REF>								iterator;
	typedef rbtree_node<T>*												node_type;
	typedef ft::iterator<ft::bidirectional_iterator_tag, T, Ref, Ptr>	iterator_tags;
	typedef typename iterator_tags::value_type							value_type;
	typedef typename iterator_tags::difference_type						difference_type;
	typedef typename iterator_tags::pointer								pointer;
	typedef typename iterator_tags::reference							reference;

	// Constructor
	explicit	_rbtreeIterator(node_type node) : _m_curr(node) {}
				_rbtreeIterator(iterator CREF it) : _m_curr(it._m_curr) {}
				~_rbtreeIterator() {}

	// In/Equality Operator
	template <class U, class URef, class UPtr>
	bool operator	== (_rbtreeIterator<U, URef, UPtr> CREF rhs) { return this->_m_curr == rhs._m_curr; }
	template <class U, class URef, class UPtr>
	bool operator	!= (_rbtreeIterator<U, URef, UPtr> CREF rhs) { return this->_m_curr != rhs._m_curr; }

	// Dereference Operators
	reference	operator * () { return _m_curr->value; }
	pointer		operator ->() { return &_m_curr->value; }

	// Shift Operators
	this_type REF	operator ++ () { _increment(); return *this; }
	this_type		operator ++ (int) { this_type tmp = *this; operator++(); return tmp; }
	this_type REF	operator -- () { _decrement(); return *this; }
	this_type		operator -- (int) { this_type tmp = *this; operator--(); return tmp; }

	// Helper function
	void _increment();
	void _decrement();

	// Attributes
	node_type	_m_curr;
};



template <typename T>
struct rbtree_node
{
	// Typedefs
	typedef rbtree_node		this_type;
	typedef T				value_type;
	typedef unsigned char	color_type;

	// Constructor
	rbtree_node(value_type CREF value, this_type *parent = NULL)
		: parent(parent), value(value), color(RBT_RED)  { ft::fill(next, next + 2, static_cast<this_type*>(0)); }

	// Methods
	this_type	*rotate(bool rotateRight);
	this_type	*insert(value_type CREF val = value_type());

	// Attributes
	this_type	*next[2];
	this_type	*parent;
	value_type	value;
	color_type	color;
};


} // namespace impl
} // namespace ft


template <typename T, typename Ptr, typename Ref>
void
ft::internal::_rbtreeIterator<T, Ptr, Ref>::_increment()
{
	if (!_m_curr->parent) // this means we're at the end
		return ;
	if (_m_curr->next[LEFT])
		_m_curr = _m_curr->next[LEFT];
	else if (_m_curr->next[RIGHT])
		_m_curr = _m_curr->next[RIGHT];
	else if (_m_curr->parent->next[RIGHT])

}



template <typename T>
typename ft::internal::rbtree_node<T>::this_type*
ft::internal::rbtree_node<T>::rotate(bool rotateRight)
{
	this_type	*child = next[!rotateRight];
	if (!child)
		return this;
	this->next[!rotateRight] = child->next[rotateRight];
	if (child->next[rotateRight])
		child->next[rotateRight]->parent = this;
	child->parent = this->parent;
	if (!this->parent)
		;
	else if (this->parent == this->parent->next[rotateRight])
		this->parent->next[rotateRight] = child;
	else
		this->parent->next[!rotateRight] = child;
	child->next[rotateRight] = this;
	this->parent = child;
	return child;
}


template <typename T>
typename ft::internal::rbtree_node<T>::this_type*
ft::internal::rbtree_node<T>::insert(value_type CREF val)
{
	(void)val;
	return *this;
}


#endif //RBTREE_HPP
