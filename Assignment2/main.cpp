/*
main.cpp
Joyce Huang sh2393

March 16, 2019

driver file for matrix jacobain solver
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "helpers.h"
#include "test.h"

using namespace std;

void loadMatrix (Matrix* m) {    
    ifstream rowFile, valueFile, colFile;
    rowFile.open("data/rowPtr.csv");
    valueFile.open("data/value.csv");
    colFile.open("data/colInd.csv");
    
    string line = "";
    
    while (valueFile >> line) {
        double value = stod(line);
        m->value.push_back(value);
    }
    
    while (rowFile >> line) {
        int rowNum = stoi(line);
        m->rowPtr.push_back(rowNum-1);
    }
    
    while (colFile >> line) {
        int colIndex = stoi(line);
        m->colInd.push_back(colIndex-1);
    }
}

void test1(Matrix matrix){
    clock_t t = clock();   
    vector<double> b(5000, 0), x; b[0] = 1.0;
    vector<double> answer = Jacobian(matrix,b,x,1E-10);
    t = clock() - t;
    printf ("Computation time: %f seconds.\n\n",((float)t)/CLOCKS_PER_SEC);
}

void test2(Matrix matrix){
    clock_t t = clock();
    vector<double> b(5000, 0), x; b[4] = 1.0;
    vector<double> answer = Jacobian(matrix,b,x,1E-10);
    t = clock() - t;
    printf ("Computation time: %f seconds.\n\n",((float)t)/CLOCKS_PER_SEC);
}

void test3(Matrix matrix){
    clock_t t = clock();    
    vector<double> b(5000, 1), x; 
    vector<double> answer = Jacobian(matrix,b,x,1E-10);
    t = clock() - t;
    printf ("Computation time: %f seconds.\n\n",((float)t)/CLOCKS_PER_SEC);
}


int main(int argc, const char * argv[]) {
    Matrix matrix;
    loadMatrix(&matrix); 
    
    printf("Begin Testing\n");

    if(!testLoad(&matrix)) exit(1);

    Matrix T1;
    T1 = InverseDiagonal(matrix);
    if(!testInverseDiagonal(matrix, T1)) exit(1);

    T1 = UpperMatrix(matrix);
    if(!testUpperMatrix(matrix, T1)) exit(1);

    T1 = LowerMatrix(matrix);
    if(!testLowerMatrix(matrix, T1)) exit(1);

    printf("Testing Completed\n");

    printf("test 1 begin\n");
    test1(matrix);
    printf("test 1 completed\n");

    printf("test 2 begin\n");    
    test2(matrix);
    printf("test 2 completed\n");

    printf("test 3 begin\n"); 
    test3(matrix);
    printf("test 3 completed\n");

    reportMemory();
    
    return 0;
}
