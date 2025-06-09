#include "Takahashi.h"

Takahashi::Takahashi(Graph* g) : STP(g) {}

pair<vector<pair<int, int>>, double> Takahashi::solve() const {
    vector<pair<int, int>> Te;
    unordered_set<int> Tv;
    int r = -1;
    vector<int> R;
    double finalWeight = 0;

    // Crear lista de terminales
    for (int i = 0; i < g->getV(); i++) {
        if (g->getT()[i]) {
            R.push_back(i);
        }
    }

    if (R.empty()) {
        cout << "[Takahashi::solve] Error: No hay vertices terminales en el grafo" << endl;
        return {Te, -1};
    }

    // Inicializar con el primer terminal
    r = R[0];
    R.erase(R.begin());
    Tv.insert(r);

    while (!R.empty()) {
        double minWeight = g->getINF(); // Peso minimo a retornar en la aproximacion
        pair<vector<pair<pair<int, int>, double>>, double> currentPath;   // camino actual de cada iteracion (Tv, pesoCamino)
        vector<pair<pair<int, int>, double>> shortestPath;    // camino mas corto (Tv)
        int v = R[0]; // Tomar un terminal de R

        for(int tv : Tv){
            cout << "[Takahashi::solve] Buscando camino entre " << tv << " y " << v << endl;
            currentPath = g->dijkstra(tv, v);
            g->printDijkstra(currentPath.first);
            //cin.get(); // Esperar a que el usuario presione Enter para continuar
            
            if (!currentPath.first.empty()) {
                if(currentPath.second < minWeight){
                    minWeight = currentPath.second;
                    shortestPath = currentPath.first;
                }
            }
        }

        // Verificar si se encontró un camino
        if (minWeight == g->getINF()) {
            cout << "[Takahashi::solve] Error: No se encontró camino entre conjuntos" << endl;
            return {Te, -1};
        }
        
        // Actualizar el peso total
        finalWeight += minWeight;

        // Agregar las aristas al árbol de Steiner
        for (const auto& edge : shortestPath) {
            Te.push_back(edge.first);
        }

        // Actualizar Tv y eliminar el terminal de R
        for (const auto& [node, _] : shortestPath) {
            Tv.insert(node.first);
        }
        R.erase(R.begin());
    }

    return {Te, finalWeight};
}

void Takahashi::print(const pair<vector<pair<int, int>>, double>& AproxST) const {
    if (AproxST.second == -1) {
        cout << "[Takahashi::print] No hay arbol de Steiner para imprimir." << endl;
        return;
    }
    cout << endl << "[Takahashi::print] Imprimiendo arbol de Steiner (nodos desde 1)..." << endl;
    vector<pair<int, int>> Te = AproxST.first;
    for (const auto& [u, v] : Te) {
        cout << "(" << u + 1 << ", " << v + 1 << ")" << endl;
    }
    cout << "Peso total de la aproximacion (metodo Takahashi-Matsuyama) al arbol de Steiner: " << AproxST.second << endl;
    cout << endl;
}