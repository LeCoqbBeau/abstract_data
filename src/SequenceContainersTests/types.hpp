//
// Created by mscheman on 2/16/26.
//

#ifndef TYPES_HPP
#define TYPES_HPP


#ifndef USE_FT
# include <list>
# include <deque>
# include <vector>
#else
# include "list.hpp"
# include "deque.hpp"
# include "vector.hpp"
#endif

namespace ns = TESTED_NAMESPACE;


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
>	testContainers_type;


#endif //TYPES_HPP
