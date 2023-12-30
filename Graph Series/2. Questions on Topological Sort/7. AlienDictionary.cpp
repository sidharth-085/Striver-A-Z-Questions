#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity: O(V + E + n*(average of word lengths in dictionary))
// Space Complexity: O(k)

// In this question, we have the dictionary and we have to get the order
// of the alphabets according to the words given in dictionary. And, when
// whenever we talk about the order of elements (one comes before other),
// we have to apply Topo Sort. Hence, we created the graph first and done
// the topo sort after that.

string getAlienLanguage(vector<string> &dictionary, int k) {
    int n = dictionary.size();

    vector<vector<int>> graph(k);

    vector<int> inDegree(k, 0);

    for (int i = 0; i < n - 1; i++) {
        string str1 = dictionary[i];
        string str2 = dictionary[i+1];

        int len = min(str1.size(), str2.size());

        for (int j = 0; j < len; j++) {
            if (str1[j] != str2[j]) {
                graph[str1[j] - 'a'].push_back(str2[j] - 'a');
                inDegree[str2[j] - 'a']++;
                break;
            }
        }
    }

    queue<int> q;

    for (int vertex = 0; vertex < k; vertex++) {
        if (inDegree[vertex] == 0) {
            q.push(vertex);
        }
    }

    string ans;

    while (!q.empty()) {
        int top = q.front();
        q.pop();

        ans.push_back(top + 'a');

        for (int neighbour : graph[top]) {
            inDegree[neighbour]--;

            if (inDegree[neighbour] == 0) {
                q.push(neighbour);
            }
        }
    }

    return ans;
}