// bfs 求最短路径：最短路径是使用bfs的场景之一。
//
// 关键点1： queue中保存的是啥？队列中保存的是遍历过程中需要的东西。所以除了<i, j>，还需要知道蛇的方向。
// ps. 使用tuple可以，如果需要更多成员，可能就需要使用struct了。使用struct的好处是，每个字段的含义很明确，不需要额外使用get<0>获取。
// 
// 关键点2： visited数组如何定义。即如何判断是否重复？光靠<i, j>是不行的，还需要有方向。如何考虑到这一因素？题目的复杂度决定了需要额外考虑下。
// ps. 这里使用了三维数组来标识visited，即需要根据哪个维度来去重，就定义一维数组。如果维度更多，可能就需要使用set等数据结构了。
//
// 关键点3：最短距离，是否需要在queue中保存distance信息？如果不使用两个queue，那么就需要保存，否则就不需要保存，因为每次都是distance加一的关系。
//
// 其他点：根据题意，分类讨论蛇可以如何走的问题了。分类讨论占了大头。
//
// 快速理解题意：蛇只能往有空格的地方走（直着走，滚着走两个方向），也可以旋转走（顺时针和逆时针走），问走到最终点需要的最少步骤。
// 
// 1210. 穿过迷宫的最少移动次数 https://leetcode.cn/problems/minimum-moves-to-reach-target-with-rotations/
class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int res = 0;

        queue<tuple<int, int, bool>> q1, q2;
        vector<vector<vector<bool>>> visited(grid.size(), vector<vector<bool>>(grid[0].size(), vector<bool>(2)));
        q1.push({0, 0, true});
        visited[0][0][true] = true;
        while (!q1.empty()) {
            while (!q1.empty()) {
                auto vals = q1.front();
                q1.pop();
                int i = get<0>(vals); // tuple的使用方法，注意是全局get函数，以及模板参数是数字。
                int j = get<1>(vals);
                bool isPal = get<2>(vals);
                if (i == grid.size() - 1 && j == grid[0].size() - 2 && isPal) {
                    return res;
                }
                if (isPal && j + 2 < grid[0].size() && grid[i][j + 2] == 0 && !visited[i][j + 1][true]) {
                    visited[i][j + 1][true] = true;
                    q2.push({i, j + 1, true});
                }
                if (isPal && i + 1 < grid.size() && grid[i + 1][j] == 0 && grid[i + 1][j + 1] == 0) {
                    if (!visited[i + 1][j][true]) {
                        visited[i + 1][j][true] = true;
                        q2.push({i + 1, j, true});
                    } 
                    if (!visited[i][j][false]) {
                        visited[i][j][false] = true;
                        q2.push({i, j, false});
                    }
                }
                if (!isPal && i + 2 < grid.size() && grid[i + 2][j] == 0 && !visited[i + 1][j][false]) {
                    visited[i + 1][j][false] = true;
                    q2.push({i + 1, j, false});
                }
                if (!isPal && j + 1 < grid[0].size() && grid[i][j + 1] == 0 && grid[i + 1][j + 1] == 0) {
                    if (!visited[i][j + 1][false]) {
                        visited[i][j + 1][false] = true;
                        q2.push({i, j + 1, false});
                    } 
                    if (!visited[i][j][true]) {
                        visited[i][j][true] = true;
                        q2.push({i, j, true});
                    }
                }

            }
            swap(q1, q2);
            res++;
        }
        return -1;
    }
};

// 附赠一个dfs版本的。
// 关键点1：dfs版本的思路如何？递归遍历所有情况。势必会超时，无法处理10 * 10大小的用例。
// ps. 一个问题：顺时针和逆时针来回转换的问题如何解决？引入了fromPal。
// 
// 关键点2：剪枝1：发现当前steps已比res大，无法构成最终结果，提前返回。无法处理15 * 15大小的用例。
//
// 关键点3：剪枝2：缓存。（AC）
// 1. 如何缓存是个问题。其实和bfs的visited的维度思考方式一致，是三个维度。
// 2. 缓存的是啥呢，即map的value是啥呢？这里的一个小技巧是，value是steps。新的steps只有比缓存的steps小才可以继续进行。
class Solution {
    map<tuple<int, int, bool>, int> cache;
    void helper(vector<vector<int>>& grid, int i, int j, bool isPal, bool fromPal, int steps, int& res) {
        if (cache.find({i, j, isPal}) != cache.end() && cache[{i, j, isPal}] <= steps) {
            return;
        }
        cache[{i, j, isPal}] = steps;
        if (res <= steps) {
            return;
        }
        if (i >= grid.size() || j >= grid[0].size()) {
            return;
        }
        if (i == grid.size() - 1 && j == grid[0].size() - 2 && isPal) {
            res = min(res, steps);
            return;
        }
        if(isPal) {
            if (j + 2 < grid[0].size() && grid[i][j + 2] == 0) {
                helper(grid, i, j + 1, isPal, true, steps + 1, res);
            }
            if (i + 1 < grid.size() && grid[i + 1][j] == 0 && grid[i + 1][j + 1] == 0) {
                helper(grid, i + 1, j, isPal, true, steps + 1, res);
                if (fromPal) {
                    helper(grid, i, j, false, true, steps + 1, res);
                }
            }
        } else {
            if (i + 2 < grid.size() && grid[i + 2][j] == 0) {
                helper(grid, i + 1, j, isPal, false, steps + 1, res);
            }
            if (j + 1 < grid[0].size() && grid[i][j + 1] == 0 && grid[i+ 1][j + 1] == 0) {
                helper(grid, i, j + 1, isPal, false, steps + 1, res);
                if (!fromPal) {
                    helper(grid, i, j, true, false, steps + 1, res);
                }
            } 
        }
    }
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int res = INT_MAX;
        helper(grid, 0, 0, true, true, 0, res);
        return res == INT_MAX ? -1 : res;
    }
};

// bfs：求权重为1的单源最短路问题。与Dijkstra相比，bfs解决权重为1的问题。
//
// 关键点1：存在红蓝属性时，如何保存邻接表？多出了一个维度的数组，那个维度是color的含义。
//
// 关键点2：如何设计visited数组？需要同时根据红蓝属性去重，所以也是一个二维数组。（完全是根据如何去重来设计visited）
// ps. visited数组，决定了一个点可以访问多少次。
// 
// 关键点3：此问题为多起点问题，所以初始入队的有两个点。
//
// 关键点4： 何时入visited数组？<入队，设置visited数组>是一对操作，避免入队后，再次入队。
//
// 其他点：
// 1. pair利用结构化绑定语法，可以很方便地绑定到变量，用的太爽了。
// 2. 三维数组中，第二维是color的含义，如何取到color？多维数组中间维的索引即为值。
//
// 快速理解题意：图中每条边存在一个额外的属性，是红蓝属性，路径要求红蓝交替。求最短路径。
//
// 1129. 颜色交替的最短路径 https://leetcode.cn/problems/shortest-path-with-alternating-colors/
class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<vector<vector<int>>> edges(n, vector<vector<int>>(2, vector<int>()));
        for (auto edge : redEdges) {
            edges[edge[0]][0].push_back(edge[1]);
        }
        for (auto edge : blueEdges) {
            edges[edge[0]][1].push_back(edge[1]);
        }

        vector<vector<bool>> visited(n, vector<bool>(2, false));
        queue<pair<int, int>> q1, q2;
        q1.push({0, 0});
        q1.push({0, 1}); // 多起点
        visited[0][0] = visited[0][1] = true;

        int distance = 1;
        vector<int> res(n, INT_MAX);
        res[0] = 0;
        while (!q1.empty()) {
            while (!q1.empty()) {
                auto [currNodeId, currColor] = q1.front(); // 太方便了。结构化绑定
                q1.pop();

                for (int color = 0; color < edges[currNodeId].size(); color++) { // 这种遍历的方式更具有通用性，比如存在多种color的场景下。
                    if (currColor == color) { // 如何拿到中间值？索引即为值。
                        continue;
                    }
                    for (int child : edges[currNodeId][color]) { // 每个变量都有合适的命名，就很好理解了。
                        if (!visited[child][color]) {
                            visited[child][color] = true;
                            q2.push({child, color});
                            res[child] = min(res[child], distance);
                        }
                    }
                }
            }
            q1.swap(q2);
            distance++; 
        }
        for (int i = 0; i < res.size(); i++) {
            if (res[i] == INT_MAX) {
                res[i] = -1;
            }
        }
        return res;
        
    }
};