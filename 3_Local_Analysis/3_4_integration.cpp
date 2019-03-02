#include <iostream>
#include <cmath>
#define TRUTH 2.3504

using namespace std;

double f(double x){
	return exp(x);
}

double trap(double left, double right){
	return 2*(f(left)/2+f(right)/2);
}

int main(){
	double left = -1;
	double step = 2/10000;
	double right = left + step;
	double sum = 0;
	for(int i = 0; i <= 10000; i++){
		sum += trap(left, right);
		left += step;
		right += step;
	}

	cout << sum << endl;
	
	return 0;
}