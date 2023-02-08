// 树的递归算法
void inorder(TreeNode* root) {
    if (!root) return;

    inorder(root->left);
    visit(root);
    inorder(root->right);
}

void preorder(TreeNode* root) {
    if (!root) return

    visit(root);
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode* root) {
    if (!root) return;

    postorder(root->left);
    postorder(root->right);
    visit(root);
}

// 如何直接将树的递归算法转化为非递归算法？
// TODO:尾递归如何处理。
//
// 先序遍历的点：
// 0. 递归的参数是啥，栈中就需要保存啥。引用型的参数不需要保存。
// 1. preorder自身第一次调用，root入栈，所以定义完stack，root入栈；
// 2. visit的本质就是 while(!empty) {visit(stack.top()); stack.pop();}
// 3. 如何处理连续两次的递归？本质就是简单的两次入栈操作，但是需要注意顺序，下次先遍历谁，谁后入栈。(一会用这个技巧处理后序试试)
// 4. visit之前的递归在while循环之外，visit之后的递归在while循环之内。
//
// 递归中每层开始都检查是否为null，非递归则将这个操作转移到了push到栈之前。
vector<int> preorderTraversal(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
        
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        TreeNode* node = s.top();
        s.pop();
        res.push_back(node->val);

        if (node->right) s.push(node->right);
        if (node->left) s.push(node->left);
    }
    return res;
}

// 中序遍历-使用栈的非递归算法
//
// 这里我们可以学习到，如何使用栈替换函数调用来完成递归对非递归的转化，技巧如下：
// 2. visit之前的递归，如何转化为非递归？就是不断将root->left入栈；小问题：是不断对root入栈，还是不断对root->left入栈？
// 3. visit方法本质就是遍历栈中的内容。while(!empty) visit(stack.top())即可；
// 4. visit之后的递归，如何转化为非递归？当前元素root->right作为root不断入栈root->left。
vector<int> inorderTraversal(TreeNode* root) {
    if (!root) return {};

    stack<TreeNode*> s;
    s.push(root); // 外层函数调用，开始。

    vector<int> res;
    while (!s.empty()) {
        while (root && root->left) { // 遍历的是谁，为啥会是root而不是s.top()?函数调用里每次进入一个新的函数，都需要从栈顶获取信息不是？
            s.push(root->left);
            root = root->left;
        }

        root = s.top();
        res.push_back(root->val);
        s.pop();

        if (root->right) {
            s.push(root->right);
        }
        root = root->right;
    }
    return res;
}

// 层序遍历：最大宽度问题
//
// 本题难点在于如何处理空节点，最大的技巧，我们没有使用节点的值，而是自己定义了编号，使用自己定义的编号计算最大宽度。
//
// 2的幂次增长很快，即使ull，也只能处理大约64深度的树，如何处理溢出问题呢？
// 解决：使用unsigned忽略溢出问题。在某一层，一旦最左边的节点相对父节点溢出了，那么这一层右边的节点一定也已经溢出。而这一层的节点数不可能超过2的31次幂，所以完全可以直接计算。
// 结论：**根节点从1开始**，溢出点一定在最左边，因为满二叉树每一层最右边的节点是全1的，每次都从最左边开始多一个bit。
//
// 662. 二叉树最大宽度 https://leetcode.cn/problems/maximum-width-of-binary-tree/
void preorder(TreeNode* root, int level, unsigned val, vector<unsigned>& minVal, int& res) {
    if (!root) return;

    if (level == minVal.size()) { // 层序遍历需要使用level，minVal保存每一层的最小值。
        minVal.push_back(val);
    } else {
        res = max(res, int(val - minVal[level] + 1));
    }
    preorder(root->left, level + 1, val * 2 , minVal, res);
    preorder(root->right, level + 1, val * 2 + 1, minVal, res);
}
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        vector<unsigned int> minVal;
        int res = 1;
        preorder(root, 0, 1, minVal, res);
        return res;
    }

// 遍历剪枝问题
//
// 关键点1：一旦找到这个点，那么立刻马上开始return，不再做多余的函数调用。需要在两个位置加if判断：
// 1. 最开头，和!root一起；
// 2. 中序遍历位置。
// 第二点理解：一旦找到，中序遍历位置可以保证不再进入right递归；left后面加了if，right后面不需要加，是因为right本身就要结束了。
//
// 关键点2：如何实现频繁查找第k小呢？
// 可以在每个节点记录下左右子树节点个数。(时间复杂度降低为o(logn))
//
// 关键点3：如果需要频繁修改树 && 需要频繁查找第k小
// 可以使用AVL树，不断旋转平衡，让树的高度维持在o(logn)上。
//
// 快速理解：普通中序遍历找一个数，如何高效剪枝呢？
//
// 230. 二叉搜索树中第K小的元素 https://leetcode.cn/problems/kth-smallest-element-in-a-bst/
class Solution {
    int res; // 多用成员变量，可以使得函数参数简化，反正原理都是一样的，就不弄虚的了。
public:
    int kthSmallest(TreeNode* root, int k) {
        return helper(root, k);
    }
    int helper(TreeNode* root, int& k) { // k需要传引用哈。所以k也可以放到成员变量中去。
        cout << k << endl;
        if (!root || k < 0) {
            return res;
        }
        helper(root->left, k);
        if (--k == 0) {
            res = root->val;
        } 
        if (k <= 0) {
            cout << "找到啦" << endl;  // 两个测试 cout，一旦返回，就不会调用到第一行的cout。
            return res; 
        }
        helper(root->right, k);
        return res;
    }
};