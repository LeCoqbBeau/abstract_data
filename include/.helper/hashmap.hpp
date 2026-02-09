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


template <class T, class Ref, class Ptr>
struct bucketIterator
{
	// Typedef
	typedef bucketIterator<T, Ref, Ptr>		this_type;
	typedef T								value_type;
	typedef Ref								reference;
	typedef Ptr								pointer;
	typedef ft::ptrdiff_t					difference_type;
	typedef _doublyLinkedList<value_type>*	node_type;

	// Constructor
	explicit	bucketIterator(node_type node = 0) : _iterator(node) {};
	bucketIterator(bucketIterator<T, T REF, T*> CREF rhs) : _iterator(rhs._iterator) {};
	~bucketIterator() {};

	// In/Equality Operator
	template <class U, class URef, class UPtr>
	bool operator	== (bucketIterator<U, URef, UPtr> CREF rhs) { return this->_iterator == rhs._iterator; }
	template <class U, class URef, class UPtr>
	bool operator	!= (bucketIterator<U, URef, UPtr> CREF rhs) { return this->_iterator != rhs._iterator; }

	// Dereference Operator
	reference	operator  * () { return _iterator.operator*(); }
	pointer		operator -> () { return _iterator.operator->(); }

	// Shift Operators
	this_type REF	operator ++ () { ++_iterator; return *this; }
	this_type		operator ++ (int) { this_type tmp(*this); operator++(); return tmp; }

protected:
	// Attributes
	_doublyLinkedListIterator<T, Ref, Ptr>	_iterator;
};


template <
	class Key,
	class Hash = ft::hash<Key>,
	class KeyEqual = ft::equal_to<Key>,
	class Allocator = ft::allocator<Key>
>
struct bucket {
	//  Typedefs
	typedef Key															key_type;
	typedef Key															value_type;
	typedef Hash														hasher;
	typedef KeyEqual													key_equal;
	typedef Allocator													allocator_type;
	typedef Key REF														reference;
	typedef Key CREF													const_reference;
	typedef typename allocator_type::pointer							pointer;
	typedef typename allocator_type::const_pointer						const_pointer;
	typedef _doublyLinkedListIterator<Key, Key REF, Key *>				iterator;
	typedef _doublyLinkedListIterator<Key, Key CREF, Key const*>		const_iterator;
	typedef ft::size_t													size_type;
	typedef ft::ptrdiff_t												difference_type;
	typedef _doublyLinkedList<Key>										node_type;
	typedef typename allocator_type::template rebind<node_type >::other	node_allocator_type;

	// Iterators
	iterator		begin();
	const_iterator	begin() const;
	const_iterator	cbegin() const;
	iterator		end();
	const_iterator	end() const;
	const_iterator	cend() const;

	// Methods
	size_type		size() const;
	iterator		insert(value_type CREF val);

	// Helper Methods
	node_type	_createNode(key_type CREF val) const;

	//	Attributes
	node_type				_sentinel;
	hasher					_hasher;
	key_equal				_equal;
	mutable allocator_type	_allocator;
	node_allocator_type		_nodeAllocator() const { return _node_allocator_type(_allocator); }
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
		typedef bucket<Key, Hash, KeyEqual, Allocator>	bucket_type;

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
