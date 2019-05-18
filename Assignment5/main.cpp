#include <iostream>
#include "solver.h"
#include "solver2D.h"
#include "helpers.h"

using namespace std;

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
	outfileName = "results/out2DJacobi";
	scenario = "2DJacobi";
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
        string oufileNameCrancNicholson = outfileName + "CrankNicholson";

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

	if (scenario == "2D"){
		string outfileName2DExplicit;
        string outfileName2DImplicit;
        string outfileName2DImplicitGaussSeidel;

        Solver2D explicit2D = Solver2D(dt, dx, dy, thetaForwardEuler, T, Nx, Ny, Nt);
        Solver2D implicit2D = Solver2D(dt, dx, dy, thetaForwardEuler, T, Nx, Ny, Nt);
        Solver2D implicit2DGaussSeidel = Solver2D(dt, dx, dy, thetaForwardEuler, T, Nx, Ny, Nt);

        outfileName2DExplicit = outfileName + "Explicit";
        explicit2D.solve(outfileName2DExplicit, "Explicit");

        outfileName2DImplicit = outfileName + "Implicit";
        implicit2D.solve(outfileName2DImplicit, "ImplicitJacobi");

        outfileName2DImplicitGaussSeidel = outfileName + "GaussSeidel";
        implicit2DGaussSeidel.solve(outfileName2DImplicitGaussSeidel, "ImplicitGauss");

        analytical2D(outfileName, dt, dx, dy, Nt, Nx, Ny, explicit2D);

	}

	if (scenario == "2DJacobi"){
        string outfileName2DImplicitJacobi;
        Solver2D implicit2DJacobi = Solver2D( dt, dx, dy, thetaForwardEuler, T, Nx, Ny, Nt);

        outfileName2DImplicitJacobi = outfileName +"Jacobi";
        implicit2DJacobi.solve(outfileName2DImplicitJacobi, "ImplicitJacobi");

        string outfileName2DImplicitGaussSeidel;
        Solver2D implicit2DGaussSeidel = Solver2D( dt, dx, dy, thetaForwardEuler, T, Nx, Ny, Nt);

        outfileName2DImplicitGaussSeidel = outfileName + "GaussSeidel";
        implicit2DGaussSeidel.solve(outfileName2DImplicitGaussSeidel, "ImplicitGaussSeidel");
    }

	return 0;

}




