/* check.h
 * Header file for check.cpp. Used to generate IEEE compliance report for floating point exception
 */

#ifndef HELPERS_H
#define HELPERS_H


//behavior checks
void check_equal(double x, double y);
void propogate(double x);
void interact(double x);

//report funciton
bool pass_underflow(double y, double z);


//File I/O
void check_factorial_overflow(int x, int n, const char * func_name);
void check_float(double x, const char* func_name);
void write_log(char* details);

#endif