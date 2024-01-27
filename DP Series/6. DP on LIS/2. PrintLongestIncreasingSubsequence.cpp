#include <iostream>
#include <vector>
using namespace std;

// In this approach, we continously storing the previous indices of LIS in hash 
// array which further helps to get the LIS. Also, we find the lastIndex where we 
// get the maximum length of increasing subsequence. So that, we can start from 
// there.

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
			// Check if the current element is greater than the previous element.
			if (nums[prevIndex] < nums[index]) {
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