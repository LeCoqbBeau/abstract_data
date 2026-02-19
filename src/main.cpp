//
// Created by mscheman on 2/13/26.
//

#include "gtest/gtest.h"
#include "config.h"

typedef std::string	str;
#include "Fat.hpp"

#include "generator.hpp"

#include "SequenceContainersTests/Tests.hpp"

#include "list.hpp"
#include "deque.hpp"
#include "vector.hpp"

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
