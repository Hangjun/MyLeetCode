/*
Given a binary tree, find the leftmost value in the last row of the tree.

Example 1:
Input:

    2
   / \
  1   3

Output:
1
Example 2: 
Input:

        1
       / \
      2   3
     /   / \
    4   5   6
       /
      7

Output:
7
Note: You may assume the tree (i.e., the given root node) is not NULL.
*/

/* Analysis: A straightforward solution is to scan each level, and pick the first node of the last row. Intuitively this is not the best answer since we are interested any other row except the last one. One idea is to traverse via DFS, and record the height even reached and compare it with the height that the node is current in. If the height ever reached is less than the current height, then that means a new left node (at a deeper level) is reached. 

Another key is to first traverse curNode->left then curNode->right.

One should recognize the similarity between this problem and Problem 199: https://github.com/Hangjun/MyLeetCode/blob/master/199_Binary_Tree_Right_Side_View.cpp.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        int res = 0;
        int heightReached = 0;
        findBottomLeftValueRecur(root, 1, heightReached, res);
        return res;
    }
    
    void findBottomLeftValueRecur(TreeNode *curNode, int depth, int &heightReached, int &res) {
        // a new left node with deeper depth
        if (depth > heightReached) {
            heightReached = depth;
            res = curNode->val;
        }
        // go left first
        if (curNode->left) findBottomLeftValueRecur(curNode->left, depth+1, heightReached, res);
        if (curNode->right) findBottomLeftValueRecur(curNode->right, depth+1, heightReached, res);
    }
};

// Just to compare, below is the solution to Problem 199.
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (!root) return res;
        rightSideViewDFS(root, 1, res);
        return res;
    }
    
    void rightSideViewDFS(TreeNode *curNode, int level, vector<int> &res) {
        if (level > res.size()) res.push_back(curNode->val);
        if (curNode->right) rightSideViewDFS(curNode->right, level+1, res);
        if (curNode->left) rightSideViewDFS(curNode->left, level+1, res);
    }
};
