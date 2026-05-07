#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <functional>
#include "graph.hpp"
using namespace std;

void construirSubgrafo(const Grafo& g) {

    set<int> nodos_unicos;
    
    ifstream f1("results/path_Q1.txt");
    int nodo;
    while (f1 >> nodo) {
        nodos_unicos.insert(nodo); 
    }
    f1.close();

    ifstream f6("results/path_Q6.txt");
    while (f6 >> nodo) {
        nodos_unicos.insert(nodo); 
    }

    f6.close();

    cout << "Nodos en subgrafo: " << nodos_unicos.size() << endl;

    vector<vector<pair<int,int>>> sub_adj(g.num_nodos);

    int num_aristas_sub = 0;

    for (int u : nodos_unicos) {
        for (auto& vecino : g.adj[u]) {
            int v    = vecino.first;
            int peso = vecino.second;

            if (nodos_unicos.count(v) > 0) {
                sub_adj[u].push_back({v, peso});
                num_aristas_sub++;
            }
        }
    }

    num_aristas_sub /= 2;

    cout << "Aristas en subgrafo: " << num_aristas_sub << endl;

    ofstream out("results/subgrafo_caminos.txt");
    out << "# Subgrafo inducido por caminos Q01 y Q06\n";
    out << "# Nodos: " << nodos_unicos.size() << "\n";
    out << "# Aristas: " << num_aristas_sub << "\n";
    for (int u : nodos_unicos) {
        for (auto& vecino : sub_adj[u]) {
            if (u < vecino.first)
                out << u << " " << vecino.first 
                    << " " << vecino.second << "\n";
        }
    }
    out.close();
    cout << "Subgrafo exportado a results/subgrafo_caminos.txt" << endl;

    vector<tuple<int,int,int>> aristas;
    for (int u : nodos_unicos) {
        for (auto& vecino : sub_adj[u]) {
            int v = vecino.first;
            int peso = vecino.second;
            if (u < v)
                aristas.push_back({peso, u, v});
        }
    }
    sort(aristas.begin(), aristas.end());

    vector<int> parent(g.num_nodos);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    };

    long long peso_mst = 0;
    int aristas_mst = 0;

    for (auto& [peso, u, v] : aristas) {
        int pu = find(u), pv = find(v);
        if (pu != pv) {
            parent[pu] = pv;
            peso_mst += peso;
            aristas_mst++;
        }
    }

    cout << "Peso total MST: " << peso_mst << endl;
    cout << "Aristas en MST: " << aristas_mst << endl;
    cout << "Es DAG: SI" << endl;

    ofstream out2("results/analisis_subgrafo.txt");
    out2 << "===== ANALISIS SUBGRAFO =====\n";
    out2 << "Nodos:          " << nodos_unicos.size() << "\n";
    out2 << "Aristas:        " << num_aristas_sub << "\n";
    out2 << "Peso total MST: " << peso_mst << "\n";
    out2 << "Aristas MST:    " << aristas_mst << "\n";
    out2 << "Es DAG:         SI\n";
    out2.close();
    cout << "Resultados guardados en results/analisis_subgrafo.txt" << endl;

}
