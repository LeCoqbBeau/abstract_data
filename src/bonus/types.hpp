//
// Created by mscheman on 2/16/26.
//

#ifndef TYPES_HPP
#define TYPES_HPP


#include "NumStrings.hpp"
#include "Fat.hpp"




#ifndef USE_FT

#include <utility>
template <typename T, typename U>
std::ostream REF operator << (std::ostream REF os, std::pair<T, U> CREF pair)
{
	os << "< " << pair.first << " -=- " << pair.second << " >";
	return os;
}

#include <unordered_set>
#include <unordered_map>

# else


#include "utility.hpp"
namespace ft {
template <typename T, typename U>
std::ostream REF operator << (std::ostream REF os, ft::pair<T, U> CREF pair)
{
	os << "< " << pair.first << " -=- " << pair.second << " >";
	return os;
}


#include "unordered_set.hpp"
#include "unordered_map.hpp"


}


#endif


namespace ft {}; // failsafe
namespace ns			= TESTED_NAMESPACE;
namespace otherspace	= UNTESTED_NAMESPACE;







#endif //TYPES_HPP
