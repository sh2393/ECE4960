#include <iostream>
#include "CSR_matrix.hpp"

using namespace std;

int main(){
	vector<int> val{1,2,3,4,5,6,7,8,9,10,11,12};
	vector<int> row{0,3,6,9,10,12};
	vector<int> col{0,1,4,0,1,2,1,2,4,3,0,4};

	Matrix matrix(val, row, col);

/*
	(1)	Permutation of (1, 3) and then (1, 5).  
	(2)	Test 3.0*row[1] + row [4] and -4.4*row[5] + row[2].
	(3)	Test Ax = b.
*/
	cout << "matrix" << endl;
	matrix.printMatrix();

	cout << "row permutation 1 and 3" << endl;
	matrix.rowPermute(0, 2);
	matrix.printMatrix();

	cout << "row permutation 1 and 5" << endl;
	matrix.rowPermute(0, 4);
	matrix.printMatrix();

	cout << "3.0*row[1] + row [4]" << endl;
	matrix.rowScale(0, 3, 3);
	matrix.printMatrix();

	cout << "-4.4*row[5] + row[2]" << endl;
	matrix.rowScale(4, 1, -4);
	matrix.printMatrix();

	cout << "Ax = b" << endl;
	vector<int> x{5, 4, 3, 2, 1};
	vector<int> b(5, 0);
	matrix.productAx(x, &b);
	for(int i = 0; i < b.size(); i++){
		cout << b[i] << " " << endl;
	}
	cout << endl;

	return 0;
}