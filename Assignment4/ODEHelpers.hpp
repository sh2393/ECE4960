#ifndef ODEhelper_hpp
#define ODEhelper_hpp

#include <stdio.h>
#include <math.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "../eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

double ground_truth(double t);
double compute_error(double truth, double simulation);

double compute_current(double t);
double compute_currentEKV(double V1, double V2);



#endif 
