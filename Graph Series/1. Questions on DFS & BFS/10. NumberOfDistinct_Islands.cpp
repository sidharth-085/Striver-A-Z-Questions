#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

// Approach : BFS/DFS Method
// Time Complexity: O(V + E) or O(M * N)
// Space Complexity: O(V) or O(M * N)

// In this question, we have to find distinct islands (distinct islands are 
// those islands which are not same when we translate them not rotation or
// reflection).

// So here, we have used a vector storing the pair of row and col distances 
// from source of the island. And, we store these vectors in set to avoid 
// duplicates of that vector which represents the distinct islands number.

void bfs(int row, int col, int sRow, int sCol, int n, int m, int **grid, vector<pair<int, int>> &path, vector<vector<int>> &visited) {
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

            if (nRow >= 0 && nCol >= 0 && nRow < n && nCol < m && visited[nRow][nCol] == 0 && grid[nRow][nCol] == 1) {
                visited[nRow][nCol] = 1;
                
                path.push_back({nRow - sRow, nCol - sCol});

                q.push({nRow, nCol});
            }
        }
    }
}

void dfs(int row, int col, int sRow, int sCol, int n, int m, int **grid, vector<pair<int, int>> &path, vector<vector<int>> &visited) {
    visited[row][col] = 1;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int i=0; i<4; i++) {
        int nRow = row + dx[i];
        int nCol = col + dy[i];

        if (nRow >= 0 && nCol >= 0 && nRow < n && nCol < m && visited[nRow][nCol] == 0 && grid[nRow][nCol] == 1) {
            path.push_back({nRow - sRow, nCol - sCol});

            dfs(nRow, nCol, sRow, sCol, n, m, grid, path, visited);
        }
    }
}

int distinctIslands(int** grid, int n, int m) {
    vector<vector<int>> visited(n, vector<int>(m, 0));

    set<vector<pair<int, int>>> st;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (grid[row][col] == 1 && visited[row][col] == 0) {
                vector<pair<int, int>> path;

                dfs(row, col, row, col, n, m, grid, path, visited);

                st.insert(path);
            }
        } 
    }

    return st.size();
}