/*Homework #2 Differention in Local Analysis
* Joyce Huang
* sh2393
* 
* Darwin appledeMacBook-Pro-2.local 16.7.0 
* Darwin Kernel Version 16.7.0: Wed Oct  4 00:17:00 PDT 2017; 
* root:xnu-3789.71.6~1/RELEASE_X86_64 x86_64
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define GRND_TRUTH1 600
#define GRND_TRUTH2 3

namespace p1
{

	double f(double x) 					{return pow(x, 3)+300*x;}
	double f1(double x) 				{return pow(x, 3) + 300*x + pow(10, 10);}

	double fderiv1 (double x, double h) {return (f(x+h)-f(x))/h;}
	double fderiv2 (double x, double h) {return (f(x+h)-f(x-h))/(2*h);}

	double f1deriv1(double x, double h) {return (f1(x+h)-f1(x))/h;}
	double f1deriv2(double x, double h) {return (f1(x+h)-f1(x-h))/(2*h);}
}

namespace p2
{
	double f(double x) {return pow(x, 3);}

	double fderiv1(double x, double h) {return (f(x+h)-f(x))/h;}

	double fderiv2(double x, double h) 
	{
		double z = 2*h;
		return -1*f(x+z)/z - 3*f(x)/z + 2*f(x+h)/h;
	}

	double fderiv3(double x, double h)
	{
		double z = 2*h;
		return -1/z*f(x+z) - 3/z*f(x) + 2/h*f(x+h);
	}

}

int main()
{
	ofstream problem1;
	problem1.open("problem1.csv");
	double x1 = 10;
	double h1 = 1;
	printf("x1 = %f, ground truth = %d\n", x1, GRND_TRUTH1);

	printf("%16s, %16s\n", "h", "error");
	for(int i = 1; i <=15; i++)
	{
		double o1 = p1::fderiv1(x1, h1) - GRND_TRUTH1;
		printf("%16.5e, %16f\n", h1, o1);
		problem1 << -1 * log10(h1) << "," << log10(abs(o1)) << endl;

		h1 /= 10;
	}

	printf("\n");
	x1 = 10;
	h1 = 1;
	for(int i = 1; i <=15; i++)
	{
		double o1 = p1::f1deriv1(x1, h1) - GRND_TRUTH1;
		printf("%16.5e, %16f\n", h1, o1);
		problem1 << -1 * log10(h1) << "," << log10(abs(o1)) << endl;
		h1 /= 10;
	}

	printf("\n");
	x1 = 10;
	h1 = 1;
	for(int i = 1; i <=15; i++)
	{
		double o1 = p1::fderiv2(x1, h1) - GRND_TRUTH1;
		printf("%16.5e, %16f\n", h1, o1);
		problem1 << -1 * log10(h1) << "," << log10(abs(o1)) << endl;
		h1 /= 10;
	}

	printf("\n");
	x1 = 10;
	h1 = 1;
	for(int i = 1; i <=15; i++)
	{
		double o1 = p1::f1deriv2(x1, h1) - GRND_TRUTH1;
		printf("%16.5e, %16f\n", h1, o1);
		problem1 << -1 * log10(h1) << "," << log10(abs(o1)) << endl;
		h1 /= 10;
	}


	problem1.close();

	//problem 2
	ofstream problem2;
	problem2.open("problem2.csv");

	double x = 1;
	double h = pow(2, -4);
	for(int i = 4; i <= 40; i++)
	{
		double error1 = p2::fderiv1(x, h)-GRND_TRUTH2;
		printf("%16.5e, %16f\n", h, error1);
		problem2 << h << "," << abs(error1) << endl;
		h/=2;
	}

	x = 1;
	h = pow(2, -4);
	for(int i = 4; i <= 40; i++)
	{
		double error1 = p2::fderiv2(x, h)-GRND_TRUTH2;
		printf("%16.5e, %16f\n", h, error1);
		problem2 << h << "," << abs(error1) << endl;
		h/=2;
	}

	x = 1;
	h = pow(2, -4);
	for(int i = 4; i <= 40; i++)
	{
		double error1 = p2::fderiv3(x, h)-GRND_TRUTH2;
		printf("%16.5e, %16f\n", h, error1);
		problem2 << h << "," << abs(error1) << endl;
		h/=2;
	}

	x = 1;
	h = pow(2, -4);
	for(int i = 4; i <= 40; i++)
	{
		double error1 = p2::fderiv1(x, h)-GRND_TRUTH2;
		double error2 = p2::fderiv1(x, 2*h)-GRND_TRUTH2;
		double eta = error2/error1;
		printf("%16.5e, %16f\n", h, eta);
		problem2 << h << "," << abs(eta) << endl;
		h/=2;
	}

	x = 1;
	h = pow(2, -4);
	for(int i = 4; i <= 40; i++)
	{
		double error1 = p2::fderiv1(x, h)-GRND_TRUTH2;
		double error2 = p2::fderiv1(x, 2*h)-GRND_TRUTH2;
		double error4 = p2::fderiv1(x, 4*h)-GRND_TRUTH2;
		double eta = (error4-error2)/(error2-error1);
		printf("%16.5e, %16f\n", h, eta);
		problem2 << h << "," << abs(eta) << endl;
		h/=2;
	}

	problem2.close();

	return 0;
}