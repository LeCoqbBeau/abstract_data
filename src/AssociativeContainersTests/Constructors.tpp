//
// Created by mscheman on 2/24/26.
//

#ifndef ACT_CONSTRUCTORS_TPP
#define ACT_CONSTRUCTORS_TPP


template <typename Container>
class actConstructorTests : public ::testing::Test {};


TYPED_TEST_CASE_P(actConstructorTests);


TYPED_TEST_P(actConstructorTests, Default)
{
	TypeParam container;
	EXPECT_EQ(container.empty(), true);
	EXPECT_EQ(container.size(), static_cast<typename TypeParam::size_type>(0));
}


TYPED_TEST_P(actConstructorTests, Range)
{
	
}


TYPED_TEST_P(actConstructorTests, Copy)
{

}


TYPED_TEST_P(actConstructorTests, AssignementOperator)
{

}


REGISTER_TYPED_TEST_CASE_P(
	actConstructorTests,
	Default,
	Range,
	Copy,
	AssignementOperator
);


INSTANTIATE_TYPED_TEST_CASE_P(
	AssociativeContainers,
	actConstructorTests,
	associativeContainers_type
);

#endif //ACT_CONSTRUCTORS_TPP