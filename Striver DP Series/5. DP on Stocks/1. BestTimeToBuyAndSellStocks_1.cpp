#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Brute Force Method
// Time Complexity: O(N * N)
// Space Complexity: O(1)

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    
    int maxi = 0;  // Initialize the maximum profit to 0

    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            if (prices[j] > prices[i]) {
                // Calculate the profit if buying on day i and selling on day j
                int currProfit = prices[j] - prices[i];
                // Update maxi with the maximum profit found so far
                maxi = max(maxi, currProfit);
            }
        }
    }

    return maxi;  // Return the maximum profit
}

// Approach 2: DP Method
// Time Complexity: O(N)
// Space Complexity: O(1)

int maxProfit(vector<int>& prices) {
    int n = prices.size();

    int maxi = 0;  // Initialize the maximum profit to 0

    int minPrice = prices[0];  // Initialize the minimum price to the price on the first day

    for (int i=1; i<n; i++) {
        int currProfit = prices[i] - minPrice;  // Calculate the profit if selling on day i

        maxi = max(maxi, currProfit);  // Update maxi with the maximum profit found so far
        
        minPrice = min(minPrice, prices[i]);  // Update minPrice to the minimum price seen so far
    }

    return maxi;  // Return the maximum profit
}