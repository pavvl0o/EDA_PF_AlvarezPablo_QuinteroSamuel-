#include <queue>
#include <vector>
#include "graph.hpp"
using namespace std;

int bfs(int inicio, int destino, const Grafo& g, int& nodesExplored) {

    int n = g.adj.size();
    vector<int> dist(n, -1);
    queue<int> cola;
    nodesExplored = 0;

    dist[inicio] = 0;
    cola.push(inicio);

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        nodesExplored++;

        if (actual == destino) return dist[destino];

        for (auto& vecino : g.adj[actual]) {
            int v = vecino.first;
            if (dist[v] == -1) {
                dist[v] = dist[actual] + 1;
                cola.push(v);
            }
        }
    }

    return -1;
}

vector<int> bfs(int inicio, const Grafo& g) {

    int n = g.adj.size();
    vector<int> dist(n, -1);
    queue<int> cola;
    dist[inicio] = 0;
    cola.push(inicio);

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        for (auto& vecino : g.adj[actual]) {
            int v = vecino.first;
            if (dist[v] == -1) {
                dist[v] = dist[actual] + 1;
                cola.push(v);
            }
        }
    }

    return dist;
}