//
// Created by mscheman on 3/2/26.
//

#ifndef AdCT_COMMON_MEMBER_FUNCTIONS_TPP
#define AdCT_COMMON_MEMBER_FUNCTIONS_TPP


// DONT LOOK PLZ VERY UGLY
namespace AdCT {
template <typename AdaptorContainer>
struct builder
{
	typedef typename AdaptorContainer::container_type	container_type;
	template <typename InputIt>
	AdaptorContainer operator()(InputIt first, InputIt last) const { return AdaptorContainer(container_type(first, last)); }
};
template <typename T, typename Container, typename Compare>
struct builder<ns::priority_queue<T, Container, Compare> >
{
	template <typename InputIt>
	ns::priority_queue<T, Container, Compare> operator()(InputIt first, InputIt last) const { return ns::priority_queue<T, Container, Compare>(Compare(), Container(first, last)); }
};
template <typename TypeParam>
struct getTop
{
	typename TypeParam::value_type CREF operator()(TypeParam CREF c) const { return c.top(); }
};
template <typename T, typename Container>
struct getTop<ns::queue<T, Container> >
{
	T CREF operator()(ns::queue<T, Container> CREF c) const { return c.back(); }
};
}
// LOOK AGAIN TY


template <typename Container>
class adctCommonMemberFunctions : public ::testing::Test
{
	public:
		// Helper Typedef
		typedef typename Container::value_type value_type;

		// Setup
		adctCommonMemberFunctions() : container(AdCT::builder<Container>()(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY)) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(adctCommonMemberFunctions);


TYPED_TEST_P(adctCommonMemberFunctions, Empty)
{
	TypeParam emptyContainer;

	EXPECT_TRUE(emptyContainer.empty());
	EXPECT_FALSE(this->container.empty());
}


TYPED_TEST_P(adctCommonMemberFunctions, Size)
{
	typedef typename TypeParam::size_type	size_type;

	TypeParam emptyContainer;

	EXPECT_EQ(emptyContainer.size(), size_type(0));
	EXPECT_EQ(this->container.size(), size_type(ARRAY_TINY));
}


TYPED_TEST_P(adctCommonMemberFunctions, Push)
{
	typedef typename TypeParam::size_type	size_type;
	typedef typename TypeParam::value_type	value_type;

	arrayGenerator<value_type>	array;
	TypeParam					c;

	for (size_type i = 0; i < ARRAY_TINY; ++i) {
		c.push(array[i]);
		EXPECT_EQ(AdCT::getTop<TypeParam>()(c), array[i]);
		EXPECT_EQ(c.size(), i + 1);
	}
}


TYPED_TEST_P(adctCommonMemberFunctions, Pop)
{
	typedef typename TypeParam::size_type	size_type;
	typedef typename TypeParam::value_type	value_type;

	arrayGenerator<value_type>	array;
	TypeParam					c;

	for (size_type i = 0; i < ARRAY_TINY; ++i) {
		c.push(array[i]);
		EXPECT_EQ(AdCT::getTop<TypeParam>()(c), array[i]);
		EXPECT_EQ(c.size(), i + 1);
	}
	for (size_type i = 0; i < ARRAY_TINY; ++i) {
		c.pop();
		EXPECT_EQ(c.size(), ARRAY_TINY - i - 1);
	}
}


REGISTER_TYPED_TEST_CASE_P(
	adctCommonMemberFunctions,
	Empty,
	Size,
	Push, // also test Top or back
	Pop
);


INSTANTIATE_TYPED_TEST_CASE_P(
	AdaptorContainers,
	adctCommonMemberFunctions,
	adaptorContainers_type
);


#endif //AdCT_COMMON_MEMBER_FUNCTIONS_TPP