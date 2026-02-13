//
// Created by mscheman on 2/13/26.
//

#ifndef SEQUENCE_CONTAINERS_TESTS_TPP
#define SEQUENCE_CONTAINERS_TESTS_TPP

#if ns == std
#include <list>
#include <deque>
#include <vector>
#else
#include "list.hpp"
#include "deque.hpp"
#include "vector.hpp"
#endif

typedef ns::list<int>	intList_t;
typedef ns::list<str>	strList_t;
typedef ns::list<Fat>	fatList_t;

typedef ns::deque<int>	intDeque_t;
typedef ns::deque<str>	strDeque_t;
typedef ns::deque<Fat>	fatDeque_t;

typedef ns::vector<int>	intVector_t;
typedef ns::vector<str>	strVector_t;
typedef ns::vector<Fat>	fatVector_t;

#endif //SEQUENCE_CONTAINERS_TESTS_TPP
