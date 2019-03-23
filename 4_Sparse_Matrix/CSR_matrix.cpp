//Linear Algebra and Sparse Matrices

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include "CSR_matrix.h"

//TODO: add and delete has to change row pointers 
//TODO: check exceptions
//TODO: figure out rowScale when i > j

using namespace std;

//initialize emptry martix
Matrix::Matrix(){
	value = {};
	rowPtr = {0};
	colInd = {};
	rank = 0;
}

//initialize matrix with a given
Matrix::Matrix(vector<double> val, vector<int> row, vector<int> col){
	value = val;
	rowPtr = row;
	colInd = col;
	rank = *max_element(colInd.begin(), colInd.end())+1;
}

void Matrix::addElement(int ri, int ci, double val){
	//inserting one element at row i so every i+1 row pointer has to plus 1
	for(int i = ri+1; i < rowPtr.size(); i++) rowPtr[i]++;

	int start = rowPtr[ri];
	int end = rowPtr[ri+1]; 

	for(int i = start; i < end; i++){
		if (ci < colInd[i]){
			colInd.insert(colInd.begin() + i, ci);
			value.insert(value.begin() + i, val);
			break;
		}
	}

	//rank = *max_element(colInd.begin(), colInd.end())+1;
}


void Matrix::deleteElement(int ri, int ci){
	int start = rowPtr[ri];
	int end = rowPtr[ri+1];

	for(int i = start; i < end; i++){
		if (ci == colInd[i]){
			value.erase(value.begin() + i, value.begin()+(i+1));
			colInd.erase(colInd.begin() + i, colInd.begin()+(i+1));
			break;
		}
	}

	for(int i = ri+1; i < rowPtr.size(); i++) rowPtr[i]--;
	//rank = *max_element(colInd.begin(), colInd.end())+1;	
}

double Matrix::retrieveElement(int ri, int ci){
	int start = rowPtr[ri];
	int end = rowPtr[ri+1];

	for(int i = start; i < end; i++){
		if (colInd[i] == ci){
			return value[i];
		}
	}

	return 0;
}

int Matrix::rankMatrix(){
	return rank;
}

int Matrix::countElementMatrix(){
	return colInd.size();
}

void Matrix::printMatrix(){
	int val_iter = 0;
	for(int i = 0; i < rowPtr.size()-1; i++){
		int col_iter = rowPtr[i];
		for(int j = 0; j < rank; j++){
			if (j == colInd[col_iter]){
				printf("%2.2f  ", value[val_iter]);
				//cout << value[val_iter] << " ";
				val_iter++;
				col_iter++;
			}else{
				printf("%2.2f  ", 0.0);
			}
		}
		cout << endl;
	}
	cout << endl;
}


//Swith i-th row and j-th row
/*
Implementation ideas: 
last element of rowptr would not change because size remain the same
switch colInd places and values places
recalculate rowptr based on col subvector size 
*/

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int Matrix::rowPermute(int i, int j){
	if (i > j) swap(&i, &j);

	int start1 = rowPtr[i];
	int end1 = rowPtr[i+1];
	int start2 = rowPtr[j];
	int end2 = rowPtr[j+1];

	//extrac col informations
	vector<int> row1_colInd;
	vector<int> row1_val;
	for (int row1_iter = start1; row1_iter < end1; row1_iter++){ //iterate through col
		row1_colInd.push_back(colInd[row1_iter]);
		row1_val.push_back(value[row1_iter]);
	}

	vector<int> row2_colInd;
	vector<int> row2_val;
	for (int row2_iter = start2; row2_iter < end2; row2_iter++){ //iterate through col
		row2_colInd.push_back(colInd[row2_iter]);
		row2_val.push_back(value[row2_iter]);
	}

	colInd.erase(colInd.begin() + start1, colInd.begin()+end1);
	value.erase(value.begin()   + start1, value.begin()+ end1);
	colInd.erase(colInd.begin() + start2 - (end1-start1), colInd.begin() + end2 - (end1-start1));
	value.erase(value.begin()   + start2 - (end1-start1), value.begin() + end2 - (end1-start1));


	//swtich rowptr
	int diff = rowPtr[i+1]- (rowPtr[i] + (end2-start2));
	for(int k = i+1; k <= j; k++) rowPtr[k] += diff;

	colInd.insert(colInd.begin()+rowPtr[i], row2_colInd.begin(), row2_colInd.end());
	colInd.insert(colInd.begin()+rowPtr[j], row1_colInd.begin(), row1_colInd.end());
	value.insert(value.begin()+rowPtr[i], row2_val.begin(), row2_val.end());
	value.insert(value.begin()+rowPtr[j], row1_val.begin(), row1_val.end());


	return SUCCESS;
}

// add the ith row multiplied by a constant a to the jth row
int Matrix::rowScale(int i, int j, double a){
	int start_i = rowPtr[i];
	int end_i = rowPtr[j+1];
	int start_j = rowPtr[j];
	int end_j = rowPtr[j+1];


	vector<int> row1_val;
	if(end_i-1-start_i == 0){
		row1_val.push_back(value[start_i]);
	}else if (end_i-1-start_i < 0){
		return 0;
	}else{
		vector<int> row1_val_copy(value.begin() + start_i, value.begin() + end_i-1);
		for(int k = 0; k < row1_val_copy.size(); k++){
			row1_val.push_back(row1_val_copy[k]);
		}
	}


	for(int k = 0; k < row1_val.size(); k++){
		row1_val[k] *= a;  //scale i by a
	}


	vector<int> row1_colInd(colInd.begin()+ start_i, colInd.begin() + end_i-1);


	//adding to j
	int i_iter = 0; //0, ro1_col_size()
	int j_iter = start_j; //start_j, end_j
	cout << i_iter << endl;
	cout << row1_colInd.size() << endl;
	for(int k = 0; k < row1_val.size(); k++){
		cout << row1_val[k] << " ";
	}
	cout << endl;
	cout << j_iter << endl;
	cout << end_j << endl;
	while(i_iter < row1_colInd.size() && j_iter < end_j){
		if (row1_colInd[i_iter] == colInd[j_iter]){
			cout << " case 1" << endl;
			value[j_iter] += row1_val[i_iter];
			j_iter++;
			i_iter++;
		}else if(row1_colInd[i_iter] < colInd[j_iter]){
			cout << " case 2" << endl;
			colInd.insert(colInd.begin() + j_iter, row1_colInd[i_iter]);
			value.insert(value.begin() + j_iter, row1_val[i_iter]);
			i_iter++;
			j_iter++;
			end_j++;
		}else if (row1_colInd[i_iter] > colInd[j_iter]){ 
			cout << " case 3" << endl;
			j_iter++;
		}else{
			cout << " case 4" << endl;
			i_iter++;
			j_iter++;
		}
	}

	int diff = end_j-rowPtr[j+1];
	for(int k = j+1; k < rowPtr.size(); k++){
		rowPtr[k] += diff;
	}

	return SUCCESS;
}

int Matrix::productAx(vector<double> x, vector<double> *result){    
    for (int i=0; i <rowPtr.size()-1; i++) {
    	int start= rowPtr[i];
        int end = rowPtr[i+1];
               
        double acc = 0;
        for (int j = start; j < end; j++) acc += (value[j] * x[colInd[j]]);
        result->push_back(acc);
    }
    return 0;
}

