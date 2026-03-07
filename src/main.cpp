//
// Created by mscheman on 2/13/26.
//


#include "gtest/gtest.h"
#include "config.h"

#include "vector.hpp"
#include "list.hpp"

#if ENABLE_SEQUENCE == true
# include "SequenceContainersTests/Tests.hpp"
#endif

#if ENABLE_ASSOCIATIVE == true
# include "AssociativeContainersTests/Tests.hpp"
#endif

#if ENABLE_ADAPTORS == true
# include "AdaptorContainersTests/Tests.hpp"
#endif


int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
