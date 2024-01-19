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

// In this question, we are given some coordinates of the grid of size
// n x m. It is dynamic graph questions, means with each query, graph
// changes. We have to number of islands are there at every query 
// and islands become when the land coordinate shares another land
// coordinate adjacent to each other. And, we have to store all the
// islands number at every query in vector to return it.

// This problem involves 3 steps to solve:

// 1. Firstly, we know that the queries contains some duplicate 
// coordinates also, therefore we keep a visited grid which check 
// if this coordinateis already taken or not. And, when at every 
// query we check if it repeated, we add the previous island number
//  which is before the current query. 

// 2. Secondly, we get the node from current coordinate which is 
// node = (row * m) + col because we are assuming every cell as number
// and take union with the help of them. Also, increase the count 
// of islands because for current query, there is increase in island
// number. But, now we have to check that for current query, it is
// making a group of coordinates which makes a single island or not.

// 3. So, we check all 4 directions (up, down, left, right) and if
// we get the adjacent coordinate which is marked as visited means
// there is already a land adjacent to it which makes a group and 
// joins into a single island. But, we also have to do union of 
// both newNode = (newRow * m) + newCol and node. And, if union of
// both is true, means they are different islands and now attached
// together only then, we decrease island number by 1. We continue
// this for every adjacent coordinate, and if there is adjacent
// coordinate which is visited but union of that newNode and node
// is false means ultimateParent of both are same, implies there are
// already connected so we dont have to reduce the island number.

// Finally, add the count number for every query inside ans and
// returns.

// Time Complexity: O((N*M) + (Q*Log(N*M)))
// Space Complexity: O(N*M)

vector<int> numberOfIslandII(int n, int m, vector<vector<int>>& queries, int q) {
    vector<int> ans;

    DSU dsu(n * m);
    
    int count = 0;

    vector<vector<int>> visited(n, vector<int>(m, 0));

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (auto &query : queries) {
        int row = query[0];
        int col = query[1];

        if (visited[row][col] == 1) {
            ans.push_back(count);
            continue;
        }

        int node = (row * m) + col;
        visited[row][col] = 1;

        count++;

        for (int i=0; i<4; i++) {
            int newRow = row + dx[i];
            int newCol = col + dy[i];

            int newNode = (newRow * m) + newCol;

            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m) {
                if (visited[newRow][newCol] == 1 && dsu.unionByRank(node, newNode) == true) {
                    count--;
                }
            }
        }

        ans.push_back(count);
    }

    return ans;
}