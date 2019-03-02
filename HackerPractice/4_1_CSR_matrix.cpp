//Linear Algebra and Sparse Matrices

#include <iostream>
#include <vector>
#include <cmath>
#include "4_1_CSR_matrix.h"

using namespace std;

void addElement(int rowInd, int colInd, int value){
	// int row = int(rowInd/rank);
	// rowPtr.append(row);
	// colInd.append(colInd);
	// value.append(value);
}


//void Matrix::deleteElement(int ri, int ci);

double Matrix::retrieveElement(int ri, int ci){
	int start = rowPtr[ri];
	int end;
	if (ri == rowPtr.size()-1){ //last element
		end = colInd.size();
	}else{
		end = rowPtr[ri+1];
	}

	for(int i = start; i < end; i++){
		if (colInd[i] == ci){
			return value[i];
		}
	}

	return 0;
}

int rankMatrix();
int countElementMatrix();

void printMatrix();

