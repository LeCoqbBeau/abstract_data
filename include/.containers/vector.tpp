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
	: _array(NULL), _size(VECTOR_ARRAY_INIT_SIZE), _lastConstructedIndex(0), _allocator(alloc)
{
	_init(_size);
}


template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(size_type n, value_type CREF val, allocator_type CREF alloc)
	: _array(NULL), _size(VECTOR_ARRAY_INIT_SIZE), _lastConstructedIndex(0), _allocator(alloc)
{
	_assignHelper(n, val, ft::true_type());
}


template <typename T, typename Allocator>
template <typename InputIt>
ft::vector<T, Allocator>::vector(InputIt first, InputIt last, allocator_type CREF alloc)
	: _array(NULL), _size(VECTOR_ARRAY_INIT_SIZE), _lastConstructedIndex(0), _allocator(alloc)
{
	_assignHelper(first, last, ft::is_integral<InputIt>());
}


template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(vector CREF rhs)
	: _array(NULL), _size(VECTOR_ARRAY_INIT_SIZE), _lastConstructedIndex(0), _allocator(rhs._allocator)
{
	*this = rhs;
}


template <typename T, typename Allocator>
ft::vector<T, Allocator> REF
ft::vector<T, Allocator>::operator = (vector CREF rhs)
{
	if (this != &rhs) {
		if (!_array)
			_init(rhs.size());
		reserve(rhs.size());
		_assignHelper(rhs.begin(), rhs.end(), ft::false_type());
	}
	return *this;
}


template <typename T, typename Allocator>
ft::vector<T, Allocator>::~vector()
{
	if (!_array)
		return ;
	for (value_type* it = _array; it != _end; ++it)
		_allocator.destroy(it);
	_allocator.deallocate(_array, _size);
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
	if (n > size())
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
	return _size;
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
		_reallocate(_size * 2);
	_allocator.construct(_end++, value);
	++_lastConstructedIndex;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::pop_back()
{
	_allocator.destroy(--_end);
	--_lastConstructedIndex;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::assign(size_type n, value_type CREF value)
{
	_assignHelper(n, value, ft::true_type());
}


template <typename T, typename Allocator>
template <typename InputIt>
void
ft::vector<T, Allocator>::assign(InputIt first, InputIt last)
{
	_assignHelper(first, last, ft::is_integral<InputIt>());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::insert(iterator position, value_type CREF val)
{
	return _insertHelper(position, 1, val, ft::true_type());
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::insert(iterator position, size_type count, value_type CREF val)
{
	_insertHelper(position, count, val, ft::true_type());
}


template <typename T, typename Allocator>
template <typename InputIt>
void
ft::vector<T, Allocator>::insert(iterator position, InputIt first, InputIt last)
{
	_insertHelper(position, first, last, ft::is_integral<InputIt>());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::erase(iterator position)
{
	size_type const posIndex	= position._curr - _array;
	size_type const elemAfter	= size() - posIndex - 1;

	if (position._curr == _end) {
		pop_back();
		return _end;
	}
	TRY_RET(
		ft::copy(_end - elemAfter, _end, _array + posIndex);,
		_end;
	)
	pop_back();
	return iterator(_array + posIndex);
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::erase(iterator first, iterator last)
{
	size_type const posIndex	= first._curr - _array;
	size_type const n			= ft::distance(first, last);
	size_type const elemAfter	= size() - posIndex - n;

	TRY_RET(
		ft::copy(_end - elemAfter, _end, _array + posIndex);,
		_end;
	)
	for (size_type i = 0; i < n; ++i)
		pop_back();
	return iterator(_array + posIndex);
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::swap(vector REF other)
{
	ft::swap(_array, other._array);
	ft::swap(_end, other._end);
	ft::swap(_size, other._size);
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
	size_type newSize = _size;
	if (newSize < VECTOR_ARRAY_INIT_SIZE)
		newSize = VECTOR_ARRAY_INIT_SIZE;
	while (newSize < n)
		newSize *= 2;
	value_type *tmpArray = _allocator.allocate(newSize);
	ft::swap(_array, tmpArray);
	_end = _array;
	_size = newSize;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::_assignHelper(size_type n, value_type CREF val, ft::true_type)
{
	if (!_array)
		_init(n);
	else
		reserve(n);
	if (_end > _array + n) {
		for (value_type *it = _array + n; it < _end; ++it)
			_allocator.destroy(it);
		_lastConstructedIndex = n;
	}
	_end = _array + n;
	for (value_type *it = _array; it < _end; ++it) {
		if (static_cast<size_type>(it - _array) >= _lastConstructedIndex) {
			_allocator.construct(it, val);
			++_lastConstructedIndex;
		}
		else
			*it = val;
	}
}


template <typename T, typename Allocator>
template <typename InputIt>
void
ft::vector<T, Allocator>::_assignHelper(InputIt first, InputIt last, ft::false_type)
{
	size_type const n = ft::distance(first, last);
	if (!_array)
		_init(n);
	else
		reserve(n);
	if (_end > _array + n) {
		for (value_type *it = _array + n; it < _end; ++it)
			_allocator.destroy(it);
		_lastConstructedIndex = n;
	}
	_end = _array + n;
	size_type i = 0;
	while (first != last) {
		if (i >= _lastConstructedIndex) {
			_allocator.construct(_array + i++, *first++);
			++_lastConstructedIndex;
		}
		else
			_array[i++] = *first++;
	}
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::_insertHelper(iterator position, size_type n, value_type CREF val, ft::true_type)
{
	if (position._curr == _end) {
		for (size_type i = 0; i < n; ++i)
			push_back(val);
		return _end - 1;
	}
	value_type const	saveValue = val;
	size_type const		posIndex = position._curr - _array;
	size_type			constructCount = 0;
	reserve(size() + n);
	// Shift the back elements to the right to make a hole
	for (size_type i = size() - 1; i >= posIndex && i < size(); --i) {
		if (n + i >= _lastConstructedIndex) {
			_allocator.construct(_array + n + i, _array[i]);
			++constructCount;
		}
		else
			_array[n + i] = _array[i];
	}
	// Fill the fresh hole with the correct values
	for (size_type i = 0; i < n; ++i)
		_array[posIndex + i] = saveValue;
	// Adjust iterator position
	_lastConstructedIndex += constructCount;
	_end += n;
	return _array + posIndex;
}


template <typename T, typename Allocator>
template <typename InputIt>
void
ft::vector<T, Allocator>::_insertHelper(iterator position, InputIt first, InputIt last, ft::false_type)
{
	if (position._curr == _end) {
		while (first != last)
			push_back(*first++);
		return ;
	}
	size_type const n = ft::distance(first, last);
	size_type const posIndex = position._curr - _array;
	reserve(size() + n);
	// Shift the back elements to the right to make a hole
	for (size_type i = size() - 1; i >= posIndex; --i) {
		if (n + i >= _lastConstructedIndex) {
			_allocator.construct(_array + n + i, _array[i]);
			++_lastConstructedIndex;
		}
		else
			_array[n + i] = _array[i];
	}
	for (size_type i = 0; i < n; ++i)
		_array[posIndex + i] = *first++;
	_end += n;
	return _array + posIndex + 1;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::_reallocate(size_type n)
{
	if (n < _size)
		return;
	size_type newSize = _size;
	while (newSize < n)
		newSize *= 2;
	value_type* newArray = _allocator.allocate(newSize);
	for (value_type *it = _array; it != _end; ++it)
		_allocator.construct(newArray + (it - _array), *it);
	size_type const arraySize = _end - _array;
	for (value_type* it = _array; it != _end; ++it)
		_allocator.destroy(it);
	_allocator.deallocate(_array, _size);
	_size = newSize;
	_array = newArray;
	_end = _array + arraySize;
}


#endif //VECTOR_TPP
