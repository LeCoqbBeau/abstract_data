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
void
hidden::sct_pushFrontTest(TypeParam REF container)
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
void
hidden::sct_popFrontTest(TypeParam REF container)
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
	typedef typename TypeParam::size_type	size_type;
	typedef typename TypeParam::iterator	iterator;
	arrayGenerator<value_type>				array;
	TypeParam REF							c = this->container;

	// Insert at the back
	iterator inserted = c.insert(c.end(), array[ARRAY_TINY]);
	EXPECT_EQ(*inserted, array[ARRAY_TINY]);
	EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_TINY + 1));
	// Insert at the front
	c = TypeParam(array() + 1, array() + 1 + ARRAY_TINY);
	inserted = c.insert(c.begin(), array[0]);
	EXPECT_EQ(*inserted, array[0]);
	EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_TINY + 1));
	// Insert in the middle
	c = TypeParam(array(), array() + ARRAY_TINY);
	iterator fifthElement = std::next(c.begin(), 5);
	inserted = c.insert(fifthElement, array[5]);
	EXPECT_EQ(*inserted, array[5]);
	iterator it = c.begin();
	int i;
	for (i = 0; i < 5; ++i, ++it) {
		EXPECT_EQ(*it, array[i]);
	}
	EXPECT_EQ(*it++, array[i++]);
	for (++it; i < ARRAY_TINY; ++i, ++it)
		EXPECT_EQ(*it, array[i]);
	// Insert at the back in empty container
	c = TypeParam();
	inserted = c.insert(c.end(), array[0]);
	EXPECT_EQ(*inserted, array[0]);
	EXPECT_EQ(c.size(), static_cast<size_type>(1));
	// Insert at the front in empty container
	c = TypeParam();
	inserted = c.insert(c.begin(), array[ARRAY_TINY]);
	EXPECT_EQ(*inserted, array[ARRAY_TINY]);
	EXPECT_EQ(c.size(), static_cast<size_type>(1));
}


TYPED_TEST_P(sctModifiersTests, InsertFill)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::size_type	size_type;
	typedef typename TypeParam::iterator	iterator;
	arrayGenerator<value_type>				array;
	TypeParam const							copy	= this->container;
	TypeParam REF							c		= this->container;
	TypeParam const							target(10, array[ARRAY_TINY]);

	// Insert Single at the back
	c.insert(c.end(), 1, array[ARRAY_TINY]);
	EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_TINY + 1));
	// Insert Multiple at the back
	c = copy;
	c.insert(c.end(), 10, array[ARRAY_TINY]);
	iterator tenth = std::next(c.begin(), 10);
	EXPECT_TRUE(std::equal(tenth, c.end(), target.begin()));
	EXPECT_EQ(c.size(), size_type(20));
	// Insert Single at the front
	c = TypeParam(array() + 1, array() + 1 + ARRAY_TINY);
	c.insert(c.begin(), 1, array[0]);
	EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_TINY + 1));
	// Insert Multiple at the front
	c = TypeParam(10, array[ARRAY_TINY]);
	c.insert(c.begin(), 10, array[ARRAY_TINY]);
	EXPECT_EQ(c, TypeParam(20, array[ARRAY_TINY]));
	// Insert Single at the middle
	tenth = std::next(c.begin(), 10);
	c.insert(tenth, 1, array[1]); // this can cause it to be invalidated
	tenth = std::next(c.begin(), 10);
	EXPECT_TRUE(std::equal(c.begin(), tenth, target.begin()));
	EXPECT_EQ(*tenth, array[1]);
	++tenth;
	EXPECT_TRUE(std::equal(tenth, c.end(), target.begin()));
	EXPECT_EQ(c.size(), size_type(21));
	// Insert Multiple at the middle
	c.insert(tenth, 9, array[1]);
	tenth = std::next(c.begin(), 10);
	iterator twentieth = std::next(c.begin(), 20);
	EXPECT_TRUE(std::equal(c.begin(), tenth, target.begin()));
	EXPECT_TRUE(std::equal(tenth, twentieth, TypeParam(10, array[1]).begin()));
	EXPECT_TRUE(std::equal(twentieth, c.end(), target.begin()));
	EXPECT_EQ(c.size(), size_type(30));
}


TYPED_TEST_P(sctModifiersTests, EraseSingle)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::size_type	size_type;
	typedef typename TypeParam::iterator	iterator;
	arrayGenerator<value_type>				array;
	TypeParam REF							c		= this->container;

	// Erase from front
	iterator follower = c.erase(c.begin());
	EXPECT_EQ(*follower, array[1]);
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
	// Erase from back
	follower = c.erase(--c.end());
	EXPECT_TRUE(follower == c.end());
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY - 1));
	// Erase from middle
	iterator toErase = std::next(c.begin(), 5);
	follower = c.erase(toErase);
	EXPECT_TRUE(std::equal(c.begin(), follower, TypeParam(array() + 1, array() + 6).begin()));
	EXPECT_EQ(*follower, array[7]);
	EXPECT_TRUE(std::equal(++follower, c.end(), TypeParam(array() + 8, array() + ARRAY_TINY - 1).begin()));
	EXPECT_EQ(c.size(), size_type(7));
}


TYPED_TEST_P(sctModifiersTests, EraseRange) {
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::size_type	size_type;
	typedef typename TypeParam::iterator	iterator;
	arrayGenerator<value_type>				array;
	TypeParam const							copy	= this->container;
	TypeParam REF							c		= this->container;

	iterator limit;
	// Erase single from front
	iterator follower = c.erase(c.begin(), ++c.begin());
	EXPECT_EQ(*follower, array[1]);
	EXPECT_EQ(c, TypeParam(array() + 1, array() + ARRAY_TINY));
	// Erase multiple from front
	limit = std::next(c.begin(), 3);
	follower = c.erase(c.begin(), limit);
	EXPECT_EQ(*follower, array[4]);
	EXPECT_EQ(c, TypeParam(array() + 4, array() + ARRAY_TINY));
	// Erase single from back
	follower = c.erase(--c.end(), c.end());
	EXPECT_TRUE(follower == c.end());
	EXPECT_EQ(c, TypeParam(array() + 4, array() + ARRAY_TINY - 1));
	// Erase multiple from back
	limit = std::next( c.end(), -3);
	follower = c.erase(limit, c.end());
	EXPECT_TRUE(follower == c.end());
	EXPECT_EQ(c, TypeParam(array() + 4, array() + ARRAY_TINY - 4));
	// Erase single from the middle
	c = copy;
	limit = std::next(c.begin(), 5);
	iterator rude = std::next(c.begin(), 6);
	follower = c.erase(limit, rude);
	EXPECT_TRUE(std::equal(c.begin(), follower, TypeParam(array(), array() + 5).begin()));
	EXPECT_EQ(*follower, array[6]);
	EXPECT_TRUE(std::equal(follower, c.end(), TypeParam(array() + 6, array() + ARRAY_TINY).begin()));
	EXPECT_EQ(c.size(), size_type(9));
	// Erase multiple from the middle
	iterator pos;
	pos = std::next(c.begin(), 2);
	limit = std::next(c.begin(), 5);
	follower = c.erase(pos, limit);
	EXPECT_TRUE(std::equal(c.begin(), follower, TypeParam(array(), array() + 2).begin()));
	EXPECT_EQ(*follower, array[6]);
	EXPECT_TRUE(std::equal(follower, c.end(), TypeParam(array() + 6, array() + ARRAY_TINY).begin()));
	EXPECT_EQ(c.size(), size_type(6));
}


TYPED_TEST_P(sctModifiersTests, Swap)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam										other(ARRAY_TINY, array[1]);
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


TYPED_TEST_P(sctModifiersTests, Resize)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::size_type	size_type;

	arrayGenerator<value_type>	array;
	TypeParam REF				c = this->container;

	// Upsize with default value
	ASSERT_EQ(c.size(), size_type(10));
	c.resize(20);
	EXPECT_EQ(c.size(), size_type(20));
	EXPECT_TRUE(std::equal(std::next(c.begin(), 10), c.end(), TypeParam(10, value_type()).begin()));
	// Upsize with chosen value
	c.resize(30, array[ARRAY_SMOL]);
	EXPECT_EQ(c.size(), size_type(30));
	EXPECT_TRUE(std::equal(std::next(c.begin(), 20), c.end(), TypeParam(10, array[ARRAY_SMOL]).begin()));
	// Downsize
	c.resize(10, array[ARRAY_SMOL]);
	EXPECT_EQ(c, TypeParam(array(), array() + ARRAY_TINY));
}


TYPED_TEST_P(sctModifiersTests, Clear)
{
	TypeParam REF	c = this->container;

	EXPECT_EQ(c.empty(), false);
	c.clear();
	EXPECT_EQ(c.empty(), true);
	c.clear();
	EXPECT_EQ(c.empty(), true);
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
	InsertFill,
	EraseSingle,
	EraseRange,
	Swap,
	Resize,
	Clear
);


INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	sctModifiersTests,
	sequenceContainers_type
);


#endif //SCT_MODIFIERS_TPP