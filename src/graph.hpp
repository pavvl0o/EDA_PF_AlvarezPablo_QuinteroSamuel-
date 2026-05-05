#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

struct Grafo {
    vector<vector<pair<int,int>>> adj;  
    unordered_map<int,int> id_map;   
    int num_nodos;
    long long num_aristas;
};

void cargarGrafo(const string& archivo, Grafo& g);
vector<int> bfs(int inicio, const Grafo& g);
void analisisEstructural(const Grafo& g);

#endif