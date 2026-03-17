//
// Created by mscheman on 2/13/26.
//


#include "gtest/gtest.h"
#include "mandatory/config.h"

#if ENABLE_SEQUENCE == true
# include "SequenceContainersTests/Tests.hpp"
#endif

#if ENABLE_ASSOCIATIVE == true
# include "AssociativeContainersTests/Tests.hpp"
#endif

#if ENABLE_ADAPTORS == true
# include "AdaptorContainersTests/Tests.hpp"
#endif

#if ENABLE_GRID == true
# include "GridTests/Tests.hpp"
#endif


int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
