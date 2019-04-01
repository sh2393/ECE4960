#include <iostream>
#include <cmath>
using namespace std;

double a(double x){
	return pow(x, 3) + 300*x;
}

double b(double x){
	return pow(x, 3) + 300*x + pow(10, 8);
}

double f1deriv(double x, double h, double f(double)){
	return (f(x+h)-f(x))/h;
}

double f2deriv(double x, double h, double f(double)){
	return (f(x+h)-f(x-h))/(2*h);
}


int main(){
	double x = 10;
	double truth = 600;

	
	printf("x^3 + 300x\n");
	printf("first order approximation\t\tsecond order aprroximation\n");
	for(int i = 0; i >= -25; i--){
		double h = pow(10, i);
		printf("%9.6f\t\t\t\t", abs(f1deriv(x, h, &a)-truth));
		printf("%9.6f\n", abs(f2deriv(x, h, &a)-truth));
	}

	printf("x^3 + 300x + 10^8\n");
	printf("first order approximation\t\tsecond order aprroximation\n");
	for(int i = 0; i >= -25; i--){
		double h = pow(10, i);
		printf("%9.6f\t\t\t\t", abs(f1deriv(x, h, &b)-truth));
		printf("%9.6f\n", abs(f2deriv(x, h, &b)-truth));
	}


	return 0;
}

/*
Output
x^3 + 300x
first order approximation		second order aprroximation
31.000000				 1.000000
 3.010000				 0.010000
 0.300100				 0.000100
 0.030001				 0.000001
 0.003000				 0.000000
 0.000300				 0.000000
 0.000029				 0.000001
 0.000002				 0.000004
 0.000021				 0.000021
 0.000021				 0.000021
 0.002750				 0.002750
 0.097295				 0.097295
 0.266503				 0.266503
 0.266503				 0.266503
36.646291				36.646291
309.494702				309.494702
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000


x^3 + 300x + 10^8
first order approximation		second order aprroximation
31.000000				 1.000000
 3.010000				 0.010000
 0.300100				 0.000101
 0.030005				 0.000001
 0.003004				 0.000024
 0.000274				 0.000274
 0.004745				 0.004745
 0.069761				 0.069761
 0.516796				 0.516796
 3.953552				 3.953552
 3.953552				 3.953552
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
600.000000				600.000000
*/

/*
Conclusion
For larger h, the local analysis is dominated by truncation error, 
and for smaller x it is dominated by round-off error.

Comparing different order of approximation:
THe second order approximation is less prone to round-off error, or it approaches consistency much faster.

Comparing functino with and without offset:
When there is an offset on b intercept, the region where result can be consistent becomes smaller.
This is because the change in input is when x input magnitude reaches -10, then x^3 would be -30. 
With an offset on the magnitude of 8, the difference would be 38, truncation error happens. 
*/