//本文介绍编程过程中的小方法和技巧，如果内容比较多的话，会单独提取出去一个文件。

/* 技巧1：如何防止边界检查以提高效率
* （1）思路是，边界检查在循环会影响效率，比如排序算法中的边界检查，可以采用进入循环前先把边界检查的工作做好。没有边界检查的代码部分单独提出去的话，一般命名为unguard_开头；
* （2）如果此时还有函数调用的成本的话，可以将unguard_函数设置为inline的；
* （3）快速排序的防止边界检查是在根本上解决的，不是使用这种套路。详见《快速排序的理解与优化》
*/

template<class Iter>
inline void unguard_linear_insert(Iter it1, Iter it2, Iter value) {
    auto tmp = *value;
    while (tmp < *std::prev(it2)) {
        *it2 = *std::prev(it2);
        it2 = std::prev(it2);
    }
    *it2 = tmp;
}

//[it1, it2)是有序序列，迭代器value是待插入的值；
template<class Iter>
inline void linear_insert(Iter it1, Iter it2, Iter value) {
    auto tmp = *value;
    if (tmp < *it1) {
        copy_backward(it1, it2, std::next(it2));
        *it1 = tmp;
    }
    else
        unguard_linear_insert(it1, it2, value);
}

template<class Iter>
void insert_sort1(Iter it1, Iter it2) {
    for (Iter it = std::next(it1); it != it2; ++it) {
        linear_insert(it1, it, it);
    }
}

/* 技巧2：如何使用前置++和while循环搭配
* （1）原理：前置++效率比后置++要高，所以使用上尽可能地使用前置++，然后合适的搭配while循环可以使得代码行数减少，比如省掉单独的++操作；
* （2）使用方法：在初始化变量时，有意的声明当前位置的前一个位置的（++），或者当前位置的后一个位置的（--）；（本例中由于是从第二个元素和最后一个元素
*     开始，所以正好定义第一个元素和end()作为初始值，所以符合条件）
*/
template<class Iter>
void median(Iter a, Iter b, Iter c) {
    typedef typename Iter::value_type T;
    if (b == c) {
        if (*a > *b) std::swap(*a, *b);
        return;
    }
    T max_element = std::max(std::max(*a, *b), *c);
    T min_element = std::min(std::min(*a, *b), *c);
    T mid = *a + *b + *c - max_element - min_element;
    std::swap(*a, mid);
    std::swap(*b, min_element);
    std::swap(*c, max_element);
}

template<class Iter>
void quick_sort3(Iter it1, Iter it2) {
    auto size = std::distance(it1, it2);
    if (size <= 1) return;
    
    median(it1, std::next(it1, size / 2), std::prev(it2));
    
    Iter begin = it1;
    Iter end = it2;
    while (begin < end) {
        while (*++begin < *it1);
        while (*--end > *it1);
        if (begin < end) std::iter_swap(begin, end);
    }
    
    std::swap(*it1, *end);
    quick_sort3(it1, end);
    quick_sort3(std::next(end), it2);
}

/*技巧3：代码的缩减技巧总结
* 较一般性：
*（1）边界检查，可以先看看是否包括在循环中了，此题就不需要最开始的边界检查；（可以最后检查）
*（2）同一作用的变量考虑在同一行定义，定义dummy和result可以在同一行：ListNode dummy, *result = &dummy;
* (3)循环之外解决特殊情况，可以考虑将其放到循环的判定条件中；while (l1 || l2 || flag)
*（5）能不使用临时变量就不使用；val = val % 10可以合并到下一行；
* 特殊性：
*（4）两个list不知道哪个到头没，可以分开放到临时变量中，其实也是不用的； int val = flag + l1 ? l1->next : 0;
*（6）其实进位的flag既可以当做进位，又可以当做总和；
*/
//化简之前的代码：
    ListNode *addLists(ListNode *l1, ListNode *l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        ListNode dummy(0);
        ListNode* result = &dummy;
        int flag = 0;
        while (l1 || l2) {
            int data1 = l1 ? l1->val : 0;
            int data2 = l2 ? l2->val : 0;
            int val = data1 + data2 + flag;
            flag = val / 10;
            val = val % 10;
            result->next = new ListNode(val);
            result = result->next;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }
        if (flag)
            result->next = new ListNode(1);
        return dummy.next;
    }
    
//化简之后的代码
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0), *result = &dummy;
        int flag = 0;
        while (l1 || l2 || flag) {
            flag += (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
            result->next = new ListNode(flag % 10);
            flag /= 10;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
            result = result->next;
        } 
        return dummy.next;
        
    }
