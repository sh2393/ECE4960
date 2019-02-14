//common sparse matrix utility functions
#include <iostrea>

class matrix{
	int n_rows;
	int n_cols;
	int mat[n_rows][n_cols];

	void matrix(int in_rows, int in_cols){
		n_rows = in_rows;
		n_cols = in_cols;
	}
};

int retrieveElement(matrix A, int rowPtr, int colInd){
	return A[rowPtr][colInd];
}

int main(){
	int matrix[5][5] = {{1, 2, 0, 0, 3}, {4, 5, 6, 0, 0}, {0, 7, 8, 0, 9}, {0, 0, 0, 10, 0}, {11, 0, 0, 0, 12}};
	
	return 0;
}