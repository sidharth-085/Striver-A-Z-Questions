#include <iostream>
#include <vector>
using namespace std;

// In this question, we have to find the total number of LIS in the given array.
// To find, we simply make a count array, which count everytime when duplicate 
// length of LIS comes for every ith index while finding longest LIS. At last, add
// all the count of LIS, together which has highest length to get the answer.

// Time Complexity: O(N * N)
// Space Complexity: O(2 * N)

int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();  // Get the size of the input vector `nums`.

    vector<int> dp(n, 1);  // Create a dynamic programming array `dp` of size `n`, initialized to 1.
    
    vector<int> count(n, 1);  // Create an array `count` of size `n` to keep track of the count of longest increasing subsequences ending at each index, initialized to 1.

    int maxi = 1;  // Initialize the variable `maxi` to 1, which will store the length of the longest increasing subsequence.

    // Loop through the elements in `nums` to calculate the length of the longest increasing subsequence.
    for (int index = 1; index < n; index++) {
        for (int prevIndex = index - 1; prevIndex >= 0; prevIndex--) {
            if (nums[prevIndex] < nums[index]) {
                int possibleAns = 1 + dp[prevIndex];  // Calculate the length of a potential longer subsequence.

                if (possibleAns == dp[index]) {
                    // If the possible length is the same as the current maximum length, update the count.
                    count[index] = count[index] + count[prevIndex];
                } else if (possibleAns > dp[index]) {
                    // If the possible length is greater than the current maximum length, update `dp` and `count`.
                    dp[index] = possibleAns;
                    count[index] = count[prevIndex];
                }
            }
        }
        
        // Update `maxi` to keep track of the maximum length found so far.
        maxi = max(maxi, dp[index]);
    }

    int ans = 0;  // Initialize the variable `ans` to store the final answer.

    // Loop through the `dp` and `count` arrays to find subsequences with maximum length and sum their counts.
    for (int index = 0; index < n; index++) {
        if (dp[index] == maxi) {
            ans = ans + count[index];  // Add the count of subsequences with the maximum length to `ans`.
        }
    }

    return ans;  // Return the total count of longest increasing subsequences.
}