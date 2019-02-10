#include <iostream>
#include <cmath>
using namespace std;


double f(double t){ return exp(-t);}

double forward(double t, double delta_t)
{
	if (t <= 0) return 1;
	return (1- delta_t)*forward(t-delta_t, delta_t);
}

double backward(double t, double delta_t)
{
	if (t <= 0) return 1;
	return 1/(1+delta_t) * backward(t-delta_t, delta_t);
}

int main()
{
	for(double t = 0; t <=20; t++){
		//cout << f(t) << endl;
		double delta_t = 0.5;
		//cout << forward(t, delta_t) << endl;
		cout << backward(t, delta_t) << endl;
		cout << endl;
	}
	return 0;
}