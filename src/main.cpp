
#include ".helper/ftdef.hpp"
#include ".never_included/utils.h"
#include ".helper/binary_trees.hpp"
#include <cctype>

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
void joblyContainer(T CREF container) {
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		it->jobly();
}

typedef ft::internal::rb_tree<Loud> tree_type;
typedef tree_type::node_type* node_type;
typedef tree_type::base_type* base_type;

void joblyBST(tree_type REF tree) {
	for (node_type it = tree.begin(); it; it = (node_type)it->nextNode()) {
		if (it)
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


bool isValidBST(node_type node) {
	if (!node)
		return true;
	bool validLeft = true;
	if (node->left()) {
		if (node->comp(node->value, static_cast<node_type>((node->left()))->value))
			return false;
		validLeft = isValidBST(static_cast<node_type>(node->left()));
	}
	bool validRight = true;
	if (node->right()) {
		if (node->comp(static_cast<node_type>((node->right()))->value, node->value))
			return false;
		validRight = isValidBST(static_cast<node_type>(node->right()));
	}
	return validLeft && validRight;
}

bool areRedChildrenBlack(base_type node) {
	if (!node)
		return true;
	bool validLeft = true;
	if (node->left()) {
		if (node->color == RBT_RED)
			if (node->left()->color == RBT_RED)
				return false;
		validLeft = areRedChildrenBlack(node->left());
	}
	bool validRight = true;
	if (node->right()) {
		if (node->color == RBT_RED)
			if (node->right()->color == RBT_RED)
				return false;
		validRight = areRedChildrenBlack(node->right());
	}
	return validLeft && validRight;
}

int getBlackHeight(base_type node) {
	if (!node)
		return 1;
	int const leftBH = getBlackHeight(node->left());
	int const rightBH = getBlackHeight(node->right());
	if (leftBH != rightBH || leftBH == -1)
		return -1;
	return leftBH + (node->color == RBT_BLACK);
}

bool checkBlackHeight(base_type node) {
	return getBlackHeight(node) != -1;
}

bool isValidRBT(tree_type REF tree) {
	bool isBST = isValidBST(tree._root);
	bool validRedChild = areRedChildrenBlack(tree._root);
	bool validBlackHeight = checkBlackHeight(tree._root);
	SHOWL(isBST);
	SHOWL(validRedChild);
	SHOWL(validBlackHeight);
	return isBST && validRedChild && validBlackHeight;
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
	SHOWL(isValidRBT(tree));
	tree.remove(8);
	SHOWL(isValidRBT(tree));
	tree.remove(2);
	SHOWL(isValidRBT(tree));
	tree.remove(5);
	SHOWL(isValidRBT(tree));
	tree.remove(4);
	SHOWL(isValidRBT(tree));
	tree.remove(6);
	SHOWL(isValidRBT(tree));
	tree.remove(1);
	SHOWL(isValidRBT(tree));
	tree.remove(64);
	SHOWL(isValidRBT(tree));
	tree.remove(32);
	SHOWL(isValidRBT(tree));
	tree.remove(16);
	SHOWL(isValidRBT(tree));
	tree.remove(128);
	SHOWL(isValidRBT(tree));
	joblyRBTPrint(tree._root);
}

