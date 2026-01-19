
#include ".helper/ftdef.hpp"
#include ".never_included/utils.h"

struct Loud
{
	Loud(int const i = 0) : i(i) { /*PRINT "Loud(" AND i AND ");" ENDL;*/ }
	~Loud() { /*PRINT "~Loud(" AND i AND ");" ENDL;*/ }
	void jobly() const { PRINT "What a jobly day " AND i ENDL; }
	bool operator == (Loud CREF l) const { return i == l.i; }
	friend std::ostream REF operator << (std::ostream REF os, Loud CREF l) { os << l.i; return os; }
	int i;
};

template <typename T>
void joblyContainer(T CREF container) {
	for (__auto_type it = container.begin(); it != container.end(); ++it)
		it->jobly();
}

#include <vector>

int main() {
	std::vector<Loud> vector(10, 10);

	vector.insert(vector.end(), 15);
	joblyContainer(vector);
}

