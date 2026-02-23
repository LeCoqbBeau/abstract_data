//
// Created by mscheman on 2/13/26.
//

#ifndef CONFIG_H
#define CONFIG_H


#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE std
#endif


#ifndef BENCHMARK
# define BENCHMARK false
#endif


#include "Timer.hpp"


#if BENCHMARK == true
# define TIME(title) Timer(title)
#else
# define TIME(title)
#endif


#ifndef REF
# define REF &
#endif


#ifndef CREF
# define CREF const&
#endif


// Dont look at me plz
namespace std {
/**
 * @brief Return the nth successor (or -nth predecessor if n is negative) of iterator it.
 *
 * @tparam ForwardIt
 * @param it an iterator
 * @param n a number of elements to advance
 * @return An iterator of type InputIt that holds the nth successor (or -nth predecessor if n is negative) of iterator it.
 *
 *  For random access iterators, this uses their @c + and @c - operations
 *  and are constant time.  For other %iterator classes they are linear time.
 */
template <typename ForwardIt>
ForwardIt next(ForwardIt it, typename std::iterator_traits<ForwardIt>::difference_type n = 1)
{
	std::advance(it, n);
	return it;
}
}
// Okay look again :D


#endif //CONFIG_H
