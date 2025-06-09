#ifndef GRAPH_H
#define GRAPH_H

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

class Graph {
private:
    int V; // Numero de vertices
    int E; // Numero de edges
    int Tn; // Numero de nodos terminales
    double INF; // Infinito
    vector<unordered_map<int, double>> M; // Lista de adyacencia (antes era una matriz, por eso es M)
    vector<bool> T; // Vector de nodos terminales (true si es terminal, false si no lo es)

public:
    // Constructor
    Graph(int n);

    // Constructor con vertices y aristas
    Graph(const vector<int> Vt, const vector<pair<pair<int, int>, double>>& Et, vector<bool> T);

    // Constructor con numero de vertices, aristas y nodos terminales
    Graph(const int V, const vector<pair<pair<int, int>, double>>& Et, vector<bool> T);

    // Obtener el numero de vertices
    int getV() const;
    
    // Obtener el numero de aristas
    int getE() const;

    // Obtener el numero de nodos terminales
    int getTn() const;

    // Obtener el vector de nodos terminales
    vector<bool> getT() const;

    // Obtener la lista de adyacencia
    vector<unordered_map<int, double>> getM() const;

    // Obtener el valor de INF
    double getINF() const;
    
    // Agregar arista
    void addEdge(int u, int v, double w);

    // Obtener el peso de una arista
    double getEdge(int u, int v) const;

    // Eliminar arista
    void removeEdge(int u, int v);

    // Establecer un nodo como terminal
    void setTerm(int t);

    // Clonar el grafo
    Graph* cloneGraph() const;

    // Algoritmo de Dijkstra para encontrar el camino más corto entre dos nodos
    pair<vector<pair<pair<int, int>, double>>, double> dijkstra(int u, int v) const;

    // Imprimir el camino obtenido por Dijkstra
    void printDijkstra(const vector<pair<pair<int, int>, double>>& path);

    // Algoritmo de Prim para encontrar el árbol de expansión mínima (MST)
    pair<vector<pair<pair<int, int>, double>>, double> MSTPrim(int origin) const;

    // Imprimir el árbol de expansión mínima
    void printMST(const pair<vector<pair<pair<int, int>, double>>, double>& mstEdges) const;

    // Verificar si el grafo es cíclico (obtiene las aristas cíclicas en caso de serlo)
    pair<bool, vector<pair<int, int>>> getCyclic() const;

    // Obtener el árbol de expansión mínima (MST) del grafo
    pair<bool, vector<pair<int, int>>> getNonTermLeaves() const;

    // Imprimir grafo
    void printGraph() const;

    // Operador de igualdad (compara si dos grafos son iguales)
    bool operator==(const Graph& other) const;
};

#endif