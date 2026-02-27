//
// Created by mscheman on 2/4/26.
//

#ifndef MAP_HPP
#define MAP_HPP

#include ".helper/ftdef.hpp"
#include ".helper/binary_trees.hpp"

# define MAP_AT_EXCEPTION_MSG ("map::at(): no such key")

namespace ft {

template <
	class Key,
	class T,
	class Compare = ft::less<Key>,
	class Allocator = ft::allocator<ft::pair<const Key, T> >
>
class map
{
	protected:
		// Typedefs
		typedef ft::internal::rbt<ft::pair<const Key, T>, Compare, Allocator, ft::true_type, true>	rbt_type;

	public:
		// Typedefs
		typedef	Key														key_type;
		typedef T														mapped_type;
		typedef	typename rbt_type::value_type							value_type;
		typedef	typename rbt_type::key_compare							key_compare;
		typedef	ft::internal::ValueComparator<Compare, ft::true_type>	value_compare;
		typedef	typename rbt_type::allocator_type						allocator_type;
		typedef	typename rbt_type::reference							reference;
		typedef	typename rbt_type::const_reference						const_reference;
		typedef	typename rbt_type::pointer								pointer;
		typedef	typename rbt_type::const_pointer						const_pointer;
		typedef	typename rbt_type::iterator								iterator;
		typedef	typename rbt_type::const_iterator						const_iterator;
		typedef	typename rbt_type::reverse_iterator						reverse_iterator;
		typedef	typename rbt_type::const_reverse_iterator				const_reverse_iterator;
		typedef	typename rbt_type::difference_type						difference_type;
		typedef	typename rbt_type::size_type							size_type;

		// Constructors
		explicit							map(key_compare CREF comp = key_compare(), allocator_type CREF allocator = allocator_type());
		template <typename InputIt>			map(InputIt first, InputIt last, key_compare CREF comp = key_compare(), allocator_type CREF allocator = allocator_type());
											map(map CREF rhs);
		map REF					operator	=(map CREF rhs);
		~map();

		// Iterators
		iterator							begin();
		const_iterator						begin() const;
		iterator							end();
		const_iterator						end() const;
		reverse_iterator					rbegin();
		const_reverse_iterator				rbegin() const;
		reverse_iterator					rend();
		const_reverse_iterator				rend() const;

		// Capacity
		bool								empty() const;
		size_type							size() const;
		size_type							max_size() const;

		// Element Access
		mapped_type REF			operator	[](key_type CREF key);
		mapped_type REF						at(key_type CREF key);
		mapped_type CREF					at(key_type CREF key) const;

		// Modifiers
		ft::pair<iterator, bool>			insert(value_type CREF val);
		iterator							insert(iterator position, value_type CREF val);
		template <typename InputIt> void	insert(InputIt first, InputIt last);
		void								erase(iterator position);
		size_type							erase(key_type CREF key);
		void								erase(iterator first, iterator last);
		void								swap(map REF other);
		void								clear();

		// Observers
		key_compare							key_comp() const;
		value_compare						value_comp() const;

		// Operations
		iterator							find(value_type CREF val);
		const_iterator						find(value_type CREF val) const;
		size_type							count(value_type CREF val) const;
		iterator							lower_bound(value_type CREF val) const;
		iterator							upper_bound(value_type CREF val) const;
		ft::pair<iterator>					equal_range(value_type CREF val) const;

		// Allocator
		allocator_type						get_allocator() const;

	protected:
		// Attributes
		rbt_type	_tree;
};


template <
	class Key,
	class T,
	class Compare = ft::less<Key>,
	class Allocator = ft::allocator<ft::pair<const Key, T> >
>
class multimap
{
	protected:
		// Typedefs
		typedef ft::internal::rbt<ft::pair<const Key, T>, Compare, Allocator, ft::true_type, true>	rbt_type;

	public:
		// Typedefs
		typedef	Key														key_type;
		typedef T														mapped_type;
		typedef	typename rbt_type::value_type							value_type;
		typedef	typename rbt_type::key_compare							key_compare;
		typedef	ft::internal::ValueComparator<ft::true_type, Compare>	value_compare;
		typedef	typename rbt_type::allocator_type						allocator_type;
		typedef	typename rbt_type::reference							reference;
		typedef	typename rbt_type::const_reference						const_reference;
		typedef	typename rbt_type::pointer								pointer;
		typedef	typename rbt_type::const_pointer						const_pointer;
		typedef	typename rbt_type::iterator								iterator;
		typedef	typename rbt_type::const_iterator						const_iterator;
		typedef	typename rbt_type::reverse_iterator						reverse_iterator;
		typedef	typename rbt_type::const_reverse_iterator				const_reverse_iterator;
		typedef	typename rbt_type::difference_type						difference_type;
		typedef	typename rbt_type::size_type							size_type;

		// Constructors
		explicit							multimap(key_compare CREF comp = key_compare(), allocator_type CREF allocator = allocator_type());
		template <typename InputIt>			multimap(InputIt first, InputIt last, key_compare CREF comp = key_compare(), allocator_type CREF allocator = allocator_type());
											multimap(multimap CREF rhs);
		multimap REF			operator	=(multimap CREF rhs);
		~multimap();

		// Iterators
		iterator							begin();
		const_iterator						begin() const;
		iterator							end();
		const_iterator						end() const;
		reverse_iterator					rbegin();
		const_reverse_iterator				rbegin() const;
		reverse_iterator					rend();
		const_reverse_iterator				rend() const;

		// Capacity
		bool								empty() const;
		size_type							size() const;
		size_type							max_size() const;

		// Modifiers
		iterator							insert(value_type CREF val);
		iterator							insert(iterator position, value_type CREF val);
		template <typename InputIt> void	insert(InputIt first, InputIt last);
		void								erase(iterator position);
		size_type							erase(key_type CREF key);
		void								erase(iterator first, iterator last);
		void								swap(multimap REF other);
		void								clear();

		// Observers
		key_compare							key_comp() const;
		value_compare						value_comp() const;

		// Operations
		iterator							find(value_type CREF val);
		const_iterator						find(value_type CREF val) const;
		size_type							count(value_type CREF val) const;
		iterator							lower_bound(value_type CREF val) const;
		iterator							upper_bound(value_type CREF val) const;
		ft::pair<iterator>					equal_range(value_type CREF val) const;

		// Allocator
		allocator_type						get_allocator() const;

	protected:
		// Attributes
		rbt_type	_tree;
};


# define MAP_COMPARISON_OPERATOR(op)	template <class T, class Container> bool operator op						\
										(ft::map<T, Container> CREF lhs, ft::map<T, Container> CREF rhs)

# define MMAP_COMPARISON_OPERATOR(op)	template <class T, class Container> bool operator op						\
										(ft::multimap<T, Container> CREF lhs, ft::multimap<T, Container> CREF rhs)

# define MAPS_COMPARISON_OPERATOR(op, stmt) MAP_COMPARISON_OPERATOR(op) {stmt;}; MMAP_COMPARISON_OPERATOR(op) {stmt;};

MAPS_COMPARISON_OPERATOR(==, { return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); });
MAPS_COMPARISON_OPERATOR(!=, { return !(lhs == rhs); });
MAPS_COMPARISON_OPERATOR(<,  { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); });
MAPS_COMPARISON_OPERATOR(<=, { return !(rhs < lhs); });
MAPS_COMPARISON_OPERATOR(>,  { return (rhs < lhs); });
MAPS_COMPARISON_OPERATOR(>=, { return !(lhs < rhs); });

#undef MAPS_COMPARISON_OPERATOR
#undef MAP_COMPARISON_OPERATOR
#undef MMAP_COMPARISON_OPERATOR


}


#include ".containers/map.tpp"


#undef MAP_AT_EXCEPTION_MSG


#endif //MAP_HPP
