//
// Created by mscheman on 9/8/25.
//

#ifndef LIST_H
#define LIST_H

#include ".list/DoublyLinkedList.h"
#include ".helper/ftdef.h"
#include ".helper/iterator.h"
#include ".helper/type_traits.h"

namespace ft {

template<class T, class Allocator = std::allocator<T> >
class list {
	public:
		// Friend
		class iterator;
		class const_iterator;
		friend class iterator;
		friend class const_iterator;

		// Typedefs
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef	size_t									size_type;
		typedef ptrdiff_t								difference_type;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef iterator								iterator;
		typedef const_iterator							const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// Constructors & Destructors
		explicit list(allocator_type CREF alloc = allocator_type());
		explicit list(size_type n, value_type CREF val = value_type(), allocator_type CREF alloc = allocator_type());
		template<class InputIt> list (InputIt first, InputIt last, allocator_type CREF alloc = allocator_type());
		list(list CREF x);
		list REF operator = (list CREF rhs);
		~list();

		// Iterators
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		// Capacity
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		// Element Access
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		// Modifiers
		void assign(size_type count, value_type CREF value);
		template<class InputIt> void assign(InputIt first, InputIt last);
		void push_front(value_type CREF val);
		void pop_front();
		void push_back(value_type CREF val);
		void pop_back();
		iterator insert(iterator position, value_type CREF value);
		iterator insert(iterator position, size_type count, value_type CREF value);
		template<class InputIt> iterator insert(iterator position, InputIt first, InputIt last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(list REF x);
		void resize(size_type n, value_type CREF val = value_type());
		void clear();

		// Operations
		void splice(iterator position, list REF other);
		void splice(iterator position, list REF other, iterator it);
		void splice(iterator position, list REF other, iterator first, iterator last);
		void remove(value_type CREF val);
		template <class Predicate> void remove_if(Predicate pred);
		void unique();
		template <class BinaryPredicate> void unique(BinaryPredicate pred);
		void merge(list REF other);
		template <class Compare> void merge(list REF other, Compare comp);
		void sort();
		template <class Compare> void sort(Compare comp);
		void reverse();

		// Observers
		allocator_type get_allocator() const;

	private:
		// Typedef
		typedef DoublyLinkedList<value_type>		*_node;
		typedef typename Allocator::template rebind<DoublyLinkedList<value_type> >::other _nodeAllocator;

		// Helper methods
		_node										_createNode(value_type CREF val = value_type()) const;
		void										_assignHelper(size_type n, value_type CREF val, traits::true_type);
		template <class InputIt> void				_assignHelper(InputIt first, InputIt last, traits::false_type);
		iterator									_insertHelper(iterator position, list REF other);
		list										_insertHelper(size_type n, value_type CREF val, traits::true_type);
		template <class InputIt> list				_insertHelper(InputIt first, InputIt last, traits::false_type);
		_node										_duplicate() const;
		void										_shrinkHelper(size_type n);
		void										_clearHelper();
		_node										_delBackHelper(_node node);
		void										_swapNodes(_node a, _node b);
		template <class Compare> void				_initMergeSort(Compare comp);
		template <class Compare> _node				_split(Compare comp, _node head, size_type size);
		template <class Compare> _node				_merge( Compare comp,
															_node left, size_type leftSize,
															_node right, size_type rightSize );
		void										_cleanList(_node removed);
		_nodeAllocator								_getNodeAllocator();

		// Attributes
		_node										_sentinel;
		mutable _nodeAllocator						_allocator;
		size_type									_size;

};

template <typename T, typename Allocator>
void swap(list<T, Allocator> REF x, list<T, Allocator> REF y) {
	x.swap(y);
}

}

# define LIST_RELATIONAL_OPERATOR(op) template <class T, class Allocator> bool operator op					\
										(ft::list<T, Allocator> CREF lhs, ft::list<T, Allocator> CREF rhs)

LIST_RELATIONAL_OPERATOR(==) {
	if (lhs._size != rhs._size)
		return false;
	typename ft::list<T, Allocator>::iterator leftIt = lhs.begin();
	typename ft::list<T, Allocator>::iterator rightIt = rhs.begin();
	while (leftIt != lhs.end() && rightIt != rhs.end()) {
		if (*leftIt != *rightIt)
			return false;
		++leftIt;
		++rightIt;
	}
	return true;
}

LIST_RELATIONAL_OPERATOR(!=) {
	return !(lhs == rhs);
}

LIST_RELATIONAL_OPERATOR(<) {
	typename ft::list<T, Allocator>::iterator leftIt = lhs.begin();
	typename ft::list<T, Allocator>::iterator rightIt = rhs.begin();
	while (leftIt != lhs.end() && rightIt != rhs.end()) {
		if (*rightIt < *leftIt)
			return false;
		++leftIt;
		++rightIt;
	}
	return true;
}

LIST_RELATIONAL_OPERATOR(<=) {
	return !(rhs < lhs);
}

LIST_RELATIONAL_OPERATOR(>) {
	return (rhs < lhs);
}

LIST_RELATIONAL_OPERATOR(>=) {
	return !(lhs < rhs);
}

# undef LIST_RELATIONAL_OPERATOR

#include ".list/listIterators.hpp"
#include ".list/list.tpp"

#endif //LIST_H
