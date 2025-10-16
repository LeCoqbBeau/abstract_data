//
// Created by mscheman on 9/8/25.
//

#ifndef LIST_H
#define LIST_H

#include "ft_namespace.h"
#include "list/DoublyLinkedList.h"

#include <memory>

template<class T, class Allocator = std::allocator<T> >
class ft::list {
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

	public:

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

		// Element Access
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		// Capacity
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		// Modifiers
		void assign(size_type count, value_type CREF value);
		template<class InputIt> void assign(InputIt first, InputIt last);
		void push_front(value_type CREF val);
		void pop_front();
		void push_back(value_type CREF val);
		void pop_back();
		iterator insert(iterator position, value_type CREF value );
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
		template <class BinaryPredicate> void unique(BinaryPredicate binary_pred);

		// Observers
		allocator_type get_allocator() const;

	private:
		// Typedef
		typedef DoublyLinkedList<value_type>		*_node;
		typedef typename Allocator::template rebind<DoublyLinkedList<value_type> >::other _nodeAllocator;

		// Helper methods
		_node										_createNode(value_type CREF val = value_type());
		void										_assignHelper(size_type n, value_type CREF val);
		template <class InputIt> void				_assignHelper(InputIt first, InputIt last);
		_node										_duplicate();
		void										_shrinkHelper(size_type n);
		void										_clearHelper();
		_node										_delBackHelper(_node node);
		static bool									_isNotUnique(value_type CREF curr, value_type CREF prev);
		_nodeAllocator								_getNodeAllocator();

		// Attributes
		_node										_sentinel;
		_nodeAllocator								_allocator;
		size_type									_size;

};

#include "list/listIterators.hpp"
#include "list/list.tpp"

#endif //LIST_H
