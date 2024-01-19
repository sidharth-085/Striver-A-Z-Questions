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

// In this question, we have to find the minimum time to so that the
// person starting at (0, 0) can reach to (n - 1, n - 1) in minimum
// time. And given that, the value of the cell which is also depth 
// of the cell and time is same 't'. So, for reaching at any cell
// it takes 't' time, but if the current cell value is more than 
// adjacent value, there is not time addition it can swim if adjacent
// cell value is small. 

// This question is best example of Kruskal's Algorithm. So firstly,
// we sort all the cell values according to the cell value. After 
// sorting, we start iterating on every cell and now we get the 
// value of the cell with row and col. We just, check in all 4 directions
// if the value of adjacent cell (newRow, newCol) is less than current
// cell value (row, col) only then, we can move because there is no
// time required when adjacent cell has less value, so we can go to
// adjacent cell from current then, we can make union of both nodes
// (make node by the help of (row * n) + col). Then, after checking
// all 4 directions and making union of nodes, we just check that 
// the ultimate parent of (0, 0) and (n - 1, n - 1) using DSU are
// same or not, if same it means after the current cell, when we are
// checking for adjacent nodes, we merged the (n - 1, n - 1) with
// current component. So, the answer minTime will be value of current
// cell in grid.

// Time Complexity: (N * N * a(N * N))
// Space Complexity: O(N * N)

int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();

    vector<pair<int, int>> times;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    DSU dsu(n * n);

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            int value = grid[row][col];
            int node = (row * n) + col;

            times.push_back({value, node});
        }
    }

    sort(times.begin(), times.end());

    for (auto &time : times) {
        int value = time.first;
        int node = time.second;

        int row = node / n;
        int col = node % n;

        for (int i=0; i<4; i++) {
            int newRow = row + dx[i];
            int newCol = col + dy[i];

            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && grid[newRow][newCol] < grid[row][col]) {
                int newNode = (newRow * n) + newCol;

                dsu.unionByRank(node, newNode);
            }
        }

        if (dsu.findParent(0) == dsu.findParent((n*n) - 1)) {
            return grid[row][col];
        }
    }

    return 0;
}