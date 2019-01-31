#include <iostream>

using namespace std;


int factorial(int a){
	if(a == 0) return 1;
	return a*factorial(a-1);
}

int comb(int n, int k){
	if(n < k){
		cout << " n has to be greater than k";
		return 0;
	}
	return factorial(n) / (factorial(k) * factorial(n-k));
}

int main(){
	cout << comb(8, 3) << endl;
	return 0;
}

/*modular programming for factorial issues:
smaller range of applicability
redundant computation (combinatorics can be simplified first)
*/
