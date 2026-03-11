//
// Created by mscheman on 2/23/26.
//

#ifndef HCT_OUT_OF_CLASS_TPP
#define HCT_OUT_OF_CLASS_TPP


#ifndef USE_FT
# include <algorithm>
#else
# include "algorithm.hpp"
#endif


template <typename Container>
class hctOutOfClassTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		hctOutOfClassTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(hctOutOfClassTests);

#include "algorithm.hpp"
TYPED_TEST_P(hctOutOfClassTests, Swap)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;
	TypeParam										other(array() + ARRAY_TINY, array() + ARRAY_SMOL);
	TypeParam										otherCopy = other;

	// Normal cases
	printContainer(c); std::cout << std::endl;
	printContainer(other); std::cout << std::endl;
	ns::swap(c, other);
	printContainer(c); std::cout << std::endl;
	printContainer(other); std::cout << std::endl;
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	ns::swap(other, c);
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
	// Swap with self
	ns::swap(c, c);
	EXPECT_EQ(c, c);
	// Swap with empty
	other = TypeParam(); // create empty container without using assign nor clear
	otherCopy = other;
	ns::swap(c, other);
	EXPECT_EQ(c.empty(), true);
	EXPECT_EQ(other.empty(), false);
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	ns::swap(other, c);
	EXPECT_EQ(c.empty(), false);
	EXPECT_EQ(other.empty(), true);
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
	// Empty swap with empty
	c = TypeParam();
	cCopy = c;
	ns::swap(c, other); // other is already empty
	EXPECT_EQ(c.empty(), true);
	EXPECT_EQ(other.empty(), true);
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	ns::swap(other, c);
	EXPECT_EQ(c.empty(), true);
	EXPECT_EQ(other.empty(), true);
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
}


TYPED_TEST_P(hctOutOfClassTests, RelationalOperators)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam		a(array() + 1, array() + ARRAY_TINY + 1);
	TypeParam		b(array(), array() + ARRAY_TINY); // this is indeed c, but it's not a direct copy
	TypeParam REF	c = this->container;
	TypeParam		copy = c;

	// operator ==
	EXPECT_EQ(a == b, false);
	EXPECT_EQ(b == c, true);
	EXPECT_EQ(c == copy, true);
	// operator !=
	EXPECT_EQ(a != b, true);
	EXPECT_EQ(b != c, false);
	EXPECT_EQ(c != copy, false);
}


REGISTER_TYPED_TEST_CASE_P(
	hctOutOfClassTests,
	Swap,
	RelationalOperators
);


INSTANTIATE_TYPED_TEST_CASE_P(
	GridContainer,
	hctOutOfClassTests,
	hashmapsContainers_type
);


#endif //HCT_OUT_OF_CLASS_TPP