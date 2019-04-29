/*H**********************************************************************
* FILENAME :        parameExtraction.cpp
*
* DESCRIPTION :
*       Construct a modular program that can accomplish least-square fitting and parameter extraction
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :   28 Apr 2019
*
*H*/

#include "paramExtraction.hpp"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


//public methods
vector<vector<double>> Inverse(3, vector<double> (3, 0));

double det = 0;
double dIs=0, dk=0, dVth=0;
double delta_V_Is, delta_V_k, delta_V_Vth;


double V(double IS, double K, double VTH) {
    double sum = 0;
    
    if (task == 4) {
        for (int i=0; i<Ids.size(); i++) {
            sum += pow(IS*pow(log(1.0+exp(K*(Vgs[i]-VTH)/(2.0*Vt))),2) - IS*pow(log(1.0+exp((K*(Vgs[i]-VTH)-Vds[i])/(2.0*Vt))),2) - Ids[i],2);
        }
    }
    
    if (task == 5){
        for (int i=0; i<Ids.size(); i++) {
            sum += pow((IS*pow(log(1.0+exp(K*(Vgs[i]-VTH)/(2.0*Vt))),2) - IS*pow(log(1.0+exp((K*(Vgs[i]-VTH)-Vds[i])/(2.0*Vt))),2))/Ids[i] - Ids[i],2);
        }
    }

    return sum;
    
}


double dVdIs(double IS, double K, double VTH) {
    double sum = 0;
    for (int i=0; i<Ids.size(); i++) {
        sum += pow(pow(log(1.0+exp(K*(Vgs[i]-VTH)/(2.0*Vt))),2) - pow(log(1.0+exp((K*(Vgs[i]-VTH)-Vds[i])/(2.0*Vt))),2),2);
    }
    return sum;
}


double delta_norm(void) {
    return pow(delta_Is,2)/pow(Is,2) + pow(delta_k,2)/pow(k,2) + pow(delta_Vth,2)/pow(Vth,2);
}


void addDelta(void) {
    Hessian.compute_inverse(Inverse);
    
    delta_Is = Inverse[0][0]*dIs + Inverse[0][1]*dk + Inverse[0][2]*dVth;
    delta_k = Inverse[1][0]*dIs + Inverse[1][1]*dk + Inverse[1][2]*dVth;
    delta_Vth = Inverse[2][0]*dIs + Inverse[2][1]*dk + Inverse[2][2]*dVth;
    
    // Compute the parameter sensitivity
    delta_V_Is = (V(Is+delta_Is,k,Vth) - V(Is, k, Vth))/(V(Is,k,Vth)*(delta_Is/Is));
    delta_V_k = (V(Is,k+delta_k,Vth) - V(Is, k, Vth))/(V(Is,k,Vth)*(delta_k/k));
    delta_V_Vth = (V(Is,k,Vth+delta_Vth) - V(Is, k, Vth))/(V(Is,k,Vth)*(delta_Vth/Vth));
    

    printf("Parameter sensitivity V_Is : %10f\n", delta_V_Is);
    printf("Parameter sensitivity V_k  : %10f\n", delta_V_k);
    printf("Parameter sensitivity V_th : %10f\n", delta_V_Vth);
    
    Is += delta_Is;
    k += delta_k;
    Vth += delta_Vth;
    
}

