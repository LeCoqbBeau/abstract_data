
#include ".helper/ftdef.hpp"
#include ".never_included/utils.h"

struct Loud
{
	Loud(int const i) : i(i) { /*PRINT "Loud(" AND i AND ");" ENDL;*/ }
	~Loud() { /*PRINT "~Loud(" AND i AND ");" ENDL;*/ }
	void jobly() const { PRINT "What a jobly day " AND i ENDL; }
	bool operator == (Loud CREF l) const { return i == l.i; }
	bool operator < (Loud CREF l) const { return i < l.i; }
	friend std::ostream REF operator << (std::ostream REF os, Loud CREF l) { os << l.i; return os; }
	int i;
};

template <typename T>
void joblyContainer(T CREF container) {
	for (__auto_type it = container.begin(); it != container.end(); ++it)
		it->jobly();
}

#include "bonus/matrix.hpp"

int main() {
	ft::matrix<Loud, 3, 3> mat(9, 1);

	joblyContainer(mat);
}

