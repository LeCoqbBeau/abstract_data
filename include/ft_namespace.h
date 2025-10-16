//
// Created by mscheman on 9/8/25.
//

#ifndef FT_NAMESPACE_H
#define FT_NAMESPACE_H

#include "utils.h"

namespace ft {
	// Typedef
	typedef long int ptrdiff_t;

	// list.h
	template<class T, class Allocator>
	class list;

	// iterator.h
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

	// exception.h
	class exception;

	// ftexcept.h
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
}

#endif //FT_NAMESPACE_H
