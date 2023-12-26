#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Approach : BFS / DFS Method
// Time Complexity: O(V + E)
// Space Complexity: O(V)

// Same as Previous Question

void bfs(int row, int col, int n, int m, vector<vector<int>> &grid, vector<vector<int>> &visited) {
    visited[row][col] = 1;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    queue<pair<int, int>> q;
    q.push({row, col});

    while (!q.empty()) {
        pair<int, int> top = q.front();
        q.pop();

        int tRow = top.first;
        int tCol = top.second;

        for (int i=0; i<4; i++) {
            int nRow = tRow + dx[i];
            int nCol = tCol + dy[i];

            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && visited[nRow][nCol] == 0 && grid[nRow][nCol] == 1) {
                visited[nRow][nCol] = 1;
                q.push({nRow, nCol});
            }
        }
    }
}

void dfs(int row, int col, int n, int m, vector<vector<int>> &grid, vector<vector<int>> &visited) {
    visited[row][col] = 1;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int i=0; i<4; i++) {
        int nRow = row + dx[i];
        int nCol = col + dy[i];

        if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && grid[nRow][nCol] == 1 && visited[nRow][nCol] == 0) {
            dfs(nRow, nCol, n, m, grid, visited);
        }
    }
}

int numEnclaves(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> visited(n, vector<int>(m, 0));

    for (int row = 0; row < n; row++) {
        if (grid[row][0] == 1 && visited[row][0] == 0) {
            dfs(row, 0, n, m, grid, visited);
        }

        if (grid[row][m - 1] == 1 && visited[row][m - 1] == 0) {
            dfs(row, m - 1, n, m, grid, visited);
        }
    }

    for (int col = 0; col < m; col++) {
        if (grid[0][col] == 1 && visited[0][col] == 0) {
            dfs(0, col, n, m, grid, visited);
        }

        if (grid[n - 1][col] == 1 && visited[n - 1][col] == 0) {
            dfs(n - 1, col, n, m, grid, visited);
        }
    }

    int count = 0;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (grid[row][col] == 1 && visited[row][col] == 0) {
                count++;
            } 
        }
    }

    return count;
}