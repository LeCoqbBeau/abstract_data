//
// Created by mscheman on 10/27/25.
//

#ifndef DEQUE_H
#define DEQUE_H

#include ".helper/ftdef.hpp"
#include ".helper/iterator.hpp"
#include ".helper/type_traits.hpp"

# define DEQUE_ARRAY_SIZE 16

namespace ft {


template <typename T, typename Allocator>
class deque {
	protected:
		// Friend
		class iterator;
		class const_iterator;
		friend class iterator;
		friend class const_iterator;

	public:
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

	protected:
		T**		arrays;
};


}

#endif //DEQUE_H
