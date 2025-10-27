
#ifndef LIST_TPP
# define LIST_TPP

#include ".helper/ftexcept.h"
#include ".helper/algorithm.h"
#include ".helper/functional.h"
#include ".helper/type_traits.h"

template <class T, class Allocator>
ft::list<T, Allocator>::list(allocator_type CREF alloc)
	: _sentinel(_createNode(0)), _allocator(alloc), _size(0)
{
	_sentinel->next = _sentinel;
	_sentinel->prev = _sentinel;
}

template <class T, class Allocator>
ft::list<T, Allocator>::list(size_type n, value_type CREF val, allocator_type CREF alloc)
	: _sentinel(_createNode(0)), _allocator(alloc), _size(0)
{
	_sentinel->next = _sentinel;
	_sentinel->prev = _sentinel;
	_assignHelper(n, val, traits::true_type());
}

template <class T, class Allocator>
template <class InputIt>
ft::list<T, Allocator>::list(InputIt first, InputIt last, allocator_type CREF alloc)
	: _sentinel(_createNode(0)), _allocator(alloc), _size(0)
{
	typedef typename ft::traits::is_integer<InputIt>::type is_integral;
	_sentinel->next = _sentinel;
	_sentinel->prev = _sentinel;
	_assignHelper(first, last, is_integral());
}

template <class T, class Allocator>
ft::list<T, Allocator>::list(list CREF x)
	: _sentinel(0)
{
	*this = x;
}

template <class T, class Allocator>
ft::list<T, Allocator> REF ft::list<T, Allocator>::operator = (list CREF rhs) {
	if (this != &rhs) {
		this->_clearHelper();
		_allocator.destroy(this->_sentinel);
		_allocator.deallocate(this->_sentinel, 1);
		this->_sentinel = rhs._duplicate();
		this->_allocator = rhs._allocator;
		this->_size = rhs._size;
	}
	return *this;
}

template <class T, class Allocator>
ft::list<T, Allocator>::~list() {
	_clearHelper();
	_allocator.destroy(_sentinel);
	_allocator.deallocate(_sentinel, 1);
}

// Iterators
template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::begin() {
	return iterator(_sentinel->next);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::const_iterator ft::list<T, Allocator>::begin() const {
	return const_iterator(_sentinel->next);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::end() {
	return iterator(_sentinel);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::const_iterator ft::list<T, Allocator>::end() const {
	return const_iterator(_sentinel);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::reverse_iterator ft::list<T, Allocator>::rbegin() {
	return reverse_iterator(_sentinel);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reverse_iterator ft::list<T, Allocator>::rbegin() const {
	return const_reverse_iterator(_sentinel);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::reverse_iterator ft::list<T, Allocator>::rend() {
	return reverse_iterator(_sentinel->next);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reverse_iterator ft::list<T, Allocator>::rend() const {
	return const_reverse_iterator(_sentinel->next);
}

// Capacity
template <class T, class Allocator>
bool ft::list<T, Allocator>::empty() const {
	return (_sentinel == _sentinel->next);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::size_type ft::list<T, Allocator>::size() const {
	return this->_size;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::size_type ft::list<T, Allocator>::max_size() const {
	return _allocator.max_size();
}

// Element Access
template <class T, class Allocator>
typename ft::list<T, Allocator>::reference ft::list<T, Allocator>::front() {
	return _sentinel->next->value;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reference ft::list<T, Allocator>::front() const {
	return _sentinel->next->value;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::reference ft::list<T, Allocator>::back() {
	return _sentinel->prev->value;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reference ft::list<T, Allocator>::back() const {
	return _sentinel->prev->value;
}

// Modifiers
template <class T, class Allocator>
void ft::list<T, Allocator>::assign(size_type count, value_type CREF value) {
	_clearHelper();
	_assignHelper(count, value);
}

template <class T, class Allocator>
template <class InputIt>
void ft::list<T, Allocator>::assign(InputIt first, InputIt last) {
	typedef typename ft::traits::is_integer<InputIt>::type is_integral;
	_clearHelper();
	_assignHelper(first, last, is_integral());
}

template <class T, class Allocator>
void ft::list<T, Allocator>::push_front(value_type CREF val) {
	_node insertedNode = _createNode(val);
	_sentinel->next->prev = insertedNode;
	insertedNode->next = _sentinel->next;
	insertedNode->prev = _sentinel;
	_sentinel->next = insertedNode;
	++_size;
	++_sentinel->value;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::pop_front() {
	if (empty())
		return;
	_node toDel = _sentinel->next;
	_sentinel->next = _sentinel->next->next;
	_sentinel->next->prev = _sentinel;
	_allocator.destroy(toDel);
	_allocator.deallocate(toDel, 1);
	--_size;
	--_sentinel->value;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::push_back(value_type CREF val) {
	_node insertedNode = _createNode(val);
	_sentinel->prev->next = insertedNode;
	insertedNode->prev = _sentinel->prev;
	insertedNode->next = _sentinel;
	_sentinel->prev = insertedNode;
	++_size;
	++_sentinel->value;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::pop_back() {
	if (empty())
		return;
	_node toDel = _sentinel->prev;
	_sentinel->prev = _sentinel->prev->prev;
	_sentinel->prev->next = _sentinel;
	_allocator.destroy(toDel);
	_allocator.deallocate(toDel, 1);
	--_size;
	--_sentinel->value;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, value_type CREF value) {
	_node insertedNode = _createNode(value);
	insertedNode->next = position._currentNode;
	insertedNode->prev = position._currentNode->prev;
	insertedNode->next->prev = insertedNode;
	insertedNode->prev->next = insertedNode;
	++_size;
	++_sentinel->value;
	return insertedNode;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, size_type count, value_type CREF value) {
	list tmp(_allocator);
	tmp._assignHelper(count, value);
	iterator ret = _insertHelper(position, tmp);
	return ret;
}

template <class T, class Allocator>
template<class InputIt> typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, InputIt first, InputIt last) {
	typedef typename ft::traits::is_integer<InputIt>::type is_integral;
	list tmp(_allocator);
	tmp._assignHelper(first, last, is_integral());
	iterator ret = _insertHelper(position, tmp);
	return ret;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::erase(iterator position) {
	if (empty())
		return end();
	position._currentNode->prev->next = position._currentNode->next;
	position._currentNode->next->prev = position._currentNode->prev;
	--_size;
	--_sentinel->value;
	_node toDel = position._currentNode;
	++position;
	_allocator.destroy(toDel);
	_allocator.deallocate(toDel, 1);
	return (position);
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::erase(iterator first, iterator last) {
	if (empty())
		return end();
	_node startingNode = first._currentNode;
	startingNode->prev->next = last._currentNode;
	last._currentNode->prev = startingNode->prev;
	while (startingNode != last._currentNode) {
		_node nextNode = startingNode->next;
		_allocator.destroy(startingNode);
		_allocator.deallocate(startingNode, 1);
		startingNode = nextNode;
		_size--;
		--_sentinel->value;
	}
	return last._currentNode;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::swap(list REF x) {
	_node		tmpSentinel = this->_sentinel;
	size_type	tmpSize  = this->_size;

	this->_sentinel = x._sentinel;
	this->_size = x._size;
	x._sentinel = tmpSentinel;
	x._size = tmpSize;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::resize(size_type n, value_type CREF val) {
	if (n < _size)
		return _shrinkHelper(n);
	else if (n == _size)
		return;
	list tmp(n - _size, val, _allocator);
	_node tmpNodesFront = tmp._sentinel->next;
	_node tmpNodesBack = tmp._sentinel->prev;
	_sentinel->prev->next = tmpNodesFront;
	tmpNodesFront->prev = _sentinel->prev;
	tmpNodesBack->next = _sentinel;
	_sentinel->prev = tmpNodesBack;
	_size = n;
	_sentinel->value = n;
	tmp._sentinel->next = tmp._sentinel;
	tmp._sentinel->prev = tmp._sentinel;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::clear() {
	_clearHelper();
	_size = 0;
	_sentinel->value = 0;
}

// Operations
template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, list REF other) {
	_node frontInserted = other._sentinel->next;
	_node backInserted = other._sentinel->prev;
	frontInserted->prev = position._currentNode->prev;
	backInserted->next = position._currentNode;
	frontInserted->prev->next = frontInserted;
	backInserted->next->prev = backInserted;
	_size += other.size();
	_sentinel->value += other.size();
	other._size = 0;
	other._sentinel->value = 0;
	other._sentinel->next = other._sentinel;
	other._sentinel->prev = other._sentinel;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, list REF other, iterator it) {
	it._currentNode->prev->next = it._currentNode->next;
	it._currentNode->next->prev = it._currentNode->prev;
	it._currentNode->next = NULL;
	it._currentNode->prev = NULL;
	position._currentNode->prev->next = it._currentNode;
	it._currentNode->prev = position._currentNode->prev;
	position._currentNode->prev = it._currentNode;
	it._currentNode->next = position._currentNode;
	++_size;
	++_sentinel->value;
	--other._size;
	--other._sentinel->value;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, list REF other, iterator first, iterator last) {
	_node firstInserted = first._currentNode;
	_node lastInserted = last._currentNode->prev;

	while (first != last) {
		++_size;
		++_sentinel->value;
		--other._size;
		--other._sentinel->value;
		++first;
	}
	firstInserted->prev->next = last._currentNode;
	last._currentNode->prev = firstInserted->prev;
	position._currentNode->prev->next = firstInserted;
	firstInserted->prev = position._currentNode->prev;
	lastInserted->next = position._currentNode;
	position._currentNode->prev = lastInserted;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::remove(value_type CREF val) {
	_cleanList(
		ft::remove(begin(), end(), val)._currentNode
	);
}

template <class T, class Allocator>
template <class Predicate> void ft::list<T, Allocator>::remove_if(Predicate pred) {
	_cleanList(
		ft::remove_if(begin(), end(), pred)._currentNode
	);
}

template <class T, class Allocator>
void ft::list<T, Allocator>::unique() {
	_cleanList(
		ft::unique(begin(), end())._currentNode
	);
}

template <class T, class Allocator>
template <class BinaryPredicate> void ft::list<T, Allocator>::unique(BinaryPredicate pred) {
	_cleanList(
		ft::unique(begin(), end(), pred)._currentNode
	);
}

template <class T, class Allocator>
void ft::list<T, Allocator>::sort() {
	sort(ft::less<value_type>());
}

template <class T, class Allocator>
template <class Compare> void ft::list<T, Allocator>::sort(Compare comp) {
	_initMergeSort(comp);
}

template <class T, class Allocator>
void ft::list<T, Allocator>::reverse() {
	_node curr = _sentinel;
	do {
		_node tmp = curr->next;
		curr->next = curr->prev;
		curr->prev = tmp;
		curr = tmp;
	} while (curr != _sentinel);
}

template <class T, class Allocator>
void ft::list<T, Allocator>::merge(list REF other) {
	merge(other, ft::less<value_type>());
}

template <class T, class Allocator>
template <class Compare> void ft::list<T, Allocator>::merge(list REF other, Compare comp) {
	_node thisNode = _sentinel->next;
	_node otherNode = other._sentinel->next;

	if (other.empty())
		return;
	if (this->empty()) {
		ft::swap(_size, other._size);
		ft::swap(this->_sentinel, other._sentinel);
		_sentinel->value = 0;
		return ;
	}
	while (otherNode != other._sentinel && thisNode != _sentinel) {
		if (comp(otherNode->value, thisNode->value)) {
			_node nextOther = otherNode->next;
			// Makes otherNode orphan
			otherNode->prev->next = otherNode->next;
			otherNode->next->prev = otherNode->prev;
			// Links otherNode inside this
			otherNode->prev = thisNode->prev;
			otherNode->prev->next = otherNode;
			otherNode->next = thisNode;
			thisNode->prev = otherNode;
			otherNode = nextOther;
			++_size;
			++_sentinel->value;
			--other._size;
			--other._sentinel->value;
		} else {
			thisNode = thisNode->next;
		}
	}
	if (other.empty()) {
		other._sentinel->value = 0;
		other._sentinel->next = other._sentinel;
		other._sentinel->prev = other._sentinel;
		return;
	}
	this->_sentinel->prev->next = other._sentinel->next;
	other._sentinel->prev->next = this->_sentinel;
	this->_sentinel->prev = other._sentinel->prev;
	other._sentinel->next = other._sentinel;
	other._sentinel->prev = other._sentinel;
	_size += other._size;
	_sentinel->value += other._size;
	other._size = 0;
	other._sentinel->value = 0;
}

// Observers
template <class T, class Allocator>
typename ft::list<T, Allocator>::allocator_type ft::list<T, Allocator>::get_allocator() const {
	return _allocator;
}

// Private Helper Methods
template <class T, class Allocator>
typename ft::list<T, Allocator>::_node ft::list<T, Allocator>::_createNode(value_type CREF val) const {
	_node node;
	try {
		node = _allocator.allocate(1);
	} catch (...) {
		throw ft::bad_alloc();
	}
	_allocator.construct(node, DoublyLinkedList<value_type>(val));
	return node;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::_assignHelper(size_type n, value_type CREF val, traits::true_type) {
	_node nodeIterator = NULL;

	if (!n)
		return;
	_size = n;
	_sentinel->value = n;
	_sentinel->next = _createNode(val);
	_sentinel->next->prev = _sentinel;
	nodeIterator = _sentinel->next;
	while (--n) {
		nodeIterator->next = _createNode(val);
		nodeIterator->next->prev = nodeIterator;
		nodeIterator = nodeIterator->next;
	}
	nodeIterator->next = _sentinel;
	_sentinel->prev = nodeIterator;
}

template <class T, class Allocator>
template <class InputIt> void ft::list<T, Allocator>::_assignHelper(InputIt first, InputIt last, traits::false_type) {
	_node nodeIterator = _sentinel;
	_size = 0;
	_sentinel->value = 0;
	do {
		nodeIterator->next = _createNode(*first);
		nodeIterator->next->prev = nodeIterator;
		nodeIterator = nodeIterator->next;
		++first;
		++_size;
		++_sentinel->value;
	} while (first != last);
	nodeIterator->next = _sentinel;
	_sentinel->prev = nodeIterator;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::_insertHelper(
	iterator position,
	list REF other
) {
	_node frontInserted = other._sentinel->next;
	_node backInserted = other._sentinel->prev;
	frontInserted->prev = position._currentNode->prev;
	backInserted->next = position._currentNode;
	frontInserted->prev->next = frontInserted;
	backInserted->next->prev = backInserted;
	_size += other._size;
	_sentinel->value += other._size;
	other._sentinel->next = other._sentinel;
	other._sentinel->prev = other._sentinel;
	return frontInserted;
}

template <class T, class Allocator>
ft::list<T, Allocator> ft::list<T, Allocator>::_insertHelper(
	size_type n,
	value_type CREF val,
	traits::true_type t
) {
	list tmp(_allocator);
	tmp._assignHelper(n, val, t);
	return tmp;
}

template <class T, class Allocator>
template <class InputIt> ft::list<T, Allocator> ft::list<T, Allocator>::_insertHelper(
	InputIt first,
	InputIt last,
	traits::false_type t
) {
	list tmp(_allocator);
	tmp._assignHelper(first, last, t);
	return tmp;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::_node ft::list<T, Allocator>::_duplicate() const {
	_node newSentinel = _createNode();
	_node newIt = newSentinel;
	_node srcIt = _sentinel->next;

	while (srcIt != _sentinel) {
		newIt->next = _createNode(srcIt->value);
		newIt->next->prev = newIt;
		newIt = newIt->next;
		srcIt = srcIt->next;
	}
	newIt->next = newSentinel;
	newSentinel->prev = newIt;
	return newSentinel;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::_shrinkHelper(size_type n) {
	_node nodeIterator;
	_node nextNode;
	if (n < _size / 2) {
		nodeIterator = _sentinel->prev;
		for (size_type i = 0; i < _size - n - 1; ++i)
			nodeIterator = nodeIterator->prev;
	} else {
		nodeIterator = _sentinel->next;
		for (size_type i = 0; i < n; ++i)
			nodeIterator = nodeIterator->next;
	}
	_sentinel->prev = nodeIterator->prev;
	_sentinel->prev->next = _sentinel;
	nodeIterator->prev = NULL;
	while (nodeIterator != _sentinel) {
		nextNode = nodeIterator->next;
		_allocator.destroy(nodeIterator);
		_allocator.deallocate(nodeIterator, 1);
		nodeIterator = nextNode;
	}
}

template <class T, class Allocator>
void ft::list<T, Allocator>::_clearHelper() {
	_node	nodeIterator = NULL;
	_node	nextNode = NULL;

	if (!_sentinel)
		return;
	nodeIterator = _sentinel->next;
	while (nodeIterator != _sentinel) {
		nextNode = nodeIterator->next;
		_allocator.destroy(nodeIterator);
		_allocator.deallocate(nodeIterator, 1);
		nodeIterator = nextNode;
	}
	_sentinel->next = _sentinel;
	_sentinel->prev = _sentinel;
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::_node ft::list<T, Allocator>::_delBackHelper(_node node) {
	if (!node)
		return NULL;
	_node prev = node->prev;
	_allocator.destroy(node);
	_allocator.deallocate(node, 1);
	return prev;
}

template <class T, class Allocator>
template <class Compare> void ft::list<T, Allocator>::_initMergeSort(Compare comp) {
	if (_size <= 1)
		return;
	_node oldNext = _sentinel->next;
	_node oldPrev = _sentinel->prev;

	_node head = oldNext;
	head->prev = 0;

	try {
		_node newHead = _split(comp, head, _size);
		_node newTail = newHead;
		while (newTail->next)
			newTail = newTail->next;
		_sentinel->next = newHead;
		newHead->prev = _sentinel;
		_sentinel->prev = newTail;
		newTail->next = _sentinel;
	} catch (...) {
		// Rollback list
		_sentinel->next = oldNext;
		oldNext->prev = _sentinel;
		_sentinel->prev = oldPrev;
		oldPrev->next = _sentinel;
		throw;
	}
}

template <class T, class Allocator>
template <class Compare>
typename ft::list<T, Allocator>::_node ft::list<T, Allocator>::_split(Compare comp, _node head, size_type size) {
	if (size <= 1)
		return head;
	size_type mid = size / 2;
	_node midNode = head;
	for (size_type i = 0; i < mid; ++i)
		midNode = midNode->next;
	_node left = _split(comp, head, mid);
	_node right = _split(comp, midNode, size - mid);
	return _merge(comp, left, mid, right, size - mid);
}

template <class T, class Allocator>
template <class Compare>
typename ft::list<T, Allocator>::_node ft::list<T, Allocator>::_merge(
	Compare comp,
	_node left, size_type leftSize,
	_node right, size_type rightSize
) {
	_node result = 0;
	_node tail = 0;

	while (leftSize && rightSize) {
		_node next;
		if (comp(right->value, left->value)) {
			next = right;
			right = right->next;
			--rightSize;
		} else {
			next = left;
			left = left->next;
			--leftSize;
		}

		if (!result) {
			result = next;
			next->prev = 0;
			tail = next;
			continue;
		}
		tail->next = next;
		next->prev = tail;
		tail = next;
	}
	_node remaining = (leftSize ? left : right);
	size_type remainingSize = (leftSize ? leftSize : rightSize);

	while (remainingSize) {
		tail->next = remaining;
		remaining->prev = tail;
		tail = remaining;
		remaining = remaining->next;
		--remainingSize;
	}
	tail->next = 0;
	return result;
}

template <class T, class Allocator>
void ft::list<T, Allocator>::_cleanList(_node removed) {
	removed->prev->next = _sentinel;
	_sentinel->prev = removed->prev;
	while (removed != _sentinel) {
		_node nextNode = removed->next;
		_allocator.destroy(removed);
		_allocator.deallocate(removed, 1);
		removed = nextNode;
		--_size;
		--_sentinel->value;
	}
}

template <class T, class Allocator>
typename ft::list<T, Allocator>::_nodeAllocator ft::list<T, Allocator>::_getNodeAllocator() {
	return _allocator;
}

#endif