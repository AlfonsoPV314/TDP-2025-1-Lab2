#include "Strategy.h"

Strategy::Strategy(Graph* g) : g(g) {
    if (g == nullptr) {
        cout << "[Strategy::Strategy] Error: El grafo es nulo." << endl;
        exit(1);
    }
}

pair<vector<pair<int, int>>, double> Strategy::solve() const{
    cout << "[Strategy::solve] No se ha implementado el metodo de solucion." << endl;
    return pair<vector<pair<int, int>>, double>{};
};

void Strategy::print(const pair<vector<pair<int, int>>, double>& AproxST) const {
    cout << "[Strategy::print] No se ha implementado el metodo de impresion." << endl;
}

Strategy::~Strategy() {
    delete g;
    g = nullptr;
}