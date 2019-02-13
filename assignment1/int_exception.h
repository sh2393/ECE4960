//int exception header file
#ifndef INT_EXCEPTION_H
#define INT_EXCEPTION_H

#include <iostream>
#include <cmath>
#include <climits>
#include <exception>

class MyException: public std::exception
{
	virtual const char* what() const throw()
	{
		return "Divide by zero";
	}
};


void int_overflow(void);

void int_zerodiv(void);

#endif

