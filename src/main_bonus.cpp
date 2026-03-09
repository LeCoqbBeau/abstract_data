//
// Created by mscheman on 2/13/26.
//


#include "gtest/gtest.h"
#include "bonus/config.h"


#include "GridTests/Tests.hpp"
#include "../include/unordered_set.hpp"
#include "../include/unordered_map.hpp"


int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
