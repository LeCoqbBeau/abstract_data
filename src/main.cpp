
#include ".helper/ftdef.hpp"
#include ".helper/rbtree.hpp"
#include ".never_included/utils.h"

struct Loud
{
	Loud(int const i = 0) : i(i) { /*PRINT "Loud(" AND i AND ");" ENDL;*/ }
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

void joblyRBT(ft::internal::rbtree_node<Loud> const* node, int depth = 0) {
	if (!node)
		return;
	node->value.jobly();
	if (node->next[LEFT]) {
		for (int i = 0; i < depth; ++i)
			PRINT TAB;
		PRINT "Left: ";
		joblyRBT(node->next[LEFT], depth + 1);
	}
	if (node->next[LEFT]) {
		for (int i = 0; i < depth; ++i)
			PRINT TAB;
		PRINT "Right: ";
		joblyRBT(node->next[RIGHT], depth + 1);
	}
}


int main() {
	typedef ft::internal::rbtree_node<Loud> node;

	node seventeen(17);

	node fifty(50, &seventeen);
	seventeen.next[RIGHT] = &fifty;

	node a(1, &seventeen);
	seventeen.next[LEFT] = &a;

	node b(2, &fifty);
	fifty.next[LEFT] = &b;
	node c(3, &fifty);
	fifty.next[RIGHT] = &c;

	node *root = &seventeen;
	joblyRBT(root);
	root = root->rotate(LEFT);
	joblyRBT(root);
}

