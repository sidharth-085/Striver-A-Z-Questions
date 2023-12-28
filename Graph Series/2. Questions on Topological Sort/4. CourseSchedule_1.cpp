#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// In this question, we have the prerequesites contains pair of two courses (a,b)
// which represents if you wanted to complete course a, you have to do course b
// first, means there is an edge between b to a. Therefore, questions is asking
// that we can complete all the courses or not. 
// If we can finish all the courses it means, we can complete b courses first 
// and then a courses in the prerequisites. So, if count of topo sort is same
// as number of courses, we can complete the courses else no.

// Time Complexity: O(V + E)
// Space Complexity: O(V)

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);

    vector<int> inDegree(numCourses, 0);

    for (auto edge : prerequisites) {
        int first = edge[0];
        int second = edge[1];

        graph[second].push_back(first);
        inDegree[first]++;
    }

    queue<int> q;

    int count = 0;

    for (int vertex = 0; vertex < numCourses; vertex++) {
        if (inDegree[vertex] == 0) {
            q.push(vertex);
        }
    }

    while (!q.empty()) {
        int top = q.front();
        q.pop();

        count++;

        for (int neighbour : graph[top]) {
            inDegree[neighbour]--;

            if (inDegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }
    }

    if (count == numCourses) {
        return true;
    }

    return false;
}