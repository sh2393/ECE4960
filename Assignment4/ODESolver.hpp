#ifndef ODESOLVER_HPP
#define ODESOLVER_HPP

#include <stdio.h>
#include <vector>
#include "../eigen/Eigen/Dense"
using namespace std;
using namespace Eigen;

void forwardEulerRC(double t,double deltaT,Vector2d last);
void forwardEulerEKV(double t,double deltaT,Vector2d last);

void RK34_RC(double t, double deltaT, Vector2d last);
void RK34_EKV(double t, double deltaT, Vector2d last);

void RK4_RC(double t, double deltaT, Vector2d last);
void RK4_EKV(double t, double deltaT, Vector2d last);


//Validation Functions
void forwardEuler_test(double t,double deltaT,double last); 
void RK34_test(double t, double deltaT, double last);
void RK4_test(double t, double deltaT, double last);

#endif 
