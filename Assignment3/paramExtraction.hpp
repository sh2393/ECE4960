/*H**********************************************************************
* FILENAME :        parameExtraction.hpp
*
* DESCRIPTION :
*       Parameter extraciton methods
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :   28 Apr 2019
*
*H*/

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

int NaN(double x) return (x > 0 || x <=0)? 0:1; 

double V(double IS, double K, double VTH);

void addDelta(void);

double dVdIs(double IS, double K, double VTH);

double delta_norm(void);


#endif 
