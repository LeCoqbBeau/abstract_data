//
// Created by mscheman on 9/12/25.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace ft {

class exception {
	public:
		// Constructors
		exception() throw() : _emsg("ft::exception") {}
		exception(exception CREF other) throw() : _emsg(other._emsg) {}
		exception REF operator = (exception CREF other) throw() {if (this != &other) _emsg = what(); return (*this);}
		virtual ~exception() {}

		// Method
		virtual const char* what() const throw() {return _emsg.c_str();}

	protected:
		// Constructor
		explicit exception(std::string CREF str) : _emsg(str) {}

		// Attributes
		std::string _emsg;
};

}


#endif //EXCEPTION_H
