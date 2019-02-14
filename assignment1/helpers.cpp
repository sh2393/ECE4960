/*H**********************************************************************
* FILENAME :        helpers.cpp             
*
* DESCRIPTION :
*       Flag functions check for exception handling for both integer and floating point
*		File I/O Helper functions for generating IEEE compliance report and log files
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    1 Feb 2019
*
* UPDATE :	 13 Feb 2019
*
*H*/

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <climits>
#include <cfloat>

#include "helpers.h"

/******************************************
Flag Functions
******************************************/
bool isINF(double x){
	if(x > DBL_MAX && (1.0/x == 0)) return true;
	else return false;
}

bool isNINF(double x){
	if (x < DBL_MIN && (-1.0/x == 0)) return true;
	else return false;
}

bool isPositiveZero(double x){
	if(isINF(1.0/x)) return true;
	else return false;
}

bool isNegativeZero(double x){
	if(isNINF(1.0/x)) return true;
	else return false;
}

bool isNan(double x){
	if (x != x) return true;
	else return false;
}

/******************************************
Behavior Functions
******************************************/
void check_equal(double x, double y){
	freopen("log.txt", "a", stdout);
	if (x==y){
		printf("Equivalence: %f equals to %f\n", x, y);
	}else{
		printf("Equivalence: %f does not equal to %f\n", x, y);
	}
	fclose(stdout);
}

void propogate(double x){
	freopen("log.txt", "a", stdout);
	double temp = x/200;
	//printf("Propogation: %f/200 = %f\n", x, temp);
	if (isINF(x) && isINF(temp)){
		printf("Infinity propogates\n");
	}
	if (isNINF(x) && isNINF(temp)){
		printf("Negative infinity propogates\n");
	}
	if(isNan(x) && isNan(temp)){
		printf("NaN propogates\n");
	}
	fclose(stdout);
}

void interact(double x){
	freopen("log.txt", "a", stdout);

	double inf_t = x * (1.0/0.0);
	printf("computation of %f and INF = %f\n", x, inf_t);

	double ninf_t = x * (-1.0/0.0);
	printf("computation of %f and NINF = %f\n", x, ninf_t);

	double nan_t = x * (0.0/0.0);
	printf("computation of %f and NaN = %f\n", x, nan_t);

	fclose(stdout);
}

/******************************************
Report Functions
******************************************/


bool pass_int_overflow(int x){
	if (x > INT_MIN && x < INT_MAX) return true;
	else return false;
}
bool pass_int_divzero(int x){
	if (x > INT_MIN && x < INT_MAX) return true;
	else return false;
}

bool pass_fp_overflow(double x){
	if (isINF(x)) return true;
	else return false;
}

bool pass_fp_inf(double x){
	if (isINF(x)) return true;
	else return false;
}

bool pass_fp_ninf(double x){
	if (isNINF(x)) return true;
	else return false;
}
bool pass_fp_nan(double x){
	if (isNan(x)) return true;
	else return false;
}
bool pass_fp_poszero(double x){
	if (isPositiveZero(x)) return true;
	else return false;
}
bool pass_fp_negzero(double x){
	if (isNegativeZero(x)) return true;
	else return false;
}

bool pass_fp_underflow(double y, double z){
	if( (y == z) && (y-z == 0)) return true;
	if( (y != z) && (y-z == 0)) return false;
	else return true;
}

void report_violation(const char* func_name){
	freopen("report.txt", "a", stdout);
	printf("%s violated IEEE standard.\n", func_name);
	fclose(stdout);
}

/******************************************
Log functions
******************************************/
void check_factorial_overflow(int x, int n, const char* func_name){
	freopen("log.txt", "a", stdout);
	for(int i = 1; i <= n; i++) x /= i; 
	if (x != 1) {
		printf("%s %d! generated integer overflow", func_name, n);
	}
	fclose(stdout);
}

void check_float(double x, const char* func_name){
	freopen("log.txt", "a", stdout);
	if (isINF(x)){
		printf("%s generated infinity\n", func_name);
	}
	if (isNINF(x)){
		printf("%s generated negative infinity\n", func_name);
	}
	if (isPositiveZero(x)){
		printf("%s generated positive zero\n", func_name);
	}
	if (isNegativeZero(x)){
		printf("%s generated negative zero\n", func_name);
	}
	if (isNan(x)){
		printf("%s generated Nan\n", func_name);
	}
	fclose(stdout);
}

/******************************************
File I/O
******************************************/
void write_log(char* details){
	freopen("log.txt", "a", stdout);
	printf("%s\n", details);
	fclose(stdout);
}