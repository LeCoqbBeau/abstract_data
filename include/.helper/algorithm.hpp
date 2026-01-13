//
// Created by mscheman on 10/17/25.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "ftdef.hpp"

namespace ft {


template <typename T>
void swap(
	T REF x,
	T REF y
) {
	T tmp(x);
	x = y;
	y = tmp;
}


template <typename T>
T abs(T CREF x) {
	return (x < 0) ? -x : x;
}


template <typename T>
T CREF min(
	T CREF x,
	T CREF y
) {
	return (x < y) ? x : y;
}


template <typename T, typename BinaryPredicate>
T CREF min(
	T CREF x,
	T CREF y,
	BinaryPredicate comp
) {
	return (comp(x, y)) ? x : y;
}


template <typename T>
T CREF max(
	T CREF x,
	T CREF y
) {
	return (x < y) ? y : x;
}


template <typename T, typename BinaryPredicate>
T CREF max(
	T CREF x,
	T CREF y
	, BinaryPredicate comp
) {
	return (comp(x, y)) ? y : x;
}


template <typename T>
T CREF clamp(
	T CREF x,
	T CREF min,
	T CREF max
) {
	return ft::max(min, ft::min(x, max));
}


template <typename T, typename BinaryPredicate>
T CREF clamp(
	T CREF x,
	T CREF min,
	T CREF max,
	BinaryPredicate comp
) {
	return ft::max(min, ft::min(x, max, comp), comp);
}


template<class InputIt, class T>
InputIt find(
	InputIt first,
	InputIt last,
	T CREF value
) {
	for (; first != last; ++first)
		if (*first == value)
			return first;
	return last;
}


template<class InputIt, class UnaryPred>
InputIt find_if(
	InputIt first,
	InputIt last,
	UnaryPred pred
) {
	for (; first != last; ++first)
		if (pred(*first))
			return first;
	return last;
}


template< class ForwardIt, class T >
ForwardIt remove(
	ForwardIt first,
	ForwardIt last,
	T CREF value
) {
	first = find(first, last, value);
	for (ForwardIt it = first; ++it != last;)
		if (!(*it == value))
			*first++ = *it;
	return first;
}


template< class ForwardIt, class UnaryPred >
ForwardIt remove_if(
	ForwardIt first,
	ForwardIt last,
	UnaryPred pred
) {
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
ForwardIt unique(
	ForwardIt first,
	ForwardIt last,
	BinaryPred pred
) {
	if (first == last)
		return last;

	ForwardIt result = first;
	while (++first != last)
		if (!pred(*result, *first) && ++result != first)
			*result = *first;
	return ++result;
}


template<class InputIt, class OutputIt>
OutputIt copy(
	InputIt first,
	InputIt last,
	OutputIt d_first
) {
	for (; first != last; (void)++first, (void)++d_first)
		*d_first = *first;
	return d_first;
}


template<class InputIt, class Size, class OutputIt>
OutputIt copy_n(
	InputIt first,
	Size count,
	OutputIt result
) {
	if (count > 0)
	{
		*result = *first;
		++result;
		for (Size i = 1; i != count; ++i, (void)++result)
			*result = *++first;
	}
	return result;
}


template <class InputIt1, class InputIt2>
bool lexicographical_compare(
	InputIt1 first1,
	InputIt1 last1,
	InputIt2 first2,
	InputIt2 last2
) {
	for(; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		if (*first1 < *first2)
			return true;
		if (*first2 < *first1)
			return false;
	}
	return (first1 == last1) && (first2 != last2);
}


template <class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(
	InputIt1 first1,
	InputIt1 last1,
	InputIt2 first2,
	InputIt2 last2,
	Compare comp
) {
	for(; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		if (comp(*first1, *first2))
			return true;
		if (comp(*first2, *first1))
			return false;
	}
	return (first1 == last1) && (first2 != last2);
}


}

#endif //ALGORITHM_H
