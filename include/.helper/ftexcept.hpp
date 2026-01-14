//
// Created by mscheman on 9/12/25.
//

#ifndef FTEXCEPT_H
#define FTEXCEPT_H

#include "exception.hpp"

namespace ft {

class logic_error : public exception {
	public:
		explicit logic_error(str CREF error = "ft::logic_error") FT_NOTHROW : exception(error) {}
		logic_error(logic_error CREF src) FT_NOTHROW : exception(src) {}
		logic_error REF operator = (logic_error CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};

class invalid_argument : public exception {
	public:
		explicit invalid_argument(str CREF error = "ft::invalid_argument") FT_NOTHROW : exception(error) {}
		invalid_argument(invalid_argument CREF src) FT_NOTHROW : exception(src) {}
		invalid_argument REF operator = (invalid_argument CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


class domain_error : public exception {
	public:
		explicit domain_error(str CREF error = "ft::domain_error") FT_NOTHROW : exception(error) {}
		domain_error(domain_error CREF src) FT_NOTHROW : exception(src) {}
		domain_error REF operator = (domain_error CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


class length_error : public exception {
	public:
		explicit length_error(str CREF error = "ft::length_error") FT_NOTHROW : exception(error) {}
		length_error(length_error CREF src) FT_NOTHROW : exception(src) {}
		length_error REF operator = (length_error CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


class out_of_range : public exception {
	public:
		explicit out_of_range(str CREF error = "ft::out_of_range") FT_NOTHROW : exception(error) {}
		out_of_range(out_of_range CREF src) FT_NOTHROW : exception(src) {}
		out_of_range REF operator = (out_of_range CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


class runtime_error : public exception {
	public:
		explicit runtime_error(str CREF error = "ft::runtime_error") FT_NOTHROW : exception(error) {}
		runtime_error(runtime_error CREF src) FT_NOTHROW : exception(src) {}
		runtime_error REF operator = (runtime_error CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


class range_error : public exception {
	public:
		explicit range_error(str CREF error = "ft::range_error") FT_NOTHROW : exception(error) {}
		range_error(range_error CREF src) FT_NOTHROW : exception(src) {}
		range_error REF operator = (range_error CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


class overflow_error : public exception {
	public:
		explicit overflow_error(str CREF error = "ft::overflow_error") FT_NOTHROW : exception(error) {}
		overflow_error(overflow_error CREF src) FT_NOTHROW : exception(src) {}
		overflow_error REF operator = (overflow_error CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


class underflow_error : public exception {
	public:
		explicit underflow_error(str CREF error = "ft::underflow_error") FT_NOTHROW : exception(error) {}
		underflow_error(underflow_error CREF src) FT_NOTHROW : exception(src) {}
		underflow_error REF operator = (underflow_error CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


}

#endif //FTEXCEPT_H
