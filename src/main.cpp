//
// Created by mscheman on 2/13/26.
//


#if (ENABLE_SEQUENCE == false && ENABLE_ASSOCIATIVE == false && ENABLE_ADAPTORS == false && ENABLE_GRID == false) || __cplusplus >= 201103L
# include "main_bonus.cpp"
#else


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

#if ENABLE_GRID == false
# include "GridTests/Tests.hpp"
#endif


#include "Timer.h"


int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;

	Timer t;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#endif