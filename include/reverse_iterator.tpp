//
// Created by mscheman on 10/14/25.
//

#ifndef REVERSE_ITERATOR_TPP
#define REVERSE_ITERATOR_TPP

// Constructors
template <class Iter>
ft::reverse_iterator<Iter>::reverse_iterator()
	: _current() {}

template <class Iter>
ft::reverse_iterator<Iter>::reverse_iterator(iterator_type it)
	: _current(it) {}

template <class Iter>
ft::reverse_iterator<Iter>::reverse_iterator(reverse_iterator CREF rev_it)
	: _current(rev_it._current) {}

template <class Iter>
typename ft::reverse_iterator<Iter>::iterator_type ft::reverse_iterator<Iter>::base() const {
	return _current;
}

// Access Operators Overload
template <class Iter>
typename ft::reverse_iterator<Iter>::reference ft::reverse_iterator<Iter>::operator * () {
	Iter tmp = _current;
	return *(--tmp);
}

template <class Iter>
typename ft::reverse_iterator<Iter>::pointer ft::reverse_iterator<Iter>::operator -> () {
	return &(operator*());
}

template <class Iter>
typename ft::reverse_iterator<Iter>::reference ft::reverse_iterator<Iter>::operator [] (difference_type n) const {
	return base()[-n - 1];
}

// Shift Operators Overload
template<class Iter>
ft::reverse_iterator<Iter> REF ft::reverse_iterator<Iter>::operator ++ () {
	--_current;
	return *this;
}

template<class Iter>
ft::reverse_iterator<Iter> REF ft::reverse_iterator<Iter>::operator -- () {
	++_current;
	return *this;
}

template<class Iter>
ft::reverse_iterator<Iter> ft::reverse_iterator<Iter>::operator ++ ( int ) {
	reverse_iterator tmp = *this;
	--_current;
	return tmp;
}

template<class Iter>
ft::reverse_iterator<Iter> ft::reverse_iterator<Iter>::operator -- ( int ) {
	reverse_iterator tmp = *this;
	++_current;
	return tmp;
}

template<class Iter>
ft::reverse_iterator<Iter> ft::reverse_iterator<Iter>::operator + ( difference_type n ) const {
	return reverse_iterator(_current - n);
}

template<class Iter>
ft::reverse_iterator<Iter> ft::reverse_iterator<Iter>::operator - ( difference_type n ) const {
	return reverse_iterator(_current + n);
}

template<class Iter>
ft::reverse_iterator<Iter> REF ft::reverse_iterator<Iter>::operator += ( difference_type n ) {
	_current -= n;
	return *this;
}

template<class Iter>
ft::reverse_iterator<Iter> REF ft::reverse_iterator<Iter>::operator -= ( difference_type n ) {
	_current += n;
	return *this;
}

// Relational Operator Overloads
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
										ft::reverse_iterator<Iter> CREF it ) {
	return ft::reverse_iterator<Iter>(it.base() - n);
}

template< class Iter >
typename ft::reverse_iterator<Iter>::difference_type operator - ( ft::reverse_iterator<Iter> CREF lhs,
																  ft::reverse_iterator<Iter> CREF rhs ) {
	return rhs.base() - lhs.base();
}

#endif //REVERSE_ITERATOR_TPP
