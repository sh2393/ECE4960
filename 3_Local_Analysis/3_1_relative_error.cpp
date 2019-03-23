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

	printf("first order approximation\t\tsecond order aprroximation\n");
	printf("x^3 + 300x\tx^3 + 300x + 10^8 x^3 + 300x\tx^3 + 300x + 10^8\n");
	for(int i = 0; i >= -25; i--){
		double h = pow(10, i);
		printf("%9.6f\t", abs(f1deriv(x, h, &a)-truth));
		printf("%9.6f\t", abs(f1deriv(x, h, &b)-truth));
		printf("%9.6f\t", abs(f2deriv(x, h, &a)-truth));
		printf("%9.6f\t", abs(f2deriv(x, h, &b)-truth));
		printf("\n");
	}


	return 0;
}

/*
Output
first order approximation		second order aprroximation
x^3 + 300x	x^3 + 300x + 10^8 x^3 + 300x	x^3 + 300x + 10^8
31.000000	31.000000	 1.000000	 1.000000	
 3.010000	 3.010000	 0.010000	 0.010000	
 0.300100	 0.300100	 0.000100	 0.000101	
 0.030001	 0.030005	 0.000001	 0.000001	
 0.003000	 0.003004	 0.000000	 0.000024	
 0.000300	 0.000274	 0.000000	 0.000274	
 0.000029	 0.004745	 0.000001	 0.004745	
 0.000002	 0.069761	 0.000004	 0.069761	
 0.000021	 0.516796	 0.000021	 0.516796	
 0.000021	 3.953552	 0.000021	 3.953552	
 0.002750	 3.953552	 0.002750	 3.953552	
 0.097295	600.000000	 0.097295	600.000000	
 0.266503	600.000000	 0.266503	600.000000	
 0.266503	600.000000	 0.266503	600.000000	
36.646291	600.000000	36.646291	600.000000	
309.494702	600.000000	309.494702	600.000000	
600.000000	600.000000	600.000000	600.000000	
600.000000	600.000000	600.000000	600.000000	
600.000000	600.000000	600.000000	600.000000	
600.000000	600.000000	600.000000	600.000000	
600.000000	600.000000	600.000000	600.000000	
600.000000	600.000000	600.000000	600.000000	
600.000000	600.000000	600.000000	600.000000	
600.000000	600.000000	600.000000	600.000000	
600.000000	600.000000	600.000000	600.000000	
600.000000	600.000000	600.000000	600.000000
*/

/*
Result, we can see that for larger h the local analysis is dominated by truncation error, 
and for smaller x it is dominated by round-off error.
The second order approximation is more prone to input error.
*/