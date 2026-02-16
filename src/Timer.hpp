//
// Created by mscheman on 2/13/26.
//

#ifndef BENCHMARK_TPP
#define BENCHMARK_TPP


#include <ctime> // clock_t, clock()
#include <iostream>


struct Timer
{
	Timer(char const* title) : _title(title), _start(clock()) {}
	~Timer() { clock_t const elapsed = clock() - _start; std::cout << _title << ": " << elapsed << " >> " << elapsed * 20 << std::endl; }
	char const* _title;
	clock_t	_start;
};


#endif //BENCHMARK_TPP
