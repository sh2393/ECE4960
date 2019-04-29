/*H**********************************************************************
* FILENAME :        fullGriddedearch.cpp
*
* DESCRIPTION :
*       Helper method for gridded search
*       Public methods included in the methods header. 
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :   28 Apr 2019
*
*H*/


#include "methods.hpp"
#include "paramExtraction.hpp"
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void fullGriddedSearch(void) {
    cout << "Performing a full gridded search" << endl;

    vector<double> isGridded = {1E-8,3E-8,1E-7,3E-7,1E-6,3E-6,1E-5,3E-5};
    vector<double> kGridded = {0.5,0.6,0.7,0.8,0.9};
    vector<double> vthGridded = {0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0};
    double test=0, min=1, Is_opt=0, k_opt=0, Vth_opt=0;
    
    for (int i=0; i<isGridded.size(); i++) {
        for (int j=0; i<kGridded.size(); i++) {
            for (int k=0; i<vthGridded.size(); i++) {
                test = V(isGridded[i],kGridded[j],vthGridded[k]);
                if (test < min) { 
                    Is_opt = isGridded[i];
                    k_opt = kGridded[j];
                    Vth_opt = vthGridded[k];
                }
            }
        }
    }

    printf("Results\n");
    printf("V  = %10f\nIs = %10f\nk  = %10f\nVth= %10f\n", V(Is_opt,k_opt,Vth_opt), Is_opt, k_opt, Vth_opt);
}