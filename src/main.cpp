//
// Created by mscheman on 2/13/26.
//

#include "gtest/gtest.h"
#include "config.h"


template <typename T, typename U>
std::ostream REF operator << (std::ostream REF os, ns::pair<T, U> CREF pair)
{
	os << "< " << pair.first << " -=- " << pair.second << " >";
	return os;
}


template <typename TypeParam>
void printContainer(TypeParam c)
{
	for (typename TypeParam::iterator it = c.begin(); it != c.end(); ++it)
		std::cout << *it << " > ";
	std::cout << std::endl;
}



// #include "SequenceContainersTests/Tests.hpp"
#include "AssociativeContainersTests/Tests.hpp"

#include "set.hpp"
#include "map.hpp"

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
