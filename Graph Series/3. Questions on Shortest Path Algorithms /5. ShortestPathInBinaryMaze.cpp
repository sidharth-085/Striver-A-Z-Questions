#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(N * N)
// Space Complexity: O(N * N)

// This is the Application of Dijkstra Algorithm. As we use min heap in
// Dijkstra Algorithm but, here we used the queue because we move to every
// edge by one unit distance. So, automatically the front element is low 
// and below, all are bigger than front element. Hence, we can use the
// queue also.

// Also, we used the Dijkstra Method of comparing the distances like 
// tDist + 1 < distance[row][col]. But, we can also use the general BFS, by
// replacing the distance grid with visited grid. And, it gives the same
// answer as this code, but take high time complexity because here we are
// storing the distances in distance vector, but in that case we get the 
// distance by popping out the front element.

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();

    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
        return -1;
    } 

    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, -1, 1, 1, -1, -1, 1};

    vector<vector<int>> distance(n, vector<int>(n, 1e9));
    distance[0][0] = 1;

    queue<pair<pair<int, int>, int>> q;
    q.push({{0, 0}, 1});

    while (!q.empty()) {
        auto top = q.front();
        q.pop();

        int tRow = top.first.first;
        int tCol = top.first.second;
        int tDist = top.second;

        for (int i=0; i<8; i++) {
            int nRow = tRow + dx[i];
            int nCol = tCol + dy[i];

            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < n &&  
            grid[nRow][nCol] == 0 && tDist + 1 < distance[nRow][nCol]) {
                if (nRow == n - 1 && nCol == n - 1) {
                    return tDist + 1;
                }

                distance[nRow][nCol] = tDist + 1;
                q.push({{nRow, nCol}, distance[nRow][nCol]});
            }
        }
    }

    if (distance[n - 1][n - 1] == 1e9) {
        return -1;
    } 

    return distance[n - 1][n - 1];
}