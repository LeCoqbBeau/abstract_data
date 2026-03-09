//
// Created by mscheman on 1/24/26.
//

#ifndef GRID_HPP
#define GRID_HPP

#include ".helper/algorithm.hpp"
#include ".helper/ftdef.hpp"
#include ".helper/iterator.hpp"
#include ".helper/ftexcept.hpp"


#define GRID_AT_N_EXCEPTION_MSG ("matrix::at(): column n out of bounds")
#define GRID_AT_M_EXCEPTION_MSG ("matrix::at(): row m out of bounds")


namespace ft {
namespace internal {


template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>
struct gridIterator
	: ft::iterator<ft::random_access_iterator_tag, T, ft::ptrdiff_t, Ptr, Ref>
{
	// Typedefs
	typedef gridIterator<T, Ref, Ptr, M, N>	this_type;
	typedef T								value_type;
	typedef Ref								reference;
	typedef Ptr								pointer;
	typedef ft::ptrdiff_t					difference_type;
	typedef ft::size_t						size_type;

	// Constructor
	explicit	gridIterator(pointer data, size_type pos);
				gridIterator(gridIterator<T, T REF, T*, M, N> CREF iterator);
	~gridIterator() {}

	// In/Equality Operator
	bool			operator	==	(this_type CREF rhs) const;
	bool			operator	!=	(this_type CREF rhs) const;

	// Dereference Operator
	reference		operator	*	();
	pointer			operator	->	();
	reference		operator	[]	(difference_type n);

	// Shift Operators
	this_type REF	operator	++	();
	this_type		operator	++	(int);
	this_type REF	operator	+=	(difference_type n);
	this_type		operator	+	(difference_type n);
	this_type REF	operator	--	();
	this_type		operator	--	(int);
	this_type REF	operator	-=	(difference_type n);
	this_type		operator	-	(difference_type n);
	difference_type	operator	-	(this_type CREF rhs);

	// Attributes
	pointer		_data;
	size_type	_pos;
};

#define GRIDIT_COMPARISON(op)																											\
	template <typename T, typename Ref, typename Ptr, unsigned int M, unsigned int N>													\
	bool operator op (ft::internal::gridIterator<T, T REF, T*, M, N> CREF lhs, ft::internal::gridIterator<T, T REF, T*, M, N> CREF rhs)	\
	{ return lhs._pos op rhs._pos; }

GRIDIT_COMPARISON(<);
GRIDIT_COMPARISON(<=);
GRIDIT_COMPARISON(>);
GRIDIT_COMPARISON(>=);

#undef GRIDIT_COMPARISON


}


template <typename T, unsigned int M, unsigned int N>
class grid
{
	public:
		// Typedefs
		typedef T													value_type;
		typedef T													row_type[N];
		typedef T													grid_type[M][N];
		typedef	size_t												size_type;
		typedef ptrdiff_t											difference_type;
		typedef value_type REF										reference;
		typedef value_type CREF										const_reference;
		typedef T*													pointer;
		typedef T const*											const_pointer;
		typedef internal::gridIterator<T, T REF, T*, M, N>			iterator;
		typedef internal::gridIterator<T, T CREF, T const*, M, N>	const_iterator;
		typedef reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		// Constructors

		/**
		 * @brief The default constructor.
		 * * Constructs a grid with M rows and N columns.
		 * @throw Nothing unless T default constructor does.
		 * @details Complexity: M * N calls to T default constructor.
		 */
		grid();

		/**
		 * @brief The fill constructor.
		 * * Constructs a grid with copies of elements with value `value`.
		 * @throw Nothing unless T copy assignment operator does.
		 * @details Complexity: M * N calls to T's copy assignment operator.
		 */
		grid(const_reference value);

		/**
		 * @brief The range constructor.
		 * * Constructs a grid with the contents of the range [first, last).
		 * * Iterators in [first, last) is at most dereferenced exactly once.
		 * @warning If the distance between first and last is bigger than M * N,
		 then the constructor stop after initializing M * N elements.
		 * @warning If the distance between first and last is less than M * N,
		 then the constructor initializes the rest of the element with their default value.
		 * @tparam InputIt A class that satisfies the requirements of LegacyInputIterator.
		 * @param first, last the pair of iterators defining the source range of elements to copy
		 * @throw Nothing unless T copy assignment operator does.
		 * @details Complexity: ft::distance(first, last) calls to T's copy assignment operator,
		 and M*N - ft::distance(first, last) calls to T's default constructor.
		 */
		template <typename InputIt> grid(InputIt first, InputIt last);

		/**
		 * @brief The copy constructor.
		 * * Constructs a grid with the contents of other.
		 * @param other another grid to be used as source to initialize the elements of the grid with
		 * @throw Nothing unless T copy assignment operator does.
		 * @details Complexity: M * N calls to T's copy assignment operator.
		 */
		grid(grid CREF other);

		/**
		 * @brief Replaces the contents of the container.
		 * * Constructs a grid with the contents of other.
		 * @param other another container to use as data source
		 * @throw Nothing unless T copy assignment operator does.
		 * @details Complexity: M * N calls to T's copy assignment operator.
		 * @remark While this function does modify the container, it doesn't cause any reference/iterator invalidation.
		 */
		grid REF operator = (grid CREF other);

		/**
		 * @brief Destructs the grid. The destructors of the elements are called.
		 * @throw Nothing this function never throws.
		 * @details Complexity: M * N calls to T's destructor.
		 * @note If the elements are pointers, the pointed-to objects are not destroyed.
		 */
		~grid();

		// Iterators
		/**
		 * @brief Returns an iterator to the first element of *this.
		 * * If *this is empty, the returned iterator will be equal to end().
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Iterator to the first element.
		 */
		iterator					begin();

		/**
		 * @brief Returns an iterator to the first element of *this.
		 * * If *this is empty, the returned iterator will be equal to end().
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Iterator to the first element.
		 */
		const_iterator				begin() const;

		/**
		 * @brief Returns an iterator past the last element of *this.
		 * * This returned iterator only acts as a sentinel. It is not guaranteed to be dereferenceable.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Iterator past the last element.
		 */
		iterator					end();

		/**
		 * @brief Returns an iterator past the last element of *this.
		 * * This returned iterator only acts as a sentinel. It is not guaranteed to be dereferenceable.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Iterator past the last element.
		 */
		const_iterator				end() const;

		/**
		 * @brief Returns a reverse iterator to the first element of the reversed *this.
		 * * It corresponds to the last element of the non-reversed *this.
		 * * If *this is empty, the returned iterator is equal to rend().
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reverse iterator to the first element.
		 */
		reverse_iterator			rbegin();

		/**
		 * @brief Returns a reverse iterator to the first element of the reversed *this.
		 * * It corresponds to the last element of the non-reversed *this.
		 * * If *this is empty, the returned iterator is equal to rend().
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reverse iterator to the first element.
		 */
		const_reverse_iterator		rbegin() const;

		/**
		 * @brief Returns a reverse iterator past the last element of the reversed *this.
		 * * It corresponds to the element preceding the first element of the non-reversed *this.
		 * * This returned iterator only acts as a sentinel. It is not guaranteed to be dereferenceable.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reverse iterator to the element following the last element.
		 */
		reverse_iterator			rend();

		/**
		 * @brief Returns a reverse iterator past the last element of the reversed *this.
		 * * It corresponds to the element preceding the first element of the non-reversed *this.
		 * * This returned iterator only acts as a sentinel. It is not guaranteed to be dereferenceable.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reverse iterator to the element following the last element.
		 */
		const_reverse_iterator		rend() const;

		// Capacity

		/**
		 * @brief Returns the number of rows in the grid.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Compile-time.
		 * @return The template parameter M.
		 */
		static unsigned int			rows()		{ return M; };

		/**
		 * @brief Returns the number of column in the grid.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Compile-time.
		 * @return The template parameter N.
		 */
		static unsigned int			cols()		{ return N; };

		/**
		 * @brief Returns the number of elements in the container.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Compile-time.
		 * @return M * N
		 */
		static unsigned int			size()		{ return M * N; };

		/**
		 * @brief Checks if the container has no elements.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Compile-time.
		 * @return true if the container is empty, false otherwise.
		 * @note The container is considered empty if it has 0 columns or rows.
		 */
		static unsigned int			max_size()	{ return M * N; };

		/**
		 * @brief Checks if the container has no elements.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Compile-time.
		 * @return true if the container is empty, false otherwise.
		 * @note The container is considered empty if it has 0 columns or rows.
		 */
		static bool					empty()		{ return !M || !N; }

		// Element Access

		/**
		 * @brief Returns the m-th row of the grid as an array of elements.
		 * * This allows the use of the double subscript operator syntax.
		 * @warning If m < M, the behavior is undefined.
		 * @param m index of the row to return
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Pointer of the requested row
		 */
		pointer			operator	[](size_type m);

		/**
		 * @brief Returns the m-th row of the grid as an array of elements.
		 * * This allows the use of the double subscript operator syntax.
		 * @warning If m < M, the behavior is undefined.
		 * @param m index of the row to return
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Pointer of the requested row.
		 */
		const_pointer	operator	[](size_type m) const;

		/**
		 * @brief Returns a reference to the element at the m-th row and the n-th column, with bounds checking.
		 * * If m or n is not within the range of the container, an exception of type ft::out_of_range is thrown.
		 * @param m index of the row of the element
		 * @param n index of the column of the element
		 * @throw ft::out_of_range if m >= M or n >= N
		 * @details Complexity: Constant.
		 * @return Reference of the requested element.
		 */
		reference					at(size_type m, size_type n);

		/**
		 * @brief Returns a reference to the element at the m-th row and the n-th column, with bounds checking.
		 * * If m or n is not within the range of the container, an exception of type ft::out_of_range is thrown.
		 * @param m index of the row of the element
		 * @param n index of the column of the element
		 * @throw ft::out_of_range if m >= M or n >= N
		 * @details Complexity: Constant.
		 * @return Reference of the requested element.
		 */
		const_reference				at(size_type m, size_type n) const;

		/**
		 * @brief Returns a reference to the first element in the container.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the first element.
		 */
		reference					front();

		/**
		 * @brief Returns a reference to the first element in the container.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the first element.
		 */
		const_reference				front() const;

		/**
		 * @brief Returns a reference to the first element of the m-th row.
		 * @warning If m < M, the behavior is undefined.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the first element of the m-th row.
		 */
		reference					front(size_type m);

		/**
		 * @brief Returns a reference to the first element of the m-th row.
		 * @warning If m < M, the behavior is undefined.
		 * @param m index of the row
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the first element of the m-th row.
		 */
		const_reference				front(size_type m) const;

		/**
		 * @brief Returns a reference to the last element in the container.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the last element.
		 */
		reference					back();

		/**
		 * @brief Returns a reference to the last element in the container.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the last element.
		 */
		const_reference				back() const;

		/**
		 * @brief Returns a reference to the last element of the m-th row
		 * @warning If m < M, the behavior is undefined.
		 * @param m index of the row
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the last element of the m-th row.
		 */
		reference					back(size_type m);

		/**
		 * @brief Returns a reference to the last element of the m-th row
		 * @warning If m < M, the behavior is undefined.
		 * @param m index of the row
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the last element of the m-th row.
		 */
		const_reference				back(size_type m) const;

		/**
		 * @brief Returns a pointer to the flatten grid serving as element storage.
		 * * The pointer is such that range [data(), data() + size()) is always a valid range.
		 * * If *this is empty, data() is not dereferenceable.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the last element of the m-th row.
		 * @note Note that the underlying data storage is in fact a grid,
		 * * however since converting from an array to a pointer is impossible,
		 * * returning a pointer is the most convenient solution.
		 */
		pointer						data();

		/**
		 * @brief Returns a pointer to the flatten grid serving as element storage.
		 * * The pointer is such that range [data(), data() + size()) is always a valid range.
		 * * If *this is empty, data() is not dereferenceable.
		 * @throw Nothing this function never throws.
		 * @details Complexity: Constant.
		 * @return Reference to the last element of the m-th row.
		 * @note Note that the underlying data storage is in fact a grid,
		 * * however since converting from an array to a pointer is impossible,
		 * * returning a pointer is the most convenient solution.
		 */
		const_pointer				data() const;

		// Modifiers

		/**
		 * @brief Assigns the value to all elements in the container.
		 * @param value the value to assign to the elements
		 * @throw Nothing unless T copy assignment operator does.
		 * @details Complexity: Linear in the size of the container.
		 * @remark While this function does modify the container, it doesn't cause any reference/iterator invalidation.
		 */
		void						fill(const_reference value);

		/**
		 * @brief Exchanges the contents of the container with those of rhs.
		 * * Does not cause iterators and references to associate with the other container.
		 * @param rhs container to exchange the contents with
		 * @throw Nothing unless T copy assignment operator does.
		 * @details Complexity: Linear in the size of the container.
		 * @remark While this function does modify the container, it doesn't cause any reference/iterator invalidation.
		 */
		void						swap(grid REF rhs);


	protected:
		// Attributes
		grid_type					_grid;
};

#define GRID_COMPARISON(op) template <typename T, unsigned int M, unsigned int N> bool operator op (ft::grid<T, M, N> CREF lhs, ft::grid<T, M, N> CREF rhs)

GRID_COMPARISON(==) { return ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
GRID_COMPARISON(!=) { return !(lhs == rhs); }
GRID_COMPARISON(<)	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
GRID_COMPARISON(<=)	{ return !(rhs < lhs); }
GRID_COMPARISON(>)	{ return rhs < lhs; }
GRID_COMPARISON(>=)	{ return !(lhs < rhs); }

#undef GRID_COMPARISON


template <typename T, unsigned int M, unsigned int N>
void swap(ft::grid<T, M, N> CREF lhs, ft::grid<T, M, N> CREF rhs)
{
	lhs.swap(rhs);
}


}


#include ".containers/grid.tpp"


#undef GRID_AT_N_EXCEPTION_MSG
#undef GRID_AT_M_EXCEPTION_MSG


#endif //GRID_HPP
