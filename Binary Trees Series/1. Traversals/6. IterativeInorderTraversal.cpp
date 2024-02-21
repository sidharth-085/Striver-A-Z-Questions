#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class TreeNode {
    public:
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

vector<int> inorderTraversal(TreeNode *root) {
    if (root == NULL) {
        return {};
    }

    vector<int> ans;
    TreeNode *temp = root;

    stack<TreeNode*> s;

    while (true) {
        if (temp != NULL) {
            s.push(temp);
            temp = temp->left;
        }
        else {
            if (s.empty()) {
                break;
            }
            
            temp = s.top();
            s.pop();

            ans.push_back(temp->data);
            temp = temp->right;
        }
    }

    return ans;
}