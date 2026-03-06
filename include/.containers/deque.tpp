//
// Created by mscheman on 1/13/26.
//

#ifndef DEQUE_TPP
#define DEQUE_TPP


#include "iostream"
#include ".helper/ftexcept.hpp"
#include ".helper/new.hpp"


// Public Members
// Constructor
template <typename T, typename Allocator>
ft::deque<T, Allocator>::deque(allocator_type CREF allocator)
	: _allocator(allocator)
{
	_init(DEQUE_INIT_ARRAY_NUM);
}


template <typename T, typename Allocator>
ft::deque<T, Allocator>::deque(size_type n, value_type CREF val, allocator_type CREF allocator)
	: _map(NULL), _mapSize(DEQUE_INIT_ARRAY_NUM), _allocator(allocator)
{
	_init(DEQUE_INIT_ARRAY_NUM);
	_assignFill(n, val);
}


template <typename T, typename Allocator>
template <typename Iterator>
ft::deque<T, Allocator>::deque(Iterator first, Iterator last, allocator_type CREF allocator)
	: _map(NULL), _mapSize(DEQUE_INIT_ARRAY_NUM), _allocator(allocator)
{
	_init(DEQUE_INIT_ARRAY_NUM);
	_assignHelper(first, last, ft::dispatch<Iterator>::identify());
}


template <typename T, typename Allocator>
ft::deque<T, Allocator>::deque(deque CREF rhs)
	: _map(NULL), _mapSize(0)
{
	_init(DEQUE_INIT_ARRAY_NUM);
	*this = rhs;
}


template <typename T, typename Allocator>
ft::deque<T, Allocator> REF
ft::deque<T, Allocator>::operator = (deque CREF rhs)
{
	if (this != &rhs)
		_assignHelper(rhs.begin(), rhs.end(), ft::dispatch_forward());
	return *this;
}


template <typename T, typename Allocator>
ft::deque<T, Allocator>::~deque()
{
	_clearHelper();
}


// Iterators
template <class T, class Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::begin()
{
	return iterator(_start);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_iterator
ft::deque<T, Allocator>::begin() const
{
	return const_iterator(_start);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::end()
{
	return _end;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_iterator
ft::deque<T, Allocator>::end() const
{
	return _end;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reverse_iterator
ft::deque<T, Allocator>::rbegin()
{
	return reverse_iterator(end());
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reverse_iterator
ft::deque<T, Allocator>::rbegin() const
{
	return const_reverse_iterator(end());
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reverse_iterator
ft::deque<T, Allocator>::rend()
{
	return reverse_iterator(begin());
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reverse_iterator
ft::deque<T, Allocator>::rend() const
{
	return const_reverse_iterator(begin());
}


// Capacity
template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::size_type
ft::deque<T, Allocator>::size() const
{
	return _end - _start;
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::size_type
ft::deque<T, Allocator>::max_size() const
{
	return _allocator.max_size();
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::resize(size_type n, value_type CREF val)
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
bool
ft::deque<T, Allocator>::empty() const
{
	return !(_end - _start);
}


// Element Access
template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference
ft::deque<T, Allocator>::operator [] (size_type n)
{
	return *(_start + n);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference
ft::deque<T, Allocator>::operator [] (size_type n) const
{
	return *(_start + n);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference
ft::deque<T, Allocator>::at(size_type n)
{
	if (n >= size())
		throw ft::out_of_range(DEQUE_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference
ft::deque<T, Allocator>::at(size_type n) const
{
	if (n > size())
		throw ft::out_of_range(DEQUE_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference
ft::deque<T, Allocator>::front()
{
	return *_start._mCurrent;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference
ft::deque<T, Allocator>::front() const
{
	return *_start._mCurrent;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference
ft::deque<T, Allocator>::back()
{
	return *ft::next(_end, -1);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference
ft::deque<T, Allocator>::back() const
{
	return *ft::next(_end, -1);
}


// Modifiers
template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::assign(size_type n, value_type CREF value)
{
	_assignFill(n, value);
}


template <typename T, typename Allocator>
template <typename Iterator>
void
ft::deque<T, Allocator>::assign(Iterator first, Iterator last)
{
	_assignHelper(first, last, ft::dispatch<Iterator>::identify());
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::push_back(value_type CREF value)
{
	_allocator.construct(_end._mCurrent, value);
	++_end._mCurrent;
	if (FT_UNLIKELY(_end._mCurrent == _end._mEnd))
		_expandBack();
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::push_front(value_type CREF value)
{
	if (FT_UNLIKELY(_start._mCurrent == _start._mBegin))
		_expandFront();
	else
		--_start._mCurrent;
	_allocator.construct(_start._mCurrent, value);
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::pop_back()
{
	if (FT_LIKELY(!empty())) {
		--_end;
		_allocator.destroy(_end._mCurrent);
	}
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::pop_front()
{
	if (FT_LIKELY(!empty())) {
		_allocator.destroy(_start._mCurrent);
		++_start;
	}
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::insert(iterator position, value_type CREF value)
{
	if (empty()) {
		_assignFill(1, value);
		return _start;
	}
	return _insertFill(position, 1, value);
}


template <class T, class Allocator>
void
ft::deque<T, Allocator>::insert(iterator position, size_type count, value_type CREF value)
{
	if (empty())
		return _assignFill(count, value);
	_insertFill(position, count, value);
}


template <class T, class Allocator>
template<class Iterator>
void
ft::deque<T, Allocator>::insert(iterator position, Iterator first, Iterator last)
{
	if (empty())
		return _assignHelper(first, last, ft::dispatch<Iterator>::identify());
	_insertHelper(position, first, last, ft::dispatch<Iterator>::identify());
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::erase(iterator position)
{
	size_type const posIndex	= position - _start;
	size_type const elemBefore	= posIndex;
	size_type const elemAfter	= size() - elemBefore - 1;

	// Edge cases
	if (FT_UNLIKELY(position._mCurrent == _start._mCurrent)) {
		pop_front();
		return _start;
	}
	if (FT_UNLIKELY(position == _end - 1)) {
		pop_back();
		return _end;
	}

	if (elemBefore < elemAfter) {
		ft::rcopy(_start, position, position + 1); // this causes conditional jump?
		pop_front();
	}
	else {
		ft::copy(position + 1, end(), position);
		pop_back();
	}
	return _start + posIndex;
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::erase(iterator first, iterator last)
{
	size_type const posIndex	= first - _start;
	size_type const n			= ft::distance(first, last);
	size_type const elemBefore	= posIndex;
	size_type const elemAfter	= size() - elemBefore - n;

	// Edge cases
	if (FT_UNLIKELY(first == _start)) {
		while (first++ != last)
			pop_front();
		return _start;
	}
	if (FT_UNLIKELY(last == _end)) {
		while (last-- != first)
			pop_back();
		return _end;
	}

	if (elemBefore < elemAfter) {
		TRY_RET(
			ft::rcopy(_start, _start + elemBefore, _start + elemBefore + n),
			_end
		);
		for (size_type i = 0; i < n; ++i)
			pop_front();
	}
	else {
		TRY_RET(
			ft::copy(_end - elemAfter, _end, _start + posIndex),
			_end
		);
		for (size_type i = 0; i < n; ++i)
			pop_back();
	}
	return _start + posIndex;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::swap(deque REF other)
{
	if (this == &other)
		return;
	ft::swap(_map, other._map);
	ft::swap(_mapSize, other._mapSize);
	ft::swap(_start, other._start);
	ft::swap(_end, other._end);
	ft::swap(_allocator, other._allocator);
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::clear()
{
	_clearHelper(true);
}


// Allocator
template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::allocator_type
ft::deque<T, Allocator>::get_allocator() const
{
	return _allocator;
}


// Protected Members
// Helper Functions
template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::_init(size_type size)
{
	if (size < DEQUE_INIT_ARRAY_NUM)
		size = DEQUE_INIT_ARRAY_NUM;
	_map = _allocateMap(size);
	_map[(size + 2) / 2] = _allocateBuffer();
	_mapSize = size;
	size_type startIdx = (size + 2) / 2;
	_start = iterator(&_map[startIdx], &_map[startIdx][DEQUE_ARRAY_SIZE / 2 - 1]);
	_end = _start;
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::_assignFill(size_type n, value_type CREF val)
{
	clear();
	_reserveBack(n);
	while (n) {
		push_back(val);
		--n;
	}
}


template <typename T, typename Allocator>
template <typename Integer>
void
ft::deque<T, Allocator>::_assignHelper(Integer first, Integer last, ft::dispatch_int)
{
	_assignFill(static_cast<size_type>(first), static_cast<value_type>(last));
}


template <typename T, typename Allocator>
template <typename InputIt>
void
ft::deque<T, Allocator>::_assignHelper(InputIt first, InputIt last, ft::dispatch_input)
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
ft::deque<T, Allocator>::_assignHelper(ForwardIt first, ForwardIt last, ft::dispatch_forward)
{
	clear();
	_reserveBack(ft::distance(first, last));
	while (first != last) {
		push_back(*first);
		++first;
	}
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::_expandBack()
{
	if (FT_UNLIKELY(_end._mMap == _map + _mapSize + 2))
		_reallocateMap(_mapSize * 2);
	if (_end._mMap[1] == NULL)
		_end._mMap[1] = _allocateBuffer();
	_end._setSubarray(_end._mMap + 1);
	_end._mCurrent = _end._mBegin;
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::_expandFront()
{
	if (FT_UNLIKELY(_start._mMap - 1 == _map))
		_reallocateMap(_mapSize * 2);
	if (_start._mMap[-1] == NULL)
		_start._mMap[-1] = _allocateBuffer();
	_start._setSubarray(_start._mMap - 1);
	_start._mCurrent = *_start._mMap + DEQUE_ARRAY_SIZE - 1;
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::_reserveBack(size_type n)
{
	if (_end._mCurrent + n < _end._mEnd)
		return ;
	if (FT_UNLIKELY(_end._mMap > _map + _mapSize + 2))
		_reallocateMap(_mapSize + n);
	size_type j = 1;
	for (difference_type i = n; i > 0; i -= DEQUE_ARRAY_SIZE) {
		if (!_end._mMap[j])
			_end._mMap[j] = _allocateBuffer();
		++j;
	}
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::_reserveFront(size_type n)
{
	if (_start._mCurrent - _start._mBegin > static_cast<difference_type>(n))
		return ;
	if (FT_UNLIKELY(_start._mMap == _map + 1))
		_reallocateMap(_mapSize + n);
	size_type j = 1;
	for (difference_type i = n; i > 0; i -= DEQUE_ARRAY_SIZE) {
		if (!_start._mMap[-j])
			_start._mMap[-j] = _allocateBuffer();
		++j;
	}
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::_insertFill(iterator pos, size_type n, value_type CREF val)
{
	size_type posIndex			= pos - _start;
	size_type const elemBefore	= posIndex;
	size_type const elemAfter	= size() - elemBefore;
	value_type const saveValue	= val;

	if (FT_UNLIKELY(pos == _start)) {
		while (n--)
			push_front(saveValue);
		return _start;
	}
	if (FT_UNLIKELY(pos == _end)) {
		while (n--)
			push_back(saveValue);
		return _end - 1;
	}
	if (elemBefore < elemAfter) {
		_reserveFront(n);
		// Shift the front elements to the left to make a hole
		iterator it = begin();
		for (size_type i = 0; i < posIndex; ++i, ++it) {
			value_type *shifted = (it - n)._mCurrent;
			if (i < n)
				_allocator.construct(shifted, *it);
			else
				*shifted = *it;
		}
		// Fill the fresh hole with the correct values
		ft::advance(it, -n);
		for (size_type i = 0; i < n; ++i, ++it)
			if (_start > it)
				_allocator.construct(it._mCurrent, saveValue);
			else
				*it._mCurrent = saveValue;
		// Adjust iterator position
		_start -= n;
	}
	else {
		_reserveBack(n);
		// Shift the front elements to the left to make a hole
		iterator it = end() - 1;
		for (size_type i = 0; i < elemAfter; ++i, --it) {
			value_type *shifted = (it + n)._mCurrent;
			if (i < n)
				_allocator.construct(shifted, *it);
			else
				*shifted = *it;
		}
		// Fill the fresh hole with the correct values
		ft::advance(it, n);
		for (size_type i = 0; i < n; ++i, --it)
			if (it >= _end)
				_allocator.construct(it._mCurrent, saveValue);
			else
				*it._mCurrent = saveValue;
		// Adjust iterator position
		_end += n;
	}
	return _start + posIndex;
}


template <typename T, typename Allocator>
template <typename Integer>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::_insertHelper(iterator position, Integer first, Integer last, ft::dispatch_int)
{
	return _insertFill(position, first, last);
}


template <typename T, typename Allocator>
template <typename InputIt>
void
ft::deque<T, Allocator>::_insertHelper(iterator position, InputIt first, InputIt last, ft::dispatch_input)
{
	size_type	posIndex	= position - _start;

	if (FT_UNLIKELY(position == _start)) {
		ft::deque<T, Allocator>	range(first, last, get_allocator());
		insert(position, range.begin(), range.end());
		return ;
	}
	if (FT_UNLIKELY(position == _end)) {
		while (first != last) {
			push_back(*first);
			++first;
		}
		return ;
	}
	ft::deque<T, Allocator>	save(get_allocator());
	if (posIndex < size() / 2) {
		ft::deque<T, Allocator>	range(first, last, get_allocator());
		// Front insert
		save.assign(_start, position);
		_reserveFront(save.size());
		erase(_start, position);
		for (reverse_iterator it = range.rbegin(); it != range.rend(); ++it)
			push_front(*it);
		for (reverse_iterator it = save.rbegin(); it != save.rend(); ++it)
			push_front(*it);
	}
	else {
		// Back insert
		save.assign(position, _end);
		_reserveBack(save.size());
		erase(position, _end);
		while (first != last) {
			push_back(*first);
			++first;
		}
		for (iterator it = save.begin(); it != save.end(); ++it)
			push_back(*it);
	}
}


template <typename T, typename Allocator>
template <typename ForwardIt>
void
ft::deque<T, Allocator>::_insertHelper(iterator position, ForwardIt first, ForwardIt last, ft::dispatch_forward)
{
	size_type	posIndex			= position - _start;
	size_type	const n				= ft::distance(first, last);
	size_type	const elemBefore	= posIndex;
	size_type	const elemAfter		= size() - n;

	if (FT_UNLIKELY(position == _start)) {
		_reserveFront(n);
		_start -= n;
		for (iterator it = _start; first != last; ++it, ++first)
			_allocator.construct(it._mCurrent, *first);
		return ;
	}
	if (FT_UNLIKELY(position == _end)) {
		_reserveBack(n);
		while (first != last) {
			push_back(*first);
			++first;
		}
		return ;
	}
	if (elemBefore < elemAfter) {
		_reserveFront(n);
		// Shift the front elements to the left to make a hole
		iterator it = begin();
		for (size_type i = 0; i < posIndex; ++i, ++it) {
			value_type *shifted = (it - n)._mCurrent;
			if (i < n)
				_allocator.construct(shifted, *it);
			else
				*shifted = *it;
		}
		// Fill the fresh hole with the correct values
		ft::advance(it, -n);
		while (first != last) {
			if (_start > it)
				_allocator.construct(it._mCurrent, *first);
			else
				*it._mCurrent = *first;
			++it;
			++first;
		}
		// Adjust iterator position
		_start -= n;
	}
	else {
		_reserveBack(n);
		// Shift the back elements to the right to make a hole
		iterator it = end() - 1;
		for (size_type i = 0; i < elemAfter; ++i, --it) {
			value_type *shifted = (it + n)._mCurrent;
			if (i < n)
				_allocator.construct(shifted, *it);
			else
				*shifted = *it;
		}
		// Fill the fresh hole with the correct values
		ft::advance(it, n);
		while (first != last) {
			if (it >= _end)
				_allocator.construct(it._mCurrent, *first);
			else
				*it._mCurrent = *first;
			++it;
			++first;
		}
		// Adjust iterator position
		_end += n;
	}
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_clearHelper(bool preserveMap)
{
	if (!_map)
		return;
	for (iterator it = begin(); it != end(); ++it)
		_allocator.destroy(it._mCurrent);
	for (size_type i = 0; i < _mapSize + 2; ++i) {
		if (FT_LIKELY(!preserveMap || i != (_mapSize + 2) / 2)) {
			_allocator.deallocate(_map[i], DEQUE_ARRAY_SIZE);
			_map[i] = NULL;
		}
	}
	if (!preserveMap) {
		_mapAllocator().deallocate(_map, _mapSize + 2);
		_map = NULL;
		_mapSize = 0;
		return;
	}
	_start = iterator(&_map[(_mapSize + 2) / 2], &_map[(_mapSize + 2) / 2][DEQUE_ARRAY_SIZE / 2]);
	_end = _start;
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::value_type **
ft::deque<T, Allocator>::_allocateMap(size_type n)
{
	if (n < DEQUE_INIT_ARRAY_NUM)
		n = DEQUE_INIT_ARRAY_NUM;
	value_type **newMap = NULL;
	TRY_ALLOC( newMap = _mapAllocator().allocate(n + 2);,;);
	ft::fill(newMap, newMap + n + 2, static_cast<value_type*>(0));
	return newMap;
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::value_type *
ft::deque<T, Allocator>::_allocateBuffer()
{
	TRY_ALLOC(return _allocator.allocate(DEQUE_ARRAY_SIZE);,;);
}


template <typename T, typename Allocator>
void
ft::deque<T, Allocator>::_reallocateMap(size_type n)
{
	// Make sure _mapSize is still a multiple of itself
	size_type newSize = _mapSize;
	while (newSize < n)
		newSize *= 2;
	n = newSize;
	// Allocate the new map
	value_type** oldMap = _map;
	_map = _allocateMap(n);
	// Move the data and update iterator position
	size_type const copyStart = (n - _mapSize + 2) / 2;
	ft::copy_n(oldMap + 1, _mapSize - 2, _map + copyStart);
	size_type const startOffset = _start._mMap - oldMap;
	size_type const endOffset = _end._mMap - oldMap;
	_start._mMap = _map + copyStart + startOffset;
	_end._mMap = _map + copyStart + endOffset;
	// Cleanup
	_mapAllocator().deallocate(oldMap, _mapSize + 2);
	_mapSize = n;
}


#endif //DEQUE_TPP
