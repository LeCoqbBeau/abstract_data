//
// Created by mscheman on 2/5/26.
//

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "ftdef.hpp"
#include "functional.hpp"


# define HASHMAP_INIT_SIZE 16


namespace ft { namespace internal {


template <
	class Key,
	class Hash = ft::hash<Key>,
	class KeyEqual = ft::equal_to<Key>,
	class Allocator = ft::allocator<Key>
>
struct hashmap {
	//  Typedefs
	typedef Key										key_type;
	typedef Key										value_type;
	typedef Hash									hasher;
	typedef KeyEqual								key_equal;
	typedef Allocator								allocator_type;
	typedef Key REF									reference;
	typedef Key CREF								const_reference;
	typedef typename allocator_type::pointer		pointer;
	typedef typename allocator_type::const_pointer	const_pointer;
	typedef void									iterator;
	typedef void									const_iterator;
	typedef void									local_iterator;
	typedef void									const_local_iterator;
	typedef ft::size_t								size_type;
	typedef ft::ptrdiff_t							difference_type;

	// Constructor
	hashmap(hasher CREF hash = hasher(), key_equal CREF equal = key_equal(), allocator_type CREF allocator = allocator_type())
		: _hasher(hash), _equal(equal), _allocator(allocator)
		{ _init(HASHMAP_INIT_SIZE); }
	~hashmap();

	// Modifiers
	void clear();


	// Helper Typedefs
	typedef hashmap<Key, Hash, KeyEqual, Allocator>						this_type;
	typedef typename hasher::result_type								index_type;
	typedef typename allocator_type::template rebind<index_type>::other	index_allocator;
	typedef typename allocator_type::template rebind<value_type>::other	value_allocator;

	// Helper Static Attributes
	static const index_type npos;

	// Helper Member Function
	void		_init(size_type n);
	void		_reallocate(size_type n);

	// Attributes
	index_type*				_indices;
	value_type*				_array;
	size_type				_size;
	hasher					_hasher;
	key_equal				_equal;
	mutable allocator_type	_allocator;
	value_allocator			_indexAllocator() const { return index_allocator(_allocator); }
	value_allocator			_valueAllocator() const { return value_allocator(_allocator); }
};


} // internal
} // ft

template <class Key, class Hash, class KeyEqual, class Allocator>
const typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::index_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::npos = static_cast<ft::uint64_t>(-1);


#include "hashmap.tpp"


#endif //HASHMAP_HPP
