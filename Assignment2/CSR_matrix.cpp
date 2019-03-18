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
#define MAX(x,y) ((x>y)?x:y)


double computeError(Matrix *matrix, vector<double> *x, vector<double> *b) {    
    vector<double> Ax;    
    vector<double> B = *b;
    
    productAx(matrix, x, &Ax);
    
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


double retrieveElement(Matrix *matrix, int x, int y) {

    int rowPointer = matrix->rowPtr[x+1];
    int prePointer = matrix->rowPtr[x];
    int non_zero = rowPointer - prePointer;
    
    for (int i = prePointer; i < (prePointer+non_zero); i++) {
        if (matrix->colInd[i] == y) {
            
            return matrix->value[i];
        }
    }
    
    return 0;
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



void productAx(Matrix *A, vector<double> *x, vector<double> *b) {
    int currRow = 0;
    int prevRow = 0;
    int nonZero = 0;
    
    for (int i=0; i <A->rowPtr.size()-1; i++) {
        currRow = A->rowPtr[i+1];
        prevRow = A->rowPtr[i];
        nonZero = currRow - prevRow;
        
        double acc = 0;
        for (int j = prevRow; j < (prevRow+nonZero); j++) {
            acc += (A->value[j] * (*x)[A->colInd[j]]);
        }        
        b->push_back(acc);
    }
    
}



Matrix InverseDiagonal(Matrix matrix) {

    Matrix inverse;
    
    int width = 0;
    for (int k=0; k < matrix.colInd.size(); k++) width = MAX(width,matrix.colInd[k]);
    
    int count = 0;
    double element = 0;
    inverse.rowPtr.push_back(0);
    
    for (int i = 0; i < matrix.rowPtr.size()-1; i++) {
        element = retrieveElement(&matrix,i,i);
        
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
                sum += A.value[index] * retrieveElement(&B, A.colInd[index], col);
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


void addElement(Matrix *matrix, double value, int row, int col) {
    int prevRowPtr = matrix->rowPtr[row];
    int nextRowPtr = matrix->rowPtr[row+1];
    
    int inserted = 0;
    
    int zeroSum = 0, zeroSumLocation = 0;
    
    for (int i=prevRowPtr; i<nextRowPtr; i++) {
        
        if (inserted || zeroSum) break;
        

        if (col == matrix->colInd[i]) {

            if (matrix->value[i] + value == 0) {
                zeroSum = 1;
                zeroSumLocation = i;
                
            }
            else {
                matrix->value[i] += value;
                inserted = 1;
            }
        }
        

        else if (col < matrix->colInd[i]) {
            matrix->value.insert(matrix->value.begin() + i,value);
            
            matrix->colInd.insert(matrix->colInd.begin() + i,col);
            inserted = 1;
            
            for (int i=row+1; i<matrix->rowPtr.size(); i++) matrix->rowPtr[i]++;
        }
    }
    
    if (zeroSum) {
        matrix->value.erase(matrix->value.begin()+zeroSumLocation); // delete the value at this location
        matrix->colInd.erase(matrix->colInd.begin() + zeroSumLocation); // delete the column at this location
        for (int i=row+1; i<matrix->rowPtr.size(); i++) matrix->rowPtr[i]--;
    }
    
    if (!inserted && !zeroSum) {
        matrix->value.insert(matrix->value.begin() + nextRowPtr,value);
        
        matrix->colInd.insert(matrix->colInd.begin() + nextRowPtr,col);
        
        for (int i=row+1; i<matrix->rowPtr.size(); i++) matrix->rowPtr[i]++;
    }
    
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
        int prevRowPtr = B.rowPtr[i];
        int currRowPtr = B.rowPtr[i+1];
        
        for (int j = prevRowPtr; j < currRowPtr; j++) {
            double before = retrieveElement(&A, i, B.colInd[j]);
            
            addElement(&A, B.value[j], i, B.colInd[j]);
            
            double after = retrieveElement(&A, i, B.colInd[j]);
            if (after - before != B.value[j]) counter++;
        }
    }
    
    return A;
}


void printout(Matrix matrix) {
    for (int row = 0; row < matrix.rowPtr.size()-1; row++) {
        for (int col = 0; col < matrix.rowPtr.size()-1; col++) {
            printf("%.5f ", retrieveElement(&matrix, row, col)); 
        }
        printf("\n");
    }
}

vector<double> Jacobian(Matrix matrix, vector<double> b, vector<double> x, double errorTolerance) {
    
    Matrix Dinv = InverseDiagonal(matrix);        
    Matrix upper = UpperMatrix(matrix);
    Matrix lower = LowerMatrix(matrix);
    Matrix add = matrixAddition(upper, lower);
    Matrix UnDinv = InverseDiagonal(Dinv);
    Matrix MMult = matrixMultiplier(Dinv,add);
    vector<double> Minit;

    productAx(&Dinv, &b, &Minit);    

    x = Minit;
    
    vector<double> tmp;
    double error = errorTolerance+1;
    int iterations=0;    
    while (error > errorTolerance) {
        iterations++;
        productAx(&MMult, &x, &tmp);
        
        x = {};
        for (int j = 0; j < tmp.size(); j++) {
            x.push_back(Minit[j] - tmp[j]);
        }

        tmp = {};
        error = computeError(&matrix,&x,&b);
        
    }
    
    cout << "Num iterations = " << iterations << endl;
    cout << "Error = " << error << endl;
    
    return x;
}
