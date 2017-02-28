/*1  判断一颗树是否是二叉搜索树：
*/
//思路1：中序遍历的过程中进行判断；
//错误：需要使用LONG_MIN;
class Solution {
    void helper(bool& result, TreeNode* root, long long& value) {
        if (!root || !result) return;
        helper(result, root->left, value);
        if (root->val <= value) result = false;
        value = root->val;
        helper(result, root->right, value);
    }
public:
    bool isValidBST(TreeNode* root) {
        bool result = true;
        long long value = LLONG_MIN;
        helper(result, root, value);
        return result;
    }
};

//思路2：非递归算法，关键在于中序遍历的非递归算法：
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        long long value = LLONG_MIN;
        stack<TreeNode*> s;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->val <= value) return false;
            value = root->val;
            s.pop();
            root = root->right;
        }
        return true;
    }
};
