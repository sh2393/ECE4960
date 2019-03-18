/*
CSR_matrix.h
Joyce Huang sh2393

March 16, 2019
*/

#ifndef _CSR_MATRIX_H
#define _CSR_MATRIX_H
#define MAX(x,y) ((x>y)?x:y)

#include <vector>

using namespace std;

class Matrix{
public:
	vector<double> value;
    vector<int> rowPtr;
    vector<int> colInd;

	double retrieveElement(int x, int y);

	void addElement(double val, int row, int col);

	void productAx(vector<double> *x, vector<double> *b);

	void printMatrix(void);
};

Matrix UpperMatrix(Matrix matrix);

Matrix LowerMatrix(Matrix matrix);

Matrix matrixMultiplier(Matrix A, Matrix B);

Matrix matrixAddition(Matrix A, Matrix B);

Matrix InverseDiagonal(Matrix matrix);

double residualNorm(Matrix *matrix, vector<double> *x, vector<double> *b);

vector<double> Jacobian(Matrix matrix, vector<double> b, vector<double> x, double epsilon);


#endif
