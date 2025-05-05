all: testGraph testUserInput

UserInput.o: UserInput.cpp UserInput.h
	g++ -g -c UserInput.cpp

Graph.o: Graph.cpp Graph.h
	g++ -g -c Graph.cpp

testUserInput: Graph.o UserInput.o testUserInput.cpp
	g++ -g Graph.o UserInput.o testUserInput.cpp -o testUserInput

testGraph: Graph.o testGraph.cpp
	g++ -g Graph.o testGraph.cpp -o testGraph

clean:
	rm -rf *.o testGraph testUserInput