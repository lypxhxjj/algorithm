// 树的序列化。
//
// 结论：树可以通过一定方式和字符串一对一转化。
// 所以：子树问题，可以考虑使用序列化来实现。
//
// 如何序列化呢？最好使用先序序列化方式，因为方便反序列化。反序列化可以使用一个全局的i指针进行反序列化。
//
// 652. 寻找重复的子树 https://leetcode.cn/problems/find-duplicate-subtrees/
string preorder(TreeNode* root, unordered_map<string, int>& hash, vector<TreeNode*>& res) {
    if (!root) return "#";
    string str = to_string(root->val) + " " + preorder(root->left, hash, res) + " " + preorder(root->right, hash, res);
    if (++hash[str] == 2) {
        res.push_back(root); // 空节点使用#，节点之间使用空格。约定好就可以。
    }
    return str;
}

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    unordered_map<string, int> hash;
    vector<TreeNode*> res;
    preorder(root, hash, res);
    return res;
}