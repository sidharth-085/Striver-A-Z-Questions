#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

// Approach: BFS Method
// Time Complexity: O(V + E) or O(M * N)
// here, V = M = WordList size
// and, E = connections between strings
// N = length of string 

// Space Complexity: O(V)

// In this question, we have to reach to endWord from beginWord by replacing 
// the characters of strings and if the new string is present in the wordList.
// We will proceed and continue till we get the endWord.

// Here we are using the BFS Algorithm because when we are replacing the characters
// in any string, we can get multiple strings which are present in wordList.
// So, we take the queue for BFS and keep current string with chain length, 
// every time we get a string and chain length we replace the characters to that
// string and check is it present in wordList or not, if yes add to the queue
// with increase in chain length. 

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