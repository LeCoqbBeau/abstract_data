//
// Created by lecoqbeau on 3/4/26.
//

#ifndef DISPATCH_HPP
#define DISPATCH_HPP

#include ".helper/iterator.hpp"
#include ".helper/type_traits.hpp"

namespace ft {


struct dispatch_int		{};
struct dispatch_input	{};
struct dispatch_forward	{};


namespace internal {


template <typename IteratorCategory>
struct dispatch_impl_helper {
	typedef dispatch_forward	type;
};


template <>
struct dispatch_impl_helper<ft::input_iterator_tag> {
	typedef dispatch_input	type;
};


template <typename Iterator, bool isIntegral>
struct dispatch_impl {
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename dispatch_impl_helper<iterator_category>::type		type;
};


template <typename Integer>
struct dispatch_impl<Integer, true> {
	typedef dispatch_int type;
};


}

template <typename T>
struct dispatch {
	typedef typename internal::dispatch_impl<T, IS_INTEGRAL_V(T)>::type type;
	static type	identify() { return type(); }
};

}

#endif //DISPATCH_HPP