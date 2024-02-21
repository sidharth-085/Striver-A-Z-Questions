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

vector<int> preorderTraversal(TreeNode *root) {
    if (root == NULL) {
        return {};
    }

    stack<TreeNode*> s;
    s.push(root);

    vector<int> ans;

    while (!s.empty()) {
        TreeNode *node = s.top();
        s.pop();

        ans.push_back(node->data);

        if (node->right != NULL) {
            s.push(node->right);
        }

        if (node->left != NULL) {
            s.push(node->left);
        }
    }

    return ans;
}