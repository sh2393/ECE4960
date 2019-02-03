#include "fp_exception.h"

using namespace std;

bool is_equal(double x, double y)
{
	if (x == y) return true;
	else return false;
}

void fp_overflow(void)
{
	printf("\nfloating point overflow\n");

	double dmax = DBL_MAX;
	double dsquare = dmax * dmax;
	printf("double max squared = %f\n", dsquare);

	if (dsquare == DBL_INF) cout << "double overflow exception: PASSED" << endl;
	else cout << "double overflow exception: FAILED" << endl; 

}

void fp_infinity(void)
{
	printf("floating point positive infinity\n");
	double pos_inf = 1.0/0.0;
	printf("1.0/0.0 = %f", pos_inf);

	printf("infinity equivalence\n");
	if (pos_inf == pos_inf) printf("INF == INF\n");
	else printf("INF != INF\n");

	printf("infinity propogation\n");
	double result1 = pos_inf /200;
	printf("(1.0/0.0)/200 = %f\n", result1);
}

bool isINF(double x)
{
	if(x > DBL_MAX && (1.0/x == 0)) return true;
	else return false;
}

void fp_ninf(void)
{
	printf("negative infinity\n");
	double neg_inf = -1.0/0.0;
	printf("-1.0/0.0 = %f\n", neg_inf);

	printf("equivalence\n");
	if(neg_inf == neg_inf) printf("NINF == NINF\n");
	else printf("NINF != NINF\n");

	printf("infinity propogation\n");
	double result2 = neg_inf / 200;
	printf("(-1.0/0.0) = %f\n", result2);
}

bool isNINF(double x)
{
	if (x < DBL_MIN && (-1.0/x == 0)) return true;
	else return false;
}

void fp_nan(void)
{
	//generation
	double double_nan = 0.0/0.0;
	printf("0.0/0.0 = %f\n", double_nan);
	double imaginary = sqrt(-1.0);
	printf("sqrt(-1.0) = %f\n", imaginary);

	//detection
	printf("isnan(0.0/0.0) : %d\n", isnan(double_nan));
	printf("isnan(sqrt(-1.0_ : %d\n", isnan(imaginary));

	//equivalence
	printf("NaN equivalence\n");
	if (is_equal(double_nan, double_nan)) printf("NaN == Nan\n");
	else printf("Nan != Nan\n");

	// propogation
	printf("NaN propogation\n");
	double result0 = double_nan * 200;
	printf("(0.0/0.0)*200 = %f\n", result0);

	// interaction with INF, NINF
	double result1 = double_nan * (-1.0/0.0);
	printf("Nan * NINF = %f\n", result1);
	double result2 = double_nan = (1.0/0.0);
	printf("Nan * INF = %f\n", result2);
}


void fp_signed_zero(void)
{
	printf("signed zero\n");
	double px = 1.0;
	double nx = -1.0;

	px *= pow(10, -307);
	nx *= pow(10, -307);
	for(int i = 1; i < 20; i++){
		px/=10.0;
		nx/=10.0;
		printf("log(px) = %f\n", log(px));
		printf("log(nx) = %f\n", log(nx));
		printf("sin(px)/px = %f\n", sin(px)/px);
		printf("sin(nx)/nx = %f\n", sin(nx)/nx);
		printf("sin(nx)/px = %f\n", sin(nx)/px);
	}

	
}

bool isPositiveZero(double x){
	if(isINF(1.0/x)) return true;
	else return false;
}

bool isNegativeZero(double x){
	if(isNINF(1.0/x)) return true;
	else return false;
}


void fp_underflow(void)
{
	printf("gradual underflow\n");

	double x = 1.234567890123456789;
	double y = 1.625;
	double z = 1.6875;
	double w = 1.0;

	x *= pow(10, -307);
	y *= pow(10, -307);
	z *= pow(10, -307);
	w *= pow(10, -307);

	for(int i = 1; i < 20; i++)
	{
		//division
		x/=10.0;
		printf("x/10 = %.16e\n", x);

		//subtraction
		y/=10.0;
		z/=10.0;
		printf("y-z = %.16f\n", y-z);
		if( y==z){
			printf("y==z, ");
			if (y-z == 0) printf("gradual underflow: PASSED\n");
		} 
		if( y != z){
			printf("y!=z\n");
			if(y-z == 0) printf("gradual underflow:FAILED\n");
		}

		//sine of small number
		w/=10.0;
		printf("sin(1.234567890123456789*x)/x = %f\n", sin(1.234567890123456789*w)/w);

	}

}
