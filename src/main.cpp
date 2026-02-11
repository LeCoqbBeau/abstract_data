
#include ".helper/ftdef.hpp"
#include ".never_included/utils.h"
#include ".helper/functional.hpp"

template <typename T = int>
struct Loud
{
	Loud() {}
	Loud(T CREF var) : var(var) { /* PRINT "Loud(" AND var AND ");" ENDL; */ }
	~Loud() { /*PRINT PRP "~Loud(" AND var AND ");" CENDL;*/ }
	void jobly() const { PRINT "what a jobly day " AND var ENDL; }
	operator T() const { return var; }
	bool operator == (Loud CREF l) const { return var == l.var; }
	bool operator < (Loud CREF l) const { return var < l.var; }
	friend std::ostream REF operator << (std::ostream REF os, Loud CREF l) { os << l.var; return os; }
	T var;
};


template <typename T>
struct LoudHasher : public ft::hash<T>
{
	ft::uint64_t operator()(T CREF x) const { return ft::hash<T>()(x); }
};

template <typename T>
void joblyContainer(T REF container) {
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		PRINT *it ENDL;
}


template <typename T>
void joblyHashmap(T REF container) {
	for (typename T::local_iterator it = container.begin(1); it != container.end(1); ++it)
		PRINT *it ENDL;
}


template <typename T>
void containerJobly(T REF container) {
	for (typename T::reverse_iterator it = container.rbegin(); it != container.rend(); ++it)
		it->jobly();
}

// #include <utility>
// #include <functional>
// #include <unordered_set>
#include ".helper/hashmap.hpp"


int main() {
	ft::allocator<Loud<> >			allocator;
	ft::internal::bucket<Loud<> >	test;

	test.insert(1, allocator);
	test.insert(2, allocator);
	test.insert(3, allocator);
	test.insert(4, allocator);
	test.insert(5, allocator);
	test.insert(6, allocator);

	joblyContainer(test);
	test.clear(allocator);
	// typedef int hashed_type;
	// typedef LoudHasher<hashed_type>::result_type hash_result;
	// LoudHasher<hashed_type> hasher;
	// std::vector<hash_result> results;
	// hash_result hashed = hasher(5089) % 100;
	// SHOWL(hashed);
	// results.reserve(100);
	// for (int i = 0; i < 100; ++i) {
	// 	hash_result toPush = hasher(5089) % 100;
	// 	results.push_back(toPush);
	// }
	// for (AUTO it = results.begin(); it != results.end(); ++it)
	// 	PRINT *it ENDL;
}

