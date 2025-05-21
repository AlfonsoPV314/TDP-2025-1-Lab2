#include "Graph.h"

Graph::Graph(int n) : V(n), INF(numeric_limits<double>::infinity()), M(n), E(0), T(n, false) {}

Graph::Graph(const vector<int> Vt, const vector<pair<pair<int, int>, double>>& Et, vector<bool> T) : V(Vt.size()), INF(numeric_limits<double>::infinity()), M(V), E(Et.size()), T(V, false) {
    for (int i = 0; i < Vt.size(); i++) {
        this->T[i] = T[i];
    }
    for (const auto& edge : Et) {
        addEdge(edge.first.first, edge.first.second, edge.second); // Peso por defecto de 1.0
    }
}

int Graph::getV() const {
    return V;
}

int Graph::getE() const {
    return E;
}

vector<bool> Graph::getT() const {
    return T;
}

vector<unordered_map<int, double>> Graph::getM() const {
    return M;
}

double Graph::getINF() const {
    return INF;
}

void Graph::addEdge(int u, int v, double w) {

    // Verificar si los vertices y el peso son validos
    if (u < 0 || u >= V || v < 0 || v >= V || w < 0) { 
        if(u < 0 || u >= V) {
            cout << "[Graph::addEdge] Error: Primer vertice " << u << " fuera de rango (V es: " << getV() << ")" << endl;
        }
        else if(v < 0 || v >= V) {
            cout << "[Graph::addEdge] Error: Segundo vertice " << v << " fuera de rango (V es: " << getV() << ")" << endl;
        }
        else{
            cout << "[Graph::addEdge] Error: Peso " << w << " fuera de rango (debe ser positivo)" << endl;
        }
        return;
    }
    M[u][v] = w;
    M[v][u] = w;
    E++;
}

double Graph::getEdge(int u, int v) const {

    // Verificar si los vertices son validos
    if (u < 0 || u >= V || v < 0 || v >= V) {
        if(u < 0 || u >= V) {
            cout << "[Graph::getEdge] Error: Primer vertice " << u << " fuera de rango (V es: " << getV() << ")" << endl;
        }
        else {
            cout << "[Graph::getEdge] Error: Segundo vertice " << v << " fuera de rango (V es: " << getV() << ")" << endl;
        }
        return INF;
    }
    auto it = M[u].find(v); // Buscar el vertice v en la lista de adyacencia del vertice u
    return (it != M[u].end()) ? it->second : INF;   // Si no existe la arista, devolver INF. Si existe, devolver el peso
}

void Graph::setTerm(int t) {
    if (t < 0 || t >= V) {
        cout << "[Graph::addTerm] Error: Vertice " << t << " fuera de rango (V es: " << getV() << ")" << endl;
        return;
    }
    T[t] = true;
}

Graph* Graph::cloneGraph() const {
    Graph* clone = new Graph(V);
    clone->M = M;
    clone->E = E;
    clone->T = T;
    clone->INF = INF;
    return clone;
}

pair<vector<pair<pair<int, int>, double>>, double> Graph::dijkstra(int u, int v) const {
    vector<pair<pair<int, int>, double>> path;
    vector<double> dist(V, INF);
    vector<int> prev(V, -1);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    double totalWeight = 0;

    dist[u] = 0;
    pq.push({0, u});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if (d > dist[node]) continue;

        for (const auto& [neighbor, weight] : M[node]) {
            if (dist[node] + weight < dist[neighbor]) {
                dist[neighbor] = dist[node] + weight;
                prev[neighbor] = node;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    for (int at = v; at != -1; at = prev[at]) {
        if (prev[at] != -1) {
            path.push_back({{at, prev[at]}, getEdge(at, prev[at])});
            totalWeight += getEdge(at, prev[at]);
        }
    }
    reverse(path.begin(), path.end());
    return {path, totalWeight};
}

// Función para imprimir el camino obtenido por Dijkstra
void Graph::printDijkstra(const vector<pair<pair<int, int>, double>>& path) {
    cout << "[Graph::printDijkstra] Camino más corto:" << endl;
    for (const auto& [edge, weight] : path) {
        int node = edge.first;
        int prev = edge.second;
        if(prev != -1 && weight != INF && weight != -1) {
            cout << "(" << node << ", " << prev << ", " << weight << ")" << endl;
        }
    }
    cout << endl;
}

pair<vector<pair<pair<int, int>, double>>, double> Graph::MSTPrim(int origin) const {
    vector<pair<pair<int, int>, double>> mstEdges;
    vector<double> dist(V, INF);
    vector<int> prev(V, -1);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    double totalWeight = 0;

    dist[origin] = 0;
    pq.push({0, origin});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if (d > dist[node]) continue;

        for (const auto& [neighbor, weight] : M[node]) {
            if (weight < dist[neighbor]) {
                dist[neighbor] = weight;
                prev[neighbor] = node;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        if (prev[i] != -1) {
            mstEdges.push_back({{i, prev[i]}, getEdge(i, prev[i])});
            totalWeight += getEdge(i, prev[i]);
        }
    }

    return {mstEdges, totalWeight};
}

void Graph::printMST(const pair<vector<pair<pair<int, int>, double>>, double>& mstEdges) const {
    cout << "[Graph::printMST] Arbol de expansión mínima:" << endl;
    for (const auto& [u, v] : mstEdges.first) {
        cout << "(" << u.first << ", " << u.second << ", " << v << ")" << endl;
    }
    cout << "Peso total del MST: " << mstEdges.second << endl;
}

bool Graph::isCyclic() const {
    vector<bool> visited(V, false);
    for (int i = 0; i < V; ++i) {
        if (!visited[i] && isCyclicUtil(i, visited, -1)) {
            return true;
        }
    }
    return false;
}

bool Graph::isCyclicUtil(int v, vector<bool>& visited, int parent) const {
    visited[v] = true;
    for (const auto& [neighbor, _] : M[v]) {
        if (!visited[neighbor]) {
            if (isCyclicUtil(neighbor, visited, v)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;
        }
    }
    return false;
}

void Graph::printGraph() const {
    cout << "[Graph::printGraph] Imprimiendo grafo..." << endl;
    cout << "Numero de vertices: " << V << endl;
    cout << "Numero de aristas: " << E << endl;
    cout << "Vertices terminales: ";
    for (int i = 0; i < V; i++) {
        if (T[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "Lista de adyacencia: " << endl;
    for (int u = 0; u < V; u++) {
        cout << u << ": ";
        for (const auto& [v, w] : M[u]) {
            cout << "(" << v << ", " << w << ") ";
        }
        cout << endl;
    }
    cout << endl;
}

bool Graph::operator==(const Graph& other) const {
    return (V == other.V && E == other.E && M == other.M);
}