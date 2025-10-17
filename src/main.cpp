
#include <iterator>
#include <stdint.h>
#include <limits>
#include <list>

#include "helper/utils.h"
#include "list.h"

#include "helper/iterator.h"

TEMPLATE(class list) static void testList();

#include <cstdlib>
#include <ctime>
int main() {
	std::srand(std::time(NULL));
	PRINT CYN BOLD "std::list" CENDL;
	testList<std::list<int> >();
	NEWL;
	PRINT GRN BOLD "ft::list" CENDL;
	testList<ft::list<int> >();
	NEWL;
}

// #include <vector>
// std::vector<int> job(static_cast<size_t>(10), 25);

TEMPLATE_T bool isUnique(T CREF curr, T CREF prev) {
	return curr == prev;
}

TEMPLATE(class list) static void testList() {
	list listVar;
	list otherList;
	for (int i = 0; i < 3; ++i) {
		listVar.push_back(i * 9); // std::rand() % 201 - 100
		otherList.push_back((1 + i) * 10);
	}
	listVar.merge(otherList);
	for (typename list::iterator it2 = listVar.begin(); it2 != listVar.end(); ++it2)
		SHOWL(*it2);
	SHOWL(listVar.size());
	SHOWL(otherList.size());
}