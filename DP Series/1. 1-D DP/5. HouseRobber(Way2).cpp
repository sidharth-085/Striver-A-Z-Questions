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

int robHelper(vector<int> &nums, int si, int n) {
    // step 1: when si reaches to n or n + 1 (in case when si becomes n-1 and we 
    // call robFirstHouse si+2, it reaches to n + 1), return 0.

    if (si == n || si == n + 1) {
        return 0;
    }

    // step 2; take and not take approach (rob first house & not rob first house)

    int robFirstHouse = nums[si] + robHelper(nums, si + 2, n);

    int notRobFirstHouse = robHelper(nums, si + 1, n);

    // step 3: find the find the maximum of both 

    return max(robFirstHouse, notRobFirstHouse);
}

int rob(vector<int>& nums) {
    int n = nums.size();

    return robHelper(nums, 0, n); // make an helper function to solve the question

    // remembe we can do with n to 0 instead of 0 to n.
}

// Approach 2: Memoization Solution
// Time Complexity: O(N)
// Space Complexity: O(N)

int robHelper(vector<int> &nums, int si, int n, vector<int> &dp) {
    if (si == n || si == n + 1) {
        return 0;
    }

    if (dp[si] != -1) {
        return dp[si];
    }

    int robFirstHouse = nums[si] + robHelper(nums, si + 2, n, dp);

    int notRobFirstHouse = robHelper(nums, si + 1, n, dp);

    return dp[si] = max(robFirstHouse, notRobFirstHouse);
}

int rob(vector<int>& nums) {
    int n = nums.size();
    
    vector<int> dp(n + 1, -1);

    return robHelper(nums, 0, n, dp);

    // remembe we can do with n to 0 instead of 0 to n.
}

// Approach 3: Iterative DP (Bottom Up DP)
// Time Complexity: O(N)
// Space Complexity: O(N)

int rob(vector<int>& nums) {
    int n = nums.size();
    
    vector<int> dp(n + 2); // make the dp array of size n+2 because si can go to n + 1 

    dp[n] = 0; // if si is n, answer should be 0.

    dp[n + 1] = 0; // and if it reaches to n + 1, again answer is 0.

    for (int i = n - 1; i >= 0; i--) { // start from n - 2 to 0 (bottom up)
        int robFirstHouse = nums[i] + dp[i + 2];

        int notRobFirstHouse = dp[i+1];

        dp[i] = max(robFirstHouse, notRobFirstHouse);
    }

    return dp[0]; // return the answer if si is 0. 

    // remembe we can do with 0 to n (bottom up).
}

// Approach 4: Space Optimization
// Time Complexity: O(N)
// Space Complexity: O(1)

int rob(vector<int>& nums) {
    int n = nums.size();

    int robNext = 0; // replaced variable in place of dp[n]
    int robAfterNext = 0; // replaced variable in place of dp[n+1]

    for (int i = n - 1; i >= 0; i--) {
        int robFirstHouse = nums[i] + robAfterNext; 
        // rob first house and add the rob amount and skip next one.

        int notRobFirstHouse = robNext;
        // rob next one skipping first one

        int maxi = max(robFirstHouse, notRobFirstHouse);
        // take maximum of both and store as ans

        robAfterNext = robNext; // update robAfterNext to robNext

        robNext = maxi; // and update robNext to maxi
    }

    // remembe we can do with 0 to n (bottom up).

    return robNext;
}