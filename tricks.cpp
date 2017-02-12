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

/* 技巧2：如何使用前置++和while循环搭配
*  前置++效率比后置++要高，所以使用上尽可能地使用前置++，然后合适的搭配while循环可以使得代码行数减少，比如省掉单独的++操作；
*  使用方法：在初始化变量时，有意的声明当前位置的前一个位置的（++），或者当前位置的后一个位置的（--）；
*/

template<class Iter>
void quick_sort(Iter it1, Iter it2) {
    auto size = std::distance(it1, it2);
    if (size < 2) return;
    
    Iter begin = it1;
    Iter end = it2;
    auto tmp = *it1;
    while (begin < end) {
        while (*--end > tmp );  //没有必要使用边界判断，因为*begin肯定是等于的；
        *begin = *end;
        while (begin < end && *++begin < tmp);
        *end = *begin;
    }
    *begin = tmp;
    quick_sort(it1, begin);
    quick_sort(begin + 1, it2);
}
