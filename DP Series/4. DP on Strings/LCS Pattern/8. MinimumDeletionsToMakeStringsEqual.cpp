#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// In this question, we have to delete characters from either string1 or string2 to
// make string1 equal to string2.

// Approach 1: Recursive Approach
// Time Complexity: O(2^(N + M))
// Space Complexity: O(min(N, M))

int helper(int n, int m, string &text1, string &text2) {
    if (n == 0) {
        return m;
    }

    if (m == 0) {
        return n;
    }

    if (text1[n - 1] == text2[m - 1]) {
        return helper(n - 1, m - 1, text1, text2);
    }

    int deleteText1 = 1 + helper(n - 1, m, text1, text2);

    int deleteText2 = 1 + helper(n, m - 1, text1, text2);

    return min(deleteText1, deleteText2);
}

int minDeletions(string word1, string word2) {
    int size1 = word1.size();
    int size2 = word2.size();

    return helper(size1, size2, word1, word2);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int helper(int n, int m, string &text1, string &text2, vector<vector<int>> &dp) {
    if (n == 0) {
        return m;
    }

    if (m == 0) {
        return n;
    }

    if (dp[n][m] != -1) {
        return dp[n][m];
    }

    if (text1[n - 1] == text2[m - 1]) {
        return dp[n][m] = helper(n - 1, m - 1, text1, text2, dp);
    }

    int deleteText1 = 1 + helper(n - 1, m, text1, text2, dp);

    int deleteText2 = 1 + helper(n, m - 1, text1, text2, dp);

    return dp[n][m] = min(deleteText1, deleteText2);
}

int minDeletions(string word1, string word2) {
    int size1 = word1.size();
    int size2 = word2.size();

    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    return helper(size1, size2, word1, word2, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int minDeletions(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    // Initialize a 2D dp table to store the results of subproblems.
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));

    // Initialize the base cases for empty substrings.
    for (int m = 0; m <= size2; m++) {
        dp[0][m] = m;
    }

    for (int n = 0; n <= size1; n++) {
        dp[n][0] = n;
    }

    // Fill the dp table using a nested loop to consider all substrings.
    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            // If the last characters of both strings match, no operation is needed.
            if (text1[n - 1] == text2[m - 1]) {
                dp[n][m] = dp[n - 1][m - 1];
            }
            else {
                // Calculate the minimum of deletion from text1 and text2.
                int deleteText1 = 1 + dp[n - 1][m];
                int insertText2 = 1 + dp[n][m - 1];

                dp[n][m] = min(deleteText1, insertText2);
            }
        }
    }

    // The final result is stored in dp[size1][size2].
    return dp[size1][size2];
}

// Approach 4: Space Optimization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int minDeletions(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    // Initialize a 1D array to store the previous row of the dp table.
    vector<int> prev(size2 + 1, 0);

    // Initialize the base cases for empty substrings.
    for (int m = 0; m <= size2; m++) {
        prev[m] = m;
    }

    // Iterate through text1 and text2 to fill the dp table row by row.
    for (int n = 1; n <= size1; n++) {
        // Initialize a new row for the current iteration.
        vector<int> curr(size2 + 1, 0);
        curr[0] = n;

        for (int m = 1; m <= size2; m++) {
            // If the last characters of both strings match, no operation is needed.
            if (text1[n - 1] == text2[m - 1]) {
                curr[m] = prev[m - 1];
            }
            else {
                // Calculate the minimum of deletion from text1 and text2.
                int insertText1 = 1 + prev[m];
                int insertText2 = 1 + curr[m - 1];

                curr[m] = min(insertText1, insertText2);
            }
        }

        // Update the previous row with the current row for the next iteration.
        prev = curr;
    }

    // The final result is stored in prev[size2].
    return prev[size2];
}