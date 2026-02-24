//
// Created by mscheman on 2/24/26.
//

#ifndef ACT_CONSTRUCTORS_TPP
#define ACT_CONSTRUCTORS_TPP


template <typename Container>
class actConstructorTests : public ::testing::Test {};


TYPED_TEST_CASE_P(actConstructorTests);


TYPED_TEST_P(actConstructorTests, Default)
{
	TypeParam container;
	EXPECT_EQ(container.empty(), true);
	EXPECT_EQ(container.size(), static_cast<typename TypeParam::size_type>(0));
}


TYPED_TEST_P(actConstructorTests, Range)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::size_type	size_type;
	arrayGenerator<value_type>				array;

	TypeParam	c(array(), array() + ARRAY_TINY);
	EXPECT_EQ(c.empty(), false);
	EXPECT_EQ(c.size(), size_type(ARRAY_TINY));
	int i = 0;
	for (typename TypeParam::iterator it = c.begin(); it != c.end(); ++it) {
		EXPECT_EQ(*it, array[i]);
		++i;
	}
}


TYPED_TEST_P(actConstructorTests, Copy)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::size_type	size_type;
	arrayGenerator<value_type>				array;

	// Creates the source
	TypeParam	src(array(), array() + ARRAY_TINY);
	ASSERT_EQ(src.empty(), false);
	ASSERT_EQ(src.size(), size_type(ARRAY_TINY));
	int i = 0;
	for (typename TypeParam::iterator it = src.begin(); it != src.end(); ++it) {
		ASSERT_EQ(*it, array[i]);
		++i;
	}
	// Actual tests
	TypeParam dest(src);
	EXPECT_EQ(dest, src);
	{
		TypeParam isDeepCopy(dest);
		EXPECT_EQ(dest, isDeepCopy);
	}
	EXPECT_EQ(src, dest);
}


TYPED_TEST_P(actConstructorTests, AssignementOperator)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::size_type		size_type;
	arrayGenerator<value_type>					array;

	TypeParam const copy(array(), array() + ARRAY_TINY);
	TypeParam	dest = copy;
	EXPECT_EQ(copy, dest);
	{
		TypeParam	isDeepCopy = dest;
		EXPECT_EQ(dest, isDeepCopy);
	}
	EXPECT_EQ(copy, dest);
	// Resizing
	TypeParam	sneaky(array(), array() + 2);
	EXPECT_EQ(sneaky.size(), static_cast<size_type>(2));
	sneaky = copy;
	EXPECT_EQ(copy, sneaky);
	// Self Assignement
	TypeParam	dudeSeriously;
	TypeParam	*iAmDoingShenanigans = &dudeSeriously;
	dudeSeriously = *iAmDoingShenanigans;
	EXPECT_EQ(dudeSeriously.empty(), true);
	// Return by value
	TypeParam	partially(array(), array() + ARRAY_TINY / 2);
	(dudeSeriously = partially) = copy;
	EXPECT_NE(dudeSeriously, partially);
	EXPECT_EQ(dudeSeriously, copy);
	// Empty Assignement
	TypeParam empty;
	dest = empty;
	empty = copy;
	EXPECT_NE(empty, dest);
	EXPECT_NE(dest, copy);
	EXPECT_EQ(empty, copy);
}


REGISTER_TYPED_TEST_CASE_P(
	actConstructorTests,
	Default,
	Range,
	Copy,
	AssignementOperator
);


INSTANTIATE_TYPED_TEST_CASE_P(
	AssociativeContainers,
	actConstructorTests,
	associativeContainers_type
);

#endif //ACT_CONSTRUCTORS_TPP