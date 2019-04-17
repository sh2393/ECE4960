#ifndef FULLMATRIX_HPP
#define FULLMATRIX_HPP

#include <vector>
using namespace std;

class fullMatrix{
public:
	vector<vector<double>> val;
	int dimension;

	fullMatrix(vector<vector<double>> val_in){
		val = val_in;
		dimension = val_in.size();
	}

	double compute_determinant();

	int compute_inverse(vector<vector<double>> &Inverse);

};

#endif
