
#include <deque>
#include "deque.hpp"

#include ".helper/ftdef.hpp"
#include ".never_included/utils.h"
// #include "list.hpp"
// #include <list>
// #include "./listTests.tpp"

struct Loud
{
	Loud(int const i) : i(i) { PRINT "Loud(" AND i AND ");	" ENDL; }
	~Loud() { PRINT "~Loud(" AND i AND ");" ENDL; }
	void jobly() const { PRINT "What a jobly day " AND i ENDL; }
	int i;
};

int main() {
	// PRINT CYN "std::list" CENDL;
	// benchmark(testLists<std::list<int> >);
	// PRINT GRN "ft::list" CENDL;
	// benchmark(testLists<ft::list<int> >);

#define NAMESPACE ft
	NAMESPACE::deque<Loud> deque(17, 1);
	for (NAMESPACE::deque<Loud>::const_iterator it = deque.begin(); it != deque.end(); ++it)
		it->jobly();
}
