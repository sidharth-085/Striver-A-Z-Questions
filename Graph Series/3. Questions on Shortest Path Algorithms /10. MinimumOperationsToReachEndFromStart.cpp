#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int minimumOperations(int n, int start, int end, vector<int> &arr) {
    if (start == end) {
        return 0;
    }

    int mod = 1e3;

    vector<int> operations(mod, 1e9);
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