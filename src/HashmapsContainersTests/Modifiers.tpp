	//
// Created by mscheman on 2/16/26.
//

#ifndef HCT_MODIFIERS_TPP
#define HCT_MODIFIERS_TPP


template <typename Container>
class hctModifiersTests : public ::testing::Test
{
	// Helper Typedefs
	typedef typename Container::value_type	value_type;

	public:
		hctModifiersTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


namespace HCT {
template <typename T>
struct allowDuplicates : ns::false_type {};
template <typename Key, typename Hash, typename KeyEqual, typename Allocator>
struct allowDuplicates<ns::unordered_multiset<Key, Hash, KeyEqual, Allocator> > : ns::true_type {};
template <typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
struct allowDuplicates<ns::unordered_multimap<Key, T, Hash, KeyEqual, Allocator> > : ns::true_type {};
template <typename T>
struct getValue
{
	T REF operator()(T REF t) { return t; }
	T CREF operator()(T CREF t) const { return t; }
};
template <typename T, typename U>
struct getValue<ns::pair<T, U> >
{
	U REF operator()(ns::pair<T, U> REF pair) { return pair.second; }
	U CREF operator()(ns::pair<T, U> CREF pair) const { return pair.second; }
};
template <bool allowDuplicates, typename T, typename Container>
struct checkInsert
{
	checkInsert(T CREF t, bool b) : value(t), shouldBeInserted(b) {}
	bool operator()(ns::pair<typename Container::iterator, bool> result) const { return getValue<typename Container::value_type>()(*result.first) == getValue<T>()(value) && result.second == shouldBeInserted; }
	T CREF	value;
	bool	shouldBeInserted;
};
template <typename T, typename Container>
struct checkInsert<true, T, Container> : ns::true_type
{
	checkInsert(T CREF t, bool) : value(t) {}
	bool operator()(typename Container::iterator it) const { return getValue<typename Container::value_type>()(*it) == getValue<T>()(value); }
	T CREF	value;
};
}


TYPED_TEST_CASE_P(hctModifiersTests);


TYPED_TEST_P(hctModifiersTests, Clear)
{
	TypeParam REF	c = this->container;

	EXPECT_EQ(c.empty(), false);
	EXPECT_EQ(c.size(), ARRAY_TINY);
	EXPECT_NE(c.begin(), c.end());
	c.clear();
	EXPECT_EQ(c.empty(), true);
	EXPECT_EQ(c.size(), 0u);
	EXPECT_EQ(c.begin(), c.end());
}


TYPED_TEST_P(hctModifiersTests, Insert)
{
	constexpr bool	allowDuplicates = HCT::allowDuplicates<TypeParam>::value;
	typedef typename TypeParam::value_type value_type;
	typedef typename ns::conditional<
		allowDuplicates,
		typename TypeParam::iterator,
		ns::pair<typename TypeParam::iterator, bool>
	>::type	result_type;
	typedef HCT::checkInsert<allowDuplicates, value_type, TypeParam>	checker_type;

	arrayGenerator<value_type>	array;
	TypeParam					c;
	result_type					result;

	// Insert in empty
	result = c.insert(array[0]);
	{
		checker_type checker(array[0], true);
		EXPECT_TRUE(checker(result) == true);
		EXPECT_EQ(c.size(), 1u);
		EXPECT_EQ(*c.begin(), array[0]);
		EXPECT_EQ(c.empty(), false);
	}
	// Insert in non-empty
	result = c.insert(array[1]);
	{
		checker_type checker(array[1], true);
		EXPECT_TRUE(checker(result) == true);
		EXPECT_EQ(c.size(), 2u);
		EXPECT_TRUE(*c.begin() == array[1] || *std::next(c.begin()) == array[1]);
		EXPECT_EQ(c.empty(), false);
	}
	// Insert duplicate
	result = c.insert(array[1]);
	{
		checker_type checker(array[1], false);
		EXPECT_TRUE(checker(result) == true);
		if (allowDuplicates)
			EXPECT_EQ(c.size(), 3u);
		else
			EXPECT_EQ(c.size(), 2u);
		EXPECT_TRUE(*c.begin() == array[1] || *std::next(c.begin()) == array[1]);
		EXPECT_EQ(c.empty(), false);
	}
}


TYPED_TEST_P(hctModifiersTests, InsertRange)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::iterator		iterator;

	arrayGenerator<value_type>					array;
	std::vector<value_type>						range(10, array[ARRAY_TINY]);
	TypeParam	REF 							c = this->container;
	iterator									ret;

	// Insert Range of duplicates
	c.insert(range.begin(), range.end());
	if (HCT::allowDuplicates<TypeParam>::value)
		EXPECT_EQ(c.size(), 20u);
	else {
		EXPECT_EQ(c.size(), 11u);
		EXPECT_TRUE(std::is_permutation(array(), array() + 11, c.begin()));
	}
	// Insert nothing but duplicates
	c.insert(range.begin(), range.end());
	if (HCT::allowDuplicates<TypeParam>::value)
		EXPECT_EQ(c.size(), 30u);
	else
		EXPECT_EQ(c.size(), 11u);
	// Insert valid range of numbers
	std::vector<value_type>	secondRange(array() + ARRAY_TINY + 1, array() + ARRAY_SMOL);
	c.insert(secondRange.begin(), secondRange.end());
	if (HCT::allowDuplicates<TypeParam>::value)
		EXPECT_EQ(c.size(), 69u);
	else {
		EXPECT_EQ(c.size(), 50u);
		EXPECT_TRUE(std::is_permutation(array(), array() + ARRAY_SMOL, c.begin()));
	}
}


TYPED_TEST_P(hctModifiersTests, Erase)
{
	TypeParam	REF	c = this->container;

	for (unsigned int i = 0u; i < ARRAY_TINY; ++i) {
		c.erase(c.begin());
		EXPECT_EQ(c.size(), ARRAY_TINY - i - 1);
	}
	EXPECT_TRUE(c.empty());
}


TYPED_TEST_P(hctModifiersTests, EraseKey)
{
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::key_type		key_type;

	arrayGenerator<value_type>					array;
	arrayGenerator<key_type>					keyArray;
	TypeParam	REF 							c = this->container;
	size_type									ret;

	// Erase valid key
	ret = c.erase(keyArray[0]);
	EXPECT_EQ(c.size(), 9u);
	EXPECT_EQ(ret, 1u);
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
	// Erase invalid key
	ret = c.erase(keyArray[0]);
	EXPECT_EQ(c.size(), 9u);
	EXPECT_EQ(ret, 0u);
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
	if (!HCT::allowDuplicates<TypeParam>::value)
		return ;
	// Remove multiple key
	for (int i = 0; i < 10; ++i)
		c.insert(array[0]);
	ret = c.erase(keyArray[0]);
	EXPECT_EQ(ret, 10u);
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
}


TYPED_TEST_P(hctModifiersTests, EraseRange)
{
	typedef typename TypeParam::iterator		iterator;

	TypeParam	REF 							c		= this->container;
	TypeParam									cCopy	= c;

	iterator ret;

	// Erase whole range :Ds
	ret = c.erase(c.begin(), c.end());
	EXPECT_EQ(ret, c.end());
	EXPECT_TRUE(c.empty());
	EXPECT_EQ(c.size(), 0u);

	// Erase
	c = cCopy;

	// Erase Single from begin
	c.erase(c.begin(), std::next(c.begin()));
	EXPECT_EQ(c.size(), 9u);
	// Erase Single from end
	c.erase(std::next(c.begin(), c.size() - 1), c.end());
	EXPECT_EQ(c.size(), 8u);
	// Erase Single from middle
	c.erase(std::next(c.begin(), 4), std::next(c.begin(), 5));
	EXPECT_EQ(c.size(), 7u);

	// Multiple erases
	c = cCopy;

	// Erase from begin
	c.erase(c.begin(), std::next(c.begin(), 2));
	EXPECT_EQ(c.size(), 8u);
	// Erase from end
	c.erase(std::next(c.begin(), c.size() - 2), c.end());
	EXPECT_EQ(c.size(), 6u);
	// Erase from middle
	c.erase(std::next(c.begin(), 2), std::next(c.begin(), 4));
	EXPECT_EQ(c.size(), 4u);
}


TYPED_TEST_P(hctModifiersTests, Swap)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam										other(array() + ARRAY_SMOL, array() + ARRAY_HUGE);
	TypeParam										otherCopy = other;
	TypeParam REF									c = this->container;
	TypeParam										cCopy = c;

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
	EXPECT_EQ(c.empty(), true);
	EXPECT_EQ(other.empty(), false);
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	other.swap(c);
	EXPECT_EQ(c.empty(), false);
	EXPECT_EQ(other.empty(), true);
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
	// Empty swap with empty
	c = TypeParam();
	cCopy = c;
	c.swap(other); // other is already empty
	EXPECT_EQ(c.empty(), true);
	EXPECT_EQ(other.empty(), true);
	EXPECT_EQ(c, otherCopy);
	EXPECT_EQ(other, cCopy);
	other.swap(c);
	EXPECT_EQ(c.empty(), true);
	EXPECT_EQ(other.empty(), true);
	EXPECT_EQ(c, cCopy);
	EXPECT_EQ(other, otherCopy);
}


REGISTER_TYPED_TEST_CASE_P(
	hctModifiersTests,
	Clear,
	Insert,
	InsertRange,
	Erase,
	EraseKey,
	EraseRange,
	Swap
);


INSTANTIATE_TYPED_TEST_CASE_P(
	HashmapsContainers,
	hctModifiersTests,
	hashmapsContainers_type
);


#endif //HCT_MODIFIERS_TPP