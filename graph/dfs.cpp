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