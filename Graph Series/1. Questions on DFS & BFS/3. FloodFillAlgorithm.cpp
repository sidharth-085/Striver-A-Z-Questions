#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Approach 1: DFS Approach
// Time Complexity: O(V + E)
// Space Complexity: O(V)

// Steps:
// 1. Do the general Flood Fill Algorithm with just one addition. 
// 2. Replace only those nodes which has same color as Source Color.

void dfs(int sRow, int sCol, int pColor, int nColor, int n, int m, vector<vector<int>> &image) {
    image[sRow][sCol] =  nColor;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int i=0; i<4; i++) {
        int nRow = sRow + dx[i];
        int nCol = sCol + dy[i];

        if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && image[nRow][nCol] != nColor && image[nRow][nCol] == pColor) {
            dfs(nRow, nCol, pColor, nColor, n, m, image);
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>> &image, int sRow, int sCol, int nColor) {
    int n = image.size();
    int m = image[0].size();

    int pColor = image[sRow][sCol];

    dfs(sRow, sCol, pColor, nColor, n, m, image);

    return image;
}

// Approach 2: BFS Approach
// Time Complexity: O(V + E)
// Space Complexity: O(V)

void bfs(int sRow, int sCol, int pColor, int nColor, int n, int m, vector<vector<int>> &image) {
    image[sRow][sCol] = nColor;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    queue<pair<int, int>> q;
    q.push({sRow, sCol});

    while (!q.empty()) {
        pair<int, int> top = q.front();
        q.pop();

        int tRow = top.first;
        int tCol = top.second;

        for (int i=0; i<4; i++) {
            int nRow = tRow + dx[i];
            int nCol = tCol + dy[i];

            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && image[nRow][nCol] == pColor && image[nRow][nCol] != nColor) {
                image[nRow][nCol] = nColor;
                q.push({nRow, nCol});
            }
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>> &image, int sRow, int sCol, int nColor) {
    int n = image.size();
    int m = image[0].size();

    int pColor = image[sRow][sCol];

    bfs(sRow, sCol, pColor, nColor, n, m, image);

    return image;
}