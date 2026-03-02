//
// Created by mscheman on 3/2/26.
//

#ifndef ACT_OPERATIONS_TPP
#define ACT_OPERATIONS_TPP


template <typename Container>
class actOperationsTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		actOperationsTests() : container(arrayGenerator<value_type>()() + 1, arrayGenerator<value_type>()() + ARRAY_TINY + 1) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(actOperationsTests);


TYPED_TEST_P(actOperationsTests, Find)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::key_type	key_type;
	typedef typename TypeParam::iterator	iterator;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	ACT::getValue<value_type>	getter;
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


TYPED_TEST_P(actOperationsTests, ConstFind)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::key_type		key_type;
	typedef typename TypeParam::const_iterator	const_iterator;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	ACT::getValue<value_type>	getter;
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


TYPED_TEST_P(actOperationsTests, Count)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::key_type	key_type;
	typedef typename TypeParam::size_type	size_type;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	TypeParam CREF				c			= this->container;
	size_type					count;
	bool const					allowDup	= ACT::allowsDuplicate<TypeParam>::value;

	// Make duplicate to check for multi[set/map]
	if (allowDup)
		for (int i = 0; i < ARRAY_TINY; ++i)
			this->container.insert(array[i]);

	// Count
	count = c.count(keyArray[1]);
	if (allowDup)
		EXPECT_EQ(count, size_type(2));
	else
		EXPECT_EQ(count, size_type(1));

	// No element Count
	count = c.count(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(count, size_type(0));
}


TYPED_TEST_P(actOperationsTests, LowerBound)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::key_type	key_type;
	typedef typename TypeParam::iterator	iterator;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	ACT::getValue<value_type>	getter;
	TypeParam REF				c			= this->container;
	iterator					bound;

	// Has element
	bound = c.lower_bound(keyArray[1]);
	ASSERT_NE(bound, c.end());
	EXPECT_EQ(getter(*bound), getter(array[1]));
	// Out of range but is bigger
	bound = c.lower_bound(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(bound, c.end());
	// Out of range but is smaller
	bound = c.lower_bound(keyArray[0]);
	ASSERT_NE(bound, c.end());
	EXPECT_EQ(getter(*bound), getter(array[1]));
}


TYPED_TEST_P(actOperationsTests, ConstLowerBound)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::key_type		key_type;
	typedef typename TypeParam::const_iterator	const_iterator;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	ACT::getValue<value_type>	getter;
	TypeParam CREF				c			= this->container;
	const_iterator				bound;

	// Has element
	bound = c.lower_bound(keyArray[1]);
	ASSERT_NE(bound, c.end());
	EXPECT_EQ(getter(*bound), getter(array[1]));
	// Out of range but is bigger
	bound = c.lower_bound(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(bound, c.end());
	// Out of range but is smaller
	bound = c.lower_bound(keyArray[0]);
	ASSERT_NE(bound, c.end());
	EXPECT_EQ(getter(*bound), getter(array[1]));
}


TYPED_TEST_P(actOperationsTests, UpperBound)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::key_type	key_type;
	typedef typename TypeParam::iterator	iterator;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	ACT::getValue<value_type>	getter;
	TypeParam REF				c			= this->container;
	iterator					bound;

	// Has element
	bound = c.upper_bound(keyArray[1]);
	ASSERT_NE(bound, c.end());
	EXPECT_EQ(getter(*bound), getter(array[2]));
	// Out of range but is bigger
	bound = c.upper_bound(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(bound, c.end());
	// Out of range but is smaller
	bound = c.upper_bound(keyArray[0]);
	ASSERT_NE(bound, c.end());
	EXPECT_EQ(getter(*bound), getter(array[1]));
}


TYPED_TEST_P(actOperationsTests, ConstUpperBound)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::key_type		key_type;
	typedef typename TypeParam::const_iterator	const_iterator;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	ACT::getValue<value_type>	getter;
	TypeParam CREF				c			= this->container;
	const_iterator				bound;

	// Has element
	bound = c.upper_bound(keyArray[1]);
	ASSERT_NE(bound, c.end());
	EXPECT_EQ(getter(*bound), getter(array[2]));
	// Out of range but is bigger
	bound = c.upper_bound(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(bound, c.end());
	// Out of range but is smaller
	bound = c.upper_bound(keyArray[0]);
	ASSERT_NE(bound, c.end());
	EXPECT_EQ(getter(*bound), getter(array[1]));
}


TYPED_TEST_P(actOperationsTests, EqualRange)
{
	typedef typename TypeParam::difference_type	difference_type;
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::key_type		key_type;
	typedef typename TypeParam::iterator		iterator;
	typedef ns::pair<iterator, iterator>		bound_type;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	ACT::getValue<value_type>	getter;
	TypeParam REF				c			= this->container;
	difference_type				dist;
	bound_type					bound;
	bool const					allowDup	= ACT::allowsDuplicate<TypeParam>::value;

	// Make duplicate to check for multi[set/map]
	if (allowDup)
		for (int i = 1; i < ARRAY_TINY + 1; ++i)
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
	EXPECT_EQ(getter(*bound.second), getter(array[2]));

	// Hasn't but lower
	bound = c.equal_range(keyArray[0]);
	ASSERT_NE(bound.first, c.end());
	ASSERT_NE(bound.second, c.end());
	if (allowDup)
		EXPECT_EQ(dist, 2);
	else
		EXPECT_EQ(dist, 1);
	EXPECT_EQ(getter(*bound.first), getter(array[1]));
	EXPECT_EQ(getter(*bound.second), getter(array[1]));

	// Hasn't but bigger
	bound = c.equal_range(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(bound.first, c.end());
	EXPECT_EQ(bound.second, c.end());
}


TYPED_TEST_P(actOperationsTests, ConstEqualRange)
{
	typedef typename TypeParam::difference_type			difference_type;
	typedef typename TypeParam::value_type				value_type;
	typedef typename TypeParam::key_type				key_type;
	typedef typename TypeParam::const_iterator			const_iterator;
	typedef ns::pair<const_iterator, const_iterator>	bound_type;

	arrayGenerator<value_type>	array;
	arrayGenerator<key_type>	keyArray;
	ACT::getValue<value_type>	getter;
	TypeParam CREF				c			= this->container;
	difference_type				dist;
	bound_type					bound;
	bool const					allowDup	= ACT::allowsDuplicate<TypeParam>::value;

	// Make duplicate to check for multi[set/map]
	if (allowDup)
		for (int i = 1; i < ARRAY_TINY + 1; ++i)
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
	EXPECT_EQ(getter(*bound.second), getter(array[2]));

	// Hasn't but lower
	bound = c.equal_range(keyArray[0]);
	ASSERT_NE(bound.first, c.end());
	ASSERT_NE(bound.second, c.end());
	if (allowDup)
		EXPECT_EQ(dist, 2);
	else
		EXPECT_EQ(dist, 1);
	EXPECT_EQ(getter(*bound.first), getter(array[1]));
	EXPECT_EQ(getter(*bound.second), getter(array[1]));

	// Hasn't but bigger
	bound = c.equal_range(keyArray[ARRAY_TINY + 1]);
	EXPECT_EQ(bound.first, c.end());
	EXPECT_EQ(bound.second, c.end());
}


REGISTER_TYPED_TEST_CASE_P(
	actOperationsTests,
	Find,
	ConstFind,
	Count,
	LowerBound,
	ConstLowerBound,
	UpperBound,
	ConstUpperBound,
	EqualRange,
	ConstEqualRange
);


INSTANTIATE_TYPED_TEST_CASE_P(
	AssociativeContainers,
	actOperationsTests,
	associativeContainers_type
);

#endif //ACT_OPERATIONS_TPP