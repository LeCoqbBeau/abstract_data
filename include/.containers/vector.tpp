//
// Created by mscheman on 1/19/26.
//

#ifndef VECTOR_TPP
#define VECTOR_TPP


#include ".helper/algorithm.hpp"
#include ".helper/ftexcept.hpp"
#include ".helper/new.hpp"


template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(allocator_type CREF alloc)
	: _array(NULL), _capacity(VECTOR_ARRAY_INIT_SIZE), _allocator(alloc)
{
	_init(_capacity);
}


template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(size_type n, value_type CREF val, allocator_type CREF alloc)
	: _array(NULL), _capacity(VECTOR_ARRAY_INIT_SIZE), _allocator(alloc)
{
	_init(_capacity);
	_assignFill(n, val);
}


template <typename T, typename Allocator>
template <typename InputIt>
ft::vector<T, Allocator>::vector(InputIt first, InputIt last, allocator_type CREF alloc)
	: _array(NULL), _capacity(VECTOR_ARRAY_INIT_SIZE), _allocator(alloc)
{
	_init(_capacity);
	_assignHelper(first, last, ft::dispatch<InputIt>::identify());
}


template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(vector CREF rhs)
	: _array(NULL), _capacity(VECTOR_ARRAY_INIT_SIZE), _allocator(rhs._allocator)
{
	_init(_capacity);
	*this = rhs;
}


template <typename T, typename Allocator>
ft::vector<T, Allocator> REF
ft::vector<T, Allocator>::operator = (vector CREF rhs)
{
	if (this != &rhs)
		_assignHelper(rhs.begin(), rhs.end(), ft::dispatch_forward());
	return *this;
}


template <typename T, typename Allocator>
ft::vector<T, Allocator>::~vector()
{
	if (!_array)
		return ;
	for (value_type* it = _array; it != _end; ++it)
		_allocator.destroy(it);
	_allocator.deallocate(_array, _capacity);
}


// Iterators
template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::begin()
{
	return _array;
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_iterator
ft::vector<T, Allocator>::begin() const
{
	return _array;
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::end()
{
	return _end;
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_iterator
ft::vector<T, Allocator>::end() const
{
	return _end;
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::reverse_iterator
ft::vector<T, Allocator>::rbegin()
{
	return reverse_iterator(end());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_reverse_iterator
ft::vector<T, Allocator>::rbegin() const
{
	return const_reverse_iterator(end());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::reverse_iterator
ft::vector<T, Allocator>::rend()
{
	return reverse_iterator(begin());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_reverse_iterator
ft::vector<T, Allocator>::rend() const
{
	return const_reverse_iterator(begin());
}

// Capacity
template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::size_type
ft::vector<T, Allocator>::size() const
{
	return _end - _array;
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::size_type
ft::vector<T, Allocator>::max_size() const
{
	return _allocator.max_size();
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::resize(size_type n, value_type CREF val)
{
	if (n == 0)
		clear();
	else if (n > size())
		for (size_type i = size(); i < n; ++i)
			push_back(val); // this can throw :D
	else
		for (size_type i = size() - 1; i >= n; --i)
			pop_back(); // this never throws
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::size_type
ft::vector<T, Allocator>::capacity() const
{
	return _capacity;
}


template <typename T, typename Allocator>
bool
ft::vector<T, Allocator>::empty() const
{
	return _array == _end;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::reserve(size_type n)
{
	if (capacity() > n)
		return;
	_reallocate(n);
}


// Element Access
template <class T, class Allocator>
typename ft::vector<T, Allocator>::reference
ft::vector<T, Allocator>::operator [] (size_type n)
{
	return *(_array + n);
}


template <class T, class Allocator>
typename ft::vector<T, Allocator>::const_reference
ft::vector<T, Allocator>::operator [] (size_type n) const
{
	return *(_array + n);
}


template <class T, class Allocator>
typename ft::vector<T, Allocator>::reference
ft::vector<T, Allocator>::at(size_type n)
{
	if (n >= size())
		throw ft::out_of_range(VECTOR_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <class T, class Allocator>
typename ft::vector<T, Allocator>::const_reference
ft::vector<T, Allocator>::at(size_type n) const
{
	if (n > size())
		throw ft::out_of_range(VECTOR_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <class T, class Allocator>
typename ft::vector<T, Allocator>::reference
ft::vector<T, Allocator>::front()
{
	return *_array;
}


template <class T, class Allocator>
typename ft::vector<T, Allocator>::const_reference
ft::vector<T, Allocator>::front() const
{
	return *_array;
}


template <class T, class Allocator>
typename ft::vector<T, Allocator>::reference
ft::vector<T, Allocator>::back()
{
	return *(_end - 1);
}


template <class T, class Allocator>
typename ft::vector<T, Allocator>::const_reference
ft::vector<T, Allocator>::back() const
{
	return *(_end - 1);
}


// Modifiers
template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::push_back(value_type CREF value)
{
	if (FT_UNLIKELY(size() == capacity()))
		_reallocate(_capacity * 2);
	_allocator.construct(_end, value);
	++_end;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::pop_back()
{
	--_end;
	_allocator.destroy(_end);
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::assign(size_type n, value_type CREF value)
{
	_assignFill(n, value);
}


template <typename T, typename Allocator>
template <typename Iterator>
void
ft::vector<T, Allocator>::assign(Iterator first, Iterator last)
{
	_assignHelper(first, last, ft::dispatch<Iterator>::identify());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::insert(iterator position, value_type CREF val)
{
	if (empty()) {
		_assignFill(1, val);
		return _array;
	}
	return _insertFill(position, 1, val);
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::insert(iterator position, size_type count, value_type CREF val)
{
	if (count == 0)
		return ;
	if (empty())
		_assignFill(count, val);
	else
		_insertFill(position, count, val);
}


template <typename T, typename Allocator>
template <typename Iterator>
void
ft::vector<T, Allocator>::insert(iterator position, Iterator first, Iterator last)
{
	if (empty())
		_assignHelper(first, last, ft::dispatch<Iterator>::identify());
	else
		_insertHelper(position, first, last, ft::dispatch<Iterator>::identify());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::erase(iterator position)
{
	size_type const posIndex	= position._curr - _array;

	ft::copy(position + 1, end(), position);
	pop_back();
	return iterator(_array + posIndex);
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::erase(iterator first, iterator last)
{
	size_type const posIndex	= first._curr - _array;

	if (last != end())
		ft::copy(last, end(), first);
	while (first != last) {
		pop_back();
		++first;
	}
	return iterator(_array + posIndex);
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::swap(vector REF other)
{
	ft::swap(_array, other._array);
	ft::swap(_end, other._end);
	ft::swap(_capacity, other._capacity);
	ft::swap(_allocator, other._allocator);
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::clear()
{
	while (_end != _array)
		pop_back();
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::allocator_type
ft::vector<T, Allocator>::get_allocator() const
{
	return _allocator;
}


// Protected Helper Method
template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::_init(size_type n)
{
	size_type newSize = _capacity;
	if (newSize < VECTOR_ARRAY_INIT_SIZE)
		newSize = VECTOR_ARRAY_INIT_SIZE;
	while (newSize < n)
		newSize *= 2;
	value_type *tmpArray = _allocator.allocate(newSize);
	ft::swap(_array, tmpArray);
	_end = _array;
	_capacity = newSize;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::_assignFill(size_type n, value_type CREF val)
{
	reserve(n);
	difference_type const	preSize	= _end - _array;
	difference_type			i		= 0;
	while (static_cast<size_type>(i) != n) {
		if (i < preSize)
			_array[i] = val;
		else
			_allocator.construct(_array + i, val);
		++i;
	}
	_end = _array + i;
	while (i < preSize) {
		_allocator.destroy(_array + i);
		++i;
	}
}


template <typename T, typename Allocator>
template <typename Integer>
void
ft::vector<T, Allocator>::_assignHelper(Integer first, Integer last, ft::dispatch_int)
{
	_assignFill(static_cast<size_type>(first), static_cast<value_type>(last));
}


template <typename T, typename Allocator>
template <typename InputIt>
void
ft::vector<T, Allocator>::_assignHelper(InputIt first, InputIt last, ft::dispatch_input)
{
	clear();
	while (first != last) {
		push_back(*first);
		++first;
	}
}


template <typename T, typename Allocator>
template <typename ForwardIt>
void
ft::vector<T, Allocator>::_assignHelper(ForwardIt first, ForwardIt last, ft::dispatch_forward)
{
	reserve(ft::distance(first, last));
	difference_type const	preSize	= _end - _array;
	difference_type			i		= 0;
	while (first != last) {
		if (i < preSize)
			_array[i] = *first;
		else
			_allocator.construct(_array + i, *first);
		++i;
		++first;
	}
	_end = _array + i;
	while (i < preSize) {
		_allocator.destroy(_array + i);
		++i;
	}
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::_insertFill(iterator position, size_type n, value_type CREF val)
{
	if (position._curr == _end) {
		for (size_type i = 0; i < n; ++i)
			push_back(val);
		return _end - 1;
	}
	value_type const	saveValue	= val;
	size_type const		posIndex	= position._curr - _array;
	size_type const		preSize		= _end - _array;
	reserve(size() + n);
	// Shift the back elements to the right to make a hole
	for (size_type i = size() - 1; i >= posIndex && i < size(); --i) {
		if (n + i >= preSize)
			_allocator.construct(_array + n + i, _array[i]);
		else
			_array[n + i] = _array[i];
	}
	// Fill the hole
	for (size_type i = 0; i < n; ++i)
		if (posIndex + i >= preSize)
			_allocator.construct(_array + posIndex + i, saveValue);
		else
			_array[posIndex + i] = saveValue;
	// Adjust end position
	_end += n;
	return _array + posIndex;
}


template <typename T, typename Allocator>
template <typename ForwardIt>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::_insertHelper(iterator position, ForwardIt first, ForwardIt last, ft::dispatch_int)
{
	return _insertFill(position, static_cast<size_type>(first), static_cast<value_type>(last));
}


template <typename T, typename Allocator>
template <typename InputIt>
void
ft::vector<T, Allocator>::_insertHelper(iterator position, InputIt first, InputIt last, ft::dispatch_input)
{
	if (first == last)
		return ;
	if (position._curr == _end) {
		while (first != last) {
			push_back(*first);
			++first;
		}
		return ;
	}
	ft::vector<T, Allocator>	save(position, end(), get_allocator());
	erase(position, _end);
	while (first != last) {
		push_back(*first);
		++first;
	}
	for (iterator it = save.begin(); it != save.end(); ++it)
		push_back(*it);
}


template <typename T, typename Allocator>
template <typename ForwardIt>
void
ft::vector<T, Allocator>::_insertHelper(iterator position, ForwardIt first, ForwardIt last, ft::dispatch_forward)
{
	if (position._curr == _end) {
		while (first != last) {
			push_back(*first);
			++first;
		}
		return ;
	}
	size_type const	n			= ft::distance(first, last);
	size_type const	posIndex	= position._curr - _array;
	size_type const preSize		= _end - _array;
	reserve(size() + n);
	// Shift the back elements to the right to make a hole
	for (size_type i = size() - 1; i >= posIndex && i < size(); --i) {
		if (n + i >= preSize)
			_allocator.construct(_array + n + i, _array[i]);
		else
			_array[n + i] = _array[i];
	}
	// Fill the hole
	for (size_type i = 0; i < n; ++i) {
		if (posIndex + i >= preSize)
			_allocator.construct(_array + posIndex + i, *first);
		else
			_array[posIndex + i] = *first;
		++first;
	}
	// Adjust end position
	_end += n;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::_reallocate(size_type n)
{
	if (n < _capacity)
		return;
	size_type newSize = _capacity;
	while (newSize < n)
		newSize *= 2;
	value_type* newArray = _allocator.allocate(newSize);
	for (value_type *it = _array; it != _end; ++it)
		_allocator.construct(newArray + (it - _array), *it);
	size_type const arraySize = _end - _array;
	for (value_type* it = _array; it != _end; ++it)
		_allocator.destroy(it);
	_allocator.deallocate(_array, _capacity);
	_capacity = newSize;
	_array = newArray;
	_end = _array + arraySize;
}


#endif //VECTOR_TPP
