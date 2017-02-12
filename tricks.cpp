//本文介绍编程过程中的小方法和技巧，如果内容比较多的话，会单独提取出去一个文件。

/* 技巧1：如何防止边界检查以提高效率
* （1）思路是，边界检查在循环会影响效率，比如排序算法中的边界检查，可以采用进入循环前先把边界检查的工作做好。没有边界检查的代码部分单独提出去的话，一般命名为unguard_开头；
* （2）如果此时还有函数调用的成本的话，可以将unguard_函数设置为inline的；
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
