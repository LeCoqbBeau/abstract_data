
#include "list.h"
#include <list>
#include ".helper/utils.h"

#include "./listTests.tpp"

int main() {
	PRINT GRN "ft::list" CENDL;
	testLists<ft::list<int> >();
	PRINT CYN "std::list" CENDL;
	testLists<std::list<int> >();
}

