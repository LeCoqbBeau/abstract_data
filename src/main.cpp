

#include <limits>
#include <list>

#include "utils.h"
#include "list.h"

int main() {
	ft::list<int> test;
	test.assign(0, 10);
	SHOWL(test.size());
	SHOWL(test.empty());
}
