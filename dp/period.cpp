// 区间dp的思路，一个输入数组，区间dp定义为一个二元数组，代表从i到j。

// 一个数组的二维dp：区间dp
//
// 遍历方式：区间dp由于从斜线向右遍历，所以必须从下到上，从左到右遍历。因为上边的会依赖下边的。
// 
// 本题的表达式推导：任意k个组合最优，其实可以优化为任意两个组合最优，因为两个组合最优就嵌套包含了多个组合最优。
//
// 664. 奇怪的打印机 https://leetcode.cn/problems/strange-printer/
int strangePrinter(string s) {
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), s.size()));

    for (int i = (int)s.size() - 1; i >= 0; i--) {
        for (int j = i; j < s.size(); j++) {
            if (i == j) {
                dp[i][j] = 1;
                continue;
            }
            if (s[i] == s[j]) {
                dp[i][j] = dp[i][j - 1];
                continue;
            }
            for (int k = 1; k < j - i + 1; k++) {
                dp[i][j] = min(dp[i][j], dp[i][i + k - 1] + dp[i + k][j]); // 拆成两个，注意k的边界，需要保证这俩dp不越界。
            }
        }
    }
    return dp[0].back();
}