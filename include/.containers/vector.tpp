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
	: _size(VECTOR_ARRAY_INIT_SIZE), _allocator(alloc)
{
	_init(_size);
}


template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(size_type n, value_type CREF val, allocator_type CREF alloc)
	: _size(VECTOR_ARRAY_INIT_SIZE), _allocator(alloc)
{
	_assignHelper(n, val, ft::true_type());
}


template <typename T, typename Allocator>
template <typename InputIt>
ft::vector<T, Allocator>::vector(InputIt first, InputIt last, allocator_type CREF alloc)
	: _size(VECTOR_ARRAY_INIT_SIZE), _allocator(alloc)
{
	_assignHelper(first, last, ft::is_integral<InputIt>());
}


template <typename T, typename Allocator>
ft::vector<T, Allocator>::vector(vector CREF rhs)
	: _array(NULL), _size(rhs._size), _allocator(rhs._allocator)
{
	*this = rhs;
}


template <typename T, typename Allocator>
ft::vector<T, Allocator> REF
ft::vector<T, Allocator>::operator = (vector CREF rhs)
{
	if (this != &rhs) {
		if (_array)
			_allocator.deallocate(_array, _size);
		_assignHelper(rhs._array, rhs._array + _size, ft::false_type());
	}
	return *this;
}


template <typename T, typename Allocator>
ft::vector<T, Allocator>::~vector()
{
	if (!_array)
		return ;
	for (size_type i = 0; i < _size; ++i)
		_allocator.destroy(_array + i);
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
	return _array + _size;
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_iterator
ft::vector<T, Allocator>::end() const
{
	return _array + _size;
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::reverse_iterator
ft::vector<T, Allocator>::rbegin()
{
	return reverse_iterator(begin());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_reverse_iterator
ft::vector<T, Allocator>::rbegin() const
{
	return const_reverse_iterator(begin());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::reverse_iterator
ft::vector<T, Allocator>::rend()
{
	return reverse_iterator(end());
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::const_reverse_iterator
ft::vector<T, Allocator>::rend() const
{
	return const_reverse_iterator(end());
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
	size_type const arraySize = size();
	if (arraySize < n)
		for (difference_type i = arraySize; i != n; ++i) {
			--_end;
			_allocator.destroy(*_end);
		}
	else
		for (difference_type i = arraySize; i != n; ++i)
			push_back(val);

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
	return _array + n;
}


template <class T, class Allocator>
typename ft::vector<T, Allocator>::const_reference
ft::vector<T, Allocator>::operator [] (size_type n) const
{
	return _array + n;
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
	return _array;
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
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::pop_back()
{
	_allocator.destroy(--_end);
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
	size_type const posIndex	= position - _array;
	size_type const elemAfter	= size() - posIndex - 1;

	if (position + 1 == _end)
		pop_back();
	try {
		ft::rcopy(_end - elemAfter, _end, _end - 1);
	} catch (...) { return _end; }
	pop_back();
	return _array + posIndex;
}


template <typename T, typename Allocator>
template <typename InputIt>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::erase(InputIt first, InputIt last)
{
	size_type const posIndex	= first - _array;
	size_type const n			= ft::distance(first, last);
	size_type const elemAfter	= size() - posIndex - n;

	try {
		ft::copy(_end - elemAfter, _end, _end - elemAfter - n);
	} catch (...) { return _end; }
	for (size_type i = 0; i < n; ++i)
		pop_back();
	return _array + posIndex;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::swap(vector CREF other)
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
	while (newSize < n)
		newSize *= 2;
	value_type *tmpArray = _allocator.allocate(newSize);
	ft::swap(_array, tmpArray);
	_allocator.deallocate(tmpArray, _size);
	_end = _array;
	_size = newSize;
}


template <typename T, typename Allocator>
void
ft::vector<T, Allocator>::_assignHelper(size_type n, value_type CREF val, ft::true_type)
{
	_init(n);
	_end = _array + n;
	ft::fill(_array, _end, val);
}


template <typename T, typename Allocator>
template <typename InputIt>
void
ft::vector<T, Allocator>::_assignHelper(InputIt first, InputIt last, ft::false_type)
{
	size_type const n = ft::distance(first, last);
	_init(n);
	_end = _array + n;
	ft::copy(first, last, _array);
}


template <typename T, typename Allocator>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::_insertHelper(iterator position, size_type n, value_type CREF val, ft::true_type)
{
	if (position == _end)
		for (size_type i = 0; i < n; ++i)
			push_back(val);
	value_type const saveValue = val;
	size_type const posIndex = position - _array;
	size_type const elemAfter = size() - posIndex - n;
	reserve(size() + n);
	ft::rcopy(_array + elemAfter, _end, _end + n);
	ft::fill_n(_array + posIndex + 1, n, saveValue);
	return _array + posIndex;
}


template <typename T, typename Allocator>
template <typename InputIt>
typename ft::vector<T, Allocator>::iterator
ft::vector<T, Allocator>::_insertHelper(iterator position, InputIt first, InputIt last, ft::false_type)
{
	if (position == _end)
		while (first != last)
			push_back(*first++);
	size_type const n = ft::distance(first, last);
	size_type const posIndex = position - _array;
	size_type const elemAfter = size() - posIndex - n;
	reserve(size() + n);
	ft::rcopy(_array + elemAfter, _end, _end + n);
	ft::copy(first, last, _array + posIndex + 1);
	return _array + posIndex;
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
	_size = newSize;
	ft::copy(_array, _end, newArray);
	size_type const arraySize = _end - _array;
	_allocator.deallocate(_array);
	_array = newArray;
	_end = _array + arraySize;
}


#endif //VECTOR_TPP
