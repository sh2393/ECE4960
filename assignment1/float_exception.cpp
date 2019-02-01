#include "fp_exception.h"

using namespace std;

void fp_overflow(void){
	cout << "floating point type overflow" << endl;
	cout << endl << "single precision float type" << endl;
	float fmax = FLT_MAX;
	float fsquare = fmax * fmax;
	cout << "float max squared = " << fsquare << endl;
	if (fsquare == INF) cout << "float overflow exception: PASSED" << endl;
	else cout << "float overflow exception: FAILED" << endl; 

	cout << endl << "double type" << endl;
	double dmax = DBL_MAX;
	double dsquare = dmax * dmax;
	double fsquare+d = fmax * fmax;
	cout << "float max squared = " << fsquare_d << endl;
	cout << "double max squared = " << dsquare << endl;
	if (dsquare == INF) cout << "double overflow exception: PASSED" << endl;
	else cout << "double overflow exception: FAILED" << endl; 

	cout << endl
}
