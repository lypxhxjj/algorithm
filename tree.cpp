/**************************************** 中序遍历的问题  *********************************************/
/*
*（1）中序遍历的非递归版本；
* (2)二叉搜索树的问题；
*/

//1  中序遍历的非递归版本，格式固定
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


//2  判断一颗树是否是二叉搜索树：
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
        long long value = LLONG_MIN;        //需要使用LLONG_MIN;
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
3  二叉搜索树有两个节点颠倒了，交换过来
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

//判断二叉搜索树（包含重复）中出现次数最多的那些数字；
class Solution {
    void inorder(TreeNode* root, int& cur, int& count, vector<int>& result, int& max_size) { //目前的值及总次数，是全局的，所以引用传递；
        if (!root) return;
        inorder(root->left, cur, count, result, max_size);
        if (root->val == cur)
            count++;
        else {
            cur = root->val;
            count = 1;
        }
        if (count == max_size) {            //如果等于了，也加入结果数组；
            result.push_back(cur);
        }
        else if(count > max_size) {         //如果大于了，清空结果数组；
            result.resize(0);
            result.push_back(cur);
            max_size = count;
        }
        inorder(root->right, cur, count, result, max_size);
    }
public:
    vector<int> findMode(TreeNode* root) {
        vector<int> result;
        int max_size = 0;
        int cur = INT_MIN;
        int count = 0;
        inorder(root, cur, count, result, max_size);
        return result;
    }
};
/**************************************** 后序遍历的问题 ********************************/
/*  后序遍历处理的问题是：以任一个节点为根节点，与其下面所有的节点构成的树的性质
*/

//以当前节点作为根节点的树的所有数和中，和出现次数最多的那些和
class Solution {
    int poster(TreeNode* root, unordered_map<int, int>& map, int& max_value) {
        if (!root) return 0;
        int left = poster(root->left, map, max_value);
        int right = poster(root->right, map, max_value);
        int sum = root->val + left + right;
        map[sum]++;
        max_value = max(max_value, map[sum]);
        return sum;
    }
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> result;
        unordered_map<int, int> map;
        int max = 0;
        poster(root, map, max);
        for (auto m : map) {
            if (m.second == max)
                result.push_back(m.first);
        }
        return result;
    }
};
/**************************************** 层序遍历的问题 ******************************/
/*
* (1)层序遍历的非递归算法；
*（2）按层处理的，比如获取每行最后一个值（最大值），比如每行使用next连接起来；
*/

//1  层序遍历的递归版本非递归版本；
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

//2  问题：将每行的数据使用箭头连接起来；
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root) return;
        queue<TreeLinkNode*> p, q;
        p.push(root);
        TreeLinkNode* pre = nullptr;        //与层序遍历相比，这个就是多需要一个前继节点；（前继节点的使用就是在遍历的时候有用）
        while (!p.empty()) {
            pre = nullptr;
            while (!p.empty()) {
                root = p.front();
                if (pre != nullptr) pre->next = root;
                pre = root;
                p.pop();
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
            p.swap(q);
        }
    }
};
//优化，如果需要使用常数空间，此题的思路是，链表就要有dummy；
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root) return;
        while (root) {
            TreeLinkNode dummy(0), *result = &dummy;        //与链表有关，就要使用dummy；
            while (root) {
                if (root->left) {
                    result->next = root->left;
                    result = result->next;
                }
                if (root->right) {
                    result->next = root->right;
                    result = root->right;
                }
                root = root->next;
            }
            root = dummy.next;
        }
    }
};

/*********************************************** 新建树的问题 **********************************/
/*新建树的基本原则：
（1）helper的返回值是TreeNode*类型；
（2）开始就创建node，然后递归产生root->left，和root->right;
（3）貌似使用迭代器的方法比较简单；
*/
/*
* (1)根据前序和中序，中序和后序新建树；
*（2）有序数组构建搜索二叉树；
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
        Iter mid = it1 + (it2 - it1) / 2;            //使用迭代器取中间元素，是第二部分的第一个元素；
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

//根据有序链表新建二叉搜索树；（难点在于怎么找到链表的中点）
class Solution {
    ListNode* get_mid_element(ListNode* head, ListNode* end) {  //链表的中点需要单独一个函数来遍历；
        if (head == end) return nullptr;
        ListNode* first = head, *second = head;
        while (second != end && second->next != end) {
            first = first->next;
            second = second->next->next;
        }
        return first;
    }
public:
    TreeNode* sortedListToBST(ListNode* head, ListNode* end = nullptr) {
        ListNode* mid = get_mid_element(head, end);         //实现链表的二分法，可以使用两个参数，第二个参数代表链表结束；
        if (!mid) return nullptr;
        TreeNode* root = new TreeNode(mid->val);
        root->left = sortedListToBST(head, mid);
        root->right = sortedListToBST(mid->next, end);
        return root;
    }
};

/*************************************** 前序遍历的算法题 *************************************/
//使用前序遍历得到所有的路径
class Solution {
    void preorder(TreeNode* root, vector<vector<int>>& result, vector<int> tmp, int sum) {
        if (!root) return;
        tmp.push_back(root->val);                                       //前序遍历 + 非全局的部分路径tmp，直到叶子节点才被push_back；
        sum -= root->val;
        if (!root->left && !root->right && sum == 0) {
            result.push_back(tmp);
        }
        preorder(root->left, result, tmp, sum);
        preorder(root->right, result, tmp, sum);
        
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> result;
        vector<int> tmp;
        preorder(root, result, tmp, sum);
        return result;
    }
};

//同是使用前序遍历得到一条路径的问题：判断有没有一条路径的和是sum；
class Solution {
    bool preorder(TreeNode* root, int sum) {
        if (!root) return false;
        if (!root->left && !root->right) {                          //强调root-to-leaf的，一定要检验是否是叶子节点，不能直接检查当前节点是否为空；
            if (sum == root->val) return true;          
            else return false;
        }
        return preorder(root->left, sum - root->val) || preorder(root->right, sum - root->val); //前序遍历没有问题；
    }
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        return preorder(root, sum);
    }
};


/***************************************** 另类的遍历方式 ****************************/
/*
* 分析题目的时候，遍历方式可以与前序，中序，后序遍历相反的方式来解题，代码还是差不多的；
*/
//题目，将树变成一个只有右节点的flat树；
class Solution {
    void postorder(TreeNode* root, TreeNode*& pre) {
        if (!root) return;
        postorder(root->right, pre);
        postorder(root->left, pre);
        root->left = nullptr;                   //从右下角开始遍历
        root->right = pre;
        pre = root;
    }
public:
    void flatten(TreeNode* root) {
        TreeNode* pre = nullptr;            //采取某种遍历的方式才可以使用pre，且初始值是nullptr；
        postorder(root, pre);
    }
};

/************************************** 需要用到返回值的典型题 *****************************/
/* 树的问题，一般可以使用返回值的，有以下几种情况：
（1）判断是否的；
（2）计算长度的；
（3）创建树的；
有返回值的一般利用起来是特别方便的：
*/

/* 问题1：判断两颗树是否相同；
问题2：判断一棵树是否镜像对称；    //从root拆成两个子树，然后左边的left和右边的right比较；
我想判断两颗树是否是一样的，势必要判断两个节点是否同时为空，不全为空的情况下怎么办？
*/

bool isSameTree (TreeNode* p, TreeNode* q) {
  if (p || q)                                 //将可能为空的情况提取出来，然后判断是否都为空，这个用于判断两个同时为空的情况很是不错；
    return p == q;
  return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right); 
}

//问题2：计算树的高度：
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;    //返回int或者bool都可以将左右的遍历放到return上；
    }
};
//问题3 由此，判断高度平衡的算法是：
class Solution {
    int cal_height(TreeNode* root) {
        if (!root) return 0;
        return max(cal_height(root->left), cal_height(root->right)) + 1;  //这有递归；
    }
public:
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        if (abs(cal_height(root->left) - cal_height(root->right)) > 1) return false;
        return isBalanced(root->left) && isBalanced(root->right);                     //这也有递归；
    }
};
//问题4  挑战性：计算高度最小值，必须是根到叶子节点：   //主要在于注意子节点为空时，当前节点是否是叶子节点；
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        int min1 = minDepth(root->left);
        int min2 = minDepth(root->right);
        return (min1 == 0 || min2 == 0) ?  min1 + min2 + 1 :min(min1, min2) + 1;   //两个技巧，两个数不知道哪个为0，使用min1 + min2 + 1;
                                                                                   //此题如果是长度为0，就不能计算0为最小长度；因为缺少一个子节点，但是另一节点不为空，当前节点就不是叶子节点；
    }
