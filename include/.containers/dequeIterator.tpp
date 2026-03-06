//
// Created by mscheman on 3/6/26.
//

#ifndef DEQUE_ITERATOR_TPP
#define DEQUE_ITERATOR_TPP


// Constructor
template <typename T, typename TRef, typename TPtr>
ft::_dequeIterator<T, TRef, TPtr>::_dequeIterator(value_type** map, value_type *curr)
	: _mCurrent(curr), _mMap(map)
{
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
	: _mCurrent(iterator._mCurrent), _mBegin(iterator._mBegin), _mEnd(iterator._mEnd), _mMap(iterator._mMap)
{}


// In/Equality Operator
template <typename T, typename TRef, typename TPtr>
template <class U, class URef, class UPtr>
bool
ft::_dequeIterator<T, TRef, TPtr>::operator ==(_dequeIterator<U, URef, UPtr> CREF rhs) const
{
	return _mCurrent == rhs._mCurrent;
}


template <typename T, typename TRef, typename TPtr>
template <class U, class URef, class UPtr>
bool
ft::_dequeIterator<T, TRef, TPtr>::operator !=(_dequeIterator<U, URef, UPtr> CREF rhs) const
{
	return _mCurrent != rhs._mCurrent;
}


// Shift Operators
template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator ++()
{
	if (FT_UNLIKELY(++_mCurrent == _mEnd)) {
		if (FT_UNLIKELY(*(_mMap + 1) == NULL))
			return *this;
		_setSubarray(_mMap + 1);
		_mCurrent = _mBegin;
	}
	return *this;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator ++ (int)
{
	this_type temp(*this);
	operator++();
	return temp;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator += (difference_type n)
{
	const difference_type arrayPos = (_mCurrent - _mBegin) + n;

	if (static_cast<ft::size_t>(arrayPos) < static_cast<ft::size_t>(n))
		_mCurrent += n;
	else {
#define LARGE_OFFSET (1 << 24)
		difference_type arrayIndex = (LARGE_OFFSET + arrayPos) / static_cast<difference_type>(DEQUE_ARRAY_SIZE);
		arrayIndex -= (LARGE_OFFSET / DEQUE_ARRAY_SIZE);
		_setSubarray(_mMap + arrayIndex);
		_mCurrent = _mBegin + (arrayPos - (arrayIndex * DEQUE_ARRAY_SIZE));
#undef LARGE_OFFSET
	}
	return *this;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator + (difference_type n) const
{
	return this_type(*this).operator+=(n);
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator -- ()
{
	if (FT_UNLIKELY(_mCurrent == _mBegin)) {
		_setSubarray(_mMap - 1);
		_mCurrent = _mEnd;
	}
	--_mCurrent;
	return *this;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator -- (int)
{
	this_type temp(*this);
	operator--();
	return temp;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator -= (difference_type n)
{
	return this->operator+=(-n);
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator - (difference_type n) const
{
	return this_type(*this).operator+=(-n);
}


template <typename T, typename TRef, typename TPtr>
template <class U, class URef, class UPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::difference_type
ft::_dequeIterator<T, TRef, TPtr>::operator - (_dequeIterator<U, URef, UPtr> CREF rhs) const
{
	difference_type const bufferSize	= static_cast<difference_type>(DEQUE_ARRAY_SIZE);
	difference_type const nodeDiff		= this->_mMap - rhs._mMap;
	difference_type const offset		= (this->_mCurrent - this->_mBegin) - (rhs._mCurrent - rhs._mBegin);
	return bufferSize * nodeDiff + offset;
}


template <typename T, typename Ref, typename Ptr>
ft::_dequeIterator<T, Ref, Ptr>
operator + (ft::ptrdiff_t n, ft::_dequeIterator<T, Ref, Ptr> CREF iterator)
{
	return iterator + n;
}


// Helper Function
template <typename T, typename TRef, typename TPtr>
void
ft::_dequeIterator<T, TRef, TPtr>::_setSubarray(value_type **map)
{
	_mMap = map;
	_mBegin = *_mMap;
	_mEnd = _mBegin + DEQUE_ARRAY_SIZE;
}


#endif //DEQUE_ITERATOR_TPP