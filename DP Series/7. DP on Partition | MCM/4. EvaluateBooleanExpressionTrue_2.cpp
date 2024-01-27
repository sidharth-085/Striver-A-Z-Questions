#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

int mod = 1e9 + 7;

// Approach 1: Recursive Approach
// Time Complexity: Exponential
// Space Complexity: O(N)

int helper(int start, int end, int lookingForTrue, string &expression) {
    // Base case: If the start index exceeds the end index, return 0.
    if (start > end) {
        return 0;
    }
    
    // Base case: If there's only one character left, evaluate it.
    if (start == end) {
        if (lookingForTrue == 1) {
            if (expression[start] == 'T') {
                return 1;
            }
            return 0;
        }
        else {
            if (expression[start] == 'F') {
                return 1;
            }
            return 0;
        }
    }

    int numWays = 0;

    // Loop through operators in the expression.
    for (int index = start + 1; index <= end - 1; index = index + 2) {
        // Recursive calls for left and right sub-expressions with different values of lookingForTrue.
        int leftPartTrue = helper(start, index - 1, 1, expression);
        int leftPartFalse = helper(start, index - 1, 0, expression);
        int rightPartTrue = helper(index + 1, end, 1, expression);
        int rightPartFalse = helper(index + 1, end, 0, expression);

        // Evaluate the current operator and update numWays.
        if (expression[index] == '&') {
            if (lookingForTrue == true) {
                numWays += (leftPartTrue * rightPartTrue);
            }
            else {
                numWays += (leftPartTrue * rightPartFalse) + (leftPartFalse * rightPartTrue) + (leftPartFalse * rightPartFalse);
            }
        }
        else if (expression[index] == '|') {
            if (lookingForTrue == true) {
                numWays += (leftPartTrue * rightPartTrue) + (leftPartTrue * rightPartFalse) + (leftPartFalse * rightPartTrue);
            }
            else {
                numWays += (leftPartFalse * rightPartFalse);
            }
        }
        else {
            if (lookingForTrue == true) {
                numWays += (leftPartTrue * rightPartFalse) + (leftPartFalse * rightPartTrue);
            }
            else {
                numWays += (leftPartTrue * rightPartTrue) + (leftPartFalse * rightPartFalse);
            }
        }
    }

    return numWays;
}

int evaluateExp(string &expression) {
    int n = expression.size();
    return helper(0, n - 1, 1, expression);
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * N * N * 2)
// Space Complexity: O(N * N * 2)

// Recursive function with memoization to evaluate the expression
long long helper(int start, int end, int lookingForTrue, string &expression, vector<vector<vector<long long>>> &dp) {
    if (start > end) {
        return 0;
    }
    
    if (start == end) {
        // Base case: Evaluate single characters.
        if (lookingForTrue == 1) {
            if (expression[start] == 'T') {
                return 1;
            }
            return 0;
        }
        else {
            if (expression[start] == 'F') {
                return 1;
            }
            return 0;
        }
    }

    if (dp[start][end][lookingForTrue] != -1) {
        // If this subproblem has been solved before, return its result.
        return dp[start][end][lookingForTrue];
    }

    long long numWays = 0;

    for (int index = start + 1; index <= end - 1; index = index + 2) {
        // Recursive calls for left and right sub-expressions with different values of lookingForTrue.
        long long leftTrue = helper(start, index - 1, 1, expression, dp);

        long long leftFalse = helper(start, index - 1, 0, expression, dp);

        long long rightTrue = helper(index + 1, end, 1, expression, dp);
        
        long long rightFalse = helper(index + 1, end, 0, expression, dp);

        // Evaluate the current operator and update numWays.
        if (expression[index] == '&') {
            if (lookingForTrue == true) {
                numWays += (leftTrue * rightTrue) % mod;
            }
            else {
                numWays += ((leftTrue * rightFalse) % mod + (leftFalse * rightTrue) % mod + (leftFalse * rightFalse) % mod) % mod;
            }
        }
        else if (expression[index] == '|') {
            if (lookingForTrue == true) {
                numWays += ((leftTrue * rightTrue) % mod + (leftTrue * rightFalse) % mod + (leftFalse * rightTrue)% mod) % mod;
            }
            else {
                numWays += (leftFalse * rightFalse) % mod;
            }
        }
        else {
            if (lookingForTrue == true) {
                numWays += ((leftTrue * rightFalse) % mod + (leftFalse * rightTrue) % mod) % mod;
            }
            else {
                numWays += ((leftTrue * rightTrue) % mod  + (leftFalse * rightFalse) % mod) % mod;
            }
        }
    }

    // Store the result in the memoization table and return it.
    return dp[start][end][lookingForTrue] = numWays % mod;
}

int evaluateExp(string &expression) {
    int n = expression.size();

    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, -1)));

    return helper(0, n - 1, 1, expression, dp);
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * N * N * 2)
// Space Complexity: O(N * N * 2)

int evaluateExp(string &expression) {
    int n = expression.size();
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, 0)));

    for (int start = n - 1; start >= 0; start--) {
        for (int end = 0; end <= n - 1; end++) {
            for (int lookingForTrue = 0; lookingForTrue <= 1; lookingForTrue++) {
                if (start > end) {
                    continue;
                }
                
                if (start == end) {
                    // Base case: Evaluate single characters.
                    if (lookingForTrue == 1) {
                        if (expression[start] == 'T') {
                            dp[start][start][1] = 1;
                        }
                        else {
                            dp[start][start][1] = 0;
                        }
                    }
                    else {
                        if (expression[start] == 'F') {
                            dp[start][start][0] = 1;
                        }
                        else {
                            dp[start][start][0] = 0;
                        }
                    }

                    continue;
                }

                long long numWays = 0;

                for (int index = start + 1; index <= end - 1; index = index + 2) {
                    // Retrieve precomputed values for sub-expressions.
                    long long leftTrue = dp[start][index - 1][1];

                    long long leftFalse = dp[start][index - 1][0];

                    long long rightTrue = dp[index + 1][end][1];

                    long long rightFalse = dp[index + 1][end][0];

                    // Evaluate the current operator and update numWays.
                    if (expression[index] == '&') {
                        if (lookingForTrue == true) {
                            numWays += (leftTrue * rightTrue) % mod;
                        }
                        else {
                            numWays += (leftTrue * rightFalse) % mod;
                            numWays += (leftFalse * rightTrue) % mod;
                            numWays += (leftFalse * rightFalse) % mod;

                            numWays = numWays % mod;
                        }
                    }
                    else if (expression[index] == '|') {
                        if (lookingForTrue == true) {
                            numWays += (leftTrue * rightTrue) % mod;
                            numWays += (leftTrue * rightFalse) % mod;
                            numWays += (leftFalse * rightTrue)% mod;

                            numWays = numWays % mod;
                        }
                        else {
                            numWays += (leftFalse * rightFalse) % mod;
                        }
                    }
                    else {
                        if (lookingForTrue == true) {
                            numWays += (leftTrue * rightFalse) % mod;
                            numWays += (leftFalse * rightTrue) % mod;

                            numWays = numWays % mod;
                        }
                        else {
                            numWays += (leftTrue * rightTrue) % mod;
                            numWays += (leftFalse * rightFalse) % mod;

                            numWays = numWays % mod;
                        }
                    }
                }

                // Store the result in the table.
                dp[start][end][lookingForTrue] = numWays % mod;
            }
        }
    }

    // The final result is stored in dp[0][n-1][1].
    return dp[0][n - 1][1];
}