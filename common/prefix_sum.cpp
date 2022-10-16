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

// 前缀和的另外一个版本：任意区间，任意字符出现的次数。（二维数组，第一维代表前缀和，第二维代表字符，值代表个数）
// 这里能这样使用的一个前提：字符数量/数字数量是有限制的，比如此题最多100种数字。
// 结论：如果字符数量有限（比如都是小写字母），根据前缀和，可以快速找到任何区间内各个数字出现的次数。
// 引申结论：任意区间内字符数量，因为字符集大小较小，等价于字符已排序，可以解决排序相关的问题。
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