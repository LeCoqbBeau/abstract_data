//
// Created by mscheman on 2/16/26.
//

#ifndef GT_ITERATORS_TPP
#define GT_ITERATORS_TPP


template <typename Container>
class gtIteratorsTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		gtIteratorsTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + Container::size()) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(gtIteratorsTests);


TYPED_TEST_P(gtIteratorsTests, Loop)
{
	typedef typename TypeParam::iterator iterator;

	iterator it;
	for (it = this->container.begin(); it != this->container.end(); ++it)
		;
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(gtIteratorsTests, RowLoop)
{
	typedef typename TypeParam::iterator iterator;

	iterator	it;
	for (unsigned int i = 0; i < TypeParam::rows(); ++i) {
		int pos = 0;
		for (it = this->container.begin(i); it != this->container.end(i); ++it) {
			EXPECT_EQ(it._pos, i * TypeParam::rows() + pos);
			++pos;
		}
		EXPECT_EQ(it, this->container.end(i));
	}
	if (!TypeParam::rows())
		return SUCCEED();
	EXPECT_EQ(it, this->container.end());
}


TYPED_TEST_P(gtIteratorsTests, ConstLoop)
{
	typedef typename TypeParam::const_iterator const_iterator;

	const_iterator it;
	for (it = this->container.begin(); it != this->container.end(); ++it)
		;
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(gtIteratorsTests, ReverseLoop)
{
	typedef typename TypeParam::reverse_iterator reverse_iterator;

	reverse_iterator it;
	for (it = this->container.rbegin(); it != this->container.rend(); ++it)
		;
	EXPECT_TRUE(it == this->container.rend());
}


TYPED_TEST_P(gtIteratorsTests, ConstReverseLoop)
{
	typedef typename TypeParam::const_reverse_iterator const_reverse_iterator;

	const_reverse_iterator it;
	for (it = this->container.rbegin(); it != this->container.rend(); ++it)
		;
	EXPECT_TRUE(it == this->container.rend());
}


TYPED_TEST_P(gtIteratorsTests, LoopModification)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::iterator	iterator;
	value_type const* array = arrayGenerator<value_type>()();


	iterator it;
	int i = 0;
	for (it = this->container.begin(); it != this->container.end(); ++it) {
		*it = wrapAround<value_type>()(array, i, 1);
		++i;
	}
	i = 0;
	for (it = this->container.begin(); it != this->container.end(); ++it) {
		EXPECT_EQ(*it, wrapAround<value_type>()(array, i, 1));
		++i;
	}
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(gtIteratorsTests, ReverseLoopModification)
{
	typedef typename TypeParam::value_type			value_type;
	typedef typename TypeParam::reverse_iterator	reverse_iterator;
	value_type const* array = arrayGenerator<value_type>()();

	reverse_iterator it;
	int i = ARRAY_TINY;
	for (it = this->container.rbegin(); it != this->container.rend(); ++it) {
		*it = wrapAround<value_type>()(array, i, -3);
		--i;
	}
	i = ARRAY_TINY;
	for (it = this->container.rbegin(); it != this->container.rend(); ++it) {
		EXPECT_EQ(*it, wrapAround<value_type>()(array, i, -3));
		--i;
	}
	EXPECT_TRUE(it == this->container.rend());
}


TYPED_TEST_P(gtIteratorsTests, BidirectionalTest)
{
	typedef typename TypeParam::iterator iterator;

	if (TypeParam::empty())
		return SUCCEED();
	iterator it = this->container.end();
	--it;
	EXPECT_EQ(*it, this->container.back());
}


TYPED_TEST_P(gtIteratorsTests, Comparison)
{
	typedef typename TypeParam::iterator iterator;

	iterator first = this->container.begin();
	iterator last = this->container.end();
	for (unsigned int i = 0; i < TypeParam::size(); ++i) {
		EXPECT_NE(first, last);
		++first;
	}
	EXPECT_EQ(first, last);
}


TYPED_TEST_P(gtIteratorsTests, ArrowOperator)
{
	typedef typename TypeParam::iterator iterator;

	for (iterator it = this->container.begin(); it != this->container.end(); ++it)
		EXPECT_EQ(it.operator->(), &it.operator*());
}


REGISTER_TYPED_TEST_CASE_P(
	gtIteratorsTests,
	Loop,
	RowLoop,
	ConstLoop,
	ReverseLoop,
	ConstReverseLoop,
	LoopModification,
	ReverseLoopModification,
	BidirectionalTest,
	Comparison,
	ArrowOperator
);


INSTANTIATE_TYPED_TEST_CASE_P(
	GridContainer,
	gtIteratorsTests,
	testGrid_type
);


#endif //GT_ITERATORS_TPP