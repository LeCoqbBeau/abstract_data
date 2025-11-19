//
// Created by mscheman on 10/27/25.
//

#ifndef BLOCK_H
#define BLOCK_H

#include ".helper/utils.h"
#include ".helper/algorithm.h"

TEMPLATE_T struct Block {
	// Constructors
	explicit Block(size_t const capacity = 16, int const dir = 1, std::allocator<T> allocator = std::allocator<T>())
		: capacity(capacity), dir(dir), alloc(allocator)
	{
		array = alloc.allocate(sizeof(T) * capacity);
		for (size_t i = 0; i < capacity; ++i)
			alloc.construct(array + i, T());
		if (this->dir > 0) {
			first = array;
			last = array;
			return;
		}
		if (this->dir < 0) {
			first = array + capacity - 1;
			last = array + capacity - 1;
			return;
		}
		first = array + capacity / 2;
		last = array + capacity / 2;
	}

	Block(Block CREF rhs)
		: capacity(rhs.capacity), dir(rhs.dir), alloc(rhs.alloc)
	{
		array = alloc.allocate(sizeof(T) * capacity);
		ft::copy_n(rhs.array, capacity, array);
		first = array + (rhs.first - rhs.array);
		last = array + (rhs.last - rhs.array);
	}

	~Block() {
		for (size_t i = 0; i < capacity; ++i)
			alloc.destroy(array + i);
		alloc.deallocate(array, capacity);
	}

	// Capacity
	size_t size() const {
		return ft::abs(last - first);
	}

	bool hasSpace() const {
		return size() != capacity;
	}

	// Element Access
	T REF operator [] (size_t const pos) {
		if (dir < 0)
			return first[-pos];
		return first[pos];
	}

	T CREF operator [] (size_t const pos) const {
		if (dir < 0)
			return first[-pos];
		return first[pos];
	}

	// Modifiers
	int push(T CREF val) {
		if (push_front(val))
			return 1;
		if (push_back(val))
			return -1;
		return 0;
	}

	bool push_front(T CREF val) {
		if (!hasSpace()
			|| (dir >= 0 && first == array)
			|| (dir < 0 && first == array + capacity - 1))
			return false;
		(dir >= 0) ? --first : ++first;
		*first = val;
		return true;
	}

	bool push_back(T CREF val) {
		if (!hasSpace()
			|| (dir >= 0 && last == array + capacity)
			|| (dir < 0 && last == array - 1))
			return false;
		*last = val;
		(dir >= 0) ? ++last : --last;
		return true;
	}

	// Attributes
	T					*array;
	T					*first;
	T					*last;
	size_t const		capacity;
	int					dir;
	std::allocator<T>	alloc;
};

#endif //BLOCK_H
