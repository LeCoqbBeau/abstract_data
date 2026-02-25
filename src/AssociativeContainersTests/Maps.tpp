//
// Created by mscheman on 2/25/26.
//

#ifndef ACT_MAPS_TPP
#define ACT_MAPS_TPP


template <typename Container>
class actMapsTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		actMapsTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(actMapsTests);


TYPED_TEST_P(actMapsTests, SubscriptOperator)
{
	arrayGenerator<typename TypeParam::key_type>	keyArray;
	arrayGenerator<typename TypeParam::mapped_type>	mapArray;
	TypeParam REF	c = this->container;

	// Insert using subscript operator[]
	c[keyArray[ARRAY_TINY]] = mapArray[ARRAY_TINY];
	EXPECT_EQ(c[keyArray[ARRAY_TINY]], mapArray[ARRAY_TINY]);
	// Find using subscript operator[]
	EXPECT_EQ(c[keyArray[0]], mapArray[0]);
}


TYPED_TEST_P(actMapsTests, At)
{
	arrayGenerator<typename TypeParam::key_type>	keyArray;
	arrayGenerator<typename TypeParam::mapped_type>	mapArray;
	TypeParam REF	c = this->container;

	EXPECT_THROW(c.at(keyArray[ARRAY_TINY]), ns::out_of_range);
	EXPECT_EQ(c.at(keyArray[0]), mapArray[0]);
}


REGISTER_TYPED_TEST_CASE_P(
	actMapsTests,
	SubscriptOperator,
	At
);


INSTANTIATE_TYPED_TEST_CASE_P(
	AssociativeContainers,
	actMapsTests,
	testMap_type
);



#endif //ACT_MAPS_TPP