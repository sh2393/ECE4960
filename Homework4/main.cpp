#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <armadillo>

#include "CSR_matrix.hpp"
#include "test_functions.hpp"

using namespace std;
using namespace arma;

void partAtest(){
	vector<double> val{1,2,3,4,5,6,7,8,9,10,11,12};
	vector<int> row{0,3,6,9,10,12};
	vector<int> col{0,1,4,0,1,2,1,2,4,3,0,4};

	Matrix matrix(val, row, col);

	cout << "matrix" << endl;
	matrix.printMatrix();

	cout << "add element" << endl;
	matrix.addElement(3, 1, 13);
	matrix.addElement(4, 1, 14);
	matrix.addElement(4, 2, 15);
	matrix.addElement(4, 3, 16);

	matrix.printMatrix();
	cout << matrix.countElementMatrix() << endl;
	cout << matrix.rankMatrix() << endl;

	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			cout << matrix.retrieveElement(i, j) << " "; // should be 11
		}
		cout << endl;
	}

	matrix.deleteElement(0, 0);
	matrix.deleteElement(4, 1);
	matrix.deleteElement(4, 2);
	matrix.deleteElement(4, 3);
	matrix.printMatrix();
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			cout << matrix.retrieveElement(i, j) << " "; // should be 11
		}
		cout << endl;
	}
	cout << matrix.countElementMatrix() << endl;
	cout << matrix.rankMatrix() << endl;

	//assignment tasks
	/*
		(1)	Permutation of (1, 3) and then (1, 5).  
		(2)	Test 3.0*row[1] + row [4] and -4.4*row[5] + row[2].
		(3)	Test Ax = b.
	*/
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
	vector<double> x{1, 1, 2, 2, 1};
	vector<double> b;
	matrix.productAx(x, &b);
	for(int i = 0; i < b.size(); i++){
		cout << b[i] << " ";
	}
	cout << endl;
}


void testload(Matrix* mpm){
	int rowRank, colRank, nNZ;
	int lc = 1;
	string line;
	ifstream memplus("mpm_text.mtx");
	if (memplus.is_open()){
		while(getline(memplus, line)){
			istringstream iss(line);
			if (lc > 2){
				int ri, ci; 
				double val;
				if(!(iss >> ri >> ci >> val)) { break; }
				ri = ZTO(ri);
				ci = ZTO(ci);
				//printf("\n%d, %d, %f\n", ri, ci, val);

				mpm->addElement(ri, ci, val);
				printf("%.16e\n", mpm->retrieveElement(ri, ci));
			}else if (lc == 2){
				iss >> rowRank >> colRank >> nNZ;
				lc++;
			}else{
				lc++;
			}
		}
		memplus.close();
	}
}

void BTask1(Matrix* mpm){
	mpm->rowPermute(ZTO(1), ZTO(3));
	mpm->rowPermute(ZTO(1), ZTO(5));
	mpm->rowPermute(ZTO(10), ZTO(3000));
	mpm->rowPermute(ZTO(5000), ZTO(10000));
	mpm->rowPermute(ZTO(6), ZTO(15000));
}

void BTask2(Matrix* mpm){
	mpm->rowScale(2, 4, 3.0);
	mpm->rowPermute(2, 5);
}


void BTest(){
	//part B
	Matrix mpm;
	testload(&mpm);
	//cout << mpm.retrieveElement(ZTO(1), ZTO(2));
	// BTask1(&mpm);
	// BTask2(&mpm);
}

int main(){
	
	// mat A = randu<mat>(4, 5);
	// vec x = randu<vec>(5);
	// cout << testProduct(A, x) << endl;
	BTest();

	return 0;
}