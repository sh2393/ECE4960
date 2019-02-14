/*H**********************************************************************
* FILENAME :        fp_exception.h           
*
* DESCRIPTION :
*       Floating point exception handling header file.
*
* NOTES :
*       ECE4960 Programming Assignment 1
* 		Arithmetic Exception Handling
*		Floating point exception checks: infinity, positive inifiniy, NaN, overflow, underflow, signed zero
* 
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    1 Feb 2019
*
* UPDATE :	 13 Feb 2019
*
*H*/

#ifndef FP_EXCEPTION_H
#define FP_EXCEPTION_H

#include <iostream>
#include <cmath>
#include <climits>
#include <cfloat>

#define FLT_INF std:numeric_limits<float>::infinity()
#define DBL_INF std::numeric_limits<double>::infinity()

void fp_overflow(void);

void fp_infinity(void);

void fp_ninfinity(void);

void fp_nan(void);

void fp_signed_zero(void);

void fp_underflow(void);

#endif