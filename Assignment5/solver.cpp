#include "solver.h"
#include "helpers.h"

Solver::Solver(double dt_, double dx_, double theta_, double T_, int Nx_, int Nt_){
	dt = dt_;
	dx = dx_;
	theta = theta_;
	T = T_;
	Nt = Nt_;
	Nx = Nx_;
}

ArrayXXd Solver::solve(string outfileName_){
	outfileName = outfileName_;
	ArrayXXd solutionMatrixU = ArrayXXd::Zero(Nx+1, Nt+1);

	alpha = dt/pow(dx, 2);
	offDiagonalLhs = -2*alpha*theta;
	diagonalLhs = 2.*(2.*alpha*theta + 1);
    offDiagonalRhs = 2.*alpha*(1. - theta);
    diagonalRhs = 2.*(1.-2.*alpha*(1.-theta));

    double *u, *result, *u_1;
    u 	= new double[Nx];
    u_1 = new double[Nx];
    result = new double[Nx];

    for(int i = 0; i < Nx; i++){
    	u_1[i] = -dx*i;
    	u[i] = 0;
    	result[i] = 0;
    }

    for(int t = 0; t < Nt; t++){
    	computeRhs(result, u_1, offDiagonalRhs, diagonalRhs, Nx);
    	gaussianSolver(result, u, u_1, offDiagonalLhs, diagonalLhs, Nx);

    	for(int i = 0; i < Nx; i++){
    		u[i] += dx*i;
    		solutionMatrixU(0, t+1) = t*dt;
    		solutionMatrixU(i+1, 0) = i*dx;
    		solutionMatrixU(i+1,t+1)= u[i];
    	}
    }

    //new comment
//    solutionMatrixU.save(outfileName + "solutionMatrixU.txt", iswascii);
    string fname = outfileName + "solutionMatrixU.txt";
    writeToCSVfile(fname, solutionMatrixU);

    delete [] result;
    delete [] u;
    delete [] u_1;

    return solutionMatrixU;
}

void Solver::computeRhs(double *result, double* u_1, double offDiagonalRhs, double diagonalRhs, int Nx){
	result[1] = diagonalRhs*u_1[1] + offDiagonalRhs * u_1[2];
	for(int i = 2; i < Nx-2; i++ ){
		result[i] = offDiagonalRhs * u_1[i-1] + diagonalRhs * u_1[i] + offDiagonalRhs * u_1[i+1];
	}
	result[Nx-2] = offDiagonalRhs * u_1[Nx-3] + diagonalRhs * u_1[Nx-2];
	result[0] = 0;
	result[Nx-1] = 0;
}

void Solver::gaussianSolver(double * result, double *u, double *u_1, double offDiagonalLhs, double diagonalLhs, int Nx){
	double* f; 
	f = new double[Nx];
	f[0] = 0;
	f[Nx-1] = 0;
	f[1] = result[1];

	double *g;
	g = new double[Nx];
	g[0] = 0;
	g[Nx-1] = 0;
	g[1] = diagonalLhs;
	for(int i = 2; i < Nx-1; i++){
		g[i] = diagonalLhs - pow(offDiagonalLhs, 2)/g[i-1];
		f[i] = result[i] - offDiagonalLhs*f[i-1]/g[i-1];
	}

	//Backward Substitution
	u[0] = 0;
	u[Nx-1] = 0;
	u[Nx-2] = f[Nx-2]/g[Nx-2];
	for(int i = Nx-2; i>1; i--){
		u[i-1] = (f[i-1] - offDiagonalLhs*u[i])/g[i-1];
	}

	delete [] f;
	delete [] g;
	for(int i = 0; i < Nx; i++) u_1[i] = u[i];

}

void Solver::calculate_error(ArrayXXd numerical, ArrayXXd exact, double *error, int Nx_, int Nt_){
	//L2 norm
	*error = 0;

	double sum = 0;
	for(int t = 3; t < Nt_; t++){
		for(int i = 3; i < Nx_; i++){
			sum += pow((numerical(i, t) - exact(i, t)), 2);
		}
	}

	sum = sqrt(dt*dx*sum);
	*error = sum;
}
