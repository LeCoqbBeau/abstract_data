//
// Created by mscheman on 3/2/26.
//

#ifndef AdCT_OUT_OF_CLASS_TPP
#define AdCT_OUT_OF_CLASS_TPP
#include "CommonMemberFunctions.tpp"


template <typename Container>
class adctOutOfClass : public ::testing::Test
{
	public:
		// Helper Typedef
		typedef typename Container::value_type value_type;

		// Setup
		adctOutOfClass() : container(AdCT::builder<Container>()(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY)) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(adctOutOfClass);


TYPED_TEST_P(adctOutOfClass, RelationalOperators)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam		a = AdCT::builder<TypeParam>()(array() + 1, array() + ARRAY_TINY + 1);
	TypeParam		b = AdCT::builder<TypeParam>()(array(), array() + ARRAY_TINY); // this is indeed c, but it's not a direct copy
	TypeParam REF	c = this->container;
	TypeParam		copy = c;

	// operator ==
	EXPECT_TRUE((a == b) == false);
	EXPECT_TRUE((b == c) == true);
	EXPECT_TRUE((c == copy) == true);
	// operator !=
	EXPECT_TRUE((a != b) == true);
	EXPECT_TRUE((b != c) == false);
	EXPECT_TRUE((c != copy) == false);
	// operator <
	EXPECT_TRUE((a < b) == false);
	EXPECT_TRUE((b < c) == false);
	EXPECT_TRUE((c < copy) == false);
	// operator <=
	EXPECT_TRUE((a <= b) == false);
	EXPECT_TRUE((b <= c) == true);
	EXPECT_TRUE((c <= copy) == true);
	// operator >
	EXPECT_TRUE((a > b) == true);
	EXPECT_TRUE((b > c) == false);
	EXPECT_TRUE((c > copy) == false);
	// operator >=
	EXPECT_TRUE((a >= b) == true);
	EXPECT_TRUE((b >= c) == true);
	EXPECT_TRUE((c >= copy) == true);
}


REGISTER_TYPED_TEST_CASE_P(
	adctOutOfClass,
	RelationalOperators
);


typedef ::testing::Types<
	intNQueue_t, strNQueue_t, fatNQueue_t,
	intBQueue_t, strBQueue_t, fatBQueue_t,
	intNStack_t, strNStack_t, fatNStack_t,
	intBStack_t, strBStack_t, fatBStack_t
>	comparableAdaptorContainers_type;


INSTANTIATE_TYPED_TEST_CASE_P(
	AdaptorContainers,
	adctOutOfClass,
	comparableAdaptorContainers_type
);



#endif //AdCT_OUT_OF_CLASS_TPP