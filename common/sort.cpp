// 当数字种类很少时，o(n)就已经是有序的了。只不过此时遍历会有些不方便。
// 其实可以写一个迭代器，就方便了，因为每次找到下一个元素都需要一个while。
// 
// 参考：common/prefix_sum.cpp 1906. 查询差绝对值的最小值
void traverse() {
    int delta = 101; 
    int lastVal = 101; // 遍历要素1：lastVal需要单独记下来，因为不是顺序的了。
    for (int k = 0; k <= 100; k++) {
        if (prefixCntSum[j + 1][k] - prefixCntSum[i][k] > 0) { // 遍历要素2：说明找到了下个元素。
            delta = min(delta, k - lastVal);
            lastVal = k; // 哪些是必做，哪些是不必做的
        }
    }
}

// 取最大最小的2个数：插入排序的方法
// 而sort函数在数据量很少的情况下，本身就是插入排序了，所以可以借助sort排序实现
//
// but: 插入排序一定快吗？并没有，并没有直接sort数组快。猜测是因为，logn在一万条数据这种其实很小，远比下面函数做的事情少的多。
//
// 1913. 两个数对之间的最大乘积差 https://leetcode.cn/problems/maximum-product-difference-between-two-pairs/
int maxProductDifference(vector<int>& nums) {
    vector<int> maxValues{nums[0], nums[1]};
    vector<int> minValues{nums[0], nums[1]};

    for (int i = 2; i < nums.size(); i++) {
        maxValues.push_back(nums[i]);
        minValues.push_back(nums[i]);
        sort(maxValues.begin(), maxValues.end(), greater<int>());
        sort(minValues.begin(), minValues.end());
        maxValues.pop_back();
        minValues.pop_back();
    }
    return maxValues[0] * maxValues[1] - minValues[0] * minValues[1];
}

// 三个数比较大小：依旧放入数组中，排序解决
//
// 本题的思路，找规律，脑中模拟。
//
// 1753. 移除石子的最大得分 https://leetcode.cn/problems/maximum-score-from-removing-stones/
int maximumScore(int a, int b, int c) {
    vector<int> arr{a,b,c};
    sort(arr.begin(), arr.end());
    int delta = arr[2] - arr[1];
    if (delta >= arr[0]) {
        return arr[0] + arr[1];
    }
    return arr[0] + (arr[1] + arr[2] - arr[0]) / 2;
}