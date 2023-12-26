#include <iostream>
#include <vector>
#include <string>
using namespace std;

// In this question we have to find the number of distinct subsequences of string 1
// which is same as string 2. So, we used take and skip method.

// If the characters are same, we can take that character or we can skip that
// character to explore other same characters.
// And, if characters are not same, we have to skip that character from string 1.
// Then, total subsequences will be addition of both.

int mod = 1e9 + 7;

// Approach 1: Recursive Approach
// Time Complexity: O(2^(N + M))
// Space Complexity: O(N + M)

int distinctSubseq(int n, int m, string &text1, string &text2) {
    // Base case 1: If text2 is empty, there is exactly one way to match it (an empty sequence).
    if (m == 0) {
        return 1;
    }
    
    // Base case 2: If text1 is empty but text2 is not, there is no way to match.
    if (n == 0) {
        return 0;
    }
    
    // If the current characters of text1 and text2 are equal, we have two choices:
    // 1. Take the character and move to the next character in both strings.
    // 2. Skip the character in text1 and move to the next character in text1.
    // Return the sum of these two choices modulo 'mod'.
    if (text1[n - 1] == text2[m - 1]) {
        int take = distinctSubseq(n - 1, m - 1, text1, text2);

        int skip = distinctSubseq(n - 1, m, text1, text2);

        return (take + skip) % mod;
    }
    
    // If the current characters of text1 and text2 are not equal, we have to skip the
    // character in text1 to match it with text2. Return the result after skipping.
    int skip = distinctSubseq(n - 1, m, text1, text2);

    return skip;
}

int distinctSubsequences(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();
    return distinctSubseq(size1, size2, text1, text2);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int distinctSubseq(int n, int m, string &text1, string &text2, vector<vector<int>> &dp) {
    if (m == 0) {
        return 1;
    }

    if (n == 0) {
        return 0;
    }

    // If the result for this subproblem is already calculated, return it.
    if (dp[n][m] != -1) {
        return dp[n][m];
    }

    if (text1[n - 1] == text2[m - 1]) {
        int take = distinctSubseq(n - 1, m - 1, text1, text2);

        int skip = distinctSubseq(n - 1, m, text1, text2);

        return dp[n][m] = (take + skip) % mod;
    }
    
    // If the current characters of text1 and text2 are not equal, we have to skip the
    // character in text1 to match it with text2. Return the result after skipping.
    int skip = distinctSubseq(n - 1, m, text1, text2);

    return dp[n][m] = skip % mod;
}

int distinctSubsequences(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));
    return distinctSubseq(size1, size2, text1, text2, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int distinctSubsequences(string &text1, string &text2) {
    int size1 = text1.size();
    int size2 = text2.size();

    // Create a DP table with size1+1 rows and size2+1 columns, initialized with -1.
    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    // Base cases: If text2 is empty, there is exactly one way to match it (an empty sequence).
    for (int m = 0; m <= size2; m++) {
        dp[0][m] = 1;
    }

    // Base case: If text1 is empty but text2 is not, there is no way to match.
    for (int n = 0; n <= size1; n++) {
        dp[n][0] = 0;
    }

    // Fill in the DP table using bottom-up dynamic programming.
    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            if (text1[n - 1] == text2[m - 1]) {
                int takeChar = dp[n - 1][m - 1];
                int skipChar = dp[n - 1][m];

                dp[n][m] = (takeChar + skipChar) % mod;

            } 
            else {
                int skipChar = dp[n - 1][m];

                dp[n][m] = skipChar % mod;
            }
        }
    }

    return dp[size1][size2];
}

// Approach 4: Space Optimization Approach (Two 1-D array)
// Time Complexity: O(N * M)
// Space Complexity: O(2 * M)

int distinctSubsequences(string &text1, string &text2) {
	// Initialize the size of the input strings text1 and text2.
    int size1 = text1.size();
    int size2 = text2.size();

    // Initialize a vector to keep track of the previous row's values.
    vector<int> prev(size2 + 1, -1);

    // Initialize the base case for when the text2 is empty (an empty subsequence).
    for (int m = 0; m <= size2; m++) {
        prev[m] = 0;
    }
    prev[0] = 1;  // Base case for an empty subsequence.

    // Loop through text1 characters.
    for (int n = 1; n <= size1; n++) {
        // Initialize a vector to store the current row's values.
        vector<int> curr(size2 + 1, -1);
        curr[0] = 1;  // Base case for an empty subsequence.

        // Loop through text2 characters.
        for (int m = 1; m <= size2; m++) {
            // Check if the current characters in text1 and text2 match.
            if (text1[n - 1] == text2[m - 1]) {
                // Calculate the number of ways to take the current character or skip it.
                int takeChar = prev[m - 1];
                int skipChar = prev[m];

                // Update the current row with the total number of distinct subsequences.
                curr[m] = (takeChar + skipChar) % mod;
            } else {
                // If the characters don't match, we can only skip the character in text1.
                int skipChar = prev[m];

                // Update the current row with the number of ways to skip the character.
                curr[m] = (skipChar) % mod;
            }
        }

        // Set the previous row to the current row for the next iteration.
        prev = curr;
    }

    // Return the result, which is the total number of distinct subsequences.
    return prev[size2];
}

// Approach 5: Space Optimization Approach (One 1-D array)
// Time Complexity: O(N * M)
// Space Complexity: O(M)

int distinctSubsequences(string &text1, string &text2) {
	// Initialize the size of the input strings text1 and text2.
    int size1 = text1.size();
    int size2 = text2.size();

    // Initialize a vector to keep track of the previous row's values.
    vector<int> prev(size2 + 1, -1);

    // Initialize the base case for when the text2 is empty (an empty subsequence).
    for (int m = 0; m <= size2; m++) {
        prev[m] = 0;
    }
    prev[0] = 1;  // Base case for an empty subsequence.

    // Loop through text1 characters.
    for (int n = 1; n <= size1; n++) {
        // Loop through text2 characters in reverse order.
        for (int m = size2; m >= 1; m--) {
            // Check if the current characters in text1 and text2 match.
            if (text1[n - 1] == text2[m - 1]) {
                // Calculate the number of ways to take the current character or skip it.
                int takeChar = prev[m - 1];
                int skipChar = prev[m];

                // Update the previous row with the total number of distinct subsequences.
                prev[m] = (takeChar + skipChar) % mod;
            } else {
                // If the characters don't match, we can only skip the character in text1.
                int skipChar = prev[m];

                // Update the previous row with the number of ways to skip the character.
                prev[m] = (skipChar) % mod;
            }
        }
    }

    // Return the result, which is the total number of distinct subsequences.
    return prev[size2];
}