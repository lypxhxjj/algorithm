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

归并排序

如果不考虑的空间占用，归并排序是极好的算法：因为它是唯一的稳定的算法。

实现上也很简单：找到输入列表的中间点，然后对两边分别执行归并排序。最后使用 std::inplace_merge 将两个部分合并。

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
归并排序需要双向迭代器，因为 std::inplace_merge 需要它。注意，当对链表进行排序时，归并排序只需要 O(log N) extra的额外空间（来执行递归）。

堆排序

堆排序很容易实现。它是一个的原地排序法，但是它不稳定。

首先，我们将一个数组「堆化」。然后，我们不断的执行这么一个动作：将根元素和最后的元素交换，然后「向下沉」来重整堆序。有了标准模板库，生活变得如此容易：

template<class RandomIt, class Compare = std::less<>>
void heap_sort(RandomIt first, RandomIt last, Compare cmp = Compare{})
{
    lib::make_heap(first, last, cmp); // assert(std::is_heap(first, last, cmp));
    lib::sort_heap(first, last, cmp); // assert(std::is_sorted(first, last, cmp));
}
为了防止你说我作弊，我自己实现了std中的make_heap和sort_heap。

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
标准模板库的 push_heap 和 pop_heap 的复杂度都是 O(log N)。注意到在 [first, last) 上循环，导致了 make_heap 的复杂度变为 O(N log N) ，而非 std::make_heap 的only O(N) 。不过，总体的复杂度仍然是，这无关紧要。
