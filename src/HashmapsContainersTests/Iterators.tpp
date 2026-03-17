	//
// Created by mscheman on 2/16/26.
//

#ifndef HCT_ITERATORS_TPP
#define HCT_ITERATORS_TPP


template <typename Container>
class hctIteratorsTests : public ::testing::Test
{
	// Helper Typedefs
	typedef typename Container::value_type	value_type;

	public:
		hctIteratorsTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(hctIteratorsTests);


TYPED_TEST_P(hctIteratorsTests, Loop)
{
	typedef typename TypeParam::iterator iterator;

	iterator it;
	for (it = this->container.begin(); it != this->container.end(); ++it)
		;
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(hctIteratorsTests, ConstLoop)
{
	typedef typename TypeParam::const_iterator const_iterator;

	const_iterator it;
	for (it = this->container.begin(); it != this->container.end(); ++it)
		;
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(hctIteratorsTests, Comparison)
{
	typedef typename TypeParam::iterator iterator;

	iterator first = this->container.begin();
	iterator last = std::next(this->container.begin(), 5);
	for (int i = 0; i < 5; ++i) {
		EXPECT_TRUE(first != last);
		++first;
	}
	EXPECT_TRUE(first == last);
}


TYPED_TEST_P(hctIteratorsTests, ArrowOperator)
{
	typedef typename TypeParam::iterator iterator;

	for (iterator it = this->container.begin(); it != this->container.end(); ++it)
		EXPECT_EQ(it.operator->(), &it.operator*());
}


REGISTER_TYPED_TEST_CASE_P(
	hctIteratorsTests,
	Loop,
	ConstLoop,
	Comparison,
	ArrowOperator
);


INSTANTIATE_TYPED_TEST_CASE_P(
	HashmapsContainers,
	hctIteratorsTests,
	hashmapsContainers_type
);


#endif //HCT_ITERATORS_TPP