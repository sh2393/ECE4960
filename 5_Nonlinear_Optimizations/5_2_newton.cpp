#include <iostream>
#include <cmath>
using namespace std;

double f(double x){
	return x - cos(x);
}

double fo(double x){
	return exp(100.0*x)-1;
}

double foderiv(double x){
	return 100*exp(100.0*x);
}


void Newton(double x){
	double tolerance = 0.01;
	double deltaX = fo(x)/foderiv(x);

	do{
		deltaX = fo(x)/foderiv(x);
		x = x-deltaX;
		cout << deltaX << endl;

	}while(abs(deltaX) > tolerance);

	cout << "x = " << x << endl;
}

int main(){
	Newton(1.0);
	return 0;
}