#include <iostream>
#include <vector>
#include <unordered_set>
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

    void unionByRank(int u, int v) {
        int up_u = findParent(u);
        int up_v = findParent(v);

        if (up_u == up_v) {
            return;
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
    }
};

// In this question, we have given coordinates of the stones placed
// in grid. Now, we have to find how many stones we have to remove 
// if there is a stone in same row or column, it should be removed.

// This is little complicated to understand, but there is only one
// trick we apply here. We have the coordinates of the stones placed
// in grid. Firstly, we know that if there is stone sharing same
// row or column, should be removed. Hence, we can look it as component
// in which stones sharing same row or column, makes edges with each 
// other and form component. And, according to this, we know only
// one should remain in that component so, we have to remove 
// (component size - 1) stones from each component made using this
// approach.

// So, following this approach, we take rows and cols as nodes means
// if there is stone at (a, b) it means ath row and bth col is connected
// and for column we start after last row number, it can make this 
// easier for us.

// And, finally, we call DSU union by rank on every stone coordinate
// updated according to last row number. And, union happens with 
// two nodes which is row and col of a stone. And, by doing this we
// get the components having ultimate parents. Now, we only get 
// the number of components according to row and col number. 
// Then, final answer is (total number of stones - number of components).

// Proof: 

// For every component made by sharing of same row and col, we have
// to remove (component size - 1) stones. Assume, there is n components
// then, ((component size - 1) * n) is the final number of stones
// should be deleted. Solving it, (n * component size) = total number
// of stones. Hence, final formula (number of stones - number of components).

// Time Complexity: O(N * a(totalRows + totalCols) + (2 * N))
// where N is total number of stones

// Space Complexity: O(N)

int removeStones(vector<vector<int>>& stones) {
    int maxRow = 0;
    int maxCol = 0;

    int numStones = stones.size();

    for (auto &stone : stones) {
        maxRow = max(maxRow, stone[0]);
        maxCol = max(maxCol, stone[1]);
    }

    int totalRows = maxRow + 1;
    int totalCols = maxCol + 1;

    DSU dsu(totalRows + totalCols);

    unordered_set<int> set;

    for (auto &stone : stones) {
        int nodeRow = stone[0];
        int nodeCol = stone[1] + (maxRow + 1);

        dsu.unionByRank(nodeRow, nodeCol);

        set.insert(nodeRow);
        set.insert(nodeCol);
    }

    int count = 0;

    for (auto &node : set) {
        if (dsu.findParent(node) == node) {
            count++;
        }
    }
    
    return numStones - count;
}