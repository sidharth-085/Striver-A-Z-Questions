#include <iostream>
#include <vector>
using namespace std;

// This problem is similar to LIS, but there is some differences also. In this 
// question, we have to find the largest subset which has every element divisible
// by either each other. So, to solve this, we can apply the sorting so that
// small elements comes at the starting. Then, we know that if the array is sorted
// and b is divisible by a, and c is divisible by b, therefore, c is also divisible
// by a. Therefore, using this logic we will find LONGEST DIVISIBLE SUBSEQUENCE by
// applying sorting to the main array. Just change the nums[prevIndex] < nums[index]
// condition to (nums[index] % nums[prevIndex] == 0) and other remains same.

// Time Complexity: O(N * N)
// Space Complexity: O(N)

vector<int> printingLongestIncreasingSubsequence(vector<int> nums, int n) {
	// Initialize a dynamic programming array to store the length of the longest increasing subsequence ending at each position.
	vector<int> dp(n, 1);

	// Initialize a hash array to keep track of the previous index contributing to the longest increasing subsequence ending at each position.
	vector<int> hash(n);

    for (int i=0; i<n; i++) {
		hash[i] = i;
	}

	// Initialize a variable to keep track of the maximum length of the longest increasing subsequence.
	int maxi = 1;

	// Initialize a variable to keep track of the index of the last element in the longest increasing subsequence.
	int lastIndex = 0;

	// Iterate through the elements in the 'nums' array.
	for (int index = 1; index < n; index++) {
		// For each element, compare it with previous elements.
		for (int prevIndex = index - 1; prevIndex >= 0; prevIndex--) {
			// Check if the current element is divisible by the previous element.
			if (nums[index] % nums[prevIndex] == 0) {
				// Calculate the length of the increasing subsequence ending at the current element.
				int possibleAns = 1 + dp[prevIndex];

				// If this length is greater than the previously calculated length, update the dp array and the hash array.
				if (possibleAns > dp[index]) {
					dp[index] = possibleAns;
					hash[index] = prevIndex;
				}
			}
		}

		// Update 'maxi' and 'lastIndex' if the length of the current increasing subsequence is greater than the previous maximum.
		if (dp[index] > maxi) {
			maxi = dp[index];
			lastIndex = index;
		}
	}

	// Create a vector 'ans' to store the longest increasing subsequence.
	vector<int> ans(maxi);

    for (int index = maxi - 1; index >= 0; index--) {
        ans[index] = nums[lastIndex];

        lastIndex = hash[lastIndex];
    }

	// Return the longest increasing subsequence.
	return ans;
}