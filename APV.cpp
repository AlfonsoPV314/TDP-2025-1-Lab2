#include "APV.h"

APV::APV(Graph* g) : STP(g) {}

/*
    Método solve: Resuelve el problema del árbol de Steiner utilizando el método APV (Aproximación por Perturbaciones entre Vértices).
    Este método sigue los pasos del algoritmo KMB (Kou-Markowsky-Berman) añadiendo perturbaciones aleatorias a las aristas del grafo e iterando entre candidatos a solución para encontrar una mejor aproximación al árbol de Steiner.
    Parámetros:
    * - Ninguno.
    Retorno:
    * - pair<vector<pair<int, int>>, double>: Un par que contiene un vector de pares de enteros (aristas del árbol de Steiner) y un double (peso total del árbol).
*/
pair<vector<pair<int, int>>, double> APV::solve() const {
    const int num_iterations = 20;  // 20 iteraciones para mejorar la solución
    srand(static_cast<unsigned>(time(nullptr)));  // semilla para la generación de números aleatorios

    // (KMB) paso 1: clausura métrica del grafo original
    const vector<bool>& T = g->getT();
    int S = T.size();
    Graph* GPrima = new Graph(S);
    
    // variables para almacenar el mapa de caminos y sus costos
    // pathMap[i][j] almacena el camino entre i y j como un vector de pares (arista, peso)
    // donde arista es un par (u, v) y peso es el peso de la arista
    vector<vector<vector<pair<pair<int, int>, double>>>> pathMap(S, vector<vector<pair<pair<int, int>, double>>>(S));

    // construir el grafo de clausura métrica
    for (int i = 0; i < S; ++i) {
        if (!T[i]) continue;
        for (int j = i+1; j < S; ++j) {
            if (!T[j]) continue;
            auto [path, cost] = g->dijkstra(i, j);
            if (cost < g->getINF()) {
                GPrima->addEdge(i, j, cost);
                pathMap[i][j] = path;
                pathMap[j][i] = path;  // Symmetric
            }
        }
    }

    // generar candidatos de árboles de Steiner
    double bestCost = g->getINF();
    vector<pair<int, int>> bestTree;

    // pre-computar nodos terminales
    vector<int> terminals;
    for (int i = 0; i < S; ++i) if (T[i]) terminals.push_back(i);

    // realizar iteraciones para encontrar el mejor árbol de Steiner
    for (int iter = 0; iter < num_iterations; ++iter) {
        Graph* GPrima_pert = GPrima->cloneGraph();

        // perturbación aleatoria de aristas
        // se perturba el peso de las aristas en un 1% del valor aleatorio
        if (iter > 0) {
            for (int u = 0; u < S; ++u) {
                const auto& adj = GPrima_pert->getM();
                if (u >= adj.size()) continue;  // evitar acceso fuera de rango
                for (const auto& [v, w] : adj[u]) {
                    if (u < v) {  // para evitar duplicados
                        double perturb = w * ((double)rand()/RAND_MAX) * 0.01;  // perturbación con 1% del valor aleatorio generado ponderando el peso de la arista
                        GPrima_pert->removeEdge(u, v);
                        GPrima_pert->addEdge(u, v, w + perturb);
                    }
                }
            }
        }

        // nodo terminal de inicio aleatorio para el árbol de Steiner
        int startNode = terminals[rand() % terminals.size()];
        auto candidate = buildSteinerTree(GPrima_pert, pathMap, startNode); // candidato de árbol de Steiner
        
        // verificar si el candidato es mejor que el mejor encontrado hasta ahora
        if (candidate.second > 0 && candidate.second < bestCost) {
            bestCost = candidate.second;
            bestTree = candidate.first;
        }

        delete GPrima_pert;
    }

    delete GPrima;
    return {bestTree, bestCost};
}

/*
    Método buildSteinerTree: Construye el árbol de Steiner a partir del grafo perturbado y el mapa de caminos.
    Este método sigue los pasos 2 al 6 del algoritmo KMB (Kou-Markowsky-Berman) para construir el árbol de Steiner a partir de los caminos mínimos entre nodos terminales.
    También se encarga de perturbar las aristas del grafo y eliminar hojas no terminales del árbol resultante.
    Parámetros:
    * - GPrima: Grafo perturbado sobre el cual se construirá el árbol de Steiner.
    * - pathMap: Mapa de caminos mínimos entre nodos terminales.
    * - startNode: Nodo terminal desde el cual se iniciará la construcción del árbol de Steiner.
    Retorno:
    * - pair<vector<pair<int, int>>, double>: Un par que contiene un vector de pares de enteros (aristas del árbol de Steiner) y un double (peso total del árbol).
*/
pair<vector<pair<int, int>>, double> APV::buildSteinerTree(Graph* GPrima, const vector<vector<vector<pair<pair<int, int>, double>>>>& pathMap, int startNode) const {
    const vector<bool>& T = g->getT();
    int S = T.size();

    // (KMB) paso 2: MST en la clausura métrica perturbada
    if (startNode < 0 || startNode >= S || !T[startNode]) {
        return {{}, -1};  // nodo de inicio no válido
    }

    auto TPrima = GPrima->MSTPrim(startNode);
    if (TPrima.first.empty() || TPrima.second == -1) return {{}, -1};

    // (KMB) paso 3: construir el árbol de Steiner a partir de los caminos en el MST
    vector<pair<pair<int, int>, double>> Et;
    unordered_set<int> Vt_set;

    // combinar los caminos mínimos entre nodos terminales
    for (const auto& edge : TPrima.first) {
        int u = edge.first.first;
        int v = edge.first.second;
        
        if (u >= S || v >= S) continue;
        if (!T[u] || !T[v]) continue;

        const auto& path = pathMap[u][v];
        for (const auto& e : path) {
            Et.push_back(e);
            Vt_set.insert(e.first.first);
            Vt_set.insert(e.first.second);
        }
    }

    // convertur a vector y crear el grafo de Steiner
    vector<int> Vt(Vt_set.begin(), Vt_set.end());
    Graph* ST = new Graph(Vt, Et, T);

    // (KMB) paso 4: crear árbol de Steiner
    int mstStart = -1;
    for (int node : Vt) {
        if (node < S && T[node]) {
            mstStart = node;
            break;
        }
    }

    if (mstStart == -1) {
        delete ST;
        return {{}, -1};
    }

    // sacar MST de los caminos encontrados
    auto ST_MST = ST->MSTPrim(mstStart);
    if (ST_MST.first.empty()) {
        delete ST;
        return {{}, -1};
    }

    // (KMB) paso 5: podar hojas no terminales
    while (true) {
        auto leaves = ST->getNonTermLeaves();
        if (!leaves.first) break;
        for (const auto& leaf : leaves.second) {
            ST->removeEdge(leaf.first, leaf.second);
        }
    }

    // (KMB) paso 6: formateo del resultado
    // convertir el árbol de Steiner a un vector de pares (u, v) y calcular el peso total
    vector<pair<int, int>> Te;
    double totalWeight = 0;
    const auto& adjList = ST->getM();
    
    for (int i = 0; i < ST->getV(); ++i) {
        if (i < static_cast<int>(adjList.size())) {
            for (const auto& [j, w] : adjList[i]) {
                if (i < j) {
                    Te.push_back({i, j});
                    totalWeight += w;
                }
            }
        }
    }

    delete ST;
    return {Te, totalWeight};
}

void APV::print(const pair<vector<pair<int, int>>, double>& AproxST) const {
    if (AproxST.second == -1) {
        cout << "No hay arbol de Steiner para imprimir." << endl;
        return;
    }
    cout << endl << "Imprimiendo arbol de Steiner mejorado (metodo APV)..." << endl;
    const vector<pair<int, int>>& Te = AproxST.first;
    for (const auto& [u, v] : Te) {
        cout << "(" << u + 1 << ", " << v + 1 << ")" << endl;
    }
    cout << "Peso total de la aproximacion (metodo APV) al arbol de Steiner: " << AproxST.second << endl << endl;
}