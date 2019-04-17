#include <iostream>
#include <fstream>
#include <sstream>
#include "dmSolver.hpp"
#include "methods.hpp"
#include "paramExtraction.hpp"
using namespace std;

int task = 0;

//File input helper
void readFile() {
    ifstream inputFile("outputNMOS.txt");
    string line;

    inputFile >> line; //discard first line

    while (getline(inputFile, line)) {

        istringstream ss(line);
        double Vgs_val, Vds_val, Ids_val;
        ss >> Vgs_val >> Vds_val >> Ids_val;
        Vgs.push_back(Vgs_val);
        Vds.push_back(Vds_val);
        Ids.push_back(Ids_val);

    }
}

int main(){
	//test 
	verifySolver();
	validate();
    
    printf("Load file input form outputNMOS.txt\n");
    readFile();
    
    task = 4;
    printf("\n\n======================\nTask4 : Quasi-Newton method\n======================\n");
    QuasiNewton();

    task = 5;
    printf("\n\n======================\nTask5 : Quasi-Newton method\n======================\n");
    QuasiNewton();

    // search for the opt parameters
    task = 6;
    printf("\n\n======================\nTask6: fullGriddedSearch()\n======================\n");
    fullGriddedSearch();
    printf("\n");

	return 0;
}