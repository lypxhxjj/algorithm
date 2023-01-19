// 树的更改：要么刀左边，要么刀右边，要么递归刀。
//
// 本题的特点是：一定有解，因为是二叉搜索树。
//
// 669. 修剪二叉搜索树 https://leetcode.cn/problems/trim-a-binary-search-tree/
TreeNode* trimBST(TreeNode* root, int low, int high) {
    if (!root) return nullptr;
    if (root->val < low) {
        return trimBST(root->right, low, high);
    } else if (root->val > high) {
        return  trimBST(root->left, low, high);
    } else {
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
    }
    return root;
}