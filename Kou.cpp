#include "Kou.h"

Kou::Kou(Graph* g) : Strategy(g) {}

pair<vector<pair<int, int>>, double> Kou::solve() const {
    int S = g->getT().size();   // Cantidad de nodos terminales
    vector<bool> T = g->getT();   // Vector de nodos terminales
    pair<vector<pair<pair<int, int>, double>>, double> EPrima;   // camino actual de cada iteracion (para encontrar la clausura metrica)
    Graph* GPrima = new Graph(S);    // Grafo completo de distancias entre nodos terminales (clausura metrica)

    // Paso 1: Calcular la clausura metrica
    // para cada par de nodos terminales, encontrar el camino mas corto entre ellos
    for (int i = 0; i < S; ++i) {
        for (int j = i + 1; j < S; ++j) {
            EPrima = g->dijkstra(T[i], T[j]);
            if (EPrima.second == g->getINF()) {
                continue;   // Si no se encuentra un camino, continuar
            }
            GPrima->addEdge(i, j, EPrima.second);
        }
    }

    if(GPrima->getE() == 0) {
        cout << "[Kou::solve] Error: No se encontraron caminos entre nodos terminales." << endl;
        return { {}, -1 };
    }

    // Paso 2: Extraer un recubrimiento de la clausura metrica
    // Encontrar el árbol de expansión mínima (MST) del grafo completo de distancias
    pair<vector<pair<pair<int, int>, double>>, double> TPrima = GPrima->MSTPrim(0);

    if (TPrima.second == -1) {
        cout << "[Kou::solve] Error: No se encontró un árbol de expansión mínima." << endl;
        return { {}, -1 };
    }

    // Paso 3: Generar grafo utilizando todos los caminos minimos encontrados
    int u = -1, v = -1;   // Variables para almacenar los nodos de las aristas
    double w = -1;   // Variable para almacenar el peso de las aristas
    vector<pair<pair<int, int>, double>> Et;   // Aristas del grafo encontrado
    vector<int> Vt;   // Nodos del grafo encontrado
    pair<vector<pair<pair<int, int>, double>>, double> Puv;   // camino entre nodos terminales
    
    // Encontrar los caminos minimos entre los nodos terminales
    for (const auto& edge : TPrima.first) {
        u = edge.first.first;
        v = edge.first.second;
        Puv = g->dijkstra(T[u], T[v]);
        if (Puv.second == g->getINF()) {
            continue;   // Si no se encuentra un camino, continuar
        }
        for (const auto& e : Puv.first) {
            Et.push_back({e});
            if(find(Vt.begin(), Vt.end(), e.first.first) == Vt.end()) {
                Vt.push_back(e.first.first);
            }
            if(find(Vt.begin(), Vt.end(), e.first.second) == Vt.end()) {
                Vt.push_back(e.first.second);
            }
        }
    }

    // Paso 4: Crear el árbol de Steiner
    Graph* ST = new Graph(Vt, Et, T);   // Grafo de aristas y nodos encontrados

    // Si el grafo es cíclico, eliminar la arista de mayor peso que causa el ciclo
    while(ST->isCyclic()) {
        // keep going!
    }

}

void Kou::print(const pair<vector<pair<int, int>>, double>& AproxST) const {
    if (AproxST.second == -1) {
        cout << "[Kou::print] No hay arbol de Steiner para imprimir." << endl;
        return;
    }
    cout << endl << "[Kou::print] Imprimiendo arbol de Steiner..." << endl;
    vector<pair<int, int>> Te = AproxST.first;
    for (const auto& [u, v] : Te) {
        cout << "(" << u << ", " << v << ")" << endl;
    }
    cout << "Peso total de la aproximacion (metodo Kou-Markowsky-Berman) al arbol de Steiner: " << AproxST.second << endl;
    cout << endl;
}