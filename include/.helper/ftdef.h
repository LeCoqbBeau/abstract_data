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

# include <string>	// for std::string, might implement ft::string later
# include <memory>	// for std::allocator, might implement ft::allocator later
					// subjects ask for use of std::allocator ??? what does it mean?

namespace ft {

typedef long int	ptrdiff_t;

typedef size_t		size_t;

typedef std::string	string;
typedef ft::string	str;

# define FT_ALLOCATOR(T) std::allocator<T>

}

#endif //DEF_H
