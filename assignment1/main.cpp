//test file
#include <iostream>
#include <fstream>
#include "stdio.h"
#include "int_exception.h"
#include "fp_exception.h"

using namespace std;



int main(){
	FILE * logfile;
	logfile = fopen("log.txt", "w");
	if(logfile != NULL){
		fputs("=====================\ndetailed record for exception handling behavior\n=====================\n", logfile);
		fclose(logfile);
	}

	FILE * reportfile;
	reportfile = fopen("report.txt", "w");
	if(reportfile != NULL){
		fputs("=====================\nIEEE violation report\n=====================\n(no violation if blank)\n", reportfile);
		fclose(reportfile);
	}

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