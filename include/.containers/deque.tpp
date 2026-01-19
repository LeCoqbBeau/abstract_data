//
// Created by mscheman on 1/13/26.
//

#ifndef DEQUE_TPP
#define DEQUE_TPP

#include ".helper/ftexcept.hpp"
#include ".helper/new.hpp"

//	//
//	//	ft::_dequeIterator<T, TRef, TPtr>
//	//

// Constructor
template <typename T, typename TRef, typename TPtr>
ft::_dequeIterator<T, TRef, TPtr>::_dequeIterator(value_type** map, value_type *curr)
	: _mCurrent(curr), _mMap(map) {
	if (!map) {
		_mBegin = NULL;
		_mEnd = NULL;
	} else {
		_mBegin = *map;
		_mEnd = _mBegin + DEQUE_ARRAY_SIZE;
	}
}


template <typename T, typename TRef, typename TPtr>
ft::_dequeIterator<T, TRef, TPtr>::_dequeIterator(_dequeIterator<T, T REF, T*> CREF iterator)
	: _mCurrent(iterator._mCurrent), _mBegin(iterator.begin), _mEnd(iterator.end), _mMap(iterator.map)
{}


// Shift Operators
template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator ++ () {
	if (FT_UNLIKELY(++_mCurrent == _mEnd)) {
		_mBegin = *++_mMap;
		_mCurrent = _mBegin;
		_mEnd = _mBegin + DEQUE_ARRAY_SIZE;
	}
	return *this;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator ++ (int) {
	this_type temp(*this);
	operator++();
	return temp;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator += (difference_type n) {
	const difference_type arrayPos = (_mCurrent - _mBegin) + n;

	if (static_cast<ft::size_t>(arrayPos) < static_cast<ft::size_t>(n))
		_mCurrent += n;
	else {
#define LARGE_OFFSET (1 << 24)
		difference_type arrayIndex = (LARGE_OFFSET + arrayPos) / static_cast<difference_type>(DEQUE_ARRAY_SIZE);
		arrayIndex -= (LARGE_OFFSET / DEQUE_ARRAY_SIZE);
		_mMap += arrayIndex;
		_mBegin = *_mMap;
		_mEnd = _mBegin + DEQUE_ARRAY_SIZE;
		_mCurrent = _mBegin + (arrayPos - (arrayIndex * DEQUE_ARRAY_SIZE));
#undef LARGE_OFFSET
	}
	return *this;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator + (difference_type n) {
	return this_type(*this).operator+=(n);
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator -- () {
	if (FT_UNLIKELY(_mCurrent == _mBegin)) {
		_mBegin = *--_mMap;
		_mEnd = _mBegin + DEQUE_ARRAY_SIZE;
		_mCurrent = _mEnd;
	}
	--_mCurrent;
	return *this;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator -- (int) {
	this_type temp(*this);
	operator--();
	return temp;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator -= (difference_type n) {
	return this->operator+=(-n);
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator - (difference_type n) {
	return this_type(*this).operator+=(-n);
}

// Comparison Operators
#define TWO_DEQUEIT_TEMPLATE template <typename U, typename RefA, typename PtrA, typename RefB, typename PtrB>
#define TWO_DEQUEIT_PARAMETERS ft::_dequeIterator<U, RefA, PtrA> CREF a, ft::_dequeIterator<U, RefB, PtrB> CREF b
#define TWO_DEQUEIT_COMPARISON(op) TWO_DEQUEIT_TEMPLATE inline bool operator op (TWO_DEQUEIT_PARAMETERS)


TWO_DEQUEIT_COMPARISON(==)	{ return a._mCurrent == b._mCurrent; }
TWO_DEQUEIT_COMPARISON(!=)	{ return !(a == b); }
TWO_DEQUEIT_COMPARISON(<)	{ return (a.map == b.map) ? (a._mCurrent < b._mCurrent) : (a.map < b.map); }
TWO_DEQUEIT_COMPARISON(<=)	{ return !(b < a); }
TWO_DEQUEIT_COMPARISON(>)	{ return (b < a); }
TWO_DEQUEIT_COMPARISON(>=)	{ return !(a < b); }

// Arithmetic Operators
// to handle n + iterator
template <typename T, typename Ref, typename Ptr>
ft::_dequeIterator<T, Ref, Ptr>
operator + (ft::ptrdiff_t n, ft::_dequeIterator<T, Ref, Ptr> CREF iterator) {
	return iterator + n;
}


TWO_DEQUEIT_TEMPLATE
typename ft::_dequeIterator<U, RefA, PtrA>::difference_type
operator - (TWO_DEQUEIT_PARAMETERS) {
	typedef typename ft::_dequeIterator<U, RefA, PtrA>::difference_type difference_type;
	difference_type const bufferSize = static_cast<difference_type>(DEQUE_ARRAY_SIZE);
	difference_type const nodeDiff = a.map - b.map;
	difference_type const offset = (a._mCurrent - a.begin) - (b._mCurrent - b.begin);
	return bufferSize * nodeDiff + offset;
}


#undef TWO_DEQUEIT_TEMPLATE
#undef TWO_DEQUEIT_PARAMETERS
#undef TWO_DEQUEIT_COMPARISON


//	//
//	//	ft::_deque<T, Allocator>
//	//

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
	_assignHelper(n, val, ft::true_type());
}


template <typename T, typename Allocator>
template <typename InputIt>
ft::deque<T, Allocator>::deque(InputIt first, InputIt last, allocator_type CREF allocator)
	: _map(NULL), _mapSize(DEQUE_INIT_ARRAY_NUM), _allocator(allocator)
{
	_assignHelper(first, last, ft::is_integral<InputIt>());
}


template <typename T, typename Allocator>
ft::deque<T, Allocator>::deque(deque CREF rhs)
	: _map(NULL), _mapSize(0)
{
	*this = rhs;
}


template <typename T, typename Allocator>
ft::deque<T, Allocator> REF ft::deque<T, Allocator>::operator = (deque CREF rhs) {
	if (this != &rhs) {
		// Cleanups before allocating
		if (_map)
			_clearHelper();
		_map = NULL;
		// Copy basic attributes
		_allocator = rhs._allocator;	// can throw, shouldn't throw
		_mapSize = rhs._mapSize;
		_map = _allocateMap(_mapSize);
		size_type const elemNum = rhs.size();
		size_type const maxElem = _mapSize * DEQUE_ARRAY_SIZE;
		size_type const startOffset = (maxElem - elemNum) / 2;
		_map[startOffset / DEQUE_ARRAY_SIZE] = _allocateBuffer();
		_start = iterator(
			&_map[startOffset / DEQUE_ARRAY_SIZE],
			&_map[startOffset / DEQUE_ARRAY_SIZE][startOffset % DEQUE_ARRAY_SIZE - 1]
		);
		_end = _start;
		// Copy content
		try {
			for (const_iterator it = rhs.begin(); it != rhs._end; ++it)
				push_back(*it);			// can throw, shouldn't throw
		} catch (...) {
			while (_start != _end)
				pop_back();
		}
	}
	return *this;
}


template <typename T, typename Allocator>
ft::deque<T, Allocator>::~deque() {
	_clearHelper();
}


// Iterators
template <class T, class Allocator>
typename ft::deque<T, Allocator>::iterator ft::deque<T, Allocator>::begin() {
	return iterator(_start);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_iterator ft::deque<T, Allocator>::begin() const {
	return const_iterator(_start);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::iterator ft::deque<T, Allocator>::end() {
	return _end;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_iterator ft::deque<T, Allocator>::end() const {
	return _end;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reverse_iterator ft::deque<T, Allocator>::rbegin() {
	return reverse_iterator(end());
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reverse_iterator ft::deque<T, Allocator>::rbegin() const {
	return const_reverse_iterator(end());
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reverse_iterator ft::deque<T, Allocator>::rend() {
	return reverse_iterator(begin());
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reverse_iterator ft::deque<T, Allocator>::rend() const {
	return const_reverse_iterator(begin());
}


// Capacity
template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::size_type ft::deque<T, Allocator>::size() const {
	return _end - _start;
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::size_type ft::deque<T, Allocator>::max_size() const {
	return _allocator.max_size();
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::resize(size_type n, value_type CREF val) {
	if (n > size())
			for (size_type i = size(); i < n; ++i)
				push_back(val); // this can throw :D
	else
		for (size_type i = size() - 1; i > n; --i)
			pop_back(); // this never throws
}


template <typename T, typename Allocator>
bool ft::deque<T, Allocator>::empty() const {
	return !(_end - _start);
}


// Element Access
template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference
ft::deque<T, Allocator>::operator [] (size_type n) {
	return *(begin().operator+=(n));
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference
ft::deque<T, Allocator>::operator [] (size_type n) const {
	return *(begin().operator+=(n));
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference
ft::deque<T, Allocator>::at(size_type n) {
	if (n >= size())
		throw ft::out_of_range(DEQUE_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference
ft::deque<T, Allocator>::at(size_type n) const {
	if (n > size())
		throw ft::out_of_range(DEQUE_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference
ft::deque<T, Allocator>::front() {
	return *_start._mCurrent;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference
ft::deque<T, Allocator>::front() const {
	return *_start._mCurrent;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference
ft::deque<T, Allocator>::back() {
	return *(_end._mCurrent - 1);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference
ft::deque<T, Allocator>::back() const {
	return *(_end._mCurrent - 1);
}


// Modifiers
template <typename T, typename Allocator>
void ft::deque<T, Allocator>::assign(size_type n, value_type CREF value) {
	_assignHelper(n, value, ft::true_type());
}


template <typename T, typename Allocator>
template <typename InputIt>
void ft::deque<T, Allocator>::assign(InputIt first, InputIt last) {
	_assignHelper(first, last, ft::is_integral<InputIt>());
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::push_back(value_type CREF value) {
	if (FT_UNLIKELY(_end._mCurrent == _end.end))
		_expandBack();
	_allocator.construct(_end._mCurrent, value);
	++_end._mCurrent;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::push_front(value_type CREF value) {
	if (FT_UNLIKELY(_start._mCurrent == _start.begin - 1))
		_expandFront();
	_allocator.construct(&(_start._mCurrent[-1]), value);
	--_start._mCurrent;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::pop_back() {
	if (FT_LIKELY(!empty())) {
		--_end;
		_allocator.destroy(_end._mCurrent);
	}
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::pop_front() {
	if (FT_LIKELY(!empty()))
		_allocator.destroy((++_start)._mCurrent);
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::insert(iterator position, value_type CREF value) {
	return _insertHelper(position, 1, value, ft::true_type());
}


template <class T, class Allocator>
void ft::deque<T, Allocator>::insert(iterator position, size_type count, value_type CREF value) {
	_insertHelper(position, count, value, ft::true_type());
}


template <class T, class Allocator>
template<class InputIt>
void ft::deque<T, Allocator>::insert(iterator position, InputIt first, InputIt last) {
	_insertHelper(position, first, last, ft::is_integral<InputIt>());
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::erase(iterator position) {
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
		try {
			ft::copy(_start, _start + elemBefore, _start + 1);
		} catch (...) { return _end; }
		pop_front();
		return _start + elemBefore - 1;
	}
	try {
	ft::rcopy(_end - elemAfter, _end, _end - 1);
	} catch (...) { return _end; }
	pop_back();
	return _start + posIndex;
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::erase(iterator first, iterator last) {
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
		try {
			ft::copy(_start, _start + elemBefore, _start + n);
		} catch (...) { return _end; }
		for (size_type i = 0; i < n; ++i)
			pop_front();
		return _start + elemBefore;
	}
	try {
		ft::copy(_end - elemAfter, _end, _end - elemAfter - n);
	} catch (...) { return _end; }
	for (size_type i = 0; i < n; ++i)
		pop_back();
	return _start + posIndex;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::swap(deque REF other) {
	if (this != &other)
		return;
	ft::swap(_map, other._map);
	ft::swap(_mapSize, other._mapSize);
	ft::swap(_start, other._start);
	ft::swap(_end, other._end);
	ft::swap(_allocator, other._allocator);
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::clear() {
	_clearHelper(true);
	// _init(DEQUE_INIT_ARRAY_NUM);
}


// Allocator
template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::allocator_type
ft::deque<T, Allocator>::get_allocator() const {
	return _allocator;
}


// Protected Members
// Helper Functions
template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_init(size_type size) {
	_map = _allocateMap(size);
	_map[size / 2] = _allocateBuffer();
	_mapSize = size;
	size_type startIdx = _mapSize / 2;
	_start = iterator(&_map[startIdx], &_map[startIdx][DEQUE_ARRAY_SIZE / 2 - 1]);
	_end = _start;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_assignHelper(size_type n, value_type CREF val, ft::true_type) {
	if (_map)
		_clearHelper();
	while (_mapSize * DEQUE_ARRAY_SIZE < n)
		_mapSize *= 2;
	_init(_mapSize);
	while (n) {
		push_back(val);
		--n;
	}
}


template <typename T, typename Allocator>
template <typename InputIt>
void ft::deque<T, Allocator>::_assignHelper(InputIt first, InputIt last, ft::false_type) {
	if (_map)
		_clearHelper();
	size_type const elemNum = static_cast<size_type>(ft::distance(first, last));
	while (_mapSize * DEQUE_ARRAY_SIZE < elemNum)
		_mapSize *= 2;
	_init(_mapSize);
	while (first != last) {
		push_back(*first);
		++first;
	}
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_expandBack() {
	if (FT_UNLIKELY(_end.map == _map + _mapSize - 1))
		_reallocateMap(_mapSize * 2);
	_end.map[1] = _allocateBuffer();
	++_end.map;
	_end._mCurrent = *_end.map;
	_end.begin = _end._mCurrent;
	_end.end = _end.begin + DEQUE_ARRAY_SIZE;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_expandFront() {
	if (FT_UNLIKELY(_start.map == _map))
		_reallocateMap(_mapSize * 2);
	_start.map[-1] = _allocateBuffer();
	--_start.map;
	_start._mCurrent = *_start.map + DEQUE_ARRAY_SIZE - 1;
	_start.begin = *_start.map;
	_start.end = _start.begin + DEQUE_ARRAY_SIZE;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_reserveBack(size_type n) {
	if (_end._mCurrent + n < _end.end)
		return ;
	if (FT_UNLIKELY(_end.map > &_map[_mapSize]))
		_reallocateMap(_mapSize + n);
	size_type j = 1;
	for (difference_type i = n; i > 0; i -= DEQUE_ARRAY_SIZE) {
		*(_end.map + j) = _allocateBuffer();
		++j;
	}
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_reserveFront(size_type n) {
	if (_start.end - _start._mCurrent > static_cast<difference_type>(n))
		return ;
	if (FT_UNLIKELY(_start.map == _map))
		_reallocateMap(_mapSize + n);
	size_type j = 1;
	for (difference_type i = n; i > 0; i -= DEQUE_ARRAY_SIZE) {
		*(_start.map - j) = _allocateBuffer();
		++j;
	}
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::_insertHelper(iterator pos, size_type n, value_type CREF val, ft::true_type) {
	size_type posIndex			= pos - _start;
	size_type const elemBefore	= posIndex;
	size_type const elemAfter	= size() - elemBefore - n;
	value_type const saveValue	= val;

	if (FT_UNLIKELY(pos == _start)) {
		while (n--)
			push_front(saveValue);
		return _start;
	}
	if (FT_UNLIKELY(pos == _end)) {
		while (n--)
			push_back(saveValue);
		return iterator(_end).operator--();
	}
	if (elemBefore < elemAfter) {
		_reserveFront(n);
		ft::copy(_start, _start + posIndex, _start - n);
		ft::fill_n(_start - n + posIndex, n, saveValue);
		_start -= n;
		return _start + n + posIndex - 1;
	}
	_reserveBack(n);
	ft::rcopy(_end - posIndex + 1, _end, _end + n);
	ft::fill_n(_end - posIndex + 1, n, saveValue);
	_end += n;
	return _end - n - 1;
}


template <typename T, typename Allocator>
template <typename InputIt>
typename ft::deque<T, Allocator>::iterator
ft::deque<T, Allocator>::_insertHelper(iterator pos, InputIt first, InputIt last, ft::false_type) {
	size_type posIndex			= pos - _start;
	size_type const n			= ft::distance(first, last);
	size_type const elemBefore	= posIndex;
	size_type const elemAfter	= size() - elemBefore - n;

	if (FT_UNLIKELY(pos == _start)) {
		while (first != last)
			push_front(*first++);
		return _start;
	}
	if (FT_UNLIKELY(pos == _end)) {
		while (first != last)
			push_back(*first++);
		return iterator(_end).operator--();
	}
	if (elemBefore < elemAfter) {
		_reserveFront(n);
		ft::copy(_start, _start + posIndex, _start - n);
		ft::copy(first, last, _start - n + posIndex);
		_start -= n;
		return _start + n + posIndex - 1;
	}
	_reserveBack(n);
	ft::rcopy(_end - posIndex + 1, _end, _end + n);
	ft::copy(first, last, _end - posIndex + 1);
	_end += n;
	return _end - n - 1;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_clearHelper(bool preserveMap) {
	for (iterator it = begin(); it != end(); ++it)
		_allocator.destroy(it._mCurrent);
	for (size_type i = 0; i < _mapSize; ++i)
		if (FT_LIKELY(!preserveMap || i != _mapSize / 2)) {
			_allocator.deallocate(_map[i], DEQUE_ARRAY_SIZE);
			_map[i] = NULL;
		}
	if (!preserveMap) {
		_mapAllocator().deallocate(_map, _mapSize);
		_map = NULL;
		_mapSize = 0;
		return;
	}
	_start = iterator(&_map[_mapSize / 2], &_map[_mapSize / 2][DEQUE_ARRAY_SIZE / 2]);
	_end = _start;
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::value_type **
ft::deque<T, Allocator>::_allocateMap(size_type n) {
	if (n < DEQUE_INIT_ARRAY_NUM)
		n = DEQUE_INIT_ARRAY_NUM;
	value_type **newMap = NULL;
	TRY_ALLOCATION( newMap = _mapAllocator().allocate(n); )
	ft::fill(newMap, newMap + n, static_cast<value_type*>(0));
	return newMap;
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::value_type *
ft::deque<T, Allocator>::_allocateBuffer() {
	TRY_ALLOCATION(
		return _allocator.allocate(DEQUE_ARRAY_SIZE);
	)
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_reallocateMap(size_type n) {
	if (n < DEQUE_INIT_ARRAY_NUM || n < _mapSize)
		throw ft::invalid_argument("ft::deque::_reallocateMap(): n parameter too small");
	// Make sure _mapSize is still a multiple of itself
	size_type newSize = _mapSize;
	while (newSize < n)
		newSize *= 2;
	n = newSize;
	// Allocate the new map
	value_type** oldMap = _map;
	_map = _allocateMap(n);
	// Move the data and update iterator position
	size_type const copyStart = (n - _mapSize) / 2;
	copy_n(oldMap, _mapSize, _map + copyStart);
	size_type const startOffset = _start.map - oldMap;
	size_type const endOffset = _end.map - oldMap;
	_start.map = _map + copyStart + startOffset;
	_end.map = _map + copyStart + endOffset;
	// Cleanup
	_mapAllocator().deallocate(oldMap, _mapSize);
	_mapSize = n;
}


#endif //DEQUE_TPP
