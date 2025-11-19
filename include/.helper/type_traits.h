//
// Created by mscheman on 10/22/25.
//

#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

namespace ft {
namespace traits {

template<typename T, T v>
struct integral_constant {
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T, v> type;

	operator value_type() const FT_NOTHROW { return value; }
	value_type operator()() const FT_NOTHROW { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <bool B> struct bool_constant : public integral_constant<bool, B> {};

typedef char	yes_type;						// sizeof(yes_type) == 1
struct			no_type { char padding[8]; };	// sizeof(no_type)  != 1

struct unused {};

template <bool B, typename T = void>		struct enable_if {};
template <typename T>						struct enable_if<true, T> { typedef T type; };
#define										ENABLE_IF_T(B, T) ft::traits::enable_if<B, T>::type
#define										ENABLE_IF_TT(B, T) typename ft::traits::enable_if<B, T>::type

template <bool B, typename T = void>		struct disable_if {};
template <typename T>						struct disable_if<false, T> { typedef T type; };
#define										DISABLE_IF_T(B, T) ft::traits::disable_if<B, T>::type
#define										DISABLE_IF_TT(B, T) typename ft::traits::disable_if<B, T>::type

template <bool B, typename T, typename F>	struct conditional { typedef T type; };
template <typename T, typename F>			struct conditional<false, T, F> { typedef F type; };
#define										CONDITIONAL_T(B, T, F) ft::traits::conditional<B, T, F>::type
#define										CONDITIONAL_TT(B, T, F) typename ft::traits::conditional<B, T, F>::type

template <typename T, typename U>			struct is_same : public false_type {};
template <typename T>						struct is_same<T, T> : public true_type {};
#define										IS_SAME_V(T, U) ft::traits::is_same<T, U>::value

template <typename T>						struct is_const : public false_type {};
template <typename T>						struct is_const<const T> : public true_type {};
#define										IS_CONST_V(T) ft::traits::is_const<T>::value

template <typename T>						struct is_volatile : public false_type {};
template <typename T>						struct is_volatile<volatile T> : public true_type {};
#define										IS_VOLATILE_V(T) ft::traits::is_volatile<T>::value

template <typename T>						struct is_reference      : public false_type{};
template <typename T>						struct is_reference<T REF>  : public true_type{};
#define										IS_REFERENCE_V(T) ft::traits::is_reference<T>::value

template <typename T>						struct remove_const				{ typedef T type;    };
template <typename T>						struct remove_const<const T>	{ typedef T type;    };
template <typename T>						struct remove_const<const T[]>	{ typedef T type[];  };
template <typename T, size_t N>				struct remove_const<const T[N]>	{ typedef T type[N]; };
#define										REMOVE_CONST_T(T) ft::traits::remove_const<T>::type
#define										REMOVE_CONST_TT(T) typename ft::traits::remove_const<T>::type

template <typename T>						struct remove_volatile					{ typedef T type;    };
template <typename T>						struct remove_volatile<volatile T>		{ typedef T type;    };
template <typename T>						struct remove_volatile<volatile T[]>	{ typedef T type[];  };
template <typename T, size_t N>				struct remove_volatile<volatile T[N]>	{ typedef T type[N]; };
#define										REMOVE_VOLATILE_T(T) ft::traits::remove_volatile<T>::type
#define										REMOVE_VOLATILE_TT(T) typename ft::traits::remove_volatile<T>::type

template <typename T>						struct remove_cv { typedef REMOVE_VOLATILE_TT(REMOVE_CONST_TT(T)) type; };
#define										REMOVE_CV_T(T) ft::traits::remove_cv<T>::type
#define										REMOVE_CV_TT(T) typename ft::traits::remove_cv<T>::type

template <typename T> 						struct remove_reference			{ typedef T type; };
template <typename T> 						struct remove_reference<T REF>	{ typedef T type; };
#define										REMOVE_REFERENCE_T(T) ft::traits::remove_reference<T>::type
#define										REMOVE_REFERENCE_TT(T) typename ft::traits::remove_reference<T>::type

template <typename T> 						struct remove_cvref	{ typedef REMOVE_CV_TT(REMOVE_REFERENCE_TT(T)) type; };
#define										REMOVE_CVREF_T(T) ft::traits::remove_cvref<T>::type
#define										REMOVE_CVREF_TT(T) typename ft::traits::remove_cvref<T>::type

template <typename T>						struct is_integral_helper						: public false_type{};
template <> 								struct is_integral_helper<unsigned char>		: public true_type{};
template <> 								struct is_integral_helper<unsigned short>		: public true_type{};
template <> 								struct is_integral_helper<unsigned int>			: public true_type{};
template <> 								struct is_integral_helper<unsigned long>		: public true_type{};
template <> 								struct is_integral_helper<unsigned long long>	: public true_type{};
template <> 								struct is_integral_helper<signed char>			: public true_type{};
template <> 								struct is_integral_helper<signed short>			: public true_type{};
template <> 								struct is_integral_helper<signed int>			: public true_type{};
template <> 								struct is_integral_helper<signed long>			: public true_type{};
template <> 								struct is_integral_helper<signed long long>		: public true_type{};
template <> 								struct is_integral_helper<bool>					: public true_type{};
template <> 								struct is_integral_helper<char>					: public true_type{};
template <typename T>						struct is_integral : public is_integral_helper<REMOVE_CV_TT(T)>{};
#define										IS_INTEGRAL_V(T) ft::traits::is_integral<T>::value
#define										IS_INTEGRAL_T(T) ft::traits::is_integral<T>::type
#define										IS_INTEGRAL_TT(T) typename ft::traits::is_integral<T>::type

}
}

#undef IS_INT_TRAIT

#endif //TYPE_TRAITS_H
