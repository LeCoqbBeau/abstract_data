//
// Created by mscheman on 10/20/25.
//

#ifndef LIST_TESTS_TPP
# define LIST_TESTS_TPP

#include <algorithm>
#include <fstream>

#include "../include/.never_included/utils.h"

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

#define MORE_BENCHMARK true

#define REG_UNIT_TEST(test) TEMPLATE(class List) static void testList##test()

#if (MORE_BENCHMARK)
# define INVOKE_UNIT_TEST(test) PRINT PRP BOLD "Now testing lists " #test CENDL; benchmark(testList##test<List>)
#else
# define INVOKE_UNIT_TEST(test) PRINT PRP BOLD "Now testing lists " #test CENDL; testList##test<List>()
#endif

#define LIST_STATE(l) //(void)l; SHOWL(l.size()); if (!l.empty()) { SHOWL(l.front()); SHOWL(l.back()); }

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
	}
	NEWL;
	{
		PRINT YLW BOLD "const_iterator:" CENDL;
		typename List::const_iterator cit;
		for (cit = list.begin(); cit != list.end(); ++cit)
			PRINT *cit AND " - ";
		NEWL;
	}
	NEWL;
	{
		PRINT YLW BOLD "reverse_iterator:" CENDL;
		typename List::reverse_iterator rit;
		for (rit = list.rbegin(); rit != list.rend(); ++rit)
			PRINT *rit AND " - ";
		NEWL;
	}
	NEWL;
	{
		PRINT YLW BOLD "const_reverse_iterator:" CENDL;
		typename List::const_reverse_iterator crit;
		for (crit = list.rbegin(); crit != list.rend(); ++crit)
			PRINT *crit AND " - ";
		NEWL;
	}
	NEWL;
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
	// insert
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
	// erase
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
	// swap & resize
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

TEMPLATE_T bool isEven(T num) {
	return !(num % 2);
}

TEMPLATE_T bool isOdd(T num) {
	return (num % 2);
}

TEMPLATE_T bool isNotUnique(T curr, T prev) {
	return curr == prev;
}

TEMPLATE_T bool isGreater(T x, T y) {
	return x > y;
}
TEMPLATE_TU bool isSorted(T begin, T end, U Comp) {
	T isSorted = std::adjacent_find(begin, end, Comp);
	return isSorted == end;
}

REG_UNIT_TEST(Operations) {
	List list;
	// Splice
	{
		List otherList;
		{
			for (int i = 0; i < 9; ++i)
				list.push_back(i + 1);
			for (int i = 0; i < 9; ++i)
				otherList.push_back((i + 1) * 10);
			LIST_STATE(list);
			LIST_STATE(otherList);
			list.splice(list.begin(), otherList);
			LIST_STATE(list);
			LIST_STATE(otherList);
		}
		list.clear();
		otherList.clear();
		NEWL;
		{
			for (int i = 0; i < 9; ++i)
				list.push_back(i + 1);
			for (int i = 0; i < 9; ++i)
				otherList.push_back((i + 1) * 10);
			typename List::iterator it = otherList.begin();
			for (int i = 0; i < 5; ++i)
				++it;
			LIST_STATE(list);
			LIST_STATE(otherList);
			list.splice(list.begin(), otherList, it);
			LIST_STATE(list);
			LIST_STATE(otherList);
		}
		list.clear();
		otherList.clear();
		NEWL;
		{
			for (int i = 0; i < 9; ++i)
				list.push_back(i + 1);
			for (int i = 0; i < 9; ++i)
				otherList.push_back((i + 1) * 10);
			typename List::iterator it = otherList.begin();
			for (int i = 0; i < 5; ++i)
				++it;
			LIST_STATE(list);
			LIST_STATE(otherList);
			list.splice(list.begin(), otherList, otherList.begin(), it);
			LIST_STATE(list);
			LIST_STATE(otherList);
		}
	}
	list.clear();
	NEWL;
	// Remove
	{
		for (int i = 0; i < 9; ++i)
			list.push_back(i + 1);
		LIST_STATE(list);
		list.remove(1);
		LIST_STATE(list);
		list.remove(9);
		LIST_STATE(list);
		list.remove_if(isEven<typename List::value_type>);
		LIST_STATE(list);
		list.remove_if(isOdd<typename List::value_type>);
		LIST_STATE(list);
	}
	list.clear();
	NEWL;
	// Unique
	{
		for (int i = 0; i < 20; ++i)
			list.push_back(i/2 + 1);
		LIST_STATE(list);
		list.unique();
		LIST_STATE(list);
		list.clear();
		for (int i = 0; i < 20; ++i)
			list.push_back(i/2 + 1);
		list.unique(isNotUnique<typename List::value_type>);
	}
	list.clear();
	NEWL;
	// Merge
	{
		List otherList;
		for (int i = 0; i < 9; ++i)
			list.push_back(i + 1);
		for (int i = 0; i < 9; ++i)
			otherList.push_back(i/2 - 2);
		LIST_STATE(list);
		LIST_STATE(otherList);
		list.merge(otherList);
		LIST_STATE(list);
		LIST_STATE(otherList);
		list.clear();
		for (int i = 0; i < 9; ++i)
			otherList.push_back(i/2 - 2);
		list.merge(otherList, isGreater<typename List::value_type>);
		LIST_STATE(list);
		LIST_STATE(otherList);
	}
	list.clear();
	NEWL;
	// Sort & Reverse
	{
		std::ifstream input;
		input.open("numbers.rand");
		if (!input.is_open()) {
			PRINT RED BOLD "Failed to open file :(" ENDL;
			return;
		}
		while (!input.eof()) {
			str buffer;
			std::getline(input, buffer);
			list.push_back(std::strtol(buffer.c_str(), NULL, 10));
		}
		input.close();
		LIST_STATE(list);
		list.sort();
		LIST_STATE(list);
		bool sorted = isSorted(list.begin(), list.end(), std::greater<typename List::value_type>());
		SHOWL(sorted);
		list.clear();
		input.open("numbers.rand");
		if (!input.is_open()) {
			PRINT RED BOLD "Failed to open file :(" ENDL;
			return;
		}
		while (!input.eof()) {
			str buffer;
			std::getline(input, buffer);
			list.push_back(std::strtol(buffer.c_str(), NULL, 10));
		}
		input.close();
		list.sort(std::greater<typename List::value_type>());
		LIST_STATE(list);
		sorted = isSorted(list.begin(), list.end(), std::less<typename List::value_type>());
		SHOWL(sorted);
		list.reverse();
		LIST_STATE(list);
		sorted = isSorted(list.begin(), list.end(), std::less<typename List::value_type>());
		SHOWL(sorted);
		sorted = isSorted(list.begin(), list.end(), std::greater<typename List::value_type>());
		SHOWL(sorted);
		list.clear();
	}
}

TEMPLATE(class List) void testLists() {
	INVOKE_UNIT_TEST(Iterators);
	INVOKE_UNIT_TEST(Capacity);
	INVOKE_UNIT_TEST(ElementAccess);
	INVOKE_UNIT_TEST(Modifiers);
	INVOKE_UNIT_TEST(Operations);
}

#undef LIST_STATE
#undef REG_UNIT_TEST
#undef INVOKE_UNIT_TEST

#endif