//
// Created by mscheman on 1/24/26.
//

#ifndef STATIC_ASSERT_HPP
#define STATIC_ASSERT_HPP

#include "type_traits.hpp"

namespace ft {

template<bool expr>
struct assertion;


template<>
struct assertion<true>
{
	static const char test;
};


template <int A, int B>
struct is_equal : ft::false_type{};


template<int A>
struct is_equal<A, A> : ft::true_type{};


template <int A, int B>
struct is_not_equal : ft::true_type{};


template <int A>
struct is_not_equal<A, A> : ft::false_type{};


}

# define FT_ASSERT(check) ft::assertion<check>::test

#endif //STATIC_ASSERT_HPP
