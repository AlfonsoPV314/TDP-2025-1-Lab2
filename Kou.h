#ifndef KOU_H
#define KOU_H

#include "STP.h"

using namespace std;

/*
    * Clase Kou: Implementa el algoritmo de Kou-Markowsky-Berman para el problema del árbol de Steiner.
    * Hereda de la clase STP.
    * Esta clase se encarga de resolver el problema del árbol de Steiner utilizando el método Kou-Markowsky-Berman.
    * El algoritmo sigue los pasos del método KMB (Kou-Markowsky-Berman) para encontrar una aproximación al árbol de Steiner.
*/
class Kou: public STP {
public:
    // Constructor de la clase Kou.
    Kou(Graph* g);
    // Método solve: Resuelve el problema del árbol de Steiner utilizando el método Kou-Markowsky-Berman.
    pair<vector<pair<int, int>>, double> solve() const override;

    // Método print: Imprime el árbol de Steiner aproximado y su peso total.
    void print(const pair<vector<pair<int, int>>, double>& AproxST) const override;
};

#endif