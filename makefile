all: testGraph testTakahashi

UserInput.o: UserInput.cpp UserInput.h
	g++ -g -c UserInput.cpp

Graph.o: Graph.cpp Graph.h
	g++ -g -c Graph.cpp

Strategy.o: Strategy.cpp Strategy.h
	g++ -g -c Strategy.cpp

Takahashi.o: Takahashi.cpp Takahashi.h
	g++ -g -c Takahashi.cpp

testUserInput: Graph.o UserInput.o testUserInput.cpp
	g++ -g Graph.o UserInput.o testUserInput.cpp -o testUserInput

testGraph: Graph.o testGraph.cpp
	g++ -g Graph.o testGraph.cpp -o testGraph

testTakahashi: Graph.o Strategy.o Takahashi.o testTakahashi.cpp
	g++ -g Graph.o Strategy.o Takahashi.o testTakahashi.cpp -o testTakahashi

clean:
	rm -rf *.o testGraph testTakahashi