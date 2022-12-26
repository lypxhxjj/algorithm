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