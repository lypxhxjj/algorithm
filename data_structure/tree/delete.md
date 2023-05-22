树的删除套路：
```
TreeNode* dfs(TreeNode* root) {
    if (!root) return root;
    root->left = dfs(root->left);
    root->right = dfs(root->right);
    return toDelete() ? nullptr : root;
}
```
删除其实和创建很像，创建一个树的过程也是类似的。

这里的删除存在一个问题：一旦决定删除当前root，就相当于将这个root下的子树删除了！所以如果需求为，只删除root自身，而不删除其左右孩子，那就需要特殊考虑。

题目如下：
```
1080. 根到叶路径上的不足节点

给你二叉树的根节点 root 和一个整数 limit ，请你同时删除树中所有 不足节点 ，并返回最终二叉树的根节点。

假如通过节点 node 的每种可能的 “根-叶” 路径上值的总和全都小于给定的 limit，则该节点被称之为 不足节点 ，需要被删除。

叶子节点，就是没有子节点的节点。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/insufficient-nodes-in-root-to-leaf-paths
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
```
解决：
```
class Solution {
    pair<TreeNode*, int> postOrder(TreeNode* root, int limit, int sum) {
        if (!root) return {nullptr, INT_MIN};
        sum += root->val;
        if (!root->left && !root->right) {
            return {sum < limit ? nullptr : root, sum};
        }
        auto [left, leftMax] = postOrder(root->left, limit, sum);
        auto [right, rightMax] = postOrder(root->right, limit, sum);
        root->left = left;
        root->right = right;


        int currMax = max(leftMax, rightMax);
        if (currMax < limit) {
            return {nullptr, currMax};
        }
        return {root, currMax};
    }
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        if (!root) return nullptr;
        auto [res,_ ] = postOrder(root, limit, 0);
        return res;
    }
};
```

关键问题有如下几种：
1. 根-叶路径和问题。先序遍历求和，使用按值传递的参数来向下传递和。

路径和问题在当前问题下可以简化：因为当前问题存在一个limit参数，所以可以使用减法代替加法，不断削减limit来达到间接求和的目的，这样就不再需要上面的sum字段了。

2. 叶子节点特殊考虑。为啥要特殊考虑呢？两个因素：
（1）叶子节点的处理逻辑和非叶子节点不一样，比如此题需要在叶子节点处拿到最终的路径和；
（2）不特殊考虑叶子节点，只特殊考虑nullptr节点可以吗？不可以，这样会导致叶子节点的逻辑被处理两次，因为叶子节点有两个nullptr孩子。

3. 关于只有一个孩子是空的问题。
这会导致代码执行到nullptr的分支判断。单孩子问题需要特殊考虑，因为nullptr子节点不能影响到计算。所以这里返回INT_MIN来避免影响。

那后序遍历过程中，如何知晓是否有一个孩子为空呢？提前保存好root->left和root->right，后续遍历完成后，可以使用这两个变量来判断，不需要单独一个返回值结果来保存孩子是否为nullptr。

4. 删除逻辑参考上面模板，对于本题，本质就是判断一个节点是否被删除。需要想方设法找到需要的参数来进行判断。

比如本题，需要找到经过某个节点的最大路径和，而这个路径和只有到了叶子节点才会知晓。所以需要想办法将这个信息传递上来，这个可以通过返回值的方式传递（如上代码）。

当前逻辑在本题可以优化，但是不太好想：如果当前节点是叶子节点，直接判断是否可以删除；如果不是叶子节点，判断左右孩子是否已经被删除，如果都已经被删除，则当前节点也应该被删除！

简化后的代码：
```
class Solution {
    TreeNode* postOrder(TreeNode* root, int limit) {
        if (!root) return nullptr;
        if (!root->left && !root->right) {
            return root->val < limit ? nullptr : root;
        }
        root->left = postOrder(root->left, limit - root->val);
        root->right = postOrder(root->right, limit - root->val);
        
        if (!root->left && !root->right) {
            return nullptr;
        }
        return root;
    }
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        if (!root) return nullptr;
        return postOrder(root, limit);
    }
};
```