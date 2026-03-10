//
// Created by mscheman on 2/23/26.
//

#ifndef SCT_OUT_OF_CLASS_TPP
#define SCT_OUT_OF_CLASS_TPP

template <typename Container>
class gtOutOfClassTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		gtOutOfClassTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + Container::size()) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(gtOutOfClassTests);


TYPED_TEST_P(gtOutOfClassTests, Swap)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;
	TypeParam										other(array[1]);
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
	EXPECT_EQ(c.empty(), TypeParam::empty());
	EXPECT_EQ(other.empty(), TypeParam::empty());
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	ns::swap(other, c);
	EXPECT_EQ(c.empty(), TypeParam::empty());
	EXPECT_EQ(other.empty(), TypeParam::empty());
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
	// Empty swap with empty
	c = TypeParam();
	cCopy = c;
	ns::swap(c, other); // other is already empty
	EXPECT_EQ(c.empty(), TypeParam::empty());
	EXPECT_EQ(other.empty(), TypeParam::empty());
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	ns::swap(other, c);
	EXPECT_EQ(c.empty(), TypeParam::empty());
	EXPECT_EQ(other.empty(), TypeParam::empty());
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
}


TYPED_TEST_P(gtOutOfClassTests, RelationalOperators)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam		a(array() + 1, array() + TypeParam::size() + 1);
	TypeParam		b(array(), array() + TypeParam::size()); // this is indeed c, but it's not a direct copy
	TypeParam REF	c = this->container;
	TypeParam		copy = c;

	if (TypeParam::empty()) {
		// operator ==
		EXPECT_EQ(a == b, true);
		EXPECT_EQ(b == c, true);
		EXPECT_EQ(c == copy, true);
		// operator !=
		EXPECT_EQ(a != b, false);
		EXPECT_EQ(b != c, false);
		EXPECT_EQ(c != copy, false);
		// operator <
		EXPECT_EQ(a < b, false);
		EXPECT_EQ(b < c, false);
		EXPECT_EQ(c < copy, false);
		// operator <=
		EXPECT_EQ(a <= b, true);
		EXPECT_EQ(b <= c, true);
		EXPECT_EQ(c <= copy, true);
		// operator >
		EXPECT_EQ(a > b, false);
		EXPECT_EQ(b > c, false);
		EXPECT_EQ(c > copy, false);
		// operator >=
		EXPECT_EQ(a >= b, true);
		EXPECT_EQ(b >= c, true);
		EXPECT_EQ(c >= copy, true);

		return;
	}

	// operator ==
	EXPECT_EQ(a == b, false);
	EXPECT_EQ(b == c, true);
	EXPECT_EQ(c == copy, true);
	// operator !=
	EXPECT_EQ(a != b, true);
	EXPECT_EQ(b != c, false);
	EXPECT_EQ(c != copy, false);
	// operator <
	EXPECT_EQ(a < b, false);
	EXPECT_EQ(b < c, false);
	EXPECT_EQ(c < copy, false);
	// operator <=
	EXPECT_EQ(a <= b, false);
	EXPECT_EQ(b <= c, true);
	EXPECT_EQ(c <= copy, true);
	// operator >
	EXPECT_EQ(a > b, true);
	EXPECT_EQ(b > c, false);
	EXPECT_EQ(c > copy, false);
	// operator >=
	EXPECT_EQ(a >= b, true);
	EXPECT_EQ(b >= c, true);
	EXPECT_EQ(c >= copy, true);
}


REGISTER_TYPED_TEST_CASE_P(
	gtOutOfClassTests,
	Swap,
	RelationalOperators
);


INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	gtOutOfClassTests,
	testGrid_type
);


#endif //SCT_OUT_OF_CLASS_TPP