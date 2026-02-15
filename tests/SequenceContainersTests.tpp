//
// Created by mscheman on 2/13/26.
//

#ifndef SEQUENCE_CONTAINERS_TESTS_TPP
#define SEQUENCE_CONTAINERS_TESTS_TPP

#if ns == std
#include <list>
#include <deque>
#include <vector>
#else
#include "list.hpp"
#include "deque.hpp"
#include "vector.hpp"
#endif

typedef ns::list<int>	intList_t;
typedef ns::list<str>	strList_t;
typedef ns::list<Fat>	fatList_t;

typedef ns::deque<int>	intDeque_t;
typedef ns::deque<str>	strDeque_t;
typedef ns::deque<Fat>	fatDeque_t;

typedef ns::vector<int>	intVector_t;
typedef ns::vector<str>	strVector_t;
typedef ns::vector<Fat>	fatVector_t;

#define ARRAY X(0), X(1), X(2), X(3), X(4), X(5), X(6), X(7), X(8), X(9),
#define ARRAY_SIZE 10
#define X(e) e
int const intArray[] = { ARRAY };
#undef X

#define X(e) str(#e)
str const strArray[] = { ARRAY };
#undef X

#define X(e) Fat(e, #e)
Fat const fatArray[] = { ARRAY };
#undef X
#undef ARRAY


template <typename T>
struct arrayGenerator {};

template <>
struct arrayGenerator<int> {
	int const*	operator()() const { return intArray; }
	int CREF	operator()(unsigned int const i) const { return intArray[i]; }
};

template <>
struct arrayGenerator<str> {
	str const*		operator()() const { return strArray; }
	str CREF	operator()(unsigned int const i) const { return strArray[i]; }
};

template <>
struct arrayGenerator<Fat> {
	Fat const*	operator()() const { return fatArray; }
	Fat CREF	operator()(unsigned int const i) const { return fatArray[i]; }
};


template <bool weakAssertions>
struct assertEqual;

template <>
struct assertEqual<false> {
	template <typename T> void operator()(T CREF lhs, T CREF rhs) const { EXPECT_EQ(lhs, rhs); }
};

template <>
struct assertEqual<true> {
	template <typename T> void operator()(T CREF lhs, T CREF rhs) const { ASSERT_EQ(lhs, rhs); }
};

template <typename Container>
class ConstructorTests : public ::testing::Test {
public:

	// Helper typdefs i cant access for some reason
	typedef typename Container::size_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::const_iterator	const_iterator;

	template <typename ArrayType, bool weakAssertions>
	static void RangeConstructorCheck(Container CREF container, ArrayType const array, assertEqual<weakAssertions> assertFunctor)
	{
		size_type	i = 0;
		assertFunctor(container.empty(), false);
		assertFunctor(container.size(), static_cast<size_type>(ARRAY_SIZE));
		assertFunctor(container.front(), array[0]);
		assertFunctor(container.back(), array[ARRAY_SIZE - 1]);
		for (const_iterator it = container.begin(); it != container.end(); ++it) {
			assertFunctor(*it, array[i]);
			++i;
		}
	}

};

typedef ::testing::Types<
	intList_t, strList_t, fatList_t,
	intDeque_t, strDeque_t, fatDeque_t,
	intVector_t, strVector_t, fatVector_t
>	testContainers_type;
TYPED_TEST_CASE_P(ConstructorTests);

TYPED_TEST_P(ConstructorTests, Default) {
	TypeParam container;
	EXPECT_EQ(container.empty(), true);
}

TYPED_TEST_P(ConstructorTests, Fill) {
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::const_iterator	const_iterator;
	// Bounds check
	size_type const	arrayIndex = 5;
	ASSERT_GE(arrayIndex, static_cast<size_type>(0));
	ASSERT_LT(arrayIndex, static_cast<size_type>(ARRAY_SIZE));

	value_type CREF	valueReference = arrayGenerator<value_type>()(arrayIndex);
	TypeParam		container(arrayIndex, valueReference);
	for (const_iterator it = container.begin(); it != container.end(); ++it)
		EXPECT_EQ(*it, valueReference);
	EXPECT_EQ(container.size(), static_cast<size_type>(arrayIndex));
	EXPECT_EQ(container.empty(), false);
	EXPECT_EQ(container.front(), valueReference);
	EXPECT_EQ(container.back(), valueReference);
}

TYPED_TEST_P(ConstructorTests, Range) {
	typedef typename TypeParam::value_type		value_type;

	value_type const*	array = arrayGenerator<value_type>()();

	TypeParam			container(array, array + ARRAY_SIZE);
	ConstructorTests<TypeParam>::RangeConstructorCheck(container, array, assertEqual<false>());
}

TYPED_TEST_P(ConstructorTests, Copy) {
	typedef typename TypeParam::value_type		value_type;
	value_type const* CREF	array = arrayGenerator<value_type>()();

	TypeParam	copy(array, array + ARRAY_SIZE);
	ConstructorTests<TypeParam>::RangeConstructorCheck(copy, array, assertEqual<true>());

	TypeParam	dest(copy);
	ConstructorTests<TypeParam>::RangeConstructorCheck(dest, array, assertEqual<false>());
	{
		TypeParam	isDeepCopy(dest);
		ConstructorTests<TypeParam>::RangeConstructorCheck(isDeepCopy, array, assertEqual<false>());
	}
	ConstructorTests<TypeParam>::RangeConstructorCheck(dest, array, assertEqual<false>());
}


REGISTER_TYPED_TEST_CASE_P(
	ConstructorTests,
	Default,
	Fill,
	Range,
	Copy
);

INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	ConstructorTests,
	testContainers_type
);

#endif //SEQUENCE_CONTAINERS_TESTS_TPP
