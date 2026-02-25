	//
// Created by mscheman on 2/16/26.
//

#ifndef ACT_ITERATORS_TPP
#define ACT_ITERATORS_TPP


template <typename Container>
class actIteratorsTests : public ::testing::Test
{
	// Helper Typedefs
	typedef typename Container::value_type	value_type;

	public:
		actIteratorsTests() : container(arrayGenerator<value_type>()(), arrayGenerator<value_type>()() + ARRAY_TINY) {}

		// Attributes
		Container container;
};


// Dont look at me pwease :(
namespace ACT {
template <typename T>
struct getValue
{
	T REF operator()(T REF obj) const { return obj; }
	T CREF operator()(T CREF obj) const { return obj; }
};
template <typename T, typename U>
struct getValue<ns::pair<T, U> >
{
	U REF operator()(ns::pair<T, U> REF obj) const { return obj.second; }
	U CREF operator()(ns::pair<T, U> CREF obj) const { return obj.second; }
};
template <typename T>
struct setValue;
template <typename T>
struct setValue<ns::set<T> >
{
	void operator()(typename ns::set<T>::iterator REF, typename ns::set<T>::value_type CREF) {}
	void operator()(typename ns::set<T>::reverse_iterator REF, typename ns::set<T>::value_type CREF) {}
};
template <typename T>
struct setValue<ns::multiset<T> >
{
	void operator()(typename ns::multiset<T>::iterator REF, typename ns::multiset<T>::value_type CREF) {}
	void operator()(typename ns::multiset<T>::reverse_iterator REF, typename ns::multiset<T>::value_type CREF) {}
};
template <typename T, typename U>
struct setValue<ns::map<T, U> >
{
	void operator()(typename ns::map<T, U>::iterator REF it, typename ns::map<T, U>::value_type CREF v) { it->second = v.second; }
	void operator()(typename ns::map<T, U>::reverse_iterator REF it, typename ns::map<T, U>::value_type CREF v) { it->second = v.second; }
};
template <typename T, typename U>
struct setValue<ns::multimap<T, U> >
{
	void operator()(typename ns::multimap<T, U>::iterator REF it, typename ns::multimap<T, U>::value_type CREF v) { it->second = v.second; }
	void operator()(typename ns::multimap<T, U>::reverse_iterator REF it, typename ns::multimap<T, U>::value_type CREF v) { it->second = v.second; }
};
template <typename T>
struct iteratorValue;
template <typename T>
struct iteratorValue<ns::set<T> >
{
	typedef typename ns::set<T>::value_type value_type;
};
template <typename T>
struct iteratorValue<ns::multiset<T> >
{
	typedef typename ns::multiset<T>::value_type value_type;
};
template <typename T, typename U>
struct iteratorValue<ns::map<T, U> >
{
	typedef typename ns::map<T, U>::mapped_type value_type;
};
template <typename T, typename U>
struct iteratorValue<ns::multimap<T, U> >
{
	typedef typename ns::multimap<T, U>::mapped_type value_type;
};
template <typename T>
struct isReadOnly : ft::false_type {};
template <typename T>
struct isReadOnly<ns::set<T> > : ft::true_type {};
template <typename T>
struct isReadOnly<ns::multiset<T> > : ft::true_type {};
};
// Look again!


TYPED_TEST_CASE_P(actIteratorsTests);


TYPED_TEST_P(actIteratorsTests, Loop)
{
	typedef typename TypeParam::iterator iterator;

	iterator it;
	for (it = this->container.begin(); it != this->container.end(); ++it)
		;
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(actIteratorsTests, ConstLoop)
{
	typedef typename TypeParam::const_iterator const_iterator;

	const_iterator it;
	for (it = this->container.begin(); it != this->container.end(); ++it)
		;
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(actIteratorsTests, LoopModification)
{
	typedef typename TypeParam::value_type	value_type;
	typedef typename TypeParam::iterator	iterator;
	value_type const* array = arrayGenerator<value_type>()();


	iterator it;
	int i = 0;
	for (it = this->container.begin(); it != this->container.end(); ++it) {
		ACT::setValue<TypeParam>()(it, wrapAround<value_type>()(array, i, 1));
		++i;
	}
	i = 0;
	for (it = this->container.begin(); it != this->container.end(); ++it) {
		if (ACT::isReadOnly<TypeParam>().value)
			EXPECT_EQ(ACT::getValue<value_type>()(*it), ACT::getValue<value_type>()(array[i]));
		else
			EXPECT_EQ(ACT::getValue<value_type>()(*it), ACT::getValue<value_type>()(wrapAround<value_type>()(array, i, 1)));
		++i;
	}
	EXPECT_TRUE(it == this->container.end());
}


TYPED_TEST_P(actIteratorsTests, ReverseLoopModification)
{
	typedef typename TypeParam::value_type			value_type;
	typedef typename TypeParam::reverse_iterator	reverse_iterator;
	value_type const* array = arrayGenerator<value_type>()();

	reverse_iterator it;
	int i = ARRAY_TINY;
	for (it = this->container.rbegin(); it != this->container.rend(); ++it) {
		ACT::setValue<TypeParam>()(it, wrapAround<value_type>()(array, i, -3));
		--i;
	}
	i = ARRAY_TINY;
	for (it = this->container.rbegin(); it != this->container.rend(); ++it) {
		if (ACT::isReadOnly<TypeParam>().value)
			EXPECT_EQ(ACT::getValue<value_type>()(*it), ACT::getValue<value_type>()(array[i - 1]));
		else
			EXPECT_EQ(ACT::getValue<value_type>()(*it), ACT::getValue<value_type>()(wrapAround<value_type>()(array, i, -3)));
		--i;
	}
	EXPECT_TRUE(it == this->container.rend());
}


TYPED_TEST_P(actIteratorsTests, Comparison)
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


TYPED_TEST_P(actIteratorsTests, ArrowOperator)
{
	typedef typename TypeParam::iterator iterator;

	for (iterator it = this->container.begin(); it != this->container.end(); ++it)
		EXPECT_EQ(it.operator->(), &it.operator*());
}


REGISTER_TYPED_TEST_CASE_P(
	actIteratorsTests,
	Loop,
	ConstLoop,
	LoopModification,
	ReverseLoopModification,
	Comparison,
	ArrowOperator
);


INSTANTIATE_TYPED_TEST_CASE_P(
	AssociativeContainers,
	actIteratorsTests,
	associativeContainers_type
);


#endif //ACT_ITERATORS_TPP