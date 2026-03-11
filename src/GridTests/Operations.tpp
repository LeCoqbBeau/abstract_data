//
// Created by mscheman on 2/23/26.
//

#ifndef GT_OPERATIONS_TPP
#define GT_OPERATIONS_TPP

template <typename Container>
class gtOperationsTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		gtOperationsTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + Container::size()) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(gtOperationsTests);


TYPED_TEST_P(gtOperationsTests, Fill)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c = this->container;

	c.fill(array[TypeParam::size()]);
	for (typename TypeParam::iterator it = c.begin(); it != c.end(); ++it)
		EXPECT_EQ(*it, array[TypeParam::size()]);
}


TYPED_TEST_P(gtOperationsTests, Swap)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;
	TypeParam										other(array[1]);
	TypeParam										otherCopy = other;

	// Normal cases
	c.swap(other);
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	other.swap(c);
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
	// Swap with self
	c.swap(c);
	EXPECT_EQ(c, c);
	// Swap with empty
	other = TypeParam(); // create empty container without using assign nor clear
	otherCopy = other;
	c.swap(other);
	EXPECT_EQ(c.empty(), TypeParam::empty());
	EXPECT_EQ(other.empty(), TypeParam::empty());
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	other.swap(c);
	EXPECT_EQ(c.empty(), TypeParam::empty());
	EXPECT_EQ(other.empty(), TypeParam::empty());
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
	// Empty swap with empty
	c = TypeParam();
	cCopy = c;
	c.swap(other); // other is already empty
	EXPECT_EQ(c.empty(), TypeParam::empty());
	EXPECT_EQ(other.empty(), TypeParam::empty());
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	other.swap(c);
	EXPECT_EQ(c.empty(), TypeParam::empty());
	EXPECT_EQ(other.empty(), TypeParam::empty());
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
}


REGISTER_TYPED_TEST_CASE_P(
	gtOperationsTests,
	Fill,
	Swap
);


INSTANTIATE_TYPED_TEST_CASE_P(
	GridContainer,
	gtOperationsTests,
	testGrid_type
);


#endif //GT_OPERATIONS_TPP