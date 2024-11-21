#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

#define INF 1e9
#define N 10

// Aresta
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Gera um grafo esparso
vector<Edge> generateSparseGraph(int vertices) {
    vector<Edge> edges;
    
    for (int i = 0; i < vertices - 1; i++) {
        int weight = rand() % 100 + 1;
        edges.push_back({i, i + 1, weight});
    }

    return edges;
}

// Gera um grafo denso
vector<Edge> generateDenseGraph(int vertices) {
    vector<Edge> edges;

    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            int weight = rand() % 100 + 1;
            edges.push_back({i, j, weight});
        }
    }

    return edges;
}

// Algoritmos usados
namespace {
    static int kruskal(int vertices, vector<Edge>& edges) {
        vector<int> parent(vertices);
        int mstWeight = 0;
        
        function<int(int)> find = [&](int v) {
            if (v == parent[v]) return v;
            return parent[v] = find(parent[v]);
        };
        auto unite = [&](int u, int v) {
            parent[find(u)] = find(v);
        };

        for (int i = 0; i < vertices; i++) parent[i] = i;

        sort(edges.begin(), edges.end());
        for (const Edge& edge : edges) {
            if (find(edge.u) != find(edge.v)) {
                mstWeight += edge.weight;
                unite(edge.u, edge.v);
            }
        }
        return mstWeight;
    }

    static int prim(int vertices, vector<Edge>& edges) {
        vector<vector<pair<int, int>>> adj(vertices);
        vector<bool> visited(vertices, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({ 0, 0 });
        int mstWeight = 0;

        for (const Edge& edge : edges) {
            adj[edge.u].push_back({ edge.v, edge.weight });
            adj[edge.v].push_back({ edge.u, edge.weight });
        }

        while (!pq.empty()) {
            auto [weight, u] = pq.top();
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;
            mstWeight += weight;

            for (auto [v, w] : adj[u]) {
                if (!visited[v]) pq.push({ w, v });
            }
        }

        return mstWeight;
    }
}

int main() {
    srand(time(0));
    
    vector<int> vertices = { 10, 100, 500, 1000, 2000, 5000, 10000 };
    ofstream file("comparacao.csv");

    file << "Algoritmo,";
    for (int v : vertices) file << to_string(v) << ",";

    file << endl << "Prim Esparso,";
    for (int n : vertices) {
        double mean = 0.0;

        for (int i = 0; i < N; i++) {
            vector<Edge> sparseGraph = generateSparseGraph(n);
            
            auto start = high_resolution_clock::now();
            prim(n, sparseGraph);
            auto end = high_resolution_clock::now();

            mean += duration<double, milli>(end - start).count() / N;
            cout << mean << ", ";
        }
        cout << endl;
        file << to_string(mean) << ",";
    }

    file << endl << "Prim Denso,";
    for (int n : vertices) {
        double mean = 0.0;

        for (int i = 0; i < N; i++) {
            vector<Edge> sparseGraph = generateDenseGraph(n);
            
            auto start = high_resolution_clock::now();
            prim(n, sparseGraph);
            auto end = high_resolution_clock::now();

            mean += duration<double, milli>(end - start).count() / N;
            cout << mean << ", ";
        }
        cout << endl;
        mean /= N;

        file << to_string(mean) << ",";
    }

    file << endl << "Kruskal Esparso,";
    for (int n : vertices) {
        double mean = 0.0;

        for (int i = 0; i < N; i++) {
            vector<Edge> sparseGraph = generateSparseGraph(n);
            
            auto start = high_resolution_clock::now();
            kruskal(n, sparseGraph);
            auto end = high_resolution_clock::now();

            mean += duration<double, milli>(end - start).count() / N;
            cout << mean << ", ";
        }
        cout << endl;
        mean /= N;

        file << to_string(mean) << ",";
    }

    file << endl << "Kruskal Denso,";
    for (int n : vertices) {
        double mean = 0.0;

        for (int i = 0; i < N; i++) {
            vector<Edge> sparseGraph = generateDenseGraph(n);
            
            auto start = high_resolution_clock::now();
            kruskal(n, sparseGraph);
            auto end = high_resolution_clock::now();

            mean += duration<double, milli>(end - start).count() / N;
            cout << mean << ", ";
        }
        cout << endl;
        mean /= N;

        file << to_string(mean) << ",";
    }

    file.close();
    return 0;
}
