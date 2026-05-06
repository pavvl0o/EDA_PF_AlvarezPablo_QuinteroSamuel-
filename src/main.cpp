#include <iostream>
#include <windows.h>
#include "graph.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc < 2) {
        cout << "Uso: ./eda_pf <modulo>" << endl;
        cout << "  A → analisis estructural" << endl;
        cout << "  B → consultas Dijkstra" << endl;
        cout << "  C → subgrafo y MST" << endl;
        return 1;
    }


    Grafo g;
    cout << "Cargando grafo..." << endl;
    cargarGrafo("data/roadNet-PA.txt", g);
    cout << "Grafo cargado: " << g.num_nodos 
         << " nodos, " << g.num_aristas << " aristas" << endl;

    string modulo = argv[1];

    if (modulo == "A") {
        analisisEstructural(g);
    } else {
        cout << "Módulo " << modulo << " próximamente..." << endl;
    }

    return 0;
}