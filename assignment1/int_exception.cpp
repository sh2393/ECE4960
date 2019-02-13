#include "int_exception.h"
#include "helpers.h"

char int_buffer[200];

int factorial(int x)
{
	if(x == 0) return 1;
	return x*factorial(x-1);
}

int int_division(int x, int y)
{
	if(y == 0) throw MyException();
	else return x/y;
}

void int_overflow(void)
{
	int n = 15;
	int x = factorial(n);
	sprintf(int_buffer, "\n================\n15!\n================\n");
	write_log(int_buffer);
	check_factorial_overflow(x, n, __func__);
	if (!pass_int_overflow(x)) report_violation(__func__);
}


void int_zerodiv(void)
{
	sprintf(int_buffer, "\n================\n2/0\n================\n");
	write_log(int_buffer);

	try
	{
		int zero = 0;
		int result = int_division(2, zero);	
		if (!pass_int_divzero(result)) report_violation(__func__);
	}
	catch(std::exception& e)
	{
		sprintf(int_buffer, "Exception: %s\n", e.what());
		write_log(int_buffer);
	}
}



