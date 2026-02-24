//
// Created by mscheman on 2/16/26.
//

#ifndef GENERATOR_HPP
#define GENERATOR_HPP


#define ARRAY	X(-1),																	\
				X(0), X(1), X(2), X(3), X(4), X(5), X(6), X(7), X(8), X(9),				\
				X(10), X(11), X(12), X(13), X(14), X(15), X(16), X(17), X(18), X(19),	\
				X(20), X(21), X(22), X(23), X(24), X(25), X(26), X(27), X(28), X(29),	\
				X(30), X(31), X(32), X(33), X(34), X(35), X(36), X(37), X(38), X(39),	\
				X(40), X(41), X(42), X(43), X(44), X(45), X(46), X(47), X(48), X(49),	\
				X(50), X(51), X(52), X(53), X(54), X(55), X(56), X(57), X(58), X(59),	\
				X(60), X(61), X(62), X(63), X(64), X(65), X(66), X(67), X(68), X(69),	\
				X(70), X(71), X(72), X(73), X(74), X(75), X(76), X(77), X(78), X(79),	\
				X(80), X(81), X(82), X(83), X(84), X(85), X(86), X(87), X(88), X(89),	\
				X(90), X(91), X(92), X(93), X(94), X(95), X(96), X(97), X(98), X(99),

#define ARRAY_TINY 10
#define ARRAY_SMOL 50
#define ARRAY_HUGE 100

#define X(e) e
int const intArray[] = { ARRAY };
#undef X

#define X(e) str(#e)
str const strArray[] = { ARRAY };
#undef X

#define X(e) Fat(e, #e)
Fat const fatArray[] = { ARRAY };
#undef X

#define X(e) ns::make_pair(e, e)
ns::pair<int, int> const intPairArray[] = { ARRAY };
#undef X

#define X(e) ns::make_pair(str(#e), str(#e))
ns::pair<str, str> const strPairArray[] = { ARRAY };
#undef X

#define X(e) ns::make_pair(Fat(e, #e), Fat(e, #e))
ns::pair<Fat, Fat> const fatPairArray[] = { ARRAY };
#undef X
#undef ARRAY


template <typename T>
struct arrayGenerator {};


template <>
struct arrayGenerator<int>
{
	int const*	operator()() const { return intArray + 1; }
	int CREF	operator()(unsigned int const i) const { return intArray[i + 1]; }
	int CREF	operator[](unsigned int const i) const { return intArray[i + 1]; }
};


template <>
struct arrayGenerator<str>
{
	str const*	operator()() const { return strArray + 1; }
	str CREF	operator()(unsigned int const i) const { return strArray[i + 1]; }
	str CREF	operator[](unsigned int const i) const { return strArray[i + 1]; }
};


template <>
struct arrayGenerator<Fat>
{
	Fat const*	operator()() const { return fatArray + 1; }
	Fat CREF	operator()(unsigned int const i) const { return fatArray[i + 1]; }
	Fat CREF	operator[](unsigned int const i) const { return fatArray[i + 1]; }
};


template <>
struct arrayGenerator<ns::pair<int, int> >
{
	ns::pair<int, int> const*	operator()() const { return intPairArray + 1; }
	ns::pair<int, int> CREF	operator()(unsigned int const i) const { return intPairArray[i + 1]; }
	ns::pair<int, int> CREF	operator[](unsigned int const i) const { return intPairArray[i + 1]; }
};


template <>
struct arrayGenerator<ns::pair<str, str> >
{
	ns::pair<str, str> const*	operator()() const { return strPairArray + 1; }
	ns::pair<str, str> CREF	operator()(unsigned int const i) const { return strPairArray[i + 1]; }
	ns::pair<str, str> CREF	operator[](unsigned int const i) const { return strPairArray[i + 1]; }
};


template <>
struct arrayGenerator<ns::pair<Fat, Fat> >
{
	ns::pair<Fat, Fat> const*	operator()() const { return fatPairArray + 1; }
	ns::pair<Fat, Fat> CREF	operator()(unsigned int const i) const { return fatPairArray[i + 1]; }
	ns::pair<Fat, Fat> CREF	operator[](unsigned int const i) const { return fatPairArray[i + 1]; }
};


template <typename T>
struct intConvertor {};


template <>
struct intConvertor<int>
{
	int operator()(int const i) const { return i; }
};

#define TOSTR( x )	static_cast< std::ostringstream REF>(				\
					( std::ostringstream() << std::dec << x ) ).str()

template <>
struct intConvertor<str>
{
	str operator()(int const i) const { return TOSTR(i); }
};


template <>
struct intConvertor<Fat>
{
	Fat operator()(int const i) const { return Fat(i, TOSTR(i)); }
};


#endif //GENERATOR_HPP
