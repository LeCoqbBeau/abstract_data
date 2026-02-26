//
// Created by mscheman on 2/26/26.
//

#ifndef NUMSTRINGS_HPP
#define NUMSTRINGS_HPP


struct NumStrings : public std::string
{
	NumStrings()					{}
	NumStrings(char const* s)		: std::string(s) {}
	NumStrings(std::string CREF s)	: std::string(s) {}
};


#define NUMSTRING_COMP(op) bool operator op (NumStrings CREF lhs, NumStrings CREF rhs)

NUMSTRING_COMP(==)	{ return static_cast<std::string>(lhs) == static_cast<std::string>(rhs); }
NUMSTRING_COMP(!=)	{ return !(lhs == rhs); }
NUMSTRING_COMP(<)	{ return (lhs.size() < rhs.size()) || (lhs.size() == rhs.size() && memcmp(lhs.c_str(), rhs.c_str(), lhs.size()) < 0); }
NUMSTRING_COMP(<=)	{ return !(rhs < lhs); }
NUMSTRING_COMP(>)	{ return (rhs < lhs); }
NUMSTRING_COMP(>=)	{ return !(lhs < rhs); }

#undef NUMSTRING_COMP


typedef NumStrings str;


#endif //NUMSTRINGS_HPP