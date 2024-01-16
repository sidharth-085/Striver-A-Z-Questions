#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int first;
    int second;
    int weight;
};

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
            rank[up_u]++;
        }

        return true;
    }
};

// In Kruskal's Algorithm, we use the DSU to select the smallest edges first
// and union them. If the edge we get, have the ultimate parents as same
// it means they belongs to same component. Hence, we need the smallest 
// edges to make MST, but if we get the edge having same ultimate parents
// joining again with MST which is already taken with lower weight because
// initially we sorted the newEdges.

// Steps:

// 1. Firstly, arrange the given graph in edges form in which topmost value
// is weight so that we can sort according to weight of the edges.

// 2. We have to select the minimum edges first to make the MST, but when
// ultimate parents are same, means these vertex belongs to same component.
// Thats why, we skip it because we dont need extra edges in component.

// 3. Finally, after continously doing this process

// Time Complexity: O(E Log E + E)
// Space Complexity: O(V)

int kruskalMST1(int n, vector<vector<int>> &edges) {
    vector<pair<int, pair<int, int>>> newEdges;

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int weight = edge[2];

        newEdges.push_back({weight, {first, second}});
    }

    sort(newEdges.begin(), newEdges.end());

    DSU dsu = DSU(n + 1);

    int count = 0; int mstWeight = 0;
    
    for (auto &edge : newEdges) {
        int weight = edge.first;
        int first = edge.second.first;
        int second = edge.second.second;

        if (dsu.unionByRank(first, second) == true) {
            count++;
            mstWeight = mstWeight + weight;
        }

        if (count == n - 1) {
            break;
        }
    }

    return mstWeight;
}

vector<Edge> kruskalMST2(int n, vector<vector<int>> &edges) {
    vector<pair<int, pair<int, int>>> newEdges;

    for (auto &edge : edges) {
        int first = edge[0];
        int second = edge[1];
        int weight = edge[2];

        newEdges.push_back({weight, {first, second}});
    }

    sort(newEdges.begin(), newEdges.end());

    DSU dsu(n + 1);

    int count = 0; int mstWeight = 0;

    vector<Edge> mst;
    
    for (auto &edge : newEdges) {
        int weight = edge.first;
        int first = edge.second.first;
        int second = edge.second.second;

        if (dsu.unionByRank(first, second) == true) {
            mstWeight = mstWeight + weight;
            count++;
            mst.push_back({first, second, weight});
        }

        if (count == n - 1) {
            break;
        }
    }

    return mst;
}
