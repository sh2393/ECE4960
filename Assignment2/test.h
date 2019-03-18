/*
test.h
Joyce Huang sh2393

March 16, 2019
*/

#ifndef _TEST_H
#define _TEST_H
#include <stdio.h>
#include "CSR_matrix.h"
#define SUCCESS 1
#define FAIL -1

int testLoad(Matrix *matrix);

int testUpperMatrix(Matrix matrix, Matrix upper);

int testLowerMatrix(Matrix matrix, Matrix lower);

int testInverseDiagonal(Matrix matrix, Matrix inverse);

int testProductAx(Matrix *matrix);

#endif 


