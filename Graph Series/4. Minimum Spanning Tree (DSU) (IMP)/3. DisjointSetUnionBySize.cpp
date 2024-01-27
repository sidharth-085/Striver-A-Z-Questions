#include <iostream>
#include <vector>
using namespace std;

// In this method of DSU, we use two functions. First is findParent which
// is used to find the ultimate parent of a vertex using parent vector.
// Basically, we update temp variable as parent of a vertex and continue
// till we reach at parent of a vertex is same as vertex which represents
// it is the ultimate parent. Secondly, union function which joins the 
// nodes on the basis of size and mark them parents of each other depends
// on which has highest size. The ultimate parent having more size, becomes
// parent of other.

// Time Complexity: O(E * a(N))
// where a(N) is Ackermann function
// Space Complexity: O(N)

class DSU {
    vector<int> size;
    vector<int> parent;

    public: 

    DSU(int n) {
        size.resize(n, 1);
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

    bool unionBySize(int u, int v) {
        int up_u = findParent(u);
        int up_v = findParent(v);

        if (up_u == up_v) {
            return false;
        }

        if (size[up_u] > size[up_v]) {
            parent[up_v] = up_u;
            size[up_u] = size[up_u] + size[up_v];
        }
        else if (size[up_u] < size[up_v]) {
            parent[up_u] = up_v;
            size[up_v] = size[up_v] + size[up_u];
        }
        else {
            parent[up_u] = up_v;
            size[up_u] = size[up_u] + size[up_v];
        }

        return true;
    }
};