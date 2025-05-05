#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <algorithm>
#include <queue>
using namespace std;

class Graph {
    private:
        int V; // Numero de vertices
        int E; // Numero de edges
        double INF; // Infinito
        vector<unordered_map<int, double>> M; // Lista de adyacencia
        vector<bool> T;
    public:
        // Constructor
        Graph(int n);

        // Obtener el numero de vertices
        int getV() const;
        
        // Obtener el numero de aristas
        int getE() const;

        vector<bool> getT() const;

        vector<unordered_map<int, double>> getM() const;

        double getINF() const;
        
        // Agregar arista
        void addEdge(int u, int v, double w);

        double getEdge(int u, int v);

        void setTerm(int t);

        Graph* cloneGraph() const;

        vector<pair<int, int>> dijkstra(int u, int v) const;

        void printDijkstra(const vector<pair<int, int>>& path);

        vector<pair<int, int>> solveTM() const;

        void printTM(const vector<pair<int, int>>& Te) const;

        vector<pair<int, int>> solveKMB() const;

        // Imprimir grafo
        void printGraph() const;

        bool operator==(const Graph& other) const;
};