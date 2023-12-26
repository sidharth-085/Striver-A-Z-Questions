#include <iostream>
#include <vector>
using namespace std;

// Longest Bitonic Subsequence is the subsequence which is either strictly increasing
// at some point and then strictly decreasing or Strictly Increasing completely
// or Strictly Decreasing completely. So, we will calculate as the dp array, dp[i] 
// tells us that longest increasing subsequendce till ith index. So, we will get the
// dp array filled for LIS. Then, we reverse the nums array and try toh get LIS again
// which will be Longest Decreasing Subsequence. Now, we know that till every index
// i, the longest increasing and decreasing subsequence. When we add them we get 
// the length of Longest Bitonic Subsequence but, minus 1 because the ith index value
// will be counted twice as we see LIS and LDS together. So, (lis[i] + lds[i] - 1)
// the maximum one will be our answer.

// Time Complexity: O(N * N)
// Space Complexity: O(2 * N)

void longestIncreasingSubsequence(vector<int> &nums, int n, vector<int> &dp) {
    for (int index = 1; index < n; index++) {
        for (int prevIndex = index - 1; prevIndex >= 0; prevIndex--) {
            // Check if the current element is greater than the previous element.
            if (nums[prevIndex] < nums[index]) {
                // Calculate a possible answer for the LIS at the current index.
                int possibleAns = 1 + dp[prevIndex];

                // Update the LIS value at the current index, taking the maximum
                // of the current LIS value and the new possible answer.
                dp[index] = max(dp[index], possibleAns); 
            }
        }
    }
}

int longestBitonicSubsequence(vector<int>& nums, int n) {
    // Initialize a vector 'lis' to store the Longest Increasing Subsequence
    // for the 'nums' array.
    vector<int> lis(n, 1);

    // Calculate the LIS for the 'nums' array.
    longestIncreasingSubsequence(nums, n, lis);

    // Initialize a vector 'lds' to store the Longest Decreasing Subsequence
    // for the 'nums' array in reverse order.
    vector<int> lds(n, 1);

    // Reverse the 'nums' array to calculate the LDS.
    reverse(nums.begin(), nums.end());

    // Calculate the LDS for the reversed 'nums' array.
    longestIncreasingSubsequence(nums, n, lds);

    // Reverse the 'lds' vector to get the actual Longest Decreasing Subsequence.
    reverse(lds.begin(), lds.end());

    // Initialize 'ans' to store the maximum length of the Bitonic Subsequence.
    int ans = 0;

    // Calculate the Bitonic Subsequence length by summing LIS and LDS for each index
    // and subtracting 1 since the element at the current index is counted twice.
    for (int i = 0; i < n; i++) {
        ans = max(ans, lis[i] + lds[i] - 1);
    }

    // Return the maximum Bitonic Subsequence length as the result.
    return ans;
}
