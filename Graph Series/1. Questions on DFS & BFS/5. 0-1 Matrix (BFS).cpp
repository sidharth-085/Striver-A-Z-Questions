#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Approach 1: BFS Method
// Time Complexity: O(V + E)
// Space Complexity: O(V)

// In this problem, we have to find distance of every cell from nearest 0 with
// 4 directions. So, we first push all the zeroes into the queue similar to 
// Rotton Oranges Problem. And, then we applied the trick which is every entry
// popped from the queue, the distance of the entry popped from the queue marked
// as distance of that entry's cell from nearest 0.

vector<vector<int>> updateMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    
    vector<vector<int>> visited(n, vector<int>(m, 0));

    vector<vector<int>> ans(n, vector<int>(m, 0));

    queue<pair<pair<int, int>, int>> q;

    for (int row = 0; row < n; row++) {
        for(int col = 0; col < m; col++) {
            if (grid[row][col] == 0) {
                q.push({{row, col}, 0});
                visited[row][col] = 1;
            }
        }
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto top = q.front();
        q.pop();

        int tRow = top.first.first;
        int tCol = top.first.second;
        int tDist = top.second;

        ans[tRow][tCol] = tDist;

        for (int i=0; i<4; i++) {
            int nRow = tRow + dx[i];
            int nCol = tCol + dy[i];

            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && visited[nRow][nCol] == 0) {
                visited[nRow][nCol] = 1;
                q.push({{nRow, nCol}, tDist + 1});
            }
        }
    }

    return ans;
}