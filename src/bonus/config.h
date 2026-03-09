//
// Created by mscheman on 2/13/26.
//

#ifndef CONFIG_H
#define CONFIG_H


#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE std
#endif


#if TESTED_NAMESPACE == std
# define UNTESTED_NAMESPACE ft
# else
# define UNTESTED_NAMESPACE std
#endif


#ifndef REF
# define REF &
#endif


#ifndef CREF
# define CREF const&
#endif


#ifndef PRINTCONTAINER
#define PRINTCONTAINER
template <typename TypeParam>
void printContainer(TypeParam CREF c, std::ostream REF os = std::cout)
{
	for (typename TypeParam::const_iterator it = c.begin(); it != c.end(); ++it)
		os << *it << " > ";
	os << std::endl;
}
#endif


#include "types.hpp"
#include "Generator.hpp"


#endif //CONFIG_H
