#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(E Log V)
// Space Complexity: O(V)

// In this question, we have to find the cheapest flight from src to dest
// within k stops in the path. So basically, this time we have to note number
// of stops because we have to maintain the at max k stops.

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dest, int k) {
    vector<vector<pair<int, int>>> graph(n);

    for (auto flight : flights) {
        int from = flight[0];
        int to = flight[1];
        int price = flight[2];

        graph[from].push_back({to, price});
    }

    vector<int> prices(n, 1e9);
    prices[src] = 0;

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    // we can use the queue here also

    pq.push({0, {0, src}});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int tVertex = top.second.second;
        int tPrice = top.second.first;
        int tStops = top.first;

        if (tStops > k) {
            continue;
        }

        for (auto it : graph[tVertex]) {
            int neighbour = it.first;
            int price = it.second;

            if (tStops <= k && tPrice + price < prices[neighbour]) {
                prices[neighbour] = tPrice + price;

                pq.push({tStops + 1, {prices[neighbour], neighbour}});
            }
        }
    }

    if (prices[dest] == 1e9) {
        return -1;
    }

    return prices[dest];
}