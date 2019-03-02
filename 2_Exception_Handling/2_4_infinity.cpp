#include <iostream>
#include <math.h>
#include <float.h>
using namespace std;

bool isINF(double x){
	if (x > DBL_MAX && (1.0/x == 0)) return true;
	else return false;
}

bool isNINF(double x){
	if (x < DBL_MIN && (-1.0/x == 0)) return true;
	else return false;
}

bool isNaN(double x){
	return true;
}

bool isPositiveZero(double x){
	if(isINF(1.0/x)) return true;
	else return false;
}

bool isNegativeZero(double x){
	if(isNINF(1.0/x)) return true;
	else return false;
}

bool isDoubleMax(double x){
	if (x == DBL_MAX) return true;
	else return false;
}

int main(){
	double x = DBL_MAX;
	double xx = x*x;
	cout << isINF(xx) << endl;

	return 0;
}