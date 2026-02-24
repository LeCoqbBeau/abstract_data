//
// Created by mscheman on 2/4/26.
//

#ifndef SET_HPP
#define SET_HPP

#include ".helper/ftdef.hpp"
#include ".helper/binary_trees.hpp"

namespace ft {

template <
	class Key,
	class Compare = ft::less<Key>,
	class Allocator = ft::allocator<Key>
>
class set
{
	protected:
		// Typedefs
		typedef ft::internal::rbt<Key, Compare, Allocator, ft::false_type>	rbt_type;

	public:
		// Typedefs
		typedef	typename rbt_type::key_type					key_type;
		typedef	typename rbt_type::value_type				value_type;
		typedef	typename rbt_type::key_compare				key_compare;
		typedef	typename rbt_type::value_compare			value_compare;
		typedef	typename rbt_type::allocator_type			allocator_type;
		typedef	typename rbt_type::reference				reference;
		typedef	typename rbt_type::const_reference			const_reference;
		typedef	typename rbt_type::pointer					pointer;
		typedef	typename rbt_type::const_pointer			const_pointer;
		typedef	typename rbt_type::iterator					iterator;
		typedef	typename rbt_type::const_iterator			const_iterator;
		typedef	typename rbt_type::reverse_iterator			reverse_iterator;
		typedef	typename rbt_type::const_reverse_iterator	const_reverse_iterator;
		typedef	typename rbt_type::difference_type			difference_type;
		typedef	typename rbt_type::size_type				size_type;

		// Constructors
		explicit							set(key_compare CREF comp = key_compare(), allocator_type CREF allocator = allocator_type());
		template <typename InputIt>			set(InputIt first, InputIt last, key_compare CREF comp = key_compare(), allocator_type CREF allocator = allocator_type());
											set(set CREF rhs);
		set REF					operator	=  (set CREF rhs);
		~set();

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
		ft::pair<iterator, bool>			insert(value_type CREF val);
		iterator							insert(iterator position, value_type CREF val);
		template <typename InputIt> void	insert(InputIt first, InputIt last);
		void								erase(iterator position);
		size_type							erase(value_type CREF val);
		void								erase(iterator first, iterator last);
		void								swap(set REF other);
		void								clear();

		// Observers
		key_compare							key_comp() const;
		value_compare						value_comp() const;

		// Operations
		iterator							find(value_type CREF val) const;
		size_type							count(value_type CREF val) const;
		iterator							lower_bound(value_type CREF val) const;
		iterator							upper_bound(value_type CREF val) const;
		ft::pair<iterator>					equal_range(value_type CREF val) const;

		// Allocator
		allocator_type	get_allocator() const;

	protected:
		// Attributes
		rbt_type	_tree;
};


template <
	class Key,
	class Compare = ft::less<Key>,
	class Allocator = ft::allocator<Key>
>
class multiset
{
	protected:
		// Typedefs
		typedef ft::internal::rbt<Key, Compare, Allocator, ft::false_type, false>	rbt_type;

	public:
		// Typedefs
		typedef	typename rbt_type::key_type					key_type;
		typedef	typename rbt_type::value_type				value_type;
		typedef	typename rbt_type::key_compare				key_compare;
		typedef	typename rbt_type::value_compare			value_compare;
		typedef	typename rbt_type::allocator_type			allocator_type;
		typedef	typename rbt_type::reference				reference;
		typedef	typename rbt_type::const_reference			const_reference;
		typedef	typename rbt_type::pointer					pointer;
		typedef	typename rbt_type::const_pointer			const_pointer;
		typedef	typename rbt_type::iterator					iterator;
		typedef	typename rbt_type::const_iterator			const_iterator;
		typedef	typename rbt_type::reverse_iterator			reverse_iterator;
		typedef	typename rbt_type::const_reverse_iterator	const_reverse_iterator;
		typedef	typename rbt_type::difference_type			difference_type;
		typedef	typename rbt_type::size_type				size_type;

		// Constructors
		explicit							multiset(key_compare CREF comp = key_compare(), allocator_type CREF allocator = allocator_type());
		template <typename InputIt>			multiset(InputIt first, InputIt last, key_compare CREF comp = key_compare(), allocator_type CREF allocator = allocator_type());
											multiset(multiset CREF rhs);
		multiset REF			operator	=  (multiset CREF rhs);
		~multiset();

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
		size_type							erase(value_type CREF val);
		void								erase(iterator first, iterator last);
		void								swap(multiset REF other);
		void								clear();

		// Observers
		key_compare							key_comp() const;
		value_compare						value_comp() const;

		// Operations
		iterator							find(value_type CREF val) const;
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


}


#include ".containers/set.tpp"


#endif //SET_HPP
