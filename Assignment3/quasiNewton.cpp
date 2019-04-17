
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include "paramExtraction.hpp"
#include "fullMatrix.hpp"
#include "methods.hpp"


double Vt = 0.026;
vector<double> Ids, Vgs, Vds;
fullMatrix Hessian({{0,0,0}, {0,0,0}, {0,0,0}});
double Is=0, k=0, Vth=0;
double optIs=0, optk=0, optVth=0;
double delta_Is, delta_k, delta_Vth;

double V_bound = 9999999999, delta_bound = 9999999999;

//Initialize Hessian Matrix
void computeDerivatives(void) {
    Hessian.val[0][0] = 0; 
    Hessian.val[1][1] = (V(Is,0.9999*k,Vth) - 2.0*V(Is,k,Vth) + V(Is,1.0001*k,Vth))/(1E-8)/pow(k,2); 
    Hessian.val[2][2] = (V(Is,k,0.9999*Vth) - 2.0*V(Is,k,Vth) + V(Is,k,1.0001*Vth))/(1E-8)/pow(Vth,2); 
    
    Hessian.val[1][2] = Hessian.val[2][1] = (V(Is,1.0001*k,1.0001*Vth) - V(Is,1.0001*k,0.9999*Vth) - V(Is,0.9999*k,1.0001*Vth) + V(Is,0.9999*k,0.9999*Vth))/((4E-8)*k*Vth); // dkdVth, dVthdk
    
    Hessian.val[0][1] = Hessian.val[1][0] = (dVdIs(Is,1.0001*k,Vth) - dVdIs(Is,0.9999*k,Vth)) / (0.0002*k); 
    Hessian.val[0][2] = Hessian.val[2][0] = (dVdIs(Is,k,1.0001*Vth) - dVdIs(Is,k,0.9999*Vth)) / (0.0002*Vth); 
    
    dIs = dVdIs(Is,k,Vth); 
    dk = (V(Is,1.0001*k,Vth) - V(Is,0.9999*k,Vth)) / (0.0001*k);
    dVth = (V(Is,k,1.0001*Vth) - V(Is,k,0.9999*Vth)) / (0.0001*Vth);
}


void QuasiNewton(void) {
    Is = 1E-7; k = 1; Vth = 1;
    int i=0; double ROC = 1E-10;
    
    while (abs(V(Is,k,Vth)) > ROC) {
        i++;
        
        printf("\nIs = %f, k = %f, Vth = %f\n", Is, k, Vth);

        double cur_V = V(Is,k,Vth);        
        V_bound = cur_V;
        
        computeDerivatives();        
        addDelta();
        
        double cur_delta = delta_norm();
        delta_bound = cur_delta;
        
        // Convergence Check
        printf("||V|| Convergence    : %s\n", (cur_V > V_bound)? "PASS\0" : "FAIL\0");
        printf("||delta|| Convergence: %s\n", (cur_delta > delta_bound)? "PASS\0" : "FAIL\0");

        
        double tempIs = Is, tempk = k, tempVth = Vth;
        for (int j=0; j<1000; j++) {
            if (abs(V(j*Is,j*k,j*Vth)) < abs(V(tempIs,tempk,tempVth))) {
                tempIs = j*Is;
                tempk = j*k;
                tempVth = j*Vth;
            }
        }
        
        if (!NotANumber(abs(V(Is,k,Vth))) && abs(V(Is,k,Vth)) < abs(V(optIs,optk,optVth))) {
            optIs = Is; optk = k; optVth = Vth;
        }
    }

    printf("Results\n");
    printf("V  = %10f\nIs = %10f\nk  = %10f\nVth= %10f\n", V(optIs,optk,optVth), optIs, optk, optVth);
}

