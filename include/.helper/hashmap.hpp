//
// Created by mscheman on 2/5/26.
//

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "ftdef.hpp"
#include "functional.hpp"
#include "doublyLinkedList.hpp"


# define HASHMAP_INIT_SIZE 16


namespace ft { namespace internal {


template <class Key>
struct bucket {
	//  Typedefs
	typedef Key															key_type;
	typedef Key															value_type;
	typedef Key REF														reference;
	typedef Key CREF													const_reference;
	typedef _doublyLinkedListIterator<Key, Key REF, Key *>				iterator;
	typedef _doublyLinkedListIterator<Key, Key CREF, Key const*>		const_iterator;
	typedef ft::size_t													size_type;
	typedef ft::ptrdiff_t												difference_type;
	typedef _doublyLinkedListBase										base_type;
	typedef _doublyLinkedList<Key>										node_type;

	// Iterators
	iterator		begin();
	const_iterator	begin() const;
	const_iterator	cbegin() const;
	iterator		end();
	const_iterator	end() const;
	const_iterator	cend() const;

	// Methods
	size_type		size() const;

	template <typename Allocator>
	iterator		insert(value_type CREF val, Allocator allocator);
	
	template <typename Allocator>
	iterator		erase(const_iterator position, Allocator allocator);

	template <typename Allocator, typename Predicate>
	size_type		erase(key_type CREF key, Allocator allocator, Predicate pred);

	// Helper Methods
	template <typename Allocator>
	base_type		*createNode(key_type CREF val, Allocator allocator) const;

	//	Attributes
	base_type				_sentinel;
};


template <
	class Key,
	class Hash = ft::hash<Key>,
	class KeyEqual = ft::equal_to<Key>,
	class Allocator = ft::allocator<Key>
>
struct hashmap {
	protected:
		// Helper Typedefs
		typedef hashmap<Key, Hash, KeyEqual, Allocator>	this_type;
		typedef typename Hash::result_type				index_type;
		typedef bucket<Key>								bucket_type;

	public:
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
		typedef typename bucket_type::iterator			local_iterator;
		typedef typename bucket_type::const_iterator	const_local_iterator;
		typedef ft::size_t								size_type;
		typedef ft::ptrdiff_t							difference_type;

		// Constructor
		hashmap(hasher CREF hash = hasher(), key_equal CREF equal = key_equal(), allocator_type CREF allocator = allocator_type())
			: _hasher(hash), _equal(equal), _allocator(allocator)
			{ _init(HASHMAP_INIT_SIZE); }
		~hashmap();

		// Modifiers
		void clear();

	protected:
		// Helper Static Attributes
		static const index_type npos;

		// Helper Member Function
		void		_init(size_type n);
		void		_reallocate(size_type n);
		void		_deallocate();

		// Attributes
		value_type*				_array;
		size_type				_size;
		hasher					_hasher;
		key_equal				_equal;
		mutable allocator_type	_allocator;
};


} // internal
} // ft

template <class Key, class Hash, class KeyEqual, class Allocator>
const typename ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::index_type
ft::internal::hashmap<Key, Hash, KeyEqual, Allocator>::npos = static_cast<ft::uint64_t>(-1);


#include "hashmap.tpp"


#endif //HASHMAP_HPP
