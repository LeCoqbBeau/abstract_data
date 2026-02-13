//
// Created by mscheman on 1/24/26.
//

#ifndef GRID_HPP
#define GRID_HPP

#include ".helper/algorithm.hpp"
#include ".helper/ftdef.hpp"
#include ".helper/ftexcept.hpp"
#include ".helper/iterator.hpp"

#define GRID_AT_EXCEPTION_MSG ("matrix::at(): index n out of bounds")
#define GRID_ROW_AT_EXCEPTION_MSG ("matrix::row()::at(): index n out of bounds")

namespace ft {


template <typename T, class Ref, class Ptr, ft::size_t M, ft::size_t N>
struct _gridIterator
	: public ft::iterator<ft::random_access_iterator_tag, T, Ptr, Ref>
{
	// Typedefs
	typedef _gridIterator<T, Ref, Ptr, M, N>	this_type;
	typedef _gridIterator<T, T REF, T*, M, N>	iterator;
	typedef ft::size_t							size_type;
	typedef Ref									reference;
	typedef Ptr									pointer;
	typedef ft::ptrdiff_t						difference_type;

	// Constructor
	_gridIterator(T** matrix, size_type pos) : matrix(matrix), pos(pos) {}
	_gridIterator(iterator it) : matrix(it.matrix), pos(it.pos) {}

	// Dereference operators
	reference		operator	* () 					{ return matrix[pos / N][pos % N]; }
	pointer			operator	->() 					{ return &operator*(); }

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
 * @brief ft::grid is a container that encapsulates fixed sized matrices.
 *
 * ft::grid has been designed with std::array as inspiration. However, unlike std::array which creates a fixed-sized
 * array on the stack and therefore doesn't have to handle memory, ft::array, allocates the matrices using the templated
 * allocator type.
 *
 * @tparam T			Type of the elements contained.
 * @tparam M			Number of rows, cannot be 0.
 * @tparam N			Number of columns, is also the length of each row, as in the number of elements.
 * @tparam Allocator	The allocator to use to allocate the matrix, and construct the elements.
 */
template <typename T, ft::size_t M, ft::size_t N, typename Allocator = ft::allocator<T> >
class grid {
	protected:
		// Proxy Structure to allow for the use of matrix[][] and matrix.at().at()
		struct _row;

	public:
		// Typedefs
		typedef	T											value_type;
		typedef _row										row_type;
		typedef T**											grid_type;
		typedef Allocator									allocator_type;
		typedef	ft::size_t									size_type;
		typedef ft::ptrdiff_t								difference_type;
		typedef value_type REF								reference;
		typedef value_type CREF								const_reference;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef _gridIterator<T, T REF, T*, M, N>			iterator;
		typedef _gridIterator<T, T CREF, T const*, M, N>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		// Constructors
									grid(allocator_type CREF alloc = allocator_type());
									grid(size_type n, value_type CREF value = value_type(), allocator_type CREF alloc = allocator_type());
		template<class InputIt>		grid(InputIt first, InputIt last, allocator_type CREF alloc = allocator_type(),
											ENABLE_IF_TT(!IS_INTEGRAL_V(InputIt), InputIt)* = 0);
									grid(grid CREF x);
		grid REF		operator	=(grid CREF rhs);
		~grid();

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
		row_type					row(size_type m);
		row_type const				row(size_type m) const;
		reference					front();
		const_reference				front() const;
		reference					back();
		const_reference				back() const;
		grid_type					data();
		grid_type const				data() const;

		// Modifiers
		void						fill(value_type CREF value);
		void						swap(grid REF other);

	protected:
		// Proxy Structure
		struct _row {
			// Constructor
			_row(pointer row) : row(row) {}

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
			pointer						data();
			pointer const				data() const;

			// Attributes
			pointer						row;
		};

	protected:
		// Typedefs
		typedef typename allocator_type::template rebind<pointer>::other _grid_allocator_type;

		// Helper Functions
		void					_init();
		void					_init(value_type CREF value);
		void					_clean();

		// Attributes
		grid_type				_grid;
		size_type				_size;
		mutable allocator_type	_allocator;
		_grid_allocator_type	_gridAllocator() { return _grid_allocator_type(_allocator); }
		void					_initUnleak(size_type lastM, size_type lastN);
};


}


#define GRID_COMPARISON_OPERATOR(op)	\
	template <typename T, ft::size_t M, ft::size_t N, typename Allocator>	\
		bool operator op (ft::grid<T, M, N, Allocator> CREF lhs, ft::grid<T, M, N, Allocator> CREF rhs)


GRID_COMPARISON_OPERATOR(==) {
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}


GRID_COMPARISON_OPERATOR(!=) {
	return !(lhs == rhs);
}


GRID_COMPARISON_OPERATOR(<) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}


GRID_COMPARISON_OPERATOR(<=) {
	return !(rhs < lhs);
}


GRID_COMPARISON_OPERATOR(>) {
	return (rhs < lhs);
}


GRID_COMPARISON_OPERATOR(>=) {
	return !(lhs < rhs);
}


#include ".containers/grid.tpp"


#undef GRID_COMPARISON_OPERATOR

#endif //GRID_HPP
