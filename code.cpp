基础砖块

如同建筑工人需要用到砖块来构建大楼，我们也需要用到一些基础的函数。幸而 STL 提供了很多这样的函数。

#include <algorithm>    // min_element, iter_swap, 
                        // upper_bound, rotate, 
                        // partition, 
                        // inplace_merge,
                        // make_heap, sort_heap, push_heap, pop_heap,
                        // is_heap, is_sorted
#include <cassert>      // assert 
#include <functional>   // less
#include <iterator>     // distance, begin, end, next
其中 std::begin() / std::end() / std::next() / std::is_sorted / std::is_heap 这些算法都是自 C++11 才有的。

选择排序

选择排序的时间复杂度总是，不管数据是何种样子的。但它有一点好，就是总体的交换次数最少。所以，如果交换元素的开销很大，不妨用这个算法。

这个算法的实现方法很简单，重复使用 std::min_element 来发现最小的元素，然后用 iter_swap 将它交换到应在的位置。

template<class FwdIt, class Compare = std::less<>>
void selection_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
    for (auto it = first; it != last; ++it) {
        auto const selection = std::min_element(it, last, cmp);
        std::iter_swap(selection, it); 
        assert(std::is_sorted(first, std::next(it), cmp));
    }
}
注意 selection_sort 在每次循环开启之前， [first, it) 里的元素就已经排序好了。和 std::sort比起来，这个迭代器只要求是前向迭代器，而非像 std::sort() 一样需要随机迭代器。

插入排序

虽然只是最基本的排序方法，虽然最坏的情况要达到，但是插入排序依然是很有用的排序方法。因为它是适应性的，如果数据基本有序，就有很好的效果。或者数据的量很小，它也会有很小的表现（因为它的开销很小）。因这个原因，插入排序通常会作为其他「大」递归算法（如快速排序和合并排序）的基本例。

为了实现 insertion_sort ，我们不停的使用 std::upper_bound 来找到当前元素应该在的位置，然后使用 std::rotate 将当前元素放到正确的位置。

template<class FwdIt, class Compare = std::less<>>
void insertion_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
    for (auto it = first; it != last; ++it) {
        auto const insertion = std::upper_bound(first, it, *it, cmp);
        std::rotate(insertion, it, std::next(it)); 
        assert(std::is_sorted(first, std::next(it), cmp));
    }
}
注意，insertion_sort 的循环不变量是已经将 [first, it) 排序。插入排序也是只需要前向迭代器。
快速排序

快速排序是一个很优秀的排序算法。如果不要求稳定排序，一般我们会选择这个算法。它的期望复杂度是，最坏复杂度是。

即使是最简单的快速排序，也是很复杂的。下面的算法先找到中间位置的元素，作为pivot，然后通过两次 std::partition ( O(N) 的复杂度) to调用，来找到比pivot小的，比pivot大的。最后，这两部分再次递归的调用快速排序。

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
只有pivot将数据分为大致相等的两部分，才能达到的复杂度。但的复杂度并不能将这种pivot选出来。因此大家想了很多办法，欲知详情，请去看原答案。

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
