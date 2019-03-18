all: full

main: main.cpp
	g++ -std=c++11 -o main *.cpp 

full: main.cpp
	g++ -std=c++11 -o main *.cpp -larmadillo

clean:
	rm -f main
	rm -f *.o