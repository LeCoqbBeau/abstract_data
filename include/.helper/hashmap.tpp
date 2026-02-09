//
// Created by mscheman on 2/5/26.
//

#ifndef HASHMAP_TPP
#define HASHMAP_TPP

#include "new.hpp"


// Iterators
template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::iterator
ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::begin()
{
	return _sentinel.next;
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::const_iterator
ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::begin() const
{
	return _sentinel.next;
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::const_iterator
ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::cbegin() const
{
	return _sentinel.next;
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::iterator
ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::end()
{
	return _sentinel;
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::const_iterator
ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::end() const
{
	return _sentinel;
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::const_iterator
ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::cend() const
{
	return _sentinel;
}


// Methods
template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::size_type
ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::size() const
{
	size_type size = 0;
	node_type	it = _sentinel.next;
	while (it) {
		++size;
		++it;
	}
	return size;
}


template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::iterator
ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::insert(value_type CREF val)
{
	(void)val;
}


// Helper Methods
template <class Key, class Hash, class KeyEqual, class Allocator>
typename ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::node_type
ft::internal::bucket<Key, Hash, KeyEqual, Allocator>::_createNode(key_type CREF val) const
{
	node_type	node;
	TRY_ALLOC( node = _nodeAllocator().allocate(1);,;);
	_nodeAllocator().construct(node, val);
	return node;
}


#endif //HASHMAP_TPP
