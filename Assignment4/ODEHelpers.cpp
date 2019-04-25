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


