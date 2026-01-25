
#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include ".helper/algorithm.hpp"
#include "ftdef.hpp"

#define RBT_LEFT	0
#define RBT_RIGHT	1
#define RBT_BLACK	0
#define RBT_RED		1


namespace ft { namespace internal {


struct rbt_node_base {
	// Typedefs
	typedef rbt_node_base	this_type;
	typedef char			color_type;
	typedef	bool			side_type;

	// Constructor
	rbt_node_base(this_type* parent = NULL, color_type color = RBT_RED)
		: parent(parent), color(color) { ft::fill_n(next, 2, reinterpret_cast<this_type*>(NULL)); }
	virtual ~rbt_node_base() {}

	// Methods
	this_type*	rotate(side_type side);
	this_type*	min();
	this_type*	max();
	this_type*	nextNode(); // this is used for iterators purpose
	this_type*	prevNode(); // this is used for iterators purpose

	// Attributes
	this_type*	next[2];
	this_type*	parent;
	color_type	color;
};


template <typename T>
struct rbt_node : rbt_node_base {
	public:
		// Typedefs
		typedef rbt_node<T>		this_type;
		typedef rbt_node_base	base_type;
		typedef	T				value_type;

		// Constructor
		rbt_node(value_type CREF val = value_type(), base_type* parent = NULL)
			: rbt_node_base(parent, RBT_RED), value(val) {}

		// Methods
		this_type*	insert(this_type* node);
		this_type*	remove(this_type* node);
		this_type*	find(value_type CREF val);

		// Attributes
		value_type	value;

	protected:
		void	_insertFixup();
		void	_removeFixup();	
};


template <typename T, typename Allocator = allocator<T> >
struct rb_tree {
public:

protected:

};


} // namespace internal
} // namespace ft


//
//	rbt_node_base
//


inline
ft::internal::rbt_node_base::this_type*
ft::internal::rbt_node_base::min()
{
	this_type*	ret = this;
	while (ret->next[RBT_LEFT])
		ret = ret->next[RBT_LEFT];
	return ret;
}


inline
ft::internal::rbt_node_base::this_type*
ft::internal::rbt_node_base::max()
{
	this_type*	ret = this;
	while (ret->next[RBT_RIGHT])
		ret = ret->next[RBT_RIGHT];
	return ret;
}



inline
ft::internal::rbt_node_base::this_type*
ft::internal::rbt_node_base::rotate(side_type side)
{
	this_type	*child = next[!side];
	if (!child)
		return	this;
	this->next[!side] = child->next[side];
	if (child->next[side])
		child->next[side]->parent = this;
	child->parent = this->parent;
	if (!this->parent)
		;
	else if (this->parent == this->parent->next[side])
		this->parent->next[side] = child;
	else
		this->parent->next[!side] = child;
	child->next[side] = this;
	this->parent = child;
	return child;
}


inline
ft::internal::rbt_node_base::this_type*
ft::internal::rbt_node_base::nextNode()
{
	this_type*	nextNode = this;
	if (nextNode->next[RBT_RIGHT]) {
		nextNode = nextNode->next[RBT_RIGHT];
		while (nextNode->next[RBT_LEFT])
			nextNode = nextNode->next[RBT_LEFT];
		return nextNode;
	}
	this_type*	parent = nextNode->parent;
	while (parent && parent->next[RBT_RIGHT] == nextNode) {
		nextNode = parent;
		parent = parent->parent;
	}
	return parent;
}


inline
ft::internal::rbt_node_base::this_type*
ft::internal::rbt_node_base::prevNode()
{
	this_type*	nextNode = this;
	if (nextNode->next[RBT_LEFT]) {
		nextNode = nextNode->next[RBT_LEFT];
		while (nextNode->next[RBT_RIGHT])
			nextNode = nextNode->next[RBT_RIGHT];
		return nextNode;
	}
	this_type*	parent = nextNode->parent;
	while (parent && parent->next[RBT_LEFT] == nextNode) {
		nextNode = parent;
		parent = parent->parent;
	}
	return parent;
}


//
//	rbt_node<T>
//


#define NODE(base) (dynamic_cast<ft::internal::rbt_node<T>*>(base))		// baseToNode
#define BASE(node) (dynamic_cast<ft::internal::rbt_node_base*>(node))	// nodeToBase


template <typename T>
typename ft::internal::rbt_node<T>::this_type*
ft::internal::rbt_node<T>::insert(this_type* node)
{
	side_type	insertSide = (node->value < this->value) ? RBT_LEFT : RBT_RIGHT;
	if (this->next[insertSide])
		return NODE(this->next[insertSide])->insert(node);
	this->next[insertSide] = node;
	node->color = RBT_RED;
	node->parent = this;
	ft::fill_n(node->next, 2, (base_type*)NULL);
	node->_insertFixup();
	return node;
}


#undef NODE
#undef BASE

#endif // BINARY_TREE_HPP
