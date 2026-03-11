//
// Created by mscheman on 3/11/26.
//

#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>
#include <iostream>

class Timer
{
	public:
		Timer() : _start(clock()) {}
		~Timer() { std::cout << std::setprecision(2); std::cout << static_cast<double>(clock() - _start) / CLOCKS_PER_SEC << "s" << std::endl; }

	private:
		clock_t	_start;
};

#endif //TIMER_HPP