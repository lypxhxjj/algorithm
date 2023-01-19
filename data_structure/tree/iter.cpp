// 迭代器：可以很方便的进行双指针遍历。
//
// 653. 两数之和 IV - 输入二叉搜索树 https://leetcode.cn/problems/two-sum-iv-input-is-a-bst/
class IterAsc {
private:
    stack<TreeNode*> st;
public:
    IterAsc(TreeNode* root) {
        while (root) {
            st.push(root);
            root = root->left;
        }
    }
    bool hasNext() {
        return !st.empty();
    }
    TreeNode* top() { // 本题多个一个top
        return st.top();
    }
    TreeNode* next() {
        TreeNode* res = st.top();
        st.pop();

        TreeNode* curr = res->right;
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        return res;
    }
};
class IterDesc {
private:
    stack<TreeNode*> st;
public:
    IterDesc(TreeNode* root) {
        while (root) {
            st.push(root);
            root = root->right;
        }
    }
    bool hasNext() {
        return !st.empty();
    }
    TreeNode* top() {
        return st.top();
    }
    TreeNode* next() {
        TreeNode* res = st.top();
        st.pop();

        TreeNode* curr = res->left;
        while (curr) {
            st.push(curr);
            curr = curr->right;
        }
        return res;
    }
};
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        IterAsc it1(root);
        IterDesc it2(root);
        while (it1.hasNext() && it2.hasNext()) {
            TreeNode* node1 = it1.top();
            TreeNode* node2 = it2.top();
            if (node1 == node2) { // 要单独考虑相遇的情况。
                return false;
            }
            int sum = node1->val + node2->val;
            if (sum == k) {
                return true;
            } else if (sum > k) {
                it2.next();
            } else {
                it1.next();
            }
        }
        return false;
    }
};

// 结论：数组的迭代器可以很方便的转化到索引
// 所以，如果参数用了i和j，那么代码里使用iter就会很简单。
//
// 654. 最大二叉树 https://leetcode.cn/problems/maximum-binary-tree/
TreeNode* buildTree(vector<int>& nums, int i, int j) { 
    if (i > j) return nullptr;

    auto it = max_element(nums.begin() + i, nums.begin() + j + 1);
    TreeNode* res = new TreeNode(*it);
    res->left = buildTree(nums, i, it-nums.begin() - 1);
    res->right = buildTree(nums, it-nums.begin() + 1, j);
    return res;
}
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    return buildTree(nums, 0, (int)nums.size() - 1);
}