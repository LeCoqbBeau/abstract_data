//
// Created by mscheman on 2/16/26.
//

#ifndef ACT_MODIFIERS_TPP
#define ACT_MODIFIERS_TPP


template <typename Container>
class actModifiersTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		actModifiersTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


namespace ACT {
template <typename T>
struct allowsDuplicate : ft::false_type {};
template <typename T>
struct allowsDuplicate<ns::multiset<T> > : ft::true_type {};
template <typename T, typename U>
struct allowsDuplicate<ns::multimap<T, U> > : ft::true_type {};
template <typename T>
struct insertReturnCheck;
template <typename T>
struct insertReturnCheck<ns::set<T> >
{
	void operator() (ns::pair<typename ns::set<T>::iterator, bool> insertReturn) const
	{
		EXPECT_EQ(*insertReturn.first, toComp);
		EXPECT_EQ(insertReturn.second, wasInserted);
	}

	T		toComp;
	bool	wasInserted;
};
template <typename T>
struct insertReturnCheck<ns::multiset<T> >
{
	void operator() (typename ns::multiset<T>::iterator insertReturn) const
	{
		EXPECT_EQ(*insertReturn, toComp);
	}

	T		toComp;
	bool	wasInserted;
};
template <typename T, typename U>
struct insertReturnCheck<ns::map<T, U> >
{
	void operator() (ns::pair<typename ns::map<T, U>::iterator, bool> insertReturn) const
	{
		EXPECT_EQ(insertReturn.first->second, toComp);
		EXPECT_EQ(insertReturn.second, wasInserted);
	}

	U		toComp;
	bool	wasInserted;
};
template <typename T, typename U>
struct insertReturnCheck<ns::multimap<T, U> >
{
	void operator() (typename ns::multimap<T, U>::iterator insertReturn) const
	{
		EXPECT_EQ(insertReturn->second, toComp);
	}

	U		toComp;
	bool	wasInserted;
};

# define DECLARE_AST_INSERT_RETURN_CHECKER(type)	\
	ACT::insertReturnCheck<typename ACT::iteratorValue<type>::value_type, ACT::allowsDuplicate<type>::value >
}


TYPED_TEST_CASE_P(actModifiersTests);


TYPED_TEST_P(actModifiersTests, InsertSingle)
{
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::iterator		iterator;
	typedef CONDITIONAL_TT(
		ACT::allowsDuplicate<TypeParam>::value,
		iterator,
		ns::pair<iterator FT_COMMA bool>
	)											return_type;

	arrayGenerator<value_type>					array;
	ACT::insertReturnCheck<TypeParam>			checker = {};
	ACT::getValue<value_type>					getter;
	TypeParam	REF 							c = this->container;
	return_type									ret;

	// Successful insert (no duplicate)
	ret = c.insert(array[ARRAY_TINY]);
	checker.toComp = getter(array[ARRAY_TINY]);
	checker.wasInserted = true;
	checker(ret);
	EXPECT_EQ(c.size(), size_type(11));
	EXPECT_TRUE(std::equal(array(), array() + ARRAY_TINY + 1, c.begin()));
	// Failed insert (duplicate)
	ret = c.insert(array[ARRAY_TINY]);
	checker.toComp = getter(array[ARRAY_TINY]);
	checker.wasInserted = false;
	checker(ret);
	EXPECT_TRUE(std::equal(array(), array() + ARRAY_TINY + 1, c.begin()));
	if (ACT::allowsDuplicate<TypeParam>::value) {
		EXPECT_EQ(*std::next(c.end(), -1), array[ARRAY_TINY]);
		EXPECT_EQ(*std::next(c.end(), -2), array[ARRAY_TINY]);
		EXPECT_EQ(c.size(), size_type(12));
	}
	else
		EXPECT_EQ(c.size(), size_type(11));
}


TYPED_TEST_P(actModifiersTests, InsertHint)
{
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::iterator		iterator;

	arrayGenerator<value_type>					array;
	ACT::getValue<value_type>					getter;
	TypeParam	REF 							c = this->container;
	iterator									ret;

	// Successful insert (no duplicate)
	iterator hint = c.end();
	ret = c.insert(hint, array[ARRAY_TINY]);
	EXPECT_EQ(getter(*ret), getter(array[ARRAY_TINY]));
	EXPECT_TRUE(std::equal(array(), array() + ARRAY_TINY + 1, c.begin()));
	EXPECT_EQ(c.size(), size_type(11));
	// Failure insert (no duplicate)
	ret = c.insert(hint, array[ARRAY_TINY]);
	EXPECT_EQ(getter(*ret), getter(array[ARRAY_TINY]));
	EXPECT_TRUE(std::equal(array(), array() + ARRAY_TINY + 1, c.begin()));
	if (ACT::allowsDuplicate<TypeParam>::value) {
		EXPECT_EQ(*std::next(c.end(), -1), array[ARRAY_TINY]);
		EXPECT_EQ(*std::next(c.end(), -2), array[ARRAY_TINY]);
		EXPECT_EQ(c.size(), size_type(12));
	}
	else
		EXPECT_EQ(c.size(), size_type(11));
}


TYPED_TEST_P(actModifiersTests, InsertRange)
{
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::iterator		iterator;

	arrayGenerator<value_type>					array;
	ACT::getValue<value_type>					getter;
	TypeParam	REF 							c = this->container;
	iterator									ret;

	// Insert Range of duplicates
	std::vector<value_type>						range(10, array[ARRAY_TINY]);
	c.insert(range.begin(), range.end());
	if (ACT::allowsDuplicate<TypeParam>::value)
		EXPECT_EQ(c.size(), size_type(20));
	else
		EXPECT_EQ(c.size(), size_type(11));
	// Insert nothing but duplicates
	c.insert(range.begin(), range.end());
	if (ACT::allowsDuplicate<TypeParam>::value)
		EXPECT_EQ(c.size(), size_type(30));
	else
		EXPECT_EQ(c.size(), size_type(11));
	// Insert valid range of numbers
	std::vector<value_type> secondRange(array() + ARRAY_TINY + 1, array() + ARRAY_SMOL);
	c.insert(secondRange.begin(), secondRange.end());
	if (ACT::allowsDuplicate<TypeParam>::value) {
		EXPECT_EQ(c.size(), size_type(69));
		iterator it = c.begin();
		for (int i = 0; i < ARRAY_TINY; ++i, ++it)
			EXPECT_EQ(getter(*it), getter(array[i]));
		for (int i = 0; i < 20; ++i, ++it)
			EXPECT_EQ(getter(*it), getter(array[ARRAY_TINY]));
		for (int i = ARRAY_TINY + 1; i < ARRAY_SMOL; ++i, ++it)
			EXPECT_EQ(getter(*it), getter(array[i]));
	}
	else {
		EXPECT_EQ(c.size(), size_type(50));
		EXPECT_TRUE(std::equal(array(), array() + ARRAY_SMOL, c.begin()));
	}
}


TYPED_TEST_P(actModifiersTests, ErasePos)
{
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::value_type		value_type;

	arrayGenerator<value_type>					array;
	TypeParam	REF 							c = this->container;

	// Erase from begin
	c.erase(c.begin());
	EXPECT_EQ(c.size(), size_type(9));
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
	// Erase from end
	c.erase(std::next(c.end(), -1));
	EXPECT_EQ(c.size(), size_type(8));
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY - 1));
	// Erase from middle
	c.erase(std::next(c.begin(), 4));
	EXPECT_EQ(c.size(), size_type(7));
	EXPECT_TRUE(std::equal(array() + 1, array() + 4, c.begin()));
	EXPECT_TRUE(std::equal(array() + 6, array() + ARRAY_TINY - 1, std::next(c.begin(), 4)));
}


TYPED_TEST_P(actModifiersTests, EraseKey)
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
	EXPECT_EQ(c.size(), size_type(9));
	EXPECT_EQ(ret, size_type(1));
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
	// Erase invalid key
	ret = c.erase(keyArray[0]);
	EXPECT_EQ(c.size(), size_type(9));
	EXPECT_EQ(ret, size_type(0));
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
	if (!ACT::allowsDuplicate<TypeParam>::value)
		return ;
	// Remove multiple key
	for (int i = 0; i < 10; ++i)
		c.insert(array[0]);
	ret = c.erase(keyArray[0]);
	EXPECT_EQ(ret, size_type(10));
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
}


TYPED_TEST_P(actModifiersTests, EraseRange)
{
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::value_type		value_type;

	arrayGenerator<value_type>					array;
	TypeParam	REF 							c = this->container;
	TypeParam		 							cCopy = c;

	// // Erase Single from begin
	// c.erase(c.begin(), std::next(c.begin()));
	// EXPECT_EQ(c.size(), size_type(9));
	// EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
	// // Erase Single from end
	// c.erase(std::next(c.end(), -1), c.end());
	// EXPECT_EQ(c.size(), size_type(8));
	// EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY - 1));
	// // Erase Single from middle
	// c.erase(std::next(c.begin(), 4), std::next(c.begin(), 5));
	// EXPECT_EQ(c.size(), size_type(7));
	// EXPECT_TRUE(std::equal(array() + 1, array() + 4, c.begin()));
	// EXPECT_TRUE(std::equal(array() + 6, array() + ARRAY_TINY - 1, std::next(c.begin(), 4)));

	// Multiple erases
	c = cCopy;

	// Erase from begin
	c.erase(c.begin(), std::next(c.begin(), 2));
	EXPECT_EQ(c.size(), size_type(8));
	EXPECT_EQ(c, TypeParam(array() + 2, array() + ARRAY_TINY));
	// Erase from end
	c.erase(std::next(c.end(), -2), c.end());
	EXPECT_EQ(c.size(), size_type(6));
	EXPECT_EQ(c, TypeParam(array() + 2, array() + ARRAY_TINY - 2));
	// Erase from middle
	c.erase(std::next(c.begin(), 2), std::next(c.begin(), 4));
	EXPECT_EQ(c.size(), size_type(4));
	EXPECT_TRUE(std::equal(array() + 2, array() + 4, c.begin()));
	EXPECT_TRUE(std::equal(array() + 6, array() + ARRAY_TINY - 2, std::next(c.begin(), 2)));


}


TYPED_TEST_P(actModifiersTests, Swap)
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


TYPED_TEST_P(actModifiersTests, Clear)
{
	TypeParam REF	c = this->container;

	EXPECT_EQ(c.empty(), false);
	c.clear();
	EXPECT_EQ(c.empty(), true);
	c.clear();
	EXPECT_EQ(c.empty(), true);
}


REGISTER_TYPED_TEST_CASE_P(
	actModifiersTests,
	InsertSingle,
	InsertHint,
	InsertRange,
	ErasePos,
	EraseKey,
	EraseRange,
	Swap,
	Clear
);


INSTANTIATE_TYPED_TEST_CASE_P(
	AssociativeContainers,
	actModifiersTests,
	associativeContainers_type
);


#endif //ACT_MODIFIERS_TPP