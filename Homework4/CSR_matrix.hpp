#ifndef _CSR_MATRIX_H
#define _CSR_MATRIX_H

#include <vector>
using namespace std;

#define SUCCESS 0
#define FAIL_UNMATCHED_RANK 1
#define FAIL_INF 2
#define FAIL_NAN 3
#define ZTO(i) (i-1)

class Matrix{
private:
	int rank;
	vector<double> value;
	vector<int> rowPtr;
	vector<int> colInd;

public:
	Matrix();

	Matrix(vector<double> val, vector<int> row, vector<int> col);

	void addElement(int ri, int ci, double value);
	void deleteElement(int ri, int ci);
	double retrieveElement(int ri, int ci);
	int rankMatrix();
	int countElementMatrix();

	void printMatrix();

	//Swith i-th row and j-th row
	int rowPermute(int i, int j);
	// add the ith row multiplied by a constant a to the jth row
	int rowScale(int i, int j, double a);
	//product of matrix A and vector x
	int productAx(vector<double> x, vector<double> *result);
	void printmember(int option);
};


#endif