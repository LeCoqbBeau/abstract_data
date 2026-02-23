//
// Created by mscheman on 10/17/25.
//

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "ftdef.hpp"
#include "iterator.hpp"


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


template <class InputIt, class T>
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


template <class InputIt, class UnaryPred>
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


template <class ForwardIt, class T>
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


template <class ForwardIt, class UnaryPred>
ForwardIt remove_if(
	ForwardIt first,
	ForwardIt last,
	UnaryPred pred
) {
	first = ft::find_if(first, last, pred);
	for (ForwardIt it = first; it != last; ++it)
		if (!pred(*it))
			*first++ = *it;
	return first;
}


template <class ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last) {
	if (first == last)
		return last;

	ForwardIt result = first;
	while (++first != last)
		if (!(*result == *first) && ++result != first)
			*result = *first;
	return ++result;
}


template <class ForwardIt, class BinaryPred>
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


template <class InputIt, class OutputIt>
OutputIt copy(
	InputIt first,
	InputIt last,
	OutputIt d_first
) {
	for (; first != last; (void)++first, (void)++d_first)
		*d_first = *first;
	return d_first;
}


template<class BidirIt1, class BidirIt2>
BidirIt2 rcopy(
	BidirIt1 first,
	BidirIt1 last,
	BidirIt2 d_last
) {
	while (first != last)
		*(--d_last) = *(--last);
	return d_last;
}


template <class InputIt, class Size, class OutputIt>
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


template <class ForwardIt, class T>
void fill(
	ForwardIt first,
	ForwardIt last,
	T CREF value
) {
	for (; first != last; ++first)
		*first = value;
}


template <class OutputIt, class Size, class T>
OutputIt fill_n(OutputIt first, Size count, T CREF value)
{
	for (Size i = 0; i < count; ++i)
		*first++ = value;
	return first;
}


template <class InputIterator1, class InputIterator2>
bool equal(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2
) {
	while (first1 != last1) {
		if (*first1 != *first2)
			return false;
		++first1;
		++first2;
	}
	return true;
}


template <class InputIterator1, class InputIterator2, class BinaryPred>
bool equal(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	BinaryPred pred
) {
	while (first1!=last1) {
		if (!pred(*first1,*first2))
			return false;
		++first1;
		++first2;
	}
	return true;
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


//
//	Heap
//


namespace internal {

template <typename RandomAccessIterator, typename Distance, typename T, typename ValueType>
void promote_heap_impl(
	RandomAccessIterator first,
	Distance topPosition,
	Distance position,
	T value
) {
	for (
		Distance parentPosition = (position - 1) / 2;
		(position > topPosition) && (*(first + parentPosition) < value);
		parentPosition = (position - 1) >> 1
	) {
		*(first + position) = *(first + parentPosition);
		position = parentPosition;
	}
	*(first + position) = value;
}

template <typename RandomAccessIterator, typename Distance, typename T, typename Compare, typename ValueType>
void promote_heap_impl(
	RandomAccessIterator first,
	Distance topPosition,
	Distance position,
	T value,
	Compare compare
) {
	for (
		Distance parentPosition = (position - 1) / 2;
		(position > topPosition) && compare(*(first + parentPosition), value);
		parentPosition = (position - 1) >> 1
	) {
		*(first + position) = *(first + parentPosition);
		position = parentPosition;
	}
	*(first + position) = value;
}

}


template <typename RandomAccessIterator, typename Distance, typename T>
void promote_heap(
	RandomAccessIterator first,
	Distance topPosition,
	Distance position,
	T CREF value
) {
	typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
	internal::promote_heap_impl<RandomAccessIterator, Distance, T CREF, value_type const>(
		first,
		topPosition,
		position,
		value
	);
}


template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
void promote_heap(
	RandomAccessIterator first,
	Distance topPosition,
	Distance position,
	T CREF value,
	Compare compare
) {
	typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
	internal::promote_heap_impl<RandomAccessIterator, Distance, T CREF, Compare, value_type const>(
		first,
		topPosition,
		position,
		value,
		compare
	);
}


namespace internal {

template <typename RandomAccessIterator, typename Distance, typename T, typename ValueType>
void adjust_heap_impl(
	RandomAccessIterator first,
	Distance topPosition,
	Distance heapSize,
	Distance position,
	T value
) {
	Distance childPosition = (2 * position) + 2;

	for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2)
	{
		if (*(first + childPosition) < *(first + (childPosition - 1)))
			--childPosition;
		*(first + position) = *(first + childPosition);
		position = childPosition;
	}
	if (childPosition == heapSize)
	{
		*(first + position) = *(first + (childPosition - 1));
		position = childPosition - 1;
	}
	ft::promote_heap<RandomAccessIterator, Distance, T>(first, topPosition, position, value);
}

template <typename RandomAccessIterator, typename Distance, typename T, typename Compare, typename ValueType>
void adjust_heap_impl(
	RandomAccessIterator first,
	Distance topPosition,
	Distance heapSize,
	Distance position,
	T value,
	Compare compare
) {
	Distance childPosition = (2 * position) + 2;

	for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2)
	{
		if(compare(*(first + childPosition), *(first + (childPosition - 1))))
			--childPosition;
		*(first + position) = *(first + childPosition);
		position = childPosition;
	}
	if (childPosition == heapSize)
	{
		*(first + position) = *(first + (childPosition - 1));
		position = childPosition - 1;
	}
	ft::promote_heap<RandomAccessIterator, Distance, T, Compare>(first, topPosition, position, value, compare);
}

}


template <typename RandomAccessIterator, typename Distance, typename T>
void adjust_heap(
	RandomAccessIterator first,
	Distance topPosition,
	Distance heapSize,
	Distance position,
	T CREF value
) {
	typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
	internal::adjust_heap_impl<RandomAccessIterator, Distance, T CREF, value_type const>(
		first,
		topPosition,
		heapSize,
		position,
		value
	);
}


template <typename RandomAccessIterator, typename Distance, typename T, typename Compare>
void adjust_heap(
	RandomAccessIterator first,
	Distance topPosition,
	Distance heapSize,
	Distance position,
	T CREF value,
	Compare compare
) {
	typedef typename iterator_traits<RandomAccessIterator>::value_type value_type;
	internal::adjust_heap_impl<RandomAccessIterator, Distance, T CREF, Compare, const value_type>(
		first,
		topPosition,
		heapSize,
		position,
		value,
		compare
	);
}


template <typename RandomAccessIterator>
void make_heap(
	RandomAccessIterator first,
	RandomAccessIterator last
) {
	typedef typename ft::iterator_traits<RandomAccessIterator>::difference_type	difference_type;
	typedef typename ft::iterator_traits<RandomAccessIterator>::value_type		value_type;

	difference_type const heapSize = last - first;
	if (heapSize < 2)
		return ;
	difference_type parentPosition = ((heapSize - 2) / 2) + 1;
	do{
		--parentPosition;
		value_type temp(*(first + parentPosition));
		ft::adjust_heap<RandomAccessIterator, difference_type, value_type>(
			first,
			parentPosition,
			heapSize,
			parentPosition,
			temp
		);
	} while(parentPosition != 0);
}


template <typename RandomAccessIterator, typename Compare>
void make_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare compare
) {
	typedef typename ft::iterator_traits<RandomAccessIterator>::difference_type difference_type;
	typedef typename ft::iterator_traits<RandomAccessIterator>::value_type      value_type;

	const difference_type heapSize = last - first;

	if (heapSize < 2)
		return;
	difference_type parentPosition = ((heapSize - 2) / 2) + 1;
	do{
		--parentPosition;
		value_type temp(*(first + parentPosition));
		ft::adjust_heap<RandomAccessIterator, difference_type, value_type, Compare> (
			first,
			parentPosition,
			heapSize,
			parentPosition,
			temp,
			compare
		);
	} while(parentPosition != 0);
}


template <typename RandomAccessIterator>
void push_heap(
	RandomAccessIterator first,
	RandomAccessIterator last
) {
	typedef typename ft::iterator_traits<RandomAccessIterator>::difference_type	difference_type;
	typedef typename ft::iterator_traits<RandomAccessIterator>::value_type		value_type;

	value_type const tempBottom(*(last - 1));
	ft::promote_heap<RandomAccessIterator, difference_type, value_type>(
		first,
		static_cast<difference_type>(0),
		static_cast<difference_type>(last - first - 1),
		tempBottom
	);
}


template <typename RandomAccessIterator, typename Compare>
void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
	typedef typename ft::iterator_traits<RandomAccessIterator>::difference_type	difference_type;
	typedef typename ft::iterator_traits<RandomAccessIterator>::value_type		value_type;

	const value_type tempBottom(*(last - 1));

	ft::promote_heap<RandomAccessIterator, difference_type, value_type, Compare>(
		first,
		static_cast<difference_type>(0),
		static_cast<difference_type>(last - first - 1),
		tempBottom,
		compare
	);
}


template <typename RandomAccessIterator>
void pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last
) {
	typedef typename ft::iterator_traits<RandomAccessIterator>::difference_type difference_type;
	typedef typename ft::iterator_traits<RandomAccessIterator>::value_type      value_type;

	value_type tempBottom(*(last - 1));
	*(last - 1) = *first;
	ft::adjust_heap<RandomAccessIterator, difference_type, value_type>(
		first,
		static_cast<difference_type>(0),
		static_cast<difference_type>(last - first - 1),
		0,
		tempBottom
	);
}


template <typename RandomAccessIterator, typename Compare>
void pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare compare
) {
	typedef typename ft::iterator_traits<RandomAccessIterator>::difference_type difference_type;
	typedef typename ft::iterator_traits<RandomAccessIterator>::value_type      value_type;

	value_type tempBottom(*(last - 1));
	*(last - 1) = *first;
	ft::adjust_heap<RandomAccessIterator, difference_type, value_type, Compare>(
		first,
		static_cast<difference_type>(0),
		static_cast<difference_type>(last - first - 1),
		0,
		tempBottom,
		compare
	);
}


// Random function hihi :3
inline void *memcpy(
	void *dest,
	void const* src,
	size_t len
) {
	char* d = static_cast<char*>(dest);
	char const* s = static_cast<char const*>(src);
	while (len--)
		*d++ = *s++;
	return dest;
}

}

#endif //ALGORITHM_H
