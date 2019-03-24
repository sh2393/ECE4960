/*
Joyce Huang
Use the full matrix format and row permutation to perform the minimal fill-in algorithm for choosing the sequence of pivoting.
Use backward substitution to check answer.
TODO: compare memory usage and computation stats
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void printFullMatrix(vector<vector<double>> &A){
	for(int i = 0; i < A.size(); i++){
		for(int j = 0; j < A[0].size(); j++){
			printf("%4.2f ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void swapRow(vector<vector<double>> &A, int i, int j){
	vector<double> itemp = A[i];
	vector<double> jtemp = A[j];
	A.erase(A.begin() + i);
	A.insert(A.begin()+i, jtemp);
	A.erase(A.begin()+j);
	A.insert(A.begin()+j, itemp);
}

//use brute force to check the min number of fill-in
//bring the pivot row to the top before return
//input: matrix
//output: pivot row index
void minFillPivot(vector<vector<double>> &A, int pi){
	int i = pi;
	int min_count = A[0].size(); //initialize to rank

	for(int r = pi; r < A.size(); r++){
		//if the row has a pivot on the coloumn we're looking at
		if(A[r][pi] != 0){
			int nz_count = 0;
			for(int c = pi; c < A[r].size(); c++){
				if(A[r][c] != 0){
					nz_count++;
				}
			}
			if(nz_count < min_count){
				min_count = nz_count;
				i = r;
			}
		}
	}
	swapRow(A, i, pi);
}

// Add a*row[i] to row[j] for matrix A 
int rowScale(vector<vector<double>> &A, int i, int j, double a){
	if(i >= A.size() || j >= A.size()){
		printf("row indices out of bouund\n");
		return 1;
	}

	for(int k = 0; k < A[i].size(); k++){
		A[j][k] += a*A[i][k];
	}

	return 0;
}	

void luDecomposition(vector<vector<double>> &A, vector<vector<double>> &L, vector<vector<double>> &U){
	for(int d = 0; d < A.size(); d++){  //walk through diagonal
		for(int r = d+1; r < A.size(); r++){
			double a = -A[r][d] / A[d][d];
			rowScale(A, d, r, a);
			L[r][d] = a;
		}
		U.push_back(A[d]);
	}
}

int main(){
	vector<vector<double>> A{{1, 2, 0, 0, 3}, {4, 5, 6, 0, 0}, {0, 7, 8, 0, 9}, {0, 0, 0, 10, 0}, {11, 0, 0, 0, 12}};
	vector<double> b = {5, 4, 3, 2, 1};

	for(int i = 0; i < A.size(); i++)minFillPivot(A, i);
	printFullMatrix(A);  //after swapping rows to have minimal fill in structure
	
	vector<vector<double>> L(5, vector<double>(5)), U;

	//initalize diagonal for L matrix
	for(int i = 0; i < L.size(); i++) L[i][i] = 1;

	//perform LU decomposition
	luDecomposition(A, L, U);
	printFullMatrix(L);
	printFullMatrix(U);

	//back substitution for checking answer
	
	return 0;
}