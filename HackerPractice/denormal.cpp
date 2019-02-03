#include <iostream>
#include <math.h>
#include <float.h>
using namespace std;
#include <tgmath.h>

int main(){
	double x = 1.234567890123456789;
	int i = 1;

	x *= pow(10, -307);
	for(i = 1; i < 20; i++){
		x/=10.0;
		printf("%.16e\n", x);
	}
}

