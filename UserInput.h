#ifndef USERINPUT_H
#define USERINPUT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include "Takahashi.h"
#include "Kou.h"
#include "APV.h"

using namespace std;
using namespace std::chrono;

/*
    * Clase UserInput: Maneja la entrada del usuario y la interacción con el programa.
    * Esta clase permite al usuario cargar un grafo desde un archivo, agregar aristas, definir nodos terminales,
    * y elegir el método de aproximación para resolver el problema del árbol de Steiner.
    * Utilizada para implementar el patrón de diseño Command.
*/
class UserInput {
private:
    string nombreArchivo; // Nombre del archivo a leer
    string currentSection; // Seccion actual
    Graph* g;   // Grafo que se va a construir
    bool exit;  // Bandera para salir del bucle de entrada
    int u, v;   // Nodos de la arista a agregar
    int waiting;    // Contador para esperar cambio de sección
    
public:  

    // Constructor
    UserInput();

    // Método para iniciar la interacción con el usuario
    void menu();

    // Método para procesar el archivo de entrada
    void readFile();

    // Método para procesar una palabra de la línea leída del archivo
    void processWord(string word, int i, int j);

    // Método para elegir el método de aproximación a utilizar
    void elegirMetodo();
};

#endif