#include <iostream>
#include <stack>
#include <vector>
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

vector<int> iterativePostorder(TreeNode *root) {
    if (root == NULL) {
        return {};
    }

    stack<TreeNode*> stk1;
    stack<TreeNode*> stk2;

    stk1.push(root);

    while (!stk1.empty()) {
        TreeNode *node = stk1.top();
        stk1.pop();

        stk2.push(node);

        if (node->left != NULL) {
            stk1.push(node->left);
        }

        if (node->right != NULL) {
            stk1.push(node->right);
        }
    }
    
    vector<int> ans;
    
    while (!stk2.empty()) {
        TreeNode *node = stk2.top();
        stk2.pop();

        ans.push_back(node->data);
    }

    return ans;
}