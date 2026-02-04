
#include <list>

#include ".helper/ftdef.hpp"
#include ".never_included/utils.h"
#include ".helper/binary_trees.hpp"
#include <set>
#include <map>

#include "set.hpp"
#include "map.hpp"


struct Loud
{
	Loud(int const i) : i(i) { /*PRINT "Loud(" AND i AND ");" ENDL;*/ }
	~Loud() { /* PRINT PRP "~Loud(" AND i AND ");" CENDL; */ }
	void jobly() const { PRINT "what a jobly day " AND i ENDL; }
	bool operator == (Loud CREF l) const { return i == l.i; }
	bool operator < (Loud CREF l) const { return i < l.i; }
	friend std::ostream REF operator << (std::ostream REF os, Loud CREF l) { os << l.i; return os; }
	int i;
};

template <typename T>
void joblyContainer(T REF container) {
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		it->jobly();
}


template <typename T>
void joblyMap(T REF container) {
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		it->second.jobly();
}


template <typename T>
void containerJobly(T REF container) {
	for (typename T::reverse_iterator it = container.rbegin(); it != container.rend(); ++it)
		it->jobly();
}

template <typename Map>
void init_map(Map REF set) {

}

int main() {

}

