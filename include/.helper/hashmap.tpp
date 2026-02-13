//
// Created by mscheman on 2/5/26.
//

#ifndef HASHMAP_TPP
#define HASHMAP_TPP

#include ".helper/doublyLinkedList.hpp"
#include "hashmap.hpp"
#include "new.hpp"

//
//	bucket<Key>
//

// Iterators
template <class Key>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::begin()
{
	return iterator(_sentinel.next());
}


template <class Key>
typename ft::internal::bucket<Key>::const_iterator
ft::internal::bucket<Key>::begin() const
{
	return const_iterator(_sentinel.next());
}


template <class Key>
typename ft::internal::bucket<Key>::const_iterator
ft::internal::bucket<Key>::cbegin() const
{
	return const_iterator(_sentinel.next());
}


template <class Key>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::end()
{
	return iterator(&_sentinel);
}


template <class Key>
typename ft::internal::bucket<Key>::const_iterator
ft::internal::bucket<Key>::end() const
{
	return const_iterator(&_sentinel);
}


template <class Key>
typename ft::internal::bucket<Key>::const_iterator
ft::internal::bucket<Key>::cend() const
{
	return const_iterator(&_sentinel);
}


// Methods
template <class Key>
typename ft::internal::bucket<Key>::size_type
ft::internal::bucket<Key>::size() const
{
	size_type	size = 0;
	base_type*	it = _sentinel.next();
	while (it != &_sentinel) {
		++size;
		++it;
	}
	return size;
}


template <class Key>
template <typename Allocator, typename Predicate>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::insert(value_type CREF val, Allocator allocator, Predicate predicate)
{
	typedef Key	T;
	base_type	*inserted = createNode(val, allocator);
	base_type	*insertPos = _sentinel.next();

	// Make sure all keys are together
	while (insertPos != &_sentinel
		&& !predicate(FT_DLLNODE(insertPos)->value, val))
		insertPos = insertPos->next();
	// Insert position behind insertPos
	insertPos->prev()->next() = inserted;
	inserted->prev() = insertPos->prev();
	inserted->next() = insertPos;
	insertPos->prev() = inserted;
	return iterator(inserted);
}


template <class Key>
void
ft::internal::bucket<Key>::insert(base_type *node)
{
	node->prev()->next() = node->next();
	node->next()->prev() = node->prev();
	_sentinel.prev()->next() = node;
	node->prev() = _sentinel.prev();
	node->next() = &_sentinel;
	_sentinel.prev() = node;
}


template <class Key>
template <typename Allocator>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::erase(const_iterator position, Allocator allocator)
{
	typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;
	typedef Key														T; // required by FT_DLLNODE

	base_type	*erasedNode = position._currentNode;
	node_allocator_type nodeAllocator(allocator);

	++position;
	erasedNode->prev()->next() = erasedNode->next();
	erasedNode->next()->prev() = erasedNode->prev();
	nodeAllocator.destroy(FT_DLLNODE(erasedNode));
	nodeAllocator.deallocate(FT_DLLNODE(erasedNode), 1);
	return iterator(position._currentNode);
}


template <class Key>
template <typename Allocator, typename Predicate>
typename ft::internal::bucket<Key>::size_type
ft::internal::bucket<Key>::erase(key_type CREF key, Allocator allocator, Predicate pred)
{
	typedef Key														T; // required by FT_DLLNODE

	size_type	erased = 0;
	for (base_type *it = _sentinel.next(); it != &_sentinel;) {
		base_type *nextNode = it->next();
		if (pred(FT_DLLNODE(it)->value, key)) {
			erase(const_iterator(it), allocator);
			++erased;
		}
		it = nextNode;
	}
	return erased;
}


// Helper Methods
template <class Key>
template <typename Allocator>
typename ft::internal::bucket<Key>::base_type*
ft::internal::bucket<Key>::createNode(value_type CREF val, Allocator allocator) const
{
	typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;

	node_type	*node;
	node_allocator_type nodeAllocator(allocator);
	TRY_ALLOC( node = nodeAllocator.allocate(1);,;);
	nodeAllocator.construct(node, node_type(val));
	return node;
}


template <class Key>
template <typename Allocator>
void
ft::internal::bucket<Key>::duplicate(base_type *newSentinel, Allocator allocator) const
{
	typedef Key	T;

	base_type*	newIt = newSentinel;
	base_type*	srcIt = _sentinel.next();

	while (srcIt != &_sentinel) {
		newIt->next() = createNode(FT_DLLNODE(srcIt)->value, allocator);
		newIt->next()->prev() = newIt;
		newIt = newIt->next();
		srcIt = srcIt->next();
	}
	newIt->next() = newSentinel;
	newSentinel->prev() = newIt;
}


template <class Key>
void
ft::internal::bucket<Key>::swap(bucket REF x)
{
	bool tEmpty = &this->_sentinel == this->_sentinel.next();
	bool xEmpty = &x->_sentinel == x->_sentinel.next();
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
	base_type* emptySentinel = (tEmpty) ? &this->_sentinel : &x._sentinel;
	base_type* otherSentinel = (tEmpty) ? &x._sentinel : &this->_sentinel;
	emptySentinel->next() = otherSentinel->next();
	emptySentinel->prev() = otherSentinel->prev();
	otherSentinel->next() = otherSentinel->prev() = otherSentinel;
	emptySentinel->next()->prev() = emptySentinel;
	emptySentinel->prev()->next() = emptySentinel;
}


template <class Key>
template <typename Allocator>
void
ft::internal::bucket<Key>::clear(Allocator allocator)
{
	typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;
	typedef Key														T; // required by FT_DLLNODE

	node_allocator_type nodeAllocator(allocator);
	base_type	*nodeIterator = _sentinel.next();
	while (nodeIterator != &_sentinel) {
		base_type	*nextNode = nodeIterator->next();
		node_type	*toDelete = FT_DLLNODE(nodeIterator);
		nodeAllocator.destroy(toDelete);
		nodeAllocator.deallocate(toDelete, 1);
		nodeIterator = nextNode;
	}
	_sentinel.next() = _sentinel.prev() = &_sentinel;
}


//
//	hashmap<Key, Hash, KeyEqual, Allocator>
//


// Constructors
template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::hashmap(hashmap CREF rhs)
	: _bucketArray(NULL)
	, _bucketNum(rhs._bucketNum)
	, _elemNum(rhs._bucketNum)
	, _first(NULL, 0, 0, NULL)
	, _maxLoadFactor(rhs._maxLoadFactor)
	, _hasher(rhs._hasher)
	, _equal(rhs._equal)
	, _allocator(rhs._allocator)
{
	*this = rhs;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators> REF
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::operator = (hashmap CREF rhs)
{
	if (this != &rhs) {
		if (_bucketArray)
			_deallocate();
		_bucketArray = NULL;
		_bucketNum = rhs._bucketNum;
		_elemNum = rhs._elemNum;
		_maxLoadFactor = rhs._maxLoadFactor;
		_hasher = rhs._hasher;
		_equal = rhs._equal;
		_allocator = rhs._allocator;
		_init(_bucketNum);
		for (size_type i = 0; i < _bucketNum; ++i)
			rhs._bucketArray[i].duplicate(&_bucketArray[i]._sentinel);
		_first = iterator(
			_bucketArray,
			_bucketNum,
			rhs._first._bucket_idx,
			_bucketArray[rhs._first._bucket_idx]._sentinel.next()
		);
	}
	return *this;
}

// Capacity
template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
bool
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::empty() const
{
	return _elemNum == 0;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::size() const
{
	return _elemNum;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::max_size() const
{
	return _allocator.max_size();
}


// Iterators
template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::begin()
{
	return _first;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::begin() const
{
	return const_iterator(_first);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::local_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::begin(size_type n)
{
	return _bucketArray[n].begin();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_local_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::begin(size_type n) const
{
	return _bucketArray[n].begin();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::cbegin() const
{
	return const_iterator(_first);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_local_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::cbegin(size_type n) const
{
	return _bucketArray[n].begin();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::end()
{
	return iterator(_bucketArray, _bucketNum, _bucketNum, NULL);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::end() const
{
	return const_iterator(_bucketArray, _bucketNum, _bucketNum, NULL);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::local_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::end(size_type n)
{
	return _bucketArray[n].end();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_local_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::end(size_type n) const
{
	return _bucketArray[n].end();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::cend() const
{
	return const_iterator(_bucketArray, _bucketNum, _bucketNum, NULL);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_local_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::cend(size_type n) const
{
	return _bucketArray[n].end();
}


// Element Lookup
template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::find(key_type CREF key)
{
	index_type index = KeyHasher<extractKey, Key>(_hasher)(key) % _bucketNum;
	for (local_iterator it = _bucketArray[index].begin(); it != _bucketArray[index].end(); ++it)
		if (KeyComparator<extractKey, KeyEqual>(_equal)(key, *it))
			return iterator(_bucketArray, _bucketNum, index, it._currentNode);
	return end();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::find(key_type CREF key) const
{
	index_type index = KeyHasher<extractKey, Key>(_hasher)(key) % _bucketNum;
	for (local_iterator it = _bucketArray[index].begin(); it != _bucketArray[index].end(); ++it)
		if (KeyComparator<extractKey, KeyEqual>(_equal)(key, *it))
			return iterator(_bucketArray, _bucketNum, index, it._currentNode);
	return end();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::count(key_type CREF key) const
{
	index_type	index = KeyHasher<extractKey, Key>(_hasher)(key) % _bucketNum;
	size_type	count = 0;
	for (local_iterator it = _bucketArray[index].begin(); it != _bucketArray[index].end(); ++it)
		if (KeyComparator<extractKey, KeyEqual>(_equal)(key, *it))
			++count;
	return count;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
ft::utility<typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::iterator>
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::equal_range(key_type CREF key)
{
	iterator	first = find(key);
	if (first == end())
		return make_pair(end(), end());
	local_iterator	local_end = end(first._bucket_idx);
	local_iterator	last(first._curr);
	KeyComparator<extractKey, KeyEqual> predicate(_equal);
	while (last != local_end
		&& predicate(key, *last))
		++last;
	return make_pair(first, --last);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
ft::utility<typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::const_iterator>
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::equal_range(key_type CREF key) const
{
	const_iterator	first = find(key);
	if (first == end())
		return make_pair(end(), end());
	const_local_iterator	local_end = end(first._bucket_idx);
	const_local_iterator	last(first._curr);
	KeyComparator<extractKey, KeyEqual> predicate(_equal);
	while (last != local_end
		&& predicate(key, *last))
		++last;
	return make_pair(first, --last);
}



// Modifiers
template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::insert(value_type CREF value)
{
	if (_shouldRehash(1))
		rehash(_bucketNum + 1);
	index_type		index = KeyHasher<extractKey, Hash>(_hasher)(value) % _bucketNum;
	local_iterator	localInserted = _bucketArray[index].insert(value, _allocator, KeyComparator<extractKey, KeyEqual>(_equal));
	iterator		mapInserted = iterator(_bucketArray, _bucketNum, index, localInserted._currentNode);
	++_elemNum;
	if (_first == end()
		|| mapInserted._bucket_idx < _first._bucket_idx)
		_first = mapInserted;
	return mapInserted;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::insert(const_iterator hint, value_type CREF value)
{
	(void)hint;
	return insert(value);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
template <class InputIt>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::insert(InputIt first, InputIt last)
{
	size_type newElem = ft::distance(first, last);
	_elemNum += newElem;
	if (_shouldRehash(newElem))
		rehash((_elemNum + newElem) / _maxLoadFactor);
	while (first != last) {
		insert(*first);
		++first;
	}
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::erase(const_iterator position)
{
	--_elemNum;
	if (position == _first)
		++_first;
	return position._bucket[position._bucket_idx].erase(position, _allocator);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::erase(key_type CREF key)
{
	while (_first != end() && KeyComparator<extractKey, KeyEqual>(_equal)(key, *_first))
		++_first;
	size_type removed = _bucketArray[bucket(key)].erase(key, _allocator, _equal);
	return removed;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::iterator
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::erase(const_iterator first, const_iterator last)
{
	if (first == _first)
		_first = ++iterator(last);
	while (first != last) {
		--_elemNum;
		++first;
	}
	return last;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::clear()
{
	for (array_type it = _bucketArray; it != _bucketArray + _bucketNum; ++it)
		it->clear(_allocator);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::swap(this_type REF rhs)
{
	ft::swap(_bucketArray, rhs._bucketArray);
	ft::swap(_bucketNum, rhs._bucketNum);
	ft::swap(_elemNum, rhs._elemNum);
	ft::swap(_first, rhs._first);
	ft::swap(_maxLoadFactor, rhs._maxLoadFactor);
	ft::swap(_hasher, rhs._hasher);
	ft::swap(_equal, rhs._equal);
	ft::swap(_allocator, rhs._allocator);
}


// Buckets
template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::bucket_count() const
{
	return _bucketNum;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::max_bucket_count() const
{
	return _bucketAllocator().max_size();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::bucket_size(size_type n) const
{
	return _bucketArray[n].size();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::bucket(key_type CREF key) const
{
	return KeyHasher<extractKey, Hash>(_hasher)(key) % _bucketNum;
}


// Hash policy
template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
float
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::load_factor() const
{
	return static_cast<float>(_elemNum) / static_cast<float>(_bucketNum);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
float
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::max_load_factor() const
{
	return _maxLoadFactor;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::max_load_factor(float f)
{
	float const oldLoadFactor = _maxLoadFactor;
	_maxLoadFactor = ft::clamp(f, 0.0f, 1.0f);
	if (!_shouldRehash(0))
		return;
	float const increase = oldLoadFactor / _maxLoadFactor;
	rehash(_bucketNum * increase);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::rehash(size_type n)
{
	typedef ft::internal::_doublyLinkedListBase base_type;
	typedef Key	T;

	if (n < _bucketNum)
		return;
	size_type newSize = _bucketNum;
	while (newSize < n)
		newSize *= 2;
	array_type newArray = _bucketAllocator().allocate(newSize);
	// Rehash the new hashmap without any copy, we steal the nodes
	for (size_type i = 0; i < newSize; ++i)
		::new(static_cast<void*>(newArray + i)) bucket_type;
	for (size_type i = 0; i < _bucketNum; ++i) {
		base_type *buckSentinel = &_bucketArray[i]._sentinel;
		for (base_type *node = buckSentinel->next(); node != buckSentinel;) {
			base_type *nextNode = node->next();
			index_type index = KeyHasher<extractKey, Hash>(_hasher)(FT_DLLNODE(node)->value) % _bucketNum;
			newArray[index].insert(node);
			node = nextNode;
		}
	}
	for (size_type i = 0; i < _bucketNum; ++i) {
		_bucketArray[i].clear(_allocator);
		_bucketArray[i].~bucket_type();
	}
	// Swap and free old memory
	_bucketAllocator().deallocate(_bucketArray, _bucketNum);
	_bucketArray = newArray;
	_bucketNum = newSize;
	_first = iterator(_bucketArray, _bucketNum, 0, NULL);
	_first._getNextBucket();
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::reserve(size_type n)
{
	if (n <= bucket_count() * max_load_factor())
		return ;
	rehash(n);
}


// Observers
template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::hasher
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::hash_function() const
{
	return _hasher;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::key_equal
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::key_eq() const
{
	return _equal;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::allocator_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::get_allocator() const
{
	return _allocator;
}


// Helper Methods
template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::_init(size_type n)
{
	array_type newArray = _bucketAllocator().allocate(n);
	for (size_type i = 0; i < n; ++i)
		::new(static_cast<void*>(newArray + i)) bucket_type; // horrible war crimes I have to commit to default initialize my buckets
	ft::swap(_bucketArray, newArray);
	_bucketNum = n;
	_first = iterator(_bucketArray, _bucketNum, 0, NULL);
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator, typename extractKey, bool mutableIterators>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>::_deallocate()
{
	clear();
	for (array_type it = _bucketArray; it != _bucketArray + _bucketNum; ++it)
		_bucketAllocator().destroy(it);
	_bucketAllocator().deallocate(_bucketArray, _bucketNum);
}


#endif //HASHMAP_TPP
