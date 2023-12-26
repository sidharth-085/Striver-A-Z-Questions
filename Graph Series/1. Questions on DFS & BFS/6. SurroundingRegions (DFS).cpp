#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Approach : BFS / DFS Method
// Time Complexity: O(V + E)
// Space Complexity: O(V)

// In this question, we have to mark all 'O' which are surrounded by 'X' across
// 4 directions. We know that those 'O' which are on the boundries are not
// surrounded by 'X'. Hence, we will do the DFS/BFS on those boundry 'O'.
// And at last, mark remaining 'O' with 'X' which are not visited or not visited 
// by BFS/DFS.

void bfs(int row, int col, int n, int m, vector<vector<char>> &board, vector<vector<int>> &visited) {
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

            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && visited[nRow][nCol] == 0 && board[nRow][nCol] == 'O') {
                visited[nRow][nCol] = 1;
                q.push({nRow, nCol});
            }
        }
    }
}

void dfs(int row, int col, int n, int m, vector<vector<char>> &board, vector<vector<int>> &visited) {
    visited[row][col] = 1;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int i=0; i<4; i++) {
        int nRow = row + dx[i];
        int nCol = col + dy[i];

        if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && visited[nRow][nCol] == 0 && board[nRow][nCol] == 'O') {
            dfs(nRow, nCol, n, m, board, visited);
        }
    }
}

void solve(vector<vector<char>> &board) {
    int n = board.size();
    int m = board[0].size();

    vector<vector<int>> visited(n, vector<int>(m, 0));

    for (int col = 0; col < m; col++) {
        if (board[0][col] == 'O' && visited[0][col] == 0) {
            dfs(0, col, n, m, board, visited);
        }

        if (board[n - 1][col] == 'O' && visited[n - 1][col] == 0) {
            dfs(n - 1, col, n, m, board, visited);
        }
    }

    for (int row = 0; row < n; row++) {
        if (board[row][0] == 'O' && visited[row][0] == 0) {
            dfs(row, 0, n, m, board, visited);
        }

        if (board[row][m - 1] == 'O' && visited[row][m - 1] == 0) {
            dfs(row, m - 1, n, m, board, visited);
        }
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (board[row][col] == 'O' && visited[row][col] == 0) {
                board[row][col] = 'X';
            }
        }
    }
}