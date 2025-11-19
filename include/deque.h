//
// Created by mscheman on 10/27/25.
//

#ifndef DEQUE_H
#define DEQUE_H

#include ".deque/block.h"
# define INIT_MAP_SIZE 8

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class deque
{
	public:
		// Friend
		class iterator;
		class const_iterator;

		// Typedefs
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef	size_t									size_type;
		typedef ptrdiff_t								difference_type;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		// typedef iterator								iterator;
		// typedef const_iterator							const_iterator;
		// typedef ft::reverse_iterator<iterator>			reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// Constructors
		explicit deque(allocator_type CREF alloc = allocator_type());
		// explicit deque(size_type n, value_type CREF val = value_type(), allocator_type CREF alloc = allocator_type());
		// template<class InputIt> deque (InputIt first, InputIt last, allocator_type CREF alloc = allocator_type());
		// deque(deque CREF x);
		// deque REF operator = (deque CREF x);

	private:
		// Typedefs
		typedef pointer		_block_t;
		typedef _block_t*	_map_t;
		typedef typename Allocator::template rebind<_map_t >::other _mapAllocator;

		// Helper Functions
		size_type				_blockSize() const;

		// Attributes
		_map_t					**_map;
		mutable allocator_type	_allocator;
		mutable _mapAllocator	_map_allocator;
		size_type				_size;
};

}

#include ".deque/deque.tpp"
#undef INIT_MAP_SIZE

#endif //DEQUE_H
