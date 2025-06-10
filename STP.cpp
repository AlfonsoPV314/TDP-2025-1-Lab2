#include "STP.h"

/*
    * Constructor de la clase STP.
    * Inicializa el grafo g y prepara el entorno para resolver el problema del árbol de Steiner.
    * Parametros: Puntero al grafo sobre el cual se resolverá el problema del árbol de Steiner.
    * - g: Puntero al objeto Graph que representa el grafo.
    * Retorno: 
    * - void
*/
STP::STP(Graph* g) : g(g) {
    if (g == nullptr) {
        //cout << "[STP::STP] Error: El grafo es nulo." << endl;
        exit(1);
    }
}

/*
    Método solve: Resuelve el problema del árbol de Steiner.
    Este método es virtual y debe ser implementado por las clases derivadas.
    Parametros:
    * - Ninguno.
    Retorno:
    * - pair<vector<pair<int, int>>, double>: Un par que contiene un vector de pares de enteros (aristas del árbol de Steiner) y un double (peso total del árbol).
*/
pair<vector<pair<int, int>>, double> STP::solve() const{
    return pair<vector<pair<int, int>>, double>{};
};

/*
    Método verifyValidity: Verifica la validez del árbol de Steiner aproximado.
    Este método comprueba si el conjunto de aristas y el peso total cumplen con las condiciones del problema.
    Parametros:
    * - Te: Conjunto de aristas del árbol de Steiner aproximado.
    * - totalWeight: Peso total del árbol de Steiner aproximado.
    Retorno:
    * - bool: Verdadero si la aproximación es válida, falso en caso contrario.
*/
bool STP::verifyValidity(const vector<pair<int, int>>& Te, double totalWeight) const {
    cout << "Verificando la validez de la aproximacion..." << endl;
    bool isValid = true;

    if (Te.empty()) {
        cout << "Error: El conjunto de aristas es vacio." << endl;
        isValid = false;
    }

    if (totalWeight < 0 || totalWeight == g->getINF()) {
        cout << "Error: El peso total no es valido (negativo o infinito)." << endl;
        isValid = false;
    }

    if (Te.size() > g->getE()) {
        cout << "Error: El conjunto de aristas de la aproximacion es mayor que el numero de aristas del grafo original." << endl;
        isValid = false;
    }

    if (Te.size() < g->getTn()) {
        cout << "Error: El numero de aristas de la aproximacion (" << Te.size() << ") es menor que el numero de nodos terminales original (" << g->getTn() << ")." << endl;
        isValid = false;
    }

    for(int i = 0; i < Te.size(); ++i) {
        const auto& edge = Te[i];
        if (edge.first < 0 || edge.second < 0 || edge.first >= g->getV() || edge.second >= g->getV()) {
            cout << "Error: La arista " << edge.first << "-" << edge.second << " (de la aproximacion) es invalida." << endl;
            isValid = false;
        }
        if (g->getEdge(edge.first, edge.second) == g->getINF()) {
            cout << "Error: La arista " << edge.first + 1 << "-" << edge.second + 1 << " (de la aproximacion) no existe en el grafo original." << endl;
            isValid = false;
        }
        if (g->getEdge(edge.first, edge.second) < 0) {
            cout << "Error: La arista " << edge.first << "-" << edge.second << " (de la aproximacion) tiene un peso negativo." << endl;
            isValid = false;
        }
        if (find_if(Te.begin(), Te.end(), [edge](const pair<int, int>& e) {
            return (e.first == edge.first && e.second == edge.second) || (e.first == edge.second && e.second == edge.first);
        }) == Te.end()) {
            cout << "Error: La arista " << edge.first << "-" << edge.second << " (de la aproximacion) no es parte del conjunto de aristas original." << endl;
            isValid = false;
        }
    }
    for(int i = 0; i < g->getV(); ++i) {
        if (g->getT()[i] && find_if(Te.begin(), Te.end(), [i](const pair<int, int>& edge) {
            return edge.first == i || edge.second == i;
        }) == Te.end()) {
            cout << "Error: El nodo terminal original " << i + 1 << " no está conectado al el árbol de Steiner de la aproximacion." << endl;
            isValid = false;
        }
    }

    // recorrer el conjunto de aristas y verificar si el peso total es correcto
    double calculatedWeight = 0;
    for (const auto& edge : Te) {
        calculatedWeight += g->getEdge(edge.first, edge.second);
    }

    if (calculatedWeight != totalWeight) {
        cout << "Warning: El peso total calculado (" << calculatedWeight << ") no coincide con el peso total proporcionado por la aproximacion (" << totalWeight << ")." << endl << "El peso real del arbol de Steiner es: " << calculatedWeight << endl;
    }
    if(!isValid) {
        cout << "La aproximacion no es valida." << endl;
        return false;
    }
    cout << "La aproximacion es valida." << endl;
    return true;
}

/*
    Método print: Imprime el árbol de Steiner aproximado.
    Este método es virtual y debe ser implementado por las clases derivadas.
    Parametros:
    * - AproxST: Un par que contiene un vector de pares de enteros (aristas del árbol de Steiner) y un double (peso total del árbol).
    Retorno:
    * - void
*/
void STP::print(const pair<vector<pair<int, int>>, double>& AproxST) const {}

/*
    Destructor de la clase STP.
    Libera la memoria del grafo g.
    Retorno: 
    - void
*/
STP::~STP() {
    delete g;
    g = nullptr;
}