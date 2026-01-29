//
// Created by mscheman on 1/26/26.
//

#ifndef BINARY_TREES_TPP
#define BINARY_TREES_TPP


#include "ftexcept.hpp"
#include "new.hpp"


//
//	rbt_node_base
//


inline
ft::internal::rbt_node_base::this_type* REF
ft::internal::rbt_node_base::left()
{
	return next[RBT_LEFT];
}


inline
ft::internal::rbt_node_base::this_type* CREF
ft::internal::rbt_node_base::left() const
{
	return next[RBT_LEFT];
}


inline
ft::internal::rbt_node_base::this_type* REF
ft::internal::rbt_node_base::right()
{
	return next[RBT_RIGHT];
}


inline
ft::internal::rbt_node_base::this_type* CREF
ft::internal::rbt_node_base::right() const
{
	return next[RBT_RIGHT];
}


inline
ft::internal::rbt_node_base::this_type*
ft::internal::rbt_node_base::min()
{
	this_type*	ret = this;
	while (ret->left())
		ret = ret->left();
	return ret;
}


inline
ft::internal::rbt_node_base::this_type*
ft::internal::rbt_node_base::max()
{
	this_type*	ret = this;
	while (ret->right())
		ret = ret->right();
	return ret;
}


inline
ft::internal::rbt_node_base::this_type*
ft::internal::rbt_node_base::rotate(side_type side)
{
	this_type	*child = next[!side];
	if (!child)
		return this;
	this->next[!side] = child->next[side];
	if (child->next[side])
		child->next[side]->parent = this;
	child->parent = this->parent;
	if (!this->parent)
		;
	else if (this == this->parent->next[RBT_LEFT])
		this->parent->next[RBT_LEFT] = child;
	else
		this->parent->next[RBT_RIGHT] = child;
	child->next[side] = this;
	this->parent = child;
	return child;
}


inline
ft::internal::rbt_node_base::this_type*
ft::internal::rbt_node_base::nextNode()
{
	this_type*	nextNode = this;
	if (nextNode->right()) {
		nextNode = nextNode->right();
		while (nextNode->left())
			nextNode = nextNode->left();
		return nextNode;
	}
	this_type*	parent = nextNode->parent;
	while (parent && parent->right() == nextNode) {
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
	if (nextNode->left()) {
		nextNode = nextNode->left();
		while (nextNode->right())
			nextNode = nextNode->right();
		return nextNode;
	}
	this_type*	parent = nextNode->parent;
	while (parent && parent->left() == nextNode) {
		nextNode = parent;
		parent = parent->parent;
	}
	return parent;
}


inline
void
ft::internal::rbt_node_base::transplant(this_type* other)
{
	if (!this->parent)
		;
	else if (this == this->parent->left())
		this->parent->left() = other;
	else
		this->parent->right() = other;
	if (other)
		other->parent = this->parent;
}


//
//	rbt_node<T, Comp>
//


#define NODE(base) (static_cast<ft::internal::rbt_node<T, Comp>*>(base))	// baseToNode
#define BASE(node) (static_cast<ft::internal::rbt_node_base*>(node))		// nodeToBase


template <typename T, typename Comp>
typename ft::internal::rbt_node<T, Comp>::this_type*
ft::internal::rbt_node<T, Comp>::find(value_type CREF val)
{
	bool const isSmaller = comp(val, this->value);
	bool const isBigger = comp(this->value, val);
	if (!isSmaller && !isBigger)
		return this;
	side_type searchSide = (isSmaller) ? RBT_LEFT : RBT_RIGHT;
	if (next[searchSide])
		return NODE(next[searchSide])->find(val);
	return NULL;
}


template <typename T, typename Comp>
typename ft::internal::rbt_node<T, Comp>::this_type*
ft::internal::rbt_node<T, Comp>::insert(this_type* node)
{
	// node < this
	side_type insertSide = (comp(node->value, this->value)) ? RBT_LEFT : RBT_RIGHT;
	if (this->next[insertSide])
		return NODE(this->next[insertSide])->insert(node);
	this->next[insertSide] = node;
	node->color = RBT_RED;
	node->parent = this;
	ft::fill_n(node->next, 2, static_cast<base_type*>(NULL));
	return node;
}


template <typename T, typename Comp>
template <typename Allocator, typename FreeFunc>
typename ft::internal::rbt_node<T, Comp>::remove_result
ft::internal::rbt_node<T, Comp>::remove(Allocator allocator, FreeFunc free)
{
	remove_result	result;

	if (!left() && !right())
		result = noChildRemove(this);
	else if (left() && right())
		result = twoChildrenRemove(this);
	else // if (left() || right())
		result = oneChildRemove(this);
	free(allocator, this);
	return result;
}


//
//	rb_tree<T, Comp, Allocator>
//


template <typename T, typename Comp, typename Allocator>
ft::internal::rb_tree<T, Comp, Allocator>::~rb_tree()
{
	_clearTree(_root);
}


template <typename T, typename Comp, typename Allocator>
typename ft::internal::rb_tree<T, Comp, Allocator>::node_type*
ft::internal::rb_tree<T, Comp, Allocator>::begin()
{
	return NODE(_sentinel.left());
}


template <typename T, typename Comp, typename Allocator>
typename ft::internal::rb_tree<T, Comp, Allocator>::node_type*
ft::internal::rb_tree<T, Comp, Allocator>::begin() const
{
	return NODE(_sentinel.left());
}


template <typename T, typename Comp, typename Allocator>
typename ft::internal::rb_tree<T, Comp, Allocator>::node_type*
ft::internal::rb_tree<T, Comp, Allocator>::end()
{
	return NODE(&_sentinel);
}


template <typename T, typename Comp, typename Allocator>
typename ft::internal::rb_tree<T, Comp, Allocator>::node_type*
ft::internal::rb_tree<T, Comp, Allocator>::end() const
{
	return NODE(&_sentinel);
}

template <typename T, typename Comp, typename Allocator>
typename ft::internal::rb_tree<T, Comp, Allocator>::node_type*
ft::internal::rb_tree<T, Comp, Allocator>::find(value_type CREF val)
{
	if (!_root)
		return NODE(&_sentinel);
	node_type* ret = _root->find(val);
	if (ret)
		return ret;
	return NODE(&_sentinel);
}


template <typename T, typename Comp, typename Allocator>
typename ft::internal::rb_tree<T, Comp, Allocator>::node_type*
ft::internal::rb_tree<T, Comp, Allocator>::insert(value_type CREF val)
{
	node_type	*insertNode = _createNode(val);

	if (!_root) {
		_root = insertNode;
		_sentinel.parent = _root;
		_sentinel.left() = _root;
		_sentinel.right() = _root;
		_root->parent = NULL;
		_root->color = RBT_BLACK;
		return _root;
	}
	_root->insert(insertNode);
	_insertFixup(insertNode);
	_root->color = RBT_BLACK;
	if (insertNode->parent == _sentinel.left() && insertNode == _sentinel.left()->left())
		_sentinel.left() = insertNode;
	else if (insertNode->parent == _sentinel.right() && insertNode == _sentinel.right()->right())
		_sentinel.right() = insertNode;
	return insertNode;
}


template <typename T, typename Comp, typename Allocator>
typename ft::internal::rb_tree<T, Comp, Allocator>::remove_result
ft::internal::rb_tree<T, Comp, Allocator>::remove(value_type CREF val)
{
	node_type	*toRemove = find(val);
	if (toRemove == &_sentinel)
		return remove_result(toRemove, toRemove, toRemove->color);
	// Prefix the _sentinel
	if (toRemove == _sentinel.left())
		_sentinel.left() = _sentinel.left()->parent;
	else if (toRemove == _sentinel.right())
		_sentinel.right() = _sentinel.right()->parent;
	// Actually remove the node
	remove_result result = toRemove->remove(_node_allocator(), _deallocateNode);
	// Fixup the _root
	if (toRemove == _root) {
		if (!result.parentNode && result.replacementNode)
			_root = result.replacementNode;
		if (_root) {
			_root->color = RBT_BLACK;
			_root->parent = &_sentinel;
		}
	} else if (result.removedColor == RBT_BLACK)
		_removeFixup(result);
	return result;
}


template <typename T, typename Comp, typename Allocator>
typename ft::internal::rb_tree<T, Comp, Allocator>::node_type*
ft::internal::rb_tree<T, Comp, Allocator>::_createNode(value_type CREF val)
{
	node_type* newNode;
	TRY_ALLOC(newNode = _node_allocator().allocate(1);,;);
	_node_allocator().construct(newNode, val);
	return newNode;
}


template <typename T, typename Comp, typename Allocator>
void
ft::internal::rb_tree<T, Comp, Allocator>::_insertFixup(node_type* inserted)
{
	color_type	blackRef = RBT_BLACK;
	while (inserted->parent && inserted->parent->color == RBT_RED) {
		base_type*		parent = inserted->parent;
		if (!parent)
			return;
		base_type*		grandParent = parent->parent;
		if (!grandParent)
			return;
		side_type		parentSide = (parent == grandParent->left()) ? RBT_LEFT : RBT_RIGHT;
		base_type*		uncle = grandParent->next[!parentSide];
		color_type REF	uncleColor = (uncle) ? uncle->color : blackRef;
		if (uncleColor == RBT_RED) {
			parent->color = RBT_BLACK;
			uncleColor = RBT_BLACK;
			parent->parent->color = RBT_RED;
			inserted = NODE(parent->parent);
			continue;
		}
		if (inserted == parent->next[!parentSide]) {
			inserted = NODE(parent);
			base_type* rotatedNode = inserted->rotate(parentSide);
			if (!rotatedNode->parent)
				_root = NODE(rotatedNode);
		}
		inserted->parent->color = RBT_BLACK;
		inserted->parent->parent->color = RBT_RED;
		base_type* rotatedNode = inserted->parent->parent->rotate(!parentSide);
		if (!rotatedNode->parent)
			_root = NODE(rotatedNode);
	}
}

template <typename T, typename Comp, typename Allocator>
void
ft::internal::rb_tree<T, Comp, Allocator>::_removeFixup(remove_result result)
{
	base_type*	node = result.replacementNode;
	base_type*	parent = result.parentNode;

	while ((!node || node->color) && node != _root) {
		if (!parent)
			break;
		side_type	nodeSide = (parent->left() == node) ? RBT_LEFT : RBT_RIGHT;
		base_type*	sibling = parent->next[!nodeSide];

		if (sibling && sibling->color == RBT_RED) {
			sibling->color = RBT_BLACK;
			parent->color = RBT_RED;
			parent->rotate(nodeSide);
			sibling = parent->next[!nodeSide];
		}
		base_type* nearNephew = (sibling) ? sibling->next[nodeSide] : NULL;
		base_type* farNephew  = (sibling) ? sibling->next[!nodeSide] : NULL;
		bool isNearRed = (nearNephew && nearNephew->color == RBT_RED);
		bool isFarRed  = (farNephew && farNephew->color == RBT_RED);
		if (!isNearRed && !isFarRed) {
			if (sibling)
				sibling->color = RBT_RED;
			node = parent;
			parent = node->parent;
			continue;
		}
		if (!isFarRed) {
			if (nearNephew)
				nearNephew->color = RBT_BLACK;
			if (sibling) {
				sibling->color = RBT_RED;
				sibling->rotate(!nodeSide);
			}
			sibling = parent->next[!nodeSide];
			farNephew = (sibling) ? sibling->next[!nodeSide] : NULL;
		}
		if (sibling)
			sibling->color = parent->color;
		parent->color = RBT_BLACK;
		if (farNephew)
			farNephew->color = RBT_BLACK;
		parent->rotate(nodeSide);
		node = _root;
	}
	if (node)
		node->color = RBT_BLACK;
}


template <typename T, typename Comp, typename Allocator>
void
ft::internal::rb_tree<T, Comp, Allocator>::_clearTree(node_type* node)
{
	if (!node)
		return ;
	_clearTree(NODE(node->left()));
	_clearTree(NODE(node->right()));
	_deallocateNode(_node_allocator(), node);
}


template <typename T, typename Comp, typename Allocator>
void
ft::internal::rb_tree<T, Comp, Allocator>::_deallocateNode(_node_allocator_type allocator, node_type* node)
{
	allocator.destroy(node);
	allocator.deallocate(node, 1);
}


// Static Functions


template <typename T, typename Comp>
static
typename ft::internal::rbt_node<T, Comp>::remove_result
noChildRemove(ft::internal::rbt_node<T, Comp>* node)
{
	typedef typename ft::internal::rbt_node<T, Comp>::remove_result remove_result;

	remove_result result(NULL, NULL, node->color);
	if (node->parent)
		(node->parent->left() == node) ? node->parent->left() = NULL : node->parent->right() = NULL;
	result.parentNode = NODE(node->parent);
	return result;
}


template <typename T, typename Comp>
static
typename ft::internal::rbt_node<T, Comp>::remove_result
oneChildRemove(ft::internal::rbt_node<T, Comp>* node)
{
	typedef ft::internal::rbt_node<T, Comp>		node_type;
	typedef typename node_type::remove_result	remove_result;

	remove_result result(NULL, NULL, node->color);
	node_type*	successor = node->left() ? NODE(node->left()) : NODE(node->right());
	successor->parent = node->parent;
	if (node->parent)
		(node->parent->left() == node) ? node->parent->left() = successor : node->parent->right() = successor;
	result.replacementNode = successor;
	result.parentNode = NODE(node->parent);
	return result;
}


template <typename T, typename Comp>
static
typename ft::internal::rbt_node<T, Comp>::remove_result
twoChildrenRemove(ft::internal::rbt_node<T, Comp>* node)
{
	typedef ft::internal::rbt_node<T, Comp>		node_type;
	typedef typename node_type::side_type		side_type;
	typedef typename node_type::remove_result	remove_result;

	remove_result	result(NULL, NULL, 0);
	node_type*		successor = NODE(node->right()->min());
	side_type		successorSide = (successor->parent->left() == successor) ? RBT_LEFT : RBT_RIGHT;

	// Fixup successor child before extracting the successor
	node_type*	successorChild = NODE(successor->right());
	if (successorChild)
		successorChild->parent = successor->parent;
	successor->parent->next[successorSide] = successorChild;

	// Initialise the correct value of result
	result.parentNode = NODE(successor->parent);
	if (successor->parent == node)
		result.parentNode = successor;
	result.replacementNode = successorChild;
	result.removedColor = successor->color;

	// Replacing the node by the successor
	successor->parent = node->parent;
	if (node->parent)
		(node->parent->left() == node) ? node->parent->left() = successor : node->parent->right() = successor;
	node->left()->parent = successor;
	node->right()->parent = successor;
	successor->left() = node->left();
	successor->right() = node->right();
	if (successor->left() == successor)
		successor->left() = NULL;
	if (successor->right() == successor)
		successor->right() = NULL;
	successor->color = node->color;
	return result;
}

#undef NODE
#undef BASE

#endif //BINARY_TREES_TPP
