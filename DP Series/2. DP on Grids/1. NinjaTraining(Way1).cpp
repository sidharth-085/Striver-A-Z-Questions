#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Recursive Approach
// Time Complexity: O(3^N)
// Space Complexity: O(3^N)

int ninjaTrainingHelper(int day, int prevTask, int n, vector<vector<int>> &points) {
    // base case: when we are at first day, the maximum of all 3 is maximum points.

    if (day == 0) { 
        int maxPoints = 0;

        for (int task = 0; task < 3; task++) {
            if (task != prevTask) {
                maxPoints = max(maxPoints, points[day][task]);
            }
        }

        return maxPoints;
    }

    // when days is between n-1 to 1, we find the maximum points using recursion and
    // taken only for those task which is not previously done

    int maxPoints = 0;

    for (int task = 0; task < 3; task++) {
        if (task != prevTask) {
            int currPoints = points[day][task] + ninjaTrainingHelper(day - 1, task, n, points);

            maxPoints = max(maxPoints, currPoints);
        }
    }

    return maxPoints;
}

int ninjaTraining(int n, vector<vector<int>> &points) {
    return ninjaTrainingHelper(n - 1, 3, n, points);

    // we are passing 3 in place of prevTask because when we are starting from last
    // day, there is no last task , so we write 3.
}

// Approach 2: Memoization Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

int ninjaTrainingHelper(int day, int prevTask, int n, vector<vector<int>> &points, vector<vector<int>> &dp) {
    if (day == 0) {
        int maxPoints = 0;

        for (int task = 0; task < 3; task++) {
            if (task != prevTask) {
                maxPoints = max(maxPoints, points[day][task]);
            }
        }

        return dp[day][prevTask] = maxPoints;
    }

    if (dp[day][prevTask] != -1) { // check is solution alreadyx exists or not.
        return dp[day][prevTask];
    }

    int maxPoints = 0;

    for (int task = 0; task < 3; task++) {
        if (task != prevTask) {
            int currPoints = points[day][task] + ninjaTrainingHelper(day - 1, task, n, points, dp);

            maxPoints = max(maxPoints, currPoints);
        }
    }

    return dp[day][prevTask] = maxPoints; // store the final value in dp
}

int ninjaTraining(int n, vector<vector<int>> &points) {
    vector<vector<int>> dp(n, vector<int>(4, -1)); 
    // make dp of size n and 4 because we are taking last as 3 at the starting

    return ninjaTrainingHelper(n - 1, 3, n, points, dp);
}

// Approach 3: Iterative DP Solution (Bottom - Up)
// Time Complexity: O(N)
// Space Complexity: O(N)

int ninjaTraining(int n, vector<vector<int>> &points) {
    vector<vector<int>> dp(n, vector<int>(4, 0));
    // dp array same as memoization 

    // base case: when we are at day 0, if previous task is 0, we can only take 
    // 1 or 2 task, which one is maximum take that and same for others

    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max(points[0][1], max(points[0][2], points[0][3]));
    // for 3 which is not part of points, so take maximum of all three

    // when  days are from 1 to n-1 (bottom to top)

    for (int day = 1; day < n; day++) {
        // take the last task from 0 to 4 in dp array

        // same recurrence as memoization and recursion
        for (int lastTask = 0; lastTask < 4; lastTask++) { 
            int maxPoints = 0;

            for (int task = 0; task < 3; task++) {
                if (task != lastTask) {
                    int currPoints = points[day][task] + dp[day - 1][task];

                    maxPoints = max(maxPoints, currPoints);
                }
            }

            dp[day][lastTask] = maxPoints; // store the answer in dp everytime 
        }
    }

    return dp[n-1][3]; 
    // finally return answer (starting from n-1 days and last task is 3)
}

// Approach 4: Space Optimization
// Time Complexity: O(N)
// Space Complexity: O(1)

int ninjaTraining(int n, vector<vector<int>> &points) {
    vector<int> dp(4, 0);
    // space optimized dp solution, take the dp of size 4, and keeps updating this 
    // everytime when we pass through a day

    dp[0] = max(points[0][1], points[0][2]);
    dp[1] = max(points[0][0], points[0][2]);
    dp[2] = max(points[0][0], points[0][1]);
    dp[3] = max(points[0][1], max(points[0][2], points[0][3]));

    for (int day = 1; day < n; day++) {
        vector<int> temp(4, 0); 
        // make a temporary array of size 4 and every value is 0, same as 2d dp ith row.

        for (int lastTask = 0; lastTask < 4; lastTask++) {
            int maxPoints = 0;

            for (int task = 0; task < 3; task++) {
                if (task != lastTask) {
                    int currPoints = points[day][task] + dp[task]; 

                    maxPoints = max(maxPoints, currPoints);
                }
            }

            temp[lastTask] = maxPoints; // store the answers in temp dp
        }
 
        dp = temp; 

        // at last update the dp with temp to use further and eliminate the extra N 
        // space
    } 

    return dp[3];
    // finally return the answer (at starting the prevTask value is 3)
}