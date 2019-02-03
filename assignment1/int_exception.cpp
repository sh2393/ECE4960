//#include <iostream>
#include "int_exception.h"
using namespace std;


int factorial(int x)
{
	if(x == 0) return 1;
	return x*factorial(x-1);
}

void integer_overflow(void)
{
	cout << "integer overflow observation: factorial" << endl;

	int x = factorial(15);
	cout << "15! = " << factorial(15) << endl;

	//check if overflows
	for(int i = 1; i <= 15; i++) x /= i; 
	if (x != 1) cout << "integer overflowed" << endl;
}

int int_division(int x, int y)
{
	if(y == 0) throw MyException();
	else return x/y;
}

void divide_by_zero()
{
	cout << "divide by zero observation" << endl;
	int m = 10, n = 0;

	try
	{
		int result = int_division(m, n);
		printf("%d/%d = %d", m, n, result);
	}
	catch(exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}



