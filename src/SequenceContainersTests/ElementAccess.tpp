//
// Created by mscheman on 2/16/26.
//

#ifndef SCT_ELEMENT_ACCESS_TPP
#define SCT_ELEMENT_ACCESS_TPP


template <typename Container>
class sctElementAccess : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		sctElementAccess() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_SIZE) {}

		// Attributes
		Container container;
};


// Can you please not look at this thank you :3
template <typename TypeParam, bool subscriptOperator>
void sct_randomLookupTest(TypeParam CREF container);
template <typename TypeParam, bool subscriptOperator>
void sct_randomModifyTest(TypeParam REF container);

template <bool subscriptOperator>
struct sct_randomAccessor {};
template <>
struct sct_randomAccessor<true>
{
	template <typename TypeParam>
	typename TypeParam::value_type REF	operator() (TypeParam REF container, unsigned int i) { return container[i]; }
	template <typename TypeParam>
	typename TypeParam::value_type CREF	operator() (TypeParam CREF container, unsigned int i) { return container[i]; }
};
template <>
struct sct_randomAccessor<false>
{
	template <typename TypeParam>
	typename TypeParam::value_type REF	operator() (TypeParam REF container, unsigned int i) { return container.at(i); }
	template <typename TypeParam>
	typename TypeParam::value_type CREF	operator() (TypeParam CREF container, unsigned int i) { return container.at(i); }
};
template <typename T, bool subscriptOperator>
struct sct_randomLookup
{
	void operator()(T CREF container) const { sct_randomLookupTest<T, subscriptOperator>(container); }
};
template <typename T, bool subscriptOperator>
struct sct_randomLookup<ns::list<T>, subscriptOperator>
{
	void operator()(ns::list<T> CREF) const { return SUCCEED(); }
};
template <typename T, bool subscriptOperator>
struct sct_randomModify
{
	void operator()(T REF container) const { sct_randomModifyTest<T, subscriptOperator>(container); }
};
template <typename T, bool subscriptOperator>
struct sct_randomModify<ns::list<T>, subscriptOperator>
{
	void operator()(ns::list<T> REF) const { return SUCCEED(); }
};


template <typename TypeParam, bool subscriptOperator>
void sct_randomLookupTest(TypeParam CREF container)
{
	sct_randomAccessor<subscriptOperator> accessor;
	arrayGenerator<typename TypeParam::value_type> array;
	for (int i = 0; i < ARRAY_SIZE; ++i)
		EXPECT_EQ(accessor(container, i), array[i]);
	if (subscriptOperator == false)
		EXPECT_THROW(container.at(-1), ns::out_of_range);
}


template <typename TypeParam, bool subscriptOperator>
void sct_randomModifyTest(TypeParam REF container)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::const_iterator	const_iterator;
	sct_randomAccessor<subscriptOperator>	accessor;
	arrayGenerator<value_type>				array;
	wrapAround<value_type>					wrap;

	for (int i = 0; i < ARRAY_SIZE; ++i)
		accessor(container, i) = wrap(array(), i, 4);
	int i = 0;
	for (const_iterator cit = container.begin(); cit != container.end(); ++cit) {
		EXPECT_EQ(*cit, wrap(array(), i, 4));
		++i;
	}
}


TYPED_TEST_CASE_P(sctElementAccess);


TYPED_TEST_P(sctElementAccess, SubscriptOperator)
{
	sct_randomLookup<TypeParam, true> testLookup;
	sct_randomModify<TypeParam, true> testModification;

	testLookup(this->container);
	testModification(this->container);
}


TYPED_TEST_P(sctElementAccess, At)
{
	sct_randomLookup<TypeParam, false> testLookup;
	sct_randomModify<TypeParam, false> testModification;

	testLookup(this->container);
	testModification(this->container);
}


TYPED_TEST_P(sctElementAccess, Front)
{
	arrayGenerator<typename TypeParam::value_type> array;

	EXPECT_EQ(&this->container.front(), &*this->container.begin());
	this->container.front() = array[8];
	EXPECT_EQ(*this->container.begin(), array[8]);
}


TYPED_TEST_P(sctElementAccess, Back)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	typedef typename TypeParam::const_iterator		const_iterator;

	const_iterator endIt = --this->container.end();
	EXPECT_EQ(&this->container.back(), &*endIt);
	this->container.back() = array[8];
	EXPECT_EQ(*endIt, array[8]);
}


REGISTER_TYPED_TEST_CASE_P(
	sctElementAccess,
	SubscriptOperator,
	At,
	Front,
	Back
);


INSTANTIATE_TYPED_TEST_CASE_P(
	SequenceContainers,
	sctElementAccess,
	testContainers_type
);




#endif //SCT_ELEMENT_ACCESS_TPP