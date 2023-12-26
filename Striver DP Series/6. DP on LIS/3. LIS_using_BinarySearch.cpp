#include <iostream>
#include <vector>
using namespace std;

// In this approach, we are using the lower bound function to find the just big
// element than current element at every index. If we found, we can replace it and
// not, we have to add it for LIS.

// Time Complexity: O(N * Log N)
// Space Complexity: O(N)

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();

    // Create a vector 'ans' to store the increasing subsequence.
    vector<int> ans;
    
    // Initialize 'ans' with the first element of 'nums'.
    ans.push_back(nums[0]);
    
    // Iterate through the elements of 'nums' starting from the second element.
    for (int index = 1; index < n; index++) {
        // Use lower_bound to find the position where 'nums[index]' can be inserted while maintaining order.
        auto it = lower_bound(ans.begin(), ans.end(), nums[index]);

        // If 'it' points to the end of 'ans', it means 'nums[index]' is greater than all elements in 'ans'.
        if (it == ans.end()) {
            // In this case, we add 'nums[index]' to 'ans' because it extends the subsequence.
            ans.push_back(nums[index]);
        }
        else {
            // If 'it' points to a valid position, it means we can replace the element at 'it' with 'nums[index'
            // because we found a smaller element to extend the subsequence.
            *it = nums[index];
        }
    }

    // The size of 'ans' is the length of the Longest Increasing Subsequence (LIS).
    return ans.size();
}