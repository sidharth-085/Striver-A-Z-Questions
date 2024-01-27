#include <iostream>
#include <vector>
#include <string>
using namespace std;

// In this question, we have two strings pat and str. pat string contains some '?'
// '*' which are different meaning. We have to check is pat and str matches or not.

// Here '?' means if we are matching pat with str, '?' matches with any single
// character.

// Here '*' means if we are matching pat with str, '*' matches with any sequence
// of characters. If pat contains 3 letters and it has one '*' character, str of 
// length 5, matchs with 2 characters of pat. Now, 3 character remaining in str
// can matches with '*'. So, pat and str can be matched.

// Approach 1: Recursive Approach
// Time Complexity: O(2^(N + M))
// Space Complexity: O(N + M)

bool helper(int n, int m, string &pat, string &str) {
    if (n == 0 && m == 0) {
        return true;  // Both pattern and string are empty, so they match.
    }

    if (n == 0) {
        return false; // Pattern is empty, but string is not, so they don't match.
    }

    if (m == 0) {
        for (int i = 0; i < n; i++) {
            if (pat[i] != '*') {
                return false; // If there are non-'*' characters in the remaining pattern, they don't match.
            }
        }
        return true; // If only '*' characters are left in the pattern, they match any remaining string.
    }

    if (pat[n - 1] == str[m - 1] || pat[n - 1] == '?') {
        return helper(n - 1, m - 1, pat, str); // Characters match, continue to the next characters in both pattern and string.
    }

    if (pat[n - 1] == '*') {
        int skipStar = helper(n - 1, m, pat, str); // Try to skip the '*' character in the pattern.
        int skipChar = helper(n, m - 1, pat, str); // Try to match the '*' character with one character in the string.
        return skipStar | skipChar; // Return true if either skipping the '*' or matching it with a character works.
    }

    return false; // Characters don't match, and it's not a '*' or '?'.
}

bool wildcardMatching(string pat, string str) {
    int size1 = pat.size();
    int size2 = str.size();

    return helper(size1, size2, pat, str);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

bool helper(int n, int m, string &pat, string &str, vector<vector<int>> &dp) {
    if (n == 0 && m == 0) {
        return true;
    }

    if (n == 0) {
        return false;
    }

    if (m == 0) {
        for (int i = 0; i < n; i++) {
            if (pat[i] != '*') {
                return false;
            }
        }
        
        return true;
    }

    if (dp[n][m] != -1) {
        return dp[n][m];
    }

    if (pat[n - 1] == str[m - 1] || pat[n - 1] == '?') {
        return dp[n][m] = helper(n - 1, m - 1, pat, str, dp);
    }

    if (pat[n - 1] == '*') {
        int skipStar = helper(n - 1, m, pat, str, dp);

        int skipChar = helper(n, m - 1, pat, str, dp);

        return dp[n][m] = skipStar | skipChar;
    }

    return dp[n][m] = false;
}

bool wildcardMatching(string pat, string str) {
    int size1 = pat.size();
    int size2 = str.size();

    vector<vector<int>> dp(size1 + 1, vector<int>(size2 + 1, -1));

    return helper(size1, size2, pat, str, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

bool wildcardMatching(string pat, string str) {
    int size1 = pat.size();
    int size2 = str.size();

    vector<vector<bool>> dp(size1 + 1, vector<bool>(size2 + 1, false));

    dp[0][0] = true;

    for (int m = 1; m <= size2; m++) {
        dp[0][m] = false;
    }

    for (int n = 1; n <= size1; n++) {
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (pat[i] != '*') {
                flag = false;
                break;
            }
        }

        dp[n][0] = flag;
    }

    for (int n = 1; n <= size1; n++) {
        for (int m = 1; m <= size2; m++) {
            if (pat[n - 1] == str[m - 1] || pat[n - 1] == '?') {
                dp[n][m] = dp[n - 1][m - 1];
            }
            else if (pat[n - 1] == '*') {
                bool skipStar = dp[n - 1][m];
                bool skipChar = dp[n][m - 1];

                dp[n][m] = skipStar | skipChar;
            }
            else {
                dp[n][m] = false;
            }
        }
    }

    return dp[size1][size2];
}

// Approach 4: Space Optimization Method
// Time Complexity: O(N * M)
// Space Complexity: O(2 * M)

bool wildcardMatching(string pat, string str) {
    int size1 = pat.size();
    int size2 = str.size();

    vector<bool> prev(size2 + 1, false);

    prev[0] = true;

    for (int m = 1; m <= size2; m++) {
        prev[m] = false;
    }

    for (int n = 1; n <= size1; n++) {
        vector<bool> curr(size2 + 1, false);

        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (pat[i] != '*') {
                flag = false;
                break;
            }
        }

        curr[0] = flag;

        for (int m = 1; m <= size2; m++) {
            if (pat[n - 1] == str[m - 1] || pat[n - 1] == '?') {
                curr[m] = prev[m - 1];
            }
            else if (pat[n - 1] == '*') {
                bool skipStar = prev[m];
                bool skipChar = curr[m - 1];

                curr[m] = skipStar | skipChar;
            }
            else {
                curr[m] = false;
            }
        }

        prev = curr;
    }

    return prev[size2];
}