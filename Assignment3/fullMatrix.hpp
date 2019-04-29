/*H**********************************************************************
* FILENAME :        fullMatrix.hpp
*
* DESCRIPTION :
*		Description the full matrix object.
*       Expose the full matrix information to public. 
*
* AUTHOR :    Joyce Huang (sh2393:Cornell University)        START DATE :    5 Apr 2019
*
* UPDATE :   28 Apr 2019
*
*H*/

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
