//
// Created by mscheman on 2/13/26.
//

#include "gtest/gtest.h"
#include "config.h"

typedef std::string	str;
#include "Fat.hpp"

#include "generator.hpp"

#include "SequenceContainersTests/Tests.hpp"

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	// str CREF reference = arrayGenerator<str>()(5);
	// strVector_t vector(5, reference);
	// for (strVector_t::const_iterator it = vector.begin(); it != vector.end(); ++it)
		// std::cout << *it << std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
