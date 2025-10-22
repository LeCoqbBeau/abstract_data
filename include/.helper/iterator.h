//
// Created by mscheman on 10/14/25.
//

#ifndef ITERATOR_H
#define ITERATOR_H

#include "ftdef.h"

namespace ft {

// helper/iterator.h
typedef std::input_iterator_tag input_iterator_tag;
typedef std::output_iterator_tag output_iterator_tag;
typedef std::forward_iterator_tag forward_iterator_tag;
typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
typedef std::random_access_iterator_tag random_access_iterator_tag;

// Iterator
template<
	class Category,
	class T,
	class Distance = ptrdiff_t,
	class Pointer = T*,
	class Reference = T&
> struct iterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

// Reverse Iterator
template < class Iter >
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

}

// Relational Operator Overload
# define REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(op)	template< class Iter1, class Iter2 >											\
													bool operator op (	ft::reverse_iterator<Iter1> CREF lhs,		\
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

// Non-member Operator overloads
template< class Iter >
ft::reverse_iterator<Iter> operator + ( typename ft::reverse_iterator<Iter>::difference_type n,
										ft::reverse_iterator<Iter> CREF it )
{
	return ft::reverse_iterator<Iter>(it.base() - n);
}
template< class Iter >
typename ft::reverse_iterator<Iter>::difference_type operator - ( ft::reverse_iterator<Iter> CREF lhs,
																  ft::reverse_iterator<Iter> CREF rhs )
{
	return rhs.base() - lhs.base();
}

# undef REVERSE_ITERATOR_RELATIONAL_PROTOTYPE

#endif //ITERATOR_H
