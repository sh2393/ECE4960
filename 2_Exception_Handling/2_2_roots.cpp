#include <iostream>
#include <math.h>
using namespace std;

int main(){
	//2.2
	int a = 10e-20;
	int b = 10e3;
	int c = 10e3;

	int x1 = (-b+sqrt(b^2-4*a*c))/(2*a);
	int x2 = (-b-sqrt(b^2-4*a*c))/(2*a);
	int x3 = -2*c/(-b+sqrt(b^2-4*a*c));
	int x4 = -2*c/(-b-sqrt(b^2-4*a*c));

	cout << x1 << endl;
	cout << x2 << endl;
	cout << x3 << endl;
	cout << x4 << endl;

}