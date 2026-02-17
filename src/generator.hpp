//
// Created by mscheman on 2/16/26.
//

#ifndef GENERATOR_HPP
#define GENERATOR_HPP


#define ARRAY	X(0), X(1), X(2), X(3), X(4), X(5), X(6), X(7), X(8), X(9),				\
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
#undef ARRAY


template <typename T>
struct arrayGenerator {};


template <>
struct arrayGenerator<int> {
	operator int const*() const { return intArray; }
	int const*	operator()() const { return intArray; }
	int CREF	operator()(unsigned int const i) const { return intArray[i]; }
	int CREF	operator[](unsigned int const i) const { return intArray[i]; }
};


template <>
struct arrayGenerator<str> {
	operator str const*() const { return strArray; }
	str const*		operator()() const { return strArray; }
	str CREF	operator()(unsigned int const i) const { return strArray[i]; }
	str CREF	operator[](unsigned int const i) const { return strArray[i]; }
};


template <>
struct arrayGenerator<Fat> {
	operator Fat const*() const { return fatArray; }
	Fat const*	operator()() const { return fatArray; }
	Fat CREF	operator()(unsigned int const i) const { return fatArray[i]; }
	Fat CREF	operator[](unsigned int const i) const { return fatArray[i]; }
};


#endif //GENERATOR_HPP
