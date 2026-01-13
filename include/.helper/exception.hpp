//
// Created by mscheman on 9/12/25.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "ftdef.hpp"

namespace ft {

class exception {
	public:
		// Constructors
		exception() FT_NOTHROW : mError("ft::exception") {}
		exception(exception CREF other) FT_NOTHROW : mError(other.mError) {}
		exception REF operator = (exception CREF other) FT_NOTHROW {if (this != &other) mError = what(); return (*this);}
		virtual ~exception() {}

		// Method
		virtual const char* what() const FT_NOTHROW {return mError.c_str();}

	protected:
		// Constructor
		explicit exception(std::string CREF str) : mError(str) {}

		// Attributes
		std::string mError;
};

}


#endif //EXCEPTION_H
