
#include <iostream>
#include <math.h>
using namespace std;

int main(){
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