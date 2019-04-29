/*H**********************************************************************
* FILENAME :        dmSolver.hpp 
*
* DESCRIPTION :
*       Header file for direct matrix implementation
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :   28 Apr 2019
*
*H*/

#ifndef _DMSOLVER_HPP
#define _DMSOLVER_HPP

#include <vector>

using namespace std;

class DMMatrix{
public:
	vector<vector<double>> A;
	vector<double> B;

	int dimension;

	DMMatrix(vector<vector<double>> value_in, vector<double> B_in){
		A = value_in;
		B = B_in;
		dimension = value_in.size();
	}

	void printDMMatrix();

	void swapRow(int i, int j);

	void rowScale(int i, int j, double c);

	void Gaussian(int index);

	int rowChoice(int index);
	
};

void Solver(DMMatrix system, vector<double> X);

int verifySolver();

#endif







