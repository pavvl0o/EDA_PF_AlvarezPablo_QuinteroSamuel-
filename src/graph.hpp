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

int bfs(int inicio, int destino, const Grafo& g, int& nodesExplored);
vector<int> bfs(int inicio, const Grafo& g);

void analisisEstructural(const Grafo& g);

int dijkstra(int inicio, int destino, const Grafo& g,
             vector<int>& prev, int& nodesExplored);
vector<int> buildPath(int inicio, int destino, vector<int>& prev);
void runQueries(const Grafo& g);

void construirSubgrafo(const Grafo& g);

#endif