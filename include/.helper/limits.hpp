//
// Created by mscheman on 11/27/25.
//

#ifndef LIMITS_H
#define LIMITS_H

#include <limits>

namespace ft
{

template<class T> struct numeric_limits : public std::numeric_limits<T> {};

}


#endif //LIMITS_H
