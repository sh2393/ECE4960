#include <iostream>
#include <cmath>
using namespace std;



vector<double> x = {1.0, 4.5, 9.0, 20.0, 74.0, 181.0};
vector<double> y = {3.0, 49.4, 245.0, 1808.0, 2.2E4, 7.3E4};


double F1(double a, double m){
	double f = 0;
	for(int i = 0; i < x.size(); i++){
		 f += (a*pow(x[i], 2.0*m) - pow(x[i], m)*y[i]);
	}
	return f;
}

double F2(double a, double m){
	double f = 0;
	for(int i = 0; i < x.size(); i++){
		f += (pow(a, 2) * log(x[i]) * pow(x[i], 2.0*m) - a*log(x[i])*pow(x[i], m)*y[i]);
	}
}

double PowerLaw(double a, double m){
	double sum = 0;
	for(int i = 0; i < x.size(); i++){
		sum += pow(a*pow(x[i], m) - y[i], 2);
	}
	return sum;
}

void QNParamExtraction(double a, double m){
}