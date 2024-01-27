#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
    Approach:

    The algorithm approach is stated below:

    - We will fill the string str from the last by maintaining a pointer. 

    - We will start from the right-most cell of the dp array, initially i=n and 
    j=m.

    - At every cell, we will check if S1[i-1] == S2[j-1], if it is then it means 
    this character is a part of the longest common substring. So we will push it 
    to the str (at last). Then we will move to the diagonally top-left(↖) 
    cell by assigning i to i-1 and j to j-1.

    - Else, this character is not a part of the longest common subsequence. 
    It means that originally this cell got its value from its left cell (←) or 
    from its top cell (↑). Whichever cell’s value will be more of the two, we will 
    move to that cell.

    - We will continue till i>0 and j>0, failing it we will break from the loop.

    - At last we will get our lcs string in “str”.
*/

int longestCommonSubsequence(string text1, string text2, vector<vector<int>> &dp) {
    int size1 = text1.size();
    int size2 = text2.size();

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

string findLCS(int size1, int size2, string &text1, string &text2) {
    // Initialize a 2D vector 'dp' to store the length of the Longest Common Subsequence (LCS)
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, 0));

    // Calculate the length of the LCS using a helper function 'longestCommonSubsequence'
    int lcsLen = longestCommonSubsequence(text1, text2, dp);

    // Initialize an empty string 'ans' to store the LCS
    string ans;

    // Fill 'ans' with '#' characters to prepare for inserting the LCS characters
    for (int i = 0; i < lcsLen; i++) {
        ans.push_back('#');
    }

    // Initialize 'index' to keep track of the current index for inserting LCS characters
    int index = lcsLen - 1;

    // Initialize variables 'n' and 'm' to traverse 'text1' and 'text2' respectively
    int n = size1;
    int m = size2;

    // Trace back the LCS by following the direction indicated by the 'dp' matrix
    while (n > 0 && m > 0) {
        // If the characters at the current positions of 'text1' and 'text2' are the same,
        // it means this character is a part of the LCS.

        if (text1[n - 1] == text2[m - 1]) {
            ans[index] = text1[n - 1];  // Store the character in 'ans'
            n--;  // Move to the previous characters in 'text1' and 'text2'
            m--;
            index--;  // Move to the previous index in 'ans'
        }
        // If not, compare the values in the 'dp' matrix to determine the next move:
        else if (dp[n - 1][m] > dp[n][m - 1]) {
            n--;  // Move in the direction of the larger value in 'dp'
        } 
        else {
            m--;
        }
    }

    // 'ans' now contains the Longest Common Subsequence
    return ans;
}