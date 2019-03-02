#include <iostream>
#include <math.h>
using namespace std;

int main(){
	//2.1
	//  //Observe NaN and iNF handling in integers
	long m = 0, n = 0, intResult1, intResult2;
	//  intResult1 = 1/m;
	intResult2 = m/n;
	printf("intResult1 = %ld, intReulst2 = %ld", intResult1, intResult2);
	//throws floating point exception:8;

	//Observe overflow handling in integers
	//
	long i = 1, intFactorial = 1, iLimit = 50;
	for(i = 2; i < iLimit; i++){
	  intFactorial *= i;
	  printf("i = %ld, intFactorial = %ld", i, intFactorial);
	}
	//returns random number

}
