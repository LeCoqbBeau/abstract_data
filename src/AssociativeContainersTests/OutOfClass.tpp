//
// Created by mscheman on 2/23/26.
//

#ifndef ACT_OUT_OF_CLASS_TPP
#define ACT_OUT_OF_CLASS_TPP


template <typename Container>
class actOutOfClassTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		actOutOfClassTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(actOutOfClassTests);


TYPED_TEST_P(actOutOfClassTests, Swap)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;
	TypeParam										other(array() + ARRAY_TINY, array() + ARRAY_SMOL);
	TypeParam										otherCopy = other;

	// Normal cases
	ns::swap(c, other);
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


TYPED_TEST_P(actOutOfClassTests, RelationalOperators)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam		a(array() + 1, array() + ARRAY_TINY + 1);
	TypeParam		b(array(), array() + ARRAY_TINY); // this is indeed c, but it's not a direct copy
	TypeParam REF	c = this->container;
	TypeParam		copy = c;

	// operator ==
	EXPECT_TRUE((a == b) == false);
	EXPECT_TRUE((b == c) == true);
	EXPECT_TRUE((c == copy) == true);
	// operator !=
	EXPECT_TRUE((a != b) == true);
	EXPECT_TRUE((b != c) == false);
	EXPECT_TRUE((c != copy) == false);
	// operator <
	EXPECT_TRUE((a < b) == false);
	EXPECT_TRUE((b < c) == false);
	EXPECT_TRUE((c < copy) == false);
	// operator <=
	EXPECT_TRUE((a <= b) == false);
	EXPECT_TRUE((b <= c) == true);
	EXPECT_TRUE((c <= copy) == true);
	// operator >
	EXPECT_TRUE((a > b) == true);
	EXPECT_TRUE((b > c) == false);
	EXPECT_TRUE((c > copy) == false);
	// operator >=
	EXPECT_TRUE((a >= b) == true);
	EXPECT_TRUE((b >= c) == true);
	EXPECT_TRUE((c >= copy) == true);
}


REGISTER_TYPED_TEST_CASE_P(
	actOutOfClassTests,
	Swap,
	RelationalOperators
);


INSTANTIATE_TYPED_TEST_CASE_P(
	AssociativeContainers,
	actOutOfClassTests,
	associativeContainers_type
);


#endif //ACT_OUT_OF_CLASS_TPP