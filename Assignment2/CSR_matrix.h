/*
CSR_matrix.h
Joyce Huang sh2393

March 16, 2019
*/

#ifndef _CSR_MATRIX_H
#define _CSR_MATRIX_H

#include <vector>
using namespace std;

struct Matrix {
    vector<double> value;
    vector<int> rowPtr;
    vector<int> colInd;
};



Matrix createMatrix (void);

double retrieveElement(Matrix *matrix, int x, int y);

Matrix UpperMatrix(Matrix matrix);

Matrix LowerMatrix(Matrix matrix);

void addElement(Matrix *matrix, double value, int row, int col);

void productAx(Matrix *A, vector<double> *x, vector<double> *b);

Matrix matrixMultiplier(Matrix m1, Matrix m2);

Matrix matrixAddition(Matrix m1, Matrix m2);

Matrix InverseDiagonal(Matrix matrix);

double computeError(Matrix *matrix, vector<double> *x, vector<double> *b);

void printout(Matrix matrix);

vector<double> Jacobian(Matrix matrix, vector<double> b, vector<double> x, double errorTolerance);


#endif
