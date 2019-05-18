#include "helpers.h"

void writeToCSVfile(string name, ArrayXXd matrix)
{
    ofstream file(name.c_str());
    file << matrix.format(CleanFormat);
}

void gauleg(double x1, double x2, double x[], double w[], int n){
	int         m,j,i;
	double      z1,z,xm,xl,pp,p3,p2,p1;
	double      const  pi = 3.14159265359;
	double      *x_low, *x_high, *w_low, *w_high;

	m  = (n + 1)/2;                             
	xm = 0.5 * (x2 + x1);
	xl = 0.5 * (x2 - x1);

	x_low  = x;                                       
	x_high = x + n - 1;
	w_low  = w;
	w_high = w + n - 1;

	for(i = 1; i <= m; i++) {                             
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
} 

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