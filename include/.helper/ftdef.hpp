//
// Created by mscheman on 10/20/25.
//

#ifndef DEF_H
#define DEF_H

#ifndef FT_NOTHROW
	#define FT_NOTHROW throw()
#endif


#ifndef FT_LIKELY
	#if defined(__GNUC__) && (__GNUC__ >= 3)
		#define FT_LIKELY(x)   __builtin_expect(!!(x), true)
		#define FT_UNLIKELY(x) __builtin_expect(!!(x), false)
	#else
		#define FT_LIKELY(x)   (x)
		#define FT_UNLIKELY(x) (x)
	#endif
#endif


#ifndef CREF
	#define CREF const&
#endif


#ifndef REF
	#define REF &
#endif


#ifndef TRY_ALLOC
	#define TRY_ALLOC(alloc, free) try { alloc } catch (...) { do { free } while (false); throw ft::bad_alloc("allocation failed"); }
#endif


#ifndef TRY_RET
	#define	TRY_RET(stmt, ret) try { stmt; } catch (...) { return ret; }
#endif


# include <string> // for std::string :)


namespace ft {

// int types
typedef signed char			int8_t;
typedef unsigned char		uint8_t;
typedef signed short int	int16_t;
typedef unsigned short int	uint16_t;
typedef signed int			int32_t;
typedef unsigned int		uint32_t;
typedef signed long int		int64_t;
typedef unsigned long int	uint64_t;
typedef __int128_t			int128_t;
typedef __uint128_t			uint128_t;


// other
typedef unsigned long int	size_t;
typedef long int			ptrdiff_t;
typedef std::string			string;
typedef ft::string			str;

template <typename T>
struct allocator : public std::allocator<T> {};

}

#endif //DEF_H
