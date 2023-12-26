#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

// In this question, we have to reach to endWord from beginWord by replacing 
// the characters of strings and if the new string is present in the wordList.
// We will proceed and continue till we get the endWord.

// Here we are using the BFS Algorithm because when we are replacing the characters
// in any string, we can get multiple strings which are present in wordList.

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> set;

    int n = beginWord.size();

    for (string word : wordList) {
        set.insert(word);
    }

    queue<pair<string, int>> q;
    q.push({beginWord, 1});

    while (!q.empty()) {
        pair<string, int> top = q.front();
        q.pop();

        string tWord = top.first;
        int chainLen = top.second;

        if (tWord == endWord) {
            return chainLen;
        }

        for (int i=0; i<n; i++) {
            char orignal = tWord[i];

            for (char ch = 'a'; ch <= 'z'; ch++) {
                tWord[i] = ch;

                if (set.find(tWord) != set.end()) {
                    set.erase(tWord);

                    q.push({tWord, chainLen + 1});
                }
            }

            tWord[i] = orignal;
        }
    }

    return 0;
}