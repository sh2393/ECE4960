/*
Joyce Huang sh2393
Backward Euler, Forward Euler

Idea: 
Backward Euler is stable, unconditionally converges. 
Forward Euler is stable only when time step is carefully chose for delta_t < -1/a;
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double f(double t){
	return exp(-t);
}

double forwardEuler(double t, double delta_t){
	return (1+delta_t) * f(t-delta_t);
}

double backwardEuler(double t, double delta_t){
	return (1/(1-delta_t)) * f(t-delta_t);
}

int main(){
	vector<double> deltas{0.5, 1.0, 2.0};
	for(double delta_t: deltas){
		printf("\ndelta_t = %f\n", delta_t);
		printf("\tforward error\t\tbackward error\n");
		for(double t = 0; t <= 20; t++){
			printf("%2.0f\t", t);
			double truth = f(t);
			double forward = forwardEuler(t, delta_t);
			double ferror = forward-truth;
			printf("%9.6f\t\t", ferror);

			double backward = backwardEuler(t, delta_t);
			double berror = backward-truth;
			printf("%9.6f\n", berror);
		}
	}

	return 0;
}

