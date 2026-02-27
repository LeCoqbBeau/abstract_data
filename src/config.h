//
// Created by mscheman on 2/13/26.
//

#ifndef CONFIG_H
#define CONFIG_H


#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE std
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


template <typename T, typename U>
std::ostream REF operator << (std::ostream REF os, std::pair<T, U> CREF pair)
{
	os << "< " << pair.first << " -=- " << pair.second << " >";
	return os;
}


template <typename TypeParam>
void printContainer(TypeParam c, std::ostream REF os)
{
	for (typename TypeParam::iterator it = c.begin(); it != c.end(); ++it)
		os << *it << " > ";
	os << std::endl;
}


#include "types.hpp"
#include "Generator.hpp"
#include "HelperFunctors.hpp"


#include <fstream>

#endif //CONFIG_H
