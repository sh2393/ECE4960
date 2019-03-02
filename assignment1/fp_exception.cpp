/*H**********************************************************************
* FILENAME :        fp_exception.cpp            
*
* DESCRIPTION :
*       Floating point exception handling implementation.
*
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

#include "fp_exception.h"
#include "helpers.h"
#include <cmath>

char buffer[200];

bool is_equal(double x, double y)
{
	if (x == y) return true;
	else return false;
}

void fp_overflow(void)
{
	double dmax = DBL_MAX;
	double dsquare = dmax * dmax;
	sprintf(buffer, "\n=================\nDBL_MAX*DBL_MAX\n=================\n");
	write_log(buffer);
	check_float(dsquare, __func__);
	if(!pass_fp_overflow(dsquare)) report_violation(__func__);

	check_equal(dsquare, dsquare);
	propogate(dsquare);
}

void fp_infinity(void)
{
	//
	double pos_inf = 1.0/0.0;
	sprintf(buffer, "\n=================\n1.0/0.0\n=================\n");
	write_log(buffer);
	check_float(pos_inf, __func__);
	if(!pass_fp_inf(pos_inf)) report_violation(__func__);

	//
	double exponent = 1000;
	double result = exp(exponent);
	sprintf(buffer, "\n=================\nexp(x) reaches infinity for x = %f\n=================\n", exponent);
	write_log(buffer);
	check_float(result, __func__);
	if(!pass_fp_inf(result)) report_violation(__func__);

	check_equal(result, result);
	propogate(result);
	interact(result);
}


void fp_ninfinity(void)
{
	//
	double neg_inf = -1.0/0.0;
	sprintf(buffer, "\n=================\n-1.0/0.0\n=================\n");
	write_log(buffer);
	check_float(neg_inf, __func__);
	if(!pass_fp_ninf(neg_inf)) report_violation(__func__);

	check_equal(neg_inf, neg_inf);
	propogate(neg_inf);
	interact(neg_inf);
}


void fp_nan(void)
{
	//
	double result = 0.0/0.0;
	sprintf(buffer, "\n=================\n0.0/0.0\n=================\n");
	write_log(buffer);
	check_float(result, __func__);
	if(!pass_fp_nan(result)) report_violation(__func__);

	//
	double imaginary = sqrt(-1.0);
	sprintf(buffer, "\n=================\nsqrt(-1.0)\n=================\n");
	write_log(buffer);
	check_float(imaginary, __func__);
	if(!pass_fp_nan(result)) report_violation(__func__);
	
	check_equal(result, result);
	propogate(result);
	interact(result);

}


void fp_signed_zero(void)
{
	for(int nfunc = 1; nfunc <=5; nfunc++){
		//initialize dummy variable
		double px = 1.0;
		double nx = -1.0;
		px *= pow(10, -307);
		nx *= pow(10, -307); //TODO

		if(nfunc == 1){
			sprintf(buffer, "\n===================================================\nlimit of log(x) as x approahces positive zero\n===================================================\n");
			write_log(buffer);
		}else if(nfunc == 2){
			sprintf(buffer, "\n===================================================\nlimit of log(x) as x approahces negative zero\n===================================================\n");
			write_log(buffer);
		}else if(nfunc == 3){
			sprintf(buffer, "\n===================================================\nlimit of sin(x)/x as x approahces positive zero\n===================================================\n");
			write_log(buffer);
		}else if(nfunc == 4){
			sprintf(buffer, "\n===================================================\nlimit of sin(x)/x as x approahces negative zero\n===================================================\n");
			write_log(buffer);
		}else{
			sprintf(buffer, "\n===================================================\nlimit of sin(x)/|x| as x approahces negative zero\n===================================================\n");
			write_log(buffer);
		}

		double temp = 0;
		for(int i = 1; i < 20; i++){
			if(nfunc == 1){
				temp = log(px);
				sprintf(buffer, "x = %.16e, result = %f", px, temp);
				write_log(buffer);
			}else if(nfunc == 2){
				temp = log(nx);
				sprintf(buffer, "x = %.16e, result = %f", nx, temp);
				write_log(buffer);
			}else if(nfunc == 3){
				temp = sin(px)/px;
				sprintf(buffer, "x = %.16e, result = %f", px, temp);
				write_log(buffer);
			}else if(nfunc == 4){
				temp = sin(nx)/nx;
				sprintf(buffer, "x = %.16e, result = %f", nx, temp);
				write_log(buffer);
			}else{
				temp = sin(nx)/px;
				sprintf(buffer, "x = %.16e, result = %f", nx, temp);
				write_log(buffer);
			}
			px/=10.0;
			nx/=10.0;
			check_float(temp, __func__);
		}
	}	
}

void fp_underflow(void)
{

	for(int nfunc = 1; nfunc <= 3; nfunc++){
		double x = 0;
		double y = 0;
		if (nfunc == 1){
			x = 1.625;
			y = 1.6875;
			sprintf(buffer, "\n=================\nx-y\n=================\n");
			write_log(buffer);
		}
		else if (nfunc == 2){
			x = 1.625;
			y = 1.6875;
			sprintf(buffer, "\n=================\nx/y\n=================\n");
			write_log(buffer);
		}
		else {
			x = 1.0;
			sprintf(buffer, "\n==================================\nsin(1.23456789012345 * x)/x\n==================================\n");
			write_log(buffer);
		}

		x *= pow(10, -307);	
		y *= pow(10, -307);	

		double temp = 0;
		for(int i = 1; i < 20; i++){
			
			if (nfunc == 1){
				temp = x-y;
				sprintf(buffer, "%.16f", temp);
				write_log(buffer);
				if(!pass_fp_underflow(x, y)) report_violation(__func__);
			}else if (nfunc == 2){
				temp = x/y;
				sprintf(buffer, "%.16f", temp);
				write_log(buffer);
				if(!pass_fp_underflow(x, y)) report_violation(__func__);
			}else{
				temp = sin(1.234567890123456789*x)/x;
				sprintf(buffer, "%.16f", temp);
				write_log(buffer);
			}
			x/=10; 
			y/=10;
			check_float(temp, __func__);

		}
		
		
	}

}
