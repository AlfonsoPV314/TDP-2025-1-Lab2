#include <iostream>
#include <string>
// fstream es para entrada y salida desde archivos
#include <fstream>
// manejo de cadenas de texto como si fuesen stream, --> la gracia es que hay deteccion automatica del tipo de dato
#include <sstream>
#include <chrono>
#include <algorithm>
#include "Graph.h"
using namespace std;
using namespace std::chrono;

class UserInput {
private:
    // Atributos
    string nombreArchivo; // Nombre del archivo a leer
    string currentSection; // Seccion actual
    Graph* g;
    bool exit;
    int u, v;
    int waiting;
public:  
    // Entradas: nada
    // Salidas: UserInput nuevo (UserInput)
    // Descripcion: Constructor de un UserInput.
    UserInput();

    // Entradas: nada
    // Salidas: void
    // Descripcion: blabla.
    void menu();
    void readFile();
    void processWord(string word, int i, int j);
    void elegirMetodo();
};