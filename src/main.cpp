#include <iostream>
#include <fstream>
#include <chrono>
#include <windows.h>
#include "graph.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc < 2) {
        cout << "Uso: ./eda_pf <modulo>" << endl;
        cout << "  A   → analisis estructural" << endl;
        cout << "  B   → consultas Dijkstra" << endl;
        cout << "  C   → subgrafo y MST" << endl;
        cout << "  ALL → ejecutar todos y generar tiempos.csv" << endl;
        return 1;
    }

    Grafo g;
    cout << "Cargando grafo..." << endl;
    auto t0 = chrono::high_resolution_clock::now();
    cargarGrafo("data/roadNet-PA.txt", g);
    auto t1 = chrono::high_resolution_clock::now();
    double t_carga = chrono::duration<double, milli>(t1 - t0).count();
    cout << "Grafo cargado: " << g.num_nodos 
         << " nodos, " << g.num_aristas << " aristas" << endl;

    string modulo = argv[1];

    if (modulo == "A") {
        analisisEstructural(g);
    } else if (modulo == "B") {
        runQueries(g);
    } else if (modulo == "C") {
        construirSubgrafo(g);
    } else if (modulo == "ALL") {

        
        auto tA1 = chrono::high_resolution_clock::now();
        analisisEstructural(g);
        auto tA2 = chrono::high_resolution_clock::now();
        double t_A = chrono::duration<double, milli>(tA2 - tA1).count();

        
        auto tB1 = chrono::high_resolution_clock::now();
        runQueries(g);
        auto tB2 = chrono::high_resolution_clock::now();
        double t_B = chrono::duration<double, milli>(tB2 - tB1).count();

        
        auto tC1 = chrono::high_resolution_clock::now();
        construirSubgrafo(g);
        auto tC2 = chrono::high_resolution_clock::now();
        double t_C = chrono::duration<double, milli>(tC2 - tC1).count();

        
        ofstream csv("results/tiempos.csv");
        csv << "modulo,operacion,tiempo_ms\n";
        csv << "general,carga_grafo," << t_carga << "\n";
        csv << "A,analisis_estructural_completo," << t_A << "\n";
        csv << "B,consultas_dijkstra_bfs_completo," << t_B << "\n";
        csv << "C,subgrafo_mst_dag_completo," << t_C << "\n";
        csv.close();

        cout << "\n===== TIEMPOS TOTALES =====" << endl;
        cout << "Carga grafo: " << t_carga << " ms" << endl;
        cout << "Modulo A:    " << t_A << " ms" << endl;
        cout << "Modulo B:    " << t_B << " ms" << endl;
        cout << "Modulo C:    " << t_C << " ms" << endl;
        cout << "Tiempos guardados en results/tiempos.csv" << endl;

    } else {
        cout << "Modulo no reconocido." << endl;
    }

    return 0;
}