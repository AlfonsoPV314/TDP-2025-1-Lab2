#include "UserInput.h"

// CLASS CURRENTLY BROKEN I HAVE TO FIX IT ACCORDING TO THE STRATEGY DESIGN PATTERN


UserInput::UserInput() : exit(false), nombreArchivo(""), currentSection(""), g(nullptr), waiting(0) {}

void UserInput::menu(){
    while(!exit){
        cout << endl << "============= MENU =============" << endl;
        cout << "1. Leer archivo" << endl;
        cout << "2. Visualizar grafo" << endl;
        cout << "3. Encontrar aproximacion de arbol minimo de Stainer" << endl;
        cout << "4. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Seleccione una opcion (numero entre 1 y 4): ";
        int option;
        cin >> option;

        // Verificar si la entrada es válida
        if (cin.fail() || option < 1 || option > 4) {
            cin.clear();  // Limpia el flag de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta el resto de la entrada
            cout << "Entrada invalida. Por favor, ingrese un numero entre 1 y 4." << endl;
            continue;
        }

        switch(option){
            case 1:
                cout << "Ingrese el nombre del archivo (ingrese 0 para regresar al menu): ";
                cin >> this->nombreArchivo;
                if (this->nombreArchivo == "0") {
                    cout << "Regresando al menu..." << endl;
                    break;
                }
                readFile();
                break;

            case 2:
                if (g != nullptr) {
                    cout << "Grafo: " << endl;
                    g->printGraph();
                } else {
                    cout << "No hay grafo para mostrar." << endl;
                }
                break;

            case 3:
                elegirMetodo();
                break;

            case 4:
                cout << "Saliendo..." << endl;
                exit = true;
                break;

            default:
                cout << "Error fatal. Abortando..." << endl;
                return;
        }
    }
}

void UserInput::readFile() {
    ifstream file(this->nombreArchivo);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }
    string line;
    int i = 0, j = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        // Procesar la línea leída
        while(iss){
            string word;
            iss >> word;
            if(iss){
                // Procesar la palabra leída
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                if(word == "section"){
                    //cout << "[UserInput::readFile] Seccion ahora es: [waiting]" << endl;
                    currentSection = "waiting";
                    i = 0;
                }
                else if (word == "eof"){
                    cout << "Archivo [" << nombreArchivo << "] leido y procesado correctamente." << endl;
                    file.close();
                    //cout << "[UserInput::readFile] Fin de archivo alcanzado." << endl;
                    return;
                }
                else{
                    processWord(word, i, j);
                    j++;
                }
            }
            
        }
        i++;
        j = 0;
    }
    cout << "[WARNING] Linea 'eof' no encontrada. Verifique que su archivo de entrada este en formato DIMACS." << endl;
    cout << "Archivo [" << nombreArchivo << "] leido y procesado." << endl;
    file.close();
}

void UserInput::processWord(string word, int i, int j) {
    cout << "[UserInput::processWord] Procesando palabra: " << word << " con i: " << i << " y j: " << j << endl;
    if(!(currentSection == "graph" || currentSection == "terminals" || currentSection == "waiting" || i >= 0 || j >= 0)) return;
    if (currentSection == "waiting") {
        currentSection = word;
        cout << "[UserInput::processWord] Seccion ahora es: [" << currentSection << "]" << endl;
        waiting = 0;
    } 
    else if (currentSection == "graph") {
        switch (i){
            case 0:
                break;

            case 1:
                if (word == "nodes") {
                    waiting = 1;
                }
                else if (waiting == 1) {
                    int nodes = stoi(word);
                    cout << "[UserInput::processWord] Creando grafo con " << nodes << " nodos." << endl;
                    g = new Graph(nodes);
                    waiting = 0;
                }
                else {
                    cout << "[UserInput::processWord] Palabra no reconocida: " << word << endl;
                }
                break;

        case 2:
            break;

        default:
            switch (j){
                case 0:
                    if ((word == "end")) {
                        return;
                    }
                    break;

                case 1:
                    u = stoi(word) - 1;
                    j++;
                    break;
                    
                case 2:
                    v = stoi(word) - 1;
                    j++;
                    break;

                case 3:
                    g->addEdge(u, v, stod(word));
                    cout << "[UserInput::processWord] Arista [" << u << ", " << v << "] con peso " << word << " agregada." << endl;
                    j = 0;
                    break;
                        
                default:
                    cout << "[UserInput::processWord] Input no reconocido: j = " << j << endl;
                    break;
                }
        
        }
    } 
    else if(currentSection == "terminals") {
        if (word == "t" || word == "end") {
            return;
        }
        if(i > 1){
            g->setTerm(stoi(word) - 1);
            cout << "[UserInput::processWord] Terminal " << word << " agregado." << endl;
        }
    }
    else {
        cout << "[UserInput::processWord] Palabra no reconocida o no relevante: " << word << endl;
    }
}

void UserInput::elegirMetodo() {
    if (g == nullptr) {
        cout << "No hay grafo para procesar." << endl;
        return;
    }
    bool end = false;
    while (!end){
        cout << "Seleccione el metodo a utilizar:" << endl;
        cout << "1. Metodo de Takahashi-Matsuyama" << endl;
        cout << "2. Metodo de Kou-Markowsky-Berman" << endl;
        cout << "3. Metodo APV" << endl;
        cout << "4. Regresar al menu" << endl;
        int option;
        time_point<chrono::high_resolution_clock> start, stop;
        chrono::microseconds duration;
        cout << "Ingrese su opcion (numero entre 1 y 4): ";
        cin >> option;

        // Verificar si la entrada es válida
        if (cin.fail() || option < 1 || option > 4) {
            cin.clear();  // Limpia el flag de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta el resto de la entrada
            cout << "Entrada invalida. Por favor, ingrese un numero entre 1 y 4." << endl;
            continue;
        }

        pair<vector<pair<int, int>>, double> S;
        STP** sol;
        sol = new STP*[3];
        sol[0] = new Takahashi(g);
        sol[1] = new Kou(g);
        sol[2] = new APV(g);
        switch(option){
            case 1:
                cout << "Ejecutando metodo de Takahashi-Matsuyama..." << endl;
                start = high_resolution_clock::now();
                S = sol[0]->solve();
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                sol[0]->print(S);
                if(!sol[0]->verifyValidity(S.first, S.second)) cout << "Oops! El arbol de Steiner encontrado tiene algun error... :^(" << endl;
                cout << "Tiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
                end = true;
                break;
                
            case 2:
                cout << "Ejecutando metodo de Kou-Markowsky-Berman..." << endl;
                start = high_resolution_clock::now();
                S = sol[1]->solve();
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                sol[1]->print(S);
                cout << "Tiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
                if(!sol[1]->verifyValidity(S.first, S.second)) "Oops! El arbol de Steiner encontrado tiene algun error... :^(";
                end = true;
                break;

            case 3:
                cout << "Ejecutando metodo APV..." << endl;
                start = high_resolution_clock::now();
                S = sol[2]->solve();
                stop = high_resolution_clock::now();
                duration = duration_cast<microseconds>(stop - start);
                sol[2]->print(S);
                cout << "Tiempo de ejecucion: " << duration.count() << " microsegundos." << endl;
                if(!sol[2]->verifyValidity(S.first, S.second)) "Oops! El arbol de Steiner encontrado tiene algun error... :^(";
                end = true;
                break;
                
            case 4:
                end = true;
                return;
                
            default:
                cout << "Error fatal. Abortando..." << endl;
                return;
        }
    }
    cout << "Regresando al menu..." << endl;
}