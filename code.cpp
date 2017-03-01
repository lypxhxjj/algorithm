/* 
*  此文件内收集优美的解法，主要是根据C++11新特性来实现的一些常见功能；
*/

//接下来几个是排序算法，大部分都可以使用几行代码就可以完成；
//引用参见：https://zhuanlan.zhihu.com/p/20652569?refer=xiaochi

/* 选择排序算法：
* （1）找到最小值位置可以使用std::min_element函数；
* （2）实现算法使用迭代器更好用，此时交换元素，使用std::iter_swap函数
*/
template<class FwdIt, class Compare = std::less<>>
void selection_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
    for (auto it = first; it != last; ++it) {
        auto const selection = std::min_element(it, last, cmp);
        std::iter_swap(selection, it); 
        //assert(std::is_sorted(first, std::next(it), cmp));
    }
}


/* 插入排序算法：
* （1）找到插入位置使用：upper_bound函数；
* （2）找到插入位置，插入的话可以使用旋转操作：std::rotate;
*     ----》std::rotate也可以理解为交换两部分迭代器中的内容，参数分别是first,middle,last；
*     ----》迭代器实现加减法运算需要使用：std::next(Iter, n)；来实现；
* （3）使用rotate可以，也可以直接使用copy_backward函数（最后一个参数是end()），只不过此时多了一行代码；
*/
template<class FwdIt, class Compare = std::less<>>
void insertion_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
    for (auto it = first; it != last; ++it) {
        auto const insertion = std::upper_bound(first, it, *it, cmp);
        std::rotate(insertion, it, std::next(it)); 
        //assert(std::is_sorted(first, std::next(it), cmp));
    }
}


/* 快速排序算法：
* （1）一般使用迭代器来实现算法，更具有通用性，涉及到的数组大小使用std::distance，迭代器的加减操作：std::next和std::prev；
* （2）使用两个std::partition函数，第一个是找到小于*it的数组，第二个是找到大于等于*it中等于的部分，最后递归的只需要是不等于的那个部分；
*     ----》第三个参数可以使用仿函数来实现，std::bind1st(std::greater<int>(), *it)代表*it大的话放左边，op(*it, value)，*it是第一个参数；
*     ----》等于的话：std::bind1st(std::equal_to<int>)
*     ----》std::greater<int>()，模板参数中的int，替换掉的话，可以使用Iter::value_type.(traits技法)
*/
template<class FwdIt, class Compare = std::less<>>
void quick_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
    auto const N = std::distance(first, last);
    if (N <= 1) return;
    auto const pivot = *std::next(first, N / 2);
    auto const middle1 = std::partition(first, last, [=](auto const& elem){ 
        return cmp(elem, pivot); 
    });
    auto const middle2 = std::partition(middle1, last, [=](auto const& elem){ 
        return !cmp(pivot, elem);
    });
    quick_sort(first, middle1, cmp); // assert(std::is_sorted(first, middle1, cmp));
    quick_sort(middle2, last, cmp);  // assert(std::is_sorted(middle2, last, cmp));
}


/* 归并排序算法：
* （1）思想是对数组对半分，直到拆成一个元素直接返回，然后使用merge合并；
*     ----》此处用的是std::inplace_merge，与merge的区别是，merge是两个不相关的数组合并到一个新的迭代器中，就地合并的话则是合并同一数组中的元素，只有三个参数，分别是first,middle,last；
*     ----》实现上，就地排序使用的是额外空间拷贝然后调用merge。
*/

template<class BiDirIt, class Compare = std::less<>>
void merge_sort(BiDirIt first, BiDirIt last, Compare cmp = Compare{})
{
    auto const N = std::distance(first, last);
    if (N <= 1) return;                   
    auto const middle = std::next(first, N / 2);
    merge_sort(first, middle, cmp); // assert(std::is_sorted(first, middle, cmp));
    merge_sort(middle, last, cmp);  // assert(std::is_sorted(middle, last, cmp));
    std::inplace_merge(first, middle, last, cmp); // assert(std::is_sorted(first, last, cmp));
}


/* 堆排序算法
* （1）学过heap算法，堆排序很简单，两行代码就可以，第一步make_heap，第二步sort_heap；
* （2）实现make_heap，可以使用push_heap算法，这个算法会将输入容器的最后一个元素当做待插入元素，调整为堆；
* （3）实现sort_heap，可以使用pop_heap算法，每次调用完，就会将最大值保存到容器的最后一个元素。
*/

template<class RandomIt, class Compare = std::less<>>
void heap_sort(RandomIt first, RandomIt last, Compare cmp = Compare{})
{
    lib::make_heap(first, last, cmp); // assert(std::is_heap(first, last, cmp));
    lib::sort_heap(first, last, cmp); // assert(std::is_sorted(first, last, cmp));
}
//为了防止你说我作弊，我自己实现了std中的make_heap和sort_heap。

namespace lib {

// NOTE: is O(N log N), not O(N) as std::make_heap
template<class RandomIt, class Compare = std::less<>>
void make_heap(RandomIt first, RandomIt last, Compare cmp = Compare{})
{
    for (auto it = first; it != last;) {
        std::push_heap(first, ++it, cmp); 
        assert(std::is_heap(first, it, cmp));           
    }
}

template<class RandomIt, class Compare = std::less<>>
void sort_heap(RandomIt first, RandomIt last, Compare cmp = Compare{})
{
    for (auto it = last; it != first;) {
        std::pop_heap(first, it--, cmp);
        assert(std::is_heap(first, it, cmp));           
    } 
}

}   // namespace lib

//以下添加4种遍历树的方法，前三种格式非常统一，最后一种的swap用的非常好；

//前序遍历
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> s;
        while (root || !s.empty()) {
            while (root) {                              //第一步，添加子节点；
                s.push(root);
                result.push_back(root->val);
                root = root->left;
            }
            root = s.top();                             //第二步，出栈操作；
            s.pop();
            root = root->right;                         //第三步，切换到右节点；
        }
        return result;
    }
};

//中序遍历
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> s; 
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            result.push_back(root->val);
            s.pop();
            root = root->right;
        }
        return result;
    }
};

//后序遍历
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> s;
        while (root || !s.empty()) {
            while (root) {
                s.push(root);
                result.push_back(root->val);
                root = root->right;
            }
            root = s.top();
            s.pop();
            root = root->left;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

//层序遍历
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        queue<TreeNode*> p, q;
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
            swap(p, q);                                 //swap用的少了很多代码；
        }
        return result;
    }
};
