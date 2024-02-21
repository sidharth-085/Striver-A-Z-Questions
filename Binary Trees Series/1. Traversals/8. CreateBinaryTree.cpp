#include <iostream>
#include <queue>
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

TreeNode* createBinaryTree(vector<int> &nodes) {
    // here array is given as level order traversal

    int n = nodes.size();

    TreeNode *root = new TreeNode(nodes[0]);

    queue<TreeNode*> q;
    q.push(root);

    int i = 1;

    while (i < n) {
        TreeNode *node = q.front();
        q.pop();

        node->left = new TreeNode(nodes[i]);
        node->right = new TreeNode(nodes[i + 1]);

        q.push(node->left);
        q.push(node->right);

        i = i + 2;
    }

    return root;
}

TreeNode* createTree(int index, int n, vector<int> &nodes) {
    if (index >= n) {
        return NULL;
    }

    TreeNode *root = new TreeNode(nodes[index]);

    root->left = createTree((2 * index) + 1, n, nodes);
    root->right = createTree((2 * index) + 2, n, nodes);

    return root;
}

TreeNode* createBinaryTree(vector<int> &nodes) {
    int n = nodes.size();

    return createTree(0, n, nodes);
}