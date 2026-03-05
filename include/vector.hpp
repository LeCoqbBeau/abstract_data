//
// Created by mscheman on 1/19/26.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include ".helper/algorithm.hpp"
#include ".helper/ftdef.hpp"
#include ".helper/iterator.hpp"
#include ".helper/dispatch.hpp"

#define VECTOR_ARRAY_INIT_SIZE 16
#define VECTOR_AT_EXCEPTION_MSG ("vector::at(): index n out of bounds")


namespace ft {

template <typename T, typename Ref, typename Ptr>
struct _vectorIterator : iterator<ft::random_access_iterator_tag, T, ft::ptrdiff_t, Ptr, Ref>
{
	// Typedefs
	typedef _vectorIterator<T, Ref, Ptr>	this_type;
	typedef T								value_type;
	typedef ft::ptrdiff_t					difference_type;
	typedef Ptr								pointer;
	typedef Ref								reference;

	// Constructors
	_vectorIterator(value_type *current = NULL) : _curr(current) {}
	_vectorIterator(_vectorIterator<T, T REF, T*> CREF iterator) : _curr(iterator._curr) {}
	~_vectorIterator() {}

	// In/Equality Operator
	template <class U, class URef, class UPtr>
	bool		operator	== (_vectorIterator<U, URef, UPtr> CREF rhs) const { return _curr == rhs._curr; }
	template <class U, class URef, class UPtr>
	bool		operator	!= (_vectorIterator<U, URef, UPtr> CREF rhs) const { return _curr != rhs._curr; }

	// Dereference Operator
	reference		operator	* ()							{ return *_curr; }
	pointer			operator	->()							{ return _curr; }
	reference		operator	[](difference_type n)			{ return _curr[n]; }

	// Shift Operators
	this_type REF	operator	++ ()							{ ++_curr; return *this; }
	this_type		operator	++ (int)						{ this_type tmp(*this); operator++(); return tmp; }
	this_type REF	operator	+= (difference_type n)			{ _curr += n; return *this; }
	this_type		operator	+  (difference_type n) const	{ return this_type(*this).operator+=(n); }
	this_type REF	operator	-- ()							{ --_curr; return *this; }
	this_type		operator	-- (int)						{ this_type tmp(*this); operator--(); return tmp; }
	this_type REF	operator	-= (difference_type n)			{ _curr -= n; return *this; }
	this_type		operator	-  (difference_type n) const	{ return this_type(*this).operator-=(n); }
	template <class U, class URef, class UPtr>
	difference_type	operator	- (_vectorIterator<U, URef, UPtr> CREF rhs) const { return _curr - rhs._curr; }


	// Attributes
	value_type	*_curr;
};


// Vector template out of class operator overloads
template <typename T, typename Ref, typename Ptr>
typename ft::_vectorIterator<T, Ref, Ptr>::this_type
operator + (typename ft::_vectorIterator<T, Ref, Ptr>::difference_type n, ft::_vectorIterator<T, Ref, Ptr> it)
{
	return it + n;
}

// Comparison Operators
#define TWO_VECTORIT_TEMPLATE			template <typename U, typename RefA, typename PtrA, typename RefB, typename PtrB>
#define TWO_VECTORIT_PARAMETERS		ft::_vectorIterator<U, RefA, PtrA> CREF lhs, ft::_vectorIterator<U, RefB, PtrB> CREF rhs
#define TWO_VECTORIT_COMPARISON(op)	TWO_VECTORIT_TEMPLATE inline bool operator op (TWO_VECTORIT_PARAMETERS)

TWO_VECTORIT_COMPARISON(<) 	{ return (lhs._curr < rhs._curr); }
TWO_VECTORIT_COMPARISON(<=)	{ return !(rhs < lhs); }
TWO_VECTORIT_COMPARISON(>)	{ return (rhs < lhs); }
TWO_VECTORIT_COMPARISON(>=)	{ return !(lhs < rhs); }

#undef TWO_VECTORIT_TEMPLATE
#undef TWO_VECTORIT_PARAMETERS
#undef TWO_VECTORIT_COMPARISON
//



template <typename T, typename Allocator = ft::allocator<T> >
class vector {
	public:
		// Typedefs
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef	ft::size_t								size_type;
		typedef ft::ptrdiff_t							difference_type;
		typedef value_type REF							reference;
		typedef value_type CREF							const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef _vectorIterator<T, T REF, T*>			iterator;
		typedef _vectorIterator<T, T CREF, T const*>	const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// Constructors
		explicit 								vector(allocator_type CREF alloc = allocator_type());
		explicit 								vector(size_type n, value_type CREF val = value_type(), allocator_type CREF alloc = allocator_type());
		template <class Iterator>				vector(Iterator first, Iterator last, allocator_type CREF alloc = allocator_type());
												vector(vector CREF rhs);
		vector REF					operator	= (vector CREF rhs);
		~vector();

		// Iterators
		iterator								begin();
		const_iterator							begin() const;
		iterator								end();
		const_iterator							end() const;
		reverse_iterator						rbegin();
		const_reverse_iterator					rbegin() const;
		reverse_iterator						rend();
		const_reverse_iterator					rend() const;

		// Capacity
		size_type								size() const;
		size_type								max_size() const;
		void									resize(size_type n, value_type CREF val = value_type());
		size_type								capacity() const;
		bool									empty() const;
		void									reserve(size_type n);

		// Element Access
		reference					operator	[] (size_type n);
		const_reference 			operator	[] (size_type n) const;
		reference 								at(size_type n);
		const_reference 						at(size_type n) const;
		reference								front();
		const_reference							front() const;
		reference								back();
		const_reference							back() const;

		// Modifiers
		void									assign(size_type n, value_type CREF value);
		template <typename Iterator> void		assign(Iterator first, Iterator last);
		void									push_back(value_type CREF value);
		void									pop_back();
		iterator								insert(iterator position, value_type CREF val);
		void									insert(iterator position, size_type count, value_type CREF val);
		template <typename Iterator> void		insert(iterator position, Iterator first, Iterator last);
		iterator								erase(iterator position);
		iterator								erase(iterator first, iterator last);
		void									swap(vector REF other);
		void									clear();

		// Allocator
		allocator_type							get_allocator() const;

	protected:
		// Helper Functions
		void									_init(size_type n);
		void									_assignFill(size_type n, value_type CREF val);
		template <typename Integer>		void	_assignHelper(Integer first, Integer last, ft::dispatch_int);
		template <typename InputIt>		void	_assignHelper(InputIt first, InputIt last, ft::dispatch_input);
		template <typename ForwardIt>	void	_assignHelper(ForwardIt first, ForwardIt last, ft::dispatch_forward);
		iterator								_insertFill(iterator position, size_type n, value_type CREF val);
		template <typename Integer>	iterator	_insertHelper(iterator position, Integer first, Integer last, ft::dispatch_int);
		template <typename InputIt>		void	_insertHelper(iterator position, InputIt first, InputIt last, ft::dispatch_input);
		template <typename ForwardIt>	void	_insertHelper(iterator position, ForwardIt first, ForwardIt last, ft::dispatch_forward);
		void									_reallocate(size_type n);

		// Attributes
		value_type*		_array;
		value_type*		_end;
		size_type		_capacity;
		allocator_type	_allocator;
};


template <typename T, typename Allocator>
void swap(ft::vector<T, Allocator> REF x, ft::vector<T, Allocator> REF y)
{
	x.swap(y);
}


# define VECTOR_COMPARISON_OPERATOR(op)	template <class T, class Allocator> bool operator op						\
										(ft::vector<T, Allocator> CREF lhs, ft::vector<T, Allocator> CREF rhs)

VECTOR_COMPARISON_OPERATOR(==)	{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
VECTOR_COMPARISON_OPERATOR(<)	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
VECTOR_COMPARISON_OPERATOR(!=)	{ return !(lhs == rhs); }
VECTOR_COMPARISON_OPERATOR(<=)	{ return !(rhs < lhs); }
VECTOR_COMPARISON_OPERATOR(>)	{ return (rhs < lhs); }
VECTOR_COMPARISON_OPERATOR(>=)	{ return !(lhs < rhs); }

#undef VECTOR_COMPARISON_OPERATOR


}


#include ".containers/vector.tpp"


#undef VECTOR_ARRAY_INIT_SIZE
#undef VECTOR_AT_EXCEPTION_MSG

#endif //VECTOR_HPP
