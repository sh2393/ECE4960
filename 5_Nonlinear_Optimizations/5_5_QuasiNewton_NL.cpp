#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


double V(double x1, double x2) {
    return pow( 3.0*pow(x1,2)+x2-4.0, 2) + pow( pow(x1,2)-3.0*x2+2.0, 2);
}

void QuasiNewtonLineSearch(double x1, double x2) {
    
    double errorTolerance = 1E-7;
    double deltaX1=0, deltaX2=0;
    int iteration = 1;
    
    // Hessian matrix
    double a, b, c, d;
    vector<vector<double>> invHessian = {{0,0},{0,0}};
    double determinant;
    
    // del V
    double delx1, delx2;
    
    do {
        
        cout << endl << "Iteration # " << iteration++ << endl;
        // Compute Hessian matrix
        // a  b
        // c  d
        a = (V(x1+0.0001*x1,x2) - 2.0*V(x1,x2) + V(x1-0.0001*x1,x2))/pow(0.0001*x1,2);
        b = c = (V(x1+0.0001*x1,x2+0.0001*x2) - V(x1,x2) - V(x1,x2) + V(x1-0.0001*x1,x2-0.0001*x2))/(0.0001*x1*0.0001*x2);
        d = (V(x1,x2+0.0001*x2) - 2.0*V(x1,x2) + V(x1-0.0001*x1,x2-0.0001*x2))/pow(0.0001*x2,2);
        cout << "Hessian: " << a << " " << b << endl << "         " << c << " " << d << endl;
        
        // Compute inverse of Hessian
        determinant = 1.0/(a*d - b*c);
        cout << "determinant: " << determinant << endl;
        invHessian[0][0] = d*determinant;
        invHessian[0][1] = -b*determinant;
        invHessian[1][0] = -c*determinant;
        invHessian[1][1] = a*determinant;
        cout << "invHessian: " << invHessian[0][0] << " " << invHessian[0][1] << endl << "           " << invHessian[1][0] << " " << invHessian[1][1] << endl;
        
        // Compute del V
        delx1 = (V(1.0001*x1,x2) - V(x1,x2))/(0.0001*x1);
        delx2 = (V(x1,1.0001*x2) - V(x1,x2))/(0.0001*x2);
        
        // Compute the delta x values
        deltaX1 = -(invHessian[0][0]*delx1 + invHessian[0][1]*delx2);
        deltaX2 = -(invHessian[1][0]*delx1 + invHessian[1][1]*delx2);
        
        // temp variables to help with line search
        double tempdeltaX1 = deltaX1;
        double tempdeltaX2 = deltaX2;
        
        // Line Search: find a multiple of deltaX which makes the function as close to zero as possible
        for (double i=1.0; i<=10000.0; i++) {
            if (V(x1+tempdeltaX1,x2) > V(x1+i*deltaX1,x2)) {
                tempdeltaX1 = i*deltaX1;
            }
        }
        for (double i=1.0; i<=10000.0; i++) {
            if (V(x1,x2+tempdeltaX2) > V(x1,x2+i*deltaX2)) {
                tempdeltaX2 = i*deltaX2;
            }
        }
        
        deltaX1 = tempdeltaX1;
        cout << "deltaX1 = " << deltaX1 << endl;
        deltaX2 = tempdeltaX2;
        cout << "deltaX2 = " << deltaX2 << endl;
        x1 = x1 + deltaX1;
        cout << "x1 = " << x1 << endl;
        x2 = x2 + deltaX2;
        cout << "x2 = " << x2 << endl;
        
        cout << "deltaX1 = " << deltaX1 << endl;
        cout << "deltaX2 = " << deltaX2 << endl;
        cout << "V(" << x1 << "," << x2 << ") = " << V(x1,x2) << endl;
        
    } while (abs(V(x1,x2)) > errorTolerance);
    
    cout << endl << "The solution is: " << endl;
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;
}

int main(){
	QuasiNewtonLineSearch(0.1, 0.1);
	return 0;
}