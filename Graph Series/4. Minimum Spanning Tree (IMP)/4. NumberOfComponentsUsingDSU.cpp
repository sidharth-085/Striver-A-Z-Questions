#include <iostream>
#include <vector>
using namespace std;

class DSU {
    vector<int> rank;
    vector<int> parent;

    public: 

    DSU(int n) {
        rank.resize(n, 0);
        parent.resize(n);
        
        for (int i=0; i<n; i++) {
            parent[i] = i;
        }
    }

    int findParent(int vertex) {
        int temp = vertex;

        while (temp != parent[temp]) {
            temp = parent[temp];
        }

        return parent[vertex] = temp;
    }

    bool unionByRank(int u, int v) {
        int up_u = findParent(u);
        int up_v = findParent(v);

        if (up_u == up_v) {
            return false;
        }

        if (rank[up_u] > rank[up_v]) {
            parent[up_v] = up_u;
        }
        else if (rank[up_u] < rank[up_v]) {
            parent[up_u] = up_v;
        }
        else {
            parent[up_u] = up_v;
            rank[up_v]++;
        }

        return true;
    }
};

// Time Complexity: O(E * a(V))
// Space Complexity: O(V)

int numberOfComponents(vector<vector<int>> &edges, int n) {
    DSU dsu(n);

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];

        dsu.unionByRank(first, second);
    }

    int numComponents = 0;

    for (int vertex = 0; vertex < n; vertex++) {
        if (dsu.findParent(vertex) == vertex) {
            numComponents++;
        }
    }

    return numComponents;
}