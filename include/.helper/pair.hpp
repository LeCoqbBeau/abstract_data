//
// Created by mscheman on 11/20/25.
//

#ifndef PAIR_H
#define PAIR_H

#include "ftdef.hpp"

namespace ft {

template <class T1, class T2>
struct pair {
	// Typedefs
	typedef T1	first_type;
	typedef T2	second_type;

	// Members
	T1			mFirst;
	T2			mSecond;

	// Constructors
	pair();
	pair(first_type CREF x, second_type CREF y);
	pair(pair CREF p);
	template <class U1, class U2> pair(pair<U1, U2> CREF p);
	pair REF operator = (pair CREF rhs);
	template <class U1, class U2> pair REF operator = (pair<U1, U2> CREF rhs);

	// Methods
	first_type REF first() FT_NOTHROW { return mFirst; };
	first_type CREF first() const FT_NOTHROW { return mFirst; };
	second_type REF second() FT_NOTHROW { return mSecond; };
	second_type CREF second() const FT_NOTHROW { return mSecond; };

};


template <class T1, class T2>
ft::pair<T1, T2> make_pair(T1 x, T2 y);

}


// Member functions
template <class T1, class T2>
ft::pair<T1, T2>::pair()
	: mFirst(), mSecond() {}


template <class T1, class T2>
ft::pair<T1, T2>::pair(
	first_type CREF x,
	second_type CREF y
)	: mFirst(x), mSecond(y) {}


template <class T1, class T2>
ft::pair<T1, T2>::pair(pair CREF p) {
	*this = p;
}


template <class T1, class T2>
template <class U1, class U2>
ft::pair<T1, T2>::pair(pair<U1, U2> CREF p) {
	*this = p;
}


template <class T1, class T2>
ft::pair<T1, T2> REF ft::pair<T1, T2>::operator = (pair CREF rhs) {
	if (this != &rhs) {
		mFirst = rhs.mFirst;
		mSecond = rhs.mSecond;
	}
	return *this;
}


template <class T1, class T2>
template <class U1, class U2>
ft::pair<T1, T2> REF ft::pair<T1, T2>::operator = (pair<U1, U2> CREF rhs) {
	if (this != &rhs) {
		mFirst = rhs.mFirst;
		mSecond = rhs.mSecond;
	}
	return *this;
}

// Non-member functions
template <class T1, class T2>
ft::pair<T1, T2> ft::make_pair(T1 x, T2 y) {
	return pair<T1, T2>(x, y);
}

# define PAIR_RELATIONAL_PROTOTYPE(op)	template <class T1, class T2, class U1, class U2>						\
										bool operator op (ft::pair<T1, T2> CREF lhs, ft::pair<U1, U2> CREF rhs)

PAIR_RELATIONAL_PROTOTYPE(==) {
	return lhs.first() == rhs.first() && lhs.second() == rhs.second();
}


PAIR_RELATIONAL_PROTOTYPE(!=) {
	return !(lhs == rhs);
}


PAIR_RELATIONAL_PROTOTYPE(<) {
	if (lhs.first() < rhs.first())
		return true;
	if (rhs.first() < lhs.first())
		return false;
	if (lhs.second() < rhs.second())
		return true;
	return false;
}


PAIR_RELATIONAL_PROTOTYPE(<=) {
	return !(rhs < lhs);
}


PAIR_RELATIONAL_PROTOTYPE(>) {
	return (rhs < lhs);
}


PAIR_RELATIONAL_PROTOTYPE(>=) {
	return !(lhs < rhs);
}


#undef  PAIR_RELATIONAL_PROTOTYPE

#endif //PAIR_H
