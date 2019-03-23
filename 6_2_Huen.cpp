#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<double> xtrue{2.0, 6.1946, 14.843, 33.677, 75.339};
double h = 1.0;

double x(double t){
	return 4/1.3*(exp(0.8*t) - exp(0.5*t))+ 2*exp(-0.5*t);
}

double dxdt(double x, double t){
	return 4*exp(0.8*t) - 0.5*x;
}

void forwardEuler(){
	double x_i = 2.0, err = 0;
	for(double ti = 0; ti<4.0; ti++){
		x_i += h*dxdt(ti, x_i);
		err =abs(x_i-xtrue[ti+1])/xtrue[ti+1];
		cout << x_i << " " << err << endl;

	}
}

void iterHuen(){
}

int main(){
	double tol = pow(10, -3);
	forwardEuler();

	return 0;
}