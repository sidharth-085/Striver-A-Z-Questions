#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Recursive Approach
// Time Complexity: O(2^(N + M))
// Space Complexity: O(min(N, M))

int helper(int n, int m, string &text1, string &text2) {
    // Base cases: if either string is empty, the minimum number of operations is equal to the length of the other string.
    if (n == 0) {
        return m;
    } 

    if (m == 0) {
        return n;
    }

    // If the last characters of both strings match, no operation is needed.
    if (text1[n - 1] == text2[m - 1]) {
        return helper(n - 1, m - 1, text1, text2);
    }

    // Calculate the minimum of three possible operations: deletion, insertion, or substitution.
    int deleteChar = 1 + helper(n - 1, m, text1, text2);
    int insertChar = 1 + helper(n, m - 1, text1, text2);
    int replaceChar = 1 + helper(n - 1, m - 1, text1, text2);

    return min(replaceChar, min(deleteChar, insertChar));
}

int editDistance(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    return helper(size1, size2, text1, text2);
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

    // If the result for this pair of substrings is already computed, return it from the memoization table.
    if (dp[n][m] != -1) {
        return dp[n][m];
    }

    if (text1[n - 1] == text2[m - 1]) {
        return dp[n][m] = helper(n - 1, m - 1, text1, text2);
    }

    int deleteChar = 1 + helper(n - 1, m, text1, text2, dp);
    int insertChar = 1 + helper(n, m - 1, text1, text2, dp);
    int replaceChar = 1 + helper(n - 1, m - 1, text1, text2);

    return dp[n][m] = min(replaceChar, min(deleteChar, insertChar));
}

int editDistance(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    return helper(size1, size2, text1, text2, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int editDistance(string &text1, string &text2) {
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
                // Calculate the minimum of two possible operations: deletion and insertion.
                int deleteChar = 1 + dp[n - 1][m];
                int insertChar = 1 + dp[n][m - 1];
                int replaceChar = 1 + dp[n - 1][m - 1];

                dp[n][m] = min(replaceChar, min(deleteChar, insertChar));
            }
        }
    }

    // The final result is stored in dp[size1][size2].
    return dp[size1][size2];
}

// Approach 4: Space Optimization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int editDistance(string &text1, string &text2) {
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
                // Calculate the minimum of two possible operations: deletion and insertion.
                int deleteChar = 1 + prev[m];
                int insertChar = 1 + curr[m - 1];
                int replaceChar = 1 + prev[m - 1];

                curr[m] = min(replaceChar, min(deleteChar, insertChar));
            }
        }

        // Update the previous row with the current row for the next iteration.
        prev = curr;
    }

    // The final result is stored in prev[size2].
    return prev[size2];
}