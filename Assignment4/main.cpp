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
    Vector2d initialRC;
    forwardEulerRC(STOP * NS, NS, initialRC);
    forwardEulerRC(STOP * NS, STEP * NS, initialRC);
    
    RK4_RC(STOP * NS, NS, initialRC);
    RK4_RC(STOP * NS, STEP * NS, initialRC);
    
    RK34_RC(STOP * NS, NS, initialRC);
    RK34_RC(STOP * NS, STEP * NS, initialRC);
    
    //EKV model
    Vector2d initialEKV;
    forwardEulerEKV(STOP * NS, NS, initialEKV);
    forwardEulerEKV(STOP * NS, STEP * NS, initialEKV);
    
    RK4_EKV(STOP * NS, NS, initialEKV);
    RK4_EKV(STOP * NS, STEP * NS, initialEKV);
    
    RK34_EKV(STOP * NS, NS, initialEKV);
    RK34_EKV(STOP * NS, STEP * NS, initialEKV);

    //Run test
    double t = 5.0, deltaT = 1.0, last = 2.0;
	run_test(t, deltaT, last);

	return 0;
}