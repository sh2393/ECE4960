
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "methods.hpp"

using namespace std;

vector<double> x;
vector<double> y;

double W(double a, double m) {
    double sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += pow(log(a)+m*log(x[i]) - log(y[i]), 2);
    }
    return sum;
}

double f1 (double a, double m) {
    double sum = 0;
    for (int i = 0; i < x.size(); i++) {
        sum += m*pow(log(x[i]),2)+log(a)*log(x[i]) - log(x[i])*log(y[i]);
    }
    return sum;
}

double f2 (double a, double m) {
    return (W(a, m*1.0001) - W(a,m))/(0.0001*m);
}

pair<double, double> deltas(double a, double m){
	double h00 = 0.0, h01 = 0.0, h10=0.0, h11=0.0;
    
    for (int i = 0; i < x.size(); i++) {
        h00 += (W(a*1.0001*1.0001, m)-2*W(a*1.0001,m)+W(a,m))/(0.0001*0.0001*a*a);
        h01 += (W(a*1.0001, m*1.0001)-2*W(a, m*1.0001)+W(a,m))/(0.0001*0.0001*a*m);
        h10 += (W(a*1.0001, m*1.0001)-2*W(a*1.0001, m)+W(a,m))/(0.0001*0.0001*a*m);
        h11 += (W(a, m*1.0001*1.0001)-2*W(a,m*1.0001)+W(a,m))/(0.0001*0.0001*m*m);
    }

    double det = -1.0/(h00*h11 - h01*h10);
    double da0 = det*(h11 *f1(a,m) - h01 * f2(a,m));
    double da1 = det*((-1.0)*h10 * f1(a,m) + h00 * f2(a,m));

    return make_pair(da0, da1);
}



int validate(){
	//constants
	double c0 = 10.0;
	double m = -0.5;

	//Generate 10 samples of internally calculated values with random noises 
	srand((unsigned)time(0));
	for(int i = 1; i <= 10; i++){
		double noise = ((double) (rand() % 10 )+ 10 )/100.0;
		double val = c0*pow(i, m);

		x.push_back(i);
		y.push_back(val * (1+noise));
	}


	// Parameter Extraction (quasi-Newton)

    double a0 = 11.00;
    double a1 = -0.865;
    pair<double, double> das;
   
    while (abs(f1(a0,a1)) > 1E-3 || abs(f2(a0,a1)) > 10E-3) {
        das = deltas(a0, a1);
        a0 += das.first;
        a1 += das.second;
    }

    printf("a0 = %f, a1 = %f\n", a0, a1);

	return 0;
}