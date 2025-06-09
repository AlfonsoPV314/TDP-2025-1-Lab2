#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <algorithm>
#include <queue>
#include <functional>
#include <set>
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

class Graph {
private:
    int V; // Numero de vertices
    int E; // Numero de edges
    int Tn; // Numero de nodos terminales
    double INF; // Infinito
    vector<unordered_map<int, double>> M; // Lista de adyacencia
    vector<bool> T;

public:
    // Constructor
    Graph(int n);

    Graph(const vector<int> Vt, const vector<pair<pair<int, int>, double>>& Et, vector<bool> T);

    Graph(const int V, const vector<pair<pair<int, int>, double>>& Et, vector<bool> T);

    // Obtener el numero de vertices
    int getV() const;
    
    // Obtener el numero de aristas
    int getE() const;

    // Obtener el numero de nodos terminales
    int getTn() const;

    vector<bool> getT() const;

    vector<unordered_map<int, double>> getM() const;

    double getINF() const;
    
    // Agregar arista
    void addEdge(int u, int v, double w);

    double getEdge(int u, int v) const;

    void removeEdge(int u, int v);

    void setTerm(int t);

    Graph* cloneGraph() const;

    pair<vector<pair<pair<int, int>, double>>, double> dijkstra(int u, int v) const;

    void printDijkstra(const vector<pair<pair<int, int>, double>>& path);

    pair<vector<pair<pair<int, int>, double>>, double> MSTPrim(int origin) const;

    void printMST(const pair<vector<pair<pair<int, int>, double>>, double>& mstEdges) const;

    // bool isCyclic() const;

    // bool isCyclicUtil(int v, vector<bool>& visited, int parent) const;

    pair<bool, vector<pair<int, int>>> getCyclic() const;

    pair<bool, vector<pair<int, int>>> getNonTermLeaves() const;

    // Imprimir grafo
    void printGraph() const;

    bool operator==(const Graph& other) const;
};

#endif