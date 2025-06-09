#ifndef STP_H
#define STP_H

#include "Graph.h"

/*
    * Clase STP: Clase base para resolver el problema del árbol de Steiner.
    * Esta clase define la interfaz y los métodos comunes para los algoritmos de aproximación del árbol de Steiner.
    * Los algoritmos específicos deben heredar de esta clase y sobreescribir el método solve().
    * Utilizada para implementar el patrón de diseño Strategy.
*/
class STP{
protected:
    Graph* g;   // Grafo sobre el cual se resolverá el problema del árbol de Steiner

    // Constructor y destructor protegidos para evitar instanciación directa de la clase base
    STP(Graph* g);
    virtual ~STP();
public:

    // Método virtual solve que debe ser implementado por las clases derivadas para resolver el problema del arbol mínimo de Steiner.
    virtual pair<vector<pair<int, int>>, double> solve() const;

    // Método virtual print que debe ser implementado por las clases derivadas para imprimir el árbol de Steiner aproximado.
    virtual void print(const pair<vector<pair<int, int>>, double>& AproxST) const;

    // Método para verificar la validez del árbol de Steiner aproximado
    bool verifyValidity(const vector<pair<int, int>>& Te, double totalWeight) const;
};

#endif 