#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Approach 1: LCS Tabulation Method
// Time Complexity: O(N * N)
// Space Complexity: O(N * N)

string longestCommonSubsequence(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();
   
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

string longestPalindromeSubsequence(string str) {
    // string revStr(str.rbegin(), str.rend());

    string revStr;

    int n = str.size();

    for (int i = n - 1; i >= 0; i--) {
        revStr = revStr + str[i];
    }

    return longestCommonSubsequence(str, revStr);
}

// Approach 2: Space Optimization Method
// Time Complexity: O(N * N)
// Space Complexity: O(N)

string longestCommonSubsequence(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();

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

string longestPalindromeSubsequence(string str) {
    // string revStr(str.rbegin(), str.rend());

    string revStr;

    int n = str.size();

    for (int i = n - 1; i >= 0; i--) {
        revStr = revStr + str[i];
    }

    return longestCommonSubsequence(str, revStr);
}