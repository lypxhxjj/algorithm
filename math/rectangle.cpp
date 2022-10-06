// 两个矩形的重叠长和宽
// 两个矩形最小的上边界，减去最大的下边界。上下边界说的是y相关，左右边界才是x相关。
//
// 223. 矩形面积: https://leetcode.cn/problems/rectangle-area/
int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
    int cx = max(0, min(ax2, bx2) - max(ax1, bx1));
    int cy = max(0, min(ay2, by2) - max(ay1, by1));
    return (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1) - cx * cy;
}

// 9 * 9 矩阵的特点：
// 1. visited数组写法：bool rows[10][10] = {0}, cols[10][10] = {0}, square[10][10] = {0};
// 2. square的索引定位：index = i / 3 * 3 + j / 3;
//
// 36. 有效的数独 https://leetcode.cn/problems/valid-sudoku/
// 37. 解数独 https://leetcode.cn/problems/sudoku-solver/
bool isValidSudoku(vector<vector<char>>& board) {
    bool rows[10][10] = {0}, cols[10][10] = {0}, square[10][10] = {0};
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == '.') {
                continue;
            }
            int val = board[i][j] - '0'; // 注意矩阵中给的是字符，不是一两次在这里出错了。
            if (rows[i][val] || cols[j][val] || square[i/ 3 * 3 + j / 3][val]) {
                return false;
            }
            rows[i][val] = cols[j][val] = square[i/ 3 * 3 + j / 3][val] = true;
        }
    }
    return true;
}

// 递归遍历矩阵：每层处理一个点
//
// 37. 解数独 https://leetcode.cn/problems/sudoku-solver/
bool dfs(vector<vector<char>>& board, int i, int j) {
    if (i == board.size()) return true;
    if (j == board.size()) return dfs(board, i + 1, 0);
}

// 正方形内，所有点坐标绝对值的和。原点在正方形中心。
// 这种数学算数问题的思路：简化 + 分解；
// 正常思路：按圈计算和 -> 根据对称性简化到1/4圈（右上都是正数） -> 按一列一列去算
//
// 1954. 收集足够苹果的最小花园周长 https://leetcode.cn/problems/minimum-garden-perimeter-to-collect-enough-apples/
long long minimumPerimeter(long long neededApples) {
    auto calAppleCnt = [](long long n) ->long long{
        return 2 * n * (2 * n + 1) * (n + 1); // 这个是最后计算出的公式：2n(2n+1)(n+1)
    };

    int i = 1, j = 100000; // 为啥右边界是10^5，因为最多是10^15，而上面是三次方。
    while (i < j) {
        long long mid = i + (j - i) / 2;
        long long apples = calAppleCnt(mid);
        if (apples == neededApples) {
            return mid * 8; // 因为返回值比较特殊，所以可以不在这里处理返回值。
        } else if (apples < neededApples) {
            i = mid + 1;
        } else {
            j = mid;
        }
    }
    return i * 8;
}
