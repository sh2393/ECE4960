#ifndef _CSR_MATRIX_H
#define _CSR_MATRIX_H

#include <vector>
using namespace std;

#define SUCCESS 0
#define FAIL_UNMATCHED_RANK 1
#define FAIL_INF 2
#define FAIL_NAN 3

class Matrix{
private:
	int rank;
	vector<int> value;
	vector<int> rowPtr;
	vector<int> colInd;

public:
	Matrix();

	Matrix(vector<int> val, vector<int> row, vector<int> col);

	void addElement(int ri, int ci, int value);
	void deleteElement(int ri, int ci);
	double retrieveElement(int ri, int ci);
	int rankMatrix();
	int countElementMatrix();

	void printMatrix();

	//4.2
	//Swith i-th row and j-th row
	int rowPermute(int i, int j);
	// add the ith row multiplied by a constant a to the jth row
	int rowScale(int i, int j, int a);
	//product of matrix A and vector x
	int productAx(vector<int> x, vector<int> *result);

};

#endif