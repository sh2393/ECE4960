#include <iostream>
#include <cstdlib>
#include "CSR_matrix.h"

using namespace std;

int main(){
	vector<double> val{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	vector<int> row{0, 3, 6, 9, 10, 12};
	vector<int> col{0, 1, 4, 0, 1, 2, 1, 2, 4, 3, 0, 4};
	Matrix m(val, row, col);

	printf("retriveElement printout\n");
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < m.rankMatrix(); j++){
			printf("i = %d, j = %d, value = %2.2f\n", i, j, m.retrieveElement(i, j));
		}
	}

	printf("Matrix printout\n");
	m.printMatrix();
	return 0;
}