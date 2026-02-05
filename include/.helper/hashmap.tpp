//
// Created by mscheman on 2/5/26.
//

#ifndef HASHMAP_TPP
#define HASHMAP_TPP

// Constructor
template <class Key, class Hash, class KeyEqual, class Allocator>
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::~hashmap()
{
	if (_array)
		clear();
	_elemAllocator().deallocate(_array, _size);
}

// Modifiers
template <class Key, class Hash, class KeyEqual, class Allocator>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::clear()
{
	for (size_type i = 0; i < _size; ++i)
		_elemAllocator().destroy(_array + i);
}

// Helper Member Functions
template <class Key, class Hash, class KeyEqual, class Allocator>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::_init(size_type n)
{
	if (n < HASHMAP_INIT_SIZE)
		n = HASHMAP_INIT_SIZE;
	ft::uint64_t	*newIndices;
	value_type		*newArray;
	TRY_ALLOC( newIndices = _indexAllocator().allocate(n);,;);
	ft::fill_n(newIndices, n, this_type::npos);
	TRY_ALLOC( newArray = _valueAllocator().allocate(n);, _indexAllocator().deallocate(newIndices, n); );
	_size = HASHMAP_INIT_SIZE;

}


template <class Key, class Hash, class KeyEqual, class Allocator>
void
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::_reallocate(size_type n)
{

}


#endif //HASHMAP_TPP
