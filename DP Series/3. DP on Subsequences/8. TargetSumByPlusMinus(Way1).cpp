#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Approach 1: Recursive Approach
// Time Complexity: O(2 ^ N)
// Space Complexity: O(N)

int countSubsets(int index, int sum, vector<int> &arr, int n) {
    if (index == 0) {
        if (sum == 0 && arr[0] == 0) {
            return 2;
        }
        if (sum == 0 || sum == arr[0]) {
            return 1;
        }

        return 0;
    }

    int include = 0;
    if (arr[index] <= sum) {
        include  = countSubsets(index - 1, sum - arr[index], arr, n);
    }

    int exclude = countSubsets(index - 1, sum, arr, n);

    return (include + exclude);
}

int countPartitions(int n, int diff, vector<int> &arr) {
    int totalSum = 0;

    for (int i=0; i<n; i++) {
        totalSum = totalSum + arr[i];
    }

    // sum1 >= sum2, sum1 - sum2 = diff
    // totalSum - 2*sum1 = diff => (totalSum - diff)/2 = sum1

    int k = (totalSum - diff)/2;

    // totalSum - diff cannot be negative and the totalSum - diff should be even
    // because there will not be no fractions in array.

    if ((totalSum - diff) < 0 || (totalSum - diff) & 1) {
        return 0;
    }

    return countSubsets(n-1, k, arr, n);
}

int targetSum(int n, int target, vector<int>& arr) {
    return countPartitions(n, target, arr);
}

// Approach 2: Memoization Approach (Top Down DP)
// Time Complexity: O(N * K)
// Space Complexity: O(N * K)

int countSubsets(int index, int sum, vector<int> &arr, int n, vector<vector<int>> &dp) {
    if (index == 0) {
        if (sum == 0 && arr[0] == 0) {
            return 2;
        }
        if (arr[0] != 0 && (sum == 0 || sum == arr[0])) {
            return 1;
        }

        return 0;
    }

    if (dp[index][sum] != -1) {
        return dp[index][sum];
    }

    int include = 0;
    if (arr[index] <= sum) {
        include  = countSubsets(index - 1, sum - arr[index], arr, n, dp);
    }

    int exclude = countSubsets(index - 1, sum, arr, n, dp);

    return dp[index][sum] = (include + exclude);
}

int countPartitions(int n, int diff, vector<int> &arr) {
    int totalSum = 0;

    for (int i=0; i<n; i++) {
        totalSum = totalSum + arr[i];
    }

    // sum1 >= sum2, sum1 - sum2 = diff
    // totalSum - 2*sum1 = diff => (totalSum - diff)/2 = sum1

    int k = (totalSum - diff)/2;

    // totalSum - diff cannot be negative and the totalSum - diff should be even
    // because there will not be no fractions in array.

    if ((totalSum - diff) < 0 || (totalSum - diff) & 1) {
        return 0;
    }

    vector<vector<int>> dp(n, vector<int>(k + 1, -1));

    return countSubsets(n-1, k, arr, n, dp);
}

int targetSum(int n, int target, vector<int>& arr) {
    return countPartitions(n, target, arr);
}

// Approach 3: Tabulation Method (Bottom Up DP)
// Time Complexity: O(N * K)
// Space Complexity: O(N * K)

int countSubsets(vector<int> &arr, int n, int k) {
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    if (arr[0] == 0) {
        dp[0][0] = 2;
    }
    else {
        dp[0][0] = 1;
        
        if (arr[0] <= k) {
            dp[0][arr[0]] = 1;
        }
    }

    for (int index = 1; index < n; index++) {
        for (int sum = 0; sum <= k; sum++) {
            int include = 0;
            if (arr[index] <= sum) {
                include = dp[index - 1][sum - arr[index]];
            }

            int exclude = dp[index - 1][sum];

            dp[index][sum] = (include + exclude);
        }
    }

    return dp[n-1][k];
}

int countPartitions(int n, int diff, vector<int> &arr) {
    int totalSum = 0;

    for (int i=0; i<n; i++) {
        totalSum = totalSum + arr[i];
    }

    // sum1 >= sum2, sum1 - sum2 = diff
    // totalSum - 2*sum1 = diff => (totalSum - diff)/2 = sum1

    int k = (totalSum - diff)/2;

    // totalSum - diff cannot be negative and the totalSum - diff should be even
    // because there will not be no fractions in array.

    if ((totalSum - diff) < 0 || (totalSum - diff) & 1) {
        return 0;
    }
    
    return countSubsets(arr, n, k);
}

int targetSum(int n, int target, vector<int>& arr) {
    return countPartitions(n, target, arr);
}

// Approach 4: Space Optimization (Bottom Up DP)
// Time Complexity: O(N * K)
// Space Complexity: O(N * K)

int countSubsets(vector<int> &arr, int n, int k) {
    vector<int> prevRow(k + 1, 0);

    if (arr[0] == 0) {
        prevRow[0] = 2;
    }
    else {
        prevRow[0] = 1;
        if (arr[0] <= k) {
            prevRow[arr[0]] = 1;
        }
    }

    for (int index = 1; index < n; index++) {
        vector<int> currRow(k + 1, 0);

        for (int sum = 0; sum <= k; sum++) {
            int include = 0;
            if (arr[index] <= sum) {
                include = prevRow[sum - arr[index]];
            }

            int exclude = prevRow[sum];

            currRow[sum] = (include + exclude);
        }

        prevRow = currRow;
    }

    return prevRow[k];
}

int countPartitions(int n, int diff, vector<int> &arr) {
    int totalSum = 0;

    for (int i=0; i<n; i++) {
        totalSum = totalSum + arr[i];
    }

    // sum1 >= sum2, sum1 - sum2 = diff
    // totalSum - 2*sum1 = diff => (totalSum - diff)/2 = sum1

    int k = (totalSum - diff)/2;

    // totalSum - diff cannot be negative and the totalSum - diff should be even
    // because there will not be no fractions in array.

    if ((totalSum - diff) < 0 || (totalSum - diff) & 1) {
        return 0;
    }
    
    return countSubsets(arr, n, k);
}

int targetSum(int n, int target, vector<int>& arr) {
    return countPartitions(n, target, arr);
}