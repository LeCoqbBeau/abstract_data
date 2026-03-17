	//
// Created by mscheman on 2/16/26.
//

#ifndef HCT_LOOKUP_TPP
#define HCT_LOOKUP_TPP


template <typename Container>
class hctLookupTests : public ::testing::Test
{
	// Helper Typedefs
	typedef typename Container::value_type	value_type;

	public:
		hctLookupTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(hctLookupTests);


TYPED_TEST_P(hctLookupTests, Find)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::key_type	key_type;
	typedef typename TypeParam::iterator	iterator;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	HCT::getValue<value_type>	getter;
	TypeParam REF				c = this->container;
	iterator					it;

	// Find exists
	it = c.find(keyArray[1]);
	ASSERT_NE(it, c.end());
	EXPECT_EQ(getter(*it), getter(array[1]));

	// Didnt found
	it = c.find(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(it, c.end());
}


TYPED_TEST_P(hctLookupTests, ConstFind)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::key_type		key_type;
	typedef typename TypeParam::const_iterator	const_iterator;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	HCT::getValue<value_type>	getter;
	TypeParam CREF				c = this->container;
	const_iterator				it;

	// Find exists
	it = c.find(keyArray[1]);
	ASSERT_NE(it, c.end());
	EXPECT_EQ(getter(*it), getter(array[1]));

	// Didnt found
	it = c.find(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(it, c.end());
}


TYPED_TEST_P(hctLookupTests, Count)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::key_type	key_type;
	typedef typename TypeParam::size_type	size_type;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	TypeParam CREF				c			= this->container;
	size_type					count;
	bool const					allowDup	= HCT::allowDuplicates<TypeParam>::value;

	// Make duplicate to check for multi[set/map]
	if (allowDup)
		for (unsigned int i = 0u; i < ARRAY_TINY; ++i)
			this->container.insert(array[i]);

	// Count
	count = c.count(keyArray[1]);
	if (allowDup)
		EXPECT_EQ(count, 2u);
	else
		EXPECT_EQ(count, 1u);

	// No element Count
	count = c.count(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(count, 0u);
}


TYPED_TEST_P(hctLookupTests, EqualRange)
{
	typedef typename TypeParam::difference_type	difference_type;
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::key_type		key_type;
	typedef typename TypeParam::iterator		iterator;
	typedef ns::pair<iterator, iterator>		bound_type;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	HCT::getValue<value_type>	getter;
	TypeParam REF				c			= this->container;
	difference_type				dist;
	bound_type					bound;
	bool const					allowDup	= HCT::allowDuplicates<TypeParam>::value;

	// Make duplicate to check for multi[set/map]
	if (allowDup)
		for (unsigned int i = 1u; i < ARRAY_TINY + 1; ++i)
			this->container.insert(array[i]);

	// Has
	bound = c.equal_range(keyArray[1]);
	ASSERT_NE(bound.first, c.end());
	ASSERT_NE(bound.second, c.end());
	dist = std::distance(bound.first, bound.second);
	if (allowDup)
		EXPECT_EQ(dist, 2);
	else
		EXPECT_EQ(dist, 1);
	EXPECT_EQ(getter(*bound.first), getter(array[1]));
	EXPECT_NE(getter(*bound.second), getter(array[1]));

	// Hasn't but lower
	bound = c.equal_range(keyArray[-1]);
	EXPECT_EQ(bound.first, c.end());
	EXPECT_EQ(bound.second, c.end());

	// Hasn't but bigger
	bound = c.equal_range(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(bound.first, c.end());
	EXPECT_EQ(bound.second, c.end());
}


TYPED_TEST_P(hctLookupTests, ConstEqualRange)
{
	typedef typename TypeParam::difference_type			difference_type;
	typedef typename TypeParam::value_type				value_type;
	typedef typename TypeParam::key_type				key_type;
	typedef typename TypeParam::const_iterator			const_iterator;
	typedef ns::pair<const_iterator, const_iterator>	bound_type;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	HCT::getValue<value_type>	getter;
	TypeParam CREF				c			= this->container;
	difference_type				dist;
	bound_type					bound;
	bool const					allowDup	= HCT::allowDuplicates<TypeParam>::value;

	// Make duplicate to check for multi[set/map]
	if (allowDup)
		for (unsigned int i = 1u; i < ARRAY_TINY + 1; ++i)
			this->container.insert(array[i]);

	// Has
	bound = c.equal_range(keyArray[1]);
	ASSERT_NE(bound.first, c.end());
	ASSERT_NE(bound.second, c.end());
	dist = std::distance(bound.first, bound.second);
	if (allowDup)
		EXPECT_EQ(dist, 2);
	else
		EXPECT_EQ(dist, 1);
	EXPECT_EQ(getter(*bound.first), getter(array[1]));
	EXPECT_NE(getter(*bound.second), getter(array[1]));

	// Hasn't but lower
	bound = c.equal_range(keyArray[-1]);
	EXPECT_EQ(bound.first, c.end());
	EXPECT_EQ(bound.second, c.end());

	// Hasn't but bigger
	bound = c.equal_range(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(bound.first, c.end());
	EXPECT_EQ(bound.second, c.end());
}


REGISTER_TYPED_TEST_CASE_P(
	hctLookupTests,
	Find,
	ConstFind,
	Count,
	EqualRange,
	ConstEqualRange
);


INSTANTIATE_TYPED_TEST_CASE_P(
	HashmapsContainers,
	hctLookupTests,
	hashmapsContainers_type
);


#endif //HCT_LOOKUP_TPP