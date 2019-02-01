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


void integer_overflow(void);

void divide_by_zero(void);

#endif

