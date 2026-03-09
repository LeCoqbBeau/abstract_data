//
// Created by mscheman on 10/22/25.
//

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {


#define FT_COMMA ,


template<typename T, T v>
struct integral_constant {
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T, v> type;

	operator value_type() const { return value; }
	value_type operator()() const { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


template <bool B> struct bool_constant : public integral_constant<bool, B> {};


typedef char	yes_type;						// sizeof(yes_type) == 1
struct			no_type { char padding[8]; };	// sizeof(no_type)  != 1


struct unused {};


template <bool B, typename T = void>		struct enable_if {};
template <typename T>						struct enable_if<true, T> { typedef T type; };


template <bool B, typename T = void>		struct disable_if {};
template <typename T>						struct disable_if<false, T> { typedef T type; };


template <bool B, typename T, typename F>	struct conditional { typedef T type; };
template <typename T, typename F>			struct conditional<false, T, F> { typedef F type; };


template <typename T, typename U>			struct is_same : public false_type {};
template <typename T>						struct is_same<T, T> : public true_type {};


template <typename T>						struct is_const : public false_type {};
template <typename T>						struct is_const<const T> : public true_type {};


template <typename T>						struct is_volatile : public false_type {};
template <typename T>						struct is_volatile<volatile T> : public true_type {};


template <typename T>						struct is_reference      : public false_type{};
template <typename T>						struct is_reference<T REF>  : public true_type{};


template <typename T>						struct remove_const				{ typedef T type;    };
template <typename T>						struct remove_const<const T>	{ typedef T type;    };
template <typename T>						struct remove_const<const T[]>	{ typedef T type[];  };
template <typename T, size_t N>				struct remove_const<const T[N]>	{ typedef T type[N]; };


template <typename T>						struct remove_volatile					{ typedef T type;    };
template <typename T>						struct remove_volatile<volatile T>		{ typedef T type;    };
template <typename T>						struct remove_volatile<volatile T[]>	{ typedef T type[];  };
template <typename T, size_t N>				struct remove_volatile<volatile T[N]>	{ typedef T type[N]; };


template <typename T>						struct remove_cv { typedef typename remove_volatile<typename remove_const<T>::type>::type type; };


template <typename T> 						struct remove_reference			{ typedef T type; };
template <typename T> 						struct remove_reference<T REF>	{ typedef T type; };


template <typename T> 						struct remove_cvref	{ typedef typename remove_cv<typename remove_reference<T>::type>::type type; };


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
template <typename T>						struct is_integral : public is_integral_helper<typename remove_cv<T>::type>{};


template <typename T>						struct is_floating_point_helper					: public false_type{};
template <>									struct is_floating_point_helper<float>			: public true_type{};
template <>									struct is_floating_point_helper<double>			: public true_type{};
template <>									struct is_floating_point_helper<long double>	: public true_type{};
template <typename T>						struct is_floating_point : public is_floating_point_helper<typename remove_cv<T>::type>{};


template <typename T>
struct										is_arithmetic : public integral_constant<bool, is_integral<T>::value || is_floating_point<T>::value >{};


template <typename T, bool = is_arithmetic<T>::value>
struct										is_signed_helper			: public bool_constant<T(-1) < T(0)> {};
template <typename T> struct				is_signed_helper<T, false>	: public false_type {};
template <typename T> struct				is_signed					: public ft::is_signed_helper<T>::type {};


template <typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void, typename T6 = void, typename T7 = void, typename T8 = void>
struct make_void {
	typedef void type;
};


#if __cplusplus < 201103L // c++98
# define	ENABLE_IF_T(B, T) ft::enable_if<B, T>::type
# define	ENABLE_IF_TT(B, T) typename ft::enable_if<B, T>::type
# define	DISABLE_IF_T(B, T) ft::disable_if<B, T>::type
# define	DISABLE_IF_TT(B, T) typename ft::disable_if<B, T>::type
# define	CONDITIONAL_T(B, T, F) ft::conditional<B, T, F>::type
# define	CONDITIONAL_TT(B, T, F) typename ft::conditional<B, T, F>::type
# define	IS_SAME_T(T, U) ft::is_same<T, U>::type
# define	IS_SAME_TT(T, U) typename ft::is_same<T, U>::type
# define	IS_SAME_V(T, U) ft::is_same<T, U>::value
# define	IS_CONST_V(T) ft::is_const<T>::value
# define	IS_VOLATILE_V(T) ft::is_volatile<T>::value
# define	IS_REFERENCE_V(T) ft::is_reference<T>::value
# define	REMOVE_CONST_T(T) ft::remove_const<T>::type
# define	REMOVE_CONST_TT(T) typename ft::remove_const<T>::type
# define	REMOVE_VOLATILE_T(T) ft::remove_volatile<T>::type
# define	REMOVE_VOLATILE_TT(T) typename ft::remove_volatile<T>::type
# define	REMOVE_CV_T(T) ft::remove_cv<T>::type
# define	REMOVE_CV_TT(T) typename ft::remove_cv<T>::type
# define	REMOVE_REFERENCE_T(T) ft::remove_reference<T>::type
# define	REMOVE_REFERENCE_TT(T) typename ft::remove_reference<T>::type
# define	REMOVE_CVREF_T(T) ft::remove_cvref<T>::type
# define	REMOVE_CVREF_TT(T) typename ft::remove_cvref<T>::type
# define	IS_INTEGRAL_V(T) ft::is_integral<T>::value
# define	IS_INTEGRAL_T(T) ft::is_integral<T>::type
# define	IS_INTEGRAL_TT(T) typename ft::is_integral<T>::type
# define	IS_FLOATING_POINT_V(T) ft::is_floating_point<T>::value
# define	IS_ARITHMETIC_V(T) ft::is_arithmetic<T>::value
# define	IS_SIGNED_V(T) ft::is_signed<T>::value
# define	MAKE_VOID_T1(T1) typename ft::make_void<T1>::type
# define	MAKE_VOID_T2(T1, T2) typename ft::make_void<T1, T2>::type
# define	MAKE_VOID_T3(T1, T2, T3) typename ft::make_void<T1, T2, T3>::type
# define	MAKE_VOID_T4(T1, T2, T3, T4) typename ft::make_void<T1, T2, T3, T4>::type
# define	MAKE_VOID_T5(T1, T2, T3, T4, T5) typename ft::make_void<T1, T2, T3, T4, T5>::type
# define	MAKE_VOID_T6(T1, T2, T3, T4, T5, T6) typename ft::make_void<T1, T2, T3, T4, T5, T6>::type
# define	MAKE_VOID_T7(T1, T2, T3, T4, T5, T6, T7) typename ft::make_void<T1, T2, T3, T4, T5, T6, T7>::type
# define	MAKE_VOID_T8(T1, T2, T3, T4, T5, T6, T7, T8) typename ft::make_void<T1, T2, T3, T4, T5, T6, T7, T8>::type
#else // c++11
# define	ENABLE_IF_T(B, T) enable_if<B, T>::type
# define	ENABLE_IF_TT(B, T) typename enable_if<B, T>::type
# define	DISABLE_IF_T(B, T) disable_if<B, T>::type
# define	DISABLE_IF_TT(B, T) typename disable_if<B, T>::type
# define	CONDITIONAL_T(B, T, F) conditional<B, T, F>::type
# define	CONDITIONAL_TT(B, T, F) typename conditional<B, T, F>::type
# define	IS_SAME_T(T, U) is_same<T, U>::type
# define	IS_SAME_TT(T, U) typename is_same<T, U>::type
# define	IS_SAME_V(T, U) is_same<T, U>::value
# define	IS_CONST_V(T) is_const<T>::value
# define	IS_VOLATILE_V(T) is_volatile<T>::value
# define	IS_REFERENCE_V(T) is_reference<T>::value
# define	REMOVE_CONST_T(T) remove_const<T>::type
# define	REMOVE_CONST_TT(T) typename remove_const<T>::type
# define	REMOVE_VOLATILE_T(T) remove_volatile<T>::type
# define	REMOVE_VOLATILE_TT(T) typename remove_volatile<T>::type
# define	REMOVE_CV_T(T) remove_cv<T>::type
# define	REMOVE_CV_TT(T) typename remove_cv<T>::type
# define	REMOVE_REFERENCE_T(T) remove_reference<T>::type
# define	REMOVE_REFERENCE_TT(T) typename remove_reference<T>::type
# define	REMOVE_CVREF_T(T) remove_cvref<T>::type
# define	REMOVE_CVREF_TT(T) typename remove_cvref<T>::type
# define	IS_INTEGRAL_V(T) is_integral<T>::value
# define	IS_INTEGRAL_T(T) is_integral<T>::type
# define	IS_INTEGRAL_TT(T) typename is_integral<T>::type
# define	IS_FLOATING_POINT_V(T) is_floating_point<T>::value
# define	IS_ARITHMETIC_V(T) is_arithmetic<T>::value
# define	IS_SIGNED_V(T) is_signed<T>::value
# define	MAKE_VOID_T1(T1) typename make_void<T1>::type
# define	MAKE_VOID_T2(T1, T2) typename make_void<T1, T2>::type
# define	MAKE_VOID_T3(T1, T2, T3) typename make_void<T1, T2, T3>::type
# define	MAKE_VOID_T4(T1, T2, T3, T4) typename make_void<T1, T2, T3, T4>::type
# define	MAKE_VOID_T5(T1, T2, T3, T4, T5) typename make_void<T1, T2, T3, T4, T5>::type
# define	MAKE_VOID_T6(T1, T2, T3, T4, T5, T6) typename make_void<T1, T2, T3, T4, T5, T6>::type
# define	MAKE_VOID_T7(T1, T2, T3, T4, T5, T6, T7) typename make_void<T1, T2, T3, T4, T5, T6, T7>::type
# define	MAKE_VOID_T8(T1, T2, T3, T4, T5, T6, T7, T8) typename make_void<T1, T2, T3, T4, T5, T6, T7, T8>::type
#endif

}


#endif //TYPE_TRAITS_HPP
