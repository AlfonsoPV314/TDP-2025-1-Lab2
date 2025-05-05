#include "Graph.h"
#include <type_traits>

int main() {
    cout << "Creando grafo 1..." << endl;
    Graph g(5); // Crear un grafo con 5 nodos

    if(!is_same<decltype(g), Graph>::value) {
        cout << "Error al crear el grafo 1" << endl;
        return 1;
    } 

    cout << "Creacion del grafo 1 exitosa!" << endl << endl;

    cout << "Añadiendo arista entre 0 y 1 con peso 10" << endl;
    g.addEdge(0, 1, 10);

    cout << "Añadiendo arista entre 0 y 4 con peso 20" << endl;
    g.addEdge(0, 4, 20);

    cout << "Añadiendo arista entre 1 y 2 con peso 30" << endl;
    g.addEdge(1, 2, 30);

    cout << "Añadiendo nodo terminal 2" << endl;
    g.setTerm(2);

    cout << endl << "Creando grafo 2 (clonando grafo 1)..." << endl;
    Graph g2 = *g.cloneGraph();

    if(!(is_same<decltype(g2), Graph>::value && g == g2)) {
        cout << "Error al crear el grafo 2" << endl;
        return 1;
    } 

    cout << "Creacion del grafo 2 exitosa!" << endl << endl;

    cout << "Añadiendo arista en grafo 1 enttre 1 y 3 con peso 40" << endl;
    g.addEdge(1, 3, 40);

    cout << "Añadiendo arista en grafo 1 entre 1 y 4 con peso 50" << endl;
    g.addEdge(1, 4, 50);

    cout << "Añadiendo arista en grafo 1 entre 3 y 4 con peso 60" << endl;
    g.addEdge(3, 4, 60);

    cout << endl << "Añadiendo nodo terminal 0" << endl;
    g.setTerm(0);

    cout << endl << "Creacion de grafos exitosa!" << endl << endl;

    cout << "========== Grafo 1: ==========" << endl;
    g.printGraph();

    cout << "========== Grafo 2 (grafo 1 clonado): ==========" << endl;
    cout << "NOTA: Este grafo no deberia tener aristas entre 1 y 3, ni entre 1 y 4, ni entre 3 y 4. Tampoco deberia tener como terminal al vertice 0." << endl;
    g2.printGraph();

    cout << endl << "Encontrando el camino de Dijkstra entre vertices 0 y 3 para el grafo 1..." << endl;
    vector<pair<int, int>> path = g.dijkstra(0, 3);
    g.printDijkstra(path);

    cout << endl << "Resolviendo el problema del arbol de Steiner a traves del metodo de Takahashi-Matsuyama para el grafo 1..." << endl;
    vector<pair<int, int>> Te = g.solveTM();
    g.printTM(Te);

    return 0;
}