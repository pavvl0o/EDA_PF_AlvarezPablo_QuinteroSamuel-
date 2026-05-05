#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cstdlib>
#include "graph.hpp"
using namespace std;

void cargarGrafo(const string& archivo, Grafo& g) {

    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "ERROR: No se pudo abrir: " << archivo << endl;
        return;
    }

    string linea;
    int contador = 0;
    srand(42);

    while (getline(file, linea)) {
        if (linea.empty() || linea[0] == '#') continue;

        istringstream ss(linea);
        int u, v;
        ss >> u >> v;

        if (g.id_map.count(u) == 0) {
            g.id_map[u] = contador++;
            g.adj.push_back({});
        }
        if (g.id_map.count(v) == 0) {
            g.id_map[v] = contador++;
            g.adj.push_back({});
        }

        int u_idx = g.id_map[u];
        int v_idx = g.id_map[v];
        int peso = (rand() % 10) + 1;
        g.adj[u_idx].push_back({v_idx, peso});
    }

    g.num_nodos = g.adj.size();
    long long total = 0;
    for (auto& lista : g.adj) total += lista.size();
    g.num_aristas = total / 2;

    file.close();
}