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
// 2. square的索引定位（大方块的路径压缩）：index = i / 3 * 3 + j / 3;
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

// 如何环形遍历矩形？需要背下来的模板：
// 1. 四个变量代表上下左右边界：上边界（i）,左边界（j），右边界（n）,下边界（m）
// 2. 不断遍历，并不断重新定义上下左右边界
//
// 54. 螺旋矩阵 https://leetcode.cn/problems/spiral-matrix/
//
// 小问题：由于每次不断重新定义边界，所以没办法遍历两次，比如下题：
// 1914. 循环轮转矩阵 https://leetcode.cn/problems/cyclically-rotating-a-grid/
//
// 解决方法：将下述逻辑封装到函数，四个边界作为参数，就可以实现多次调用了。
vector<int> spiralOrder(vector<vector<int>>& grid) {
    vector<int> data;
    int i = 0, j = 0, m = grid.size() - 1, n = grid[0].size() - 1;
    while (true) {
        for (int k = j; k <= n; k++) {
            data.push_back(grid[i][k]);
        }
        if (++i > m) break;
        for (int k = i; k <= m; k++) {
            data.push_back(grid[k][n]);
        }
        if (--n < j) break;
        for (int k = n; k >= j; k--) {
            data.push_back(grid[m][k]);
        }
        if (--m < i) break;
        for (int k = m; k >= i; k--) {
            data.push_back(grid[k][j]);
        }
        if (++j > n) break;
    }
    return data;
}