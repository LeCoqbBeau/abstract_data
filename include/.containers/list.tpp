
#ifndef LIST_TPP
# define LIST_TPP

#include "../.helper/type_traits.hpp"
#include ".helper/algorithm.hpp"
#include ".helper/doublyLinkedList.hpp"
#include ".helper/functional.hpp"
#include ".helper/new.hpp"
#include ".helper/type_traits.hpp"


template <class T, class Allocator>
ft::list<T, Allocator>::list(allocator_type CREF alloc)
	: _sentinel(), _allocator(alloc)
{
	_sentinel.next() = &_sentinel;
	_sentinel.prev() = &_sentinel;
}


template <class T, class Allocator>
ft::list<T, Allocator>::list(size_type n, value_type CREF val, allocator_type CREF alloc)
	: _sentinel(), _allocator(alloc)
{
	_sentinel.next() = &_sentinel;
	_sentinel.prev() = &_sentinel;
	_assignHelper(n, val, ft::true_type());
}


template <class T, class Allocator>
template <class InputIt>
ft::list<T, Allocator>::list(InputIt first, InputIt last, allocator_type CREF alloc)
	: _sentinel(), _allocator(alloc)
{
	_sentinel.next() = &_sentinel;
	_sentinel.prev() = &_sentinel;
	_assignHelper(first, last, ft::is_integral<InputIt>());
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
		rhs._duplicate(&this->_sentinel);
		this->_allocator = rhs._allocator;
	}
	return *this;
}


template <class T, class Allocator>
ft::list<T, Allocator>::~list() {
	_clearHelper();
}


// Iterators
template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::begin() {
	return iterator(_sentinel.next());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_iterator ft::list<T, Allocator>::begin() const {
	return const_iterator(_sentinel.next());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::end() {
	return iterator(&_sentinel);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_iterator ft::list<T, Allocator>::end() const {
	return const_iterator(&_sentinel);
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
	return (&_sentinel == _sentinel.next());
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::size_type ft::list<T, Allocator>::size() const {
	size_type listSize = 0;
	for (_base_type* node = _sentinel.next(); node != &_sentinel; node = node->next())
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
	return FT_DLLNODE(_sentinel.next())->value;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reference ft::list<T, Allocator>::front() const {
	return FT_DLLNODE(_sentinel.next())->value;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::reference ft::list<T, Allocator>::back() {
	return FT_DLLNODE(_sentinel.prev())->value;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::const_reference ft::list<T, Allocator>::back() const {
	return FT_DLLNODE(_sentinel.prev())->value;
}


// Modifiers
template <class T, class Allocator>
void ft::list<T, Allocator>::assign(size_type count, value_type CREF value) {
	_clearHelper();
	_assignHelper(count, value, ft::true_type());
}


template <class T, class Allocator>
template <class InputIt>
void ft::list<T, Allocator>::assign(InputIt first, InputIt last) {
	_clearHelper();
	_assignHelper(first, last, ft::is_integral<InputIt>());
}


template <class T, class Allocator>
void ft::list<T, Allocator>::push_front(value_type CREF val) {
	_base_type* insertedNode = _createNode(val);
	_sentinel.next()->prev() = insertedNode;
	insertedNode->mNext = _sentinel.next();
	insertedNode->mPrev = &_sentinel;
	_sentinel.next() = insertedNode;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::pop_front() {
	if (empty())
		return;
	_node_type* toDel = FT_DLLNODE(_sentinel.next());
	_sentinel.next() = _sentinel.next()->next();
	_sentinel.next()->prev() = &_sentinel;
	_getNodeAllocator().destroy(toDel);
	_getNodeAllocator().deallocate(toDel, 1);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::push_back(value_type CREF val) {
	_base_type* insertedNode = _createNode(val);
	_sentinel.prev()->next() = insertedNode;
	insertedNode->prev() = _sentinel.prev();
	insertedNode->next() = &_sentinel;
	_sentinel.prev() = insertedNode;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::pop_back() {
	if (empty())
		return;
	_node_type* toDel = FT_DLLNODE(_sentinel.prev());
	_sentinel.prev() = _sentinel.prev()->prev();
	_sentinel.prev()->next() = &_sentinel;
	_getNodeAllocator().destroy(toDel);
	_getNodeAllocator().deallocate(toDel, 1);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, value_type CREF value) {
	_base_type* insertedNode = _createNode(value);
	insertedNode->next() = position._currentNode;
	insertedNode->prev() = position._currentNode->prev();
	insertedNode->next()->prev() = insertedNode;
	insertedNode->prev()->next() = insertedNode;
	return iterator(insertedNode);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, size_type count, value_type CREF value) {
	list tmp(_allocator);
	tmp._assignHelper(count, value, ft::true_type());
	iterator ret = _insertHelper(position, tmp);
	return ret;
}


template <class T, class Allocator>
template<class InputIt> typename ft::list<T, Allocator>::iterator
ft::list<T, Allocator>::insert(iterator position, InputIt first, InputIt last) {
	list tmp(_allocator);
	tmp._assignHelper(first, last, ft::is_integral<InputIt>());
	iterator ret = _insertHelper(position, tmp);
	return ret;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::erase(iterator position) {
	if (empty())
		return end();
	position._currentNode->prev()->next() = position._currentNode->next();
	position._currentNode->next()->prev() = position._currentNode->prev();
	_node_type* toDel = FT_DLLNODE(position._currentNode);
	++position;
	_getNodeAllocator().destroy(toDel);
	_getNodeAllocator().deallocate(toDel, 1);
	return (position);
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::erase(iterator first, iterator last) {
	if (empty())
		return end();
	_base_type* startingNode = first._currentNode;
	startingNode->prev()->next() = last._currentNode;
	last._currentNode->prev() = startingNode->prev();
	while (startingNode != last._currentNode) {
		_base_type* nextNode = startingNode->next();
		_getNodeAllocator().destroy(FT_DLLNODE(startingNode));
		_getNodeAllocator().deallocate(FT_DLLNODE(startingNode), 1);
		startingNode = nextNode;
	}
	return iterator(last._currentNode);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::swap(list REF x) {
	bool tEmpty = this->empty();
	bool xEmpty = x.empty();
	if (tEmpty && xEmpty)
		return;
	if (!tEmpty && !xEmpty) {
		ft::swap(_sentinel.next(), x._sentinel.next());
		ft::swap(_sentinel.prev(), x._sentinel.prev());
		this->_sentinel.next()->prev() = &this->_sentinel;
		this->_sentinel.prev()->next() = &this->_sentinel;
		x._sentinel.next()->prev() = &x._sentinel;
		x._sentinel.prev()->next() = &x._sentinel;
		return;
	}
	_base_type* emptySentinel = (tEmpty) ? &this->_sentinel : &x._sentinel;
	_base_type* otherSentinel = (tEmpty) ? &x._sentinel : &this->_sentinel;
	emptySentinel->next() = otherSentinel->next();
	emptySentinel->prev() = otherSentinel->prev();
	otherSentinel->next() = otherSentinel->prev() = otherSentinel;
	emptySentinel->next()->prev() = emptySentinel;
	emptySentinel->prev()->next() = emptySentinel;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::resize(size_type n, value_type CREF val) {
	size_type const listSize = this->size();
	if (n < listSize)
		return _shrinkHelper(n);
	if (n == listSize)
		return;
	list tmp(n - listSize, val, _allocator);
	_base_type* tmpNodesFront = tmp._sentinel.next();
	_base_type* tmpNodesBack = tmp._sentinel.prev();
	_sentinel.prev()->next() = tmpNodesFront;
	tmpNodesFront->prev() = _sentinel.prev();
	tmpNodesBack->next() = &_sentinel;
	_sentinel.prev() = tmpNodesBack;
	tmp._sentinel.next() = &tmp._sentinel;
	tmp._sentinel.prev() = &tmp._sentinel;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::clear() {
	_clearHelper();
}


// Operations
template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, list REF other) {
	_base_type* frontInserted = other._sentinel.next();
	_base_type* backInserted = other._sentinel.prev();
	frontInserted->prev() = position._currentNode->prev();
	backInserted->next() = position._currentNode;
	frontInserted->prev()->next() = frontInserted;
	backInserted->next()->prev() = backInserted;
	other._sentinel.next() = &other._sentinel;
	other._sentinel.prev() = &other._sentinel;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, list REF other, iterator it) {
	(void)other;
	it._currentNode->prev()->next() = it._currentNode->next();
	it._currentNode->next()->prev() = it._currentNode->prev();
	it._currentNode->next() = NULL;
	it._currentNode->prev() = NULL;
	position._currentNode->prev()->next() = it._currentNode;
	it._currentNode->prev() = position._currentNode->prev();
	position._currentNode->prev() = it._currentNode;
	it._currentNode->next() = position._currentNode;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::splice(iterator position, list REF other, iterator first, iterator last) {
	(void)other;
	_base_type* firstInserted = first._currentNode;
	_base_type* lastInserted = last._currentNode->prev();

	while (first != last)
		++first;
	firstInserted->prev()->next() = last._currentNode;
	last._currentNode->prev() = firstInserted->prev();
	position._currentNode->prev()->next() = firstInserted;
	firstInserted->prev() = position._currentNode->prev();
	lastInserted->next() = position._currentNode;
	position._currentNode->prev() = lastInserted;
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
	_base_type* curr = &_sentinel;
	do {
		_base_type* tmp = curr->next();
		curr->next() = curr->prev();
		curr->prev() = tmp;
		curr = tmp;
	} while (curr != &_sentinel);
}


template <class T, class Allocator>
void ft::list<T, Allocator>::merge(list REF other) {
	merge(other, ft::less<value_type>());
}


template <class T, class Allocator>
template <class Compare> void ft::list<T, Allocator>::merge(list REF other, Compare comp) {
	_base_type* thisNode = _sentinel.next();
	_base_type* otherNode = other._sentinel.next();

	if (other.empty())
		return;
	while (otherNode != &other._sentinel && thisNode != &_sentinel) {
		if (comp(FT_DLLNODE(otherNode)->value, FT_DLLNODE(thisNode)->value)) {
			_base_type* nextOther = otherNode->next();
			// Makes otherNode orphan
			otherNode->prev()->next() = otherNode->next();
			otherNode->next()->prev() = otherNode->prev();
			// Links otherNode inside this
			otherNode->prev() = thisNode->prev();
			otherNode->prev()->next() = otherNode;
			otherNode->next() = thisNode;
			thisNode->prev() = otherNode;
			otherNode = nextOther;
		} else {
			thisNode = thisNode->next();
		}
	}
	if (other.empty()) {
		other._sentinel.next() = &other._sentinel;
		other._sentinel.prev() = &other._sentinel;
		return;
	}
	this->_sentinel.prev()->next() = other._sentinel.next();
	other._sentinel.prev()->next() = &this->_sentinel;
	this->_sentinel.prev() = other._sentinel.prev();
	other._sentinel.next() = &other._sentinel;
	other._sentinel.prev() = &other._sentinel;
}


// Observers
template <class T, class Allocator>
typename ft::list<T, Allocator>::allocator_type ft::list<T, Allocator>::get_allocator() const {
	return _allocator;
}


// Private Helper Methods
template <class T, class Allocator>
typename ft::list<T, Allocator>::_base_type* ft::list<T, Allocator>::_createNode(value_type CREF val) const {
	_node_type* node;
	TRY_ALLOC( node = _getNodeAllocator().allocate(1);,;);
	_getNodeAllocator().construct(node, _node_type(val));
	return node;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::_assignHelper(size_type n, value_type CREF val, ft::true_type) {
	_base_type* nodeIterator = NULL;

	if (!n)
		return;
	_sentinel.next() = _createNode(val);
	_sentinel.next()->prev() = &_sentinel;
	nodeIterator = _sentinel.next();
	while (--n) {
		nodeIterator->mNext = _createNode(val);
		nodeIterator->mNext->mPrev = nodeIterator;
		nodeIterator = nodeIterator->next();
	}
	nodeIterator->mNext = &_sentinel;
	_sentinel.prev() = nodeIterator;
}


template <class T, class Allocator>
template <class InputIt> void ft::list<T, Allocator>::_assignHelper(InputIt first, InputIt last, ft::false_type) {
	_base_type* nodeIterator = &_sentinel;
	do {
		nodeIterator->next() = _createNode(*first);
		nodeIterator->next()->prev() = nodeIterator;
		nodeIterator = nodeIterator->next();
		++first;
	} while (first != last);
	nodeIterator->next() = &_sentinel;
	_sentinel.prev() = nodeIterator;
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::iterator ft::list<T, Allocator>::_insertHelper(
	iterator position,
	list REF other
) {
	_base_type* frontInserted = other._sentinel.next();
	_base_type* backInserted = other._sentinel.prev();
	frontInserted->prev() = position._currentNode->prev();
	backInserted->next() = position._currentNode;
	frontInserted->prev()->next() = frontInserted;
	backInserted->next()->prev() = backInserted;
	other._sentinel.next() = &other._sentinel;
	other._sentinel.prev() = &other._sentinel;
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
void ft::list<T, Allocator>::_duplicate(_base_type *newSentinel) const {
	_base_type*	newIt = newSentinel;
	_base_type*	srcIt = _sentinel.next();

	while (srcIt != &_sentinel) {
		newIt->next() = _createNode(FT_DLLNODE(srcIt)->value);
		newIt->next()->prev() = newIt;
		newIt = newIt->next();
		srcIt = srcIt->next();
	}
	newIt->next() = newSentinel;
	newSentinel->prev() = newIt;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::_shrinkHelper(size_type n) {
	_base_type* nodeIterator;
	_base_type* nextNode;

	if (n < this->size() / 2) {
		nodeIterator = _sentinel.prev();
		for (size_type i = 0; i < this->size() - n - 1; ++i)
			nodeIterator = nodeIterator->prev();
	} else {
		nodeIterator = _sentinel.next();
		for (size_type i = 0; i < n; ++i)
			nodeIterator = nodeIterator->next();
	}
	_sentinel.prev() = nodeIterator->prev();
	_sentinel.prev()->next() = &_sentinel;
	nodeIterator->prev() = NULL;
	while (nodeIterator != &_sentinel) {
		nextNode = nodeIterator->next();
		_node_type*	toDestroy = FT_DLLNODE(nodeIterator);
		_getNodeAllocator().destroy(toDestroy);
		_getNodeAllocator().deallocate(toDestroy, 1);
		nodeIterator = nextNode;
	}
}


template <class T, class Allocator>
void ft::list<T, Allocator>::_clearHelper() {
	_base_type*	nodeIterator = NULL;
	_base_type*	nextNode = NULL;

	nodeIterator = _sentinel.next();
	while (nodeIterator && nodeIterator != &_sentinel) {
		nextNode = nodeIterator->next();
		_node_type*	toDestroy = FT_DLLNODE(nodeIterator);
		_getNodeAllocator().destroy(toDestroy);
		_getNodeAllocator().deallocate(toDestroy, 1);
		nodeIterator = nextNode;
	}
	_sentinel.next() = &_sentinel;
	_sentinel.prev() = &_sentinel;
}


template <class T, class Allocator>
template <class Compare> void ft::list<T, Allocator>::_initMergeSort(Compare comp) {
	if (this->size() <= 1)
		return;
	_base_type* oldNext = _sentinel.next();
	_base_type* oldPrev = _sentinel.prev();

	_base_type* head = oldNext;
	head->prev() = NULL;

	try {
		_base_type* newHead = _split(comp, head, this->size());
		_base_type* newTail = newHead;
		while (newTail->next())
			newTail = newTail->next();
		_sentinel.next() = newHead;
		newHead->prev() = &_sentinel;
		_sentinel.prev() = newTail;
		newTail->next() = &_sentinel;
	} catch (...) {
		// Rollback list
		_sentinel.next() = oldNext;
		oldNext->prev() = &_sentinel;
		_sentinel.prev() = oldPrev;
		oldPrev->next() = &_sentinel;
		throw;
	}
}


template <class T, class Allocator>
template <class Compare>
typename ft::list<T, Allocator>::_base_type* ft::list<T, Allocator>::_split(Compare comp, _base_type* head, size_type size) {
	if (size <= 1)
		return head;
	size_type mid = size / 2;
	_base_type* midNode = head;
	for (size_type i = 0; i < mid; ++i)
		midNode = midNode->next();
	_base_type* left = _split(comp, head, mid);
	_base_type* right = _split(comp, midNode, size - mid);
	return _merge(comp, left, mid, right, size - mid);
}


template <class T, class Allocator>
template <class Compare>
typename ft::list<T, Allocator>::_base_type* ft::list<T, Allocator>::_merge(
	Compare comp,
	_base_type* left, size_type leftSize,
	_base_type* right, size_type rightSize
) {
	_base_type* result = 0;
	_base_type* tail = 0;

	while (leftSize && rightSize) {
		_base_type* next;
		if (comp(FT_DLLNODE(right)->value, FT_DLLNODE(left)->value)) {
			next = right;
			right = right->next();
			--rightSize;
		} else {
			next = left;
			left = left->next();
			--leftSize;
		}
		if (!result) {
			result = next;
			next->prev() = 0;
			tail = next;
			continue;
		}
		tail->next() = next;
		next->prev() = tail;
		tail = next;
	}
	_base_type* remaining = (leftSize ? left : right);
	size_type remainingSize = (leftSize ? leftSize : rightSize);

	while (remainingSize) {
		tail->next() = remaining;
		remaining->prev() = tail;
		tail = remaining;
		remaining = remaining->next();
		--remainingSize;
	}
	tail->next() = 0;
	return result;
}


template <class T, class Allocator>
void ft::list<T, Allocator>::_cleanList(_base_type* removed) {
	removed->prev()->next() = &_sentinel;
	_sentinel.prev() = removed->prev();
	while (removed != &_sentinel) {
		_base_type* nextNode = removed->next();
		_getNodeAllocator().destroy(FT_DLLNODE(removed));
		_getNodeAllocator().deallocate(FT_DLLNODE(removed), 1);
		removed = nextNode;
	}
}


template <class T, class Allocator>
typename ft::list<T, Allocator>::_nodeAllocator ft::list<T, Allocator>::_getNodeAllocator() const {
	return _nodeAllocator(_allocator);
}


#endif
