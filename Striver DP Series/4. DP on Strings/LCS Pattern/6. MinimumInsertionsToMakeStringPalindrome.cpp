#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// In this question, we have to find the Minimum Number of Insertions in the given
// strings so that the string becomes Palindrome. This is similar question as 
// Longest Palindromic Subsequence because for given string, we can find the 
// longest palindromic Subsequence in it which is already a palindrome but, remain
// characters are shuffled which is not making the complete string palindrome. So,
// if we reverse the non-palindromic strings and add to the string, it will make
// the string palindrome. Hence, the number of min insertions will be - 
// Length of String - Length of Longest Palindromic Subsequence

// Approach 1: Using Tabulation Method of LPS
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

int minInsertions(string str) {
    int n = str.size();

    int lpsLen = longestPalindromeSubsequence(str);

    return n - lpsLen;
}

// Approach 2: Using Space Optimization of LPS
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

int minInsertions(string str) {
    int n = str.size();

    int lpsLen = longestPalindromeSubsequence(str);

    return n - lpsLen;
}