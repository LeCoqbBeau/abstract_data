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
		typedef T REF								reference;
		typedef T CREF								const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef void								iterator;
		typedef void								const_iterator;
		typedef void								reverse_iterator;
		typedef void								const_reverse_iterator;

		// Constructors
		explicit list(allocator_type CREF alloc = allocator_type());

	private:
		DoublyLinkedList<value_type>				*_data;
		allocator_type								_allocator;

};

template <class T, class Allocator>
ft::list<T, Allocator>::list(allocator_type CREF alloc) : _data(0), _allocator(alloc) {}

#endif //LIST_H
