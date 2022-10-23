// 前缀和一般意味着预处理，而经过预处理得到的信息，我们可以认为是已知的，但是又不是那么显而易见的。

// 二维矩阵的前缀和
// 计算过程非常优雅，多出一行一列，可以在计算前缀和和使用前缀和的时候不需要考虑各种边界情况。
vector<vector<int>> prefixSum(vector<vector<int>>& matrix) {
    vector<vector<int>> matPrefixSum(matrix.size() + 1, vector<int>(matrix[0].size() + 1));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            matPrefixSum[i + 1][j + 1] = matPrefixSum[i + 1][j] + matPrefixSum[i][j + 1] -matPrefixSum[i][j] + matrix[i][j];
        }
    }
    return matPrefixSum;
}

// 二维前缀和的使用。
// 为更符合使用习惯，可以将这个四个坐标分别加加。
int sumRegion(vector<vector<int>>& matPrefixSum, int row1, int col1, int row2, int col2) {
    row1++, col1++, row2++, col2++;
    return matPrefixSum[row2][col2] - matPrefixSum[row1 - 1][col2] - matPrefixSum[row2][col1-1] + matPrefixSum[row1 - 1][col1-1];
}

// 特殊：矩阵才可以使用前缀和，圆就不行，下题只能普通遍历了。
//
// 优化：我可以先使用二分查找x,y（找完取交集），找到圆所在正方形内的所有点，然后遍历这些点再查找在圆内的。但效率很差。
//
// 1828. 统计一个圆中点的数目 https://leetcode.cn/problems/queries-on-number-of-points-inside-a-circle/
vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
    vector<int> res(queries.size());
    for (int i = 0; i < queries.size(); i++) {
        int r = queries[i][2] * queries[i][2];
        for (auto& point : points) {
            int xDis = point[0] - queries[i][0];
            int yDis = point[1] - queries[i][1];
            if (xDis * xDis + yDis * yDis <= r) {
                res[i]++;
            }
        }
    }
    return res;
}

// 前缀和结论：任意区间，任意字符出现的次数。（二维数组，第一维代表前缀和，第二维代表字符，值代表个数）
// 结论：利用前缀和可以快速得到「字符串」任意区间内任意字符出现的次数。
// 引申结论：对于vector<int>，如果元素范围有限，也可以快速找到任何区间内各个数字出现的次数。
// 题目：下面（1906. 查询差绝对值的最小值）
vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
    vector<vector<int>> prefixCntSum(nums.size() + 1, vector<int>(101)); // 前缀和永远多一个的
    for (int i = 0; i < nums.size(); i++) {
        prefixCntSum[i + 1] = prefixCntSum[i];
        prefixCntSum[i + 1][nums[i]]++;
    }
}

// 前缀和的典型使用：一个数组，多次查询问题
// 主要就是两个模板：次数前缀和模板；按次数有序遍历（sort.cpp）
// 关键思路：任意区间内字符数量，因为字符集大小较小，等价于字符已排序，可以解决排序相关的问题。
// 
// 1906. 查询差绝对值的最小值：https://leetcode.cn/problems/minimum-absolute-difference-queries/submissions/
vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
    vector<vector<int>> prefixCntSum(nums.size() + 1, vector<int>(101)); // 前缀和永远多一个的
    for (int i = 0; i < nums.size(); i++) {
        prefixCntSum[i + 1] = prefixCntSum[i];
        prefixCntSum[i + 1][nums[i]]++;
    }

    vector<int> res;
    for (auto p : queries) {
        int i = p[0], j = p[1];
        // 模板开始
        int delta = 101; 
        int lastVal = -101;
        for (int k = 0; k <= 100; k++) {
            if (prefixCntSum[j + 1][k] - prefixCntSum[i][k] > 0) {
                delta = min(delta, k - lastVal);
                lastVal = k; // 哪些是必做，哪些是不必做的
            }
            if (delta == 1) {
                break;
            }
        }
        // 模板结束。
        if (delta == 101) {
            res.push_back(-1);
        } else {
            res.push_back(delta);
        }
    }
    return res;
}

// 前缀和的结论：可用于求任意区间内，矩形接水的量（区间两侧为高墙）
//
// 引申结论：当不是用于批量查询场景，前缀和可考虑优化为「两个前缀和变量」 + 双指针。
//
// 本题，为啥会想到用前缀和？o(n^2)算法中，从当前元素向前找的算法，可以优化为前缀和问题。
//
// 本题的方法2：从当前元素向前找，可以使用二分的方法向前找，找到当前元素的解，而二分的方法还是要借助前缀和。不如直接优化为前缀和 + 双指针的方式。
//
// 1838. 最高频元素的频数 https://leetcode.cn/problems/frequency-of-the-most-frequent-element/
int maxFrequency(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());

    int res = 1;
    long long prefixSumi = nums[0], prefixSumj = 0;
    for (int i = 1, j = 0; i < nums.size(); i++) { // 这里j是从0开始的，即有效元素的下一个位置
        prefixSumi += nums[i];
        while ((long long)(i - j + 1) * nums[i] - (prefixSumi - prefixSumj) > k) {
            prefixSumj += nums[j++];
        }
        res = max(res, i - j + 1);
    }
    return res;
} 