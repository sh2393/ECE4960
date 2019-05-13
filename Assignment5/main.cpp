#include <iostream>
#include "solver.h"
#include "solver2D.h"
#include "helpers.h"
#define   ZERO       1.0E-10

using namespace std;

ArrayXXd analyticalU (string outfileName, double dt, double dx, int Nt, int Nx);
ArrayXXd analytical2D(string outfileName, double dt, double dx, double dy, int Nt, int Nx, int Ny, Solver2D solver);
double gaussQuad(int numberOfSummationPoints, int n, int m, int numberOfIntegrationPoints);

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
	outfileName = "results/out5C";
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


ArrayXXd analytical2D(string outfileName, double dt, double dx, double dy, int Nt, int Nx, int Ny, Solver2D solver)
{
    int t=0;int i=0;int j=0;int n=0;int m=0;
    string outfileNameAnalytical = outfileName + "AnalyticalSolutionMatrixU2D";
    double uSs;
    ArrayXXd analyticalMatrixU2D;
    double fourOverPi = 4.0/M_PI;
    double tempSum = 0.0;
    int counter = 1;
    uSs = 0.0;
    double integral = 0.;
    int integrationPoints = 30;
    int sumLimit = 15;// for sums with integrals
    for (t = 0; t < Nt; t++){
        analyticalMatrixU2D = ArrayXXd::Zero(Nx,Ny);

        for (i = 0; i < Nx ; i++){//note: changed from 1 to 0
            for (j = 0; j < Ny; j++){
                tempSum = 0.;
                for (n = 1; n < sumLimit; n++){
                    for (m = 1; m < sumLimit; m++){
                        integral = gaussQuad(sumLimit, n, m, integrationPoints);
                        tempSum += integral*sin(n*M_PI*i*dx)*sin(m*M_PI*j*dy)*exp(-pow(M_PI,2)*(n*n + m*m)*t*dt);
                    }
                }
                uSs = solver.uSteadyState(i*dx, j*dy);
                analyticalMatrixU2D(i,j) = uSs -4.*tempSum;
            }
        }
        writeToCSVfile(outfileNameAnalytical+to_string(counter)+ ".txt", analyticalMatrixU2D);
        counter +=1;
    }
    return analyticalMatrixU2D;
}

void gauleg(double x1, double x2, double x[], double w[], int n){
	int         m,j,i;
	double      z1,z,xm,xl,pp,p3,p2,p1;
	double      const  pi = 3.14159265359;
	double      *x_low, *x_high, *w_low, *w_high;

	m  = (n + 1)/2;                             // roots are symmetric in the interval
	xm = 0.5 * (x2 + x1);
	xl = 0.5 * (x2 - x1);

	x_low  = x;                                       // pointer initialization
	x_high = x + n - 1;
	w_low  = w;
	w_high = w + n - 1;

	for(i = 1; i <= m; i++) {                             // loops over desired roots
		z = cos(pi * (i - 0.25)/(n + 0.5));

		do {
		    p1 =1.0;
		 	p2 =0.0;

			for(j = 1; j <= n; j++) {
			    p3 = p2;
			    p2 = p1;
			    p1 = ((2.0 * j - 1.0) * z * p2 - (j - 1.0) * p3)/j;
			}

			pp = n * (z * p1 - p2)/(z * z - 1.0);
			z1 = z;
			z  = z1 - p1/pp;                   // Newton's method
	  	} while(fabs(z - z1) > ZERO);


	  	*(x_low++)  = xm - xl * z;
	  	*(x_high--) = xm + xl * z;
	  	*w_low      = 2.0 * xl/((1.0 - z * z) * pp * pp);
	  	*(w_high--) = *(w_low++);
	}
} // End_ function gauleg()

double gaussQuad(int numberOfSummationPoints, int n, int m, int numberOfIntegrationPoints){
    int k=0;
    int integrationCounter=0;
    double leftIntegrationLimit = 0.;
    double rightIntegrationLimit = 1.;
    double *xPoints = new double [numberOfIntegrationPoints];
    double *w = new double [numberOfIntegrationPoints];

    gauleg(leftIntegrationLimit , rightIntegrationLimit,xPoints, w, numberOfIntegrationPoints);
    double integralSum = 0.;
    double beta;

    for ( k = 1;  k < numberOfSummationPoints; k++){
        beta = 2*k-1;
        double intGaussX = 0.;
        double intGaussY = 0.;
        for (integrationCounter =0; integrationCounter < numberOfIntegrationPoints; integrationCounter++){
            intGaussX += w[integrationCounter]*sin(beta*M_PI*xPoints[integrationCounter])*sin(n*M_PI*xPoints[integrationCounter]);
            intGaussY += w[integrationCounter]*sinh(beta*M_PI*xPoints[integrationCounter])*sin(m*M_PI*xPoints[integrationCounter]);
        }
        integralSum += 4./M_PI*intGaussX*intGaussY/(beta*sinh(beta*M_PI));
    }
    return integralSum;
}
