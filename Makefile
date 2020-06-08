a.out: DisjSet.o MinCutter.o main.o
	g++ -std=c++2a -O3 DisjSet.o MinCutter.o main.o

main.o: main.cpp MinCutter.o DisjSet.o
	g++ -std=c++2a -O3 -c main.cpp

MinCutter.o : MinCutter.h MinCutter.cpp DisjSet.o
	g++ -std=c++2a -O3 -c MinCutter.cpp

DisjSet.o : DisjSet.cpp DisjSet.h
	g++ -std=c++2a -O3 -c DisjSet.cpp

clean:
	rm *.o
	rm mc.out
