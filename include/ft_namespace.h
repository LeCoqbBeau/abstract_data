//
// Created by mscheman on 9/8/25.
//

#ifndef FT_NAMESPACE_H
#define FT_NAMESPACE_H

#include "helper/utils.h"

namespace ft {
	// Typedef
	typedef long int ptrdiff_t;

	// helper/iterator.h
	typedef std::input_iterator_tag input_iterator_tag;
	typedef std::output_iterator_tag output_iterator_tag;
	typedef std::forward_iterator_tag forward_iterator_tag;
	typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag random_access_iterator_tag;

	template<
		class Category,
		class T,
		class Distance = ft::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	> struct iterator;
	template < class Iter >
	class reverse_iterator;

	// helper/exception.h
	class exception;

	// helper/ftexcept.h
	class logic_error;
	class invalid_argument;
    class domain_error;
    class length_error;
    class out_of_range;
	class runtime_error;
	class range_error;
	class overflow_error;
	class underflow_error;
	class bad_alloc;

	// helper/algorithm.h
	TEMPLATE_T void swap(T REF x, T REF y);
	template<class InputIt, class T>
	InputIt find( InputIt first, InputIt last, T CREF value );
	template<class InputIt, class UnaryPred>
	InputIt find_if( InputIt first, InputIt last, UnaryPred pred );
	template<class ForwardIt, class T>
	ForwardIt remove(ForwardIt first, ForwardIt last, T CREF value);
	template<class ForwardIt, class UnaryPred>
	ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPred pred);
	template<class ForwardIt>
	ForwardIt unique(ForwardIt first, ForwardIt last);
	template<class ForwardIt, class BinaryPred>
	ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPred pred);

	// list.h
	template<class T, class Allocator>
	class list;
}

#endif //FT_NAMESPACE_H
