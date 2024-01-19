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