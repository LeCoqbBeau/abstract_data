//
// Created by mscheman on 11/27/25.
//

#ifndef NEW_H
#define NEW_H

#include "ftdef.hpp"
#include "exception.hpp"

namespace ft
{
class bad_alloc : public exception {
	public:
		explicit bad_alloc(str CREF error = "ft::bad_alloc") FT_NOTHROW : exception(error) {}
		bad_alloc(bad_alloc CREF src) FT_NOTHROW : exception(src) {}
		bad_alloc REF operator = (bad_alloc CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


class bad_array_new_length : public ft::bad_alloc {
	public:
		explicit bad_array_new_length(str CREF error = "ft::bad_array_new_length") FT_NOTHROW : bad_alloc(error) {}
		bad_array_new_length(bad_array_new_length CREF src) FT_NOTHROW : bad_alloc(src) {}
		bad_array_new_length REF operator = (bad_array_new_length CREF rhs) FT_NOTHROW {if(this!=&rhs)mError=rhs.mError;return *this;}
};


}

#endif //NEW_H
