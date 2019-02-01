//test file
#include <iostream>
#include <fstream>
#include "int_exception.h"
#include "fp_exception.h"

using namespace std;



int main(){
	ofstream log;
	ofstream report;
	//log.open("log.txt");

	//integer exceptions
	freopen("log.txt", "w", stdout);
	integer_overflow();
	printf("\n");
	divide_by_zero();
	printf("\n");

	//floating poitn exceptions
	fp_overflow();
	printf("\n");

	log.close();
	return 0;
}