#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;

// Simpler Method 

// In this method, there is a little change. In previous problem, we erase the
// string when we push it in queue so that It will not get repeat. But here, 
// we consider levels and we erase all the strings on one level together. Also,
// we will take the queue of vector to store the strings in vector at every step.
// And, when we get the endWord in queue, we add the vector in ans and continue
// exploring other chains till queue becomes empty.

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    vector<vector<string>> ans;

    int n = beginWord.size();

    unordered_set<string> set;
    
    for (string word : wordList) {
        set.insert(word);
    }

    queue<vector<string>> q;
    q.push({beginWord});

    vector<string> forErase;
    
    int level = 0;

    while (!q.empty()) {
        vector<string> top = q.front();
        q.pop();

        string tWord = top.back();
        int tChainLen = top.size();

        if (tChainLen > level) {
            level++;

            for (string str : forErase) {
                set.erase(str);
            }

            forErase.clear();
        }

        if (tWord == endWord) {
            ans.push_back(top);
            continue;
        }

        for (int i=0; i<n; i++) {
            int orignal = tWord[i];

            for (char ch = 'a'; ch <= 'z'; ch++) {
                tWord[i] = ch;

                if (set.find(tWord) != set.end()) {
                    top.push_back(tWord);
                    q.push(top);
                    top.pop_back();

                    forErase.push_back(tWord);
                }
            }

            tWord[i] = orignal;
        }
    }

    return ans;
}

// Hard method but Improved Time and Space Complexity

// In this method, we do the process in two steps to save memory of storing
// strings array in queue. First, we proceed with general previous problem but
// take a map as parameter which stores the chain Length till every string.

// Secondly, when we get the map having strings with chain length at that string,
// we do backtracking and get the strings in reverse order by starting with 
// endWord. And, now performs dfs starts from endWord and go till beginWord.
// When we get the beginWord, reverse the seq array which we are carrying to 
// store all the chains and add to the ans and reverse again to backtrack.

void bfs(string beginWord, string endWord, int n, vector<string> &wordList, unordered_map<string, int> &map) {
    unordered_set<string> set;

    for (string word : wordList) {
        set.insert(word);
    }

    set.erase(beginWord);

    queue<string> q;
    q.push(beginWord);

    map[beginWord] = 1;

    while (!q.empty()) {
        string top = q.front();
        q.pop();

        int chainLen = map[top];

        for (int i=0; i<n; i++) {
            char orignal = top[i];
            
            for (char ch = 'a'; ch <= 'z'; ch++) {
                top[i] = ch;

                if (set.find(top) != set.end()) {
                    q.push(top);

                    map[top] = chainLen + 1;

                    set.erase(top);
                }
            }

            top[i] = orignal;
        }
    }
}

void dfs(string word, string &beginWord, int n, vector<string> &seq, vector<vector<string>> &ans, unordered_map<string, int> &map) {
    if (word == beginWord) {
        reverse(seq.begin(), seq.end());

        ans.push_back(seq);

        reverse(seq.begin(), seq.end());

        return;
    }

    int num = map[word];

    for (int i=0; i<n; i++) {
        char orignal = word[i];
        
        for (char ch = 'a'; ch <= 'z'; ch++) {
            word[i] = ch;

            if (map.find(word) != map.end() && map[word] + 1 == num) {
                seq.push_back(word);

                dfs(word, beginWord, n, seq, ans, map);

                seq.pop_back();
            }
        }

        word[i] = orignal;
    }
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    unordered_map<string, int> map;

    int n = beginWord.size();

    bfs(beginWord, endWord, n, wordList, map);

    vector<vector<string>> ans;

    vector<string> seq;

    seq.push_back(endWord);

    dfs(endWord, beginWord, n, seq, ans, map);

    return ans;
}