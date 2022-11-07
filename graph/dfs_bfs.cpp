// 矩形dfs问题：dfs过程中返回额外信息。
//
// 矩形dfs的基本方法：
// 1. 定义xDirect, yDirect；
// 2. 数组允许修改，可使用grid自身作为visited数组，否则就需要定义visited数组了。
//
// 本题中，如何返回额外信息？
// 1. 完全不影响遍历过程的情况下，返回一个bool值，代表是否为子岛屿。
// PS: 一个坑：返回bool还不影响遍历过程，需要注意是否被短路：res = dfs() && res;
//
// 1905. 统计子岛屿 https://leetcode.cn/problems/count-sub-islands/
vector<int> xDirect{0, 0, 1, -1}, yDirect{1,-1,0,0};
bool set2(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int i, int j) {
    if (i < 0 || j < 0 || i >= grid2.size() || j >= grid2[0].size()) {
        return true;
    }
    if (grid2[i][j] == 0 || grid2[i][j] == 2) {
        return true;
    }
    bool res = true;
    if (grid1[i][j] == 0) {
        res = false;
    }
    grid2[i][j] = 2;
    for (int k = 0; k < 4; k++) {
        res = set2(grid1, grid2, i + xDirect[k], j + yDirect[k]) && res; // 返回值bool类型要注意，小心短路。
    }
    return res;
}
int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
    int res = 0;
    for (int i = 0; i < grid1.size(); i++) {
        for (int j = 0; j < grid1[0].size(); j++) {
            if (grid2[i][j] == 1) {
                if (set2(grid1, grid2, i, j)) {
                    res++;
                }
            }
        }
    }
    return res;
}

// 矩形dfs问题：不能原路返回的dfs
//
// 如何不原路返回？参数中额外加个方向。两个技巧（其余都一样）：
// 1. 参数四个方向DULR，理解为：不是来自D，那么就可以往D走，对于D来说，遍历来自U；
// 2. 多了这个参数，没办法使用xDirect和yDirect了。
//
// 1559. 二维网格图中探测环 https://leetcode.cn/problems/detect-cycles-in-2d-grid/
bool dfs(vector<vector<char>>& grid, int i, int j, char ch, vector<vector<bool>>& visited, char from) {
    if (i < 0 || j < 0 || i >=grid.size() || j >= grid[0].size() || grid[i][j] != ch) {
        return false;
    }
    if (visited[i][j]) return true;

    visited[i][j] = true;
    if ((from != 'D' && dfs(grid, i + 1, j, ch, visited, 'U')) ||
    (from != 'U' && dfs(grid, i - 1, j, ch, visited, 'D')) ||
    (from != 'L' && dfs(grid, i, j - 1, ch, visited, 'R')) ||
    (from != 'R' && dfs(grid, i, j + 1, ch, visited, 'L'))) {
        return true;
    }
    return false;
}
bool containsCycle(vector<vector<char>>& grid) {
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (!visited[i][j]) {
                if (dfs(grid, i, j, grid[i][j], visited, 'L')) {
                    return true;
                }
            }
        }
    }
    return false;
}

// bfs解决排列组合问题。
//
// bfs解决排列组合问题基本思路：
// 1. 两个queue。如果不分层处理，甚至可以优化为一个queue。但是考虑使用queue会使得代码行数陡增，所以可以将queue使用vector代替。
// 2. 一个初始化。处理queue之前一定要先入队一个。
// 3. 处理每一层。每一层的处理基本两种思路：利用上一层的生成当前层，并丢弃上一层的（两个queue）；利用前边所有生成新的，以2倍的方式增加（一个queue）；
//
// bfs的效率问题？只要不是获取所有排列组合，一般都会有效率问题的，因为涉及大量的中间结果的生成和保存；
//
// 本题中：需要分层，因为新一层需要上一层作为基础生成新的字符串。
//
// 17. 电话号码的字母组合: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) {
        return {};
    }
    vector<string> q1,q2;
    q1.push_back("");
    for (int i = 0; i < digits.size(); i++) { // 每一层
        string str = strs[digits[i] - '2'];
        for (int j = 0; j < q1.size(); j++) { // 以1=》多生成新的元素；
            for (int k = 0; k < str.size(); k++) {
                q2.push_back(q1[j] + string(1, str[k]));
            }
        }
        q1.swap(q2); // 用完即抛弃。
        q2.resize(0);
    }
    return q1;
}

// bfs要做的事情2：组合。组合是拿到所有结果，所以非常适合bfs。
//
// 子序列什么时候可以使用bfs：bfs拿到所有组合。前提是数据量足够小。那到底需要多少的数据量呢？
// 20: 2的20次幂是100万，这个量级还是可以接受的；
// 30: 2的30次幂是10亿，即1G，这个量级就不可接受了。
// 那如何将40的数据优化为20呢？分治。
//
// 1755. 最接近目标值的子序列和 https://leetcode.cn/problems/closest-subsequence-sum/
vector<int> getSubsetSum(vector<int>& nums, int i, int j) {
    vector<int> res{0};
    for (int k = i; k <= j; k++) { // 每个元素即为一层；
        int sz = res.size();
        for (int m = 0; m < sz; m++) { // 用之前所有元素生成新的元素
            res.push_back(res[m] + nums[k]);
        }
    }
    return res;
}
int minAbsDifference(vector<int>& nums, int goal) {
    auto sums1 = getSubsetSum(nums, 0, nums.size()/ 2); // 所有左半子序列的和；
    auto sums2 = getSubsetSum(nums, nums.size() / 2 + 1, nums.size() - 1); // 所有右半子序列的和；
    sort(sums1.begin(), sums1.end());
    sort(sums2.begin(), sums2.end()); // 排序
    int res = abs(sums1[0] + sums2[0] - goal);
    int i = 0, j = sums2.size() - 1; // 双指针法去合并
    while (i < sums1.size() && j >= 0) {
        int sum = sums1[i]+sums2[j] - goal;
        res = min(res, abs(sum));
        if (sum == 0) return 0;
        if (sum > 0) {
            j--;
        } else {
            i++;
        }
    }
    return res;
}

