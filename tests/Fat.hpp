//
// Created by mscheman on 2/13/26.
//

#ifndef FAT_HPP
#define FAT_HPP

#include <string>
#include <iostream>

struct Fat
{
	Fat(int num=0, std::string CREF str=std::string()) : integer(num), string(str) {}

	int			integer;
	std::string	string;
};


inline std::ostream REF operator << (std::ostream REF os, Fat CREF fat)
{
	os << "fat_" << fat.integer << "_" << fat.string;
	return os;
}


inline bool operator==(Fat CREF lhs, Fat CREF rhs) { return lhs.integer == rhs.integer; }
inline bool operator!=(Fat CREF lhs, Fat CREF rhs) { return lhs.integer != rhs.integer; }
inline bool operator<(Fat CREF lhs, Fat CREF rhs) { return lhs.integer < rhs.integer; }
inline bool operator<=(Fat CREF lhs, Fat CREF rhs) { return lhs.integer <= rhs.integer; }
inline bool operator>(Fat CREF lhs, Fat CREF rhs) { return lhs.integer > rhs.integer; }
inline bool operator>=(Fat CREF lhs, Fat CREF rhs) { return lhs.integer >= rhs.integer; }


#endif //FAT_HPP
