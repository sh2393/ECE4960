/*H**********************************************************************
* FILENAME :        int_exception.h         
*
* DESCRIPTION :
* 		Integer exception checks header file
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    1 Feb 2019
*
* UPDATE :	 13 Feb 2019
*
*H*/

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

