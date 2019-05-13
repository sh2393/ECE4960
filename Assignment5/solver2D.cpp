#include "solver2D.h"
#include "helpers.h"


Solver2D::Solver2D(double dt_, double dx_, double dy_, double theta_, double T_, int Nx_, int Ny_, int Nt_){
	dt = dt_;
	dx = dx_;
	dy = dy_;
	theta = theta_;
	T = T_;
	Nt = Nt_;
	Nx = Nx_;
	Ny = Ny_;
}

ArrayXXd Solver2D::solve(string outfileName_, string method_){
	outfileName = outfileName_;

	double iter = 0.0;
	int maxIterations = 100000;
	VectorXd iterCol = VectorXd::Zero(1);

	double tolerance = 1E-6;
	ArrayXXd solutionMatrixU = ArrayXXd::Zero(Nx, Ny);

	alpha = dt/pow(dx, 2);

	double **u, **u_1;
	u_1 = createMatrix(Nx, Ny);
	u = createMatrix(Nx, Ny);

	for(int i = 0; i < Nx; i++){
		for(int j = 0; j < Ny; j++){
			u_1[i][j] = -uSteadyState(i*dx,j*dy);
		}
	}

	int counter = 1;
	for(int t = 1; t < Nt; t++){
		if (method_ == "Explicit") explicitScheme(u, u_1, Nx, Ny);
		else if (method_ == "ImplicitJacobi") backwardEulerJacobi(u, u_1, Nx, Ny, maxIterations, tolerance, iter);
		else if (method_ == "ImplicitGauss") backwardEulerGauss(u, u_1, Nx, Ny, maxIterations, tolerance, iter);
		for(int i = 0; i < Nx; i++){
			for(int j = 0; j < Ny; j++){
				u[i][j] += uSteadyState(i*dx, j*dy);
				solutionMatrixU(i, j) = u[i][j];
			}
		}
		writeToCSVfile(outfileName + "solutionMatrixUTime" + to_string(counter) + ".txt", solutionMatrixU);
		iterCol(0) = iter;
		counter += 1;
	}
	writeToCSVfile(outfileName + "IterationNumber.txt", iterCol);
	destroyMatrix(u, Nx, Ny);
	destroyMatrix(u_1, Nx, Ny);
	return solutionMatrixU;
}


double Solver2D::uSteadyState(double x, double y){
	int k;
	double u_ss = 0.0;
	double c = 4.0/M_PI;

	for(k = 1; k < 15; k++){
		double beta = 2*k-1;
		u_ss = sin(beta*M_PI*x)*sinh(beta*M_PI*y)/(beta*sinh(beta*M_PI));
	}

	u_ss *= c;
	return u_ss;
}

void Solver2D::explicitScheme( double **u, double **u_1, int Nx, int Ny){
	for(int i = 0; i < Nx; i++){
		u[i][0] = u[0][i] = u[i][Nx-1] = u[Nx-1][i] = 0.0;
	}

	for(int i = 1; i < Nx-1; i++){
		for(int j = 1; j < Ny-1;j++){
			u[i][j] = u_1[i][j] + alpha*(u_1[i+1][j] + u_1[i-1][j] + u_1[i][j+1] + u_1[i][j-1] - 4*u_1[i][j]);
		}
	}

	setEqual(u_1, u, Nx, Ny);
}


void Solver2D::backwardEulerJacobi( double **u, double **u_1, int Nx, int Ny, int maxIterations, double tolerance, double &iter){
    for (int i = 0 ; i < Nx; i++){
        u[i][0] = u[0][i] = u[i][Nx-1] = u[Nx-1][i] = 0.0;
    }
    double **uTemp = createMatrix(Nx, Ny);
    double diff = 1.;
    int iterations = 1;

    while ((iterations < maxIterations) && (diff > tolerance)){
        diff = 0.;
        setEqual(uTemp, u, Nx, Ny);

        for (int i = 1; i < Nx-1; i++){
            for (int j = 1; j < Ny-1; j++){
                u[i][j] =   1./(1+4.*alpha)*(alpha*(uTemp[i+1][j] + uTemp[i-1][j] + uTemp[i][j+1] + uTemp[i][j-1]) + u_1[i][j]);
                diff += fabs(u[i][j] - uTemp[i][j]);
            }
        }
        diff /= (Nx*Ny);
        iterations += 1;
    }
    iter = iterations/double(Nx);
    if ((iterations == maxIterations) && (diff > tolerance))
        cout << "Iteration limit reached without convergence. |u^(k+1) - u^k| = " << diff << endl;
    setEqual(u_1, u, Nx, Ny);
    destroyMatrix(uTemp, Nx, Ny);
}


void Solver2D::backwardEulerGauss(double **u, double **u_1 ,int Nx, int Ny, int maxIterations, double tolerance, double &iter){
    for (int i = 0 ; i < Nx; i++){
        u[i][0] = u[0][i] = u[i][Nx-1] = u[Nx-1][i] = 0.0;
    }

    double **uTemp = createMatrix(Nx, Ny);
    double diff = 1.;
    int iterations = 1;
    while ((iterations < maxIterations) && (diff > tolerance)){
        diff = 0.;
        setEqual(uTemp, u, Nx, Ny);
        for (int i = 1; i < Nx-1; i++){
            for (int j = 1; j < Ny-1; j++){
                u[i][j] =   1./(1+4.*alpha)*(alpha*(u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1]) + u_1[i][j]);
                diff += fabs(u[i][j] - uTemp[i][j]);
            }
        }
        diff /= (Nx*Ny);
        iterations += 1;
    }
    iter = iterations/double(Nx);
    if ((iterations == maxIterations) && (diff > tolerance))
        cout << "Iteration limit reached without convergence. |u^(k+1) - u^k| = " << diff << endl;
    setEqual(u_1, u, Nx, Ny);
    destroyMatrix(uTemp, Nx, Ny);
}

double** Solver2D::createMatrix(int m, int n){
	double ** mat;
	mat = new double*[m];

	for(int i=0;i<m;i++){
		mat[i] = new double[n];
		for(int j=0;j<m;j++){
		  mat[i][j] = 0.0;
		}
	}
	return mat;
}

void Solver2D::destroyMatrix(double** mat, int m, int n){
	for(int i=0;i<m;i++)
    delete[] mat[i];
  	delete[] mat;
}

void Solver2D::setEqual(double **A, double **B, int m, int n){
	for (int i = 0; i < m; i++){
	    for (int j = 0; j < n; j++){
	        A[i][j] = B[i][j];
	    }
	}
}

void Solver2D::calculate_error(ArrayXXd numerical, ArrayXXd exact, double *error, int Nx_, int Nt_){
	*error = 0.0;
	double sum = 0.0;
	for(int i = 0; i < Nx_; i++){
		for(int j = 0; j < Nx_; j++){
			sum += pow((numerical(i,j) - exact(i, j)), 2);
		}
	}

	sum = sqrt(dx*dx*sum);
	*error = sum;
}




