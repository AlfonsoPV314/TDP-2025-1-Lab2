all: testGraph testTakahashi testKou main

UserInput.o: UserInput.cpp UserInput.h
	g++ -g -c UserInput.cpp

Graph.o: Graph.cpp Graph.h
	g++ -g -c Graph.cpp

STP.o: STP.cpp STP.h
	g++ -g -c STP.cpp

Takahashi.o: Takahashi.cpp Takahashi.h
	g++ -g -c Takahashi.cpp

Kou.o: Kou.cpp Kou.h
	g++ -g -c Kou.cpp

testUserInput: Graph.o UserInput.o testUserInput.cpp
	g++ -g Graph.o UserInput.o testUserInput.cpp -o testUserInput

testGraph: Graph.o testGraph.cpp
	g++ -g Graph.o testGraph.cpp -o testGraph

testTakahashi: Graph.o STP.o Takahashi.o testTakahashi.cpp
	g++ -g Graph.o STP.o Takahashi.o testTakahashi.cpp -o testTakahashi

testKou: Graph.o STP.o Kou.o testKou.cpp
	g++ -g Graph.o STP.o Kou.o testKou.cpp -o testKou

main: Graph.o STP.o Kou.o Takahashi.o UserInput.o main.cpp
	g++ -g Graph.o STP.o Kou.o Takahashi.o UserInput.o main.cpp -o main

clean:
	rm -rf *.o testGraph testKou testTakahashi main