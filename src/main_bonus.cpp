//
// Created by mscheman on 2/13/26.
//


#include "gtest/gtest.h"
#include "bonus/config.h"

#include "HashmapsContainersTests/Tests.hpp"


int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
