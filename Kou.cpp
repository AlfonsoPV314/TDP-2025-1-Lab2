#include "Kou.h"

/*
    * Constructor de la clase Kou.
    * Inicializa el grafo g y prepara el entorno para resolver el problema del árbol de Steiner.
    * Parametros: Puntero al grafo sobre el cual se resolverá el problema del árbol de Steiner.
    * - g: Puntero al objeto Graph que representa el grafo.
    * Retorno:
    * - void
*/
Kou::Kou(Graph* g) : STP(g) {}

/*
    Método solve: Resuelve el problema del árbol de Steiner utilizando el método Kou-Markowsky-Berman.
    Parametros:
    * - Ninguno.
    Retorno:
    * - pair<vector<pair<int, int>>, double>: Un par que contiene un vector de pares de enteros (aristas del árbol de Steiner) y un double (peso total del árbol).
*/
pair<vector<pair<int, int>>, double> Kou::solve() const {
    int S = g->getT().size();   // Cantidad de nodos terminales
    vector<bool> T = g->getT();   // Vector de nodos terminales
    pair<vector<pair<pair<int, int>, double>>, double> EPrima;   // camino actual de cada iteracion (para encontrar la clausura metrica)
    Graph* GPrima = new Graph(S);    // Grafo completo de distancias entre nodos terminales (clausura metrica)

    // Paso 1: Calcular la clausura metrica
    // para cada par de nodos terminales, encontrar el camino mas corto entre ellos
    for (int i = 0; i < S; ++i) {
        for (int j = i + 1; j < S; ++j) {
            if (!T[i] || !T[j]) {
                continue;   // Si alguno de los nodos no es terminal, continuar
            }
            //cout << "[Kou::solve] Buscando camino entre " << i << " y " << j << endl;
            EPrima = g->dijkstra(i, j);
            if (EPrima.second == g->getINF()) {
                continue;   // Si no se encuentra un camino, continuar
            }
            GPrima->addEdge(i, j, EPrima.second);
            //g->printDijkstra(EPrima.first);   // Imprimir el camino encontrado
        }
    }

    if(GPrima->getE() == 0) {
        //cout << "[Kou::solve] Error: No se encontraron caminos entre nodos terminales." << endl;
        return { {}, -1 };
    }

    //cout << "[Kou::solve] (Paso 1) Grafo completo de distancias entre nodos terminales (clausura metrica) creado con " << GPrima->getV() << " nodos y " << GPrima->getE() << " aristas:" << endl;
    //GPrima->printGraph();   // Imprimir el grafo completo de distancias entre nodos terminales

    // Paso 2: Extraer un recubrimiento de la clausura metrica
    // Encontrar el árbol de expansión mínima (MST) del grafo completo de distancias
    int ini = -1;
    for(int i = 0; i < S; ++i) {
        if (T[i]) {
            ini = i;
            break;   // Si el nodo no es terminal, no se incluye en el árbol de expansión mínima
        }
    }

    if(ini == -1) {
        //cout << "[Kou::solve] Error: No se encontró un nodo terminal para iniciar el árbol de expansión mínima." << endl;
        return { {}, -1 };
    }

    pair<vector<pair<pair<int, int>, double>>, double> TPrima = GPrima->MSTPrim(ini);

    if (TPrima.first.empty()) {
        //cout << "[Kou::solve] Error: No se encontró un árbol de expansión mínima." << endl;
        return { {}, -1 };
    }

    //cout << "[Kou::solve] (Paso 2) Árbol de expansión mínima encontrado con " << TPrima.first.size() << " aristas y peso total: " << TPrima.second << endl;
    //GPrima->printMST(TPrima);   // Imprimir el árbol de expansión mínima encontrado

    if (TPrima.second == -1) {
        //cout << "[Kou::solve] Error: No se encontró un árbol de expansión mínima." << endl;
        return { {}, -1 };
    }

    // Paso 3: Generar grafo utilizando todos los caminos minimos encontrados
    int u = -1, v = -1;   // Variables para almacenar los nodos de las aristas
    double w = -1;   // Variable para almacenar el peso de las aristas
    vector<pair<pair<int, int>, double>> Et;   // Aristas del grafo encontrado
    vector<int> Vt;   // Nodos del grafo encontrado
    pair<vector<pair<pair<int, int>, double>>, double> Puv;   // camino entre nodos terminales
    
    // Encontrar los caminos minimos entre los nodos terminales
    for (const auto& edge : TPrima.first) {
        u = edge.first.first;
        v = edge.first.second;
        if(!T[u] || !T[v]) {
            continue;   // Si alguno de los nodos no es terminal, continuar
        }
        //cout << "[Kou::solve] Buscando camino entre " << u << " y " << v << endl;
        Puv = g->dijkstra(u, v);
        if (Puv.second == g->getINF()) {
            continue;   // Si no se encuentra un camino, continuar
        }
        for (const auto& e : Puv.first) {
            Et.push_back({e});
            if(find(Vt.begin(), Vt.end(), e.first.first) == Vt.end()) {
                Vt.push_back(e.first.first);
            }
            if(find(Vt.begin(), Vt.end(), e.first.second) == Vt.end()) {
                Vt.push_back(e.first.second);
            }
        }
    }

    Graph* ST = new Graph(Vt, Et, T);   // Grafo de aristas y nodos encontrados
    //cout << "[Kou::solve] (Paso 3) Grafo de aristas y nodos encontrados (caminos minimos) creado con " << ST->getV() << " nodos y " << ST->getE() << " aristas:" << endl;
    //ST->printGraph();   // Imprimir el grafo de aristas y nodos encontrados (del paso 3)
    
    // Paso 4: Crear el árbol de Steiner
    // Si el grafo es cíclico, eliminar la arista de mayor peso que causa el ciclo
    for(auto cycle = ST->getCyclic(); cycle.first; cycle = ST->getCyclic()) {
        vector<pair<int, int>> cyclicEdges = cycle.second;
        double maxWeight = -1;
        pair<int, int> edgeToRemove;

        // Encontrar la arista de mayor peso en el ciclo
        for (const auto& edge : cyclicEdges) {
            double weight = ST->getEdge(edge.first, edge.second);
            if (weight > maxWeight) {
                maxWeight = weight;
                edgeToRemove = edge;
            }
        }

        // Eliminar la arista de mayor peso
        ST->removeEdge(edgeToRemove.first, edgeToRemove.second);
    }

    //cout << "[Kou::solve] (Paso 4) Eliminación de ciclos completada. Grafo de Steiner actualizado:" << endl;
    //ST->printGraph();   // Imprimir el grafo después de eliminar ciclos (del paso 4)
    
    // Paso 5: Eliminar ramas que no conduzcan a nodos terminales
    for(auto nonTermLeaves = ST->getNonTermLeaves(); nonTermLeaves.first; nonTermLeaves = ST->getNonTermLeaves()) {
        vector<pair<int, int>> leaves = nonTermLeaves.second;
        for (const auto& leaf : leaves) {
            ST->removeEdge(leaf.first, leaf.second);
        }
    }

    //cout << "[Kou::solve] (Paso 5) Eliminación de ramas que no conducen a nodos terminales completada. Grafo de Steiner actualizado:" << endl;
    //ST->printGraph();   // Imprimir el grafo después de eliminar ramas que no conducen a nodos terminales (del paso 5)

    // Paso 6: Armar el resultado final
    vector<pair<int, int>> Te;   // Aristas del árbol de Steiner
    double totalWeight = 0;   // Peso total del árbol de Steiner
    const auto& adjList = ST->getM(); // Referencia al mapa para evitar copias innecesarias
    for (int i = 0; i < ST->getV(); ++i) {
        //cout << "[Kou::solve] Procesando nodo " << i << " con adyacentes: " << endl;
        for (const auto& [neighbor, weight] : adjList.at(i)) { // Usa 'at' para acceso seguro
            //cout << "[Kou::solve] Nodo " << i << " tiene vecino " << neighbor << " con peso " << weight << endl;
            if (i < neighbor) { // No necesitas verificar si la lista está vacía; el bucle no iterará si lo está
                Te.push_back({i, neighbor});
                totalWeight += weight;
            }
        }
    }
    delete GPrima;   // Liberar memoria del grafo completo de distancias
    delete ST;   // Liberar memoria del árbol de Steiner
    //cout << "[Kou::solve] Arbol de Steiner encontrado con " << Te.size() << " aristas y peso total: " << totalWeight << endl;
    return {Te, totalWeight};   // Retornar el árbol de Steiner y su peso total
}

/*
    Método print: Imprime el árbol de Steiner aproximado y su peso total.
    Este método muestra las aristas del árbol de Steiner y su peso total.
    Parametros:
    * - AproxST: Un par que contiene un vector de pares de enteros (aristas del árbol de Steiner) y un double (peso total del árbol).
    Retorno:
    * - void
*/
void Kou::print(const pair<vector<pair<int, int>>, double>& AproxST) const {
    if (AproxST.second == -1) {
        cout << "No hay arbol de Steiner para imprimir." << endl;
        return;
    }
    cout << endl << "Imprimiendo arbol de Steiner (metodo Kou-Markowsky-Berman)..." << endl;
    vector<pair<int, int>> Te = AproxST.first;
    for (const auto& [u, v] : Te) {
        cout << "(" << u + 1<< ", " << v + 1 << ")" << endl;
    }
    cout << "Peso total de la aproximacion (metodo Kou-Markowsky-Berman) al arbol de Steiner: " << AproxST.second << endl;
    cout << endl;
}