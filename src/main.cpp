
#include ".helper/ftdef.hpp"
#include ".never_included/utils.h"

struct Loud
{
	Loud(int const i) : i(i) { /*PRINT "Loud(" AND i AND ");" ENDL;*/ }
	~Loud() { /* PRINT PRP "~Loud(" AND i AND ");" CENDL; */ }
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

#include ".helper/binary_trees.hpp"
typedef ft::internal::rb_tree<Loud> tree_type;
typedef tree_type::node_type* node_type;

void joblyBST(tree_type REF tree) {
	for (__auto_type it = tree.begin(); it != tree.end(); it = (node_type)it->nextNode()) {
		SHOWL(it);
		it->value.jobly();
	}
}

void joblyRBTPrint(node_type node, uint depth = 1) {
	if (!node)
		return;
	PRINT (node->color == RBT_RED ? RED : CYN) AND node->value CENDL;
	if (static_cast<node_type>(node->left())) {
		for (uint i = 0; i < depth; ++i)
			PRINT TAB;
		PRINT "L: ";
		joblyRBTPrint(static_cast<node_type>(node->left()), depth + 1);
	}
	if (static_cast<node_type>(node->right())) {
		for (uint i = 0; i < depth; ++i)
			PRINT TAB;
		PRINT "R: ";
		joblyRBTPrint(static_cast<node_type>(node->right()), depth + 1);
	}
}

int main() {
	tree_type tree;

	tree.insert(8);
	tree.insert(2);
	tree.insert(5);
	tree.insert(4);
	tree.insert(6);
	tree.insert(1);
	tree.insert(64);
	tree.insert(32);
	tree.insert(16);
	tree.insert(128);


	// SHOWL(&tree._sentinel);
	joblyRBTPrint(tree._root);
	tree.remove(8);
	joblyRBTPrint(tree._root);

}

