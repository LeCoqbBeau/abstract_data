//
// Created by mscheman on 2/16/26.
//

#ifndef TYPES_HPP
#define TYPES_HPP


#include "NumStrings.hpp"
#include "Fat.hpp"


#ifndef USE_FT


#include <utility>
template <typename T, typename U>
std::ostream REF operator << (std::ostream REF os, std::pair<T, U> CREF pair)
{
	os << "< " << pair.first << " -=- " << pair.second << " >";
	return os;
}

#include <unordered_set>
#include <unordered_map>


# else


#include "utility.hpp"
template <typename T, typename U>
std::ostream REF operator << (std::ostream REF os, ft::pair<T, U> CREF pair)
{
	os << "< " << pair.first << " -=- " << pair.second << " >";
	return os;
}

#include "unordered_set.hpp"
#include "unordered_map.hpp"


#endif


namespace ns			= TESTED_NAMESPACE;



struct HashFat {
	ns::size_t operator ()(Fat CREF f) const { return ns::hash<unsigned long int>()(reinterpret_cast<unsigned long int>(f.chonk)); }
};


typedef ::ns::unordered_set<int>					intUSet_t;
typedef ::ns::unordered_set<str>					strUSet_t;
typedef ::ns::unordered_set<Fat, HashFat>			fatUSet_t;


typedef ::ns::unordered_multiset<int>				intUMSet_t;
typedef ::ns::unordered_multiset<str>				strUMSet_t;
typedef ::ns::unordered_multiset<Fat, HashFat>		fatUMSet_t;


typedef ::ns::unordered_map<int, int>				intUMap_t;
typedef ::ns::unordered_map<str, str>				strUMap_t;
typedef ::ns::unordered_map<Fat, Fat, HashFat>		fatUMap_t;


typedef ::ns::unordered_multimap<int, int>			intUMMap_t;
typedef ::ns::unordered_multimap<str, str>			strUMMap_t;
typedef ::ns::unordered_multimap<Fat, Fat, HashFat>	fatUMMap_t;


typedef ::testing::Types<
	intUSet_t, strUSet_t, fatUSet_t
>	testUSet_type;


typedef ::testing::Types<
	intUMSet_t, strUMSet_t, fatUMSet_t
>	testUMSet_type;


typedef ::testing::Types<
	intUMap_t, strUMap_t, fatUMap_t
>	testUMap_type;


typedef ::testing::Types<
	intUMMap_t, strUMMap_t, fatUMMap_t
>	testUMMap_type;


typedef ::testing::Types<
	intUSet_t//,	strUSet_t,	fatUSet_t,
	// intUMSet_t,	strUMSet_t,	fatUMSet_t,
	// intUMap_t,	strUMap_t,	fatUMap_t,
	// intUMMap_t,	strUMMap_t,	fatUMMap_t
>	hashmapsContainers_type;


#endif //TYPES_HPP
