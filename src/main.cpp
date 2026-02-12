
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
struct LoudHasher : ft::unary_function<Loud<T>, ft::uint64_t>
{
	ft::uint64_t operator()(Loud<T> CREF x) const { return ft::hash<T>()(x.var); }
};

template <typename T>
void joblyContainer(T REF container) {
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		PRINT *it ENDL;
}

template <typename T>
void containerJobly(T REF container) {
	for (typename T::reverse_iterator it = container.rbegin(); it != container.rend(); ++it)
		it->jobly();
}

#include ".helper/hashmap.hpp"

typedef int	type;
typedef ft::internal::hashmap<Loud<type>, LoudHasher<type> > hashmap;

void containerHashmap(hashmap CREF hashmap) {
	typedef Loud<type>							T;
	typedef ft::internal::bucket<T>				bucket_type;
	typedef ft::internal::_doublyLinkedListBase base_type;

	bucket_type *buckets = hashmap.begin()._bucket;
	ft::size_t size = hashmap.begin()._bucket_count;
	for (ft::size_t i = 0; i < size; ++i) {
		PRINT "hashmap[";
		RPRINT(2) i;
		PRINT "]: { ";
		size_t count;
		count = 0;
		for (base_type *node = buckets[i]._sentinel.next(); node != &buckets[i]._sentinel; node = node->next()) {
			PRINT FT_DLLNODE(node)->value AND " > ";
			++count;
		}
		PRINT "} ";
		if (count)
			PRINT "has " AND count AND " elements";
		NEWL;
	}
}

// #include <utility>
// #include <functional>
// #include <unordered_set>


int main() {

	hashmap lookup;
	for (int i = 0; i < 63; ++i)
		lookup.insert(1);

	// SHOWL(lookup.size());
	// SHOWL(ft::distance(lookup.begin(), lookup.end()));
	// joblyContainer(lookup);
	containerHashmap(lookup);
}

