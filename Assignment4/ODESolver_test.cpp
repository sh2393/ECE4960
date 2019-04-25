/*H**********************************************************************
* FILENAME :        ODESolver_test.cpp     
*
* DESCRIPTION :
*       Test suite for each function
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :   21 Apr 2019
*
*H*/

#include <iostream>
#include <vector>
#include <cmath>
#include "ODESolver.hpp"
#include "ODEHelpers.hpp"

void forwardEuler_test(double t,double deltaT,double last) {
    double time = 0.0;
    double truth = last;
    printf("forwardEuler_Test\n");
    printf("%-15s%-15s%-15s%-15s\n", "Time", "Result", "Groundtruth", "Error");
    printf("%-15.5f%-15.5f%-15.5f%.5f%%\n",0.0,1.0,truth,0.0);
    
    while(time < t) {
        double result = (4 * exp(0.8 * time) - 0.5 * last) * deltaT + last;
        last = result;
        time += deltaT;
        truth = ground_truth(time);
        printf("%-15.5f%-15.5f%-15.5f%.5f%%\n", time,result,truth, compute_error(truth,result));
    }
    printf("\n");
}

void RK34_test(double t, double deltaT, double last) {
    double time = 0.0;
    double Er = 1e-4;
    double Ea = 1e-7;
    double deltaTZero = deltaT;
    double deadline = time + deltaTZero;
    double truth = last;
    
    printf("RK34_test\n");
    printf("%-15s%-15s%-15s%-15s%-15s\n", "Time", "Step", "Result", "Groundtruth", "Error");
    printf("%-15.5f%-15.5f%-15.5f%-15.5f%.5f%%\n",0.0,0.0,truth,truth,0.0);
    
    double halfDeltaT;
    double time1, time2, time3, time4;
    double K1, K2, K3, K4;
    double x1, x2, x3, x4;
    double result, error;
    
    while (time < t) {
        
        halfDeltaT = deltaT / 2;
        
        time1 = time;
        x1 = last;
        K1 = 4 * exp(0.8 * time1) - 0.5 * x1;
        
        time2 = time + halfDeltaT;
        x2 = last + K1 * halfDeltaT;
        K2 = 4 * exp(0.8 * time2) - 0.5 * x2;
        
        time3 = time + halfDeltaT;
        x3 = last + K2 * halfDeltaT;
        K3 = 4 * exp(0.8 * time3) - 0.5 * x3;
        
        time4 = time + deltaT;
        x4 = last + K3 * deltaT;
        K4 = 4 * exp(0.8 * time4) - 0.5 * x4;
        
        result = last + 1.0 / 6.0 * deltaT * (K1 + 2.0 * K2 + 2.0 * K3 + K4);
        
        error = 1.0 / 72.0 * (-5.0 * K1 + 6.0 * K2 + 8.0 * K3 - 9.0 * K4) * deltaT;
        
        time += deltaT;
        deltaT = deltaT * pow((Er / (abs(error) / (abs(result) + Ea))), 1.0/3);
        last = result;
        
        if(time == deadline) {
            truth = ground_truth(deadline);
            printf("%-15.5f%-15.5f%-15.5f%-15.5f%.5f%%\n", deadline, deltaT, result, truth, compute_error(truth,result));
            deadline += deltaTZero;
        }
    }
    printf("\n");
    
}

void RK4_test(double t, double deltaT, double last) {
    double time = 0.0;
    double truth = last;
    
    printf("RK4_test\n");
    printf("%-15s%-15s%-15s%-15s\n", "Time", "Result", "Groundtruth", "Error");
    printf("%-15.5f%-15.5f%-15.5f%.5f%%\n",0.0,truth,truth,0.0);
    
    while(time < t) {
        double halfDeltaT = deltaT / 2;
        
        double time1 = time;
        double x1 = last;
        double K1 = 4 * exp(0.8 * time1) - 0.5 * x1;

        double time2 = time + halfDeltaT;
        double x2 = last + K1 * halfDeltaT;
        double K2 = 4 * exp(0.8 * time2) - 0.5 * x2;

        double time3 = time + halfDeltaT;
        double x3 = last + K2 * halfDeltaT;
        double K3 = 4 * exp(0.8 * time3) - 0.5 * x3;

        double time4 = time + deltaT;
        double x4 = last + K3 * deltaT;
        double K4 = 4 * exp(0.8 * time4) - 0.5 * x4;

        double result = last + 1.0 / 6.0 * deltaT * (K1 + 2.0 * K2 + 2.0 * K3 + K4);
        
        last = result;
        time += deltaT;
        truth = ground_truth(time);
        printf("%-15.5f%-15.5f%-15.5f%.5f%%\n", time,result,truth, compute_error(truth,result));
        
    }
    printf("\n");
}