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
template <typename Predicate>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::find(key_type CREF key, Predicate predicate)
{
	iterator it;
	for (it = begin(); it != end(); ++it)
		if (predicate(it, key))
			break;
	return it;
}


template <class Key>
template <typename Allocator>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::insert(value_type CREF val, Allocator allocator)
{
	base_type	*inserted = createNode(val, allocator);
	_sentinel.prev()->next() = inserted;
	inserted->prev() = _sentinel.prev();
	inserted->next() = &_sentinel;
	_sentinel.prev() = inserted;
	return iterator(inserted);
}


template <class Key>
template <typename Allocator>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::erase(const_iterator position, Allocator allocator)
{
	typedef typename Allocator::template rebind<value_type>::other	node_allocator_type;
	typedef Key														T; // required by FT_DLLNODE

	base_type	*erasedNode = position._currentNode;
	node_allocator_type nodeAllocator(allocator);

	++position;
	erasedNode->prev()->next() = erasedNode->next();
	erasedNode->next()->prev() = erasedNode->prev();
	allocator.destroy(FT_DLLNODE(erasedNode));
	allocator.deallocate(FT_DLLNODE(erasedNode), 1);
	return position;
}


template <class Key>
template <typename Allocator, typename Predicate>
typename ft::internal::bucket<Key>::size_type
ft::internal::bucket<Key>::erase(key_type CREF key, Allocator allocator, Predicate pred)
{
	typedef Key														T; // required by FT_DLLNODE

	size_type	erased = 0;
	for (base_type *it = _sentinel.next(); it != &_sentinel; ++it) {
		if (!pred(FT_DLLNODE(it), key))
			continue;
		erase(const_iterator(it), allocator);
		++erased;
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

// Capacity
template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
bool
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::empty() const
{
	return _size == 0;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::size() const
{
	return _size;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::size_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::max_size() const
{
	return _allocator.max_size();
}


// Iterators
template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::begin()
{
	return iterator();
}


template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::const_iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::begin() const
{
	return const_iterator();
}


template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::local_iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::begin(size_type n)
{
	return _array[n].begin();
}


template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::const_local_iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::begin(size_type n) const
{
	return _array[n].begin();
}


template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::end()
{
	return iterator();
}


template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::const_iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::end() const
{
	return const_iterator();
}


template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::local_iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::end(size_type n)
{
	return _array[n].end();
}


template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::const_local_iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::end(size_type n) const
{
	return _array[n].end();
}


// Modifiers
template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::insert(value_type CREF value)
{
	index_type	index = _hasher(value) % _arraySize;
	return _array[index].insert(value);
}


template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
typename ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::iterator
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::insert(const_iterator hint, value_type CREF value)
{
	(void)hint;
	index_type	index = _hasher(value) % _arraySize;
	return _array[index].insert(value);
}


template <typename Key, typename Hasher, typename KeyEqual, typename Allocator>
template <class InputIt>
void
ft::internal::hashmap<Key, Hasher, KeyEqual, Allocator>::insert(InputIt first, InputIt last)
{
	while (first != last) {
		insert(*first);
		++first;
	}
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::clear()
{
	for (array_type it = _array; it != _array + _arraySize; ++it)
		it->clear();
}


// Helper Methods
template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::_init(size_type n)
{
	size_type newSize = _size;
	while (newSize < n)
		newSize *= 2;
	value_type *tmpArray = _arrayAllocator().allocate(newSize + 1);
	tmpArray[newSize] = NULL;
	ft::swap(_array, tmpArray);
	_arrayAllocator().deallocate(tmpArray, _size);
	_size = newSize;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::_reallocate(size_type n)
{
	if (n < _size)
		return;
	size_type newSize = _size;
	while (newSize < n)
		newSize *= 2;
	array_type newArray = _arrayAllocator().allocate(newSize + 1);
	tmpArray[newSize] = NULL;
	for (array_type it = _array; it != _array + _arraySize; ++it)
		_arrayAllocator().construct(newArray + (it - _array), *it);
	_arrayAllocator().deallocate(_array);
	_size = newSize;
	_array = newArray;
}


template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::_deallocate()
{
	clear();
	for (array_type it = _array; it != _array + _arraySize + 1; ++it)
		_arrayAllocator().destroy(it);
	_arrayAllocator().deallocate(_array, _arraySize + 1);
}

#endif //HASHMAP_TPP
