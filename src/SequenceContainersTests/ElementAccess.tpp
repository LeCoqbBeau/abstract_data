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

		sctElementAccess() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


// Can you please not look at this thank you :3
namespace SCT {
template <typename TypeParam, bool subscriptOperator>
void randomLookupTest(TypeParam CREF container);
template <typename TypeParam, bool subscriptOperator>
void randomModifyTest(TypeParam REF container);
template <bool subscriptOperator>
struct randomAccessor {};
template <>
struct randomAccessor<true>
{
	template <typename TypeParam>
	typename TypeParam::value_type REF	operator() (TypeParam REF container, unsigned int i) { return container[i]; }
	template <typename TypeParam>
	typename TypeParam::value_type CREF	operator() (TypeParam CREF container, unsigned int i) { return container[i]; }
};
template <>
struct randomAccessor<false>
{
	template <typename TypeParam>
	typename TypeParam::value_type REF	operator() (TypeParam REF container, unsigned int i) { return container.at(i); }
	template <typename TypeParam>
	typename TypeParam::value_type CREF	operator() (TypeParam CREF container, unsigned int i) { return container.at(i); }
};
template <typename T, bool subscriptOperator>
struct randomLookup
{
	void operator()(T CREF container) const { SCT::randomLookupTest<T, subscriptOperator>(container); }
};
template <typename T, bool subscriptOperator>
struct randomLookup<ns::list<T>, subscriptOperator>
{
	void operator()(ns::list<T> CREF) const { return SUCCEED(); }
};
template <typename T, bool subscriptOperator>
struct randomModify
{
	void operator()(T REF container) const { SCT::randomModifyTest<T, subscriptOperator>(container); }
};
template <typename T, bool subscriptOperator>
struct randomModify<ns::list<T>, subscriptOperator>
{
	void operator()(ns::list<T> REF) const { return SUCCEED(); }
};
}
// You can look now


template <typename TypeParam, bool subscriptOperator>
void SCT::randomLookupTest(TypeParam CREF container)
{
	SCT::randomAccessor<subscriptOperator> accessor;
	arrayGenerator<typename TypeParam::value_type> array;

	for (int i = 0; i < ARRAY_TINY; ++i)
		EXPECT_EQ(accessor(container, i), array[i]);
	if (subscriptOperator == false) { // what da hell???
		EXPECT_THROW(container.at(-1), ns::out_of_range);
	}
}


template <typename TypeParam, bool subscriptOperator>
void SCT::randomModifyTest(TypeParam REF container)
{
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::const_iterator	const_iterator;
	SCT::randomAccessor<subscriptOperator>	accessor;
	arrayGenerator<value_type>				array;
	wrapAround<value_type>					wrap;

	for (int i = 0; i < ARRAY_TINY; ++i)
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
	SCT::randomLookup<TypeParam, true> testLookup;
	SCT::randomModify<TypeParam, true> testModification;

	testLookup(this->container);
	testModification(this->container);
}


TYPED_TEST_P(sctElementAccess, At)
{
	SCT::randomLookup<TypeParam, false> testLookup;
	SCT::randomModify<TypeParam, false> testModification;

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
	sequenceContainers_type
);




#endif //SCT_ELEMENT_ACCESS_TPP