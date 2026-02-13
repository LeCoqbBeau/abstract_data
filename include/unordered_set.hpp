//
// Created by mscheman on 2/12/26.
//

#ifndef UNORDERED_SET_HPP
#define UNORDERED_SET_HPP


#include ".helper/hashmap.hpp"


#define UST_DEFAULT_PARAMETERS_DECL size_type n = HASHMAP_INIT_SIZE, hasher CREF hash = hasher(), key_equal CREF equal = key_equal(), allocator_type CREF allocator = allocator_type()
#define UST_DEFAULT_PARAMETERS size_type n, hasher CREF hash, key_equal CREF equal, allocator_type CREF allocator


namespace ft {


template <
	class Key,
	class Hash = hash<Key>,
	class KeyEqual = equal_to<Key>,
	class Allocator = allocator<Key>
> class unordered_set
{
	protected:
		// Typedef
		typedef ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, ft::false_type, false>	hashmap_type;

	public:
		// Typedefs
		typedef typename hashmap_type::key_type				key_type;
		typedef typename hashmap_type::value_type			value_type;
		typedef typename hashmap_type::hasher				hasher;
		typedef typename hashmap_type::key_equal			key_equal;
		typedef typename hashmap_type::allocator_type		allocator_type;
		typedef typename hashmap_type::reference			reference;
		typedef typename hashmap_type::const_reference		const_reference;
		typedef typename hashmap_type::pointer				pointer;
		typedef typename hashmap_type::const_pointer		const_pointer;
		typedef typename hashmap_type::iterator				iterator;
		typedef typename hashmap_type::const_iterator		const_iterator;
		typedef typename hashmap_type::local_iterator		local_iterator;
		typedef typename hashmap_type::const_local_iterator	const_local_iterator;
		typedef typename hashmap_type::size_type			size_type;
		typedef typename hashmap_type::difference_type		difference_type;

		// Constructors
		explicit 						unordered_set(UST_DEFAULT_PARAMETERS_DECL);
		explicit 						unordered_set(allocator_type CREF allocator);
		template <class InputIt>		unordered_set(InputIt first, InputIt last, UST_DEFAULT_PARAMETERS_DECL);
										unordered_set(unordered_set CREF rhs);
										unordered_set(unordered_set CREF rhs, allocator_type CREF allocator);
		unordered_set REF	operator	=(unordered_set CREF rhs);
		~unordered_set();

		// Capacity
		bool							empty() const;
		size_type						size() const;
		size_type						max_size() const;

		// Iterators
		iterator						begin();
		const_iterator					begin() const;
		local_iterator					begin(size_type n);
		const_local_iterator			begin(size_type n) const;
		const_iterator					cbegin() const;
		const_local_iterator			cbegin(size_type n) const;
		iterator						end();
		const_iterator					end() const;
		local_iterator					end(size_type n);
		const_local_iterator			end(size_type n) const;
		const_iterator					cend() const;
		const_local_iterator			cend(size_type n) const;

		// Element Lookup
		iterator						find(key_type CREF key);
		const_iterator					find(key_type CREF key) const;
		size_type						count(key_type CREF key) const;
		ft::utility<iterator>				equal_range(key_type CREF key);
		ft::utility<const_iterator>		equal_range(key_type CREF key) const;

		// Modifiers
		ft::utility<iterator, bool>		insert(value_type CREF value);
		iterator						insert(const_iterator hint, value_type CREF value);
		template <class InputIt>
		void							insert(InputIt first, InputIt last);
		iterator						erase(const_iterator position);
		size_type						erase(key_type CREF key);
		iterator						erase(const_iterator first, const_iterator last);
		void							clear();
		void							swap(unordered_set REF rhs);

		// Buckets
		size_type						bucket_count() const;
		size_type						max_bucket_count() const;
		size_type						bucket_size(size_type n) const;
		size_type						bucket(key_type CREF key) const;

		// Hash Policy
		float							load_factor() const;
		float							max_load_factor() const;
		void							max_load_factor(float f);
		void							rehash(size_type n);
		void							reserve(size_type n);

		// Observers
		hasher							hash_function() const;
		key_equal						key_eq() const;
		allocator_type					get_allocator() const;

	protected:
		// Attributes
		hashmap_type	_hashmap;
};


template <
	class Key,
	class Hash = hash<Key>,
	class KeyEqual = equal_to<Key>,
	class Allocator = allocator<Key>
> class unordered_multiset
{
	protected:
		// Typedef
		typedef ft::internal::hashmap<Key, Hash, KeyEqual, Allocator, ft::false_type, false>	hashmap_type;

	public:
		// Typedefs
		typedef typename hashmap_type::key_type				key_type;
		typedef typename hashmap_type::value_type			value_type;
		typedef typename hashmap_type::hasher				hasher;
		typedef typename hashmap_type::key_equal			key_equal;
		typedef typename hashmap_type::allocator_type		allocator_type;
		typedef typename hashmap_type::reference			reference;
		typedef typename hashmap_type::const_reference		const_reference;
		typedef typename hashmap_type::pointer				pointer;
		typedef typename hashmap_type::const_pointer		const_pointer;
		typedef typename hashmap_type::iterator				iterator;
		typedef typename hashmap_type::const_iterator		const_iterator;
		typedef typename hashmap_type::local_iterator		local_iterator;
		typedef typename hashmap_type::const_local_iterator	const_local_iterator;
		typedef typename hashmap_type::size_type			size_type;
		typedef typename hashmap_type::difference_type		difference_type;

		// Constructors
		explicit 							unordered_multiset(UST_DEFAULT_PARAMETERS_DECL);
		explicit 							unordered_multiset(allocator_type CREF allocator);
		template <class InputIt>			unordered_multiset(InputIt first, InputIt last, UST_DEFAULT_PARAMETERS_DECL);
											unordered_multiset(unordered_multiset CREF rhs);
											unordered_multiset(unordered_multiset CREF rhs, allocator_type CREF allocator);
		unordered_multiset REF	operator	=(unordered_multiset CREF rhs);
		~unordered_multiset();

		// Capacity
		bool								empty() const;
		size_type							size() const;
		size_type							max_size() const;

		// Iterators
		iterator							begin();
		const_iterator						begin() const;
		local_iterator						begin(size_type n);
		const_local_iterator				begin(size_type n) const;
		const_iterator						cbegin() const;
		const_local_iterator				cbegin(size_type n) const;
		iterator							end();
		const_iterator						end() const;
		local_iterator						end(size_type n);
		const_local_iterator				end(size_type n) const;
		const_iterator						cend() const;
		const_local_iterator				cend(size_type n) const;

		// Element Lookup
		iterator							find(key_type CREF key);
		const_iterator						find(key_type CREF key) const;
		size_type							count(key_type CREF key) const;
		ft::utility<iterator>					equal_range(key_type CREF key);
		ft::utility<const_iterator>			equal_range(key_type CREF key) const;

		// Modifiers
		ft::utility<iterator, bool>			insert(value_type CREF value);
		iterator							insert(const_iterator hint, value_type CREF value);
		template <class InputIt>
		void								insert(InputIt first, InputIt last);
		iterator							erase(const_iterator position);
		size_type							erase(key_type CREF key);
		iterator							erase(const_iterator first, const_iterator last);
		void								clear();
		void								swap(unordered_multiset REF rhs);

		// Buckets
		size_type							bucket_count() const;
		size_type							max_bucket_count() const;
		size_type							bucket_size(size_type n) const;
		size_type							bucket(key_type CREF key) const;

		// Hash Policy
		float								load_factor() const;
		float								max_load_factor() const;
		void								max_load_factor(float f);
		void								rehash(size_type n);
		void								reserve(size_type n);

		// Observers
		hasher								hash_function() const;
		key_equal							key_eq() const;
		allocator_type						get_allocator() const;

	protected:
		// Attributes
		hashmap_type	_hashmap;
};


}


#include ".containers/unordered_set.tpp"

#undef UST_DEFAULT_PARAMETERS
#undef UST_DEFAULT_PARAMETERS_DECL

#endif //UNORDERED_SET_HPP