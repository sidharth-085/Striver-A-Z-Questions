#include <iostream>
#include <vector>
#include <string>
using namespace std;

// In this question, we have to find Supersequence to which String 1 and String 2
// both are subsequences of this Supersequence.

// Approach 1: Using LCS Length function
// Time and Space Complexity same as LCS

/*
    Algorithm: 
    - We start from cell dp[n][m]. Initially i=n and j=m.

    - At every cell, we will check if S1[i-1] == S2[j-1], if it is then it means 
    this character is a part of the longest common subsequence. So we will push it 
    to the ans string str. Then we will move to the diagonally top-left(↖)  cell 
    by assigning i to i-1 and j to j-1.

    - Else, this character is not a part of the longest common subsequence so we 
    include it in ans string. Originally this cell got its value from its left 
    cell (←) or from its top cell (↑). Whichever cell’s value will be more of the 
    two, we will move to that cell.

    - We will continue till i>0 and j>0, failing it we will break from the loop.
    - After breaking, either i>0 or j>0 (only one condition will fail to break 
    from the while loop), if(i>0) we push all the characters from S1 to ans 
    string, else if(j>0), we push all the remaining characters from S2.

    - At last, we reverse the ‘ans’ string and we get our answer.
*/

int longestCommonSubsequence(int size1, int size2, string text1, string text2, vector<vector<int>> &dp) {
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

string shortestCommonSupersequence(string str1, string str2) {
    int size1 = str1.size();
    int size2 = str2.size();

    // Step 1: Initialize a 2D DP array to store the lengths of LCS of substrings.
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    // Step 2: Calculate the length of the Longest Common Subsequence (LCS).
    int lcsLen = longestCommonSubsequence(size1, size2, str1, str2, dp);

    // Step 3: Initialize an empty string to store the result.
    string ans;

    int n = size1;
    int m = size2;

    // Step 4: Reconstruct the shortest common supersequence using LCS and DP array.
    while (n > 0 && m > 0) {
        // If the current characters match, it's part of the LCS.
        if (str1[n - 1] == str2[m - 1]) {
            ans.push_back(str1[n - 1]);
            n--;
            m--;
        }
        // If not, choose the path with a higher LCS length.
        else if (dp[n - 1][m] > dp[n][m - 1]) {
            ans.push_back(str1[n - 1]);
            n--;
        } else {
            ans.push_back(str2[m - 1]);
            m--;
        }
    }

    // Step 5: If there are remaining characters in str1, add them to the result.
    while (n > 0) {
        ans.push_back(str1[n - 1]);
        n--;
    }

    // Step 6: If there are remaining characters in str2, add them to the result.
    while (m > 0) {
        ans.push_back(str2[m - 1]);
        m--;
    }

    // Step 7: Reverse the result string to obtain the shortest common supersequence.
    reverse(ans.begin(), ans.end());

    // Step 8: Return the shortest common supersequence.
    return ans;
}

// Approach 2: Using LCS String function
// Time and Space Complexity remains same as LCS

/*
    Algorithm: 

    - Calculate the lengths of str1 and str2 and store them in size1 and size2.

    - Find the Longest Common Subsequence (LCS) of str1 and str2 using the findLCS 
    function. Store the LCS in the variable LCS.

    - Calculate the length of the LCS and store it in lcsSize.

    - Initialize an empty string called ans to store the result, which is the SCS.

    - Initialize three pointers: i for str1, j for str2, and k for LCS, all set to 0.

    - While the LCS is not exhausted (i.e., k < lcsSize):
        a. While there are characters in str1 before the current character in the 
        LCS, add those characters to ans, and increment i.

        b. While there are characters in str2 before the current character in the 
        LCS, add those characters to ans, and increment j.

        c. Add the current character of the LCS to ans.

        d. Increment i, j, and k to move to the next characters in str1, str2, and 
        LCS.

    - After the loop, add the remaining characters in str1 (if any) and str2 (if any) to the ans.

    - Return the ans, which is the shortest common supersequence of str1 and str2.
*/

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

string shortestCommonSupersequence(string str1, string str2) {
    int size1 = str1.size(); // Get the length of the first string.
    int size2 = str2.size(); // Get the length of the second string.

    // Find the Longest Common Subsequence (LCS) of the two strings.
    string LCS = findLCS(size1, size2, str1, str2);
    
    int lcsSize = LCS.size(); // Get the length of the LCS.

    string ans; // Initialize the result string.

    int i = 0, j = 0, k = 0; // Initialize pointers for str1, str2, and LCS.

    // Merge the characters before the LCS from str1 and str2 into ans.
    
    while (k < lcsSize) {
        // Add characters from str1 to ans until the current character matches the LCS.
        while (i < size1 && str1[i] != LCS[k]) {
            ans.push_back(str1[i]);
            i++;
        }
        // Add characters from str2 to ans until the current character matches the LCS.
        while (j < size2 && str2[j] != LCS[k]) {
            ans.push_back(str2[j]);
            j++;
        }
        ans.push_back(LCS[k]); // Add the current LCS character to ans.
        i++;
        j++;
        k++;
    }

    // Add the remaining characters from str1 and str2 to ans.
    ans = ans + str1.substr(i) + str2.substr(j);

    return ans; // Return the shortest common supersequence.
}