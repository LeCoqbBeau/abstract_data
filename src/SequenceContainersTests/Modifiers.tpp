//
// Created by mscheman on 2/16/26.
//

#ifndef SCT_MODIFIERS_TPP
#define SCT_MODIFIERS_TPP

template <typename Container>
class sctModifiersTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		// Setup
		sctModifiersTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};

// Can you please not look at this thank you :3
namespace hidden {
template <typename TypeParam>
void sct_pushFrontTest(TypeParam REF container);
template <typename TypeParam>
void sct_popFrontTest(TypeParam REF container);
template <typename TypeParam>
struct sct_hasPushFront
{
	void operator() (TypeParam REF container) { sct_pushFrontTest(container); }
};
template <typename value_type>
struct sct_hasPushFront<ns::vector<value_type> >
{
	void operator() (ns::vector<value_type> REF) { SUCCEED(); }
};
template <typename TypeParam>
void sct_popFrontTest(TypeParam REF container);
template <typename TypeParam>
struct sct_hasPopFront
{
	void operator() (TypeParam REF container) { sct_popFrontTest(container); }
};
template <typename value_type>
struct sct_hasPopFront<ns::vector<value_type> >
{
	void operator() (ns::vector<value_type> REF) { SUCCEED(); }
};
}
// You can look now


template <typename TypeParam>
void hidden::sct_pushFrontTest(TypeParam REF container)
{
	typedef typename TypeParam::value_type	value_type;
	arrayGenerator<value_type>				array;

	TypeParam	goal(array(), array() + ARRAY_SMOL);
	container.assign(array() + ARRAY_SMOL - ARRAY_TINY, array() + ARRAY_SMOL);
	for (int i = ARRAY_SMOL - ARRAY_TINY - 1; i >= 0; --i)
		container.push_front(array[i]);
	EXPECT_EQ(container, goal);
}


template <typename TypeParam>
void hidden::sct_popFrontTest(TypeParam REF container)
{
	typedef typename TypeParam::value_type	value_type;
	arrayGenerator<value_type>				array;

	TypeParam	goal(array() + ARRAY_TINY, array() + ARRAY_SMOL);
	container.assign(array(), array() + ARRAY_SMOL);
	for (int i = 0; i < ARRAY_TINY; ++i)
		container.pop_front();
	EXPECT_EQ(container, goal);
}


TYPED_TEST_CASE_P(sctModifiersTests);


TYPED_TEST_P(sctModifiersTests, AssignFill)
{
	typedef typename TypeParam::value_type	value_type;
	arrayGenerator<value_type>	array;

	TypeParam const	target(57, array[3]);
	TypeParam		victim;
	EXPECT_NE(victim, target);
	victim.assign(57, array[3]);
	EXPECT_NE(this->container, target);
	this->container.assign(57, array[3]);
	EXPECT_EQ(this->container, target);
}


TYPED_TEST_P(sctModifiersTests, AssignRange)
{
	typedef typename TypeParam::value_type	value_type;
	value_type const*			first = arrayGenerator<value_type>()();
	value_type const*			last = first + ARRAY_SMOL;

	TypeParam	target(first, last);
	TypeParam	victim;
	EXPECT_NE(victim, target);
	victim.assign(first, last);
	EXPECT_NE(this->container, target);
	this->container.assign(first, last);
	EXPECT_EQ(this->container, target);
}


TYPED_TEST_P(sctModifiersTests, PushBack)
{
	typedef typename TypeParam::value_type	value_type;
	arrayGenerator<value_type>				array;

	TypeParam	goal(array(), array() + ARRAY_SMOL);
	for (int i = ARRAY_TINY; i < ARRAY_SMOL; ++i)
		this->container.push_back(array[i]);
	EXPECT_EQ(this->container, goal);
}


TYPED_TEST_P(sctModifiersTests, PushFront)
{
	hidden::sct_hasPushFront<TypeParam>	tester;

	tester(this->container);
}


TYPED_TEST_P(sctModifiersTests, PopBack)
{
	typedef typename TypeParam::value_type	value_type;
	arrayGenerator<value_type>				array;

	TypeParam	goal(array(), array() + ARRAY_SMOL);
	for (int i = ARRAY_TINY; i < ARRAY_SMOL; ++i)
		this->container.push_back(array[i]);
	EXPECT_EQ(this->container, goal);
}


TYPED_TEST_P(sctModifiersTests, PopFront)
{
	hidden::sct_hasPopFront<TypeParam>	tester;

	tester(this->container);
}


TYPED_TEST_P(sctModifiersTests, InsertSingle)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::iterator	iterator;
	arrayGenerator<value_type>				array;

	iterator inserted = this->container.insert(this->container.end(), array[ARRAY_TINY]);
	EXPECT_EQ(*inserted, array[ARRAY_TINY]);
	EXPECT_EQ(this->container, TypeParam(array(), array() + ARRAY_TINY + 1));
	this->container = TypeParam(array() + 1, array() + 1 + ARRAY_TINY);
	inserted = this->container.insert(this->container.begin(), array[0]);
	EXPECT_EQ(*inserted, array[0]);
	EXPECT_EQ(this->container, TypeParam(array(), array() + ARRAY_TINY + 1));
	this->container = TypeParam(array(), array() + ARRAY_TINY);
	iterator fifthElement = this->container.begin();
	std::advance(fifthElement, 5);
	inserted = this->container.insert(fifthElement, array[5]);
	EXPECT_EQ(*inserted, array[5]);
	iterator it = this->container.begin();
	int i;
	for (i = 0; i < 5; ++i, ++it)
		EXPECT_EQ(*it, array[i]);
	EXPECT_EQ(*it++, array[i++]);
	for (++it; i < ARRAY_TINY; ++i, ++it)
		EXPECT_EQ(*it, array[i]);
}


TYPED_TEST_P(sctModifiersTests, InsertFill)
{
}


REGISTER_TYPED_TEST_CASE_P(
	sctModifiersTests,
	AssignFill,
	AssignRange,
	PushBack,
	PushFront,
	PopBack,
	PopFront,
	InsertSingle,
	InsertFill
);


INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	sctModifiersTests,
	testContainers_type
);


#endif //SCT_MODIFIERS_TPP