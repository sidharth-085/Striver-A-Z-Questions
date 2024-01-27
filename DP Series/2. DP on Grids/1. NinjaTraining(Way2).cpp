#include <iostream>
#include <vector>
using namespace std;

// In this question, we are given a 2D matrix in which rows represents the number of
// days N and cols represents the 3 tasks. It is given that Ninja want to perform
// these activities in vacation but, he will not perform 2 same activities on consecutive
// days. In the matrix we have points for each day and each activity. Return the 
// maximum number of points he can score in given N days.

// Approach 1: Brute Force Recursive Solution
// Time Complexity: O(3^N)
// Space Complexity: O(3^N)

int ninjaTrainingHelper(int day, int lastTask, int n, vector<vector<int>> &points) {
    // Base case: If we have considered all days (reached day == -1), return 0.

    if (day == -1) {
        return 0;
    }

    int maxPoints = 0;

    // Iterate through the three possible tasks for the current day.
    for (int task = 0; task < 3; task++) {
        // Avoid choosing the same task as the previous day.
        if (task != lastTask) {

            // Calculate the total points for the current day's task
            // and recursively call the function for the previous day.
            int currPoints = points[day][task] + ninjaTrainingHelper(day - 1, task, n, points);

            // Update maxPoints with the maximum of the current points and previous maxPoints.
            maxPoints = max(maxPoints, currPoints);
        }
    }

    return maxPoints;
}

int ninjaTraining(int n, vector<vector<int>> &points) {
    int maxPoints = 0;

    // Try each task for the last day and calculate the maximum points.
    for (int lastTask = 0; lastTask < 3; lastTask++) {
        int currPoints = points[n-1][lastTask] + ninjaTrainingHelper(n-2, lastTask, n, points);

        // Update maxPoints with the maximum of the current points and previous maxPoints.
        maxPoints = max(maxPoints, currPoints);
    }

    return maxPoints;
}

// Approach 2: Memoization Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

int ninjaTrainingHelper(int day, int lastTask, int n, vector<vector<int>> &points, vector<vector<int>> &dp) {    
    if (day == -1) {
        return 0;
    }

    if (dp[day][lastTask] != -1) { // check is the answer is already computed or not.
        return dp[day][lastTask];
    }

    int maxPoints = 0;

    for (int task = 0; task < 3; task++) {
        if (task != lastTask) {
            int currPoints = points[day][task] + ninjaTrainingHelper(day - 1, task, n, points, dp);

            maxPoints = max(maxPoints, currPoints);
        }
    }

    return dp[day][lastTask] = maxPoints; // finally return the answer and update the dp
}

int ninjaTraining(int n, vector<vector<int>> &points) {
    int maxPoints = 0;

    vector<vector<int>> dp(n, vector<int>(3, -1)); // dp array of rows n and cols 3

    for (int lastTask = 0; lastTask < 3; lastTask++) {
        int currPoints = points[n-1][lastTask] + ninjaTrainingHelper(n-2, lastTask, n, points, dp);

        maxPoints = max(maxPoints, currPoints);
    }

    return maxPoints;
}

// Approach 3: Iterative DP Solution (Bottom - Up)
// Time Complexity: O(N)
// Space Complexity: O(N)

int ninjaTraining(int n, vector<vector<int>> &points) {
    // Create a 2D DP array to store maximum points for each day and task.
    vector<vector<int>> dp(n, vector<int>(3));

    // Initialize the DP array with points for the first day's tasks.
    for (int i = 0; i < 3; i++) {
        dp[0][i] = points[0][i];
    }

    // Loop through each day starting from the second day.
    for (int day = 1; day < n; day++) {
        for (int task = 0; task < 3; task++) {
            int maxPoints = 0;

            // Loop through all possible tasks for the previous day.
            for (int lastTask = 0; lastTask < 3; lastTask++) {
                // Avoid choosing the same task as the previous day.
                if (task != lastTask) {
                    // Calculate the total points for the current day's task
                    // and add it to the maximum points achieved on the previous day.
                    int currPoints = points[day][task] + dp[day - 1][lastTask];

                    // Update maxPoints with the maximum of the current points and previous maxPoints.
                    maxPoints = max(maxPoints, currPoints);
                }
            }

            // Store the maximum points achievable for the current day and task in the DP array.
            dp[day][task] = maxPoints;
        }
    }

    // Find the maximum points achievable on the last day by trying all tasks.
    int finalMax = 0;
    for (int task = 0; task < 3; task++) {
        finalMax = max(finalMax, dp[n - 1][task]);
    }

    // Return the overall maximum points achievable.
    return finalMax;
}

/* Way 2

#include <iostream>
#include <vector>
using namespace std;

// Approach 1: Brute Force Recursive Solution
// Time Complexity: O(3^N)
// Space Complexity: O(3^N)

int ninjaTrainingHelper(int day, int lastTaskIndex, int n, vector<vector<int>> &points) {
    // step 1: check for base case

    if (day == n) { // if all days are completed the maximum points ninja get is 0.
        return 0;
    }

    // step 2: check for every task which is not previously done and take maximum
    // of the points which is scored

    int maxPoints = 0;

    for (int i=0; i<3; i++) {
        if (i != lastTaskIndex) {
            int currPoints = points[day][i] + ninjaTrainingHelper(day + 1, i, n, points);

            maxPoints = max(maxPoints, currPoints);
        }
    }

    // step 3: return the maxPoints scored by trying all possible ways

    return maxPoints;
}

int ninjaTraining(int n, vector<vector<int>> &points) {
    int maxPoints = 0;

    // take every task from first day and find the maximum points scored for all i
    // tasks.

    for (int i=0; i<3; i++) {
        int currPoints = points[0][i] + ninjaTrainingHelper(1, i, n, points);

        maxPoints = max(maxPoints, currPoints);
    }

    return maxPoints;
}

// Approach 2: Memoization Approach
// Time Complexity: O(N)
// Space Complexity: O(N)

int ninjaTrainingHelper(int day, int lastTaskIndex, int n, vector<vector<int>> &points, vector<vector<int>> &dp) {
    // step 1: check for base case

    if (day == n) { // if all days are completed the maximum points ninja get is 0.
        return 0;
    }

    if (dp[day][lastTaskIndex] != -1) { // condition for checking is previously computed.
        return dp[day][lastTaskIndex];
    }

    // step 2: check for every task which is not previously done and take maximum
    // of the points which is scored

    int maxPoints = 0;

    for (int i=0; i<3; i++) {
        if (i != lastTaskIndex) {
            int currPoints = points[day][i] + ninjaTrainingHelper(day + 1, i, n, points, dp);

            maxPoints = max(maxPoints, currPoints);
        }
    }

    // step 3: return the maxPoints scored by trying all possible ways

    return dp[day][lastTaskIndex] = maxPoints; // store the answer in dp to use in future.
}

int ninjaTraining(int n, vector<vector<int>> &points) {
    int maxPoints = 0;

    vector<vector<int>> dp(n + 1, vector<int>(3, -1)); // dp array for memoization.

    // take every task from first day and find the maximum points scored for all i
    // tasks.

    for (int i=0; i<3; i++) {
        int currPoints = points[0][i] + ninjaTrainingHelper(1, i, n, points, dp);

        maxPoints = max(maxPoints, currPoints);
    }

    return maxPoints;
}

*/