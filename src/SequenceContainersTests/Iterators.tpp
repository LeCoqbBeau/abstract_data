	//
// Created by mscheman on 2/16/26.
//

#ifndef SEQUENCE_CONTAINERS_TESTS_ITERATORS_TPP
#define SEQUENCE_CONTAINERS_TESTS_ITERATORS_TPP

template <typename Container>
class sctIteratorsTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		sctIteratorsTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


template <typename T>
struct wrapAround
{
	T operator() (T const* array, int const index, int const offset) { return array[static_cast<unsigned int>(index + offset) % ARRAY_TINY]; }
};


TYPED_TEST_CASE_P(sctIteratorsTests);


TYPED_TEST_P(sctIteratorsTests, Loop)
{
	typedef typename TypeParam::iterator iterator;

	iterator it;
	for (it = this->container.begin(); it != this->container.end(); ++it)
		;
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(sctIteratorsTests, ConstLoop)
{
	typedef typename TypeParam::const_iterator const_iterator;

	const_iterator it;
	for (it = this->container.begin(); it != this->container.end(); ++it)
		;
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(sctIteratorsTests, ReverseLoop)
{
	typedef typename TypeParam::reverse_iterator reverse_iterator;

	reverse_iterator it;
	for (it = this->container.rbegin(); it != this->container.rend(); ++it)
		;
	EXPECT_TRUE(it == this->container.rend());
}


TYPED_TEST_P(sctIteratorsTests, ConstReverseLoop)
{
	typedef typename TypeParam::const_reverse_iterator const_reverse_iterator;

	const_reverse_iterator it;
	for (it = this->container.rbegin(); it != this->container.rend(); ++it)
		;
	EXPECT_TRUE(it == this->container.rend());
}


TYPED_TEST_P(sctIteratorsTests, LoopModification)
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


TYPED_TEST_P(sctIteratorsTests, ReverseLoopModification)
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


TYPED_TEST_P(sctIteratorsTests, BidirectionalTest)
{
	typedef typename TypeParam::iterator iterator;

	iterator it = this->container.end();
	--it;
	EXPECT_EQ(*it, this->container.back());
}


TYPED_TEST_P(sctIteratorsTests, Comparison)
{
	typedef typename TypeParam::iterator iterator;

	iterator first = this->container.begin();
	iterator last = this->container.end();
	for (int i = 0; i < 5; ++i) {
		EXPECT_TRUE(first != last);
		++first;
		--last;
	}
	EXPECT_TRUE(first == last);
}


TYPED_TEST_P(sctIteratorsTests, ArrowOperator)
{
	typedef typename TypeParam::iterator iterator;

	for (iterator it = this->container.begin(); it != this->container.end(); ++it)
		EXPECT_EQ(it.operator->(), &it.operator*());
}


REGISTER_TYPED_TEST_CASE_P(
	sctIteratorsTests,
	Loop,
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
	SequenceContainers,
	sctIteratorsTests,
	sequenceContainers_type
);


#endif //SEQUENCE_CONTAINERS_TESTS_ITERATORS_TPP