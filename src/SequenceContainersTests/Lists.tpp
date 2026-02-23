//
// Created by mscheman on 2/16/26.
//

#ifndef SCT_LIST_TPP
#define SCT_LIST_TPP
#include "../Generator.hpp"


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
	typedef typename TypeParam::iterator	iterator;

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
	EXPECT_TRUE(std::equal(array() + 1, array + ARRAY_SMOL, c.begin()));
	EXPECT_EQ(c.back(), array[0]);
	// Whole range splice!
	cCopy = c;
	c.splice(c.end(), c, c.begin(), c.end());
	EXPECT_EQ(c, cCopy);
	// Partial range splice finally!
	c.splice(c.end(), c, c.begin(), std::next(c.begin(), 19));
	EXPECT_TRUE(std::equal(array() + 20, array + ARRAY_SMOL, c.begin()));
	EXPECT_TRUE(std::equal(array(), array + 20, std::next(c.end(), -20)));
}


TYPED_TEST_P(sctListsTests, RemoveIf)
{
	typedef typename TypeParam::size_type size_type;
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
	TypeParam REF c = this->container;
	TypeParam cCopy = c;

	c.unique();
	EXPECT_EQ(c, cCopy);
	c.unique(alwaysTrue());
	EXPECT_EQ(c.size(), false);
}


REGISTER_TYPED_TEST_CASE_P(
	sctListsTests,
	SpliceEntire,
	SpliceOne,
	SpliceRange,
	RemoveIf,
	Unique
);


INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	sctListsTests,
	testList_type
);

#endif //SCT_LIST_TPP