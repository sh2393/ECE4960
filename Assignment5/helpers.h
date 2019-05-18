#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <fstream>
#include <string>
#include "solver2D.h"

#include "../eigen/Eigen/Eigen"

#define   ZERO       0

using namespace std;
using namespace Eigen;

const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");
const static IOFormat CleanFormat(4, 0, ", ", "\n", "[", "]");


/*
File Writer Helper
*/
void writeToCSVfile(string name, ArrayXXd matrix);

ArrayXXd analyticalU (string outfileName, double dt, double dx, int Nt, int Nx);
ArrayXXd analytical2D(string outfileName, double dt, double dx, double dy, int Nt, int Nx, int Ny, Solver2D solver);
double gaussQuad(int numberOfSummationPoints, int n, int m, int numberOfIntegrationPoints);


#endif