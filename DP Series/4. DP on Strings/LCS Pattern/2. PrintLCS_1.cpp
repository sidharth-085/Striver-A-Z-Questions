#include <iostream>
#include <vector>
#include <string>
using namespace std;

// This question is similar to LCS, just we have to find the LCS lengths for 
// every sizes of text1 and text2 and then find the LCS in another helper func.
// We can combine both functions by doing in single dp grid of pair<int, string>
// which can be space optimized later same as LCS (using prev and curr 1-D array).

// Approach 1: Recursive Approach
// Time Complexity: O(2^N * 2*M)
// Space Complexity: O(2 * N * M)

string helper(int n, int m, string &text1, string &text2, vector<vector<int>> &dp) {
    // Base case: If either of the strings is empty, return an empty string
    if (n == 0 || m == 0) {
        return "";
    }

    // If the last characters of both strings match
    if (text1[n - 1] == text2[m - 1]) {
        // Include the matching character and recursively call the helper function
        return helper(n - 1, m - 1, text1, text2, dp) + text1[n - 1];
    }
    else {
        // If the characters don't match, choose the maximum of two skip options
        int skip1 = dp[n - 1][m];
        int skip2 = dp[n][m - 1];

        if (skip1 > skip2) {
            // Skip a character in text1
            return helper(n - 1, m, text1, text2, dp);
        }
        else {
            // Skip a character in text2
            return helper(n, m - 1, text1, text2, dp);
        }
    }
}

string findLCS(int size1, int size2, string text1, string text2) {
    // Initialize a 2D DP array for memoization
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    // Initialize the first row and first column of DP array
    for (int n = 0; n <= size1; n++) {
        dp[n][0] = 0;
    }

    for (int m = 0; m <= size2; m++) {
        dp[0][m] = 0;
    }

    // Fill in the DP array using bottom-up approach
    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            if (text1[n - 1] == text2[m - 1]) {
                dp[n][m] = 1 + dp[n-1][m-1];
            }
            else {
                int skip1 = dp[n-1][m];
                int skip2 = dp[n][m-1];

                dp[n][m] = max(skip1, skip2);
            }
        }
    }

    // Call the helper function to reconstruct the LCS string
    return helper(size1, size2, text1, text2, dp);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(2 * N * M)

string helper(int n, int m, string &text1, string &text2, vector<vector<int>> &dp, vector<vector<string>> &ans) {
    // Base case: If either of the strings is empty, return an empty string
    if (n == 0 || m == 0) {
        return "";
    }

    // If the last characters of both strings match
    if (text1[n - 1] == text2[m - 1]) {
        // Include the matching character and recursively call the helper function
        return ans[n][m] = helper(n - 1, m - 1, text1, text2, dp, ans) + text1[n - 1];
    }
    else {
        // If the characters don't match, choose the maximum of two skip options
        int skip1 = dp[n - 1][m];
        int skip2 = dp[n][m - 1];

        if (skip1 > skip2) {
            // Skip a character in text1
            return ans[n][m] = helper(n - 1, m, text1, text2, dp, ans);
        }
        else {
            // Skip a character in text2
            return ans[n][m] = helper(n, m - 1, text1, text2, dp, ans);
        }
    }
}

string findLCS(int size1, int size2, string text1, string text2) {
    // Initialize a 2D DP array for memoization
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    // Initialize the first row and first column of DP array
    for (int n = 0; n <= size1; n++) {
        dp[n][0] = 0;
    }

    for (int m = 0; m <= size2; m++) {
        dp[0][m] = 0;
    }

    // Fill in the DP array using bottom-up approach
    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            if (text1[n - 1] == text2[m - 1]) {
                dp[n][m] = 1 + dp[n-1][m-1];
            }
            else {
                int skip1 = dp[n-1][m];
                int skip2 = dp[n][m-1];

                dp[n][m] = max(skip1, skip2);
            }
        }
    }

    // Initialize a 2D array for storing LCS strings
    vector<vector<string>> ans(size1 + 1, vector<string>(size2 + 1));

    // Call the helper function to reconstruct the LCS string
    return helper(size1, size2, text1, text2, dp, ans);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * M)
// Space Complexity: O(2 * N * M)

string helper(int size1, int size2, string &text1, string &text2, vector<vector<int>> &dp) {
    // Initialize a 2D array to store LCS strings
    vector<vector<string>> ans(size1 + 1, vector<string>(size2 + 1));

    // Initialize the first row and first column of ans array
    for (int n = 0; n <= size1; n++) {
        ans[n][0] = "";
    }

    for (int m = 0; m <= size2; m++) {
        ans[0][m] = "";
    }

    // Fill in the ans array using bottom-up approach
    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            if (text1[n - 1] == text2[m - 1]) {
                ans[n][m] = ans[n-1][m-1] + text1[n - 1];
            }
            else {
                int skip1 = dp[n-1][m];
                int skip2 = dp[n][m-1];

                if (skip1 > skip2) {
                    ans[n][m] = ans[n-1][m];
                }
                else {
                    ans[n][m] = ans[n][m - 1];
                }
            }
        }
    }

    // Return the LCS string
    return ans[size1][size2];
}

string findLCS(int size1, int size2, string text1, string text2) {
    // Initialize a 2D DP array for tabulation
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    // Initialize the first row and first column of DP array
    for (int n = 0; n <= size1; n++) {
        dp[n][0] = 0;
    }

    for (int m = 0; m <= size2; m++) {
        dp[0][m] = 0;
    }

    // Fill in the DP array using bottom-up approach
    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            if (text1[n - 1] == text2[m - 1]) {
                dp[n][m] = 1 + dp[n-1][m-1];
            }
            else {
                int skip1 = dp[n-1][m];
                int skip2 = dp[n][m-1];

                dp[n][m] = max(skip1, skip2);
            }
        }
    }

    // Call the helper function to reconstruct the LCS string
    return helper(size1, size2, text1, text2, dp);
}

// Approach 4: Same tabulation code (combination of helper and findLCS function)
// Time Complexity: O(N * M)
// Space Complexity: O(2 * N * M)

string findLCS(int size1, int size2, string text1, string text2) {
    // Initialize a 2D DP array to store both length and LCS string
    vector<vector<pair<int, string>>> dp(size1 + 1, vector<pair<int, string>>(size2 + 1));

    // Initialize the first row and first column of DP array
    for (int n = 0; n <= size1; n++) {
        dp[n][0] = {0, ""};
    }

    for (int m = 0; m <= size2; m++) {
        dp[0][m] = {0, ""};
    }

    // Fill in the DP array using bottom-up approach
    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            if (text1[n - 1] == text2[m - 1]) {
                // Include the matching character and update length and LCS string
                dp[n][m] = {1 + dp[n-1][m-1].first, dp[n-1][m-1].second + text1[n-1]};
            }
            else {
                // Choose the maximum of two skip options
                int skip1 = dp[n-1][m].first;
                int skip2 = dp[n][m-1].first;

                if (skip1 > skip2) {
                    dp[n][m] = {skip1, dp[n-1][m].second};
                } else {
                    dp[n][m] = {skip2, dp[n][m-1].second};
                }
            }
        }
    }

    // Return the LCS string
    return dp[size1][size2].second;
}

// Approach 5: Space Optimization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(2 * M)

string findLCS(int size1, int size2, string text1, string text2) {
    // Initialize a vector to store the previous row of DP values
    vector<pair<int, string>> prev(size2 + 1);

    // Initialize the first row of prev with zeros
    prev[0] = {0, ""};

    for (int m = 0; m <= size2; m++) {
        prev[m] = {0, ""};
    }

    // Iterate through the text1 and text2 characters
    for (int n = 1; n <= size1; n++) {
        // Initialize a vector to store the current row of DP values
        vector<pair<int, string>> curr(size2 + 1);
        curr[0] = {0, ""};

        for (int m = 1; m <= size2; m++) {
            if (text1[n - 1] == text2[m - 1]) {
                // Include the matching character and update length and LCS string
                curr[m] = {1 + prev[m-1].first, prev[m-1].second + text1[n-1]};
            }
            else {
                // Choose the maximum of two skip options
                int skip1 = prev[m].first;
                int skip2 = curr[m-1].first;

                if (skip1 > skip2) {
                    curr[m] = {skip1, prev[m].second};
                } else {
                    curr[m] = {skip2, curr[m-1].second};
                }
            }
        }

        // Update prev to be curr for the next iteration
        prev = curr;
    }

    // Return the LCS string from the last row of DP values
    return prev[size2].second;
}