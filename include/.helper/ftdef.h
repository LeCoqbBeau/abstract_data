//
// Created by mscheman on 10/20/25.
//

#ifndef DEF_H
#define DEF_H

#define FT_NOTHROW throw()

#ifndef FT_LIKELY
	#if defined(__GNUC__) && (__GNUC__ >= 3)
		#define FT_LIKELY(x)   __builtin_expect(!!(x), true)
		#define FT_UNLIKELY(x) __builtin_expect(!!(x), false)
	#else
		#define FT_LIKELY(x)   (x)
		#define FT_UNLIKELY(x) (x)
	#endif
#endif

namespace ft {
	typedef long int	ptrdiff_t;
	typedef size_t		size_t;
}

#endif //DEF_H
