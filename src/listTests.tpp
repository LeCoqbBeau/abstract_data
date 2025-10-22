//
// Created by mscheman on 10/20/25.
//

#ifndef LIST_TESTS_TPP
# define LIST_TESTS_TPP

#include ".helper/utils.h"

TEMPLATE(class func) void benchmark(func f) {
	clock_t const start = clock();
	f();
	clock_t const end = clock();
	double elapsed = static_cast<double>(end - start) / static_cast<double>(CLOCKS_PER_SEC);
	PRINT RED BOLD "Took: ";
	if (elapsed > 1)
		PRINT elapsed AND " ";
	else if (elapsed * 1e3 > 1)
		PRINT elapsed * 1e3 AND " milli";
	else if (elapsed * 1e6 > 1)
		PRINT elapsed * 1e6 AND " micro";
	else
		PRINT elapsed * 1e9 AND " nano";
	PRINT "seconds " CENDL;
	elapsed *= 20;
	PRINT ITAL "(20x more is ";
	if (elapsed > 1)
		PRINT elapsed AND " ";
	else if (elapsed * 1e3 > 1)
		PRINT elapsed * 1e3 AND " milli";
	else if (elapsed * 1e6 > 1)
		PRINT elapsed * 1e6 AND " micro";
	else
		PRINT elapsed * 1e9 AND " nano";
	PRINT "seconds)" ENDL ENDL;
}

#define REG_UNIT_TEST(test) TEMPLATE(class List) static void testList##test()
#define INVOKE_UNIT_TEST(test) PRINT PRP BOLD "Now testing lists " #test CENDL; benchmark(testList##test<List>)

#define LIST_STATE(l) SHOWL(l.size()); SHOWL(l.front()); SHOWL(l.back())

REG_UNIT_TEST(Iterators) {
	List list;
	for (int i = 0; i < 5; ++i)
		list.push_back(1 + i);
	{
		PRINT YLW BOLD "iterator:" CENDL;
		typename List::iterator it;
		for (it = list.begin(); it != list.end(); ++it)
			PRINT *it AND " - ";
		NEWL;
		it = list.begin();
		for (int i = 0; i < 10; ++i) {
			PRINT *it AND " - ";
			++it;
		}
	}
	NEWL;
	{
		PRINT YLW BOLD "const_iterator:" CENDL;
		typename List::const_iterator cit;
		for (cit = list.begin(); cit != list.end(); ++cit)
			PRINT *cit AND " - ";
		NEWL;
		cit = list.begin();
		for (int i = 0; i < 10; ++i) {
			PRINT *cit AND " - ";
			++cit;
		}
	}
	NEWL;
	{
		PRINT YLW BOLD "reverse_iterator:" CENDL;
		typename List::reverse_iterator rit;
		for (rit = list.rbegin(); rit != list.rend(); ++rit)
			PRINT *rit AND " - ";
		NEWL;
		rit = list.rbegin();
		for (int i = 0; i < 10; ++i) {
			PRINT *rit AND " - ";
			++rit;
		}
	}
	NEWL;
	{
		PRINT YLW BOLD "const_reverse_iterator:" CENDL;
		typename List::const_reverse_iterator crit;
		for (crit = list.rbegin(); crit != list.rend(); ++crit)
			PRINT *crit AND " - ";
		NEWL;
		crit = list.rbegin();
		for (int i = 0; i < 10; ++i) {
			PRINT *crit AND " - ";
			++crit;
		}
	}
}

REG_UNIT_TEST(Capacity) {
	List list;
	{
		PRINT YLW "empty(): " CENDL;
		PRINT (list.empty() ? "empty" : "not empty") ENDL;
		list.push_back(10);
		PRINT (list.empty() ? "empty" : "not empty") ENDL;
		list.pop_back();
		PRINT (list.empty() ? "empty" : "not empty") ENDL;
	}
	list.clear();
	NEWL;
	{
		PRINT YLW "size(): " CENDL;
		PRINT "size: " AND list.size() ENDL;
		list.push_back(10);
		PRINT "size: " AND list.size() ENDL;
		list.assign(25000, -1);
		PRINT "size: " AND list.size() ENDL;
	}
	list.clear();
	NEWL;
	{
		PRINT YLW "max_size(): " CENDL;
		PRINT "max_size: " AND list.max_size() ENDL;
		list.push_back(10);
		PRINT "max_size: " AND list.max_size() ENDL;
		list.assign(25000, -1);
		PRINT "max_size: " AND list.max_size() ENDL;
	}
}

REG_UNIT_TEST(ElementAccess) {
	List list;
	for (int i = 0; i < 31; ++i) {
		if (i % 3 == 0) list.push_back(i);
		else if (i % 3 == 1) (i % 2 ? list.front() = list.front() * -1 : list.back() = list.back() * -1);
		else list.push_front(i);
		PRINT i AND ": " TAB;
		RPRINT(3) list.front(); PRINT " <=> "; RPRINT(3) list.back() ENDL;
	}
}

REG_UNIT_TEST(Modifiers) {
	List list;
	// assign
	{
		List otherList(52, 86);
		{
			List copy(otherList);
			LIST_STATE(copy);
		}
		{
			list.assign(25, 68);
			LIST_STATE(list);
		}
		{
			list.assign(otherList.begin(), otherList.end());
			LIST_STATE(list);
		}
	}
	list.clear();
	NEWL;
	// push/pop front/back
	{
		{
			for (int i = 0; i < 20; ++i) {
				list.push_back(i * 10);
				if (!(i % 2)) list.pop_front();
			}
			LIST_STATE(list);
		}
		list.clear();
		{
			for (int i = 0; i < 20; ++i) {
				list.push_front(-i * 10);
				if (!(i % 2)) list.pop_back();
			}
			LIST_STATE(list);
		}
	}
	list.clear();
	NEWL;
	{
		typename List::iterator it = list.begin();
		list.insert(it, 10, 50);
		LIST_STATE(list);
		for (int i = 0; i < 200; ++i)
			list.insert(it, 30);
		LIST_STATE(list);
		for (int i = 0; i < 100; ++i)
			++it;
		list.insert(list.end(), list.begin(), it);
		LIST_STATE(list);
	}
	list.clear();
	NEWL;
	{
		for (int i = 0; i < 10; ++i)
			list.push_back(i + 1);
		LIST_STATE(list);
		list.erase(list.begin());
		LIST_STATE(list);
		list.erase(--list.end());
		LIST_STATE(list);
		for (int i = 0; i < 92; ++i)
			list.push_back(10 + i);
		LIST_STATE(list);
		typename List::iterator it = list.begin();
		for (int i = 0; i < 50; ++i)
			++it;
		list.erase(it, list.end());
		LIST_STATE(list);
		list.erase(list.begin(), list.end());
		LIST_STATE(list);
	}
	// no list.clear() because we did list.erase(beg..end);
	NEWL;
	{
		list.assign(68, 86);
		List otherList(86, 68);
		LIST_STATE(list);
		LIST_STATE(otherList);
		list.swap(otherList);
		LIST_STATE(list);
		LIST_STATE(otherList);
		list.resize(68);
		LIST_STATE(list);
		LIST_STATE(otherList);
		list.resize(86);
		LIST_STATE(list);
		LIST_STATE(otherList);
	}
}

TEMPLATE(class List) void testLists() {
	// INVOKE_UNIT_TEST(Iterators);
	// INVOKE_UNIT_TEST(Capacity);
	// INVOKE_UNIT_TEST(ElementAccess);
	INVOKE_UNIT_TEST(Modifiers);

}

#undef LIST_STATE
#undef REG_UNIT_TEST
#undef INVOKE_UNIT_TEST

#endif