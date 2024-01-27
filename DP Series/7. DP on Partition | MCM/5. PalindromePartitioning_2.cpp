#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Approach 1: Brute Force Recursive Solution
// Time Complexity: O(N^3)
// Space Complexity: O(N^2)

// Function to check if a substring is a palindrome
bool checkPalindrome(string str, int start, int end) {
    while (start <= end) {
        if (str[start] != str[end]) {
            return false;
        }

        start++;
        end--;
    }

    return true;
}

// Function to find the minimum number of partitions to make all substrings palindromic
int palindromePartition(string str, int index, int n) {
    // If we've reached the end of the string, no more partitions needed
    if (index == n) {
        return 0;
    }

    int mini = INT_MAX; // Initialize with a large value

    // Iterate over possible partition points
    for (int partitionIndex = index; partitionIndex < n; partitionIndex++) {
        // If the substring from 'index' to 'partitionIndex' is a palindrome

        if (checkPalindrome(str, index, partitionIndex) == true) {
            // Calculate the number of ways after making this partition
            int ways = 1 + palindromePartition(str, partitionIndex + 1, n);

            // Update 'mini' with the minimum number of partitions
            mini = min(mini, ways);
        }
    }

    return mini; 
    // Return the minimum number of partitions for the current substring
}

// Main function to find the minimum partitions for a given string

int palindromePartitioning(string str) {
    int n = str.size();

    return palindromePartition(str, 0, n) - 1; 
    // Return the result of the partitioning - 1 because it always count partition at 
    // ending so we have to minus 1
}

// Approach 2: Using Memoization 
// Time Complexity: O(N^2)
// Space Complexity: O(N)

int palindromePartition(string str, int index, int n, vector<int> &dp) {
    // If we've reached the end of the string, no more partitions needed
    if (index == n) {
        return 0;
    }

    // If the minimum partitions for this index have been calculated before, 
    // return the result

    if (dp[index] != -1) {
        return dp[index];
    }

    int mini = INT_MAX; // Initialize with a large value

    // Iterate over possible partition points
    for (int partitionIndex = index; partitionIndex < n; partitionIndex++) {
        // If the substring from 'index' to 'partitionIndex' is a palindrome

        if (checkPalindrome(str, index, partitionIndex) == true) {
            // Calculate the number of ways after making this partition
            int ways = 1 + palindromePartition(str, partitionIndex + 1, n, dp);

            // Update 'mini' with the minimum number of partitions
            mini = min(mini, ways);
        }
    }

    dp[index] = mini; // Store the result for this index to avoid recomputation

    return mini; 

    // Return the minimum number of partitions for the current substring
}

// Main function to find the minimum partitions for a given string

int palindromePartitioning(string str) {
    int n = str.size(); // Get the length of the input string

    vector<int> dp(n, -1);

    // Call the helper function with the dp array and subtract 1 from the final result
    return palindromePartition(str, 0, n, dp) - 1;
}

// Approach 3: Tabulation Method (by Using 2-D Check Palindrome DP)
// Time Complexity: O(N^2) (less time)
// Space Complexity: O(N^2) (more space)

int palindromePartitioning(string str) {
    int n = str.size(); // Get the length of the input string

    // Create a 2D array to store whether substrings are palindromes or not
    vector<vector<bool>> palCheck(n, vector<bool>(n, false));

    // Fill the palCheck array using dynamic programming approach
    for (int j = 0; j < n; j++) {
        for (int i = 0; i <= j; i++) {
            // Check if the substring from 'i' to 'j' is a palindrome

            if (str[i] == str[j] && (j - i + 1 <= 2 || palCheck[i + 1][j - 1] == true)) {
                palCheck[i][j] = true;
            }
        }
    }

    vector<int> dp(n + 1, 0);

    dp[n] = 0; // Base case: no partition needed for an empty substring

    // Iterate over substrings in reverse order, filling the dp array

    for (int index = n - 1; index >= 0; index--) {
        int minCuts = INT_MAX; // Initialize with a large value

        // Iterate over possible partition points
        for (int partitionIndex = index; partitionIndex < n; partitionIndex++) {
            // If the substring from 'index' to 'partitionIndex' is a palindrome
            if (palCheck[index][partitionIndex] == true) {
                // Calculate the number of ways after making this partition
                int numCuts = 1 + dp[partitionIndex + 1];

                // Update 'mini' with the minimum number of partitions
                minCuts = min(minCuts, numCuts);
            }
        }

        dp[index] = minCuts;
    }

    return dp[0] - 1;
}

// Approach 4: Tabulation Method (less Space used)
// Time Complexity: O(N * N * N) (more time)
// Space Complexity: O(N) (less space)

int palindromePartitioning(string str) {
    int n = str.size(); // Get the length of the input string

    vector<int> dp(n + 1, 0);

    dp[n] = 0; // Base case: no partition needed for an empty substring

    // Iterate over substrings in reverse order, filling the dp array

    for (int index = n - 1; index >= 0; index--) {
        int minCuts = INT_MAX; // Initialize with a large value

        // Iterate over possible partition points
        for (int partitionIndex = index; partitionIndex < n; partitionIndex++) {
            // If the substring from 'index' to 'partitionIndex' is a palindrome
            if (checkPalindrome(str, index, partitionIndex) == true) {
                // Calculate the number of ways after making this partition
                int numCuts = 1 + dp[partitionIndex + 1];

                // Update 'mini' with the minimum number of partitions
                minCuts = min(minCuts, numCuts);
            }
        }

        dp[index] = minCuts;
    }

    return dp[0] - 1;
}