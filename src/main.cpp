//
// Created by mscheman on 2/13/26.
//


#include "gtest/gtest.h"
#include "config.h"


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
