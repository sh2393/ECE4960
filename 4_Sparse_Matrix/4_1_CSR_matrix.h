#ifndef _CSR_MATRIX_H
#define _CSR_MATRIX_H

#include <vector>
using namespace std;


class Matrix{
private:
	int rank;
	vector<int> value;
	vector<int> rowPtr;
	vector<int> colInd;

public:
	Matrix();
	
	Matrix(vector<int> val, vector<int> row, vector<int> col){
		value = val;
		rowPtr = row;
		colInd = col;
	}

	void addElement(int ri, int ci, int value);
	void deleteElement(int ri, int ci);
	double retrieveElement(int ri, int ci);
	int rankMatrix();
	int countElementMatrix();

	void printMatrix();
};




#endif