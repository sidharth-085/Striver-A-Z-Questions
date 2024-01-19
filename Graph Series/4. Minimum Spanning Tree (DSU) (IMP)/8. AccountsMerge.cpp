#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DSU {
    vector<int> rank;
    vector<int> parent;

    public: 

    DSU(int n) {
        rank.resize(n, 0);
        parent.resize(n);
        
        for (int i=0; i<n; i++) {
            parent[i] = i;
        }
    }

    int findParent(int vertex) {
        int temp = vertex;

        while (temp != parent[temp]) {
            temp = parent[temp];
        }

        return parent[vertex] = temp;
    }

    void unionByRank(int u, int v) {
        int up_u = findParent(u);
        int up_v = findParent(v);

        if (up_u == up_v) {
            return;
        }

        if (rank[up_u] > rank[up_v]) {
            parent[up_v] = up_u;
        }
        else if (rank[up_u] < rank[up_v]) {
            parent[up_u] = up_v;
        }
        else {
            parent[up_u] = up_v;
            rank[up_v]++;
        }
    }
};

// In this question, we have the accounts vector contains name
// at 0th index and after that some emails for every entry in accounts.
// We have to merge all emails of given in accounts vector. It means
// some emails are repeated with same name, we can merge it but 
// if there is same name but different emails, we cant merge them.
// Two persons may have same names.

// So, we solve this problem in 3 steps which are little complicated
// but best use of DSU algorithm.

// 1. Firstly, we give every entry in accounts a number starting
// from 0. Now, we create a map and store email as key and the number
// as its value while iterating every entry in accounts excluding
// 0th index which is name of the account holder. Also, we are checking
// here if the email is repeated means it is already there in map before
// having some value number, it means this email belongs to the 
// previously found value number. Hence, we merge both numbers because
// all other emails of this entry of accounts belongs to previous one
// , so we merge the numbers using DSU.

// 2. Secondly, when we have map with distinct email as key and number
// of entry as value. We simply iterate over map values and get key
// and value pairs. Now, finding the ultimate parent of number using 
// DSU because we merge the entries having same emails using DSU. 
// So, the ultimate parent represents that other emails belong to the
// already existing name. Therefore, we store the email keys inside
// newly created vector respective to index as ultimate parent of 
// number. We store all the emails to the index denoting the number
// entry of accounts.

// 3. Lastly, we have to just sort all emails and add the name of
// the account holder using loop and attaching sorted emails after
// the name in the ans array. Also, we check that emails entry in 
// newly created vector is not 0. Then, we get the final merged
// accounts with emails.

// Time Complexity: O(N * n)
// n is average length of emails per entry in accounts

// Space Complexity: O(N * email length)

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    int n = accounts.size();

    unordered_map<string, int> map;

    DSU dsu(n);

    for (int vertex = 0; vertex < n; vertex++) {
        vector<string> account = accounts[vertex];

        for (int i = 1; i < account.size(); i++) {
            if (map.find(account[i]) == map.end()) {
                map[account[i]] = vertex;
            }
            else {
                int first = map[account[i]];
                int second = vertex;

                dsu.unionByRank(first, second);
            }
        }
    }

    vector<vector<string>> emails(n);

    for (auto &it : map) {
        string email = it.first;
        int vertex = it.second;

        int vertexUltimateParent = dsu.findParent(vertex);

        emails[vertexUltimateParent].push_back(email);
    }

    vector<vector<string>> ans;

    for (int vertex = 0; vertex < n; vertex++) {
        if (emails[vertex].empty() == false) {
            sort(emails[vertex].begin(), emails[vertex].end());

            vector<string> temp;
            temp.push_back(accounts[vertex][0]);

            for (auto &email : emails[vertex]) {
                temp.push_back(email);
            }

            ans.push_back(temp);
        }
    }

    return ans;
}