// 矩阵内正方向的最大值，表达式为：
// 和左边，上边，左上三个位置有关，三个地方都需要时正方形才可以。
// dp[i + 1][j + 1] = 1 + min(dp[i][j], min(dp[i][j + 1], dp[i + 1][j]))
// 之所以多申请了一行和一列，是因为这样就不可以不用考虑边界了。
//
// 221. 最大正方形: https://leetcode.cn/problems/maximal-square/
// 
// 其他解法：当前值保存左边1的个数，然后向上去寻找。
int maximalSquare(vector<vector<char>>& matrix) {
    int res = 0;
    vector<vector<int>> dp(matrix.size() + 1, vector<int>(matrix[0].size() + 1));
    for (int i = 0 ; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] != '0') {
                dp[i + 1][j + 1] = 1 + min(dp[i][j], min(dp[i][j + 1], dp[i + 1][j]));
                res = max(res, dp[i + 1][j + 1]);
            }
        }
    }
    return res * res;
}