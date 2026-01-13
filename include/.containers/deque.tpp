//
// Created by mscheman on 1/13/26.
//

#ifndef DEQUE_TPP
#define DEQUE_TPP

template <typename T, typename TRef, typename TPtr>
ft::_dequeIterator<T, TRef, TPtr>::_dequeIterator()
	: _curr(NULL), _begin(NULL), _end(NULL), _array(NULL) {}


template <typename T, typename TRef, typename TPtr>
ft::_dequeIterator<T, TRef, TPtr>::_dequeIterator(_dequeIterator<T, T REF, T*> CREF rhs)
	: _curr(rhs._curr), _begin(rhs._begin), _end(rhs._end), _array(rhs._end) {}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator ++ () {
	if (FT_UNLIKELY(++_curr == _end)) {
		_begin = *++_array;
		_end = _begin + DEQUE_ARRAY_SIZE;
		_curr = _begin;
	}
	return *this;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator ++ (int) {
	this_type tempIt(*this);
	operator ++ ();
	return tempIt;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator -- () {
	if (FT_UNLIKELY(--_curr == _begin)) {
		_begin = *--_array;
		_end = _begin + DEQUE_ARRAY_SIZE;
		_curr = _end;
	}
	--_curr;
	return *this;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator -- (int) {
	this_type tempIt(*this);
	operator -- ();
	return tempIt;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator += (difference_type n) {
	ft::ptrdiff_t subArrayPos = _curr - _begin + n;
	if (static_cast<ft::size_t>(n) < static_cast<ft::size_t>(DEQUE_ARRAY_SIZE))
		_curr += n;
	else {
		// EASTL magic???
#define	LARGE_OFFSET (1 << 24) // 2^24 = 16777216
		difference_type newArrayPos = subArrayPos;
		newArrayPos += LARGE_OFFSET;
		newArrayPos /= static_cast<ft::size_t>(DEQUE_ARRAY_SIZE);
		newArrayPos -= (LARGE_OFFSET / static_cast<ft::size_t>(DEQUE_ARRAY_SIZE));
		// :)

	}
	return *this;
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type REF
ft::_dequeIterator<T, TRef, TPtr>::operator -= (difference_type n) {
	return (*this).operator+=(-n);
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator + (difference_type n) const {
	return this_type(*this).operator+=(n);
}


template <typename T, typename TRef, typename TPtr>
typename ft::_dequeIterator<T, TRef, TPtr>::this_type
ft::_dequeIterator<T, TRef, TPtr>::operator - (difference_type n) const {
	return this_type(*this).operator-=(n);
}



#endif //DEQUE_TPP
