/*H**********************************************************************
* FILENAME :        ODEHelpers.hpp          
*
* DESCRIPTION :
*       Methods of helpers to be used in solver
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :	 21 Apr 2019
*
*H*/

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

Vector2d copmute_xK(Vector2d last, Vector2d Klast, double t, double tstep);
Vector2d copmute_xK_RC(Vector2d last, Vector2d Klast, double t, double tstep);

#endif 
