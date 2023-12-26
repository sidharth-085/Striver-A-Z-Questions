#include <iostream>
#include <vector>
#include <string>
using namespace std;

// This question is saying that, we have to make the longest chain of strings 
// which made by the strings if we insert a character anywhere in word A which 
// makes word B and word A & word B makes chain and so on. 

// So, we can do it by the use of LIS function with some changes in the function.
// Firstly, we sort the string according to the size of the strings using comparator
// function. Then, we will traverse the array of string and find that if the 
// previous string has size one less than the current one and compare the characters
// of smaller string with bigger string. If the character matches, we will check 
// the Largest String Chain Length at that index where we get the small string, 
// will become more than the current length of Chain at curr index. If yes, we will
// replace it and do same as LIS. With this change we can find the answer.

// Also, we have to sort the array of strings because in question, the array given
// will contains random sizes of strings at any index. So, we will sort it so that
// we can compare the strings

// Time Complexity: O(N * N * M) (where M is length of longest string in array)
// Space Complexity: O(N)

bool compare(string &str, string &prevStr) {
    int n = str.size();
    int m = prevStr.size();

    // Check if the difference in the lengths of the two strings is not equal to 1.
    if (n != m + 1) {
        return false; // If the lengths don't match the chain condition, return false.
    }

    int first = 0;
    int second = 0;

    // Iterate through both strings to find if they can form a chain.
    while (first < n) {
        if (second < m && str[first] == prevStr[second]) {
            first++;
            second++;
        }
        else {
            first++;
        }
    }

    // If we successfully iterated through both strings, it means they form a chain.
    if (second == m) {
        return true;
    }

    return false;
}

// This is a custom comparison function used for sorting the 'words' vector based on string length.
bool comp(string &str1, string &str2) {
    return str1.size() < str2.size();
}

// This function finds the length of the longest string chain in the given 'words' vector.
int longestStrChain(vector<string>& words) {
    int n = words.size();

    vector<int> dp(n, 1); // Initialize a dynamic programming array to store chain lengths for each word.

    int maxi = 1; // Initialize a variable to keep track of the maximum chain length found.

    // Sort the 'words' vector based on string length using the custom comparison function.
    sort(words.begin(), words.end(), comp);

    // Loop through each word in the 'words' vector.
    for (int index = 1; index < n; index++) {
        for (int prevIndex = index - 1; prevIndex >= 0; prevIndex--) {
            // Check if the current word can form a chain with the previous word.
            if (compare(words[index], words[prevIndex]) == true) {
                int possibleAns = 1 + dp[prevIndex];

                // Update the chain length if the new chain is longer.
                if (possibleAns > dp[index]) {
                    dp[index] = possibleAns;
                }
            }
        }

        // Update 'maxi' with the maximum chain length found so far.
        maxi = max(maxi, dp[index]);
    }

    return maxi; // Return the maximum chain length found in the 'words' vector.
}