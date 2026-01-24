//
// Created by mscheman on 1/24/26.
//

#ifndef MATRIX_TPP
#define MATRIX_TPP

#include ".helper/assertion.hpp"
#include ".helper/new.hpp"

//
//	ft::_matrixIterator<>
//

#define TWO_MATRIXIT_TEMPLATE	\
	template <typename U, typename RefA, typename PtrA, typename RefB, typename PtrB, ft::size_t M, ft::size_t N>
#define TWO_MATRIXIT_PARAMETERS	\
	ft::_matrixIterator<U, RefA, PtrA, M, N> CREF a, ft::_matrixIterator<U, RefB, PtrB, M, N> CREF b
#define TWO_MATRIXIT_COMPARISON(op) TWO_MATRIXIT_TEMPLATE inline bool operator op (TWO_MATRIXIT_PARAMETERS)


TWO_MATRIXIT_COMPARISON(==) { return a.pos == b.pos; }
TWO_MATRIXIT_COMPARISON(!=) { return !(a == b); }
TWO_MATRIXIT_COMPARISON(<) { return a.pos < b.pos; }
TWO_MATRIXIT_COMPARISON(<=) { return !(b < a); }
TWO_MATRIXIT_COMPARISON(>) { return b < a; }
TWO_MATRIXIT_COMPARISON(>=) { return !(a < b); }


template <typename T, typename Ref, typename Ptr, ft::size_t M, ft::size_t N>
typename ft::_matrixIterator<T, Ref, Ptr, M, N>::iterator
operator + (ft::ptrdiff_t n, ft::_matrixIterator<T, Ref, Ptr, M, N> CREF it)
{
	return it + n;
}


TWO_MATRIXIT_TEMPLATE
typename ft::_matrixIterator<U, RefA, PtrA, M, N>::difference_type
operator - (TWO_MATRIXIT_PARAMETERS)
{
	return a.pos - b.pos;
}


#undef TWO_MATRIXIT_COMPARISON
#undef TWO_MATRIXIT_PARAMETERS
#undef TWO_MATRIXIT_TEMPLATE

//
//	ft::matrix<>
//

// Constructor
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::matrix<T, M, N, Allocator>::matrix(allocator_type CREF alloc)
	: _matrix(NULL), _size(0), _allocator(alloc)
{
	_init();
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::matrix<T, M, N, Allocator>::matrix(size_type n, value_type CREF val, allocator_type CREF alloc)
	: _matrix(NULL), _allocator(alloc)
{
	_init();
	size_type i = 0;
	for (; i < n && i < M * N; ++i)
		_allocator.construct(&operator[](i), val);
	_size = i;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
template<class InputIt>
ft::matrix<T, M, N, Allocator>::matrix(InputIt first, InputIt last, allocator_type CREF alloc, ENABLE_IF_TT(!IS_INTEGRAL_V(InputIt), InputIt)*)
	: _matrix(NULL), _allocator(alloc)
{
	_init();
	size_type i = 0;
	for (InputIt it = first; it != last && i < N * M; ++it, ++i)
		_allocator.construct(&operator[](i), *it);
	_size = i;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::matrix<T, M, N, Allocator>::matrix(matrix CREF x)
	: _matrix(NULL), _allocator(x._allocator)
{
	*this = x;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::matrix<T, M, N, Allocator> REF
ft::matrix<T, M, N, Allocator>::operator = (matrix CREF rhs)
{
	if (this != rhs) {
		_clean();
		_init();
		for (size_type i = 0; i < rhs._size; ++i)
			_matrix[i / N][i % N] = rhs[i];
		_size = rhs._size;
	}
	return *this;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::matrix<T, M, N, Allocator>::~matrix()
{
	_clean();
}


// Iterators
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::iterator
ft::matrix<T, M, N, Allocator>::begin()
{
	return iterator(_matrix, 0);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_iterator
ft::matrix<T, M, N, Allocator>::begin() const
{
	return const_iterator(_matrix, 0);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::iterator
ft::matrix<T, M, N, Allocator>::end()
{
	return iterator(_matrix, M * N);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_iterator
ft::matrix<T, M, N, Allocator>::end() const
{
	return const_iterator(_matrix, M * N);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reverse_iterator
ft::matrix<T, M, N, Allocator>::rbegin()
{
	return reverse_iterator(end());
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reverse_iterator
ft::matrix<T, M, N, Allocator>::rbegin() const
{
	return const_reverse_iterator(end());
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reverse_iterator
ft::matrix<T, M, N, Allocator>::rend()
{
	return reverse_iterator(begin());
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reverse_iterator
ft::matrix<T, M, N, Allocator>::rend() const
{
	return const_reverse_iterator(begin());
}


// Capacity
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::size_type
ft::matrix<T, M, N, Allocator>::size() const
{
	return _size;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::size_type
ft::matrix<T, M, N, Allocator>::max_size() const
{
	return M * N;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
bool
ft::matrix<T, M, N, Allocator>::empty() const
{
	return !_size;
}


// Element Access
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reference
ft::matrix<T, M, N, Allocator>::operator [] (size_type n)
{
		return _matrix[n / N][n % N];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reference
ft::matrix<T, M, N, Allocator>::operator [] (size_type n) const
{
	return _matrix[n / N][n % N];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reference
ft::matrix<T, M, N, Allocator>::at(size_type n)
{
	if (n >= _size)
		throw out_of_range(MATRIX_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reference
ft::matrix<T, M, N, Allocator>::at(size_type n) const
{
	if (n >= _size)
		throw out_of_range(MATRIX_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::_row
ft::matrix<T, M, N, Allocator>::row(size_type m)
{
	size_type const accessedRow = m / N;
	size_type const rowLength = (accessedRow < _size / N)
									? N
								: (accessedRow == _size / N)
									? (_size % N) : 0;
	return _row(
		_matrix[accessedRow],
		rowLength
	);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::_row const
ft::matrix<T, M, N, Allocator>::row(size_type m) const
{
	size_type const accessedRow = m / N;
	size_type const rowLength = (accessedRow < _size / N)
									? N
								: (accessedRow == _size / N)
									? (_size % N) : 0;
	return _row(
		_matrix[accessedRow],
		rowLength
	);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reference
ft::matrix<T, M, N, Allocator>::front()
{
	return _matrix[0];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reference
ft::matrix<T, M, N, Allocator>::front() const
{
	return _matrix[0];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reference
ft::matrix<T, M, N, Allocator>::back()
{
	return _matrix[_size - 1];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reference
ft::matrix<T, M, N, Allocator>::back() const
{
	return _matrix[_size - 1];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::matrix_type
ft::matrix<T, M, N, Allocator>::data()
{
	return _matrix;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::matrix_type const
ft::matrix<T, M, N, Allocator>::data() const
{
	return _matrix;
}


// Modifiers
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::matrix<T, M, N, Allocator>::fill(value_type CREF value)
{
	ft::fill(this->begin(), this->end(), value);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::matrix<T, M, N, Allocator>::swap(matrix REF other)
{
	ft::swap(_matrix, other._matrix);
}


// Protected Helper Functions
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::matrix<T, M, N, Allocator>::_init()
{
	assert((ft::is_not_equal<M, 0>::value));
	assert((ft::is_not_equal<N, 0>::value));
	if (_matrix)
		return;
	_matrix = _matrixAllocator().allocate(M);
	for (size_type m = 0; m < M; ++m) {
		TRY_ALLOCATION(
			_matrix[m] = _allocator.allocate(N);,
			while (m) {
				--m;
				_allocator.deallocate(_matrix[m], N);
			}
		)
	}
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::matrix<T, M, N, Allocator>::_clean()
{
	assert((ft::is_not_equal<M, 0>::value));
	assert((ft::is_not_equal<N, 0>::value));
	if (!_matrix)
		return;
	for (size_type m = 0; m < M; ++m)
		_allocator.deallocate(_matrix[m], N);
	_matrixAllocator().deallocate(_matrix, M);
}


//
//	ft::matrix<>:_row
//


// Element Access
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reference
ft::matrix<T, M, N, Allocator>::_row::_row::operator [](size_type n)
{
	return row[n];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reference
ft::matrix<T, M, N, Allocator>::_row::_row::operator [](size_type n) const
{
	return row[n];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reference
ft::matrix<T, M, N, Allocator>::_row::_row::at(size_type n)
{
	if (n > length)
		throw ft::out_of_range(MATRIX_ROW_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reference
ft::matrix<T, M, N, Allocator>::_row::_row::at(size_type n) const
{
	if (n > length)
		throw ft::out_of_range(MATRIX_ROW_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reference
ft::matrix<T, M, N, Allocator>::_row::_row::col(size_type n)
{
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reference
ft::matrix<T, M, N, Allocator>::_row::_row::col(size_type n) const
{
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reference
ft::matrix<T, M, N, Allocator>::_row::_row::front()
{
	return operator[](0);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reference
ft::matrix<T, M, N, Allocator>::_row::_row::front() const
{
	return operator[](0);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::reference
ft::matrix<T, M, N, Allocator>::_row::_row::back()
{
	return operator[](length - 1);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::matrix<T, M, N, Allocator>::const_reference
ft::matrix<T, M, N, Allocator>::_row::_row::back() const
{
	return operator[](length - 1);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>

typename ft::matrix<T, M, N, Allocator>::row_type
ft::matrix<T, M, N, Allocator>::_row::_row::data()
{
	return row;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>

typename ft::matrix<T, M, N, Allocator>::row_type const
ft::matrix<T, M, N, Allocator>::_row::_row::data() const
{
	return row;
}


#endif //MATRIX_TPP
