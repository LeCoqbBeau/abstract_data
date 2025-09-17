//
// Created by mscheman on 9/8/25.
//

#ifndef LIST_H
#define LIST_H

#include "ft_namespace.h"
#include "DoublyLinkedList.h"

#include <memory>

template<class T, class Allocator = std::allocator<T> >
class ft::list {
	public:
		// Typedefs
		typedef T									value_type;
		typedef Allocator							allocator_type;
		typedef	size_t								size_type;
		typedef long int							difference_type;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef void								iterator;
		typedef void								const_iterator;
		typedef void								reverse_iterator;
		typedef void								const_reverse_iterator;

		// Constructors & Destructors
		explicit list(allocator_type CREF alloc = allocator_type());
		explicit list(size_type n, value_type CREF val = value_type(), allocator_type CREF alloc = allocator_type());
		// template <class InputIterator> list (InputIterator first, InputIterator last, allocator_type CREF alloc = allocator_type());
		list(list CREF x);
		list REF operator = (list CREF x);
		~list();

		// Iterators

		// Capacity
		bool empty() const;
		size_type size() const;
		// size_type max_size() const; // what da hell???

		// Element Access
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		// Modifiers
		void assign(size_type count, value_type CREF value);
		// template<class InputIt> void assign(InputIt first, InputIt last);
		void push_front(value_type CREF val);


		// Observers
		allocator_type get_allocator() const;

	private:
		// Typedef
		typedef DoublyLinkedList<pointer>			*_node;

		// Helper methods
		void										_assignHelper(size_type n, value_type CREF val);
		void										_clearHelper();

		// Attributes
		_node										_frontData;
		_node										_backData;
		allocator_type								_allocator;
		size_type									_size;

};

#include "list.tpp"

#endif //LIST_H
