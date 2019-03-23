#include <iostream>
#include "CSR_matrix.h"

using namespace std;

int main(){
	

	vector<int> val{1,2,3,4,5,6,7,8,9,10,11,12};
	vector<int> row{0,3,6,9,10,12};
	vector<int> col{0,1,4,0,1,2,1,2,4,3,0,4};

	Matrix matrix(val, row, col);

	//4.1 CSR_matrix test functions
	cout << matrix.rankMatrix() << endl;
    cout << matrix.retrieveElement(2, 2) << endl;
    cout << matrix.countElementMatrix() << endl;
    matrix.printMatrix(); 

 //    matrix.addElement(3, 2, 13);
 //    cout << matrix.rankMatrix() << endl;
 //    cout << matrix.retrieveElement(3, 2) << endl;
 //    cout << matrix.countElementMatrix() << endl;
	// matrix.printMatrix();   


	// matrix.deleteElement(1, 1) ;
	// cout << matrix.rankMatrix() << endl;
 //    cout << matrix.retrieveElement(1, 1) << endl;
 //    cout << matrix.countElementMatrix() << endl; 
	// matrix.printMatrix();  

	// matrix.rowPermute(0, 1);
	// matrix.printMatrix();
	matrix.rowScale(4, 2, 2);
	matrix.printMatrix();

    return 0;
}