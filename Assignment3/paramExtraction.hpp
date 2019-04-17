#ifndef paramExtraction_hpp
#define paramExtraction_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "fullMatrix.hpp"

using namespace std;

extern int task;

extern vector<double> Ids, Vgs, Vds;
extern vector<vector<double>> Inverse;
extern fullMatrix Hessian;

extern double Vt, Is, k, Vth;
extern double dIs, dk, dVth;
extern double delta_V_Is, delta_V_k, delta_V_Vth, delta_Is, delta_k, delta_Vth;
extern double optIs, optk, optVth;


double V(double IS, double K, double VTH);

void addDelta(void);

double dVdIs(double IS, double K, double VTH);

int NotANumber(double x);

double delta_norm(void);


#endif 
