//
// Created by mscheman on 2/16/26.
//

#ifndef GT_ELEMENT_ACCESS_TPP
#define GT_ELEMENT_ACCESS_TPP


template <typename Container>
class gtElementAccessTests : public ::testing::Test
{
	public:
		// Helper Typedefs
		typedef typename Container::value_type	value_type;

		gtElementAccessTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + Container::size()) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(gtElementAccessTests);


TYPED_TEST_P(gtElementAccessTests, SubscriptOperator)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c	= this->container;

	if (TypeParam::empty())
		return SUCCEED();
	for (unsigned int m = 0; m < TypeParam::rows(); ++m)
		for (unsigned int n = 0; n < TypeParam::cols(); ++n)
			c[m][n] = array[m * TypeParam::cols() + n + 1];
	for (unsigned int m = 0; m < TypeParam::rows(); ++m) {
		EXPECT_EQ(c[m], &c.begin(m)._data[c.begin(m)._pos]);
		for (unsigned int n = 0; n < TypeParam::cols(); ++n)
			EXPECT_EQ(c[m][n], array[m * TypeParam::cols() + n + 1]);
	}
}


TYPED_TEST_P(gtElementAccessTests, ConstSubscriptOperator)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam CREF									c	= this->container;

	if (TypeParam::empty())
		return SUCCEED();
	for (unsigned int m = 0; m < TypeParam::rows(); ++m) {
		EXPECT_EQ(c[m], &c.begin(m)._data[c.begin(m)._pos]);
		for (unsigned int n = 0; n < TypeParam::cols(); ++n)
			EXPECT_EQ(c[m][n], array[m * TypeParam::cols() + n]);
	}
}


TYPED_TEST_P(gtElementAccessTests, At)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c	= this->container;

	if (TypeParam::empty())
		return SUCCEED();
	for (unsigned int m = 0; m < TypeParam::rows(); ++m)
		for (unsigned int n = 0; n < TypeParam::cols(); ++n)
			c.at(m, n) = array[m * TypeParam::cols() + n + 1];
	for (unsigned int m = 0; m < TypeParam::rows(); ++m)
		for (unsigned int n = 0; n < TypeParam::cols(); ++n)
			EXPECT_EQ(c.at(m, n), array[m * TypeParam::cols() + n + 1]);
	EXPECT_THROW(c.at(TypeParam::rows(), 0), ft::out_of_range);
	EXPECT_THROW(c.at(0, TypeParam::cols()), ft::out_of_range);
}


TYPED_TEST_P(gtElementAccessTests, ConstAt)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam CREF									c	= this->container;

	if (TypeParam::empty())
		return SUCCEED();
	for (unsigned int m = 0; m < TypeParam::rows(); ++m)
		for (unsigned int n = 0; n < TypeParam::cols(); ++n)
			EXPECT_EQ(c.at(m, n), array[m * TypeParam::cols() + n]);
	EXPECT_THROW(c.at(TypeParam::rows(), 0), ft::out_of_range);
	EXPECT_THROW(c.at(0, TypeParam::cols()), ft::out_of_range);
}


TYPED_TEST_P(gtElementAccessTests, Front)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c	= this->container;

	if (c.empty())
		return SUCCEED();
	EXPECT_EQ(c.front(), array[0]);
	EXPECT_EQ(&c.front(), &*c.begin());
	EXPECT_EQ(&c.front(), &*c.begin(0));
	*c.begin() = array[c.size()];
	EXPECT_EQ(c.front(), array[c.size()]);
}


TYPED_TEST_P(gtElementAccessTests, ConstFront)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam CREF									c	= this->container;

	if (c.empty())
		return SUCCEED();
	EXPECT_EQ(c.front(), array[0]);
	EXPECT_EQ(&c.front(), &*c.begin());
	EXPECT_EQ(&c.front(), &*c.begin(0));
}


TYPED_TEST_P(gtElementAccessTests, Back)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c	= this->container;

	if (c.empty())
		return SUCCEED();
	typename TypeParam::iterator gridLast = std::next(c.end(), -1);
	typename TypeParam::iterator rowLast = std::next(c.end(TypeParam::rows() - 1), -1);
	EXPECT_EQ(c.back(), array[c.size() - 1]);
	EXPECT_EQ(&c.back(), &*gridLast);
	EXPECT_EQ(&c.back(), &*rowLast);
	*gridLast = array[c.size()];
	EXPECT_EQ(c.back(), array[c.size()]);
}


TYPED_TEST_P(gtElementAccessTests, ConstBack)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam CREF									c	= this->container;

	if (c.empty())
		return SUCCEED();
	typename TypeParam::const_iterator gridLast	= std::next(c.end(), -1);
	typename TypeParam::const_iterator rowLast	= std::next(c.end(TypeParam::rows() - 1), -1);
	EXPECT_EQ(c.back(), array[c.size() - 1]);
	EXPECT_EQ(&c.back(), &*gridLast);
	EXPECT_EQ(&c.back(), &*rowLast);
}


TYPED_TEST_P(gtElementAccessTests, FrontRow)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c	= this->container;

	if (c.empty())
		return SUCCEED();
	for (unsigned int m = 0; m < TypeParam::rows(); ++m) {
		EXPECT_EQ(&c.front(m), &*c.begin(m));
		EXPECT_EQ(c.front(m), array[m * TypeParam::cols()]);
		*c.begin(m) = array[TypeParam::size() + m];
		EXPECT_EQ(c.front(m), array[TypeParam::size() + m]);
	}

}


TYPED_TEST_P(gtElementAccessTests, ConstFrontRow)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam CREF									c	= this->container;

	if (c.empty())
		return SUCCEED();
	for (unsigned int m = 0; m < TypeParam::rows(); ++m) {
		EXPECT_EQ(&c.front(m), &*c.begin(m));
		EXPECT_EQ(c.front(m), array[m * TypeParam::cols()]);
	}
}


TYPED_TEST_P(gtElementAccessTests, BackRow)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam REF									c	= this->container;

	if (c.empty())
		return SUCCEED();
	typename TypeParam::iterator rowLast;
	for (unsigned int m = 0; m < TypeParam::rows(); ++m) {
		rowLast = std::next(c.end(m), -1);
		EXPECT_EQ(&c.back(m), &*rowLast);
		EXPECT_EQ(c.back(m), array[m * TypeParam::cols() + TypeParam::cols() - 1]);
		*rowLast = array[TypeParam::size() - m];
		EXPECT_EQ(c.back(m), array[TypeParam::size() - m]);
	}
}


TYPED_TEST_P(gtElementAccessTests, ConstBackRow)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam CREF									c	= this->container;

	if (c.empty())
		return SUCCEED();
	typename TypeParam::const_iterator rowLast;
	for (unsigned int m = 0; m < TypeParam::rows(); ++m) {
		rowLast = std::next(c.end(m), -1);
		EXPECT_EQ(&c.back(m), &*rowLast);
		EXPECT_EQ(c.back(m), array[m * TypeParam::cols() + TypeParam::cols() - 1]);
	}
}


REGISTER_TYPED_TEST_CASE_P(
	gtElementAccessTests,
	SubscriptOperator,
	ConstSubscriptOperator,
	At,
	ConstAt,
	Front,
	ConstFront,
	Back,
	ConstBack,
	FrontRow,
	ConstFrontRow,
	BackRow,
	ConstBackRow
);


INSTANTIATE_TYPED_TEST_CASE_P(
	GridContainer,
	gtElementAccessTests,
	testGrid_type
);


#endif //GT_ELEMENT_ACCESS_TPP