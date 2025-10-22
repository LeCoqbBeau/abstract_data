//
// Created by mscheman on 10/22/25.
//

#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#define IS_INT_TRAIT(TYPE)			\
template<>							\
struct is_integer<TYPE>				\
{									\
	enum { value = 1 };				\
	typedef true_type type;			\
};									\
template<>							\
struct is_integer<unsigned TYPE>	\
{									\
	enum { value = 1 };				\
	typedef true_type type;			\
};

namespace ft {
namespace traits {

struct true_type {};
struct false_type {};

template <typename T> struct is_integer {
	enum { value = 0 };
	typedef false_type type;
};

template<> struct is_integer<bool> {
	enum { value = 1 };
	typedef true_type type;
};

template<> struct is_integer<char> {
	enum { value = 1 };
	typedef true_type type;
};

template<> struct is_integer<signed char> {
	enum { value = 1 };
	typedef true_type type;
};

template<> struct is_integer<unsigned char> {
	enum { value = 1 };
	typedef true_type type;
};

IS_INT_TRAIT(short);
IS_INT_TRAIT(int);
IS_INT_TRAIT(long);
IS_INT_TRAIT(long long);

}
}

#undef IS_INT_TRAIT

#endif //TYPE_TRAITS_H
