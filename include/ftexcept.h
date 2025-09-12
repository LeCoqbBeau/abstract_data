//
// Created by mscheman on 9/12/25.
//

#ifndef FTEXCEPT_H
#define FTEXCEPT_H

#include "ft_namespace.h"
#include "exception.h"

class ft::logic_error : public ft::exception {
	public:
		explicit logic_error(str CREF error) : exception(error) {}
		logic_error(logic_error CREF src) : exception(src) {}
		logic_error REF operator = (logic_error CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

class ft::invalid_argument : public ft::exception {
	public:
		explicit invalid_argument(str CREF error) : exception(error) {}
		invalid_argument(invalid_argument CREF src) : exception(src) {}
		invalid_argument REF operator = (invalid_argument CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

class ft::domain_error : public ft::exception {
	public:
		explicit domain_error(str CREF error) : exception(error) {}
		domain_error(domain_error CREF src) : exception(src) {}
		domain_error REF operator = (domain_error CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

class ft::length_error : public ft::exception {
	public:
		explicit length_error(str CREF error) : exception(error) {}
		length_error(length_error CREF src) : exception(src) {}
		length_error REF operator = (length_error CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

class ft::out_of_range : public ft::exception {
	public:
		explicit out_of_range(str CREF error) : exception(error) {}
		out_of_range(out_of_range CREF src) : exception(src) {}
		out_of_range REF operator = (out_of_range CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

class ft::runtime_error : public ft::exception {
	public:
		explicit runtime_error(str CREF error) : exception(error) {}
		runtime_error(runtime_error CREF src) : exception(src) {}
		runtime_error REF operator = (runtime_error CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

class ft::range_error : public ft::exception {
	public:
		explicit range_error(str CREF error) : exception(error) {}
		range_error(range_error CREF src) : exception(src) {}
		range_error REF operator = (range_error CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

class ft::overflow_error : public ft::exception {
	public:
		explicit overflow_error(str CREF error) : exception(error) {}
		overflow_error(overflow_error CREF src) : exception(src) {}
		overflow_error REF operator = (overflow_error CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

class ft::underflow_error : public ft::exception {
	public:
		explicit underflow_error(str CREF error) : exception(error) {}
		underflow_error(underflow_error CREF src) : exception(src) {}
		underflow_error REF operator = (underflow_error CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

class ft::bad_alloc : public ft::exception {
	public:
		explicit bad_alloc(str CREF error) : exception(error) {}
		bad_alloc(bad_alloc CREF src) : exception(src) {}
		bad_alloc REF operator = (bad_alloc CREF rhs) {if(this!=&rhs)_emsg=rhs._emsg;return *this;}
};

#endif //FTEXCEPT_H
