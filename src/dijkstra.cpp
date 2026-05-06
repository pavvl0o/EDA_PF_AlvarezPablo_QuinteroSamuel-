#include <queue>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <climits>
#include <iostream>
#include "graph.hpp"
using namespace std;

int dijkstra(int inicio, int destino, const Grafo& g,
             vector<int>& prev, int& nodesExplored) {

    int n = g.adj.size();
        vector<int> dist(n, INT_MAX);
        prev.assign(n, -1);

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[inicio] = 0;
        pq.push({0, inicio});
        nodesExplored = 0;

    while (!pq.empty()) {

        auto [d, actual] = pq.top();
        pq.pop();

        if (d > dist[actual]) continue;

        nodesExplored++;

        if (actual == destino) break;

        for (auto& vecino : g.adj[actual]) {
            int v    = vecino.first;
            int peso = vecino.second;

            if (dist[actual] + peso < dist[v]) {
                dist[v] = dist[actual] + peso;
                prev[v] = actual;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[destino];
}

vector<int> buildPath(int inicio, int destino, vector<int>& prev) {
    vector<int> path;

    for (int at = destino; at != -1; at = prev[at])
        path.push_back(at);

    reverse(path.begin(), path.end());

    if (path.empty() || path[0] != inicio) return {};
    return path;
}

void runQueries(const Grafo& g) {

    vector<pair<int,int>> queries = {
        {1, 500000}, {100, 1000000}, {50000, 750000},
        {200000, 800000}, {300000, 100000}, {1, 1087562},
        {500000, 1}, {250000, 600000}, {10000, 900000},
        {400000, 150000}
    };

    ofstream file("results/consultas_p2p.csv");
    file << "consulta,origen,destino,dist_dijkstra,saltos_bfs,"
         << "nodos_dijkstra,nodos_bfs,t_dijkstra_ms,t_bfs_ms\n";

    for (int i = 0; i < (int)queries.size(); i++) {

        int origen  = queries[i].first;
        int destino = queries[i].second;

        // Validar que los nodos existen
        if (g.id_map.count(origen) == 0 || g.id_map.count(destino) == 0) {
            cout << "Q" << (i+1) << ": nodo no existe en el grafo" << endl;
            file << "Q" << (i+1) << "," << origen << "," << destino
                 << ",-1,-1,0,0,0,0\n";
            continue;
        }

        // Traducir IDs originales a indices internos
        int origen_idx  = g.id_map.at(origen);
        int destino_idx = g.id_map.at(destino);

        int nodesDij = 0, nodesBfs = 0;
        vector<int> prev;

        auto t1 = chrono::high_resolution_clock::now();
        int distDij = dijkstra(origen_idx, destino_idx, g, prev, nodesDij);
        auto t2 = chrono::high_resolution_clock::now();

        auto t3 = chrono::high_resolution_clock::now();
        int distBfs = bfs(origen_idx, destino_idx, g, nodesBfs);
        auto t4 = chrono::high_resolution_clock::now();

        double t_d = chrono::duration<double, milli>(t2 - t1).count();
        double t_b = chrono::duration<double, milli>(t4 - t3).count();

        // Reconstruir camino para Q01 y Q06
        if (i == 0 || i == 5) {
            vector<int> path = buildPath(origen_idx, destino_idx, prev);
            ofstream pathFile("results/path_Q" + to_string(i+1) + ".txt");
            for (int node : path)
                pathFile << node << " ";
            pathFile.close();
        }

        cout << "Q" << (i+1) << ": dist=" << (distDij == INT_MAX ? -1 : distDij)
             << " saltos=" << distBfs
             << " t_dij=" << t_d << "ms"
             << " t_bfs=" << t_b << "ms" << endl;

        file << "Q" << (i+1) << ","
             << origen << ","
             << destino << ","
             << (distDij == INT_MAX ? -1 : distDij) << ","
             << distBfs << ","
             << nodesDij << ","
             << nodesBfs << ","
             << t_d << ","
             << t_b << "\n";
    }

    file.close();
    cout << "\nResultados guardados en results/consultas_p2p.csv" << endl;
}