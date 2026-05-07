#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "graph.hpp"
using namespace std;

void analisisEstructural(const Grafo& g) {

    cout << "\n===== ANALISIS ESTRUCTURAL =====" << endl;
    cout << "Nodos:             " << g.num_nodos << endl;
    cout << "Aristas:           " << g.num_aristas << endl;
    cout << "Grado promedio:    " 
         << (double)(g.num_aristas * 2) / g.num_nodos << endl;
 
    int nodo_mayor = 0;
    int grado_max  = 0;
    for (int i = 0; i < g.num_nodos; i++) {
        if ((int)g.adj[i].size() > grado_max) {
            grado_max  = g.adj[i].size();
            nodo_mayor = i;
        }
    }
    cout << "Nodo mayor grado:  indice=" << nodo_mayor 
         << " grado=" << grado_max << endl;
 
    cout << "\nCalculando diametro (BFS)..." << endl;
    auto t1 = chrono::high_resolution_clock::now();
    vector<int> dist = bfs(nodo_mayor, g);
    auto t2 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t2 - t1).count();

    int diametro  = 0;
    int alcanzados = 0;
    for (int d : dist) {
        if (d != -1) { alcanzados++; diametro = max(diametro, d); }
    }
    cout << "Diametro aprox:    " << diametro 
         << " (SNAP: 782)" << endl;
    cout << "Nodos alcanzados:  " << alcanzados 
         << " (SNAP: 1087562)" << endl;
    cout << "Tiempo BFS:        " << ms << " ms" << endl;
 
    cout << "\nContando componentes conexas..." << endl;
    vector<bool> visitado(g.num_nodos, false);
    int componentes = 0;
    int mayor_comp  = 0;

    for (int i = 0; i < g.num_nodos; i++) {
        if (!visitado[i]) {
            componentes++;
            vector<int> d = bfs(i, g);
            int tam = 0;
            for (int x = 0; x < g.num_nodos; x++) {
                if (d[x] != -1) {
                    visitado[x] = true;
                    tam++;
                }
            }
            mayor_comp = max(mayor_comp, tam);
        }
    }
    cout << "Componentes:       " << componentes << endl;
    cout << "Mayor componente:  " << mayor_comp 
         << " (SNAP: 1087562)" << endl;
 
    ofstream out("results/analisis_estructural.txt");
    out << "===== ANALISIS ESTRUCTURAL =====\n";
    out << "Nodos:            " << g.num_nodos << "\n";
    out << "Aristas:          " << g.num_aristas << "\n";
    out << "Grado promedio:   " 
        << (double)(g.num_aristas * 2) / g.num_nodos << "\n";
    out << "Nodo mayor grado: indice=" << nodo_mayor 
        << " grado=" << grado_max << "\n";
    out << "Diametro aprox:   " << diametro << "\n";
    out << "Nodos alcanzados: " << alcanzados << "\n";
    out << "Componentes:      " << componentes << "\n";
    out << "Mayor componente: " << mayor_comp << "\n";
    out.close();
    cout << "\nResultados guardados en results/analisis_estructural.txt" << endl;
}