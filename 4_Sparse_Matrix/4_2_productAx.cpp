#include <armadillo>
#include "CSR_matrix.h"
using namespace std;
using namespace arma;

int main(){
	//initialization
	vector<double> val{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	vector<int> row{0, 3, 6, 9, 10, 12};
	vector<int> col{0, 1, 4, 0, 1, 2, 1, 2, 4, 3, 0, 4};
	Matrix A(val, row, col);

	//CSR matrix operations and initialization
	vector<double> b;
	vector<double> x{5, 4, 3, 2, 1};

	A.productAx(x, &b);

	//std output for checking result
	cout << "CSR product result" << endl;
	for(int i = 0; i < b.size(); i++){
		cout << b[i] << " ";
	}
	cout << endl;


	//full matrix operations and initialization
	mat A_full = {{1, 2, 0, 0, 3}, {4, 5, 6, 0, 0}, {0, 7, 8, 0, 9}, {0, 0, 0, 10, 0}, {11, 0, 0, 0, 12}};
	colvec x_full = {5, 4, 3, 2, 1};
	colvec b_full = A_full*x_full;

	cout << "full matrix multiplication" << endl;
	cout << b_full << endl;

	//test util
	int fail_flag = 0;
	for(int i = 0; i < b.size(); i++){
		if (b[i] != b_full[i]){
			printf("equivalence check failed at i = %d, (CSR = %2.2f, full = %2.2f)\n", i, b[i], b_full[i]); 
			fail_flag = 1;
		}
	}
	if(fail_flag == 0){
		cout << "PASS: productAx" << endl;
	}

	return 0;
}