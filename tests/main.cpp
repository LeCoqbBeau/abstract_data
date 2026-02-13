//
// Created by mscheman on 2/13/26.
//

#include "gtest/gtest.h"
#include "config.h"

typedef std::string	str;
#include "Fat.hpp"


#include "SequenceContainersTests.tpp"

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
