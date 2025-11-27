//
// Created by mscheman on 10/20/25.
//

#ifndef DEF_H
#define DEF_H

#ifndef FT_NOTHROW
# define FT_NOTHROW throw()
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
# define CREF const&
#endif

#ifndef REF
# define REF &
#endif

#ifndef FT_NOMINMAX
# define FT_NOMINMAX 1
#endif

# include <string>	// for std::string, might implement ft::string later

namespace ft {

typedef long int	ptrdiff_t;
typedef size_t		size_t;
typedef std::string	string;

}

#endif //DEF_H
