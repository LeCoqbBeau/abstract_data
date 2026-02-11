//
// Created by mscheman on 2/5/26.
//

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "ftdef.hpp"
#include "functional.hpp"
#include "ftexcept.hpp"
#include "pair.hpp"
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

	// Constructor
	bucket() { _sentinel.next() = _sentinel.prev() = &_sentinel; }
	~bucket() { if (_sentinel.next() != &_sentinel) throw ft::runtime_error("Memory is leaked!"); }

	// Iterators
	iterator		begin();
	const_iterator	begin() const;
	const_iterator	cbegin() const;
	iterator		end();
	const_iterator	end() const;
	const_iterator	cend() const;

	// Methods
	size_type		size() const;

	template <typename Predicate>
	iterator		find(key_type CREF key, Predicate predicate);

	template <typename Allocator>
	iterator		insert(value_type CREF val, Allocator allocator);

	template <typename Allocator>
	iterator		erase(const_iterator position, Allocator allocator);
	template <typename Allocator, typename Predicate>
	size_type		erase(key_type CREF key, Allocator allocator, Predicate pred);

	// Helper Methods
	template <typename Allocator>
	base_type		*createNode(key_type CREF val, Allocator allocator) const;

	template <typename Allocator>
	void			clear(Allocator allocator);

	//	Attributes
	base_type				_sentinel;
};


template <typename T, typename Ref, typename Ptr>
struct hashmap_iterator
	: iterator<ft::bidirectional_iterator_tag, T, ft::ptrdiff_t, Ptr, Ref>
{
	// Typedefs
	typedef hashmap_iterator<T, Ref, Ptr>		this_type;
	typedef T									value_type;
	typedef Ref									reference;
	typedef Ptr									pointer;
	typedef ft::ptrdiff_t						difference_type;
	typedef ft::internal::_doublyLinkedList<T>	node_type;
	typedef ft::internal::_doublyLinkedListBase	base_type;
	typedef ft::internal::bucket<T>				bucket_type;

	// Constructors
	explicit	hashmap_iterator(bucket_type *bucket, ft::size_t bucket_count, ft::size_t idx, base_type *current = NULL) {
		_bucket = bucket;
		_bucket_count = bucket_count;
		_bucket_idx = idx;
		_curr = current;
		if (_curr)
			return;
		for (; _bucket_idx < bucket_count; ++_bucket_idx) {
			if (_bucket[_bucket_idx].begin() == _bucket[_bucket_idx].end())
				continue;
			_curr = _bucket[_bucket_idx].begin()._currentNode;
			return;
		}
	}

	hashmap_iterator(iterator<T, T REF, T*> CREF rhs) : _curr(rhs._curr), _bucket(rhs._bucket), _bucket_idx(rhs._bucket_idx), _bucket_count(rhs._bucket_count) {}
	~hashmap_iterator() {}

	// In/Equality Operator
	template <class U, class URef, class UPtr>
	bool operator	== (hashmap_iterator<U, URef, UPtr> CREF rhs) { return _bucket == rhs._bucket && this->_curr == rhs._curr; }
	template <class U, class URef, class UPtr>
	bool operator	!= (hashmap_iterator<U, URef, UPtr> CREF rhs) { return _bucket != rhs._bucket && this->_curr != rhs._curr; }

	// Dereference Operator
	reference	operator  * () { return FT_DLLNODE(_curr)->value; }
	pointer		operator -> () { return &(operator*()); }

	// Shift Operators
	this_type REF	operator ++ () {
		_curr = _curr->next();
		if (dynamic_cast<node_type*>(_curr) == NULL) {

		}
		return *this;
	}
	this_type		operator ++ (int) { this_type tmp = *this; operator++(); return tmp; }

	// Attributes
	base_type*		_curr;
	bucket_type*	_bucket;
	ft::size_t		_bucket_idx;
	ft::size_t		_bucket_count;
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
		typedef hashmap<Key, Hash, KeyEqual, Allocator>					this_type;
		typedef typename Hash::result_type								index_type;
		typedef bucket<Key>												bucket_type;
		typedef bucket_type*											array_type;
		typedef typename Allocator::template rebind<bucket_type>::other	array_allocator_type;

	public:
		//  Typedefs
		typedef Key														key_type;
		typedef Key														value_type;
		typedef Hash													hasher;
		typedef KeyEqual												key_equal;
		typedef Allocator												allocator_type;
		typedef Key REF													reference;
		typedef Key CREF												const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef void													iterator;
		typedef void													const_iterator;
		typedef typename bucket_type::iterator							local_iterator;
		typedef typename bucket_type::const_iterator					const_local_iterator;
		typedef ft::size_t												size_type;
		typedef ft::ptrdiff_t											difference_type;

		// Constructor
		hashmap(hasher CREF hash = hasher(), key_equal CREF equal = key_equal(), allocator_type CREF allocator = allocator_type())
			: _array(NULL), _arraySize(0), _size(0), _hasher(hash), _equal(equal), _allocator(allocator)
		{ _init(HASHMAP_INIT_SIZE); }
		~hashmap() { _deallocate(); };

		// Modifiers
		bool						empty() const;
		size_type					size() const;
		size_type					max_size() const;

		// Iterators
		iterator					begin();
		const_iterator				begin() const;
		local_iterator				begin(size_type n);
		const_local_iterator		begin(size_type n) const;
		iterator					end();
		const_iterator				end() const;
		local_iterator				end(size_type n);
		const_local_iterator		end(size_type n) const;

		// Modifiers
		iterator					insert(value_type CREF value);
		iterator					insert(const_iterator hint, value_type CREF value);
		template <class InputIt>
		void						insert(InputIt first, InputIt last);
		iterator					erase(const_iterator position);
		size_type					erase(key_type CREF key);
		iterator					erase(const_iterator first, const_iterator last);
		void						clear();
		void						swap(this_type REF rhs);

		// Buckets
		size_type					bucket_count() const;
		size_type					max_bucket_count() const;
		size_type					bucket_size(size_type n) const;
		size_type					bucket(key_type CREF key) const;

		// Hash Policy
		float						load_factor() const;
		float						max_load_factor() const;
		void						max_load_factor(float f);
		void						rehash(size_type n);
		void						reserve(size_type n);

		// Observers
		hasher						hash_function() const;
		key_equal					key_eq() const;
		allocator_type				get_allocator() const noexcept;

	protected:
		// Helper Member Function
		void		_init(size_type n);
		void		_reallocate(size_type n);
		void		_deallocate();

		// Attributes
		array_type				_array;
		size_type				_arraySize;
		size_type				_size;
		hasher					_hasher;
		key_equal				_equal;
		mutable allocator_type	_allocator;
		array_allocator_type	_arrayAllocator() const { return array_allocator_type(_allocator); }
};


} // internal
} // ft


#include "hashmap.tpp"


#endif //HASHMAP_HPP
