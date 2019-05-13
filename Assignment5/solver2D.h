#ifndef SOLVER2D_H
#define SOLVER2D_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>

#include "../eigen/Eigen/Eigen"

using namespace std;
using namespace Eigen;

class Solver2D{
private:
	string outfileName;
	double dt, dx, dy, theta, T, alpha;
	int Nx, Ny, Nt;

	//steady state solution
	void explicitScheme( double **u, double **u_1, int Nx, int Ny);
	void backwardEulerJacobi( double **u, double **u_1, int Nx, int Ny, int maxIterations, double tolerance, double &iter);
	void backwardEulerGauss(double **u, double **u_1 ,int Nx, int Ny, int maxIterations, double tolerance, double &iter);
	double** createMatrix(int m, int n);
	void destroyMatrix(double** mat, int m, int n);
	void setEqual(double **A, double **B, int m, int n);

public:
	Solver2D(double dt_, double dx_, double dy_, double theta_, double T_, int Nx_, int Ny_, int Nt_);
	ArrayXXd solve(string outfileName_, string method_);
	double uSteadyState(double x, double y);
	void calculate_error(ArrayXXd numerical, ArrayXXd exact, double *error, int Nx_, int Nt_);

};

#endif