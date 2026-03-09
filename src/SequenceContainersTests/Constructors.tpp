//
// Created by mscheman on 2/13/26.
//

#ifndef SCT_CONSTRUCTOR_TPP
#define SCT_CONSTRUCTOR_TPP

template <typename Container>
class gtConstructorTests : public ::testing::Test {};

TYPED_TEST_CASE_P(sctConstructorTests);


TYPED_TEST_P(gtConstructorTests, Default)
{
	TypeParam container;
	EXPECT_EQ(container.empty(), true);
	EXPECT_EQ(container.size(), static_cast<typename TypeParam::size_type>(0));
}


TYPED_TEST_P(gtConstructorTests, Fill)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::const_iterator	const_iterator;
	// Bounds check
	size_type const	arrayIndex = 5;
	ASSERT_GE(arrayIndex, static_cast<size_type>(0));
	ASSERT_LT(arrayIndex, static_cast<size_type>(ARRAY_TINY));

	value_type CREF	valueReference = arrayGenerator<value_type>()(arrayIndex);
	TypeParam		container(arrayIndex, valueReference);
	for (const_iterator it = container.begin(); it != container.end(); ++it)
		EXPECT_EQ(*it, valueReference);
	EXPECT_EQ(container.size(), static_cast<size_type>(arrayIndex));
	EXPECT_EQ(container.empty(), false);
	EXPECT_EQ(container.front(), valueReference);
	EXPECT_EQ(container.back(), valueReference);
}


TYPED_TEST_P(gtConstructorTests, Range)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::const_iterator	const_iterator;

	value_type const*			array = arrayGenerator<value_type>()();
	rangeGenerator<value_type>	range;

	TypeParam			c1(array, array + ARRAY_TINY);
	size_type	i = 0;
	EXPECT_EQ(c1.empty(), false);
	EXPECT_EQ(c1.size(), static_cast<size_type>(ARRAY_TINY));
	EXPECT_EQ(c1.front(), array[0]);
	EXPECT_EQ(c1.back(), array[ARRAY_TINY - 1]);
	for (const_iterator it = c1.begin(); it != c1.end(); ++it) {
		EXPECT_EQ(*it, array[i]);
		++i;
	}

	TypeParam			c2(range(0), range(ARRAY_TINY));
	i = 0;
	EXPECT_EQ(c2.empty(), false);
	EXPECT_EQ(c2.size(), static_cast<size_type>(ARRAY_TINY));
	EXPECT_EQ(c2.front(), array[0]);
	EXPECT_EQ(c2.back(), array[ARRAY_TINY - 1]);
	for (const_iterator it = c2.begin(); it != c2.end(); ++it) {
		EXPECT_EQ(*it, array[i]);
		++i;
	}
}


TYPED_TEST_P(gtConstructorTests, Copy)
{
	typedef typename TypeParam::value_type		value_type;
	value_type const*	array = arrayGenerator<value_type>()();

	TypeParam	copy(array, array + ARRAY_TINY);
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
	typedef typename TypeParam::size_type		size_type;
	value_type const*	array = arrayGenerator<value_type>()();

	TypeParam const copy(array, array + ARRAY_TINY);
	TypeParam	dest = copy;
	EXPECT_EQ(copy, dest);
	{
		TypeParam	isDeepCopy = dest;
		EXPECT_EQ(dest, isDeepCopy);
	}
	EXPECT_EQ(copy, dest);
	// Resizing
	TypeParam	sneaky(array, array + 2);
	EXPECT_EQ(sneaky.size(), static_cast<size_type>(2));
	sneaky = copy;
	EXPECT_EQ(copy, sneaky);
	// Self Assignement
	TypeParam	dudeSeriously;
	TypeParam	*iAmDoingShenanigans = &dudeSeriously;
	dudeSeriously = *iAmDoingShenanigans;
	EXPECT_EQ(dudeSeriously.empty(), true);
	// Return by value
	TypeParam	partially(array, array + ARRAY_TINY / 2);
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
	sctConstructorTests,
	Default,
	Fill,
	Range,
	Copy,
	AssignementOperator
);


INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	gtConstructorTests,
	sequenceContainers_type
);


#endif //SCT_CONSTRUCTOR_TPP
