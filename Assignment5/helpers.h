#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <fstream>
#include <string>

#include "../eigen/Eigen/Eigen"

using namespace std;
using namespace Eigen;

const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");
const static IOFormat CleanFormat(4, 0, ", ", "\n", "[", "]");


/*
File Writer Helper
*/
void writeToCSVfile(string name, ArrayXXd matrix);

#endif