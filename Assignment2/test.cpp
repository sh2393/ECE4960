/*
test.cpp
Joyce Huang sh2393

March 16, 2019
*/

#include <iostream>
#include "test.h"

using namespace std;

int testLoad(Matrix *largeMatrix){
    if (largeMatrix->retrieveElement(1, 1) != 600 || largeMatrix->retrieveElement(500, 30) != 0){
        fprintf(stderr, "%s", "retrieveElement Failed\n");
        return FAIL;
    }
    return SUCCESS;
}


int testUpperMatrix(Matrix matrix, Matrix upper) {    
    int numRow = matrix.rowPtr.size()-1;
    
    for (int row = 0; row < numRow; row++) {
        for (int index = matrix.rowPtr[row]; index < matrix.rowPtr[row+1]; index++) {
            double entry = upper.retrieveElement(row, matrix.colInd[index]);
            if (matrix.colInd[index] > row) {
                if (matrix.value[index] != entry) {
                    fprintf(stderr, "%s", "testUpperMatrix Failed\n");
                    return FAIL;
                }
            }
        }
    }
    return SUCCESS;    
}


int testLowerMatrix(Matrix matrix, Matrix lower) {
    
    int numRow = matrix.rowPtr.size()-1;
    
    for (int row = 0; row < numRow; row++) {
        for (int index = matrix.rowPtr[row]; index < matrix.rowPtr[row+1]; index++) {
            double entry = lower.retrieveElement(row, matrix.colInd[index]);
            if (matrix.colInd[index] >= row) {
                if (entry != 0) {
                    fprintf(stderr, "%s", "testLowerrMatrix Failed\n");
                    return FAIL;
                }
            }
            else if (matrix.value[index] != entry) {
                    fprintf(stderr, "%s", "testLowerMatrix Failed\n");
                    return FAIL;
            }
        }
    }
    return SUCCESS;    
}


int testInverseDiagonal(Matrix matrix, Matrix inverse) {
    int numRow = inverse.rowPtr.size()-1;
    for (int i = 0; i < numRow; i++) {
        if (inverse.value[i] != 1.0/matrix.retrieveElement(i, i)) {
            fprintf(stderr, "%s", "testInverseDiagonal Failed\n");
            return FAIL;
        }
    }
    return SUCCESS;    
}


int testProductAx(Matrix *matrix) {
    vector<double> funcResult;
    vector<double> realValues;
    
    vector<double> identity;
    for (int i = 0; i <= 4999; i++) identity.push_back(1.0);
    
    matrix->productAx(&identity, &funcResult);
    
    int currRow = 0;
    int prevRow = 0;
    int nonZero = 0;
    
    for (int i=0; i < matrix->rowPtr.size()-1; i++) {
        currRow = matrix->rowPtr[i+1];
        prevRow = matrix->rowPtr[i];
        nonZero = currRow - prevRow;
        
        double acc = 0;
        for (int j = prevRow; j < (prevRow+nonZero); j++) {
            acc += matrix->value[j];
        }
        
        realValues.push_back(acc);
    }
    
    for (int i = 0; i < 5000; i++) {
        if (funcResult[i] != realValues[i]) {
            fprintf(stderr, "%s", "Matrix productAx Failed\n");
            return FAIL;
        }
    }
    
    return SUCCESS;
}


