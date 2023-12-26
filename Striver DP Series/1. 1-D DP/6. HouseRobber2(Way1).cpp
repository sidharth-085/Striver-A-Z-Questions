#include <iostream>
#include <vector>
using namespace std;

// This question is same as House Robber 1, just one difference is the houses are in
// circle. It means if last house is looted, first cant be looted and vice versa.

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
    // for houses in circle, we can take only one house out of first and last house
    // so we skip first house and find answer for remaining houses

    int n = nums.size();

    if (n == 1) {
        return nums[0];
    }

    vector<int> skipFirstHouse(nums.begin() + 1, nums.end());

    // then, we skip last house and keep remaining houses and find answer
    vector<int> skipLastHouse(nums.begin(), nums.end() - 1);

    int skipFirst = robHelper(skipFirstHouse, skipFirstHouse.size() - 1); 
    // get answer by skipping first house

    int skipLast = robHelper(skipLastHouse, skipLastHouse.size() - 1);
    // get answer by skipping last house

    return max(skipFirst, skipLast); // take maximum of both answers
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

    if (n == 1) {
        return nums[0];
    }
    
    vector<int> dp(n, -1);

    vector<int> skipFirstHouse(nums.begin() + 1, nums.end());

    vector<int> skipLastHouse(nums.begin(), nums.end() - 1);

    int skipFirst = robHelper(skipFirstHouse, skipFirstHouse.size() - 1, dp); 

    dp.clear();
    dp.resize(n, -1);

    int skipLast = robHelper(skipLastHouse, skipLastHouse.size() - 1, dp);

    return max(skipFirst, skipLast); // take maximum of both answers
}

// Approach 3: Iterative DP (Bottom Up DP)
// Time Complexity: O(N)
// Space Complexity: O(N)

int robHelper(vector<int>& nums) {
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

int rob(vector<int>& nums) {
    int n = nums.size();

    if (n == 1) {
        return nums[0];
    }

    vector<int> skipFirstHouse(nums.begin() + 1, nums.end());

    vector<int> skipLastHouse(nums.begin(), nums.end() - 1);

    int skipFirst = robHelper(skipFirstHouse); 

    int skipLast = robHelper(skipLastHouse);

    return max(skipFirst, skipLast); // take maximum of both answers
}

// Approach 4: Space Optimization
// Time Complexity: O(N)
// Space Complexity: O(1)

int robHelper(vector<int>& nums) {
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

int rob(vector<int> &nums) {
    int n = nums.size();

    if (n == 1) {
        return nums[0];
    }

    vector<int> skipFirstHouse(nums.begin() + 1, nums.end());

    vector<int> skipLastHouse(nums.begin(), nums.end() - 1);

    int skipFirst = robHelper(skipFirstHouse); 

    int skipLast = robHelper(skipLastHouse);

    return max(skipFirst, skipLast); // take maximum of both answers
}