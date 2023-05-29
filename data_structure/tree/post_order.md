后序遍历可以解决子问题的问题。是解决树难题的一种很好的方式。

有什么关键词信息可以标识是一个后序遍历呢？
1. 子树问题：遍历到一个节点，说明已经将所有子树都已遍历完；

有哪些好的解题技巧？下题给了一个思路：
```
// 1373. 二叉搜索子树的最大键值和  https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/
struct NodeResult {
    bool isNull;
    bool isSearchTree;
    int maxVal;
    int minVal;
    int sum;
};
class Solution {
    NodeResult postOrder(TreeNode* root, int& maxVal) {
        if (!root) return {true, true, 0, 0, 0};
        auto leftResult = postOrder(root->left, maxVal);
        auto rightResult = postOrder(root->right, maxVal);
        if (!leftResult.isSearchTree || !rightResult.isSearchTree) {
            return {false, false, 0,0};
        }
        if (!leftResult.isNull && leftResult.maxVal >= root->val) {
            return {false, false,0, 0};
        }
        if (!rightResult.isNull && rightResult.minVal <= root->val) {
            return {false, false,0, 0};
        }

        int currMaxVal = root->val;
        if (!rightResult.isNull) {
            currMaxVal = rightResult.maxVal;
        }
        int currMinVal = root->val;
        if (!leftResult.isNull) {
            currMinVal = leftResult.minVal;
        }
        int sum = leftResult.sum + root->val + rightResult.sum;

        maxVal = max(maxVal, sum);
        return {false, true, currMaxVal, currMinVal, sum};

    }
public:
    int maxSumBST(TreeNode* root) {
        if (!root) return 0;

        int maxVal = INT_MIN;
        postOrder(root, maxVal);
        return maxVal < 0 ? 0 : maxVal;
    }
};
```
一般遍历的过程中，需要传递一些参数，一般的方案是将参数作为函数参数或者成员变量。但此题不一样，遍历到父节点的时候，需要同时知晓两个子节点的信息。所以这里引入了新的方式，通过定义返回值结构体的方式来实现信息传递。

此题还有一个结论：一个子树的中序遍历一定是在一块的。但是依然不能使用转化到数组的方式实现。因为不知道任意一个区间是否为一个子树。