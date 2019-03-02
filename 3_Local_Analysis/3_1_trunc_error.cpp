#include <iostream>
#include <cmath>

using namespace std;

#define GRND_TRUTH 600

double f(double x)
{
	return pow(x, 3) + 300*x;
}

double derivative(double x, double h)
{
	return (f(x+h) -f(x))/h;
}

double err(double x, double h)
{
	double my_err = derivative(x, h) - GRND_TRUTH;
	return log10(abs(my_err));
}



int main(){
	double x = 10;
	double h = 10;
	for(int i = 0; i >= -15; i--)
	{
		h /= 10;
		cout << "h = " << h << endl;
		cout << "error = " << err(x, h) << endl;
		cout << endl;
	}
	return 0;
}
