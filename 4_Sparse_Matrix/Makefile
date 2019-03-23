all: main

main: main.cpp
	g++ -std=c++11 -o main main.cpp CSR_matrix.cpp

one: 4_1_retrieveElement.cpp
	g++ -std=c++11 -o 4_1_retrieveElement 4_1_retrieveElement.cpp CSR_matrix.cpp

two: 4_2_productAx.cpp
	g++ -std=c++11 -o 4_2_productAx 4_2_productAx.cpp CSR_matrix.cpp -larmadillo

three: 4_3_solver.cpp
	g++ -std=c++11 -o 4_3_solver 4_3_solver.cpp -larmadillo


