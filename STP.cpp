#include "STP.h"

STP::STP(Graph* g) : g(g) {
    if (g == nullptr) {
        cout << "[STP::STP] Error: El grafo es nulo." << endl;
        exit(1);
    }
}

pair<vector<pair<int, int>>, double> STP::solve() const{
    cout << "[STP::solve] No se ha implementado el metodo de solucion." << endl;
    return pair<vector<pair<int, int>>, double>{};
};

bool STP::verifyValidity(const vector<pair<int, int>>& Te, double totalWeight) const {
    cout << "[STP::verifyValidity] Verificando la validez de la aproximacion..." << endl;

    if (Te.empty()) {
        cout << "[STP::verifyValidity] Error: El conjunto de aristas es vacio." << endl;
        return false;
    }

    if (totalWeight < 0 || totalWeight == g->getINF()) {
        cout << "[STP::verifyValidity] Error: El peso total no es valido (negativo o infinito)." << endl;
        return false;
    }

    if (Te.size() > g->getE()) {
        cout << "[STP::verifyValidity] Error: El conjunto de aristas de la aproximacion es mayor que el numero de aristas del grafo original." << endl;
        return false;
    }

    if (Te.size() < g->getTn()) {
        cout << "[STP::verifyValidity] Error: El numero de aristas de la aproximacion (" << Te.size() << ") es menor que el numero de nodos terminales original (" << g->getT().size() << ")." << endl;
        return false;
    }

    for(int i = 0; i < Te.size(); ++i) {
        const auto& edge = Te[i];
        if (edge.first < 0 || edge.second < 0 || edge.first >= g->getV() || edge.second >= g->getV()) {
            cout << "[STP::verifyValidity] Error: La arista " << edge.first << "-" << edge.second << " (de la aproximacion) es invalida." << endl;
            return false;
        }
        if (g->getEdge(edge.first, edge.second) == g->getINF()) {
            cout << "[STP::verifyValidity] Error: La arista " << edge.first << "-" << edge.second << " (de la aproximacion) no existe en el grafo original." << endl;
            return false;
        }
        if (g->getEdge(edge.first, edge.second) < 0) {
            cout << "[STP::verifyValidity] Error: La arista " << edge.first << "-" << edge.second << " (de la aproximacion) tiene un peso negativo." << endl;
            return false;
        }
        if (find_if(Te.begin(), Te.end(), [edge](const pair<int, int>& e) {
            return (e.first == edge.first && e.second == edge.second) || (e.first == edge.second && e.second == edge.first);
        }) == Te.end()) {
            cout << "[STP::verifyValidity] Error: La arista " << edge.first << "-" << edge.second << " (de la aproximacion) no es parte del conjunto de aristas original." << endl;
            return false;
        }
    }
    for(int i = 0; i < g->getV(); ++i) {
        if (g->getT()[i] && find_if(Te.begin(), Te.end(), [i](const pair<int, int>& edge) {
            return edge.first == i || edge.second == i;
        }) == Te.end()) {
            cout << "[STP::verifyValidity] Error: El nodo terminal original " << i << " no está conectado al el árbol de Steiner de la aproximacion." << endl;
            return false;
        }
    }
    cout << "[STP::verifyValidity] La aproximacion es valida. Yippie!!!" << endl;
    return true;
}

void STP::print(const pair<vector<pair<int, int>>, double>& AproxST) const {
    cout << "[STP::print] No se ha implementado el metodo de impresion." << endl;
}

STP::~STP() {
    delete g;
    g = nullptr;
}