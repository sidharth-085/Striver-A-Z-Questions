#include <iostream>
#include <vector>
using namespace std;

class DSU {
    public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        rank.resize(n, 0);
        parent.resize(n);

        for (int i=0; i<n; i++) {
            parent[i] = i;
        }
    }

    int findUltimateParent(int vertex) {
        int curr = vertex;
        while (curr != parent[curr]) {
            curr = parent[curr];
        }

        return parent[vertex] = curr;
    }

    bool unionByRank(int u, int v) {
        int up_u = findUltimateParent(u);
        int up_v = findUltimateParent(v);

        if (up_u == up_v) {
            return false;
        }

        if (rank[up_u] < rank[up_v]) {
            parent[up_u] = up_v;
        }
        else if (rank[up_u] > rank[up_v]) {
            parent[up_v] = up_u;
        }
        else {
            parent[up_v] = up_u;
            rank[up_u]++;
        }

        return true;
    }    
};

// In this problem, we have some connections between computers represented
// by 0 to n - 1. Now, we have connections array which represents the network
// between two computers as (ai, bi). So, we have to find the minimum 
// number of times we have to remove a network from given connections 
// so that all computers are connected.

// So, as we know we have some extra edges which are not essential because
// the network can be connected directly or indirectly. So, firstly we count
// number of extra edges with the help of DSU. And, after that as we know
// if we need to connect n components together, we need minimum of n - 1
// connections. Hence, if we have extra edges or connections from given
// connections equal to n - 1 or more, we can connect the components and 
// make connected network. But, if extra edges are less than n - 1, it is
// not possible to connect all components, hence return -1.

// Time Complexity: (E * a(V) + V)
// Space Complexity: O(V)

int makeConnected(int n, vector<vector<int>>& connections) {
    DSU dsu(n);

    int extraEdges = 0;
    
    for (auto &connection : connections) {
        int first = connection[0];
        int second = connection[1];

        if (dsu.unionByRank(first, second) == false) {
            extraEdges++;
        }
    }

    int numComponents = 0;

    for (int vertex = 0; vertex < n; vertex++) {
        if (dsu.parent[vertex] == vertex) {
            numComponents++;
        }
    }

/*
    for (int vertex = 0; vertex < n; vertex++) {
        if (dsu.findUltimateParent(vertex) == vertex) {
            numComponents++;
        }
    }    
    
*/

    if (extraEdges >= numComponents - 1) {
        return numComponents - 1;
    }

    return -1;
}