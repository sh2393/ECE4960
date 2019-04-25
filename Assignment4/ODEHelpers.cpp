/*H**********************************************************************
* FILENAME :        ODEHelper.cpp        
*
* DESCRIPTION :
*       ODEHelper implmeentation
*       Extract the numbers for RC model and EKV models
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :   21 Apr 2019
*
*H*/
#include "ODEHelpers.hpp"

double ground_truth(double t) {
    return 4.0 / 1.3 * (exp(0.8 * t) - exp(-0.5 * t)) + 2 * exp(-0.5 * t);
}

double compute_error(double truth, double x) {
    return abs((x-truth)/ truth) * 100;
}

double compute_current(double t) {
    int tInt = t* 1e9 * 10;
    tInt = tInt % 200; //Period is 200 ms
    double tDouble = double(tInt/ 10.0);
    double result;

    // Regions
    if      (tDouble>=0 && tDouble<=1)      result =  0.1 * tDouble / 1000.0;
    else if (tDouble>1 && tDouble <= 10)    result =  0.1 / 1000.0;
    else if (tDouble > 10 && tDouble < 11)  result =  (0.1 - (tDouble - 10) * 0.1) / 1000.0;
    else                                    result =  0.0;

    return result;
}

double compute_currentEKV(double V1, double V2) {
    double Is = 5 * 1.0e-6;
    double k = 0.7;
    double Vt = 0.026;
    double Vth = 1.0;
    double temp1 = log(1 + exp(k * (V1 - Vth) / (2 * Vt) ));
    double temp2 = log(1 + exp((k * (V1 - Vth) - V2) / (2 * Vt) ));
    return Is * pow(temp1, 2) - Is * pow(temp2, 2);
}

Vector2d copmute_xK(Vector2d last, Vector2d Klast, double t, double tstep){
    double RC = 1.0e4 * 1.0e-12;
    double C = 1.0e-12;
    double Vdd = 5.0;

    Vector2d K, x;
    if (tstep == 0){
        x(0) = last(0);
        x(1) = last(1);
    }else{
        x(0) = last(0) + Klast(0)*tstep;
        x(1) = last(1) + Klast(1)*tstep;
    }
    K(0) = (-1.0 / RC * last(0) + compute_current(t) / C);
    K(1) = (-compute_currentEKV(x(0), x(1)) / 1e-12 - 1.0 / RC * x(1) + Vdd / RC);
    return K;
}

Vector2d copmute_xK_RC(Vector2d last, Vector2d Klast, double t, double tstep){
    double RC = 1.0e4 * 1.0e-12;
    double C = 1.0e-12;

    Vector2d K, x;
    if (tstep == 0){
        x(0) = last(0);
        x(1) = last(1);
    }else{
        x(0) = last(0) + Klast(0)*tstep;
        x(1) = last(1) + Klast(1)*tstep;
    }
    K(0) = (-1.0 *  (1.0 / RC + 1.0 / RC) * x(0) + 1.0 / RC * x(1) + compute_current(t) / C);
    K(1) = (1.0 / RC * x(0) - (1.0 / RC + 1.0 / RC) * x(1));

    return K;
}


