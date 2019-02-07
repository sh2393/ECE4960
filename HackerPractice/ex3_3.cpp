#include <iostream>
#include <cmath>
using namespace std;

#define GRND_TRUTH 3

double f(double x) {return pow(x, 3);}

double ffirst(double x, double h)
{
	return (f(x+h)-f(x))/h;
}

double fsecond(double x, double h)
{
	double z = 2*h;
	return -1*f(x+z)/z - 3*f(x)/z + 2*f(x+h)/h;
}


int main()
{
	double x = 1;
	double h = pow(2, -4);

	//eta one
	// for(int i = 4; i <= 40; i++)
	// {
	// 	double error1 = ffirst(x, h)-GRND_TRUTH;
	// 	double error2 = ffirst(x, 2*h)-GRND_TRUTH;

	// 	double eta = error2/error1;
	// 	cout << eta << endl;

	// 	h/=2;
	// }

	//first approximation
	// for(int i = 4; i <= 40; i++)
	// {
	// 	double calc1 = ffirst(x, h);
	// 	double calc2 = ffirst(x, 2*h);
	// 	double calc4 = ffirst(x, 4*h);

	// 	// double eta = error2/error1;
	// 	// cout << eta << endl;

	// 	double eta2 = (calc4-calc2)/(calc2-calc1);
	// 	cout << eta2 << endl;

	// 	h/=2;
	// }

	// second truth
	// for(int i = 4; i <= 40; i++)
	// {
	// 	double error1 = fsecond(x, h)-GRND_TRUTH;
	// 	double error2 = fsecond(x, 2*h)-GRND_TRUTH;
	// 	double error4 = fsecond(x, 4*h)-GRND_TRUTH;

	// 	// double eta = error2/error1;
	// 	// cout << eta << endl;

	// 	double eta2 = (error4-error2)/(error2-error1);
	// 	cout << eta2 << endl;

	// 	h/=2;
	// }

	//second approximation
	for(int i = 4; i <= 40; i++)
	{
		double calc1 = fsecond(x, h);
		double calc2 = fsecond(x, 2*h);
		double calc4 = fsecond(x, 4*h);

		// double eta = error2/error1;
		// cout << eta << endl;

		double eta2 = (calc4-calc2)/(calc2-calc1);
		cout << eta2 << endl;

		h/=2;
	}

	return 0;
}