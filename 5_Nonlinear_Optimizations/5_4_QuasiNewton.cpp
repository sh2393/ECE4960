#include <iostream>
#include <cmath>
using namespace std;

double f4(double x){
	return exp(100.0*x)-1;
}

double f4Prime(double x){
	return 100.0*exp(100.0*x);
}


void QuasiNewtonLineSearch(double x){
	double tol = 1E-10;
	double deltaX = 0;
	int iteration = 1;

	do{

		deltaX = -(0.0001*x)/(f4(1.0001*x) - f4(x))*f4(x);
        
        double tempdeltaX = deltaX;
        
        // Line Search: find a multiple of deltaX which makes the function as close to zero as possible
        for (double i=1.0; i<=100000.0; i++) {
            if (f4(x-tempdeltaX) > f4(x-i*deltaX)) {
                tempdeltaX = i*deltaX;
            }
        }
        
        deltaX = tempdeltaX;
        x = x + deltaX;
        
        cout << endl << "Iteration # " << iteration++ << endl;
        cout << "x = " << x << endl;
        cout << "deltaX = " << deltaX << endl;
        cout << "f(" << x << ") = " << f4(x) << endl;

	}while(abs(f4(x)) > tol);
}

int main(){
	QuasiNewtonLineSearch(1.0);
	return 0;
}