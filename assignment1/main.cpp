//test file
#include <iostream>
#include <fstream>
#include "stdio.h"
#include "int_exception.h"
#include "fp_exception.h"

using namespace std;



int main(){
	int_overflow();
	int_zerodiv();
	
	fp_overflow();
	fp_infinity();
	fp_ninfinity();
	fp_nan();
	fp_signed_zero();
	fp_underflow();

	return 0;
}