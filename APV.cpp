#include "APV.h"

APV::APV(Graph* g) : STP(g) {}

pair<vector<pair<int, int>>, double> APV::solve() const {
    const int num_iterations = 5;  // Iteraciones de perturbación
    srand(static_cast<unsigned>(time(nullptr)));  // Semilla aleatoria

    // Paso 1: Clausura métrica
    int S = g->getT().size();
    vector<bool> T = g->getT();
    Graph* GPrima = new Graph(S);
    
    // Tensor 3D para almacenar caminos: pathMap[i][j] = camino completo de i a j
    vector<vector<vector<pair<pair<int, int>, double>>>> pathMap(
        S, 
        vector<vector<pair<pair<int, int>, double>>>(
            S, 
            vector<pair<pair<int, int>, double>>()
        )
    );

    for (int i = 0; i < S; ++i) {
        for (int j = i + 1; j < S; ++j) {
            if (!T[i] || !T[j]) continue;
            
            auto EPrima = g->dijkstra(i, j);
            if (EPrima.second == g->getINF()) continue;
            
            GPrima->addEdge(i, j, EPrima.second);
            pathMap[i][j] = EPrima.first;  // Almacenar camino completo i→j
            pathMap[j][i] = EPrima.first;  // Almacenar camino completo j→i (mismo conjunto de aristas)
        }
    }

    // Paso 2: Generar múltiples candidatos con perturbaciones
    double bestCost = g->getINF();
    vector<pair<int, int>> bestTree;

    for (int iter = 0; iter < num_iterations; ++iter) {
        Graph* GPrima_pert = GPrima->cloneGraph();

        // Perturbación solo en iteraciones > 0
        if (iter > 0) {
            cout << "[APV::solve] Iteración " << iter << ": aplicando perturbaciones..." << endl;
            for (int u = 0; u < S; ++u) {
                const auto& adjList = GPrima_pert->getM();
                if (u < adjList.size()) {
                    for (const auto& [v, w] : adjList[u]) {
                        if (u < v) {
                            double perturb = ((double)rand() / RAND_MAX) * 1e-5;
                            cout << "[APV::solve] Perturbando arista (" << u << ", " << v << ") con peso original " << w << " y perturbación " << perturb << endl;
                            GPrima_pert->removeEdge(u, v);
                            GPrima_pert->addEdge(u, v, w + perturb);
                        }
                    }
                }
            }
        }

        auto candidate = buildSteinerTree(GPrima_pert, pathMap);
        if (candidate.second > 0 && candidate.second < bestCost) {
            bestCost = candidate.second;
            bestTree = candidate.first;
        }

        delete GPrima_pert;
    }

    delete GPrima;
    return {bestTree, bestCost};
}

pair<vector<pair<int, int>>, double> APV::buildSteinerTree(Graph* GPrima, const vector<vector<vector<pair<pair<int, int>, double>>>>& pathMap) const {
    cout << "[APV::buildSteinerTree] Construyendo árbol de Steiner (ejecutando pasos 2-6)..." << endl;
    int S = g->getT().size();
    vector<bool> T = g->getT();

    // Paso 2: Extraer MST del grafo perturbado GPrima
    int ini = -1;
    for(int i = 0; i < S; ++i) {
        if (T[i]) {
            ini = i;
            break;
        }
    }

    if(ini == -1) {
        cout << "[APV::buildSteinerTree] Error: No se encontró nodo terminal inicial." << endl;
        return { {}, -1 };
    }

    auto TPrima = GPrima->MSTPrim(ini);
    if (TPrima.first.empty() || TPrima.second == -1) {
        cout << "[APV::buildSteinerTree] Error: No se encontró MST válido." << endl;
        return { {}, -1 };
    }

    // Paso 3: Construir grafo con caminos mínimos del MST
    vector<pair<pair<int, int>, double>> Et;
    unordered_set<int> Vt_set;  // Usar set para nodos únicos
    
    for (const auto& edge : TPrima.first) {
        int u = edge.first.first;
        int v = edge.first.second;
        
        if(u >= static_cast<int>(pathMap.size()) || v >= static_cast<int>(pathMap.size())) {
            cout << "[APV::buildSteinerTree] Error: Índice fuera de rango en pathMap." << endl;
            continue;
        }

        if(!T[u] || !T[v]) continue;  // Solo considerar nodos terminales
        
        const auto& path = pathMap[u][v];
        for (const auto& e : path) {
            Et.push_back(e);
            Vt_set.insert(e.first.first);
            Vt_set.insert(e.first.second);
        }
    }

    // Convertir set a vector
    vector<int> Vt(Vt_set.begin(), Vt_set.end());
    
    // Crear grafo temporal con los caminos encontrados
    Graph* ST = new Graph(Vt, Et, T);
    
    // Paso 4: Eliminar ciclos
    while(true) {
        auto cycle = ST->getCyclic();
        if(!cycle.first) break;
        
        double maxWeight = -1;
        pair<int, int> edgeToRemove;
        
        for(const auto& edge : cycle.second) {
            double weight = ST->getEdge(edge.first, edge.second);
            if(weight > maxWeight) {
                maxWeight = weight;
                edgeToRemove = edge;
            }
        }
        
        ST->removeEdge(edgeToRemove.first, edgeToRemove.second);
    }

    // Paso 5: Podar hojas no terminales
    while(true) {
        auto nonTermLeaves = ST->getNonTermLeaves();
        if(!nonTermLeaves.first) break;
        
        for(const auto& leaf : nonTermLeaves.second) {
            ST->removeEdge(leaf.first, leaf.second);
        }
    }

    // Paso 6: Construir solución final
    vector<pair<int, int>> Te;
    double totalWeight = 0;
    const auto& adjList = ST->getM();
    
    for(int i = 0; i < ST->getV(); ++i) {
        if(i < static_cast<int>(adjList.size())) {
            for(const auto& [neighbor, weight] : adjList.at(i)) {
                if(i < neighbor) {  // Evitar duplicados
                    Te.push_back({i, neighbor});
                    totalWeight += weight;
                }
            }
        }
    }

    delete ST;
    return {Te, totalWeight};
}

void APV::print(const pair<vector<pair<int, int>>, double>& AproxST) const {
    if (AproxST.second == -1) {
        cout << "[APV::print] No hay árbol de Steiner para imprimir." << endl;
        return;
    }
    cout << endl << "[APV::print] Imprimiendo árbol de Steiner..." << endl;
    const vector<pair<int, int>>& Te = AproxST.first;
    for (const auto& [u, v] : Te) {
        cout << "(" << u + 1 << ", " << v + 1 << ")" << endl;
    }
    cout << "Peso total de la aproximación (método APV) al árbol de Steiner: " << AproxST.second << endl;
    cout << endl;
}