#include <iostream>
#include <cmath>
#include <map>
using namespace std;

#define RECT 0
#define TRAP 1
#define MID 2
#define SIMP 3
#define G2 4
#define G3 5

double f(double x){return exp(x);}

map<int, double> computation(double h, double left, double right){
	map<int, double> dict;
	double rectangle=0, trapezoid=0, midpoint=0, simpson=0, gaussian2=0, gaussian3=0;
	double a4= 1/(2*sqrt(3));
	double a1 = 5.0/18.0, a2 = 8.0/18.0, a3 = sqrt(3)/(2*sqrt(3));
	double mid = 0;
	
	for(double x = left; x <=right; x += h){
		mid = x+h/2.0;

		rectangle += h*f(x);
		trapezoid += h*(f(x)/2.0 + f(x+h)/2.0);
		midpoint += h*f(x + h/2.0);
		simpson += h*(1.0/6.0*f(x) + 4.0/6.0*f(mid) + 1.0/6.0*f(x+h));
		gaussian2 += h*(f(mid - a4*h)/2.0 + f(mid + a4*h)/2.0);
		gaussian3 += h*( a1*f(mid-a3*h) + a2*f(mid) + a1*f(mid + a3*h) );
	}

	dict[RECT] = rectangle;
	dict[TRAP] = trapezoid;
	dict[MID] = midpoint;
	dict[SIMP] = simpson;
	dict[G2] = gaussian2;
	dict[G3] = gaussian3;

	return dict;
}


int main(){
	double truth = f(1)-f(-1);
	double h = 0.001;
	map<int, double> result = computation(h, -1, 1);
	printf("truth = %f\n", truth);
	printf("rectangle \t| trapezoid \t| midpoint \t| simpson\t | gaussian2\t | gaussian3\n");
	printf("%f\t%f\t %f\t\t %f\t %f\t %f\n", 
		result[RECT], result[TRAP], result[MID], result[SIMP], result[G2], result[G3]);

	return 0;
}