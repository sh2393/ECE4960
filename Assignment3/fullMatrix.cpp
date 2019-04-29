/*H**********************************************************************
* FILENAME :        fullMatrix.hpp
*
* DESCRIPTION :
*       Full matrix helper operations  
*       Helper methods implemented:
*           compute_determinant() 
*           compute_inverse()
*
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :   28 Apr 2019
*
*H*/

#include "fullMatrix.hpp"

double fullMatrix::compute_determinant(){
	return (1.0)/
		 (val[0][0]*(val[1][1]*val[2][2] - val[1][2]*val[2][1]) 
		- val[0][1]*(val[1][0]*val[2][2] - val[1][2]*val[2][0]) 
		+ val[0][2]*(val[1][0]*val[2][1] - val[1][1]*val[2][0]));
}

int fullMatrix::compute_inverse(vector<vector<double>> &Inverse){
	double det = compute_determinant();

	if (det == 0) return 1;

	Inverse[0][0] = det*(val[1][1]*val[2][2] - val[1][2]*val[2][1]);
    Inverse[0][1] = det*(val[0][2]*val[2][1] - val[0][1]*val[2][2]);
    Inverse[0][2] = det*(val[0][1]*val[1][2] - val[0][2]*val[1][1]);
    Inverse[1][0] = det*(val[1][2]*val[2][0] - val[1][0]*val[2][2]);
    Inverse[1][1] = det*(val[0][0]*val[2][2] - val[0][2]*val[2][0]);
    Inverse[1][2] = det*(val[0][2]*val[1][0] - val[0][0]*val[1][2]);
    Inverse[2][0] = det*(val[1][0]*val[2][1] - val[1][1]*val[2][0]);
    Inverse[2][1] = det*(val[0][1]*val[2][0] - val[0][0]*val[2][1]);
    Inverse[2][2] = det*(val[0][0]*val[1][1] - val[0][1]*val[1][0]);

    return 0;
}

