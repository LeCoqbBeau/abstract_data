//
// Created by mscheman on 2/13/26.
//

#ifndef CONFIG_H
#define CONFIG_H


#ifndef TESTED_NAMESPACE
#define TESTED_NAMESPACE std
#endif


#define ns TESTED_NAMESPACE


#ifndef BENCHMARK
#define BENCHMARK false
#endif


#include "Timer.hpp"


#if BENCHMARK == true
# define TIME(title) Timer(title)
#else
# define TIME(title)
#endif


#ifndef REF
# define REF &
#endif


#ifndef CREF
# define CREF const&
#endif


#endif //CONFIG_H
