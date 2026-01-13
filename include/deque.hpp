//
// Created by mscheman on 10/27/25.
//

#ifndef DEQUE_H
#define DEQUE_H

#include ".helper/allocator.hpp"
#include ".helper/ftdef.hpp"
#include ".helper/iterator.hpp"
#include ".helper/type_traits.hpp"

# define DEQUE_ARRAY_SIZE 16

namespace ft {

template <typename T, typename Allocator = ft::allocator<T> >
class deque;


template <typename T, typename TRef, typename TPtr>
struct _dequeIterator
	: public ft::iterator<ft::bidirectional_iterator_tag, T, ft::ptrdiff_t, TRef, TPtr>
{
	public:
		// Typedefs
		typedef _dequeIterator<T, TRef, TPtr>	this_type;
		typedef T								value_type;
		typedef TRef							reference;
		typedef TPtr							pointer;
		typedef ft::ptrdiff_t					difference_type;

		// Constructor
		_dequeIterator();
		_dequeIterator(_dequeIterator<T, T REF, T*> CREF rhs);

		// Dereference Operator
		reference 		operator *  () const { return *_curr; };
		pointer   		operator -> () const { return _curr; };

		// Shift Operators
		this_type REF	operator ++	();
		this_type		operator ++	(int);
		this_type REF	operator --	();
		this_type		operator --	(int);
		this_type REF 	operator +=	(difference_type n);
		this_type REF 	operator -=	(difference_type n);
		this_type		operator +	(difference_type n) const;
		this_type		operator -	(difference_type n) const;

	protected:
		// Friend
		template <typename, typename>
		friend class ft::deque; // We need to do this because _deque_iterator is the class that access the data

		// Constructor
		_dequeIterator(T** array, T* _curr);

		// Attributes
		T*	_curr;
		T*	_begin;
		T*	_end;
		T**	_array;
};


template <typename T, typename Allocator>
class deque {
	public:
		// Typedefs
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef	size_t									size_type;
		typedef ft::ptrdiff_t							difference_type;
		typedef typename Allocator::reference			reference;
		typedef typename Allocator::const_reference		const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef _dequeIterator<T, T REF, T*>			iterator;
		typedef _dequeIterator<T, T CREF, T const*>	const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	protected:
		T**				_array;
		size_type		_arraySize;
		iterator		_begin;
		iterator		_end;
		allocator_type	_allocator;
};


}

#include ".containers/deque.tpp"

#endif //DEQUE_H
