//
// Created by mscheman on 1/26/26.
//

#ifndef BINARY_TREES_TPP
#define BINARY_TREES_TPP

#ifndef BINARY_TREES_HPP
# include "binary_trees.hpp"
#endif

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


//
//	rbt_node<T>
//


template <typename T>
template <typename Compare>
typename ft::internal::rbt_node<T>::this_type*
ft::internal::rbt_node<T>::insert(this_type* node, Compare comp)
{
	// node < this
	side_type insertSide = (comp(node->value, this->value)) ? RBT_LEFT : RBT_RIGHT;
	if (this->next[insertSide])
		return RBT_NODE(this->next[insertSide])->insert(node, comp);
	this->next[insertSide] = node;
	node->color = RBT_RED;
	node->parent = this;
	ft::fill_n(node->next, 2, static_cast<base_type*>(NULL));
	return node;
}


template <typename T>
template <typename Allocator, typename FreeFunc>
typename ft::internal::rbt_node<T>::remove_result
ft::internal::rbt_node<T>::erase(Allocator allocator, FreeFunc free)
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


template <typename T>
template <typename Compare>
typename ft::internal::rbt_node<T>::this_type*
ft::internal::rbt_node<T>::find(value_type CREF val, Compare comp) const
{
	bool const isSmaller = comp(val, this->value);
	bool const isBigger = comp(this->value, val);
	if (!isSmaller && !isBigger)
		return const_cast<this_type*>(this);
	side_type searchSide = (isSmaller) ? RBT_LEFT : RBT_RIGHT;
	if (next[searchSide])
		return RBT_NODE(next[searchSide])->find(val, comp);
	return NULL;
}


template <typename T>
template <typename Compare>
ft::size_t
ft::internal::rbt_node<T>::count(value_type CREF val, Compare comp) const
{
	bool const isSmaller = comp(val, this->value);
	bool const isBigger = comp(this->value, val);
	ft::size_t count = (!isSmaller && !isBigger);
	if (isSmaller && left())
		return RBT_NODE(left())->count(val, comp);
	if (isBigger && right())
		return RBT_NODE(right())->count(val, comp);
	if (left())
		count += RBT_NODE(left())->count(val, comp);
	if (right())
		count += RBT_NODE(right())->count(val, comp);
	return count;
}


template <typename T>
template <typename Compare>
typename ft::internal::rbt_node<T>::this_type const*
ft::internal::rbt_node<T>::lower_bound(value_type CREF val, Compare comp) const
{
	this_type	const* iterator = this;
	this_type	const* candidate = NULL;
	bool 		isSmaller;
	bool 		isBigger;
	while (iterator) {
		isSmaller = comp(val, iterator->value);
		isBigger = comp(iterator->value, val);
		if (!isSmaller && !isBigger)
			return iterator;
		if (isSmaller) {
			candidate = iterator;
			iterator = RBT_NODE(iterator->left());
		} else
			iterator = RBT_NODE(iterator->right());
	}
	return candidate;
}


template <typename T>
template <typename Compare>
typename ft::internal::rbt_node<T>::this_type const*
ft::internal::rbt_node<T>::upper_bound(value_type CREF val, Compare comp) const
{
	this_type	const* iterator = this;
	this_type	const* candidate = NULL;
	bool 		isSmaller;
	bool 		isBigger;
	while (iterator) {
		isSmaller = comp(val, iterator->value);
		isBigger = comp(iterator->value, val);
		if (isSmaller) {
			candidate = iterator;
			iterator = RBT_NODE(iterator->left());
		} else
			iterator = RBT_NODE(iterator->right());
	}
	return candidate;
}


template <typename T>
template <typename Compare>
ft::pair<
	typename ft::internal::rbt_node<T>::this_type const*,
	typename ft::internal::rbt_node<T>::this_type const*
>
ft::internal::rbt_node<T>::equal_range(value_type CREF val, Compare comp) const
{
	return ft::make_pair(lower_bound(val, comp), upper_bound(val, comp));
}


//
//	rb_tree<T, Comp, Allocator>
//


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::~rbt()
{
	_clearTree(_root);
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::begin()
{
	return iterator(&_sentinel, RBT_NODE(_sentinel.left()));
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::const_iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::begin() const
{
	return const_iterator(&_sentinel,RBT_NODE(_sentinel.left()));
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::end()
{
	return iterator(&_sentinel, RBT_NODE(&_sentinel));
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::const_iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::end() const
{
	return const_iterator(&_sentinel, RBT_NODE(const_cast<base_type *>(&_sentinel)));
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::reverse_iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::rbegin()
{
	return reverse_iterator(end());
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::const_reverse_iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::rbegin() const
{
	return const_reverse_iterator(end());
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::reverse_iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::rend()
{
	return reverse_iterator(begin());
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::const_reverse_iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::rend() const
{
	return const_reverse_iterator(begin());
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
bool
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::empty() const
{
	return _root->parent;
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::size_type
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::size() const
{
	return _size;
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::size_type
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::max_size() const
{
	return _node_allocator().max_size();
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::insert(value_type CREF val)
{
	node_type	*insertNode = _createNode(val);

	++_size;
	if (!_root) {
		_root = insertNode;
		_sentinel.parent = _root;
		_sentinel.left() = _root;
		_sentinel.right() = _root;
		_root->parent = NULL;
		_root->color = RBT_BLACK;
		return iterator(&_sentinel, _root);
	}
	_root->insert(insertNode, ft::internal::ValueComparator<extractKey, Comp>(_comp));
	_insertFixup(insertNode);
	_root->color = RBT_BLACK;
	if (insertNode->parent == _sentinel.left() && insertNode == _sentinel.left()->left())
		_sentinel.left() = insertNode;
	else if (insertNode->parent == _sentinel.right() && insertNode == _sentinel.right()->right())
		_sentinel.right() = insertNode;
	return iterator(&_sentinel, insertNode);
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::remove_result
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::erase(value_type CREF val)
{
	node_type	*toRemove = find(val);
	if (toRemove == &_sentinel)
		return remove_result(toRemove, toRemove, toRemove->color);
	return _fastErase(toRemove);
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::swap(this_type REF other)
{
	ft::swap(this->_root, other._root);
	ft::swap(this->_sentinel, other._sentinel);
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::clear()
{
	_clearTree(_root);
	_root = NULL;
	_sentinel.left() = NULL;
	_sentinel.right() = NULL;
	_sentinel.parent = NULL;
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::key_compare
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::key_comp() const
{
	return _comp;
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::value_compare
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::value_comp() const
{
	return _comp;
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::find(value_type CREF val)
{
	if (!_root)
		return end();
	node_type* ret = _root->find(val, ft::internal::ValueComparator<extractKey, Comp>(_comp));
	if (ret)
		return iterator(&_sentinel, ret);
	return end();
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::const_iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::find(value_type CREF val) const
{
	if (!_root)
		return end();
	node_type* ret = _root->find(val, ft::internal::ValueComparator<extractKey, Comp>(_comp));
	if (ret)
		return iterator(&_sentinel, ret);
	return end();
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::size_type
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::count(value_type CREF val) const
{
	return _root->count(val, ft::internal::ValueComparator<extractKey, Comp>(_comp));
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::lower_bound(value_type CREF val) const
{
	node_type const* bound = _root->lower_bound(val, ft::internal::ValueComparator<extractKey, Comp>(_comp));
	if (!bound)
		return end();
	return iterator(const_cast<base_type*>(&_sentinel), const_cast<node_type*>(bound));
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::iterator
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::upper_bound(value_type CREF val) const
{
	node_type const* bound = _root->upper_bound(val, ft::internal::ValueComparator<extractKey, Comp>(_comp));
	if (!bound)
		return end();
	return iterator(const_cast<base_type*>(&_sentinel), const_cast<node_type*>(bound));
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
ft::pair<
	typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::iterator,
	typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::iterator
>
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::equal_range(value_type CREF val) const
{
	ft::pair<node_type const*, node_type const*> nodeRange = _root->equal_range(val, ft::internal::ValueComparator<extractKey, Comp>(_comp));
	if (!nodeRange.first())
		nodeRange.first() = static_cast<node_type const*>(&_sentinel);
	if (!nodeRange.second())
		nodeRange.second() = static_cast<node_type const*>(&_sentinel);
	return ft::make_pair(
		iterator(const_cast<base_type*>(&_sentinel),  const_cast<node_type*>(nodeRange.first())),
		iterator(const_cast<base_type*>(&_sentinel),  const_cast<node_type*>(nodeRange.second()))
	);
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::allocator_type
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::get_allocator() const
{
	return _allocator;
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::node_type*
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::_createNode(value_type CREF val)
{
	node_type* newNode;
	TRY_ALLOC(newNode = _node_allocator().allocate(1);,;);
	_node_allocator().construct(newNode, val);
	return newNode;
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::_insertFixup(node_type* inserted)
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
			inserted = RBT_NODE(parent->parent);
			continue;
		}
		if (inserted == parent->next[!parentSide]) {
			inserted = RBT_NODE(parent);
			base_type* rotatedNode = inserted->rotate(parentSide);
			if (!rotatedNode->parent)
				_root = RBT_NODE(rotatedNode);
		}
		inserted->parent->color = RBT_BLACK;
		inserted->parent->parent->color = RBT_RED;
		base_type* rotatedNode = inserted->parent->parent->rotate(!parentSide);
		if (!rotatedNode->parent)
			_root = RBT_NODE(rotatedNode);
	}
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::remove_result
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::_fastErase(node_type* toRemove)
{
	node_type	*rootReplacement = NULL;

	// Pre-fix the _sentinel
	if (toRemove == _sentinel.left())
		_sentinel.left() = _sentinel.left()->parent;
	else if (toRemove == _sentinel.right())
		_sentinel.right() = _sentinel.right()->parent;
	if (toRemove == _root && !_root->left() && !_root->right())
		_sentinel.left() = _sentinel.right() = NULL;
	// Actually remove the node
	if (toRemove == _root && toRemove->right())
		rootReplacement = RBT_NODE(toRemove->right()->min());
	remove_result result = toRemove->erase(_node_allocator(), _deallocateNode);
	--_size;
	// Fixup the _root
	if (toRemove == _root) {
		_root = rootReplacement;
		if (_root) {
			_root->color = RBT_BLACK;
			_root->parent = NULL;
		}
	}
	if (result.removedColor == RBT_BLACK)
		_eraseFixup(result);
	return result;
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::_eraseFixup(remove_result result)
{
	base_type*	rotatedNode = NULL;
	base_type*	node = result.replacementNode;
	base_type*	parent = result.parentNode;

	while ((!node || node->color == RBT_BLACK) && node != _root) {
		if (!parent)
			break;
		side_type	nodeSide = (parent->left() == node) ? RBT_LEFT : RBT_RIGHT;
		base_type*	sibling = parent->next[!nodeSide];

		if (sibling && sibling->color == RBT_RED) {
			sibling->color = RBT_BLACK;
			parent->color = RBT_RED;
			rotatedNode = parent->rotate(nodeSide);
			if (!rotatedNode->parent)
				_root = RBT_NODE(rotatedNode);
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
				rotatedNode = sibling->rotate(!nodeSide);
				if (!rotatedNode->parent)
					_root = RBT_NODE(rotatedNode);
			}
			sibling = parent->next[!nodeSide];
			farNephew = (sibling) ? sibling->next[!nodeSide] : NULL;
		}
		if (sibling)
			sibling->color = parent->color;
		parent->color = RBT_BLACK;
		if (farNephew)
			farNephew->color = RBT_BLACK;
		rotatedNode = parent->rotate(nodeSide);
		if (!rotatedNode->parent)
			_root = RBT_NODE(rotatedNode);
		node = _root;
	}
	if (node)
		node->color = RBT_BLACK;
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::_clearTree(node_type* node)
{
	if (!node)
		return ;
	_clearTree(RBT_NODE(node->left()));
	_clearTree(RBT_NODE(node->right()));
	_deallocateNode(_node_allocator(), node);
}


template <typename T, typename Comp, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::rbt<T, Comp, Allocator, extractKey, mutableIterators>::_deallocateNode(_node_allocator_type allocator, node_type* node)
{
	allocator.destroy(node);
	allocator.deallocate(node, 1);
}


//
// Static Functions
//


template <typename T>
static
typename ft::internal::rbt_node<T>::remove_result
noChildRemove(ft::internal::rbt_node<T>* node)
{
	typedef typename ft::internal::rbt_node<T>::remove_result remove_result;

	remove_result result(NULL, NULL, node->color);
	if (node->parent)
		(node->parent->left() == node) ? node->parent->left() = NULL : node->parent->right() = NULL;
	result.parentNode = RBT_NODE(node->parent);
	return result;
}


template <typename T>
static
typename ft::internal::rbt_node<T>::remove_result
oneChildRemove(ft::internal::rbt_node<T>* node)
{
	typedef ft::internal::rbt_node<T>		node_type;
	typedef typename node_type::remove_result	remove_result;

	remove_result result(NULL, NULL, node->color);
	node_type*	successor = node->left() ? RBT_NODE(node->left()) : RBT_NODE(node->right());
	successor->parent = node->parent;
	if (node->parent)
		(node->parent->left() == node) ? node->parent->left() = successor : node->parent->right() = successor;
	result.replacementNode = successor;
	result.parentNode = RBT_NODE(node->parent);
	return result;
}


template <typename T>
static
typename ft::internal::rbt_node<T>::remove_result
twoChildrenRemove(ft::internal::rbt_node<T>* node)
{
	typedef ft::internal::rbt_node<T>		node_type;
	typedef typename node_type::side_type		side_type;
	typedef typename node_type::remove_result	remove_result;

	remove_result	result(NULL, NULL, 0);
	node_type*		successor = RBT_NODE(node->right()->min());
	side_type		successorSide = (successor->parent->left() == successor) ? RBT_LEFT : RBT_RIGHT;

	// Fixup successor child before extracting the successor
	node_type*	successorChild = RBT_NODE(successor->right());
	if (successorChild)
		successorChild->parent = successor->parent;
	successor->parent->next[successorSide] = successorChild;

	// Initialise the correct value of result
	result.parentNode = RBT_NODE(successor->parent);
	if (successor->parent == node)
		result.parentNode = successor;
	result.replacementNode = successorChild;
	result.removedColor = successor->color;

	// Replacing the node by the successor
	successor->parent = node->parent;
	if (node->parent)
		(node->parent->left() == node) ? node->parent->left() = successor : node->parent->right() = successor;
	if (node->left() && node->left()->parent != successor)
		node->left()->parent = successor;
	if (node->right() && node->right()->parent != successor)
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


#endif //BINARY_TREES_TPP
