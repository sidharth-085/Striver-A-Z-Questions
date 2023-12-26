#include <iostream>
#include <vector>
using namespace std;

// In this question, we have given that a robber has to loot the houses but there is 
// condition that robber can't loot two adjacent houses. Then, if he loot 1st house
// then, robber has to skip 2nd house and if he doesn't loot 1st house, he can loot 
// 2nd house.

// Approach 1: Brute force Recursive Solution
// Time Complexity: O(2^N)
// Space Complexity: O(2^N)

int robHelper(vector<int> &nums, int index) {
    // when we reached to first house, we have to loot it because we cant loot prev 
    // and before prev now

    if (index == 0) { 
        return nums[0];
    }

    // step 1: when all houses has been looted, return no money we will get.

    if (index < 0) {
        return 0;
    }

    // step 2; take and not take approach (rob last house & not rob first house)

    int robLastHouse = nums[index] + robHelper(nums, index-2);

    int skipLastHouse = robHelper(nums, index-1);

    // step 3: find the find the maximum of both 

    return max(robLastHouse, skipLastHouse);
}

int rob(vector<int>& nums) {
    int n = nums.size();

    return robHelper(nums, n - 1); // make an helper function to solve the question
}

// Approach 2: Memoization Solution
// Time Complexity: O(N)
// Space Complexity: O(N)

int robHelper(vector<int> &nums, int index, vector<int> &dp) {
    // when we reached to first house, we have to loot it because we cant loot prev 
    // and before prev now

    if (index == 0) {
        return nums[0];
    }

    if (index < 0) {
        return 0;
    }

    if (dp[index] != -1) {
        return dp[index];
    }

    int robLastHouse = nums[index] + robHelper(nums, index - 2, dp);

    int skipLastHouse = robHelper(nums, index - 1, dp);

    return dp[index] = max(robLastHouse, skipLastHouse);
}

int rob(vector<int>& nums) {
    int n = nums.size();
    
    vector<int> dp(n, -1);

    return robHelper(nums, n - 1, dp);
}

// Approach 3: Iterative DP (Bottom Up DP)
// Time Complexity: O(N)
// Space Complexity: O(N)

int rob(vector<int>& nums) {
    int n = nums.size();
    
    vector<int> dp(n); // make the dp array of size n for index starting from n-1 to 0

    dp[0] = nums[0]; // base case of recursion

    for (int i = 1; i < n; i++) { // start from 1 to n - 1(bottom up)
        int robLastHouse = nums[i];

        if (i > 1) {
            robLastHouse = nums[i] + dp[i-2]; // add beforePrev only if index is more than 1
        }

        int skipLastHouse = dp[i-1];

        dp[i] = max(robLastHouse, skipLastHouse);
    }

    return dp[n - 1]; // return the answer for last house n-1 
}

// Approach 4: Space Optimization
// Time Complexity: O(N)
// Space Complexity: O(1)

int rob(vector<int>& nums) {
    int n = nums.size();

    int robPrev = nums[0]; // replaced variable in place of dp[0]
    int robBeforePrev = 0; 
    // replaced variable in place of dp[-1] for which we have to apply check in above tabulation method

    for (int i = 1; i < n; i++) {
        int robLastHouse = nums[i] + robBeforePrev; 
        // rob last house and add the rob amount and skip prev house.

        int skipLastHouse = robPrev;
        // rob prev house skipping last one

        int maxi = max(robLastHouse, skipLastHouse);
        // take maximum of both and store as ans

        robBeforePrev = robPrev; // update robBeforePrev to robPrev

        robPrev = maxi; // and update robPrev to maxi
    }

    return robPrev;
}