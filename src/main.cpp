
#include <deque>
// #include "deque.hpp"

#include ".helper/ftdef.hpp"
#include ".never_included/utils.h"
// #include "list.hpp"
// #include <list>
// #include "./listTests.tpp"

struct Loud
{
	Loud(int const i = 0) : i(i) { PRINT "Loud(" AND i AND ");	" ENDL; }
	~Loud() { PRINT "~Loud(" AND i AND ");" ENDL; }
	void jobly() const { PRINT "What a jobly day " AND i ENDL; }
	friend std::ostream REF operator << (std::ostream REF os, Loud CREF l) { os << l.i; return os; }
	int i;
};

int main() {
	// ft::deque<Loud> deque1(300, 10);
	// // SHOWL(&deque1);
	// ft::deque<Loud> deque2(deque1);
	// // SHOWL(&deque2);
	// deque2 = deque1;
	// ft::deque<Loud> deque;
	// for (int i = 0; i < 10; ++i)
	// 	deque.push_back(i + 1);
	// for (int i = 0; i < 10; ++i)
	// 	SHOWL(deque.at(i));
	std::deque<Loud> deque;

	deque.push_back(1);
	deque.push_back(2);
	deque.push_back(3);

	// deque.insert(deque.begin(), 0);
	deque.insert(deque.end() - 1, 4);

	for (std::deque<Loud>::iterator it = deque.begin(); it != deque.end(); ++it)
		SHOWL(*it);
}
