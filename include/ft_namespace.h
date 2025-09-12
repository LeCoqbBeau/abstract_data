//
// Created by mscheman on 9/8/25.
//

#ifndef FT_NAMESPACE_H
#define FT_NAMESPACE_H

#include "utils.h"

namespace ft {
	// list.h
	template<class T, class Allocator>
	class list;

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
