//
// Created by mscheman on 10/20/25.
//

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

namespace ft {

template <class Arg, class Result>
struct unary_function {
	typedef Arg argument_type;
	typedef Result result_type;
};


template <class Arg1, class Arg2, class Result>
struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};


template <typename T>
struct plus : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x + y; }
};


template <typename T>
struct minus : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x - y; }
};


template <typename T>
struct multiplies : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x * y; }
};


template <typename T>
struct divides : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x * y; }
};


template <typename T>
struct modulus : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x % y; }
};


template <typename T>
struct negate : unary_function<T, T> {
	T operator () (T CREF x) const { return -x; }
};


template <typename T>
struct equal_to : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x == y; }
};


template <typename T>
struct not_equal_to : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x != y; }
};


template <typename T>
struct greater : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x > y; }
};


template <typename T>
struct less : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x < y; }
};


template <typename T>
struct greater_equal : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x >= y; }
};


template <typename T>
struct less_equal : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x <= y; }
};


}


#endif //FUNCTIONAL_H
