#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>

#include "../eigen/Eigen/Eigen"

using namespace std;
using namespace Eigen;



class Solver{
public:
	Solver(double dt_, double dx_, double theta_, double T_, int Nx_, int Nt_);
	ArrayXXd solve(string outfileName_);
	void calculate_error(ArrayXXd numerical, ArrayXXd exact, double *error, int Nx_, int Nt_);

private:
	string outfileName;
	double dt, dx, theta, T;
	int Nx, Nt;
	double alpha;
	double offDiagonalLhs;
	double diagonalLhs;
	double offDiagonalRhs;
	double diagonalRhs;

	void computeRhs(double *result, double* u_1, double offDiagonalRhs, double diagonalRhs, int Nx);
	void gaussianSolver(double * result, double *u, double *u_1, double offDiagonalLhs, double diagonalLhs, int Nx);
};

#endif