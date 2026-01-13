//
// Created by mscheman on 10/27/25.
//

#ifndef DEQUE_TPP
#define DEQUE_TPP

# define TTA template <class T, class Allocator = std::allocator<T> >

TTA ft::deque<T, Allocator>::deque(allocator_type CREF alloc)
	: _allocator(alloc), _size(0)
{
	_map = _map_allocator.allocate(DEQUE_ARRAY_SIZE);
	for (int i = 0; i < DEQUE_ARRAY_SIZE; ++i)
		_map_allocator.construct(_map + i, NULL)

}

// Private Helper Function
TTA typename ft::deque<T, Allocator>::size_type ft::deque<T, Allocator>::_blockSize() const {
	return ft::max(512 / sizeof(T), 1);
}

#include ".deque/dequeIterators.h"
#include ".deque/deque.tpp"

# undef TTA

#endif //DEQUE_TPP
