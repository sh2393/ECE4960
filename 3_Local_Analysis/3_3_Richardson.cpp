#include <iostream>
#include <cmath>

double f(double x){
	return pow(x, 3);
}

double taylorFirst(double x, double h){
	return (f(x+h)-f(x))/h;
}

double taylorSecond(double x, double h){
	return -f(x+2*h)/(2*h) - 3*f(x)/(2*h) + 2 * f(x+h)/h;
}

int main(){
	double truth = 3;
	double x = 1.0;

	printf("h\terror1\t\t\terror2\t\t\terror3\t\t\teta_truth\t\teta_rel\n");
	for(int i = -4; i >= -20; i--){

		double h = pow(2, i);
		double e1 = taylorFirst(x, h)-truth;
		double e2 = taylorFirst(x, 2*h)-truth;
		double eta_truth = e2/e1;
		double e4 = taylorFirst(x, 4*h)-truth;
		double eta_rel = (e4-e2)/(e2-e1);

		double e3 = taylorSecond(x, h)-truth;

		
		printf("2^-%d\t%9.6f \t\t %9.6f \t\t %9.6f\t\t %9.6f\t\t %9.6f\t\t\n", i, e1, e2, e3, eta_truth, eta_rel);
	}
	return 0;
}