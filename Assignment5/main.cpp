#include <iostream>
#include "solver.h"
#include "helpers.h"

using namespace std;

ArrayXXd analyticalU (string outfileName, double dt, double dx, int Nt, int Nx);

ofstream ofile1;


int main(int argc, char* argv[]){
	double dt, dx, dy, theta, T;
	int Nx, Ny, Nt;
	double thetaForwardEuler = 0.0;
	double thetaBackwardEuler = 1.0;
    double thetaCranckNicholson = 0.5;
	double computed_error;

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
		ArrayXXd solutionMatrixFe = ArrayXXd::Zero(Nx+1, Nt+1);
		ArrayXXd solutionMatrixBe = ArrayXXd::Zero(Nx+1, Nt+1);
		ArrayXXd solutionMatrixCn = ArrayXXd::Zero(Nx+1, Nt+1);
		ArrayXXd solutionMatrixExact = ArrayXXd::Zero(Nx+1, Nt+1);

		int numberOfSchemes = 3;
        int numberOfVariablesNormMatrix = 3;
        ArrayXXd normMatrix= ArrayXXd::Zero(numberOfSchemes, numberOfVariablesNormMatrix);


		string oufileNameForwardEuler = outfileName + "ForwardEuler";
        string oufileNameBackwardEuler = outfileName + "BackwardEuler";
        string oufileNameCrancNicholson = outfileName + "CrancNicholson";

		cout << "alpha: " << alpha << endl;

		Solver forwardEuler =  Solver( dt, dx, thetaForwardEuler, T, Nx, Nt);
        Solver backwardEuler =  Solver( dt, dx, thetaBackwardEuler, T,Nx, Nt);
        Solver cranckNicholson =  Solver( dt, dx, thetaCranckNicholson, T,Nx, Nt);

        solutionMatrixFe  = forwardEuler.solve(oufileNameForwardEuler);
        solutionMatrixBe  = backwardEuler.solve(oufileNameBackwardEuler);
        solutionMatrixCn  = cranckNicholson.solve(oufileNameCrancNicholson);


		solutionMatrixExact = analyticalU(outfileName, dt, dx, Nt, Nx);

		//calculate error
		forwardEuler.calculate_error(solutionMatrixFe, solutionMatrixExact, &computed_error, Nx, Nt);
		normMatrix(0,0) = log2(dt);
		normMatrix(0,1) = log2(dx);
		normMatrix(0,2) = computed_error;

		backwardEuler.calculate_error(solutionMatrixBe, solutionMatrixExact, &computed_error, Nx, Nt);
        normMatrix(1,0) = log2(dt);
        normMatrix(1,1) = log2(dx);
        normMatrix(1,2) = computed_error;

        cranckNicholson.calculate_error(solutionMatrixCn, solutionMatrixExact, &computed_error, Nx, Nt);
        normMatrix(2,0) = log2(dt);
        normMatrix(2,1) = log2(dx);
        normMatrix(2,2) = computed_error;

		writeToCSVfile(outfileName, normMatrix);
	}

	return 0;

}

ArrayXXd analyticalU (string outfileName, double dt, double dx, int Nt, int Nx){
	ArrayXXd analyticalMatrixU = ArrayXXd::Zero(Nx+1, Nt+1);
	string outfileNameAnalytical;
	double uAnalytical;

	for(int t = 1; t < Nt; t++){
		for(int x = 0; x < Nx; x++){
			uAnalytical = 0;
			for(int k = 1; k < 1000; k++){
				uAnalytical += exp(-pow(k*M_PI, 2)*(dt*t))*2./(k*M_PI)*pow((-1.), k)*sin(k*M_PI*dx*x);
			}
			uAnalytical += dx*x;
			analyticalMatrixU(0, t+1) = t*dt;
			analyticalMatrixU(x+1, 0) = x*dx;
			analyticalMatrixU(x+1, t+1) = uAnalytical;
		}
	}

	outfileNameAnalytical = outfileName + "analyticalSolutionMatrixU.txt";
	writeToCSVfile(outfileNameAnalytical, analyticalMatrixU);
	return analyticalMatrixU;
}
