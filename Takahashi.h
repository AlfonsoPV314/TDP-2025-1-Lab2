#ifndef TAKAHASHI_H
#define TAKAHASHI_H

#include "STP.h"

/*
    * Clase Takahashi: Implementa el algoritmo de Takahashi-Matsuyama para el problema del árbol de Steiner.
    * Hereda de la clase STP.
    * Esta clase se encarga de resolver el problema del árbol de Steiner utilizando el método Takahashi-Matsuyama.
    * El algoritmo sigue los pasos del método Takahashi-Matsuyama para encontrar una aproximación al árbol de Steiner.
*/
class Takahashi: public STP {
public:

    // Constructor de la clase Takahashi.
    Takahashi(Graph* g);

    // Método solve: Resuelve el problema del árbol de Steiner utilizando el método Takahashi-Matsuyama.
    pair<vector<pair<int, int>>, double> solve() const override;

    // Método print: Imprime el árbol de Steiner aproximado y su peso total.
    void print(const pair<vector<pair<int, int>>, double>& AproxST) const override;
};

#endif