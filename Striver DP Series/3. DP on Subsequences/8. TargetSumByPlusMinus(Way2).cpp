#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Approach 1: Recursive Approach 
// Time Complexity: O(2^N)
// Space Complexity: O(N)

int findTargetSumWaysHelper(int index, int target, vector<int> &arr) {
    if (index == 0) {
        if (target == 0 && arr[0] == 0) {
            return 2;
        }
        if (target == arr[0] || target == -arr[0]) {
            return 1;
        }

        return 0;
    } 

    int plusElement = findTargetSumWaysHelper(index - 1, target - arr[index], arr);

    int minusElement = findTargetSumWaysHelper(index - 1, target + arr[index], arr);

    return plusElement + minusElement;
}

int findTargetSumWays(vector<int>& nums, int amount) {
    int n = nums.size();

    return findTargetSumWaysHelper(n-1, amount, nums);
}

// Approach 2: Memoization Approach (Top Down DP)
// Time Complexity: O(N * T)
// Space Complexity: O(N * T)

int findTargetSumWaysHelper(int index, int target, vector<int> &arr, map<pair<int, int>, int> &dp) {
    if (index == 0) {
        if (target == 0 && arr[0] == 0) {
            return 2;
        }
        if (target == arr[0] || target == -arr[0]) {
            return 1;
        }

        return 0;
    }

    if (dp.find({index, target}) != dp.end()) {
        return dp[{index, target}];
    }

    int plusElement = findTargetSumWaysHelper(index - 1, target - arr[index], arr, dp);

    int minusElement = findTargetSumWaysHelper(index - 1, target + arr[index], arr, dp);

    return dp[{index, target}] = plusElement + minusElement;
}

int findTargetSumWays(vector<int>& nums, int amount) {
    int n = nums.size();

    map<pair<int, int>, int> dp;

    return findTargetSumWaysHelper(n-1, amount, nums, dp);
}

// Approach 3: Tabulation Method (Bottom Up DP)
// Time Complexity: O(N * T)
// Space Complexity: O(N * T)

int findTargetSumWays(vector<int>& nums, int amount) {
    int n = nums.size();

    map<pair<int, int>, int> dp;

    if (nums[0] == 0) {
        dp[{0, 0}] = 2;
    }
    else {
        dp[{0, nums[0]}] = 1;
        dp[{0, -nums[0]}] = 1;
    }

    int totalSum = 0;

    for (int i=0; i<n; i++) {
        totalSum = totalSum + nums[i];
    }

    for (int index = 1; index < n; index++) {
        for (int target = -totalSum; target <= amount + totalSum; target++) {
            int plusElement = dp[{index - 1, (target - nums[index])}];    

            int minusElement = dp[{index - 1, (target + nums[index])}];

            dp[{index, target}] = plusElement + minusElement;                     
        }
    }

    return dp[{n-1, amount}];
}