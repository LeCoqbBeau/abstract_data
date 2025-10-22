//
// Created by mscheman on 10/17/25.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

namespace ft {

TEMPLATE_T void swap(T REF x, T REF y) {
	T tmp(x);
	x = y;
	y = tmp;
}

template<class InputIt, class T>
InputIt find(InputIt first, InputIt last, T CREF value) {
	for (; first != last; ++first)
		if (*first == value)
			return first;
	return last;
}

template<class InputIt, class UnaryPred>
InputIt find_if(InputIt first, InputIt last, UnaryPred pred) {
	for (; first != last; ++first)
		if (pred(*first))
			return first;
	return last;
}

template< class ForwardIt, class T >
ForwardIt remove(ForwardIt first, ForwardIt last, T CREF value) {
	first = find(first, last, value);
	for (ForwardIt it = first; ++it != last;)
		if (!(*it == value))
			*first++ = *it;
	return first;
}

template< class ForwardIt, class UnaryPred >
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPred pred) {
	first = find_if(first, last, pred);
	for (ForwardIt it = first; ++it != last;)
		if (!pred(*it))
			*first++ = *it;
	return first;
}

template< class ForwardIt >
ForwardIt unique(ForwardIt first, ForwardIt last) {
	if (first == last)
		return last;

	ForwardIt result = first;
	while (++first != last)
		if (!(*result == *first) && ++result != first)
			*result = *first;

	return ++result;
}

template< class ForwardIt, class BinaryPred >
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPred pred) {
	if (first == last)
		return last;

	ForwardIt result = first;
	while (++first != last)
		if (!pred(*result, *first) && ++result != first)
			*result = *first;

	return ++result;
}

}

#endif //ALGORITHM_H
