//
// Created by mscheman on 2/5/26.
//

#ifndef HASHMAP_TPP
#define HASHMAP_TPP

#include ".helper/doublyLinkedList.hpp"
#include "hashmap.hpp"
#include "new.hpp"


// Iterators
template <class Key>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::begin()
{
	return _sentinel.next();
}


template <class Key>
typename ft::internal::bucket<Key>::const_iterator
ft::internal::bucket<Key>::begin() const
{
	return _sentinel.next();
}


template <class Key>
typename ft::internal::bucket<Key>::const_iterator
ft::internal::bucket<Key>::cbegin() const
{
	return _sentinel.next();
}


template <class Key>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::end()
{
	return &_sentinel;
}


template <class Key>
typename ft::internal::bucket<Key>::const_iterator
ft::internal::bucket<Key>::end() const
{
	return &_sentinel;
}


template <class Key>
typename ft::internal::bucket<Key>::const_iterator
ft::internal::bucket<Key>::cend() const
{
	return &_sentinel;
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
template <typename Allocator>
typename ft::internal::bucket<Key>::iterator
ft::internal::bucket<Key>::insert(value_type CREF val, Allocator allocator)
{
	base_type	*inserted = createNode(val, allocator);
	_sentinel.prev()->next() = inserted;
	inserted->prev() = _sentinel.prev();
	inserted->next() = &_sentinel;
	_sentinel.prev() = inserted;
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
	typedef typename Allocator::template rebind<value_type>::other	node_allocator_type;

	node_type	*node;
	node_allocator_type nodeAllocator(allocator);
	TRY_ALLOC( node = nodeAllocator.allocate(1);,;);
	nodeAllocator.construct(node, val);
	return node;
}


#endif //HASHMAP_TPP
