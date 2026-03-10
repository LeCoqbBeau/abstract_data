//
// Created by mscheman on 3/9/26.
//

#ifndef GT_CONSTRUCTORS_TPP
#define GT_CONSTRUCTORS_TPP


template <typename Container>
class gtConstructorTests : public ::testing::Test {};

TYPED_TEST_CASE_P(gtConstructorTests);


TYPED_TEST_P(gtConstructorTests, Default)
{
	TypeParam container;
	if (container.rows() && container.cols()) {
		EXPECT_EQ(container.empty(), false);
		EXPECT_EQ(container.size(), container.rows() * container.cols());
	}
	else {
		EXPECT_EQ(container.empty(), true);
		EXPECT_EQ(container.size(), 0u);
	}
}


TYPED_TEST_P(gtConstructorTests, Fill)
{
	arrayGenerator<typename TypeParam::value_type> array;
	TypeParam container(array[0]);
	for (typename TypeParam::iterator it = container.begin(); it != container.end(); ++it)
		EXPECT_EQ(*it, array[0]);
}


TYPED_TEST_P(gtConstructorTests, Range)
{
	typedef typename TypeParam::value_type		value_type;

	arrayGenerator<value_type>	array;
	rangeGenerator<value_type>	range;
	{
		TypeParam c(array(), array() + TypeParam::size());
		EXPECT_TRUE(std::equal(c.begin(), c.end(), array()));
	}
	{
		TypeParam c(array(), array() + TypeParam::size() + 20);
		EXPECT_TRUE(std::equal(array(),  array() + TypeParam::size(), c.begin()));
	}
	{
		TypeParam c(range(), range(TypeParam::size()));
		EXPECT_TRUE(std::equal(c.begin(), c.end(), range()));
	}
	{
		TypeParam c(range(), range(TypeParam::size() + 20));
		EXPECT_TRUE(std::equal(range(),  range(TypeParam::size()), c.begin()));
	}
}


TYPED_TEST_P(gtConstructorTests, Copy)
{
	typedef typename TypeParam::value_type		value_type;

	arrayGenerator<value_type>	array;
	TypeParam	copy(array(), array() + ARRAY_TINY);
	TypeParam	dest(copy);
	EXPECT_EQ(copy, dest);
	{
		TypeParam	isDeepCopy(dest);
		EXPECT_EQ(dest, isDeepCopy);
	}
	EXPECT_EQ(copy, dest);
}


TYPED_TEST_P(gtConstructorTests, AssignementOperator)
{
	typedef typename TypeParam::value_type		value_type;
	// typedef typename TypeParam::size_type		size_type;

	arrayGenerator<value_type>	array;
	TypeParam const copy(array(), array() + TypeParam::size());
	TypeParam	dest = copy;
	EXPECT_EQ(copy, dest);
	{
		TypeParam	isDeepCopy = dest;
		EXPECT_EQ(dest, isDeepCopy);
	}
	EXPECT_EQ(copy, dest);
	// Resizing
	TypeParam	sneaky(array(), array() + 2);
	EXPECT_EQ(sneaky.size(), TypeParam::size());
	sneaky = copy;
	EXPECT_EQ(copy, sneaky);
	// Self Assignement
	TypeParam	dudeSeriously;
	TypeParam	*iAmDoingShenanigans = &dudeSeriously;
	dudeSeriously = *iAmDoingShenanigans;
	EXPECT_EQ(dudeSeriously.empty(), TypeParam::empty());
	// Return by value
	TypeParam	partially(array(), array() + TypeParam::size() / 2);
	(dudeSeriously = partially) = copy; // dudeSeriosly = partially; dudeSeriously = copy;
	if (!TypeParam::empty())
		EXPECT_NE(dudeSeriously, partially);
	else
		EXPECT_EQ(dudeSeriously, partially);
	EXPECT_EQ(dudeSeriously, copy);
	// Empty Assignement
	TypeParam empty;
	dest = empty;
	empty = copy;
	if (!TypeParam::empty()) {
		EXPECT_NE(empty, dest);
		EXPECT_NE(dest, copy);
	}
	EXPECT_EQ(empty, copy);
}


REGISTER_TYPED_TEST_CASE_P(
	gtConstructorTests,
	Default,
	Fill,
	Range,
	Copy,
	AssignementOperator
);


INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	gtConstructorTests,
	testGrid_type
);


#endif //GT_CONSTRUCTORS_TPP