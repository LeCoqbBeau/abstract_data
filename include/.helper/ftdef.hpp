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


#ifndef TRY_ALLOCATION
	#define TRY_ALLOCATION(lines, clean) try { lines } catch (...) { do { clean } while (false); throw ft::bad_alloc("allocation failed"); }
#endif


# include <string>

namespace ft {

typedef long int	ptrdiff_t;
typedef size_t		size_t;
typedef std::string	string;
typedef ft::string	str;

template <typename T>
struct allocator : public std::allocator<T> {};

}

#endif //DEF_H
