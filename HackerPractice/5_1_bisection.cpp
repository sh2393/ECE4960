#include <iostream>
#include <cmath>
using namespace std;

double f(double x){
	return exp(x)-1;
}

double biseciton(double left, double right, double epsilon){
	// if (left >= right) return 0;
	// double mid = (left+right)/2;
	// if (abs(f(mid))<epsilon){
	// 	cout << mid << endl;
	// 	return mid;
	// }
	// else{
	// 	return biseciton(left, mid, epsilon);
	// 	return biseciton(mid, right, epsilon);
	// }
	double mid = (left+right)/2;
	int count = 0;
	while(abs(f(mid)) > epsilon){
		if(f(mid) > 0){
			
		}
	}
}

int main(){
	double left = -5;
	double right = 10;
	double epsilon = pow(10, -7);
	cout << biseciton(left, right, epsilon) << endl;
	return 0;	
}