//
// Created by mscheman on 2/16/26.
//

#ifndef TYPES_HPP
#define TYPES_HPP


#include "NumStrings.hpp"
#include "Fat.hpp"


#define ENABLE_SEQUENCE		true
#define ENABLE_ASSOCIATIVE	false
#define ENABLE_ADAPTORS		false


#ifndef USE_FT

# if ENABLE_SEQUENCE == true
#  include <deque>
#  include <vector>
#  include <list>
# endif

# if ENABLE_SEQUENCE
#  include <set>
#  include <map>
# endif

# if ENABLE_ADAPTORS
#  include <queue>
#  include <stack>
# endif

#else

# if ENABLE_SEQUENCE == true
#  include "deque.hpp"
#  include "vector.hpp"
#  include "list.hpp"
# endif

# if ENABLE_SEQUENCE
#  include "set.hpp"
#  include "map.hpp"
# endif

# if ENABLE_ADAPTORS
#  include "queue.hpp"
#  include "stack.hpp"
# endif

#endif


namespace ft {}; // failsafe
namespace ns			= TESTED_NAMESPACE;
namespace otherspace	= UNTESTED_NAMESPACE;


// Sequence Containers
#if ENABLE_SEQUENCE == true


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
	intList_t,		strList_t,		fatList_t//,
	// intDeque_t,		strDeque_t,		fatDeque_t
	// intVector_t,	strVector_t,	fatVector_t
>	sequenceContainers_type;


#endif // ENABLE_SEQUENCE


// Associative Containers
#if ENABLE_ASSOCIATIVE == true


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
	intSet_t,	strSet_t,	fatSet_t,
	intMSet_t,	strMSet_t,	fatMSet_t,
	intMap_t,	strMap_t,	fatMap_t,
	intMMap_t,	strMMap_t,	fatMMap_t
>	associativeContainers_type;


#endif // ENABLE_ASSOCIATIVE


//	Adaptor Containers
#if ENABLE_ADAPTORS == true


# include <deque>
# include <vector>

# include "deque.hpp"
# include "vector.hpp"


typedef ns::queue<int, ns::deque<int> >						intNQueue_t;
typedef ns::queue<str, ns::deque<str> >						strNQueue_t;
typedef ns::queue<Fat, ns::deque<Fat> >						fatNQueue_t;
typedef ns::queue<int, otherspace::deque<int> >				intBQueue_t;
typedef ns::queue<str, otherspace::deque<str> >				strBQueue_t;
typedef ns::queue<Fat, otherspace::deque<Fat> >				fatBQueue_t;


typedef ns::priority_queue<int, ns::vector<int> >			intNPQueue_t;
typedef ns::priority_queue<str, ns::vector<str> >			strNPQueue_t;
typedef ns::priority_queue<Fat, ns::vector<Fat> >			fatNPQueue_t;
typedef ns::priority_queue<int, otherspace::vector<int> >	intBPQueue_t;
typedef ns::priority_queue<str, otherspace::vector<str> >	strBPQueue_t;
typedef ns::priority_queue<Fat, otherspace::vector<Fat> >	fatBPQueue_t;


typedef ns::stack<int, ns::deque<int> >						intNStack_t;
typedef ns::stack<str, ns::deque<str> >						strNStack_t;
typedef ns::stack<Fat, ns::deque<Fat> >						fatNStack_t;
typedef ns::stack<int, otherspace::deque<int> >				intBStack_t;
typedef ns::stack<str, otherspace::deque<str> >				strBStack_t;
typedef ns::stack<Fat, otherspace::deque<Fat> >				fatBStack_t;



typedef ::testing::Types<
	intNQueue_t, strNQueue_t, fatNQueue_t,
	intBQueue_t, strBQueue_t, fatBQueue_t
>	testQueue_type;


typedef ::testing::Types<
	intNPQueue_t, strNPQueue_t, fatNPQueue_t,
	intBPQueue_t, strBPQueue_t, fatBPQueue_t
>	testPQueue_type;


typedef ::testing::Types<
	intNStack_t, strNStack_t, fatNStack_t,
	intBStack_t, strBStack_t, fatBStack_t
>	testStack_type;


typedef ::testing::Types<
	intNQueue_t, strNQueue_t, fatNQueue_t,
	intBQueue_t, strBQueue_t, fatBQueue_t,
	intNPQueue_t, strNPQueue_t, fatNPQueue_t,
	intBPQueue_t, strBPQueue_t, fatBPQueue_t,
	intNStack_t, strNStack_t, fatNStack_t,
	intBStack_t, strBStack_t, fatBStack_t
>	adaptorContainers_type;


#endif // ENABLE_ADPATORS


#endif //TYPES_HPP
