#include "Kou.h"

int main(){
    Graph* g = new Graph(9);
    g->addEdge(0, 1, 10);
    g->addEdge(0, 8, 1);
    g->addEdge(1, 2, 8);
    g->addEdge(1, 5, 1);
    g->addEdge(2, 3, 9);
    g->addEdge(2, 4, 2);
    g->addEdge(3, 4, 2);
    g->addEdge(4, 5, 1);
    g->addEdge(4, 8, 1);
    g->addEdge(5, 6, 1);
    g->addEdge(6, 7, 0.5);
    g->addEdge(7, 8, 0.5);
    g->setTerm(0);
    g->setTerm(1);
    g->setTerm(2);
    g->setTerm(3);
    g->printGraph();
    cout << "Resolviendo el problema del árbol de Steiner con el método Kou-Markowsky-Berman..." << endl;
    Kou* k = new Kou(g);
    k->print(k->solve());
}