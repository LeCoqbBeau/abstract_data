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
	std::vector<value_type>						range(10, array[0]);
	
}


TYPED_TEST_P(actModifiersTests, ErasePos)
{

}


TYPED_TEST_P(actModifiersTests, EraseKey)
{

}


TYPED_TEST_P(actModifiersTests, EraseRange)
{

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