//中序遍历的非递归版本，格式固定
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> s; 
        while (root || !s.empty()) {
            while (root) {                  //第一步，左边的全部进栈；
                s.push(root);
                root = root->left;
            }
            root = s.top();
            result.push_back(root->val);    //第二步，从栈顶获取数据；
            s.pop();
            root = root->right;             //第三步，切换到栈顶元素的右子树；
        }
        return result;
    }
};
/*
1  判断一颗树是否是二叉搜索树：
（1）与二叉搜索树有关的，很可能是中序遍历；
*/

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

/*
2  二叉搜索树有两个节点颠倒了，交换过来
（1）与二叉搜索树相关的使用中序遍历；
（1）思路是难点：两个节点第一次不顺序时，需要被交换的是前继节点；第二次不顺序时，需要被交换的是后继节点；没有第二次的话，说明只有两个节点，就交换那两个节点就好了；
（2）保存前继节点pre，只有在中序遍历的时候保存前继节点才有意义；
*/

//使用前继节点，需要四个节点，遍历过程中的前继和后继，保存起来的前继和后继；
class Solution {
    void inorder(TreeNode* root, TreeNode*& value, TreeNode*& pre, TreeNode*& cur) {
        if (!root) return;
        inorder(root->left, value, pre, cur);
        if (root->val <= value->val) {
            if (!pre) pre = value;          //这个肯定有，所以只赋值一次；
            cur = root;                     //这个不一定有，所以赋值两次；
        }
        else
            value = root;
        inorder(root->right, value, pre, cur);
    }
public:
    void recoverTree(TreeNode* root) {
        TreeNode* value = new TreeNode(INT_MIN);
        TreeNode* tmp = nullptr;
        TreeNode* tmp1 = nullptr;
        inorder(root, value, tmp, tmp1);
        swap(tmp->val, tmp1->val);
    }
};

//对应的非递归算法，完全是上面的拷贝
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode* pre = new TreeNode(INT_MIN);
        TreeNode* pre1 = nullptr, *cur = nullptr;
        stack<TreeNode*> s;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            if (root->val < pre->val) {
                if (!pre1) pre1 = pre;
                cur = root;
            }
            pre = root;
            s.pop();
            root = root->right;
        }
        swap(pre1->val, cur->val);
    }
};

// 3  层序遍历的递归版本，比较简单：
class Solution {
    void traverse(TreeNode* root, int level, vector<vector<int>>& result) {
        if (!root) return;
        if (level > result.size())
            result.push_back({});
        result[level - 1].push_back(root->val);
        traverse(root->left, level + 1, result);
        traverse(root->right, level + 1, result);
    }
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        traverse(root, 1, result);
        return result;
    }
};

//非递归算法：
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        queue<TreeNode*> p, q;              //两个队列，分别代表一行，使用swap技术来交换！swap技术好牛叉；
        p.push(root);
        while (!p.empty()) {
            vector<int> tmp;
            while (!p.empty()) {
                TreeNode* node = p.front();
                tmp.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                p.pop();
            }
            if (tmp.size()) result.push_back(tmp);
            swap(p, q);
        }
        return result;
    }
};
