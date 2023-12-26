#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// In this question, we have to find the largest rectangle having all 1's from
// given grid. So, we converted the grid into the heights of rectangles corresponding
// to coloumns. So, that when we find the largest rectangle in histogram using
// every row. We take the maximum out of all the rectangles.

// Time Complexity: O(N * N)
// Space Complexity: O(N)

int largestRectangle(vector<int> &heights) {
    int n = heights.size();

    stack<int> stk;
    // in this method, we are using the stack to find left smaller and right smaller 
    // boundary for the elements present in the stack itself not heights array.

    int maxArea = -1;

    for (int i=0; i<=n; i++) {
        // step 1: run the while loop till stack becomes empty and if stack is not empty
        // run until top element of stack become smaller than current height element or
        // i becomes n + 1, we are running if i == n because there will be case when 
        // i becomes n but stack still contains some elements and we are using stack
        // for calculating the area by taking stack elements as heights

        while (stk.empty() == false && (i == n || heights[stk.top()] >= heights[i])) {
            int currHeight = heights[stk.top()];
            // take out the top element of stack which is bigger than the heights[i]
            // means for top element of stack, heights[i] is right smaller boundary

            stk.pop();
            // pop the element

            int currWidth = -1;

            // check whether stack becomes empty, if stack becomes empty, currWidth is 
            // ith index because there is not left boundary now only right boundary is
            // there which is heights[i].

            if (stk.empty()) {
                currWidth = i;
            }

            // if stack is not empty, means we have the left smaller element which is 
            // next top element after popping the stack. Hence, difference of both
            // left and right smaller element indices minus 1, will be the width

            else {
                int rightSmaller = i;
                int leftSmaller = stk.top();

                currWidth = rightSmaller - leftSmaller - 1;
            }

            // finally, find the area and maximize the area.

            int currArea = currHeight * currWidth;
            
            maxArea = max(maxArea, currArea);
        }

        // push the element in the stack for completing the traversal

        stk.push(i);
    }

    return maxArea;
}

int maximalRectangle(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    // Initialize a variable to store the maximum rectangle size
    int maxi = 0;

    // Initialize a vector to keep track of the heights of bars in the current row
    vector<int> height(m, 0);

    // Iterate through each row in the matrix
    for (int row = 0; row < n; row++) {
        // Iterate through each column in the current row
        for (int col = 0; col < m; col++) {
            // If the matrix cell contains '1', increment the height for that column
            if (matrix[row][col] == 1) {
                height[col]++;
            }
            // If the matrix cell contains '0', reset the height for that column to 0
            else {
                height[col] = 0;
            }
        }

        // Calculate the largest rectangle size in the current row using a helper function
        int largestRectSize = largestRectangle(height);

        // Update the maximum rectangle size if a larger rectangle is found in the current row
        maxi = max(maxi, largestRectSize);
    }

    // Return the maximum rectangle size found in the entire matrix
    return maxi;
}