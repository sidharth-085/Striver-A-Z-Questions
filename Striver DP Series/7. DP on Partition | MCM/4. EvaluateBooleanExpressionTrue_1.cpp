#include <iostream>
#include <vector>
using namespace std;
#define ll long long

int mod = 1e9 + 7;

// Approach 1: Recursive Approach
// Time Complexity: Exponential
// Space Complexity: O(N)

pair<ll, ll> helper(int start, int end, string &exp) {
    // Base case: If we have a single character (either 'T' or 'F') in the expression.
    if (start == end) {
        if (exp[start] == 'T') {
            return {1, 0}; // If 'T', return (True, False)
        }
        return {0, 1};     // If 'F', return (False, True)
    }

    pair<ll, ll> numWays; // Initialize the result pair for the current expression.

    // Iterate through the expression, considering operators and splitting into sub-expressions.
    for (int index = start + 1; index <= end - 1; index = index + 2) {
        // Recursively calculate the left and right sub-expressions.
        pair<ll, ll> leftPart = helper(start, index - 1, exp); 
        
        // splitting is based on operators, at every odd index there will
        // be an operator, so we used them as partitions.

        pair<ll, ll> rightPart = helper(index + 1, end, exp);

        // Check the operator at the current index in the expression.
        if (exp[index] == '&') {
            // Logical AND operator
            numWays.first += (leftPart.first * rightPart.first) % mod; // True case
            numWays.second += (leftPart.first * rightPart.second) % mod; // False case
            numWays.second += (leftPart.second * rightPart.first) % mod; // False case
            numWays.second += (leftPart.second * rightPart.second) % mod; // False case
            numWays.second = numWays.second % mod; // Modulo operation to keep values within bounds.
        }
        else if (exp[index] == '|') {
            // Logical OR operator
            numWays.first += (leftPart.first * rightPart.first) % mod; // True case
            numWays.first += (leftPart.first * rightPart.second) % mod; // True case
            numWays.first += (leftPart.second * rightPart.first) % mod; // True case
            numWays.first = numWays.first % mod; // Modulo operation
            numWays.second += (leftPart.second * rightPart.second) % mod; // False case
        }
        else {
            // Logical XOR operator
            numWays.first += (leftPart.first * rightPart.second) % mod; // True case
            numWays.first += (leftPart.second * rightPart.first) % mod; // True case
            numWays.first = numWays.first % mod; // Modulo operation
            numWays.second += (leftPart.first * rightPart.first) % mod; // False case
            numWays.second += (leftPart.second * rightPart.second) % mod; // False case
            numWays.second = numWays.second % mod; // Modulo operation
        }
    }

    numWays.first = numWays.first % mod; // Modulo operation for the final result
    numWays.second = numWays.second % mod; // Modulo operation for the final result

    return numWays; // Return the calculated results for this sub-expression.
}

int evaluateExp(string & exp) {
    int n = exp.size();

    pair<ll, ll> rand = {-1, -1};

    // Call the helper function to evaluate the expression and return the 'True' count.
    auto ans = helper(0, n - 1, exp); 

    return ans.first;
}

// Approach 2: Memoization Approach
// Time Complexity: O(N * N * N)
// Space Complexity: O(N * N * 2)

pair<ll, ll> helper(int start, int end, string &exp, vector<vector<pair<ll, ll>>> &dp) {
    if (start == end) {
        if (exp[start] == 'T') {
            return {1, 0};
        }
        return {0, 1};
    }

    pair<ll, ll> rand = {-1, -1};

    if (dp[start][end] != rand) {
        return dp[start][end];
    }

    pair<ll, ll> numWays;

    for (int index = start + 1; index <= end - 1; index = index + 2) {
        pair<ll, ll> leftPart = helper(start, index - 1, exp, dp);
        
        pair<ll, ll> rightPart = helper(index + 1, end, exp, dp);

        if (exp[index] == '&') {
            numWays.first += (leftPart.first * rightPart.first) % mod;
            
            numWays.second += (leftPart.first * rightPart.second) % mod;
            numWays.second += (leftPart.second * rightPart.first) % mod;
            numWays.second += (leftPart.second * rightPart.second) % mod;
            numWays.second = numWays.second % mod;
        }
        else if (exp[index] == '|') {
            numWays.first += (leftPart.first * rightPart.first) % mod;
            numWays.first += (leftPart.first * rightPart.second) % mod;
            numWays.first += (leftPart.second * rightPart.first) % mod;
            numWays.first = numWays.first % mod;

            numWays.second += (leftPart.second * rightPart.second) % mod;
            
        }
        else {
            numWays.first += (leftPart.first * rightPart.second) % mod;
            numWays.first += (leftPart.second * rightPart.first) % mod; 
            numWays.first = numWays.first % mod;

            numWays.second += (leftPart.first * rightPart.first) % mod;
            numWays.second += (leftPart.second * rightPart.second) % mod;
            numWays.second = numWays.second % mod;
        }
    }

    numWays.first = numWays.first % mod;
    numWays.second = numWays.second % mod;

    return dp[start][end] = numWays;
}

// Approach 3: Tabulation Approach
// Time Complexity: O(N * N * N)
// Space Complexity: O(N * N * 2)

int evaluateExp(string & exp) {
    int n = exp.size();

    pair<ll, ll> rand = {-1, -1};

    vector<vector<pair<ll, ll>>> dp(n, vector<pair<ll, ll>>(n, rand));

    auto ans = helper(0, n - 1, exp, dp); 

    return ans.first;
}

int evaluateExp(string & exp) {
    int n = exp.size();

    pair<ll, ll> rand = {0, 0};

    vector<vector<pair<ll, ll>>> dp(n, vector<pair<ll, ll>>(n, rand));

    for (int start = n - 1; start >= 0; start--) {
        for (int end = 0; end <= n - 1; end++) {
            if (start == end) {
                if (exp[start] == 'T') {
                    dp[start][start] = {1, 0};
                }
                else {
                    dp[start][start] = {0, 1};
                }
                
                continue;
            }

            pair<ll, ll> numWays;

            for (int index = start + 1; index <= end - 1; index = index + 2) {
                pair<ll, ll> leftPart = dp[start][index - 1];
                
                pair<ll, ll> rightPart = dp[index + 1][end];

                if (exp[index] == '&') {
                    numWays.first += (leftPart.first * rightPart.first) % mod;
                    
                    numWays.second += (leftPart.first * rightPart.second) % mod;
                    numWays.second += (leftPart.second * rightPart.first) % mod;
                    numWays.second += (leftPart.second * rightPart.second) % mod;
                    numWays.second = numWays.second % mod;
                }
                else if (exp[index] == '|') {
                    numWays.first += (leftPart.first * rightPart.first) % mod;
                    numWays.first += (leftPart.first * rightPart.second) % mod;
                    numWays.first += (leftPart.second * rightPart.first) % mod;
                    numWays.first = numWays.first % mod;

                    numWays.second += (leftPart.second * rightPart.second) % mod;
                    
                }
                else {
                    numWays.first += (leftPart.first * rightPart.second) % mod;
                    numWays.first += (leftPart.second * rightPart.first) % mod; 
                    numWays.first = numWays.first % mod;

                    numWays.second += (leftPart.first * rightPart.first) % mod;
                    numWays.second += (leftPart.second * rightPart.second) % mod;
                    numWays.second = numWays.second % mod;
                }
            }

            numWays.first = numWays.first % mod;
            numWays.second = numWays.second % mod;

            dp[start][end] = numWays;
        }
    }

    pair<ll, ll> ans = dp[0][n - 1];

    return ans.first;
}