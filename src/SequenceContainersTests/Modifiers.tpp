//
// Created by mscheman on 2/16/26.
//

#ifndef SCT_MODIFIERS_TPP
#define SCT_MODIFIERS_TPP

template <typename Container>
class sctModifiersTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		sctModifiersTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_SIZE) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(sctModifiersTests);


TYPED_TEST_P(sctModifiersTests, FillAssign)
{
	typedef typename TypeParam::value_type	value_type;
	arrayGenerator<value_type>	array;

	TypeParam const target(25, array[3]);
	this->container = TypeParam();
	EXPECT_NE(this->container, target);
	this->container.assign(25, array[3]);
	EXPECT_EQ(this->container, target);
}


REGISTER_TYPED_TEST_CASE_P(
	sctModifiersTests,
	FillAssign
);


INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	sctModifiersTests,
	testContainers_type
);


#endif //SCT_MODIFIERS_TPP