#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// In this method of DSU, we use two functions. First is findParent which
// is used to find the ultimate parent of a vertex using parent vector.
// Basically, we update temp variable as parent of a vertex and continue
// till we reach at parent of a vertex is same as vertex which represents
// it is the ultimate parent. Secondly, union function which joins the 
// nodes on the basis of rank and mark them parents of each other depends
// on which has highest rank. The ultimate parent having more rank, becomes
// parent of other.

// Time Complexity: O(E * a(N))
// where a(N) is Ackermann function
// Space Complexity: O(N)

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