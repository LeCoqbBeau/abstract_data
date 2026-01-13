
#ifndef LIST_TPP
# define LIST_TPP

#include ".helper/algorithm.hpp"
#include ".helper/functional.hpp"
#include ".helper/new.hpp"
#include ".helper/type_traits.hpp"


template <class T, class Allocator>
ft::list<T, Allocator>::list(allocator_type CREF alloc)
	: _sentinel(_createNode()), _allocator(alloc)
{
	_sentinel->next = _sentinel;
	_sentinel->prev = _sentinel;
}


template <class T, class Allocator>
ft::list<T, Allocator>::list(size_type n, value_type CREF val, allocator_type CREF alloc)
	: _sentinel(_createNode()), _allocator(alloc)
{
	_sentinel->next = _sentinel;
	_sentinel->prev = _sentinel;
	_assignHelper(n, val, ft::true_type());
}


template <class T, class Allocator>
template <class InputIt>
ft::list<T, Allocator>::list(InputIt first, InputIt last, allocator_type CREF alloc)
	: _sentinel(_createNode()), _allocator(alloc)
{
	typedef typename ft::is_integral<InputIt>::type is_integral;
	_sentinel->next = _sentinel;
	_sentinel->prev = _sentinel;
	_assignHelper(first, last, is_integral());
}


template <class T, class Allocator>
ft::list<T, Allocator>::list(list CREF x)
	: _sentinel()
{
	*this = x;
}


template <class T, class Allocator>
ft::list<T, Allocator> REF ft::list<T, Allocator>::operator = (list CREF rhs) {
	if (this != &rhs) {
		this->_clearHelper();
		_allocator.deallocate(this->_sentinel, 1);
		this->_sentinel = rhs._duplicate();
		this->_allocator = rhs._allocator;
	}
	return *this;
}


template <class T, class Allocator>
ft::list<T, Allocator>::~list() {
	_clearHelper();
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
	return reverse_iterator(end());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reverse_iterator ft::list<T, Allocator>::rbegin() const {
	return const_reverse_iterator(end());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::reverse_iterator ft::list<T, Allocator>::rend() {
	return reverse_iterator(begin());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reverse_iterator ft::list<T, Allocator>::rend() const {
	return const_reverse_iterator(begin());
}


// Capacity
template <class T, class Allocator>
bool ft::list<T, Allocator>::empty() const {
	return (_sentinel == _sentinel->next);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::size_type ft::list<T, Allocator>::size() const {
	size_type listSize = 0;
	for (node_type node = _sentinel->next; node != _sentinel; node = node->next)
		++listSize;
	return listSize;
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
	typedef typename ft::is_integral<InputIt>::type is_integral;
	_clearHelper();
	_assignHelper(first, last, is_integral());
}


template <class T, class Allocator>
void ft::list<T, Allocator>::push_front(value_type CREF val) {
	node_type insertedNode = _createNode(val);
	_sentinel->next->prev = insertedNode;
	insertedNode->next = _sentinel->next;
	insertedNode->prev = _sentinel;
	_sentinel->next = insertedNode;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::pop_front() {
	if (empty())
		return;
	node_type toDel = _sentinel->next;
	_sentinel->next = _sentinel->next->next;
	_sentinel->next->prev = _sentinel;
	_allocator.destroy(toDel);
	_allocator.deallocate(toDel, 1);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::push_back(value_type CREF val) {
	node_type insertedNode = _createNode(val);
	_sentinel->prev->next = insertedNode;
	insertedNode->prev = _sentinel->prev;
	insertedNode->next = _sentinel;
	_sentinel->prev = insertedNode;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::pop_back() {
	if (empty())
		return;
	node_type toDel = _sentinel->prev;
	_sentinel->prev = _sentinel->prev->prev;
	_sentinel->prev->next = _sentinel;
	_allocator.destroy(toDel);
	_allocator.deallocate(toDel, 1);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, value_type CREF value) {
	node_type insertedNode = _createNode(value);
	insertedNode->next = position._currentNode;
	insertedNode->prev = position._currentNode->prev;
	insertedNode->next->prev = insertedNode;
	insertedNode->prev->next = insertedNode;
	return iterator(insertedNode);
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
	typedef typename ft::is_integral<InputIt>::type is_integral;
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
	node_type toDel = position._currentNode;
	++position;
	_allocator.destroy(toDel);
	_allocator.deallocate(toDel, 1);
	return (position);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::erase(iterator first, iterator last) {
	if (empty())
		return end();
	node_type startingNode = first._currentNode;
	startingNode->prev->next = last._currentNode;
	last._currentNode->prev = startingNode->prev;
	while (startingNode != last._currentNode) {
		node_type nextNode = startingNode->next;
		_allocator.destroy(startingNode);
		_allocator.deallocate(startingNode, 1);
		startingNode = nextNode;
	}
	return iterator(last._currentNode);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::swap(list REF x) {
	ft::swap(this->_sentinel, x._sentinel);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::resize(size_type n, value_type CREF val) {
	size_type const listSize = this->size();
	if (n < listSize)
		return _shrinkHelper(n);
	else if (n == listSize)
		return;
	list tmp(n - listSize, val, _allocator);
	node_type tmpNodesFront = tmp._sentinel->next;
	node_type tmpNodesBack = tmp._sentinel->prev;
	_sentinel->prev->next = tmpNodesFront;
	tmpNodesFront->prev = _sentinel->prev;
	tmpNodesBack->next = _sentinel;
	_sentinel->prev = tmpNodesBack;
	tmp._sentinel->next = tmp._sentinel;
	tmp._sentinel->prev = tmp._sentinel;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::clear() {
	_clearHelper();
}


// Operations
template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, list REF other) {
	node_type frontInserted = other._sentinel->next;
	node_type backInserted = other._sentinel->prev;
	frontInserted->prev = position._currentNode->prev;
	backInserted->next = position._currentNode;
	frontInserted->prev->next = frontInserted;
	backInserted->next->prev = backInserted;
	other._sentinel->next = other._sentinel;
	other._sentinel->prev = other._sentinel;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, list REF other, iterator it) {
	(void)other;
	it._currentNode->prev->next = it._currentNode->next;
	it._currentNode->next->prev = it._currentNode->prev;
	it._currentNode->next = NULL;
	it._currentNode->prev = NULL;
	position._currentNode->prev->next = it._currentNode;
	it._currentNode->prev = position._currentNode->prev;
	position._currentNode->prev = it._currentNode;
	it._currentNode->next = position._currentNode;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, list REF other, iterator first, iterator last) {
	(void)other;
	node_type firstInserted = first._currentNode;
	node_type lastInserted = last._currentNode->prev;

	while (first != last)
		++first;
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
	node_type curr = _sentinel;
	do {
		node_type tmp = curr->next;
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
	node_type thisNode = _sentinel->next;
	node_type otherNode = other._sentinel->next;

	if (other.empty())
		return;
	if (this->empty()) {
		ft::swap(this->_sentinel, other._sentinel);
		return ;
	}
	while (otherNode != other._sentinel && thisNode != _sentinel) {
		if (comp(otherNode->value, thisNode->value)) {
			node_type nextOther = otherNode->next;
			// Makes otherNode orphan
			otherNode->prev->next = otherNode->next;
			otherNode->next->prev = otherNode->prev;
			// Links otherNode inside this
			otherNode->prev = thisNode->prev;
			otherNode->prev->next = otherNode;
			otherNode->next = thisNode;
			thisNode->prev = otherNode;
			otherNode = nextOther;
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
}


// Observers
template <class T, class Allocator>
typename ft::list<T, Allocator>::allocator_type ft::list<T, Allocator>::get_allocator() const {
	return _allocator;
}


// Private Helper Methods
template <class T, class Allocator>
typename ft::list<T, Allocator>::node_type ft::list<T, Allocator>::_createNode() const {
	node_type node;
	try {
		node = _allocator.allocate(1);
	} catch (...) {
		throw ft::bad_alloc();
	}
	return node;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::node_type ft::list<T, Allocator>::_createNode(value_type CREF val) const {
	node_type node;
	try {
		node = _allocator.allocate(1);
	} catch (...) {
		throw ft::bad_alloc();
	}
	_allocator.construct(node, DoublyLinkedList<value_type>(val));
	return node;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::_assignHelper(size_type n, value_type CREF val, ft::true_type) {
	node_type nodeIterator = NULL;

	if (!n)
		return;
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
template <class InputIt> void ft::list<T, Allocator>::_assignHelper(InputIt first, InputIt last, ft::false_type) {
	node_type nodeIterator = _sentinel;
	do {
		nodeIterator->next = _createNode(*first);
		nodeIterator->next->prev = nodeIterator;
		nodeIterator = nodeIterator->next;
		++first;
	} while (first != last);
	nodeIterator->next = _sentinel;
	_sentinel->prev = nodeIterator;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::_insertHelper(
	iterator position,
	list REF other
) {
	node_type frontInserted = other._sentinel->next;
	node_type backInserted = other._sentinel->prev;
	frontInserted->prev = position._currentNode->prev;
	backInserted->next = position._currentNode;
	frontInserted->prev->next = frontInserted;
	backInserted->next->prev = backInserted;
	other._sentinel->next = other._sentinel;
	other._sentinel->prev = other._sentinel;
	return iterator(frontInserted);
}


template <class T, class Allocator>
ft::list<T, Allocator> ft::list<T, Allocator>::_insertHelper(
	size_type n,
	value_type CREF val,
	ft::true_type t
) {
	list tmp(_allocator);
	tmp._assignHelper(n, val, t);
	return tmp;
}


template <class T, class Allocator>
template <class InputIt> ft::list<T, Allocator> ft::list<T, Allocator>::_insertHelper(
	InputIt first,
	InputIt last,
	ft::false_type t
) {
	list tmp(_allocator);
	tmp._assignHelper(first, last, t);
	return tmp;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::node_type ft::list<T, Allocator>::_duplicate() const {
	node_type newSentinel = _createNode();
	node_type newIt = newSentinel;
	node_type srcIt = _sentinel->next;

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
	node_type nodeIterator;
	node_type nextNode;

	if (n < this->size() / 2) {
		nodeIterator = _sentinel->prev;
		for (size_type i = 0; i < this->size() - n - 1; ++i)
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
	node_type	nodeIterator = NULL;
	node_type	nextNode = NULL;

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
typename ft::list<T, Allocator>::node_type ft::list<T, Allocator>::_delBackHelper(node_type node) {
	if (!node)
		return NULL;
	node_type prev = node->prev;
	_allocator.destroy(node);
	_allocator.deallocate(node, 1);
	return prev;
}


template <class T, class Allocator>
template <class Compare> void ft::list<T, Allocator>::_initMergeSort(Compare comp) {
	if (this->size() <= 1)
		return;
	node_type oldNext = _sentinel->next;
	node_type oldPrev = _sentinel->prev;

	node_type head = oldNext;
	head->prev = 0;

	try {
		node_type newHead = _split(comp, head, this->size());
		node_type newTail = newHead;
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
typename ft::list<T, Allocator>::node_type ft::list<T, Allocator>::_split(Compare comp, node_type head, size_type size) {
	if (size <= 1)
		return head;
	size_type mid = size / 2;
	node_type midNode = head;
	for (size_type i = 0; i < mid; ++i)
		midNode = midNode->next;
	node_type left = _split(comp, head, mid);
	node_type right = _split(comp, midNode, size - mid);
	return _merge(comp, left, mid, right, size - mid);
}


template <class T, class Allocator>
template <class Compare>
typename ft::list<T, Allocator>::node_type ft::list<T, Allocator>::_merge(
	Compare comp,
	node_type left, size_type leftSize,
	node_type right, size_type rightSize
) {
	node_type result = 0;
	node_type tail = 0;

	while (leftSize && rightSize) {
		node_type next;
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
	node_type remaining = (leftSize ? left : right);
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
void ft::list<T, Allocator>::_cleanList(node_type removed) {
	removed->prev->next = _sentinel;
	_sentinel->prev = removed->prev;
	while (removed != _sentinel) {
		node_type nextNode = removed->next;
		_allocator.destroy(removed);
		_allocator.deallocate(removed, 1);
		removed = nextNode;
	}
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::_nodeAllocator ft::list<T, Allocator>::_getNodeAllocator() {
	return _allocator;
}


#endif