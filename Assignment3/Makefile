all: main

main: main.cpp
	g++ -std=c++11 -o main *.cpp

plot: plot.cpp
	g++ plot.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7

clean:
	rm -f main
	rm -f *.o