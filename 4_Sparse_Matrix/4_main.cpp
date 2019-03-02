#include <iostream>
#include "4_1_CSR_matrix.h"

using namespace std;

int main(){
	

	vector<int> val{1,2,3,4,5,6,7,8,9,10,11,12};
	vector<int> row{0,3,6,9,10,12};
	vector<int> col{0,1,4,0,1,2,1,2,4,3,0,4};

	Matrix matrix(val, row, col);

    cout << matrix.retrieveElement(2, 1) << endl;
    return 0;
}