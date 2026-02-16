//
// Created by mscheman on 2/16/26.
//

#ifndef GENERATOR_HPP
#define GENERATOR_HPP


#define ARRAY X(0), X(1), X(2), X(3), X(4), X(5), X(6), X(7), X(8), X(9),
#define ARRAY_SIZE 10
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
	int const*	operator()() const { return intArray; }
	int CREF	operator()(unsigned int const i) const { return intArray[i]; }
	int CREF	operator[](unsigned int const i) const { return intArray[i]; }
};


template <>
struct arrayGenerator<str> {
	str const*		operator()() const { return strArray; }
	str CREF	operator()(unsigned int const i) const { return strArray[i]; }
	str CREF	operator[](unsigned int const i) const { return strArray[i]; }
};


template <>
struct arrayGenerator<Fat> {
	Fat const*	operator()() const { return fatArray; }
	Fat CREF	operator()(unsigned int const i) const { return fatArray[i]; }
	Fat CREF	operator[](unsigned int const i) const { return fatArray[i]; }
};


#endif //GENERATOR_HPP
