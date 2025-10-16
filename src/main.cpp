
#include <stdint.h>
#include <limits>
#include <list>

#include "utils.h"
#include "list.h"

#include "iterator.h"

#include <stdexcept>

TEMPLATE(class list) static void testList();

int main() {
	PRINT CYN BOLD "std::list" CENDL;
	testList<std::list<int> >();
	NEWL;
	PRINT GRN BOLD "ft::list" CENDL;
	testList<ft::list<int> >();
	NEWL;
}

#include <vector>
// std::vector<int> job(static_cast<size_t>(10), 25);

TEMPLATE(class list) static void testList() {
	list listVar;
	list otherList;
	for (int i = 0; i < 10; ++i) {
		listVar.push_back(i);
		otherList.push_back((1 + i) * 10);
	}
	listVar.splice(listVar.begin(), otherList, ++otherList.begin(), otherList.end());
	for (typename list::iterator it2 = listVar.begin(); it2 != listVar.end(); ++it2)
		SHOWL(*it2);
	SHOWL(listVar.size());
	SHOWL(otherList.size());
}