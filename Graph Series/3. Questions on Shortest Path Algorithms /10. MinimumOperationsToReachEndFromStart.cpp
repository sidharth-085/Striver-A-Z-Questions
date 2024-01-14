#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(E Log V) or O(Min operations * N * Log 1e3)
// Space Complexity: O(1)

// In this question, we have to find the minimum number of operations to 
// reach from start to end by multiplying the numbers from array arr.
// So basically, when we multiply a number with any value of arr, that
// value of arr counted as edge weight and we do the Dijkstra Algorithm 
// and found the minimum operations. 

int minimumOperations(int n, int start, int end, vector<int> &arr) {
    if (start == end) {
        return 0;
    }

    int mod = 1e3;

    vector<int> operations(mod + 1, 1e9);
    operations[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, start});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int tNum = top.second;
        int tOperations = top.first;

        for (int i=0; i<n; i++) {
            int nNum = (tNum * arr[i]) % mod;

            if (tOperations + 1 < operations[nNum]) {
                operations[nNum] = tOperations + 1;

                if (nNum == end) {
                    return operations[nNum];
                }

                pq.push({operations[nNum], nNum});
            }
        }
    }

    return -1;
}

// BFS Approach

// We can also use BFS Algorithm to do this which means we can keep 
// visited array instead of operations array.

// Time Complexity: O(V + E) or O((Minimum operations * mod) + N)
// Space Complexity: O(1)

int minimumOperations(int n, int start, int end, vector<int> &arr) {
    if (start == end) {
        return 0;
    }

    int mod = 1e3;

    vector<int> visited(mod + 1, 0);
    visited[start] = 1;

    queue<pair<int, int>> q;
    q.push({0, start});

    while (!q.empty()) {
        auto top = q.front();
        q.pop();

        int tNum = top.second;
        int tOperations = top.first;

        if (tNum == end) {
            return tOperations;
        }

        for (int i=0; i<n; i++) {
            int nNum = (tNum * arr[i]) % mod;

            if (nNum == end) {
                return tOperations + 1;
            }

            if (visited[nNum] == 0) {
                visited[nNum] = 1;

                q.push({tOperations + 1, nNum});
            }
        }
    }

    return -1;
}