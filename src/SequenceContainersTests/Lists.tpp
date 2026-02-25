//
// Created by mscheman on 2/16/26.
//

#ifndef SCT_LIST_TPP
#define SCT_LIST_TPP


template <typename Container>
class sctListsTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		sctListsTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


// Why must you look inside me, don't
namespace SCT {
struct stableLess
{
	template <typename T>
	bool operator() (std::pair<T, int> CREF lhs, std::pair<T, int> CREF rhs) const { return lhs.first < rhs.first; }
};
struct stableGreater
{
	template <typename T>
	bool operator() (std::pair<T, int> CREF lhs, std::pair<T, int> CREF rhs) const { return lhs.first > rhs.first; }
};
struct stableCheck
{
	template <typename T>
	bool operator() (std::pair<T, int> CREF lhs, std::pair<T, int> CREF rhs) const
	{
		if (lhs.first == rhs.first)
			return lhs.second > rhs.second;
		return false;
	}
};
}
// Look again pwease :3


TYPED_TEST_CASE_P(sctListsTests);


TYPED_TEST_P(sctListsTests, SpliceEntire)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;
	TypeParam										otherList;

	// Splice empty :D
	c.splice(c.end(), otherList);
	EXPECT_EQ(c, cCopy);
	// Splice nonempty
	otherList = TypeParam(array() + ARRAY_TINY, array() + ARRAY_SMOL);
	c.splice(c.end(), otherList);
	EXPECT_TRUE(otherList.empty());
	EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_SMOL));
}


TYPED_TEST_P(sctListsTests, SpliceOne)
{
	typedef typename TypeParam::iterator			iterator;

	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;
	TypeParam										otherList(array() + ARRAY_TINY, array() + ARRAY_SMOL);

	// Normal Splice :p
	for (int i = 1; i <= ARRAY_SMOL - ARRAY_TINY; ++i) {
		c.splice(c.end(), otherList, otherList.begin());
		EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_TINY + i));
		EXPECT_EQ(otherList, TypeParam(array() + ARRAY_TINY + i, array() + ARRAY_SMOL));
	}
	EXPECT_EQ(otherList.empty(), true);
	// Self Splice :d
	for (int i = 0; i < ARRAY_SMOL - 1; ++i) {
		iterator dest = std::next(c.begin() , i);
		c.splice(dest, c, std::next(c.end(), -1));
	}
	TypeParam helperList(array(), array() + ARRAY_SMOL);
	otherList = TypeParam(helperList.rbegin(), helperList.rend()); // reverse copy without doing any shenanigans :)
	EXPECT_EQ(c, otherList);
}


TYPED_TEST_P(sctListsTests, SpliceRange)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c = this->container;
	TypeParam										cCopy;
	TypeParam										otherList(array() + ARRAY_TINY, array() + ARRAY_SMOL);

	// Normal single splice :d
	for (int i = 1; i <= ARRAY_SMOL - ARRAY_TINY; ++i) {
		c.splice(c.end(), otherList, otherList.begin(), std::next(otherList.begin()));
		EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_TINY + i));
		EXPECT_EQ(otherList, TypeParam(array() + ARRAY_TINY + i, array() + ARRAY_SMOL));
	}
	EXPECT_EQ(otherList.empty(), true);
	// Whole range splice
	c = TypeParam(array(), array() + ARRAY_TINY);
	otherList = TypeParam(array() + ARRAY_TINY, array() + ARRAY_SMOL);
	c.splice(c.end(), otherList, otherList.begin(), otherList.end());
	EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_SMOL));
	EXPECT_EQ(otherList.empty(), true);
	// Partial range splice finally !
	c = TypeParam(array(), array() + ARRAY_TINY);
	otherList = TypeParam(array() + ARRAY_TINY, array() + ARRAY_SMOL);
	c.splice(c.end(), otherList, otherList.begin(), std::next(otherList.begin(), ARRAY_TINY));
	EXPECT_EQ(c, TypeParam(array(), array() + 2 * ARRAY_TINY));
	EXPECT_EQ(otherList, TypeParam(array() + 2 * ARRAY_TINY, array() + ARRAY_SMOL));

	// Self splicing time :D
	// Single self splice
	c = TypeParam(array(), array() + ARRAY_SMOL);
	c.splice(c.end(), c, c.begin(), std::next(c.begin()));
	EXPECT_TRUE(std::equal(array() + 1, array() + ARRAY_SMOL, c.begin()));
	EXPECT_EQ(c.back(), array[0]);
	// Whole range splice!
	cCopy = c;
	c.splice(c.end(), c, c.begin(), c.end());
	EXPECT_EQ(c, cCopy);
	// Partial range splice finally!
	c.splice(c.end(), c, c.begin(), std::next(c.begin(), 19));
	EXPECT_TRUE(std::equal(array() + 20, array() + ARRAY_SMOL, c.begin()));
	EXPECT_TRUE(std::equal(array(), array() + 20, std::next(c.end(), -20)));
}


TYPED_TEST_P(sctListsTests, RemoveIf)
{
	typedef typename TypeParam::size_type			size_type;
	arrayGenerator<typename TypeParam::value_type>	array;
	arrayGenerator<int>								intGen;
	arrayGenerator<str>								strGen;

	TypeParam REF c = this->container;
	TypeParam cCopy = c;

	c.remove_if(alwaysFalse());
	EXPECT_EQ(c, cCopy);
	c.remove_if(alwaysTrue());
	EXPECT_TRUE(c.empty());
	c = cCopy;
	c.remove_if(isOdd());
	EXPECT_EQ(c.size(), size_type(5));
	c = cCopy;
	c.remove_if(isEven());
	EXPECT_EQ(c.size(), size_type(5));
	c = cCopy;
	c.remove_if(isEqual(intGen[ARRAY_SMOL], strGen[ARRAY_SMOL])); // this is equal to `c.remove(value_type CREF value)`
	EXPECT_EQ(c, cCopy);
	c.remove_if(isEqual(intGen[0], strGen[0])); // this is equal to `c.remove(value_type CREF value)`
	EXPECT_EQ(c.size(), size_type(9));
	EXPECT_TRUE(std::find(c.begin(), c.end(), array[0]) == c.end());
}


TYPED_TEST_P(sctListsTests, Unique)
{
	typedef typename TypeParam::size_type			size_type;

	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;

	// Basic tests
	c.unique(); // is always false
	EXPECT_EQ(c, cCopy);
	c.unique(alwaysTrue());
	EXPECT_EQ(c.size(), size_type(1));
	// Test without custom predicate
	c.clear();
	for (int i = 0; i < ARRAY_TINY * 2; ++i)
		c.push_back(array[i / 2]); // this will push_back twice every numbers
	ASSERT_EQ(c.size(), size_type(ARRAY_TINY * 2));
	c.unique();
	EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_TINY));
	// Test with custom predicate
	c.clear();
	for (int i = 0; i < ARRAY_TINY * 2; ++i)
		c.push_back(array[i / 2]); // this will push_back twice every numbers
	ASSERT_EQ(c.size(), size_type(ARRAY_TINY * 2));
	c.unique(areThirdOrFourth());
	// Ugly but I don't know how to code the pattern
	typename TypeParam::iterator it = c.begin();
	ASSERT_EQ(c.size(), size_type(12));
	EXPECT_EQ(*it, array[0]);	// idx: 0
	EXPECT_EQ(*++it, array[1]);	// idx: 1
	EXPECT_EQ(*++it, array[1]);	// idx: 2
	EXPECT_EQ(*++it, array[2]);	// idx: 3
	EXPECT_EQ(*++it, array[2]);	// idx: 4
	EXPECT_EQ(*++it, array[3]);	// idx: 5
	EXPECT_EQ(*++it, array[5]);	// idx: 6
	EXPECT_EQ(*++it, array[5]);	// idx: 7
	EXPECT_EQ(*++it, array[6]);	// idx: 8
	EXPECT_EQ(*++it, array[7]);	// idx: 9
	EXPECT_EQ(*++it, array[7]);	// idx: 10
	EXPECT_EQ(*++it, array[8]);	// idx: 11
}


TYPED_TEST_P(sctListsTests, Merge)
{
	arrayGenerator<typename TypeParam::value_type>	array;

	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;
	TypeParam										even;
	TypeParam										odd;

	// Merge from empty two empty
	even.merge(odd);
	EXPECT_TRUE(even.empty());
	EXPECT_TRUE(odd.empty());
	// Merge from empty
	even.merge(c);
	EXPECT_EQ(even, cCopy);
	EXPECT_TRUE(c.empty());
	// Merge with empty
	even.merge(odd);
	EXPECT_EQ(even, cCopy);
	EXPECT_TRUE(odd.empty());
	// Normal merge
	even.clear();
	for (int i = 0; i < ARRAY_TINY / 2; ++i) {
		even.push_back(array[i * 2]);
		odd.push_back(array[i * 2 + 1]);
	}
	even.merge(odd);
	EXPECT_EQ(even, cCopy);
	EXPECT_TRUE(odd.empty());
}


TYPED_TEST_P(sctListsTests, MergePredicate)
{
	std::greater<typename TypeParam::value_type>	greater;
	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;
	TypeParam										even;
	TypeParam										odd;

	// Merge from empty two empty
	even.merge(odd, greater);
	EXPECT_TRUE(even.empty());
	EXPECT_TRUE(odd.empty());
	// Merge from empty
	even.merge(c, greater);
	EXPECT_EQ(even, cCopy);
	EXPECT_TRUE(c.empty());
	// Merge with empty
	even.merge(odd, greater);
	EXPECT_EQ(even, cCopy);
	EXPECT_TRUE(odd.empty());
	// Normal merge
	even.clear();
	int i = 0;
	for (typename TypeParam::reverse_iterator it = cCopy.rbegin(); it != cCopy.rend(); ++it) {
		if (i % 2 == 0)
			even.push_back(*it);
		else
			odd.push_back(*it);
		++i;
	}
	even.merge(odd, greater);
	EXPECT_TRUE(std::equal(cCopy.rbegin(), cCopy.rend(), even.begin()));
	EXPECT_TRUE(odd.empty());
}


TYPED_TEST_P(sctListsTests, Sort)
{
	typedef typename TypeParam::value_type	value_type;
	TypeParam								toSort;
	intConvertor<value_type>				convert;

	srand(69420);
	for (int i = 0; i < 20000; ++i)
		toSort.push_back(convert(rand()));
	ASSERT_EQ(toSort.size(), typename TypeParam::size_type(20000));
	EXPECT_FALSE(isSorted::check(toSort, std::greater<value_type>()));
	toSort.sort();
	EXPECT_TRUE(isSorted::check(toSort, std::greater<value_type>()));
}


TYPED_TEST_P(sctListsTests, SortStability)
{
	typedef typename TypeParam::value_type					value_type;
	typedef std::pair<value_type, int>						stable_pair_type;
	typedef typename ns::list<stable_pair_type>::iterator	iterator;

	// Actual tests
	ns::list<stable_pair_type>				toSort;
	intConvertor<value_type>				convert;

	srand(69420);
	for (int i = 0; i < 20000; ++i)
		toSort.push_back(std::make_pair(convert(rand() % 10000), i)); // so we have some duplicates
	ASSERT_EQ(toSort.size(), typename TypeParam::size_type(20000));

	EXPECT_FALSE(isSorted::check(toSort, SCT::stableGreater()));
	toSort.sort(SCT::stableLess());
	EXPECT_TRUE(isSorted::check(toSort, SCT::stableGreater()));
	iterator	violation = std::adjacent_find(toSort.begin(), toSort.end(), SCT::stableCheck());
	EXPECT_TRUE(violation == toSort.end()) << "Sort isn't stable";

}


TYPED_TEST_P(sctListsTests, Reverse)
{
	TypeParam REF	c = this->container;
	TypeParam		cCopy = c;

	// Normal reverse
	c.reverse();
	EXPECT_TRUE(std::equal(c.begin(), c.end(), cCopy.rbegin()));
	// Reverse from empty
	c.clear();
	ASSERT_TRUE(c.empty());
	c.reverse();
	EXPECT_TRUE(c.empty());
}


REGISTER_TYPED_TEST_CASE_P(
	sctListsTests,
	SpliceEntire,
	SpliceOne,
	SpliceRange,
	RemoveIf,
	Unique,
	Merge,
	MergePredicate,
	Sort,
	SortStability, // Also test custom predicate :D
	Reverse
);


INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	sctListsTests,
	testList_type
);

#endif //SCT_LIST_TPP