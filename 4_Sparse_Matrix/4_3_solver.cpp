#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <armadillo>
using namespace std;
using namespace arma;

int main(){
	
	colvec B = {199, 197};

	for(int p = -2; p >= -9; p--){
		double e = pow(10, p);
		mat A = {{100, 99}, {99, 98.01 - e}};
		mat x = solve(A, B);

		printf("x, y pair\n");
		x.print();

		//this part is kinda weird
		colvec residual_vector = A*x - B;
		printf("second norm is %.16e\n", norm(residual_vector));
	}

	return 0;
}