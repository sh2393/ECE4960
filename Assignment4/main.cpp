/*H**********************************************************************
* FILENAME :        main.cpp           
*
* DESCRIPTION :
*       Ordinary Diffenrtial equation main fail execution.
*		Forward Euler
* 		Runge Kutta Method
* 		Require eigen library to run
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :	 21 Apr 2019
*
*H*/

#include <iostream>
#include <vector>
#include <cmath>
#include "ODESolver.hpp"
#include "ODEHelpers.hpp"

using namespace std;

#define NS 1E-9
#define STEP 0.2
#define STOP 100

void run_test(double t, double deltaT, double last){
	forwardEuler_test(t, deltaT, last);
    RK4_test(t, deltaT, last);
    RK34_test(t, deltaT, last);
}

int main(){
    //RC Model
    Vector2d RCVal;
    forwardEulerRC(STOP * NS, NS, RCVal);
    forwardEulerRC(STOP * NS, STEP * NS, RCVal);
    
    RK4_RC(STOP * NS, NS, RCVal);
    RK4_RC(STOP * NS, STEP * NS, RCVal);
    
    RK34_RC(STOP * NS, NS, RCVal);
    RK34_RC(STOP * NS, STEP * NS, RCVal);
    
    //EKV model
    Vector2d EKVVal;
    forwardEulerEKV(STOP * NS, NS, EKVVal);
    forwardEulerEKV(STOP * NS, STEP * NS, EKVVal);
    
    RK4_EKV(STOP * NS, NS, EKVVal);
    RK4_EKV(STOP * NS, STEP * NS, EKVVal);
    
    RK34_EKV(STOP * NS, NS, EKVVal);
    RK34_EKV(STOP * NS, STEP * NS, EKVVal);

    Run test
    double t = 5.0, deltaT = 1.0, last = 2.0;
	run_test(t, deltaT, last);

	return 0;
}