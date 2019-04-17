#include "dmSolver.hpp"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


void DMMatrix::printDMMatrix(void) {
    for (int i=0; i<dimension; i++) {
        for (int j=0; j<dimension; j++) {
            printf("%3f ", A[i][j]);
        }
        printf("%3f\n", B[i]);
    }
}

void DMMatrix::swapRow(int i, int j){
    if (i == j) return;
    else{
        vector<double> temp;
        temp = A[j];
        A[j] = A[i];
        A[i] = temp;

        double t = B[i];
        B[i] = B[j];
        B[j] = t;
    }
}

//scale row i by c and add to j
void DMMatrix::rowScale(int i, int j, double c) {

    for (int k=0; k<dimension; k++) A[j][k]+=c*A[i][k];

    B[j] += B[i]*c;
}



void DMMatrix::Gaussian(int index) {
    for (int i=index+1; i<dimension; i++) {
        rowScale(index,i,-(A[i][index])/(A[index][index]));
    }
}



int DMMatrix::rowChoice(int index) {
    int min = dimension;
    int row = 0;
    for (int i=index; i<dimension;i++) {
        if (A[i][index]) {
            int sum=0;
            for(int j=0;j<dimension;j++){
                if (A[i][j]) sum++; 
            }
            if (sum < min) row = i; 
        }
    }
    return row;
}


// Solver Methods

void Solver(DMMatrix system, vector<double> X){
    printf("in solver\n");
    for(int i = system.dimension-1; i >= 0; i--){
        X[i] = system.B[i]/system.A[i][i];
        for(int k = i; k >=0; k--){
            system.B[k] -= X[i]*system.A[k][i];
            system.A[k][i] = 0;
        }
    }
    for(int i = 0; i < X.size(); i++) printf("%f\n", X[i]);
}

int verifySolver(){
    vector<vector<double>> A{{1, 2, 0, 0, 3}, {4, 5, 6, 0, 0}, {0, 7, 8, 0, 9}, {0, 0, 0, 10, 0}, {11, 0, 0, 0, 12}};
    vector<double> B{5, 4, 3, 2, 1};

    DMMatrix system(A, B);
    //system.printDMMatrix();

    int row = 0;
    for (int i=0; i<system.dimension; i++) {
        row = system.rowChoice(i);
        system.swapRow(i,row);
        system.Gaussian(i);
    }

    //system.printDMMatrix();

    vector<double> X(system.dimension);
    Solver(system, X);


    return 0;
}
