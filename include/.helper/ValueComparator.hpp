//
// Created by mscheman on 2/11/26.
//

#ifndef VALUECOMPARATOR_HPP
#define VALUECOMPARATOR_HPP

#include "ftdef.hpp"
#include "type_traits.hpp"

// Helper Class Definition
template <typename extractKey, typename Comp>
struct ValueComparator {};


template <typename Comp>
struct ValueComparator<ft::false_type, Comp>  { // Don't extract keys
	explicit ValueComparator(Comp CREF comp) : _comp(comp) {}
	template <typename T>	bool operator()(T CREF lhs, T CREF rhs) { return _comp(lhs, rhs); }
	template <typename T>	bool operator()(T CREF lhs, T CREF rhs) const { return _comp(lhs, rhs); }
	Comp CREF _comp;
};


template <typename Comp>
struct ValueComparator<ft::true_type, Comp>  { // Extract keys
	explicit ValueComparator(Comp CREF comp) : _comp(comp) {}
	template <typename T>	bool operator()(T CREF lhs, T CREF rhs) { return _comp(lhs.first, rhs.first); }
	template <typename T>	bool operator()(T CREF lhs, T CREF rhs) const { return _comp(lhs.first, rhs.first); }
	Comp CREF _comp;
};

#endif //VALUECOMPARATOR_HPP
