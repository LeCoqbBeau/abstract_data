//
// Created by mscheman on 10/14/25.
//

#ifndef ITERATOR_H
#define ITERATOR_H

#include "ft_namespace.h"

// Iterator
template<
	class Category,
	class T,
	class Distance,
	class Pointer,
	class Reference
> struct ft::iterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

// Reverse Iterator
template < class Iter >
class ft::reverse_iterator {
	public:
		// Typedefs
		typedef Iter								iterator_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;

		// Constructors
		reverse_iterator();
		explicit reverse_iterator(iterator_type it);
		reverse_iterator(reverse_iterator CREF rev_it);

		// Method
		iterator_type base() const;

		// Access Operators Overload
		reference operator * ();
		pointer operator -> ();
		reference operator[] (difference_type n) const;

		// Shift Operators Overload
		reverse_iterator REF operator ++();
		reverse_iterator REF operator --();
		reverse_iterator operator ++( int );
		reverse_iterator operator --( int );
		reverse_iterator operator +( difference_type n ) const;
		reverse_iterator operator -( difference_type n ) const;
		reverse_iterator REF operator +=( difference_type n );
		reverse_iterator REF operator -=( difference_type n );

	private:
		Iter _current;
};

// Relational Operator Overload
# define REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(op)	template< class Iter >											\
													bool operator op (	ft::reverse_iterator<Iter> CREF lhs,		\
																		ft::reverse_iterator<Iter> CREF rhs )

REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(==);
REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(!=);
REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(<);
REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(<=);
REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(>);
REVERSE_ITERATOR_RELATIONAL_PROTOTYPE(>=);

// Non-member Operator overloads
template< class Iter >
ft::reverse_iterator<Iter> operator + ( typename ft::reverse_iterator<Iter>::difference_type n,
										ft::reverse_iterator<Iter> CREF it );
template< class Iter >
typename ft::reverse_iterator<Iter>::difference_type operator - ( ft::reverse_iterator<Iter> CREF lhs,
																  ft::reverse_iterator<Iter> CREF rhs );

#include "helper/reverse_iterator.tpp"

# undef REVERSE_ITERATOR_RELATIONAL_PROTOTYPE

#endif //ITERATOR_H
