	//
// Created by mscheman on 2/16/26.
//

#ifndef HCT_BUCKET_TPP
#define HCT_BUCKET_TPP


template <typename Container>
class hctBucketTests : public ::testing::Test
{
	// Helper Typedefs
	typedef typename Container::value_type	value_type;

	public:
		hctBucketTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


namespace HCT {
template <typename T>
struct getKey
{
	T CREF operator()(T CREF t) const { return t; }
};
template <typename T, typename U>
struct getKey<ns::pair<T const, U> >
{
	T CREF operator()(ns::pair<T const, U> CREF pair) const { return pair.first; }
};
}


TYPED_TEST_CASE_P(hctBucketTests);


TYPED_TEST_P(hctBucketTests, BucketLoop)
{
	typedef typename TypeParam::local_iterator	local_iterator;
	typedef typename TypeParam::size_type		size_type;
	typedef typename TypeParam::value_type		value_type;
	typedef typename TypeParam::key_type		key_type;

	arrayGenerator<key_type>	array;
	TypeParam	REF				c = this->container;

	key_type	check[c.size()]; // HOLY !
	size_type	idx = 0;
	for (size_type i = 0; i < c.bucket_count(); ++i) {
		for (local_iterator it = c.begin(i); it != c.end(i); ++it) {
			check[idx] = HCT::getKey<value_type>()(*it);
			++idx;
		}
	}
	EXPECT_TRUE(std::is_permutation(array(), array() + ARRAY_TINY, check));
}


TYPED_TEST_P(hctBucketTests, BucketConstLoop)
{
	typedef typename TypeParam::const_local_iterator	local_iterator;
	typedef typename TypeParam::size_type				size_type;
	typedef typename TypeParam::value_type				value_type;
	typedef typename TypeParam::key_type				key_type;

	arrayGenerator<key_type>	array;
	TypeParam	CREF			c = this->container;

	key_type	check[c.size()]; // HOLY !
	size_type	idx = 0;
	for (size_type i = 0; i < c.bucket_count(); ++i) {
		for (local_iterator it = c.begin(i); it != c.end(i); ++it) {
			check[idx] = HCT::getKey<value_type>()(*it);
			++idx;
		}
	}
	EXPECT_TRUE(std::is_permutation(array(), array() + ARRAY_TINY, check));
}


TYPED_TEST_P(hctBucketTests, Bucket)
{
	typedef typename TypeParam::const_local_iterator	local_iterator;
	typedef typename TypeParam::size_type				size_type;
	typedef typename TypeParam::value_type				value_type;

	HCT::getKey<value_type>	getKey;
	TypeParam	CREF		c = this->container;

	for (size_type i = 0; i < c.bucket_count(); ++i)
		for (local_iterator it = c.begin(i); it != c.end(i); ++it)
			EXPECT_EQ(c.bucket(getKey(*it)), i);
}


REGISTER_TYPED_TEST_CASE_P(
	hctBucketTests,
	BucketLoop,
	BucketConstLoop,
	Bucket
);


INSTANTIATE_TYPED_TEST_CASE_P(
	HashmapsContainers,
	hctBucketTests,
	hashmapsContainers_type
);


#endif //HCT_BUCKET_TPP