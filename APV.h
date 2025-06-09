#ifndef APV_H
#define APV_H

#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "STP.h"

using namespace std;

/*
    * Clase APV: Implementa el algoritmo de aproximación propio para el problema del árbol de Steiner.
    * Hereda de la clase STP.
    * Esta clase se encarga de resolver el problema del árbol de Steiner utilizando el método APV (Aproximación por Perturbaciones entre Vértices).
    * El algoritmo sigue los pasos del método KMB (Kou-Markowsky-Berman) añadiendo perturbaciones aleatorias a las aristas del grafo para encontrar una mejor aproximación al árbol de Steiner.
*/
class APV : public STP {
public:
    // Constructor de la clase APV.
    APV(Graph* g);

    // Método solve: Resuelve el problema del árbol de Steiner utilizando el método APV.
    pair<vector<pair<int, int>>, double> solve() const override;

    // Método print: Imprime el árbol de Steiner aproximado y su peso total.
    void print(const pair<vector<pair<int, int>>, double>& AproxST) const;

private:

    // Método auxiliar para construir el árbol de Steiner a partir del grafo perturbado y el mapa de caminos.
    pair<vector<pair<int, int>>, double> buildSteinerTree(Graph* GPrima, const vector<vector<vector<pair<pair<int, int>, double>>>>& pathMap) const;
};


#endif