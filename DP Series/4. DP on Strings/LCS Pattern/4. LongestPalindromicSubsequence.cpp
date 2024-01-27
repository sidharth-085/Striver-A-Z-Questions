#include <iostream>
#include <vector>
#include <string>
using namespace std;

// This problem is similar to LCS problem, we have to find the longest Palindromic
// subsequence from a single string. A Palindrome is the string which is same 
// when we reverse it. So, we take first take string str as text1 and reversed str
// as text2 because when we reverse str, the palindrome also get reversed and 
// palindrome will be same even after reversing the complete string. So, if we 
// find the sommon subsequence between str and reversed str, we will get our answer.

// Approach 1: Using LCS Tabulation Method to find Longest Palindromic Subsequnce
// Time Complexity: O(N * N)
// Space Complexity: O(N * N)

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

int longestPalindromeSubsequence(string str) {
    // string revStr(str.rbegin(), str.rend());

    string revStr;

    int n = str.size();

    for (int i = n - 1; i >= 0; i--) {
        revStr = revStr + str[i];
    }

    return longestCommonSubsequence(str, revStr);
}

// Approach 2: Using LCS Space Optimzation Method
// Time Complexity: O(N * N)
// Space Complexity: O(N)

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

int longestPalindromeSubsequence(string str) {
    // string revStr(str.rbegin(), str.rend());

    string revStr;

    int n = str.size();

    for (int i = n - 1; i >= 0; i--) {
        revStr = revStr + str[i];
    }

    return longestCommonSubsequence(str, revStr);
}