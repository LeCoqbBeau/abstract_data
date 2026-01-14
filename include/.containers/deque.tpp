//
// Created by mscheman on 1/13/26.
//

#ifndef DEQUE_TPP
#define DEQUE_TPP

#include ".helper/algorithm.hpp"
#include ".helper/ftexcept.hpp"

//	//
//	//	ft::_dequeIterator<T, TRef, TPtr>
//	//

// Constructor
template <typename T, typename TRef, typename TPtr>
ft::_dequeIterator<T, TRef, TPtr>::_dequeIterator(value_type** map, value_type *curr)
	: current(curr), map(map) {
	if (!map) {
		begin = NULL;
		end = NULL;
	} else {
		begin = *map;
		end = begin + DEQUE_ARRAY_SIZE;
	}
}


template <typename T, typename TRef, typename TPtr>
ft::_dequeIterator<T, TRef, TPtr>::_dequeIterator(_dequeIterator<T, T REF, T*> CREF iterator)
	: current(iterator.current), begin(iterator.begin), end(iterator.end), map(iterator.map)
{}


// Shift Operators
template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator ++ () {
	if (FT_UNLIKELY(++current == end)) {
		begin = *++map;
		current = begin;
		end = begin + DEQUE_ARRAY_SIZE;
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
	const difference_type arrayPos = (current - begin) + n;

	if (static_cast<ft::size_t>(arrayPos) < static_cast<ft::size_t>(n))
		current += n;
	else {
#define LARGE_OFFSET (1 << 24)
		difference_type arrayIndex = (LARGE_OFFSET + arrayPos) / static_cast<difference_type>(DEQUE_ARRAY_SIZE);
		arrayIndex -= (LARGE_OFFSET / DEQUE_ARRAY_SIZE);
		map += arrayIndex;
		begin = *map;
		end = begin + DEQUE_ARRAY_SIZE;
		current = begin + (arrayPos - (arrayIndex * DEQUE_ARRAY_SIZE));
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
	if (FT_UNLIKELY(current == begin)) {
		begin = *--map;
		current = end;
		end = begin + DEQUE_ARRAY_SIZE;
	}
	--current;
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


TWO_DEQUEIT_COMPARISON(==) { return a.current == b.current; }
TWO_DEQUEIT_COMPARISON(!=) { return !(a == b); }
TWO_DEQUEIT_COMPARISON(<) { return (a.map == b.map) ? (a.current < b.current) : (a.map < b.map); }
TWO_DEQUEIT_COMPARISON(<=) { return !(b < a); }
TWO_DEQUEIT_COMPARISON(>) { return (b < a); }
TWO_DEQUEIT_COMPARISON(>=) { return !(a < b); }

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
	difference_type const offset = (a.current - a.begin) - (b.current - b.begin);
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

// Iterators
template <class T, class Allocator>
typename ft::deque<T, Allocator>::iterator ft::deque<T, Allocator>::begin() {
	return _start;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_iterator ft::deque<T, Allocator>::begin() const {
	return _start;
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


// Element Access
template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference ft::deque<T, Allocator>::front() {
	return *_start.current;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference ft::deque<T, Allocator>::front() const {
	return *_start.current;
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::reference ft::deque<T, Allocator>::back() {
	return *(_end.current - 1);
}


template <class T, class Allocator>
typename ft::deque<T, Allocator>::const_reference ft::deque<T, Allocator>::back() const {
	return *(_end.current - 1);
}

// Modifiers
template <typename T, typename Allocator>
void ft::deque<T, Allocator>::push_back(value_type CREF value) {
	if (FT_UNLIKELY(_end.current == _end.end))
		_expandBack();
	_allocator.construct(_end.current++, value);
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::push_front(value_type CREF value) {
	if (FT_UNLIKELY(_start.current == _start.begin))
		_expandFront();
	_allocator.construct(--_start.current, value);
}


template <typename T, typename Allocator>
ft::deque<T, Allocator>::~deque()
{
	_clearHelper();
}

// Protected Members
// Helper Functions
template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_init(size_type size) {
	_map = _allocateMap(size);
	_mapSize = size;
	_map[_mapSize / 2] = _allocateBuffer();
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
void ft::deque<T, Allocator>::_expandBack() {
	if (FT_UNLIKELY(_end.map == _map + _mapSize - 1))
		_reallocateMap(_mapSize * 2);
	++_end.map;
	*_end.map = _allocateBuffer();
	_end.current = *_end.map;
	_end.begin = _end.current;
	_end.end = _end.begin + DEQUE_ARRAY_SIZE;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_expandFront() {
	if (FT_UNLIKELY(_start.map == _map))
		_reallocateMap(_mapSize * 2);
	--_start.map;
	*_start.map = _allocateBuffer();
	_start.current = *_start.map + DEQUE_ARRAY_SIZE - 1;
	_start.begin = *_start.map;
	_start.end = _start.begin + DEQUE_ARRAY_SIZE;
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_clearHelper() {
	iterator startSave = _start;
	while (_start != _end) {
		_allocator.destroy(_start.current);
		++_start;
	}
	while (startSave.map <= _end.map) {
		_allocator.deallocate(startSave.begin, DEQUE_ARRAY_SIZE);
		++startSave.map;
	}
	_mapAllocator().deallocate(_map, _mapSize);
}



template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::value_type **
ft::deque<T, Allocator>::_allocateMap(size_type n)
{
	if (n < DEQUE_INIT_ARRAY_NUM)
		n = DEQUE_INIT_ARRAY_NUM;
	return _mapAllocator().allocate(n);
}


template <typename T, typename Allocator>
typename ft::deque<T, Allocator>::value_type *
ft::deque<T, Allocator>::_allocateBuffer()
{
	return _allocator.allocate(DEQUE_ARRAY_SIZE);
}


template <typename T, typename Allocator>
void ft::deque<T, Allocator>::_reallocateMap(size_type n)
{
	if (n < DEQUE_INIT_ARRAY_NUM || n < _mapSize)
		throw ft::invalid_argument("ft::deque::_reallocateMap(): n parameter too small");
	// Allocate the new map
	value_type** oldMap = _map;
	_map = _mapAllocator().allocate(n);
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
