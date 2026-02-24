//
// Created by mscheman on 2/12/26.
//

#ifndef UNORDERED_MAP_HPP
#define UNORDERED_MAP_HPP


#include ".helper/hashmap.hpp"


#define UMP_DEFAULT_PARAMETERS_DECL size_type n = HASHMAP_INIT_SIZE, hasher CREF hash = hasher(), key_equal CREF equal = key_equal(), allocator_type CREF allocator = allocator_type()
#define UMP_DEFAULT_PARAMETERS size_type n, hasher CREF hash, key_equal CREF equal, allocator_type CREF allocator

# define UNORDERED_MAP_AT_EXCEPTION_MSG ("unordered_map::at(): no such key")
# define UNORDERED_MULTIMAP_AT_EXCEPTION_MSG ("unordered_multimap::at(): no such key")


namespace ft {


template <
	class Key,
	class T,
	class Hash = hash<Key>,
	class KeyEqual = equal_to<Key>,
	class Allocator = allocator<Key>
> class unordered_map
{
	protected:
		// Typedef
		typedef ft::internal::hashmap<ft::pair<const Key, T>, Hash, KeyEqual, Allocator, ft::true_type, true>	hashmap_type;

	public:
		// Typedefs
		typedef Key											key_type;
		typedef T											mapped_type;
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
		explicit 						unordered_map(UMP_DEFAULT_PARAMETERS_DECL);
		explicit 						unordered_map(allocator_type CREF allocator);
		template <class InputIt>		unordered_map(InputIt first, InputIt last, UMP_DEFAULT_PARAMETERS_DECL);
										unordered_map(unordered_map CREF rhs);
										unordered_map(unordered_map CREF rhs, allocator_type CREF allocator);
		unordered_map REF	operator	=(unordered_map CREF rhs);
		~unordered_map();

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

		// Element Access
		mapped_type REF		operator	[](key_type CREF key);
		mapped_type REF					at(key_type CREF key);
		mapped_type CREF				at(key_type CREF key) const;

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
		void							swap(unordered_map REF rhs);

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
	class T,
	class Hash = hash<Key>,
	class KeyEqual = equal_to<Key>,
	class Allocator = allocator<Key>
> class unordered_multimap
{
	protected:
		// Typedef
		typedef ft::internal::hashmap<ft::utility<const Key, T>, Hash, KeyEqual, Allocator, ft::true_type, true>	hashmap_type;

	public:
		// Typedefs
		typedef Key											key_type;
		typedef T											mapped_type;
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
		explicit 							unordered_multimap(UMP_DEFAULT_PARAMETERS_DECL);
		explicit 							unordered_multimap(allocator_type CREF allocator);
		template <class InputIt>			unordered_multimap(InputIt first, InputIt last, UMP_DEFAULT_PARAMETERS_DECL);
											unordered_multimap(unordered_multimap CREF rhs);
											unordered_multimap(unordered_multimap CREF rhs, allocator_type CREF allocator);
		unordered_multimap REF	operator	=(unordered_multimap CREF rhs);
		~unordered_multimap();

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

		// Element Access
		mapped_type REF		operator		[](key_type CREF key);
		mapped_type REF						at(key_type CREF key);
		mapped_type CREF					at(key_type CREF key) const;

		// Element Lookup
		iterator							find(key_type CREF key);
		const_iterator						find(key_type CREF key) const;
		size_type							count(key_type CREF key) const;
		ft::utility<iterator>					equal_range(key_type CREF key);
		ft::utility<const_iterator>			equal_range(key_type CREF key) const;

		// Modifiers
		iterator							insert(value_type CREF value);
		iterator							insert(const_iterator hint, value_type CREF value);
		template <class InputIt>
		void								insert(InputIt first, InputIt last);
		iterator							erase(const_iterator position);
		size_type							erase(key_type CREF key);
		iterator							erase(const_iterator first, const_iterator last);
		void								clear();
		void								swap(unordered_multimap REF rhs);

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


#include ".containers/unordered_map.tpp"


# undef UNORDERED_MULTIMAP_AT_EXCEPTION_MSG
# undef UNORDERED_MAP_AT_EXCEPTION_MSG
# undef UMP_DEFAULT_PARAMETERS
# undef UMP_DEFAULT_PARAMETERS_DECL

#endif //UNORDERED_MAP_HPP