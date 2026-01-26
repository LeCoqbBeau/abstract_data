//
// Created by mscheman on 1/26/26.
//

#ifndef BINARY_TREES_TPP
#define BINARY_TREES_TPP

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
typename ft::internal::rbt_node<T, Comp>::this_type*
ft::internal::rbt_node<T, Comp>::remove(value_type CREF val, Allocator allocator, FreeFunc free)
{
	bool const isSmaller = comp(val, this->value);
	bool const isBigger = comp(this->value, val);
	if (isSmaller)
		left() = NODE(left())->remove(val, allocator, free);
	else if (isBigger)
		right() = NODE(right())->remove(val, allocator, free);
	else {
		if (!left()) {
			this_type* tmp = NODE(right());
			free(allocator, this);
			return tmp;
		}
		if (!right()) {
			this_type* tmp = NODE(left());
			free(allocator, this);
			return tmp;
		}
		this_type* successor = NODE(this->nextNode());
		ft::swap(value, successor->value);
		this->right() = NODE(this->right())->remove(val, allocator, free);
	}
	return this;
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
		_root->parent = &_sentinel;
		_root->color = RBT_BLACK;
		return _root;
	}
	_root->insert(insertNode);
	// insert Fixup
	if (insertNode->parent == _sentinel.left() && insertNode == _sentinel.left()->left())
		_sentinel.left() = insertNode;
	else if (insertNode->parent == _sentinel.right() && insertNode == _sentinel.right()->right())
		_sentinel.right() = insertNode;
	return insertNode;
}


template <typename T, typename Comp, typename Allocator>
typename ft::internal::rb_tree<T, Comp, Allocator>::node_type*
ft::internal::rb_tree<T, Comp, Allocator>::remove(value_type CREF val)
{
	node_type *replacingNode = _root->remove(val, _node_allocator(), _deallocateNode);
	if (replacingNode == _root) {
		_root = replacingNode;
		_root->parent = &_sentinel;
	}
	_deallocateNode(_node_allocator() ,replacingNode);
	return replacingNode;
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
ft::internal::rb_tree<T, Comp, Allocator>::_deallocateNode(_node_allocator_type allocator, node_type* node)
{
	allocator.destroy(node);
	allocator.deallocate(node, 1);
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


#undef NODE
#undef BASE

#endif //BINARY_TREES_TPP
