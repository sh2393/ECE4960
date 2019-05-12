#include <iostream>
#include "solver.h"

using namespace std;

ofstream ofile1;


int main(int argc, char* argv[]){
	double dt, dx, dy, theta, T;
	int Nx, Ny, Nt;
	double thetaForwardEuler = 0.0;

	string outfileName, scenario;

	//====Input=====//
	outfileName = "outFE.txt";
	scenario = "1D";
	double dxValues[2] = {0.1, 0.01};
	double safetyFactors[2] = {0.96, 1.04};

	//pick 1 for test run
	dx = dxValues[0];
	dt = pow(dx, 2)/2.0*(1/safetyFactors[0]);
	double alpha = dt/pow(dx,2);
	theta = 0.5;
	T = 0.5;
	Nt = (int)(T/dt)+1;
	Nx = (int)(1/dx+1);
	Ny = Nx;
	dy = dx;


	//==============//

	if (scenario == "1D"){
		ArrayXXd solutionFE = ArrayXXd::Zero(Nx+1, Nt+1);
		ArrayXXd solutionExact = ArrayXXd::Zero(Nx+1, Nt+1);

		string outfileNameFE = outfileName + "ForwardEuler";

		cout << "dt: " << dt << endl;

		Solver forwardEuler = Solver(dt, dx, thetaForwardEuler, T, Nx, Nt);
		solutionFE = forwardEuler.solve(outfileNameFE);

		cout << solutionFE(0, 0) << endl;

		//solutionExact = analyticalU(outfileName, dt, dx, Nt, Nx);
	}

	return 0;

}