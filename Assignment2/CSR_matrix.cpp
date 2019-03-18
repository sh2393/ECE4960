/*
CSR_matrix.cpp
Joyce Huang sh2393

March 18, 2019
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "cmath"

#include "CSR_matrix.h"

using namespace std;

double Matrix::retrieveElement(int x, int y) {

    int rowPointer = rowPtr[x+1];
    int prePointer = rowPtr[x];
    int non_zero = rowPointer - prePointer;
    
    for (int i = prePointer; i < (prePointer+non_zero); i++) {
        if (colInd[i] == y) {
            
            return value[i];
        }
    }
    
    return 0;
}

void Matrix::addElement(double val, int row, int col) {
    int begin = rowPtr[row];
    int nextRowPtr = rowPtr[row+1];
    
    int inserted = 0;
    
    int zeroSum = 0, zeroSumLocation = 0;
    
    for (int i=begin; i<nextRowPtr; i++) {
        
        if (inserted || zeroSum) break;
        

        if (col == colInd[i]) {

            if (value[i] + val == 0) {
                zeroSum = 1;
                zeroSumLocation = i;
                
            }
            else {
                value[i] += val;
                inserted = 1;
            }
        }
        

        else if (col < colInd[i]) {
            value.insert(value.begin() + i,val);
            
            colInd.insert(colInd.begin() + i,col);
            inserted = 1;
            
            for (int i=row+1; i<rowPtr.size(); i++) rowPtr[i]++;
        }
    }
    
    if (zeroSum) {
        value.erase(value.begin()+zeroSumLocation); // delete the value at this location
        colInd.erase(colInd.begin() + zeroSumLocation); // delete the column at this location
        for (int i=row+1; i<rowPtr.size(); i++) rowPtr[i]--;
    }
    
    if (!inserted && !zeroSum) {
        value.insert(value.begin() + nextRowPtr,val);
        
        colInd.insert(colInd.begin() + nextRowPtr,col);
        
        for (int i=row+1; i<rowPtr.size(); i++) rowPtr[i]++;
    }
    
}

void Matrix::productAx(vector<double> *x, vector<double> *b) {
    int currRow = 0;
    int prevRow = 0;
    int nonZero = 0;
    
    for (int i=0; i <rowPtr.size()-1; i++) {
        currRow = rowPtr[i+1];
        prevRow = rowPtr[i];
        nonZero = currRow - prevRow;
        
        double acc = 0;
        for (int j = prevRow; j < (prevRow+nonZero); j++) {
            acc += (value[j] * (*x)[colInd[j]]);
        }        
        b->push_back(acc);
    }
    
}

void Matrix::printMatrix() {
    for (int row = 0; row < rowPtr.size()-1; row++) {
        for (int col = 0; col < rowPtr.size()-1; col++) {
            printf("%.5f ", retrieveElement(row, col)); 
        }
        printf("\n");
    }
}


Matrix UpperMatrix(Matrix matrix) {

    Matrix upper;
    
    unsigned long numRow = matrix.rowPtr.size()-1;
    
    int numCol = 0;
    for (int k=0; k < matrix.colInd.size(); k++)
        numCol = MAX(numCol, matrix.colInd[k]);
    numCol++;
    
    int count = 0;
    upper.rowPtr.push_back(0); 
    
    for (long row = 0; row < numRow; row++) {
        for (int index = matrix.rowPtr[row]; index < matrix.rowPtr[row+1]; index++) {
            if (matrix.colInd[index] > row) {
                upper.value.push_back(matrix.value[index]);
                upper.colInd.push_back(matrix.colInd[index]);
                count++;
            }
        }
        
        upper.rowPtr.push_back(count);
    }
    
    return upper;
}


Matrix LowerMatrix(Matrix matrix) {

    Matrix lower;
    
    unsigned long numRow = matrix.rowPtr.size()-1;
    int numCol = 0;
    
    for (int k=0; k < matrix.colInd.size(); k++)
        numCol = MAX(numCol, matrix.colInd[k]);
    numCol++;
    
    int count = 0;
    lower.rowPtr.push_back(0);
    
    for (long row = 0; row < numRow; row++) {
        for (int index = matrix.rowPtr[row]; index < matrix.rowPtr[row+1]; index++) {
            if (matrix.colInd[index] < row) {
                lower.value.push_back(matrix.value[index]);
                lower.colInd.push_back(matrix.colInd[index]);
                count++;
            }
        }
        
        lower.rowPtr.push_back(count);
    }

    return lower;
}


Matrix InverseDiagonal(Matrix matrix) {

    Matrix inverse;
    
    int width = 0;
    for (int k=0; k < matrix.colInd.size(); k++) width = MAX(width,matrix.colInd[k]);
    
    int count = 0;
    double element = 0;
    inverse.rowPtr.push_back(0);
    
    for (int i = 0; i < matrix.rowPtr.size()-1; i++) {
        element = matrix.retrieveElement(i,i);
        
        if (element) {
            inverse.value.push_back(1.0/element);
            inverse.colInd.push_back(i);
            count++;
            inverse.rowPtr.push_back(count);
        }
    }
    return inverse;
}



Matrix matrixMultiplier(Matrix A, Matrix B) {

    Matrix product;
    
    unsigned long numRow_A = A.rowPtr.size()-1;
    int numCol_A = 0;
    for (int k=0; k < A.colInd.size(); k++)
        numCol_A = MAX(numCol_A, A.colInd[k]);
    numCol_A ++;
    
    int numCol_B = 0;
    for (int k=0; k < B.colInd.size(); k++)
        numCol_B = MAX(numCol_B, B.colInd[k]);
    numCol_B ++;
    
    
    int j=1; 
    double sum = 0; 
    int count = 0; 
    product.rowPtr.push_back(count);
    
    for (int row = 0; row < numRow_A; row++) {
        for (int col = 0; col < numCol_B; col++) {
            for (int index = A.rowPtr[j-1]; index < A.rowPtr[j]; index ++) {
                sum += A.value[index] * B.retrieveElement(A.colInd[index], col);
            }
            
            if (sum) {
                product.value.push_back(sum);
                product.colInd.push_back(col);
                count++;
            }
            sum = 0;
        }
        
        product.rowPtr.push_back(count);
        j++;
    }

    
    return product;
}



Matrix matrixAddition(Matrix A, Matrix B) {

    unsigned long numRow_A = A.rowPtr.size()-1;
    int numCol_A = 0;
    for (int k=0; k < A.colInd.size(); k++)
        numCol_A = MAX(numCol_A, A.colInd[k]);
    numCol_A ++;
    
    unsigned long numRow_B = B.rowPtr.size()-1;
    int numCol_B = 0;
    for (int k=0; k < B.colInd.size(); k++)
        numCol_B = MAX(numCol_B, B.colInd[k]);
    numCol_B ++;

    int counter = 0;
    for (int i = 0; i < max(numRow_B, numRow_A); i++) {
        int begin = B.rowPtr[i];
        int end = B.rowPtr[i+1];
        
        for (int j = begin; j < end; j++) {
            double before = A.retrieveElement(i, B.colInd[j]);
            
            A.addElement(B.value[j], i, B.colInd[j]);
            
            double after = A.retrieveElement(i, B.colInd[j]);
            if (after - before != B.value[j]) counter++;
        }
    }
    
    return A;
}


double residualNorm(Matrix *matrix, vector<double> *x, vector<double> *b) {    
    vector<double> Ax;    
    vector<double> B = *b;
    
    matrix->productAx(x, &Ax);
    
    double sumOfb = 0, sumOfbAx = 0;
    
    for (int i=0; i<B.size(); i++) {
        sumOfb += pow(B[i],2);
        B[i] -= Ax[i];
    }
    
    for (int i=0; i<B.size(); i++) {
        sumOfbAx += pow(B[i],2);
    }
    
    double error = sqrt(sumOfbAx) / sqrt(sumOfb);

    return error;
}

vector<double> Jacobian(Matrix matrix, vector<double> b, vector<double> x, double epsilon) {
    
    Matrix Dinv = InverseDiagonal(matrix);        
    Matrix upper = UpperMatrix(matrix);
    Matrix lower = LowerMatrix(matrix);
    Matrix add = matrixAddition(upper, lower);
    Matrix MMult = matrixMultiplier(Dinv,add);
    vector<double> Minit;

    Dinv.productAx(&b, &Minit);    

    x = Minit;
    
    vector<double> tmp;
    double error = epsilon+1;
    int iterations=0;    
    while (error > epsilon) {
        iterations++;
        MMult.productAx(&x, &tmp);
        
        x = {};
        for (int j = 0; j < tmp.size(); j++) {
            x.push_back(Minit[j] - tmp[j]);
        }

        tmp = {};
        error = residualNorm(&matrix,&x,&b);
        
    }
    printf("Number of iterations: %d\n", iterations);
    printf("Error = %.8e\n", error);
    
    return x;
}
