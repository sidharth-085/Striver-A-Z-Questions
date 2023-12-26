#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Using Tabulation Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int lcs(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    // Create a 2D DP table to store the length of LCS at each (i, j) position
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));

    // Initialize the maximum length of LCS to 0
    int ans = 0;

    // Loop through text1 and text2
    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            // If the current characters in text1 and text2 match
            if (text1[n - 1] == text2[m - 1]) {
                // Increment the length of LCS by 1 and store it in dp table
                dp[n][m] = 1 + dp[n - 1][m - 1];
                // Update the maximum length of LCS if needed
                ans = max(ans, dp[n][m]);
            }
            else {
                // If characters do not match, LCS length is 0 at this position
                dp[n][m] = 0;
            }
        }
    }

    // Return the maximum length of LCS
    return ans;
}

// Approach 2: Space Optimization Approach
// Time Complexity: O(N * M) 
// Space Complexity: O(M)

int lcs(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    // Create two vectors to store the current and previous row of the DP table
    vector<int> prev(size2 + 1, 0);

    // Initialize the maximum length of LCS to 0
    int ans = 0;

    // Loop through text1 and text2
    for (int n = 1; n <= size1; n++) {
        // Create a new vector for the current row
        vector<int> curr(size2 + 1, 0);

        for (int m = 1; m <= size2; m++) {
            // If the current characters in text1 and text2 match
            if (text1[n - 1] == text2[m - 1]) {
                // Increment the length of LCS by 1 and store it in the current row
                curr[m] = 1 + prev[m - 1];
                // Update the maximum length of LCS if needed
                ans = max(ans, curr[m]);
            }
            else {
                // If characters do not match, LCS length is 0 at this position
                curr[m] = 0;
            }
        }

        // Update the previous row with the values of the current row
        prev = curr;
    }

    // Return the maximum length of LCS
    return ans;
}