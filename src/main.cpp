
#include "list.h"
#include <list>
#include "./listTests.tpp"

int main() {
	PRINT "std::list<int>" ENDL;
	benchmark(testLists<std::list<int> >);
	NEWL;
	PRINT "ft::list<int>" ENDL;
	benchmark(testLists<ft::list<int> >);

	return 0;
}

