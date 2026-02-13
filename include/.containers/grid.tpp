//
// Created by mscheman on 1/24/26.
//

#ifndef GRID_TPP
#define GRID_TPP

#include ".helper/assertion.hpp"
#include ".helper/new.hpp"

//
//	ft::_gridIterator<>
//

#define TWO_GRIDIT_TEMPLATE	\
	template <typename U, typename RefA, typename PtrA, typename RefB, typename PtrB, ft::size_t M, ft::size_t N>
#define TWO_GRIDIT_PARAMETERS	\
	ft::_gridIterator<U, RefA, PtrA, M, N> CREF a, ft::_gridIterator<U, RefB, PtrB, M, N> CREF b
#define TWO_GRIDIT_COMPARISON(op) TWO_GRIDIT_TEMPLATE inline bool operator op (TWO_GRIDIT_PARAMETERS)


TWO_GRIDIT_COMPARISON(==)	{ return a.pos == b.pos; }
TWO_GRIDIT_COMPARISON(!=)	{ return !(a == b); }
TWO_GRIDIT_COMPARISON(<)	{ return a.pos < b.pos; }
TWO_GRIDIT_COMPARISON(<=)	{ return !(b < a); }
TWO_GRIDIT_COMPARISON(>)	{ return b < a; }
TWO_GRIDIT_COMPARISON(>=)	{ return !(a < b); }


template <typename T, typename Ref, typename Ptr, ft::size_t M, ft::size_t N>
typename ft::_gridIterator<T, Ref, Ptr, M, N>::iterator
operator + (ft::ptrdiff_t n, ft::_gridIterator<T, Ref, Ptr, M, N> CREF it)
{
	return it + n;
}


TWO_GRIDIT_TEMPLATE
typename ft::_gridIterator<U, RefA, PtrA, M, N>::difference_type
operator - (TWO_GRIDIT_PARAMETERS)
{
	return a.pos - b.pos;
}


#undef TWO_GRIDIT_COMPARISON
#undef TWO_GRIDIT_PARAMETERS
#undef TWO_GRIDIT_TEMPLATE

//
//	ft::grid<>
//

// Constructor
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::grid<T, M, N, Allocator>::grid(allocator_type CREF alloc)
	: _grid(NULL), _size(0), _allocator(alloc)
{
	_init();
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::grid<T, M, N, Allocator>::grid(size_type n, value_type CREF val, allocator_type CREF alloc)
	: _grid(NULL), _allocator(alloc)
{
	_init();
	size_type i = 0;
	for (; i < n && i < M * N; ++i)
		_allocator.construct(&operator[](i), val);
	_size = i;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
template<class InputIt>
ft::grid<T, M, N, Allocator>::grid(InputIt first, InputIt last, allocator_type CREF alloc, ENABLE_IF_TT(!IS_INTEGRAL_V(InputIt), InputIt)*)
	: _grid(NULL), _allocator(alloc)
{
	_init();
	size_type i = 0;
	for (InputIt it = first; it != last && i < N * M; ++it, ++i)
		_allocator.construct(&operator[](i), *it);
	_size = i;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::grid<T, M, N, Allocator>::grid(grid CREF x)
	: _grid(NULL), _allocator(x._allocator)
{
	*this = x;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::grid<T, M, N, Allocator> REF
ft::grid<T, M, N, Allocator>::operator = (grid CREF rhs)
{
	if (this != rhs) {
		_clean();
		_init();
		for (size_type i = 0; i < rhs._size; ++i)
			_grid[i / N][i % N] = rhs[i];
	}
	return *this;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
ft::grid<T, M, N, Allocator>::~grid()
{
	_clean();
}


// Iterators
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::iterator
ft::grid<T, M, N, Allocator>::begin()
{
	return iterator(_grid, 0);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_iterator
ft::grid<T, M, N, Allocator>::begin() const
{
	return const_iterator(_grid, 0);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::iterator
ft::grid<T, M, N, Allocator>::end()
{
	return iterator(_grid, M * N);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_iterator
ft::grid<T, M, N, Allocator>::end() const
{
	return const_iterator(_grid, M * N);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reverse_iterator
ft::grid<T, M, N, Allocator>::rbegin()
{
	return reverse_iterator(end());
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reverse_iterator
ft::grid<T, M, N, Allocator>::rbegin() const
{
	return const_reverse_iterator(end());
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reverse_iterator
ft::grid<T, M, N, Allocator>::rend()
{
	return reverse_iterator(begin());
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reverse_iterator
ft::grid<T, M, N, Allocator>::rend() const
{
	return const_reverse_iterator(begin());
}


// Capacity
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::size_type
ft::grid<T, M, N, Allocator>::size() const
{
	return _size;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::size_type
ft::grid<T, M, N, Allocator>::max_size() const
{
	return M * N;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
bool
ft::grid<T, M, N, Allocator>::empty() const
{
	return false;
}


// Element Access
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reference
ft::grid<T, M, N, Allocator>::operator [] (size_type n)
{
		return _grid[n / N][n % N];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reference
ft::grid<T, M, N, Allocator>::operator [] (size_type n) const
{
	return _grid[n / N][n % N];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reference
ft::grid<T, M, N, Allocator>::at(size_type n)
{
	if (n >= M * N)
		throw out_of_range(GRID_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reference
ft::grid<T, M, N, Allocator>::at(size_type n) const
{
	if (n >= M * N)
		throw out_of_range(GRID_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::_row
ft::grid<T, M, N, Allocator>::row(size_type m)
{
	return _row(_grid[m / N]);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::_row const
ft::grid<T, M, N, Allocator>::row(size_type m) const
{
	return _row(_grid[m / N]);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reference
ft::grid<T, M, N, Allocator>::front()
{
	return _grid[0];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reference
ft::grid<T, M, N, Allocator>::front() const
{
	return _grid[0];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reference
ft::grid<T, M, N, Allocator>::back()
{
	return _grid[_size - 1];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reference
ft::grid<T, M, N, Allocator>::back() const
{
	return _grid[_size - 1];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::grid_type
ft::grid<T, M, N, Allocator>::data()
{
	return _grid;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::grid_type const
ft::grid<T, M, N, Allocator>::data() const
{
	return _grid;
}


// Modifiers
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::grid<T, M, N, Allocator>::fill(value_type CREF value)
{
	ft::fill(this->begin(), this->end(), value);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::grid<T, M, N, Allocator>::swap(grid REF other)
{
	ft::swap(_grid, other._grid);
}


// Protected Helper Functions
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::grid<T, M, N, Allocator>::_init()
{
	assert((ft::is_not_equal<M, 0>::value));
	assert((ft::is_not_equal<N, 0>::value));
	if (_grid)
		return;
	_grid = _gridAllocator().allocate(M);
	for (size_type m = 0; m < M; ++m) {
		TRY_ALLOC(
			_grid[m] = _allocator.allocate(N);,
			while (m) {
				--m;
				_allocator.deallocate(_grid[m], N);
			}
		)
		::new(static_cast<void*>(_grid[m])) value_type;
	}
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::grid<T, M, N, Allocator>::_init(value_type CREF value)
{
	assert((ft::is_not_equal<M, 0>::value));
	assert((ft::is_not_equal<N, 0>::value));
	if (_grid)
		return;
	size_type	lastN = 0;
	size_type	lastM = 0;
	TRY_ALLOC( _grid = _gridAllocator().allocate(M);,; );
	for (size_type m = 0; m < M; ++m) {
		TRY_ALLOC(
			_grid[m] = _allocator.allocate(N);
			lastM = m;
			for (size_type n = 0; n < N; ++n) {
				::new(static_cast<void*>(&_grid[m][n])) value_type(value);
				lastN = n;
			},
			_initUnleak(lastM, lastN);
		)
	}
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::grid<T, M, N, Allocator>::_clean()
{
	if (!_grid)
		return;
	for (size_type m = 0; m < M; ++m) {
		for (size_type n = 0; n < N; ++n)
			_allocator.destroy(&_grid[m][n]);
		_allocator.deallocate(_grid[m], N);
	}
	_gridAllocator().deallocate(_grid, M);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
void
ft::grid<T, M, N, Allocator>::_initUnleak(size_type lastM, size_type lastN) {
	while (lastN)
		_allocator.destroy(_grid[lastM][lastN--]);
	while (lastM) {
		--lastM;
		for (size_type n = 0; n < N; ++n)
			_allocator.destroy(&_grid[lastM][n]);
		_allocator.deallocate(_grid[lastM], N);
	}
	_allocator.deallocate(_grid, M);
}


//
//	ft::grid<>:_row
//


// Element Access
template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reference
ft::grid<T, M, N, Allocator>::_row::_row::operator [](size_type n)
{
	return row[n];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reference
ft::grid<T, M, N, Allocator>::_row::_row::operator [](size_type n) const
{
	return row[n];
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reference
ft::grid<T, M, N, Allocator>::_row::_row::at(size_type n)
{
	if (n >= N)
		throw ft::out_of_range(GRID_ROW_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reference
ft::grid<T, M, N, Allocator>::_row::_row::at(size_type n) const
{
	if (n >= N)
		throw ft::out_of_range(GRID_ROW_AT_EXCEPTION_MSG);
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reference
ft::grid<T, M, N, Allocator>::_row::_row::col(size_type n)
{
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reference
ft::grid<T, M, N, Allocator>::_row::_row::col(size_type n) const
{
	return operator[](n);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reference
ft::grid<T, M, N, Allocator>::_row::_row::front()
{
	return operator[](0);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reference
ft::grid<T, M, N, Allocator>::_row::_row::front() const
{
	return operator[](0);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::reference
ft::grid<T, M, N, Allocator>::_row::_row::back()
{
	return operator[](N - 1);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>
typename ft::grid<T, M, N, Allocator>::const_reference
ft::grid<T, M, N, Allocator>::_row::_row::back() const
{
	return operator[](N - 1);
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>

typename ft::grid<T, M, N, Allocator>::row_type
ft::grid<T, M, N, Allocator>::_row::_row::data()
{
	return row;
}


template <typename T, ft::size_t M, ft::size_t N, typename Allocator>

typename ft::grid<T, M, N, Allocator>::row_type const
ft::grid<T, M, N, Allocator>::_row::_row::data() const
{
	return row;
}


#endif //GRID_TPP
