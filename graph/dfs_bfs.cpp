// 一个结论：矩形的一次dfs可以遍历出一个岛屿，并可以返回出一个信息出来。可以利用这个信息解题。
// 比如下题，遍历的时候返回一个信息，是否为另外一个矩形的子岛屿。这个信息可通过dfs遍历得到。即就是最简单的dfs场景。
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

// bfs问题基本可以使用两个queue解决，如果不分层处理，甚至可以优化为一个queue。但是考虑使用queue会使得代码行数陡增，
// 所以可以将queue使用vector代替，但是基本思路是不变的。

// bfs要做的事1：dfs题目都可以尝试用bfs解决下。每层要做的事情。
//
// bfs最基本的套路，只不过这里使用vector代替queue了。
// 为啥需要两个queue？因为最后结果只关心最后一层的东西。
// 和dfs相比的效率问题：肯定比dfs要慢，因为bfs需要各种拷贝，dfs是直接在结果上进行各种处理的。
//
// 17. 电话号码的字母组合: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) {
        return {};
    }
    vector<string> q1,q2;
    q1.push_back("");
    for (int i = 0; i < digits.size(); i++) {
        string str = strs[digits[i] - '2'];
        for (int j = 0; j < q1.size(); j++) {
            for (int k = 0; k < str.size(); k++) {
                q2.push_back(q1[j] + string(1, str[k]));
            }
        }
        q1.swap(q2);
        q2.resize(0);
    }
    return q1;
}

// bfs要做的事情2：组合。组合是拿到所有结果，所以非常适合bfs。
//
// 子序列问题的一个思路：bfs拿到所有组合。前提是数据量足够小。那到底需要多少的数据量呢？
// 20: 2的20次幂是100万，这个量级还是可以接受的；
// 30: 2的30次幂是10亿，即1G，这个量级就不可接受了。
// 那如何将40的数据优化为20呢？分治。
//
// 1755. 最接近目标值的子序列和 https://leetcode.cn/problems/closest-subsequence-sum/
vector<int> getSubsetSum(vector<int>& nums, int i, int j) {
    vector<int> res{0};
    for (int k = i; k <= j; k++) {
        int sz = res.size();
        for (int m = 0; m < sz; m++) {
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

