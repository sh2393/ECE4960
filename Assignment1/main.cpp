/*H**********************************************************************
* FILENAME :        main.cpp         
*
* DESCRIPTION :
* 		Run test for arithmetic exception handling
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    1 Feb 2019
*
* UPDATE :	 13 Feb 2019
*
*H*/

#include <iostream>
#include <fstream>
#include "stdio.h"
#include "int_exception.h"
#include "fp_exception.h"

using namespace std;



int main(){
	//Generating empty files
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
	//end generating files

	//begin test
	int_overflow();
	int_zerodiv();
	
	fp_overflow();
	fp_infinity();
	fp_ninfinity();
	fp_nan();
	fp_signed_zero();
	fp_underflow();
	//end test

	return 0;
}