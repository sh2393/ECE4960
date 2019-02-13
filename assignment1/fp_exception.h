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