//
// Created by mscheman on 2/23/26.
//

#ifndef PREDICATES_HPP
#define PREDICATES_HPP


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
	bool operator() (str CREF s) const	{ return *std::next(s.end(), -1) % 2 == 0; }
	bool operator() (Fat CREF f) const	{ return f.integer % 2 == 0; }
};


struct isOdd
{
	bool operator() (int const i) const	{ return i % 2 == 1; }
	bool operator() (str CREF s) const	{ return *std::next(s.end(), -1) % 2 == 1; }
	bool operator() (Fat CREF f) const	{ return f.integer % 2 == 1; }
};


struct alwaysTrue
{
	template <typename T>
	bool operator() (T CREF) const { return true; }
};


struct alwaysFalse
{
	template <typename T>
	bool operator() (T CREF) const { return false; }
};


struct isSorted
{
	template <typename Container>
	static bool check(Container CREF c)
	{
		return std::adjacent_find(
			c.begin(),
			c.end(),
			std::greater<typename Container::value_Type>()
		) == c.end();
	}
};


#endif //PREDICATES_HPP