//
// Created by mscheman on 2/16/26.
//

#ifndef TYPES_HPP
#define TYPES_HPP


typedef std::string	str;
#include "Fat.hpp"


#ifndef USE_FT
# include <list>
# include <deque>
# include <vector>
# include <set>
# include <map>
#else
# include "list.hpp"
# include "deque.hpp"
# include "vector.hpp"
# include "set.hpp"
# include "map.hpp"
#endif


namespace ns = TESTED_NAMESPACE;


// Sequence Containers


typedef ns::list<int>	intList_t;
typedef ns::list<str>	strList_t;
typedef ns::list<Fat>	fatList_t;


typedef ns::deque<int>	intDeque_t;
typedef ns::deque<str>	strDeque_t;
typedef ns::deque<Fat>	fatDeque_t;


typedef ns::vector<int>	intVector_t;
typedef ns::vector<str>	strVector_t;
typedef ns::vector<Fat>	fatVector_t;


typedef ::testing::Types<
	intList_t, strList_t, fatList_t
>	testList_type;


typedef ::testing::Types<
	intDeque_t, strDeque_t, fatDeque_t
>	testDeque_type;


typedef ::testing::Types<
	intVector_t, strVector_t, fatVector_t
>	testVector_type;


typedef ::testing::Types<
	intList_t, strList_t, fatList_t,
	intDeque_t, strDeque_t, fatDeque_t,
	intVector_t, strVector_t, fatVector_t
>	sequenceContainers_type;


// Associative Containers


typedef ns::set<int>			intSet_t;
typedef ns::set<str>			strSet_t;
typedef ns::set<Fat>			fatSet_t;


typedef ns::multiset<int>		intMSet_t;
typedef ns::multiset<str>		strMSet_t;
typedef ns::multiset<Fat>		fatMSet_t;


typedef ns::map<int, int>		intMap_t;
typedef ns::map<str, str>		strMap_t;
typedef ns::map<Fat, Fat>		fatMap_t;


typedef ns::multimap<int, int>	intMMap_t;
typedef ns::multimap<str, str>	strMMap_t;
typedef ns::multimap<Fat, Fat>	fatMMap_t;


typedef ::testing::Types<
	intSet_t, strSet_t, fatSet_t
>	testSet_type;


typedef ::testing::Types<
	intMSet_t, strMSet_t, fatMSet_t
>	testMSet_type;


typedef ::testing::Types<
	intMap_t, strMap_t, fatMap_t
>	testMap_type;


typedef ::testing::Types<
	intMMap_t, strMMap_t, fatMMap_t
>	testMMap_type;


typedef ::testing::Types<
	intSet_t, strSet_t, fatSet_t,
	intMSet_t, strMSet_t, fatMSet_t,
	intMap_t, strMap_t, fatMap_t,
	intMMap_t, strMMap_t, fatMMap_t
>	associativeContainers_type;


#endif //TYPES_HPP
