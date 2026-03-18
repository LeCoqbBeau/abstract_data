//
// Created by mscheman on 2/5/26.
//

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include ".helper/ftdef.hpp"
#include ".helper/functional.hpp"
#include ".helper/ftexcept.hpp"
#include ".helper/utility.hpp"
#include ".helper/doubly_linked_list.hpp"

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
	typedef size_t														size_type;
	typedef ptrdiff_t													difference_type;
	typedef _doublyLinkedListBase										base_type;
	typedef _doublyLinkedList<Key>										node_type;

	// Constructor
	bucket() : _size(0) { _sentinel.next() = &_sentinel; _sentinel.prev() = &_sentinel; }
	bucket(bucket CREF) : _size(0) { _sentinel.next() = &_sentinel; _sentinel.prev() = &_sentinel; }
	~bucket() {}

	// Iterators
	iterator		begin();
	const_iterator	begin() const;
	const_iterator	cbegin() const;
	iterator		end();
	const_iterator	end() const;
	const_iterator	cend() const;

	// Methods
	size_type		size() const;

	template <typename Allocator, typename Predicate>
	iterator		insert(value_type CREF val, Allocator allocator, Predicate predicate);
	void			insert(base_type *node);

	template <typename Allocator>
	iterator		erase(const_iterator position, Allocator allocator);

	template <typename Allocator, typename Predicate>
	size_type		erase(key_type CREF key, Allocator allocator, Predicate pred);

	template <typename Allocator>
	base_type		*createNode(key_type CREF val, Allocator allocator) const;

	template <typename Allocator>
	void			duplicate(base_type *newSentinel, Allocator allocator) const;
	void			swap(bucket REF x);

	template <typename Allocator>
	void			clear(Allocator allocator);

	//	Attributes
	base_type		_sentinel;
	size_type		_size;
};


template <typename T, typename Ref, typename Ptr>
struct hashmap_iterator
	: iterator<forward_iterator_tag, T, ptrdiff_t, Ptr, Ref>
{
	// Typedefs
	typedef hashmap_iterator<T, Ref, Ptr>	this_type;
	typedef T								value_type;
	typedef Ref								reference;
	typedef Ptr								pointer;
	typedef ptrdiff_t						difference_type;
	typedef _doublyLinkedList<T>			node_type;
	typedef _doublyLinkedListBase			base_type;
	typedef bucket<T>						bucket_type;

	// Constructors
	explicit	hashmap_iterator() : _curr(NULL), _bucket(NULL), _bucket_count(0), _bucket_idx(0) {}
	explicit	hashmap_iterator(bucket_type *bucket, size_t bucket_count, size_t idx, base_type *current = NULL) {
		_bucket = bucket;
		_bucket_count = bucket_count;
		_bucket_idx = idx;
		_curr = current;
		if (_curr)
			return;
		_getNextBucket();
	}
	hashmap_iterator(hashmap_iterator<T, T REF, T*> CREF rhs) : _curr(rhs._curr), _bucket(rhs._bucket), _bucket_count(rhs._bucket_count), _bucket_idx(rhs._bucket_idx) {}
	~hashmap_iterator() {}

	// In/Equality Operator
	template <class U, class URef, class UPtr>
	bool operator	== (hashmap_iterator<U, URef, UPtr> CREF rhs) const { return _bucket == rhs._bucket && this->_curr == rhs._curr; }
	template <class U, class URef, class UPtr>
	bool operator	!= (hashmap_iterator<U, URef, UPtr> CREF rhs) const { return _bucket != rhs._bucket || this->_curr != rhs._curr; }

	// Dereference Operator
	reference	operator  * () { return FT_DLLNODE(_curr)->value; }
	pointer		operator -> () { return &(operator*()); }

	// Shift Operators
	this_type REF	operator ++ () {
		if (!_curr) {
			_getNextBucket();
			return *this;
		}
		if (_bucket_idx == _bucket_count)
			return *this;
		_curr = _curr->next();
		if (_curr == &_bucket[_bucket_idx]._sentinel)
			_getNextBucket();
		return *this;
	}
	this_type		operator ++ (int) { this_type tmp = *this; operator++(); return tmp; }

	// Helper Function
	void _getNextBucket() {
		if (_curr)
			++_bucket_idx;
		for (; _bucket_idx < _bucket_count; ++_bucket_idx) {
			if (_bucket[_bucket_idx]._size == 0)
				continue;
			_curr = _bucket[_bucket_idx]._sentinel.next();
			return;
		}
		_curr = NULL;
	}

	// Attributes
	base_type*		_curr;
	bucket_type*	_bucket;
	size_t			_bucket_count;
	size_t			_bucket_idx;
};


template <
	class Key,
	class Hash = hash<Key>,
	class KeyEqual = equal_to<Key>,
	class Allocator = allocator<Key>,
	typename extractKey = false_type,
	bool mutableIterators = false
>
struct hashmap {
	protected:
		// Helper Typedefs
		typedef hashmap<Key, Hash, KeyEqual, Allocator, extractKey, mutableIterators>	this_type;
		typedef typename Hash::result_type												index_type;
		typedef bucket<Key>																bucket_type;
		typedef bucket_type*															array_type;
		typedef typename Allocator::template rebind<bucket_type>::other					bucket_allocator_type;

	public:
		//  Typedefs
		typedef Key																		key_type;
		typedef Key																		value_type;
		typedef Hash																	hasher;
		typedef KeyEqual																key_equal;
		typedef Allocator																allocator_type;
		typedef Key REF																	reference;
		typedef Key CREF																const_reference;
		typedef typename allocator_type::pointer										pointer;
		typedef typename allocator_type::const_pointer									const_pointer;
		typedef hashmap_iterator<Key,
			CONDITIONAL_TT(mutableIterators, Key REF, Key CREF),
			CONDITIONAL_TT(mutableIterators, Key *, Key const*)
		>																				iterator;
		typedef hashmap_iterator<Key, Key CREF, Key const*>								const_iterator;
		typedef CONDITIONAL_TT(
			mutableIterators,
			typename bucket_type::iterator,
			typename bucket_type::const_iterator
		)																				local_iterator;
		typedef typename bucket_type::const_iterator									const_local_iterator;
		typedef size_t																	size_type;
		typedef ptrdiff_t																difference_type;

		// Constructor
		hashmap(size_type n = HASHMAP_INIT_SIZE, hasher CREF hash = hasher(), key_equal CREF equal = key_equal(), allocator_type CREF allocator = allocator_type())
			: _bucketArray(NULL), _bucketNum(0), _elemNum(0), _first(NULL, 0, 0, NULL), _maxLoadFactor(1), _hasher(hash), _equal(equal), _allocator(allocator)
		{ _init(n); }
		hashmap(hashmap CREF rhs);
		hashmap REF operator = (hashmap CREF rhs);
		~hashmap() { _deallocate(); };

		// Capacity
		bool						empty() const;
		size_type					size() const;
		size_type					max_size() const;

		// Iterators
		iterator					begin();
		const_iterator				begin() const;
		local_iterator				begin(size_type n);
		const_local_iterator		begin(size_type n) const;
		const_iterator				cbegin() const;
		const_local_iterator		cbegin(size_type n) const;
		const_iterator				end() const;
		iterator					end();
		local_iterator				end(size_type n);
		const_local_iterator		end(size_type n) const;
		const_iterator				cend() const;
		const_local_iterator		cend(size_type n) const;

		// Element Lookup
		iterator					find(key_type CREF key);
		const_iterator				find(key_type CREF key) const;
		size_type					count(key_type CREF key) const;
		pair<iterator>				equal_range(key_type CREF key);
		pair<const_iterator>		equal_range(key_type CREF key) const;

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
		allocator_type				get_allocator() const;

	protected:
		// Helper Member Function
		void						_init(size_type n);
		void						_deallocate();

		// Attributes
		array_type					_bucketArray;
		size_type					_bucketNum;
		size_type					_elemNum;
		iterator					_first;
		float						_maxLoadFactor;
		hasher						_hasher;
		key_equal					_equal;
		mutable allocator_type		_allocator;
		bucket_allocator_type		_bucketAllocator() const { return bucket_allocator_type(_allocator); }
		bool						_shouldRehash(size_type newElem) const { return _elemNum + newElem > _bucketNum * _maxLoadFactor; }
};


// Helper Class Definition
template <typename extractKey, typename Hash>
struct KeyHasher {};


template <typename Hash>
struct KeyHasher<false_type, Hash>  { // Don't extract keys
	explicit KeyHasher(Hash CREF hasher) : _hasher(hasher) {}
	template <typename T>	uint64_t operator()(T CREF x) const { return _hasher(x); }
	Hash CREF _hasher;
};


template <typename Hash>
struct KeyHasher<true_type, Hash>  { // Extract keys
	explicit KeyHasher(Hash CREF hasher) : _hasher(hasher) {}
	template <typename T>	uint64_t operator()(T CREF x) const { return _hasher(x.first); }
	Hash CREF _hasher;
};


template <typename extractKey, typename Comp>
struct KeyComparator {};


template <typename Comp>
struct KeyComparator<false_type, Comp>  { // Don't extract keys
	explicit KeyComparator(Comp CREF comp) : _comp(comp) {}
	template <typename T>	bool operator()(T CREF key, T CREF elem) const { return _comp(key, elem); }
	Comp CREF _comp;
};


template <typename Comp>
struct KeyComparator<true_type, Comp>  { // Extract keys
	explicit KeyComparator(Comp CREF comp) : _comp(comp) {}
	template <typename T>	bool operator()(T CREF key, T CREF elem) const { return _comp(key.first, elem.first); }
	Comp CREF _comp;
};


} // internal
} // ft


#include ".helper/hashmap.tpp"


#endif //HASHMAP_HPP
