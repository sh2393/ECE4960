#include <iostream>
#include <math.h>
using namespace std;

int main(){
	// //2.1
	// //  //Observe NaN and iNF handling in integers
	// long m = 0, n = 0, intResult1, intResult2;
	// //  intResult1 = 1/m;
	// intResult2 = m/n;
	// printf("intResult1 = %ld, intReulst2 = %ld", intResult1, intResult2);
	// //throws floating point exception:8;

	// //Observe overflow handling in integers
	// //
	// long i = 1, intFactorial = 1, iLimit = 50;
	// for(i = 2; i < iLimit; i++){
	//   intFactorial *= i;
	//   printf("i = %ld, intFactorial = %ld", i, intFactorial);
	// }
	// //returns random number

	// //2.2
	// int a = 10e-20;
	// int b = 10e3;
	// int c = 10e3;

	// int x1 = (-b+sqrt(b^2-4*a*c))/(2*a);
	// int x2 = (-b-sqrt(b^2-4*a*c))/(2*a);
	// int x3 = -2*c/(-b+sqrt(b^2-4*a*c));
	// int x4 = -2*c/(-b-sqrt(b^2-4*a*c));

	// cout << x1 << endl;
	// cout << x2 << endl;
	// cout << x3 << endl;
	// cout << x4 << endl;

	//2.3
	//exception handling
	double x = 0.0;
	double y = 0.0;
	double doubleResult1, doubleResult2;

	doubleResult1 = 1/x;
	doubleResult2 = y/x;


	cout << doubleResult1 << " " << doubleResult2 << endl;
	if(doubleResult1 == doubleResult1) cout << "INF == INF" << endl;
	if(doubleResult2 == doubleResult2) cout << "NaN == NaN" << endl;
	//prints inf, nan, INF == INF

}
