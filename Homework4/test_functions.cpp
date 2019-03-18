#include <iostream>
#include <vector>

#include "CSR_matrix.hpp"
#include "test_functions.hpp"

using namespace std;
using namespace arma;

bool testProduct(mat A, vec x){
	vec full_B = A*x;
	for(int i = 0; i < 5; i++){
		cout << full_B[i] << endl;
	}
	return true;
}