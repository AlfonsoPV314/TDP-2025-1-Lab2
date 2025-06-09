#include "Graph.h"

/*
    * Constructor de la clase Graph.
    * Inicializa el grafo vacío con un numero de nodos n.
    * Parametros: 
    * - n: Numero de nodos del grafo.
    * Retorno: 
    * - void
*/
Graph::Graph(int n) : V(n), INF(numeric_limits<double>::infinity()), M(n), E(0), Tn(0), T(n, false) {}

/*
    * Constructor de la clase Graph.
    * Inicializa el grafo con un vector de nodos y un vector de aristas.
    * Parametros: 
    * - Vt: Vector de nodos conectados en el grafo.
    * - Et: Vector de aristas, cada arista es un par (u, v) con su peso asociado.
    * - T: Vector que indica si un nodo es terminal (true) o no (false).
    * Retorno: 
    * - void
*/
Graph::Graph(const vector<int> Vt, const vector<pair<pair<int, int>, double>>& Et, vector<bool> T) : V(T.size()), INF(numeric_limits<double>::infinity()), M(V), E(0), Tn(0), T(V, false) {
    for (int i = 0; i < V; i++) {
        this->T[i] = T[i];
        if(T[i]) {
            Tn++;  // Contar el numero de nodos terminales
        }
    }
    for (const auto& edge : Et) {
        addEdge(edge.first.first, edge.first.second, edge.second);
    }
    //cout << "[Graph::Graph] Creando grafo con " << Vt.size() << " nodos y " << Et.size() << " aristas." << endl;
}

/*
    * Constructor de la clase Graph.
    * Inicializa el grafo con un numero de nodos, un vector de aristas y un vector de nodos terminales.
    * Parametros: 
    * - V: Numero de nodos del grafo.
    * - Et: Vector de aristas, cada arista es un par (u, v) con su peso asociado.
    * - T: Vector que indica si un nodo es terminal (true) o no (false).
    * Retorno: 
    * - void
*/
Graph::Graph(const int V, const vector<pair<pair<int, int>, double>>& Et, vector<bool> T) : V(V), INF(numeric_limits<double>::infinity()), M(V), E(0), Tn(0), T(T) {
    for (int i = 0; i < V; i++) {
        if(T[i]) {
            Tn++;  // Contar el numero de nodos terminales
        }
    }
    for (const auto& edge : Et) {
        addEdge(edge.first.first, edge.first.second, edge.second);
    }
    //cout << "[Graph::Graph] Creando grafo con " << V << " nodos y " << Et.size() << " aristas." << endl;
}

/*
    * Metodo getV: Obtiene el numero de nodos del grafo.
    * Retorno: 
    * - int: Numero de nodos del grafo.
*/
int Graph::getV() const {
    return V;
}

/*
    * Metodo getE: Obtiene el numero de aristas del grafo.
    * Retorno: 
    * - int: Numero de aristas del grafo.
*/
int Graph::getE() const {
    return E;
}

/*
    * Metodo getTn: Obtiene el numero de nodos terminales del grafo.
    * Retorno: 
    * - int: Numero de nodos terminales del grafo.
*/
int Graph::getTn() const {
    return Tn;
}

/*
    * Metodo getT: Obtiene el vector de nodos terminales del grafo.
    * Retorno: 
    * - vector<bool>: Vector que indica si un nodo es terminal (true) o no (false).
*/
vector<bool> Graph::getT() const {
    return T;
}

/*
    * Metodo getM: Obtiene la lista de adyacencia del grafo.
    * Retorno: 
    * - vector<unordered_map<int, double>>: Lista de adyacencia del grafo, donde cada nodo tiene un mapa de nodos adyacentes y sus pesos.
*/
vector<unordered_map<int, double>> Graph::getM() const {
    return M;
}

/*
    * Metodo getINF: Obtiene el valor de infinito utilizado en el grafo.
    * Retorno: 
    * - double: Valor de infinito utilizado en el grafo.
*/
double Graph::getINF() const {
    return INF;
}

/*
    * Metodo addEdge: Agrega una arista al grafo.
    * Parametros: 
    * - u: Primer nodo de la arista.
    * - v: Segundo nodo de la arista.
    * - w: Peso de la arista.
    * Retorno: 
    * - void
*/
void Graph::addEdge(int u, int v, double w) {

    // Verificar si los vertices y el peso son validos
    if (u < 0 || u >= V || v < 0 || v >= V || w < 0) { 
        // if(u < 0 || u >= V) {
        //     cout << "[Graph::addEdge] Error: Primer vertice " << u << " fuera de rango (V es: " << getV() << ")" << endl;
        // }
        // else if(v < 0 || v >= V) {
        //     cout << "[Graph::addEdge] Error: Segundo vertice " << v << " fuera de rango (V es: " << getV() << ")" << endl;
        // }
        // else{
        //     cout << "[Graph::addEdge] Error: Peso " << w << " fuera de rango (debe ser positivo)" << endl;
        // }
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
            //cout << "[Graph::getEdge] Error: Primer vertice " << u << " fuera de rango (V es: " << getV() << ")" << endl;
        }
        else {
            //cout << "[Graph::getEdge] Error: Segundo vertice " << v << " fuera de rango (V es: " << getV() << ")" << endl;
        }
        return INF;
    }
    auto it = M[u].find(v); // Buscar el vertice v en la lista de adyacencia del vertice u
    return (it != M[u].end()) ? it->second : INF;   // Si no existe la arista, devolver INF. Si existe, devolver el peso
}

/*
    * Metodo removeEdge: Elimina una arista del grafo.
    * Parametros: 
    * - u: Primer nodo de la arista.
    * - v: Segundo nodo de la arista.
    * Retorno: 
    * - void
*/
void Graph::removeEdge(int u, int v) {

    // Verificar si los vertices son validos
    if (u < 0 || u >= V || v < 0 || v >= V) {
        if(u < 0 || u >= V) {
            //cout << "[Graph::removeEdge] Error: Primer vertice " << u << " fuera de rango (V es: " << getV() << ")" << endl;
        }
        else {
            //cout << "[Graph::removeEdge] Error: Segundo vertice " << v << " fuera de rango (V es: " << getV() << ")" << endl;
        }
        return;
    }
    M[u].erase(v);
    M[v].erase(u);
    E--;
}

/*
    * Metodo setTerm: Establece un nodo como terminal.
    * Parametros: 
    * - t: Nodo a establecer como terminal.
    * Retorno: 
    * - void
*/
void Graph::setTerm(int t) {
    if (t < 0 || t >= V) {
        //cout << "[Graph::addTerm] Error: Vertice " << t << " fuera de rango (V es: " << getV() << ")" << endl;
        return;
    }
    T[t] = true;
    Tn++;
}

/*
    * Metodo cloneGraph: Clona el grafo actual.
    * Retorno: 
    * - Graph*: Puntero al nuevo grafo clonado.
*/
Graph* Graph::cloneGraph() const {
    Graph* clone = new Graph(V);
    clone->M = M;
    clone->E = E;
    clone->T = T;
    clone->INF = INF;
    clone->Tn = Tn;
    return clone;
}

/*
    * Metodo dijkstra: Implementa el algoritmo de Dijkstra para encontrar el camino más corto entre dos nodos.
    * Parametros: 
    * - u: Nodo de inicio.
    * - v: Nodo de destino.
    * Retorno: 
    * - pair<vector<pair<pair<int, int>, double>>, double>: Un par que contiene un vector de pares (arista, peso) y el peso total del camino.
*/
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
        //cout << "[Graph::dijkstra] Visitando nodo: " << at << " con distancia: " << dist[at] << " y previo: " << prev[at] << endl;
        if (prev[at] != -1) {
            path.push_back({{at, prev[at]}, getEdge(at, prev[at])});
            totalWeight += getEdge(at, prev[at]);
            //cout << "[Graph::dijkstra] Agregando arista (" << at << ", " << prev[at] << ") con peso " << getEdge(at, prev[at]) << endl;
        }
    }
    //cout << "[Graph::dijkstra] Inputs: u es " << u << " y v es " << v << endl;
    reverse(path.begin(), path.end());
    return {path, totalWeight};
}

/*
    * Metodo printDijkstra: Imprime el camino obtenido por Dijkstra.
    * Parametros:
    * - path: Vector de pares (arista, peso) que representa el camino más corto.
    * Retorno:
    * - void
*/
void Graph::printDijkstra(const vector<pair<pair<int, int>, double>>& path) {
    cout << "Camino más corto de Dijkstra:" << endl;
    for (const auto& [edge, weight] : path) {
        int node = edge.first;
        int prev = edge.second;
        if(prev != -1 && weight != INF && weight != -1) {
            cout << "(" << node + 1 << ", " << prev + 1 << ", " << weight << ")" << endl;
        }
    }
    cout << endl;
}

/*
    * Metodo MSTPrim: Implementa el algoritmo de Prim para encontrar el árbol de expansión mínima (MST) a partir de un nodo origen.
    * Parametros: 
    * - origin: Nodo de inicio para el algoritmo de Prim.
    * Retorno: 
    * - pair<vector<pair<pair<int, int>, double>>, double>: Un par que contiene un vector de pares (arista, peso) y el peso total del MST.
*/
pair<vector<pair<pair<int, int>, double>>, double> Graph::MSTPrim(int origin) const {
    if (origin < 0 || origin >= V) {
        //cout << "[Graph::MSTPrim] Error: El nodo de origen " << origin << " está fuera de rango (V es: " << getV() << ")" << endl;
        return {{}, -1};
    }

    vector<pair<pair<int, int>, double>> mstEdges;
    vector<double> dist(V, INF);
    vector<int> prev(V, -1);
    vector<bool> visited(V, false);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    double totalWeight = 0;

    dist[origin] = 0;
    pq.push({0, origin});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if (visited[node]) continue; // Salta nodos ya visitados

        visited[node] = true;

        for (const auto& [neighbor, weight] : M[node]) {
            if (!visited[neighbor] && weight < dist[neighbor]) {
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

    // Verifica si hay nodos desconectados
    // for (int i = 0; i < V; ++i) {
    //     if (!visited[i]) {
    //         cout << "[Graph::MSTPrim] Advertencia: El nodo " << i << " no es alcanzable desde el origen." << endl;
    //     }
    // }

    return {mstEdges, totalWeight};
}


/*
    * Metodo printMST: Imprime el árbol de expansión mínima obtenido por Prim.
    * Parametros: 
    * - mstEdges: Un par que contiene un vector de pares (arista, peso) y el peso total del MST.
    * Retorno: 
    * - void
*/
void Graph::printMST(const pair<vector<pair<pair<int, int>, double>>, double>& mstEdges) const {
    cout << "Arbol de expansión mínima de Prim:" << endl;
    for (const auto& [uv, w] : mstEdges.first) {
        cout << "(" << uv.first + 1 << ", " << uv.second + 1 << ", " << w << ")" << endl;
    }
    cout << "Peso total del MST: " << mstEdges.second << endl << endl;
}

/*
    * Metodo getCyclic: Verifica si el grafo es cíclico y obtiene las aristas cíclicas.
    * Retorno: 
    * - pair<bool, vector<pair<int, int>>>: Un par que indica si hay ciclos (true/false) y un vector de pares (aristas: vertice, vertice) que representa las aristas cíclicas.
*/
pair<bool, vector<pair<int, int>>> Graph::getCyclic() const {
    vector<bool> visited(V, false);
    vector<pair<int, int>> cyclicEdges; // Almacena aristas cíclicas
    set<pair<int, int>> cyclicSet;

    // Función auxiliar DFS para detectar ciclos
    function<bool(int, int)> detectCycle = [&](int node, int parent) -> bool {
        visited[node] = true;
        bool isCyclic = false;

        for (const auto& [neighbor, _] : M[node]) {

            // si el vecino no ha sido visitado
            if (!visited[neighbor]) {
                if (detectCycle(neighbor, node)) {
                    cyclicSet.insert({min(node, neighbor), max(node, neighbor)}); // Insertar arista (pertenece a un ciclo)
                    isCyclic = true;
                }
            } 
            
              // si el vecino ya ha sido visitado y no es el padre del nodo actual (se llegó por otro camino anteriormente)
            else if (neighbor != parent) {
                cyclicSet.insert({min(node, neighbor), max(node, neighbor)}); // Insertar arista (pertenece a un ciclo)
                isCyclic = true;
            }
        }
        return isCyclic;
    };

    // Ejecutar DFS en cada componente conectada
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            detectCycle(i, -1);
        }
    }

    // Copiar aristas del conjunto al vector
    cyclicEdges.assign(cyclicSet.begin(), cyclicSet.end());

    return {!cyclicEdges.empty(), cyclicEdges};
}

/*
    * Metodo getNonTermLeaves: Obtiene las hojas no terminales del grafo.
    * Retorno: 
    * - pair<bool, vector<pair<int, int>>>: Un par que indica si hay hojas no terminales (true/false) y un vector de pares (hoja, vecino) que representa las hojas no terminales.
*/
pair<bool, vector<pair<int, int>>> Graph::getNonTermLeaves() const {
    vector<pair<int, int>> nonTermLeaves;
    for (int i = 0; i < V; ++i) {
        if (!T[i] && M[i].size() == 1) { // Si el nodo no es terminal y tiene un solo vecino
            for (const auto& [neighbor, _] : M[i]) {
                nonTermLeaves.push_back({i, neighbor});
            }
        }
    }
    return {!nonTermLeaves.empty(), nonTermLeaves};
}

/*
    * Metodo printGraph: Imprime el grafo.
    * Retorno: 
    * - void
*/
void Graph::printGraph() const {
    cout << "Imprimiendo grafo (indices desde 1)..." << endl;
    cout << "Numero de vertices: " << V << endl;
    cout << "Numero de aristas: " << E << endl;
    cout << "Con " << Tn << " vertices terminales: ";
    for (int i = 0; i < V; i++) {
        if (T[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
    cout << "Lista de adyacencia: " << endl;
    for (int u = 0; u < V; u++) {
        cout << u + 1 << ": ";
        for (const auto& [v, w] : M[u]) {
            cout << "(" << v + 1 << ", " << w << ") ";
        }
        cout << endl;
    }
    cout << endl;
}

/*
    * Operador de igualdad: Compara si dos grafos son iguales.
    * Parametros: 
    * - other: Otro grafo a comparar.
    * Retorno: 
    * - bool: true si los grafos son iguales, false en caso contrario.
*/
bool Graph::operator==(const Graph& other) const {
    return (V == other.V && E == other.E && M == other.M && T == other.T && Tn == other.Tn && INF == other.INF);
}