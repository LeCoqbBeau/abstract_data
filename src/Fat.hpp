//
// Created by mscheman on 2/13/26.
//

#ifndef FAT_HPP
#define FAT_HPP

#include <string>
#include <iostream>

struct Fat
{
	Fat(int num=0, std::string CREF str=std::string()) : integer(num), string(str), chonk(NULL) { chonk = new char; }
	Fat(Fat CREF rhs) : integer(rhs.integer), string(rhs.string), chonk(NULL) { chonk = new char; }
	Fat REF operator = (Fat CREF rhs) {
		if (this != &rhs) {
			integer = rhs.integer;
			string = rhs.string;
			if (!chonk)
				chonk = new char;
		}
		return *this;
	}
	~Fat() { delete chonk; }

	int			integer;
	std::string	string;
	char		*chonk;
};


inline std::ostream REF operator << (std::ostream REF os, Fat CREF fat)
{
	os << "fat_" << fat.integer << "_" << fat.string << "_" << static_cast<void *>(fat.chonk);
	return os;
}


inline bool operator	==(Fat CREF lhs, Fat CREF rhs)	{ return lhs.integer == rhs.integer; }
inline bool operator	!=(Fat CREF lhs, Fat CREF rhs)	{ return lhs.integer != rhs.integer; }
inline bool operator	< (Fat CREF lhs, Fat CREF rhs)	{ return lhs.integer < rhs.integer; }
inline bool operator	<=(Fat CREF lhs, Fat CREF rhs)	{ return lhs.integer <= rhs.integer; }
inline bool operator	> (Fat CREF lhs, Fat CREF rhs)	{ return lhs.integer > rhs.integer; }
inline bool operator	>=(Fat CREF lhs, Fat CREF rhs)	{ return lhs.integer >= rhs.integer; }


#endif //FAT_HPP
