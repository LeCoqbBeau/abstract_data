//
// Created by mscheman on 1/24/26.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../.helper/algorithm.hpp"
#include "../.helper/ftdef.hpp"
#include "../.helper/ftexcept.hpp"
#include "../.helper/iterator.hpp"

#define MATRIX_AT_EXCEPTION_MSG ("matrix::at(): index n out of bounds")
#define MATRIX_ROW_AT_EXCEPTION_MSG ("matrix::row()::at(): index n out of bounds")

namespace ft {


template <typename T, class Ref, class Ptr, ft::size_t M, ft::size_t N>
struct _matrixIterator
	: public ft::iterator<ft::random_access_iterator_tag, T, Ptr, Ref>
{
	// Typedefs
	typedef _matrixIterator<T, Ref, Ptr, M, N>	this_type;
	typedef _matrixIterator<T, T REF, T*, M, N>	iterator;
	typedef ft::size_t							size_type;
	typedef Ref									reference;
	typedef Ptr									pointer;
	typedef ft::ptrdiff_t						difference_type;

	// Constructor
	_matrixIterator(T** matrix, size_type pos) : matrix(matrix), pos(pos) {}
	_matrixIterator(iterator it) : matrix(it.matrix), pos(it.pos) {}

	// Dereference operators
	reference	operator * () { return matrix[pos / N][pos % N]; }
	pointer		operator ->() { return &operator*(); }

	// Shift operators
	this_type REF	operator	++ ()					{ ++pos; return *this; };
	this_type		operator	++ (int)				{ this_type tmp(*this); operator++(); return tmp; };
	this_type REF	operator	+= (difference_type n)	{ pos += n; return *this; };
	this_type		operator	+  (difference_type n)	{ return this_type(*this).operator+=(n); };
	this_type REF	operator	-- ()					{ --pos; return *this; };
	this_type		operator	-- (int)				{ this_type tmp(*this); operator--(); return tmp; };
	this_type REF	operator	-= (difference_type n)	{ pos -= n; return *this; };
	this_type		operator	-  (difference_type n)	{ return this_type(*this).operator-=(n); };

	// Attributes
	T**			matrix;
	size_type	pos;
};


/**
 * @brief ft::matrix is a container that encapsulates fixed sized matrices.
 *
 * ft::matrix has been designed with std::array as inspiration. However, unlike std::array which creates a fixed-sized
 * array on the stack and therefore doesn't have to handle memory, ft::array, allocates the matrices using the templated
 * allocator type.
 *
 * @tparam T			Type of the elements contained.
 * @tparam M			Number of rows, cannot be 0.
 * @tparam N			Number of columns, is also the length of each row, as in the number of elements.
 * @tparam Allocator	The allocator to use to allocate the matrix, and construct the elements.
 */
template <typename T, ft::size_t M, ft::size_t N, typename Allocator = ft::allocator<T> >
class matrix {
	protected:
		// Proxy Structure to allow for the use of matrix[][] and matrix.at().at()
		struct _row;

	public:
		// Typedefs
		typedef	T											value_type;
		typedef T*											row_type;
		typedef T**											matrix_type;
		typedef Allocator									allocator_type;
		typedef	ft::size_t									size_type;
		typedef ft::ptrdiff_t								difference_type;
		typedef value_type REF								reference;
		typedef value_type CREF								const_reference;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef _matrixIterator<T, T REF, T*, M, N>			iterator;
		typedef _matrixIterator<T, T CREF, T const*, M, N>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		// Constructors
								matrix(allocator_type CREF alloc = allocator_type());
								matrix(size_type n, value_type CREF val = value_type(), allocator_type CREF alloc = allocator_type());
		template<class InputIt>	matrix(InputIt first, InputIt last, allocator_type CREF alloc = allocator_type(),
										ENABLE_IF_TT(!IS_INTEGRAL_V(InputIt), InputIt)* = 0);
								matrix(matrix CREF x);
		matrix REF operator		= (matrix CREF rhs);
		~matrix();

		// Iterators
		iterator					begin();
		const_iterator				begin() const;
		iterator					end();
		const_iterator				end() const;
		reverse_iterator			rbegin();
		const_reverse_iterator		rbegin() const;
		reverse_iterator			rend();
		const_reverse_iterator		rend() const;

		// Capacity
		size_type					size() const;
		size_type					max_size() const;
		bool						empty() const;

		// Element Access
		reference		operator	[](size_type n);
		const_reference	operator	[](size_type n) const;
		reference 					at(size_type n);
		const_reference	 			at(size_type n) const;
		_row						row(size_type m);
		_row const					row(size_type m) const;
		reference					front();
		const_reference				front() const;
		reference					back();
		const_reference				back() const;
		matrix_type					data();
		matrix_type const			data() const;

		// Modifiers
		void						fill(value_type CREF value);
		void						swap(matrix REF other);

	protected:
		// Proxy Structure
		struct _row {
			// Constructor
			_row(row_type row, size_type length) : row(row), length(length) {}

			// Element Access
			reference		operator	[](size_type n);
			const_reference	operator	[](size_type n) const;
			reference	 				at(size_type n);
			const_reference	 			at(size_type n) const;
			reference					col(size_type n);
			const_reference				col(size_type n) const;
			reference					front();
			const_reference				front() const;
			reference					back();
			const_reference				back() const;
			row_type					data();
			row_type const				data() const;

			// Attributes
			row_type	row;
			size_type	length;
		};

	protected:
		// Typedefs
		typedef typename allocator_type::template rebind<row_type>::other _matrixAllocator;

		// Helper Functions
		void	_init();
		void	_clean();

		// Attributes
		matrix_type				_matrix;
		size_type				_size;
		mutable allocator_type	_allocator;
		_matrixAllocator		_rowAllocator() { return _matrixAllocator(_allocator); }
};


}


#define MATRIX_COMPARISON_OPERATOR(op)	\
	template <typename T, ft::size_t M, ft::size_t N, typename Allocator>	\
		bool operator op (ft::matrix<T, M, N, Allocator> CREF lhs, ft::matrix<T, M, N, Allocator> CREF rhs)


MATRIX_COMPARISON_OPERATOR(==) {
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}


MATRIX_COMPARISON_OPERATOR(!=) {
	return !(lhs == rhs);
}


MATRIX_COMPARISON_OPERATOR(<) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


MATRIX_COMPARISON_OPERATOR(<=) {
	return !(rhs < lhs);
}


MATRIX_COMPARISON_OPERATOR(>) {
	return (rhs < lhs);
}


MATRIX_COMPARISON_OPERATOR(>=) {
	return !(lhs < rhs);
}


#include "matrix.tpp"


#undef MATRIX_COMPARISON_OPERATOR

#endif //MATRIX_HPP
