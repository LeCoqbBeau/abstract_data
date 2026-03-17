	//
// Created by mscheman on 2/16/26.
//

#ifndef HCT_HASH_POLICY_TPP
#define HCT_HASH_POLICY_TPP


template <typename Container>
class hctHashPolicyTests : public ::testing::Test
{
	// Helper Typedefs
	typedef typename Container::value_type	value_type;

	public:
		hctHashPolicyTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


TYPED_TEST_CASE_P(hctHashPolicyTests);


TYPED_TEST_P(hctHashPolicyTests, LoadFactor)
{
	TypeParam	CREF	c = this->container;
	float				expectedLoad = 0;

	expectedLoad = static_cast<float>(c.size()) / static_cast<float>(c.bucket_count());
	EXPECT_NEAR(expectedLoad, c.load_factor(), 0.001); // Last parameter is the error margin
}


TYPED_TEST_P(hctHashPolicyTests, MaxLoadFactor)
{
	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam	REF									c = this->container;

	EXPECT_NEAR(c.max_load_factor(), 1.0, 0.001); // Last parameter is the error margin
	c.max_load_factor(0.99f);
	EXPECT_TRUE(std::is_permutation(c.begin(), c.end(), array()));
	EXPECT_NEAR(c.max_load_factor(), 0.99, 0.001); // Last parameter is the error margin
	c.max_load_factor(0.15f); // this forces a rehash (I hope)
	EXPECT_TRUE(std::is_permutation(c.begin(), c.end(), array()));
	EXPECT_NEAR(c.max_load_factor(), 0.15, 0.001); // Last parameter is the error margin
}


TYPED_TEST_P(hctHashPolicyTests, Rehash)
{
	typedef typename TypeParam::size_type	size_type;

	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam	REF									c = this->container;

	size_type	preRehashBucketNum = c.bucket_count();
	c.rehash(c.size() * 2 / c.max_load_factor()); // this forces a rehash except if size() is 0 but it isn't
	EXPECT_NE(preRehashBucketNum, c.bucket_count());
	EXPECT_TRUE(std::is_permutation(c.begin(), c.end(), array()));
}


TYPED_TEST_P(hctHashPolicyTests, Reserve)
{
	typedef typename TypeParam::size_type	size_type;

	arrayGenerator<typename TypeParam::value_type>	array;
	TypeParam	REF									c = this->container;

	c.max_load_factor(1.0f);
	c.reserve(0); // ???
	size_type preRehashBucketNum = c.bucket_count();
	c.reserve(0); // this does nothing I hope
	EXPECT_EQ(preRehashBucketNum, c.bucket_count());
	EXPECT_TRUE(std::is_permutation(c.begin(), c.end(), array()));
	c.reserve(c.size() * 2 / c.max_load_factor()); // this forces a rehash except if size() is 0 but it isn't
	EXPECT_NE(preRehashBucketNum, c.bucket_count());
	EXPECT_TRUE(std::is_permutation(c.begin(), c.end(), array()));
}


REGISTER_TYPED_TEST_CASE_P(
	hctHashPolicyTests,
	LoadFactor,
	MaxLoadFactor,
	Rehash,
	Reserve
);


INSTANTIATE_TYPED_TEST_CASE_P(
	HashmapsContainers,
	hctHashPolicyTests,
	hashmapsContainers_type
);


#endif //HCT_HASH_POLICY_TPP