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

void run_test(){
	forwardEuler_test(5.0, 1.0, 2.0);
    RK4_test(5.0, 1.0, 2.0);
    RK34_test(5.0, 1.0, 2.0);
}

int main(){

	run_test();
    

    //RC
    Vector2d initialRC;
    initialRC << 0.0, 0.0;
    forwardEulerRC(100 * 1e-9, 1e-9, initialRC);
    forwardEulerRC(100 * 1e-9, 0.2 * 1e-9, initialRC);
    
    RK4_RC(100 * 1e-9, 1e-9, initialRC);
    RK4_RC(100 * 1e-9, 0.2 * 1e-9, initialRC);
    
    RK34_RC(100 * 1e-9, 1e-9, initialRC);
    RK34_RC(100 * 1e-9, 0.2 * 1e-9, initialRC);
    
    //EKV model
    Vector2d initialEKV;
    initialRC << 2.5, 2.5;
    forwardEulerEKV(100 * 1e-9, 1e-9, initialEKV);
    forwardEulerEKV(100 * 1e-9, 0.2 * 1e-9, initialEKV);
    
    RK4_EKV(100 * 1e-9, 1e-9, initialEKV);
    RK4_EKV(100 * 1e-9, 0.2 * 1e-9, initialEKV);
    
    RK34_EKV(100 * 1e-9, 1e-9, initialEKV);
    RK34_EKV(100 * 1e-9, 0.2 * 1e-9, initialEKV);

	forwardEuler_test(5.0, 1.0, 2.0);
	RK4_test(5.0, 1.0, 2.0);
    RK34_test(5.0, 1.0, 2.0);

	return 0;
}