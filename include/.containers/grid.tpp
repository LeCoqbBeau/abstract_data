//
// Created by mscheman on 1/24/26.
//

#ifndef GRID_TPP
#define GRID_TPP


// Constructor
template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
ft::internal::gridIterator<T, Ref, Ptr, M, N>::gridIterator(pointer data, size_type pos)
	: _data(data), _pos(pos)
{}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
ft::internal::gridIterator<T, Ref, Ptr, M, N>::gridIterator(gridIterator<T, T REF, T*, M, N> CREF iterator)
	: _data(iterator._data), _pos(iterator._pos)
{}


// In/Equality Operator
template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
bool
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator	== (this_type CREF rhs) const
{
	return _data == rhs._data && _pos == rhs._pos;
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
bool
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator	!= (this_type CREF rhs) const
{
	return !(*this == rhs);
}

// Dereference Operator


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::reference
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator * ()
{
	return _data[_pos];
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::pointer
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator -> ()
{
	return _data + _pos;
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::reference
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator [] (difference_type n)
{
	return _data[_pos + n];
}


// Shift Operators
template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::this_type REF
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator ++ ()
{
	++_pos;
	return (*this);
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::this_type
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator ++ (int)
{
	this_type tmp(*this);
	this->operator++();
	return tmp;
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::this_type REF
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator += (difference_type n)
{
	_pos += n;
	return *this;
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::this_type
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator + (difference_type n)
{
	return this_type(*this).operator+=(n);
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::this_type REF
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator -- ()
{
	--_pos;
	return (*this);
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::this_type
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator -- (int)
{
	this_type tmp(*this);
	this->operator++();
	return tmp;
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::this_type REF
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator -= (difference_type n)
{
	_pos -= n;
	return (*this);
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::this_type
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator - (difference_type n)
{
	return this_type(*this).operator-=(n);
}


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
typename ft::internal::gridIterator<T, Ref, Ptr, M, N>::difference_type
ft::internal::gridIterator<T, Ref, Ptr, M, N>::operator - (this_type CREF rhs)
{
	return _pos - rhs._pos;
}


#define TWO_GRIDIT_TEMPLATE			template <typename T, typename RefA, typename PtrA, typename RefB, typename PtrB, unsigned int M, unsigned int N>
#define TWO_GRIDIT_PARAM			ft::internal::gridIterator<T, RefA, PtrA, M, N> CREF lhs, ft::internal::gridIterator<T, RefB, PtrB, M, N> CREF rhs
#define TWO_GRIDIT_COMPARISON(op)	TWO_GRIDIT_TEMPLATE inline bool operator op (TWO_GRIDIT_PARAM)

TWO_GRIDIT_COMPARISON(<)	{ return lhs._pos < rhs._pos ; }
TWO_GRIDIT_COMPARISON(<=)	{ return !(rhs < lhs); }
TWO_GRIDIT_COMPARISON(>)	{ return (rhs < lhs); }
TWO_GRIDIT_COMPARISON(>=)	{ return !(lhs < rhs); }

#undef TWO_GRIDIT_TEMPLATE
#undef TWO_GRIDIT_PARAM
#undef TWO_GRIDIT_COMPARISON


//
//	ft::grid<T, M, N>
//


// Constructors
template <typename T, unsigned int M, unsigned int N>
ft::grid<T, M, N>::grid()
{
	fill(value_type());
}


template <typename T, unsigned int M, unsigned int N>
ft::grid<T, M, N>::grid(const_reference value)
{
	fill(value);
}


template <typename T, unsigned int M, unsigned int N>
template <typename InputIt>
ft::grid<T, M, N>::grid(InputIt first, InputIt last)
{
	for (size_type m = 0; m != M; ++m)
		for (size_type n = 0; n != N; ++n) {
			if (first == last)
				_grid[m][n] = value_type();
			else
				_grid[m][n] = *first++;
		}
}


template <typename T, unsigned int M, unsigned int N>
ft::grid<T, M, N>::grid(grid CREF other)
{
	*this = other;
}


template <typename T, unsigned int M, unsigned int N>
ft::grid<T, M, N> REF
ft::grid<T, M, N>::operator = (grid CREF other)
{
	if (this != &other)
		for (size_type m = 0; m != M; ++m)
			for (size_type n = 0; n != N; ++n)
				_grid[m][n] = other[m][n];
	return *this;
}


template <typename T, unsigned int M, unsigned int N>
ft::grid<T, M, N>::~grid() {}


// Iterators
template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::iterator
ft::grid<T, M, N>::begin()
{
	return iterator(data(), 0);
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_iterator
ft::grid<T, M, N>::begin() const
{
	return const_iterator(data(), 0);
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::iterator
ft::grid<T, M, N>::end()
{
	return iterator(data(), M * N);
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_iterator
ft::grid<T, M, N>::end() const
{
	return const_iterator(data(), M * N);
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::reverse_iterator
ft::grid<T, M, N>::rbegin()
{
	return reverse_iterator(end());
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_reverse_iterator
ft::grid<T, M, N>::rbegin() const
{
	return const_reverse_iterator(end());
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::reverse_iterator
ft::grid<T, M, N>::rend()
{
	return reverse_iterator(begin());
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_reverse_iterator
ft::grid<T, M, N>::rend() const
{
	return const_reverse_iterator(begin());
}


// Element Access
template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::pointer
ft::grid<T, M, N>::operator [](size_type m)
{
	return _grid[m];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_pointer
ft::grid<T, M, N>::operator [](size_type m) const
{
	return _grid[m];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::reference
ft::grid<T, M, N>::at(size_type m, size_type n)
{
	if (m >= M)
		throw ft::out_of_range(GRID_AT_M_EXCEPTION_MSG);
	if (n >= N)
		throw ft::out_of_range(GRID_AT_N_EXCEPTION_MSG);
	return _grid[m][n];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_reference
ft::grid<T, M, N>::at(size_type m, size_type n) const
{
	if (m >= M)
		throw ft::out_of_range(GRID_AT_M_EXCEPTION_MSG);
	if (n >= N)
		throw ft::out_of_range(GRID_AT_N_EXCEPTION_MSG);
	return _grid[m][n];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::reference
ft::grid<T, M, N>::front()
{
	return _grid[0][0];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_reference
ft::grid<T, M, N>::front() const
{
	return _grid[0][0];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::reference
ft::grid<T, M, N>::front(size_type m)
{
	return _grid[m][0];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_reference
ft::grid<T, M, N>::front(size_type m) const
{
	return _grid[m][0];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::reference
ft::grid<T, M, N>::back()
{
	return _grid[M - 1][N - 1];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_reference
ft::grid<T, M, N>::back() const
{
	return _grid[M - 1][N - 1];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::reference
ft::grid<T, M, N>::back(size_type m)
{
	return _grid[m][N - 1];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_reference
ft::grid<T, M, N>::back(size_type m) const
{
	return _grid[m][N - 1];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::pointer
ft::grid<T, M, N>::data()
{
	return &_grid[0][0];
}


template <typename T, unsigned int M, unsigned int N>
typename ft::grid<T, M, N>::const_pointer
ft::grid<T, M, N>::data() const
{
	return &_grid[0][0];
}


// Modifiers
template <typename T, unsigned int M, unsigned int N>
void
ft::grid<T, M, N>::fill(const_reference value)
{
	for (size_type m = 0; m != M; ++m)
		for (size_type n = 0; n != N; ++n)
			_grid[m][n] = value;
}


template <typename T, unsigned int M, unsigned int N>
void
ft::grid<T, M, N>::swap(grid REF rhs)
{
	for (size_type m = 0; m != M; ++m)
		for (size_type n = 0; n != N; ++n)
			ft::swap(_grid[m][n], rhs[m][n]);
}


#endif //GRID_TPP
