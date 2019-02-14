/*H**********************************************************************
* FILENAME :        helpers.h          
*
* DESCRIPTION :
* 		Header file for helpers.cpp. Used to generate IEEE compliance report for floating point exception
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    1 Feb 2019
*
* UPDATE :	 13 Feb 2019
*
*H*/

#ifndef HELPERS_H
#define HELPERS_H


//behavior checks
void check_equal(double x, double y);
void propogate(double x);
void interact(double x);

//report funciton
bool pass_int_overflow(int x);
bool pass_int_divzero(int x);
bool pass_fp_overflow(double x);
bool pass_fp_inf(double x);
bool pass_fp_ninf(double x);
bool pass_fp_nan(double x);
bool pass_fp_poszero(double x);
bool pass_fp_negzero(double x);
bool pass_fp_underflow(double y, double z);
void report_violation(const char* func_name);

//File I/O
void check_factorial_overflow(int x, int n, const char * func_name);
void check_float(double x, const char* func_name);
void write_log(char* details);

#endif