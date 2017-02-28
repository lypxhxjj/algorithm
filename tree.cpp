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
-----》归结为，有序数组，小数前移了，ABC，移到了B，那么比较B和C的时候才能发现；大数后移了，比较A和B就能发现；
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


/*新建树的基本原则：
（1）helper的返回值是TreeNode*类型；
（2）开始就创建node，然后递归产生root->left，和root->right;
*/

//根据前序和中序，新建一个树；
//思路固定:前序的第一个元素肯定是root，然后根据这个点将中序分为两个部分，根据这两个部分的大小也将先序分为两个部分；分别成为子问题；
class Solution {
    template<class Iter>
    TreeNode* helper(Iter pre1, Iter pre2, Iter in1, Iter in2) {        //与vector算法相关的使用迭代器，不用纠结于index还是第几个的问题；
        if (in1 == in2) return nullptr;
        TreeNode* root = new TreeNode(*pre1);
        auto it = find(in1, in2, *pre1);
        root->left = helper(pre1 + 1, it - in1 + pre1 + 1, in1, it);
        root->right = helper(it - in1 + pre1 + 1, pre2, it + 1, in2);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;
        return helper(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
        
    }
};

//同样道理，根据中序和后序遍历新建一个二叉树；
class Solution {
    template<class Iter>
    TreeNode* helper(Iter in1, Iter in2, Iter post1, Iter post2) {  
        if (in1 == in2) return nullptr;                         //根据的是中序将二者分成了两个部分，所以只需要检验中序就可以
        TreeNode* root = new TreeNode(*(post2 - 1));
        auto it = find(in1, in2, *(post2 - 1));
        root->left = helper(in1, it, post1, post1 + (it - in1));
        root->right = helper(it + 1, in2, post1 + (it - in1), post2 - 1);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0) return nullptr;
        return helper(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());
    }
};

//使用此方法：根据有序数组构建一个高度平衡的二叉搜索树，至为简单
class Solution {
    template<class Iter>
    TreeNode* helper(Iter it1, Iter it2) {
        if (it1 == it2) return nullptr;
        Iter mid = it1 + (it2 - it1) / 2;
        TreeNode* root = new TreeNode(*mid);        //都不需要比较，因为大的自动到了右边，小的自动到了左边；
        root->left = helper(it1, mid);
        root->right = helper(mid + 1, it2);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums.begin(), nums.end());
    }
};


//遍历树如何按路径遍历        //此题的方法思路比较推荐，所以单独放到一块；
//问题：看有没有一条路径的加和是sum；
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        if (!root->left && !root->right) 
            return sum == root->val;
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }                       //树要是使用递归的话，就需要考虑如何拆分成左右子树，这里是或的关系，跳出条件就是叶子节点处的值恰好为sum；
};
