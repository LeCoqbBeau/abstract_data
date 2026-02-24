//
// Created by mscheman on 2/23/26.
//

#ifndef PREDICATES_HPP
#define PREDICATES_HPP


static char str_back(str CREF s) { return *(s.end() - 1); }


struct isEqual
{
	isEqual(int const i, str CREF s) : _i(i), _s(s) {}
	bool operator() (int const i) const	{ return i == _i; }
	bool operator() (str CREF s) const	{ return s == _s; }
	bool operator() (Fat CREF f) const	{ return f.integer == _i; }

	int const _i;
	str const _s;
};


struct isEven
{
	bool operator() (int const i) const	{ return i % 2 == 0; }
	bool operator() (str CREF s) const	{ return str_back(s) % 2 == 0; }
	bool operator() (Fat CREF f) const	{ return f.integer % 2 == 0; }
};


struct isOdd
{
	bool operator() (int const i) const	{ return i % 2 == 1; }
	bool operator() (str CREF s) const	{ return str_back(s) % 2 == 1; }
	bool operator() (Fat CREF f) const	{ return f.integer % 2 == 1; }
};


struct areThirdOrFourth
{
	bool operator() (int const i) const					{ return i % 3 == 0 || i % 4 == 0; }
	bool operator() (int const i, int const j) const	{ return (*this)(i) && (*this)(j); }
	bool operator() (str CREF s1, str CREF s2) const	{ return (*this)(str_back(s1)) && (*this)(str_back(s2)); }
	bool operator() (Fat CREF f1, Fat CREF f2) const	{ return (*this)(f1.integer) && (*this)(f2.integer); }
};


struct alwaysTrue
{
	template <typename T>
	bool operator() (T CREF) const { return true; }
	template <typename T, typename U>
	bool operator() (T CREF, U CREF) const { return true; }
};


struct alwaysFalse
{
	template <typename T>
	bool operator() (T CREF) const { return false; }
};


struct isSorted
{
	template <typename Container, typename Predicate>
	static bool check(Container CREF c, Predicate CREF predicate)
	{
		return std::adjacent_find(
			c.begin(),
			c.end(),
			predicate
		) == c.end();
	}
};


#endif //PREDICATES_HPP