#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Recursive Approach
// Time Complexity: O(2^(N + M))
// Space Complexity: O(N * M)

int lcsHelper(int n, int m, string text1, string text2) {
    // Base case: If either string is empty, the LCS is 0.
    if (n == 0 || m == 0) {
        return 0;
    }

    // If the last characters match, include them in the LCS.
    if (text1[n - 1] == text2[m - 1]) {
        return (1 + lcsHelper(n - 1, m - 1, text1, text2));
    }

    // Otherwise, find LCS by excluding characters from either string.
    int skip1 = lcsHelper(n - 1, m, text1, text2);
    int skip2 = lcsHelper(n, m - 1, text1, text2);

    return max(skip1, skip2);
}

int longestCommonSubsequence(string text1, string text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    // Call the helper function with initial sizes.
    return lcsHelper(size1, size2, text1, text2);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int lcsHelper(int n, int m, string text1, string text2, vector<vector<int>> &dp) {
    if (n == 0 || m == 0) {
        return 0;
    }

    // If the result is already computed, return it.
    if (dp[n][m] != -1) {
        return dp[n][m];
    }

    if (text1[n - 1] == text2[m - 1]) {
        // Include the matching characters and memoize the result.
        return dp[n][m] = 1 + lcsHelper(n - 1, m - 1, text1, text2, dp);
    }

    // Find LCS by excluding characters and memoize the result.
    int skip1 = lcsHelper(n - 1, m, text1, text2, dp);
    int skip2 = lcsHelper(n, m - 1, text1, text2, dp);

    return dp[n][m] = max(skip1, skip2);
}

int longestCommonSubsequence(string text1, string text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    // Initialize a memoization table with -1 values.
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    // Call the helper function with initial sizes and the memoization table.
    return lcsHelper(size1, size2, text1, text2, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int longestCommonSubsequence(string text1, string text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    // Create a 2D DP table with size1+1 rows and size2+1 columns.
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    // Initialize the base cases: when one of the strings is empty.
    for (int n = 0; n <= size1; n++) {
        dp[n][0] = 0;
    }

    for (int m = 0; m <= size2; m++) {
        dp[0][m] = 0;
    }

    // Fill the DP table using bottom-up approach.
    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            if (text1[n - 1] == text2[m - 1]) {
                // If characters match, increment LCS.
                dp[n][m] = 1 + dp[n - 1][m - 1];
            } else {
                // Otherwise, choose the maximum of two previous states.
                int skip1 = dp[n - 1][m];
                int skip2 = dp[n][m - 1];
                dp[n][m] = max(skip1, skip2);
            }
        }
    }

    // The result is in the bottom-right cell of the DP table.
    return dp[size1][size2];
}

// Approach 4: Space Optimization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(M)

int longestCommonSubsequence(string text1, string text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    // Use a single vector 'prev' to store the previous row of the DP table.
    vector<int> prev(size2 + 1, 0);

    for (int n = 1; n <= size1; n++) {
        // Create a new vector 'curr' for the current row.
        vector<int> curr(size2 + 1, 0);

        for (int m = 1; m <= size2; m++) {
            if (text1[n - 1] == text2[m - 1]) {
                // If characters match, increment LCS.
                curr[m] = 1 + prev[m - 1];
            } else {
                // Otherwise, choose the maximum of two previous states.
                int skip1 = prev[m];
                int skip2 = curr[m - 1];
                curr[m] = max(skip1, skip2);
            }
        }

        // Update 'prev' with the current row before moving to the next row.
        prev = curr;
    }

    // The result is in the last element of the 'prev' vector.
    return prev[size2];
}