//
// Created by mscheman on 2/13/26.
//

#ifndef SEQUENCE_CONTAINERS_TESTS_TPP
#define SEQUENCE_CONTAINERS_TESTS_TPP

#define INPUT_IT_TEMPLATE	template <typename InputIt>
#define SCT_ALLOCATOR_PARAM	allocator_type CREF allocator=allocator_type()

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


TEST(List, DefaultConstructor)
{
	TIME("List, DefaultConstructor");

	intList_t intList;
	strList_t strList;
	fatList_t fatList;

	EXPECT_TRUE(intList.empty());
	EXPECT_TRUE(strList.empty());
	EXPECT_TRUE(fatList.empty());
}


TEST(List, FillConstructor)
{
	TIME("List, FillConstructor");

	int const listSize = 50;
	intList_t intContainer(listSize, 10);
	strList_t strContainer(listSize, "10");
	fatList_t fatContainer(listSize, Fat(10, "10"));

	intList_t::iterator intIterator = intContainer.begin();
	strList_t::iterator strIterator = strContainer.begin();
	fatList_t::iterator fatIterator = fatContainer.begin();
	EXPECT_TRUE(intContainer.size() == listSize);
	EXPECT_TRUE(strContainer.size() == listSize);
	EXPECT_TRUE(fatContainer.size() == listSize);
	for (int i = 0; i < listSize; ++i) {
		EXPECT_TRUE(*intIterator == 10);
		EXPECT_TRUE(*strIterator == "10");
		EXPECT_TRUE(*fatIterator == Fat(10, "10"));
		++intIterator;
		++strIterator;
		++fatIterator;
	}
}


TEST(List, RangeConstructor)
{
	TIME("List, RangeConstructor");

#define DATA X(0), X(1), X(2), X(3), X(4), X(5), X(6), X(7), X(8), X(9),
#define DATA_SIZE 10
#define X(elem) elem
	int	intArray[10] = { DATA };
#undef X
#define X(elem) #elem
	str	strArray[10] = { DATA };
#undef X
#define X(elem) Fat(elem, #elem)
	Fat fatArray[10] = { DATA };
#undef X
#undef DATA

	intList_t intContainer(intArray, intArray + 10);
	strList_t strContainer(strArray, strArray + 10);
	fatList_t fatContainer(fatArray, fatArray + 10);

	intList_t::iterator intIterator = intContainer.begin();
	strList_t::iterator strIterator = strContainer.begin();
	fatList_t::iterator fatIterator = fatContainer.begin();
	EXPECT_TRUE(intContainer.size() == DATA_SIZE);
	EXPECT_TRUE(strContainer.size() == DATA_SIZE);
	EXPECT_TRUE(fatContainer.size() == DATA_SIZE);
	for (int i = 0; i < DATA_SIZE; ++i) {
		EXPECT_TRUE(*intIterator == intArray[i]);
		EXPECT_TRUE(*strIterator == strArray[i]);
		EXPECT_TRUE(*fatIterator == fatArray[i]);
		++intIterator;
		++strIterator;
		++fatIterator;
	}
#undef DATA_SIZE
}


TEST(List, CopyConstructor)
{
	TIME("List, CopyConstructor");

#define DATA X(0), X(1), X(2), X(3), X(4), X(5), X(6), X(7), X(8), X(9),
#define DATA_SIZE 10
#define X(elem) elem
	int	intArray[10] = { DATA };
#undef X
#define X(elem) #elem
	str	strArray[10] = { DATA };
#undef X
#define X(elem) Fat(elem, #elem)
	Fat fatArray[10] = { DATA };
#undef X
#undef DATA

	intList_t intList(intArray, intArray + 10);
	strList_t strList(strArray, strArray + 10);
	fatList_t fatList(fatArray, fatArray + 10);

	intList_t::iterator intIterator = intList.begin();
	strList_t::iterator strIterator = strList.begin();
	fatList_t::iterator fatIterator = fatList.begin();
	EXPECT_TRUE(intList.size() == DATA_SIZE);
	EXPECT_TRUE(strList.size() == DATA_SIZE);
	EXPECT_TRUE(fatList.size() == DATA_SIZE);
	for (int i = 0; i < DATA_SIZE; ++i) {
		EXPECT_TRUE(*intIterator == intArray[i]);
		EXPECT_TRUE(*strIterator == strArray[i]);
		EXPECT_TRUE(*fatIterator == fatArray[i]);
		++intIterator;
		++strIterator;
		++fatIterator;
	}
#undef DATA_SIZE
}

#endif //SEQUENCE_CONTAINERS_TESTS_TPP
