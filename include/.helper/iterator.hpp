//
// Created by mscheman on 10/14/25.
//

#ifndef ITERATOR_H
#define ITERATOR_H

#include "ftdef.hpp"
#include "type_traits.hpp"

namespace ft {

// Iterator tags
typedef std::input_iterator_tag input_iterator_tag;
typedef std::output_iterator_tag output_iterator_tag;
typedef std::forward_iterator_tag forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

// Iterator Traits
namespace internal {

template <typename Iterator, class = void>
struct default_iterator_traits {};


template <typename Iterator>
struct default_iterator_traits<
	Iterator,
	MAKE_VOID_T5(
		typename Iterator::iterator_category,
		typename Iterator::value_type,
		typename Iterator::difference_type,
		typename Iterator::pointer,
		typename Iterator::reference
	)
> {
	typedef typename Iterator::iterator_category	iterator_category;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
};


}


template <typename Iterator>
struct iterator_traits : internal::default_iterator_traits<Iterator> {};


template <typename T>
struct iterator_traits<T*>
{
	typedef ft::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T REF							reference;
};


template <typename T>
struct iterator_traits<T const*>
{
	typedef ft::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T const*						pointer;
	typedef T CREF							reference;
};


// Iterator
template<
	class Category,
	class T,
	class Distance = ft::ptrdiff_t,
	class Pointer = T*,
	class Reference = T REF
> struct iterator {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

// Reverse Iterator
template <class Iter>
class reverse_iterator {
	public:
		// Typedefs
		typedef Iter								iterator_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;

		// Constructors
		reverse_iterator() : _current() {}
		explicit reverse_iterator(iterator_type it) : _current(it) {}
		reverse_iterator(reverse_iterator CREF rev_it) : _current() { *this = rev_it; }
		template <class U>
		reverse_iterator(reverse_iterator<U> CREF rhs) : _current(rhs.base()) {}
		template<class U>
		reverse_iterator REF operator = (reverse_iterator<U> CREF rhs) { _current = rhs.base(); return *this; }

		// Method
		iterator_type base() const { return _current; };

		// Access Operators Overload
		reference operator * () { Iter tmp = _current; return *(--tmp); }
		pointer operator -> () { return &(operator*()); }
		reference operator[] (difference_type n) const { return base()[-n - 1]; }

		// Shift Operators Overload
		reverse_iterator REF operator ++ () { --_current; return *this; }
		reverse_iterator REF operator -- () { ++_current; return *this; }
		reverse_iterator operator ++ ( int ) { reverse_iterator tmp = *this; --_current; return tmp;}
		reverse_iterator operator -- ( int ) { reverse_iterator tmp = *this; ++_current; return tmp;}
		reverse_iterator operator + ( difference_type n ) const { return reverse_iterator(_current - n); }
		reverse_iterator operator - ( difference_type n ) const { return reverse_iterator(_current + n); }
		reverse_iterator REF operator += ( difference_type n ) { _current -= n; return *this; }
		reverse_iterator REF operator -= ( difference_type n ) { _current += n; return *this; }

	private:
		Iter _current;
};


// Relational Operator Overload
# define REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(op)	template< class Iter1, class Iter2 >						\
													bool operator op (	ft::reverse_iterator<Iter1> CREF lhs,	\
													ft::reverse_iterator<Iter2> CREF rhs )


REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(==) {
	return lhs.base() == rhs.base();
}


REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(!=) {
	return lhs.base() != rhs.base();
}


REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(<)  {
	return lhs.base() > rhs.base();
}


REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(<=) {
	return lhs.base() >= rhs.base();
}


REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(>)  {
	return lhs.base() < rhs.base();
}


REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(>=) {
	return lhs.base() <= rhs.base();
}


# undef REVERSE_ITERATOR_RELATIONAL_PROTOTYPE


// Non-member Operator overloads
template< class Iter >
ft::reverse_iterator<Iter>
operator + (
	typename ft::reverse_iterator<Iter>::difference_type n,
	ft::reverse_iterator<Iter> CREF it
) {
	return ft::reverse_iterator<Iter>(it.base() - n);
}


template< class Iter >
typename ft::reverse_iterator<Iter>::difference_type
operator - (
	ft::reverse_iterator<Iter> CREF lhs,
	ft::reverse_iterator<Iter> CREF rhs
) {
	return rhs.base() - lhs.base();
}


// Functions
namespace internal {


template <typename InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
distance_impl(InputIterator first, InputIterator last, ft::input_iterator_tag)
{
	typename ft::iterator_traits<InputIterator>::difference_type n = 0;

	while(first != last)
	{
		++first;
		++n;
	}
	return n;
}


template <typename RandomAccessIterator>
typename ft::iterator_traits<RandomAccessIterator>::difference_type
distance_impl(RandomAccessIterator first, RandomAccessIterator last, ft::random_access_iterator_tag)
{
	return last - first;
}


template <typename InputIterator, typename Distance>
void advance_impl(InputIterator REF i, Distance n, ft::input_iterator_tag)
{
	while(n--)
		++i;
}


template <bool signedDistance>
struct advance_bi_impl
{
	template <typename BidirectionalIterator, typename Distance>
	static void advance_impl(BidirectionalIterator REF i, Distance n) // Specialization for unsigned distance type.
	{
		while(n--)
			++i;
	}
};


template <>
struct advance_bi_impl<true>
{
	template <typename BidirectionalIterator, typename Distance>
	static void advance_impl(BidirectionalIterator REF i, Distance n) // Specialization for signed distance type.
	{
		if(n > 0)
		{
			while(n--)
				++i;
		}
		else
		{
			while(n++)
				--i;
		}
	}
};


template <typename BidirectionalIterator, typename Distance>
void advance_impl(BidirectionalIterator REF i, Distance n, ft::bidirectional_iterator_tag)
{
	advance_bi_impl<ft::is_signed<Distance>::value>::advance_impl(i, n);
}


template <typename RandomAccessIterator, typename Distance>
void advance_impl(RandomAccessIterator REF i, Distance n, ft::random_access_iterator_tag)
{
	i += n;
}


} // namespace impl


template <typename InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
	typedef typename ft::iterator_traits<InputIterator>::iterator_category IC;

	return ft::internal::distance_impl(first, last, IC());
}


template <typename InputIterator, typename Distance>
void advance(InputIterator REF i, Distance n)
{
	typedef typename ft::iterator_traits<InputIterator>::iterator_category IC;

	ft::internal::advance_impl(i, n, IC());
}


template<class InputIt>
InputIt next(InputIt it, typename ft::iterator_traits<InputIt>::difference_type n = 1)
{
	ft::advance(it, n);
	return it;
}


}

#endif //ITERATOR_H
