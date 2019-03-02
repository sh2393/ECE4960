#include "matrix.h"
#include <iostream>
using namespace std;

int productAx(matrix* A, matrix* x, matrix* B){
	for(int i = 0; i < A.get_height(); i++){
		for(int j = 0; j < A.get_width(); j++){
			B[i] += A[i][j] * x[i];
		}
	}
	return 0;
}

int main(){
	matrix<int> A(5, 5);
	A[0][0] = 0; A[0][1] = 0; A[0][2] = 0; A[0][3] = 0; A[0][4] = 0;
	A[1][0] = 0; A[1][1] = 0; A[1][2] = 0; A[1][3] = 0; A[1][4] = 0;
	A[2][0] = 0; A[2][1] = 0; A[2][2] = 0; A[2][3] = 0; A[2][4] = 0;
	A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 0; A[3][4] = 0;
	A[4][0] = 0; A[4][1] = 0; A[4][2] = 0; A[4][3] = 0; A[4][4] = 0;

	matrix<int> x(5, 1);
	x[0][0] = 5;
	x[1][0] = 4;
	x[2][0] = 3;
	x[3][0] = 2;
	x[4][0] = 1;

	matrix<int> B(5, 1);

	int flag = productAx(A, x, B);
	cout << B[0][0] << endl;
	return 0;

}