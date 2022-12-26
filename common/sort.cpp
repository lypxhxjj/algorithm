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
        // sort(maxValues.rbegin(), maxValues.rend()); // 上两行代码等价
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

// 计数排序-基本实现
//
// 因为不是基于比较的排序算法，所以时间复杂度可以降到o(n)
//
// 912. 排序数组 https://leetcode.cn/problems/sort-an-array/
vector<int> sortArray(vector<int>& nums) {
    int count[100002] = {0};
    for (int num : nums) {
        count[num + 50000]++;
    }
    for (int i = 0, j = 0; i < 100002; i++) { // 6行代码等价于一个sort。
        while (count[i]-- > 0) {
            nums[j++] = i - 50000;
        }
    }
    return nums;
}

// 计数排序：当需要排序，且数字范围很小时，可以考虑计数排序，计数排序其实很快，代码也简单的
//
// 几个关键点：
// 1. 申请多少空间？maxV；如果只需要索引信息，可以多申请一个maxV+1，所以对应的数组定义为maxV +1/maxV+2;
// 2. 关键就是maxV不大。
//
// 274. H 指数 https://leetcode.cn/problems/h-index/
int hIndex(vector<int>& citations) {
    int count[1001] = {0};
    for (int citation : citations) {
        count[citation]++;
    }
    for (int i = 0, j = 0; i < 1001; i++) { // 这6行，其实等价于一个sort，但是时间复杂度是o(n)级别的，且没有额外申请空间，都是栈空间而已。
        while (count[i]-- > 0) {
            citations[j++] = i;
        }
    }
    for (int i = 0; i < citations.size(); i++) {
        if (citations[i] >= citations.size() - i) { // 这两行是本题的主要判断逻辑哈。
            return citations.size() - i;
        }
    }
    return 0;
}

// 计数排序-只用到了最终的索引信息
//
// 计数排序的count除了可以用于计数，还可以用于计算最终的索引信息。经过第二个循环之后，信息变为：
// count[arr[i] + 1] 为个数；
// count[arr[i]] 为 arr[i]最终位置的初始索引，多个元素依次向后拍；
//
// 1051. 高度检查器 https://leetcode.cn/problems/height-checker/
int heightChecker(vector<int>& heights) {
    const int MaxN = 102;  // 因为求了最终索引，所以这里需要额外多申请一个。
    int count[MaxN] = {0};
    for (int height : heights) {
        count[height + 1]++;  // 关键点1：只用到最终的索引。
    }
    for (int i = 1; i < MaxN; i++) {
        count[i] += count[i-1]; // 关键点2：生成索引。
    }
    int res = 0;
    for (int i = 0; i < heights.size(); i++) {
        if (i < count[heights[i]] || i >= count[heights[i] + 1]) { // 检查i是否在最终位置范围内即可。
            res++;
        }
    }
    return res;
}

// 计数排序应用-相对排序
//
// 排序问题当然可以sort，只不过此题的自定义排序规则也挺恶心的。但是使用计数排序的好处是，时间复杂度为o(n)
//
// 与普通的计数排序相比，这里自定义了顺序，所以for循环时需要修改为遍历顺序。
//
// 剑指 Offer II 075. 数组相对排序 https://leetcode.cn/problems/0H97ZC/
vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    vector<int> vals1(1001);
    for (int num : arr1) {
        vals1[num]++;
    }

    vector<int> res(arr1.size());
    int j = 0;
    for (int num : arr2) { // 这里是关键点，这行代码代表着顺序，因为自定义了顺序，所以当前行需修改为遍历arr2。
        for (int k = 0; k < vals1[num]; k++) {
            res[j++] = num;
        }
        vals1[num] = 0; // 这里也很关键，一旦用完，需要将count置为0.
    }
    for (int i = 0; i < 1001; i++) { // 剩下的点使用普通计数排序。
        for (int k = 0; k < vals1[i]; k++) {
            res[j++] = i;
        }
    }
    return res;
}