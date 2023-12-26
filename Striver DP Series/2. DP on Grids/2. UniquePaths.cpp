#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Recursive Method, whenever we reached at final destination we return 1

// Time Complexity: O(2^(N*M))
// Space Complexity: O(max(N, M)) [Due to recursion stack]
// N is number of rows
// M is number of cols

int uniquePathsHelper(int row, int col) {
    if (row == 0 && col == 0) { // when we reached to destination, we found 1 way
        return 1;
    }

    if (row < 0 || col < 0) {
        return 0;
    }

    int right = uniquePathsHelper(row, col - 1);

    int down = uniquePathsHelper(row - 1, col);

    return right + down; // for all ways sum it up.
}

int uniquePaths(int n, int m) {
    return uniquePathsHelper(n-1, m-1);
}

// Optimized Brute Force: Memoization Approach

// Time Complexity: O(M * N)
// Space Complexity: O(N*M) (due to memoization grid)

int uniquePathsHelper(int row, int col, vector<vector<int>> &dp) {
    if (row == 0 && col == 0) { // when we reached to destination, we found 1 way
        return 1;
    }

    if (row < 0 || col < 0) { // when reached out of bounds, return 0.
        return 0;
    }

    if (dp[row][col] != -1) { 
        return dp[row][col];
    }

    int right = uniquePathsHelper(row, col - 1, dp); // find right

    int down = uniquePathsHelper(row - 1, col, dp); // find left

    return dp[row][col] = right + down; // for all ways sum it up.
}

int uniquePaths(int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, -1));

    return uniquePathsHelper(n-1, m-1, dp);
}

// Optimized DP Solution
// Time Complexity: O(N * M)
// Space Complexity: O(N * M)

int uniquePaths(int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m));

    // step 1: base case, if row is 0 means only 1 row, only one path is there and
    // if only one col is there, only 1 path is there 

    for (int i=0; i<n; i++) {
        dp[i][0] = 1;
    }
    
    for (int i=0; i<m; i++) {
        dp[0][i] = 1;
    }

    // step 2: make the loops from 1 to n-1 and 1 to m-1 and copy the recurrence 
    // relation from memoization

    for (int i=1; i<n; i++) {
        for (int j=1; j<m; j++) {
            int right = dp[i][j-1]; // find right

            int down = dp[i-1][j]; // find down

            dp[i][j] = right + down;
        }
    }

    return dp[n-1][m-1]; // return the ways when reached at n-1 and m-1.
}

// Space Optimized DP approach
// Time Complexity: O(N * M)
// Space Complexity: O(N)

int uniquePaths(int n, int m) {
    // in above approach, we can see that for right (left in that case) we need (j-1)th 
    // value of dp and for down (up in that case) we need (i-1)th value of dp.

    vector<int> prevRow(m, 1);
    // we can maintain dp for prevRow for (j-1)th value of dp and currRow for (i-1)th
    // value of dp

    // initially prevRow are 1, bcoz for first row, every value in dp is 1 
    // (base case when row == 0).

    for (int i=1; i<n; i++) {
        vector<int> currRow(m, 0); 
        currRow[0] = 1; 
        // for every curr row, first element is 1 (base case when col == 0).

        for (int j=1; j<m; j++) {
            int right = currRow[j-1]; // for right, just go one back in currRow

            int down = prevRow[j]; // for down, just go above which is in prevRow

            currRow[j] = right + down;
        }

        prevRow = currRow; // update the prevRow for next row computation
    }

    return prevRow[m-1];
    // return the last element of last row i.e. destination.
}