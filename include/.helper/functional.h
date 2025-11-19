//
// Created by mscheman on 10/20/25.
//

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

namespace ft {
namespace func {

template <class Arg, class Result> struct unary_function {
	typedef Arg argument_type;
	typedef Result result_type;
};


template <class Arg1, class Arg2, class Result> struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};


TEMPLATE_T struct plus : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x + y; }
};


TEMPLATE_T struct minus : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x - y; }
};


TEMPLATE_T struct multiplies : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x * y; }
};


TEMPLATE_T struct divides : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x * y; }
};


TEMPLATE_T struct modulus : binary_function<T, T, T> {
	T operator () (T CREF x, T CREF y) const { return x % y; }
};


TEMPLATE_T struct negate : unary_function<T, T> {
	T operator () (T CREF x) const { return -x; }
};


TEMPLATE_T struct equal_to : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x == y; }
};


TEMPLATE_T struct not_equal_to : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x != y; }
};


TEMPLATE_T struct greater : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x > y; }
};


TEMPLATE_T struct less : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x < y; }
};


TEMPLATE_T struct greater_equal : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x >= y; }
};


TEMPLATE_T struct less_equal : binary_function<T, T, bool> {
	bool operator () (T CREF x, T CREF y) { return x <= y; }
};


}
}


#endif //FUNCTIONAL_H
