/*H**********************************************************************
* FILENAME :        ODESolver.cpp          
*
* DESCRIPTION :
*       Solver Implmentation
*       In this implementation, forward Euler method and parameter extraction are inherited from the previous assignments.
*       I have looked up vector manipulation and found that the eigen library is pretty useful. T
*       Thus, I have migrated my code from a custom class of vectors to the eigen vectors.
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

void forwardEulerRC(double t,double deltaT, Vector2d last) {
    
    double time = 0.0;
    printf("forwardEulerRC      deltaT = %f ns\n",deltaT*1e9);
    printf("%-15s%-15s%-15s\n", "Time", "V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f\n",0.0,0.0,0.0);
    double RC = 1.0e4 * 1.0e-12;
    
    while(time < t) {
        Vector2d result;
        result(0) = last(0) + (-1.0 *  (1.0 / RC + 1.0 / RC) * last(0) + 1.0 / RC * last(1) + compute_current(time) / 1.0e-12) * deltaT;
        result(1) = last(1) + (1.0 / RC * last(0) - (1.0 / RC + 1.0 / RC) * last(1)) * deltaT;
        last = result;
        time += deltaT;
        printf("%-15.1f%-15.5f%-15.5f\n", time*1e9,result(0),result(1));
    }
    printf("\n");
}


void forwardEulerEKV(double t,double deltaT,Vector2d last) {
    
    double time = 0.0;
    printf("forwardEulerEKV      deltaT = %f ns \n",deltaT*1e9);
    printf("%-15s%-15s%-15s\n", "Time", "V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f\n",0.0,0.0,0.0);
    double RC = 1.0e4 * 1.0e-12;
    double Vdd = 5.0;
    while(time < t) {
        Vector2d result;
        result(0) = last(0) + (-1.0 / RC * last(0) + compute_current(time) / 1e-12) * deltaT;
        result(1) = last(1) + (-compute_currentEKV(last(0), last(1))/1e-12 - 1.0/RC * last(1) + Vdd / RC) * deltaT;
        last = result;
        time += deltaT;
        printf("%-15.1f%-15.5f%-15.5f\n", time*1e9,result(0),result(1));
    }
    printf("\n");
}

void RK34_RC(double t, double deltaT, Vector2d last) {
    double time = 0.0;
    double Er = 1e-6;
    double Ea = 1e-9;
    double deltaTZero = deltaT;
    double deadline = time + deltaTZero;
    printf("RK34_RC      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s%-15s\n", "Time", "Step","V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f%-15.5f\n",0.0,deltaT*1e9,0.0,0.0);
    
    double RC = 1.0e4 * 1.0e-12;
    double C = 1.0e-12;
    
    double halfDeltaT, tempDeltaT, temphalfDeltaT;
    double time1, time2, time3, time4;
    Vector2d K0, K1, K2, K3, K4;
    Vector2d x1, x2, x3, x4;
    Vector2d result, error;
    
    while (time < t) {
        halfDeltaT = deltaT / 2;
        time1 = time;
        time2 = time + halfDeltaT;
        time3 = time + halfDeltaT;
        time4 = time + deltaT;
    
        K1 = copmute_xK_RC(last, K0, time1, 0);
        K2 = copmute_xK_RC(last, K1, time2, halfDeltaT);
        K3 = copmute_xK_RC(last, K2, time3, halfDeltaT);
        K4 = copmute_xK_RC(last, K3, time4, deltaT);
        
        result(0) = last(0) + 1.0 / 6.0 * deltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
        result(1) = last(1) + 1.0 / 6.0 * deltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));

        error(0) = 1.0 / 72.0 * (-5.0 * K1(0) + 6.0 * K2(0) + 8.0 * K3(0) - 9.0 * K4(0)) * deltaT;
        error(1) = 1.0 / 72.0 * (-5.0 * K1(1) + 6.0 * K2(1) + 8.0 * K3(1) - 9.0 * K4(1)) * deltaT;
        
        time += deltaT;
        deltaT = deltaT * pow((Er / (error.norm() / (result.norm() + Ea))), 1.0/3);
        last = result;
        
        if(time == deadline) {
            printf("%-15.1f%-15.5f%-15.5f%-15.5f\n", deadline*1e9,deltaT*1e9,result(0),result(1));
            deadline += deltaTZero;
        }
    }
    printf("\n");
    
}

void RK34_EKV(double t, double deltaT, Vector2d last) {
    double time = 0.0;
    double Er = 1e-7;
    double Ea = 1e-10;
    double deltaTZero = deltaT;
    double deadline = time + deltaTZero;
    
    printf("RK34_EKV      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s%-15s\n", "Time", "Step","V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f%-15.5f\n",0.0,deltaT*1e9,0.0,0.0);
    
    double RC = 1.0e4 * 1.0e-12;
    double Vdd = 5.0;
    double C = 1.0e-12;
    
    double time1, time2, time3, time4, halfDeltaT;
    Vector2d K0, K1, K2, K3, K4;
    Vector2d x1, x2, x3, x4;
    Vector2d result, error;
    
    while (time < t) {
        
        halfDeltaT = deltaT / 2;
        
        time1 = time;
        time2 = time + halfDeltaT;
        time3 = time + halfDeltaT;
        time4 = time + deltaT;
        
        K1 = copmute_xK(last, K0, time1, 0);
        K2 = copmute_xK(last, K1, time2, halfDeltaT);
        K3 = copmute_xK(last, K2, time3, halfDeltaT);
        K4 = copmute_xK(last, K3, time4, deltaT);
        
        result(0) = last(0) + 1.0 / 6.0 * deltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
        result(1) = last(1) + 1.0 / 6.0 * deltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));
        
        error(0) = 1.0 / 72.0 * (-5.0 * K1(0) + 6.0 * K2(0) + 8.0 * K3(0) - 9.0 * K4(0)) * deltaT;
        error(1) = 1.0 / 72.0 * (-5.0 * K1(1) + 6.0 * K2(1) + 8.0 * K3(1) - 9.0 * K4(1)) * deltaT;
        
        time += deltaT;
        deltaT = deltaT * pow((Er / (error.norm() / (result.norm() + Ea))), 1.0/3);
        last = result;
        
        if(time == deadline) {
            printf("%-15.1f%-15.5f%-15.5f%-15.5f\n", deadline*1e9,deltaT*1e9,result(0),result(1));
            deadline += deltaTZero;
        }
    }
    printf("\n");
    
}

void RK4_RC(double t, double deltaT, Vector2d last) {
    double time = 0.0;
    
    printf("RK4_RC      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s\n", "Time", "V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f\n",0.0,0.0,0.0);
    
    double RC = 1.0e4 * 1.0e-12;
    double C = 1.0e-12;
    double time1, time2, time3, time4;
    double halfDeltaT;
    Vector2d K0, K1, K2, K3, K4;
    
    while(time < t) {
        
        halfDeltaT = deltaT / 2;
        time1 = time;
        time2 = time + halfDeltaT;
        time3 = time + halfDeltaT;
        time4 = time + deltaT;
        
        K1 = copmute_xK_RC(last, K0, time1, 0);
        K2 = copmute_xK_RC(last, K1, time2, halfDeltaT);
        K3 = copmute_xK_RC(last, K2, time3, halfDeltaT);
        K4 = copmute_xK_RC(last, K3, time4, deltaT);
        
        Vector2d result;
        result(0) = last(0) + 1.0 / 6.0 * deltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
        result(1) = last(1) + 1.0 / 6.0 * deltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));
        
        last = result;
        time += deltaT;
        
        printf("%-15.1f%-15.5f%-15.5f\n", time*1e9,result(0),result(1));
    }
    printf("\n");
}


void RK4_EKV(double t, double deltaT, Vector2d last) {
    double time = 0.0;
    printf("RK4_EKV      deltaT = %f\n",deltaT*1e9);
    printf("%-15s%-15s%-15s\n", "Time", "V1", "V2");
    printf("%-15.1f%-15.5f%-15.5f\n",0.0,0.0,0.0);
    
    double RC = 1.0e4 * 1.0e-12;
    double C = 1.0e-12;
    double Vdd = 5.0;

    while(time < t) {
        double halfDeltaT = deltaT / 2;
        double time1 = time;
        double time2 = time + halfDeltaT;
        double time3 = time + halfDeltaT;
        double time4 = time + deltaT;
        
        Vector2d K0, K1, K2, K3, K4;
        K1 = copmute_xK(last, K0, time1, 0);
        K2 = copmute_xK(last, K1, time2, halfDeltaT);
        K3 = copmute_xK(last, K2, time3, halfDeltaT);
        K4 = copmute_xK(last, K3, time4, deltaT);
        
        Vector2d result;
        result(0) = last(0) + 1.0 / 6.0 * deltaT * (K1(0) + 2.0 * K2(0) + 2.0 * K3(0) + K4(0));
        result(1) = last(1) + 1.0 / 6.0 * deltaT * (K1(1) + 2.0 * K2(1) + 2.0 * K3(1) + K4(1));
        
        last = result;
        time += deltaT;
        
        printf("%-15.1f%-15.5f%-15.5f\n", time*1e9,result(0),result(1));
    }
    printf("\n");
}