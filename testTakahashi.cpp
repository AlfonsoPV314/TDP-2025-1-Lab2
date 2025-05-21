#include "Takahashi.h"

int main(){
    Graph* g = new Graph(6);
    g->addEdge(0, 1, 1);
    g->addEdge(0, 3, 2);
    g->addEdge(2, 1, 1);
    g->addEdge(4, 1, 2);
    g->addEdge(4, 2, 2);
    g->addEdge(5, 3, 1);
    g->addEdge(5, 4, 1);
    g->setTerm(0);
    g->setTerm(2);
    g->setTerm(5);
    Takahashi* t = new Takahashi(g);
    t->print(t->solve());
}