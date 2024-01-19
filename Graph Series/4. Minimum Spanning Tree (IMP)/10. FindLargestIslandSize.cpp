#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

class DSU {
    public:

    vector<int> size;
    vector<int> parent;

    DSU(int n) {
        size.resize(n, 1);
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

    void unionBySize(int u, int v) {
        int up_u = findUltimateParent(u);
        int up_v = findUltimateParent(v);

        if (up_u == up_v) {
            return;
        }

        if (size[up_u] > size[up_v]) {
            parent[up_v] = up_u;
            size[up_u] = size[up_u] + size[up_v]; 
        }
        else {
            parent[up_u] = up_v;
            size[up_v] = size[up_v] + size[up_u]; 
        }
    }
};

// In this question, we have to find the size of largest island we
// can form by changing just one 0 to 1. So, as its said we have to
// find largest island. We do this in 3 step process:

// 1. Firstly, we find the components using the DSU (union by size)
// because we have to find the island size which can be determined by
// unionBySize. Now, we go to every cell of the grid which has 1, 
// we check to  its adjacent 4 directions and if we get 1 again, means
// these are connected and should make a component. So, we union 
// the current node = (row * n) + col and newNode = (newRow * n) + newCol.
// Then, we do this for every cell and find the components.

// 2. Secondly, after getting all the components and their sizes 
// stored in size vector of DSU. We go to the every cell which has
// value 0, because we have to convert one 0 to 1. And, at every cell
// which is 0, we check to all 4 directions again and if we found
// 1, means we get the component at that direction. Therefore, when
// we get 1 in any of the four direction we check their ultimate
// parent because it can be the case that the 1 we get in adjacent 
// cell is not a parent cell of that component. And, after getting
// ultimate parent we store it in the set because we have to maintain
// unique parents (there maybe a case that same component is surrounding
// from more than 1 direction), which makes wrong results so we take
// only unique ultimate parents so that we can add the size of that
// components with 1 (because we have converted that current 0 cell 
// to 1) and check is it the largest or not.

// 3. Lastly, after doing all this we can check that for all components
// if the size of any component can be bigger than the value stored 
// in the ans because there can be a case where, after converting 
// 0 to 1, we are getting small value which is actually exists in grid.
// The case can be also when all cell values are 1 and when we are
// searching for 0 in the second step, we will not get any answer.
// Thats why, we are keeping this check so that maximum size of island
// is taken into answer. 

// Time Complexity: O(N * N * a(N))
// Space Complexity: O(N * N)

bool isSafe(int row, int col, int n) {
    return (row >= 0 && row < n && col >= 0 && col < n);
}

int largestIsland(vector<vector<int>>& grid) {
    int n = grid.size();

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    DSU dsu(n * n);

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (grid[row][col] == 0) {
                continue;
            }

            for (int i=0; i<4; i++) {
                int newRow = row + dx[i];
                int newCol = col + dy[i];

                if (isSafe(newRow, newCol, n) == true && grid[newRow][newCol] == 1) {
                    int node = (row * n) + col;
                    int newNode = (newRow * n) + newCol;

                    dsu.unionBySize(node, newNode);
                }
            }
        }
    }

    int largestIslandSize = 0;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (grid[row][col] == 1) {
                continue;
            }

            unordered_set<int> set;

            for (int i=0; i<4; i++) {
                int newRow = row + dx[i];
                int newCol = col + dy[i];

                if (isSafe(newRow, newCol, n) == true && grid[newRow][newCol] == 1) {
                    int newNode = (newRow * n) + newCol;

                    int newNode_up = dsu.findUltimateParent(newNode);

                    set.insert(newNode_up);
                }
            }

            int islandSize = 0;

            for (auto &node : set) {
                islandSize = islandSize + dsu.size[node];
            }

            largestIslandSize = max(largestIslandSize, islandSize + 1);
        }
    }

    for (int node = 0; node < (n * n); node++) {
        largestIslandSize = max(largestIslandSize, dsu.size[node]);
    }

    return largestIslandSize;
}