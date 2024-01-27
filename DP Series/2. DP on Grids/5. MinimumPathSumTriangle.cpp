#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Brute Force Recursive Solution
// Time Complexity: O(2^(N * N))
// Space Complexity: O(N)

// In this question, we started from (0, 0) instead of bottom right element because
// the minimum sum path can end at any element in last row, so if start from last
// row like previous approaches (n-1, n-1) to (0, 0) we have to start from every 
// element of last row and call function which increases the time complexity. 

// Thats why we started from (0, 0) because it is fixed starting point and ending can
// be variable thats why we take base condition as row == n-1. 

int minPathSumTriangle(int row, int col, int n, vector<vector<int>> &triangle) {
    // Base case: reached the last row, return the value

    if (row == n-1) {
        return triangle[row][col]; 
    }

    int pos1 = minPathSumTriangle(row + 1, col, n, triangle); 
    // Move to the next row, same column

    int pos2 = minPathSumTriangle(row + 1, col + 1, n, triangle); 
    // Move to the next row, next column

    return min(pos1, pos2) + triangle[row][col]; 
    // Return the minimum of the two paths plus current value
}

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size(); // Get the number of rows in the triangle

    return minPathSumTriangle(0, 0, n, triangle); 
    // Start from the top, left corner
}

// Approach 2: Memoization Solution
// Time Complexity: O(N * N)
// Space Complexity: O(N * N)

int minPathSumTriangle(int row, int col, int n, vector<vector<int>> &triangle, vector<vector<int>> &dp) {
    // Base case: reached the last row, return the value

    if (row == n-1) {
        return triangle[row][col]; 
    }

    if (dp[row][col] != -1) {
        return dp[row][col]; // If the value is already computed, return it
    }

    int pos1 = minPathSumTriangle(row + 1, col, n, triangle, dp); 
    // Move to the next row, same column

    int pos2 = minPathSumTriangle(row + 1, col + 1, n, triangle, dp); 
    // Move to the next row, next column

    return dp[row][col] = min(pos1, pos2) + triangle[row][col]; 
    // Store and return the computed value
}

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size(); // Get the number of rows in the triangle

    vector<vector<int>> dp(n, vector<int>(n, -1)); 
    // Initialize a DP table with -1 values

    return minPathSumTriangle(0, 0, n, triangle, dp); 
    // Start from the top, left corner
}

// Approach 3: Tabulation Method (Bottom Up DP)
// Time Complexity: O(N * N)
// Space Complexity: O(N * N)

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size(); // Get the number of rows in the triangle

    vector<vector<int>> dp(n, vector<int>(n, 0));
    // Initialize a DP table with zeros

    for (int col = 0; col < n; col++) { // base case (row == n-1)
        dp[n-1][col] = triangle[n-1][col];
    }

    for (int row = n-2; row >= 0; row--) { // start from n-2, base case handled
        for (int col = row; col >= 0; col--) {

            int pos1 = dp[row + 1][col]; 
            // Value from the row below, same column

            int pos2 = dp[row + 1][col + 1]; 
            // Value from the row below, next column

            dp[row][col] = min(pos1, pos2) + triangle[row][col]; 
            // Calculate and store the minimum path sum
        }
    }

    return dp[0][0]; // Return the minimum path sum from the top
}

// Approach 4: Space Optimization Method
// Time Complexity: O(N * N)
// Space Complexity: O(N)

int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size(); // Get the number of rows in the triangle

    vector<int> nextRow(n, 0); // Initialize a vector to store values of the next row

    for (int col = 0; col < n; col++) { // base case (row == n-1)
       nextRow[col] = triangle[n-1][col];
    }

    for (int row = n-2; row >= 0; row--) {
        vector<int> currRow(n, 0); // Initialize a vector for the current row

        for (int col = row; col >= 0; col--) {
            int pos1 = nextRow[col]; 
            // Value from the row below, same column

            int pos2 = nextRow[col + 1]; 
            // Value from the row below, next column

            currRow[col] = min(pos1, pos2) + triangle[row][col]; 
            // Calculate and store the minimum path sum
        }

        nextRow = currRow; // Update the nextRow vector for the next iteration
    }

    return nextRow[0]; // Return the minimum path sum from the top
}