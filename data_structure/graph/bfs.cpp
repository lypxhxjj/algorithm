// 总结一些核心问题：
// 1. bfs的distance是从0开始还是从1开始？
// 答：一般会检查start==end时，返回0；所以正常bfs逻辑是从1开始的。注意distance代表的是**已经与正在处理的**边的个数，不要从节点个数上理解。
//
// 2. dis的作用以及初始化
// 答：dis的作用是「已处理完以及正在处理的」边的个数。所以，初始从1开始。0的情况应该是在函数最开始进行校验的。
//
// 3. bfs中的queue可以切换到其他数据结构吗？
// 答：可以。使用任何一个数据结构都可以，包括栈。因为入队之后其实对出队没啥顺序的概念，所以不一定使用队列的初始化方式。
// （1）建议使用queue。因为这样语义更清晰；
// （2）以下情况建议使用vector。双向bfs中，处理q1中的数据依赖q3，此时有遍历q3的需求，但queue由于没有迭代器的概念，无法遍历，所以需要使用deque与vector，性能上讲，肯定vector更好了。
// （3）什么时候不能使用其他数据结构？目前一般使用两个queue + swap的方式，一旦使用一个queue，那么就必须使用queue了，因为就是要先进先出。
//
// 4. visited数组的使用，主要是几个点：
// （1）数据结构的选择。可选项是bool[], vector<bool>, unordered_set。优先使用bool[]，当然由于只申请一次，使用vector<bool>的成本也不高。但是使用bool[]一定记得初始化，否则会报奇怪的错误；（但是使用unordered_set还是慢）
// （2）什么时候进入visited数组？**进入visited和进入queue是一对操作**，这样可以避免一个元素进入queue好多次。 
// （3）多维visited数组的选择（1210）。其实visited数组就是去重的作用，所以可以先想想什么场景下需要去重，对应的visited数组就什么样子，所以可能存在多维的情况的。
// （4）visited数组只需要保存进入queue的成员即可。2059题中，visited数组的一个小技巧：没有必要将所有的值都保存在visited中，**而是只保存需要进入queue的就可以了**。
//
// 5. 什么时候判断是否到终点了？
// 答：最内层while循环内的流程如下：
// （1）根据curr找到下一个val；（不同题不一样）
// （2）判断val是否满足条件，以及是否访问过；（两个if，二三步的顺序就看最终值是否满足条件，所以顺序不一定，如2059题）
// （3）判断是否到达终点；（双向bfs比较麻烦，需要遍历q3，其余比较简单）
// （4）入队以及设置visited。
// 结论：<判断是否到达终点，入队，设置visited>是一组操作，密不可分的。这组操作在while外和外内分配有一套，没有办法合并，也是没办法的事。
// 
// 6. queue中保存的是啥？
// 答：队列中保存的是遍历过程中需要的东西。所以除了<i, j>，还需要知道蛇的方向。
// ps. 使用tuple可以，如果需要更多成员，可能就需要使用struct了。使用struct的好处是，每个字段的含义很明确，不需要额外使用get<0>获取。（貌似可以使用tuple与结构化绑定相关联）
//
// 7.queue中要不要保存dis信息？
// 答：双queue的方式不需要，单queue的方式就需要。

// bfs：求最短路径。
//
// 关键点1：最基础使用bfs的场景。没有其他技巧了。
//
// 关键点2：visited数组的使用，本来使用的是unordered_set，因为不一定数据会到达多少。但是其实超出这部分的数据都不要了，所以只需要一个1000的数组即可。
//
// 2059. 转化数字的最小运算数 https://leetcode.cn/problems/minimum-operations-to-convert-number/
class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        if (start == goal) {
            return 0;
        }

        auto op1 = [](int a, int b) {return a + b;};
        auto op2 = [](int a, int b) {return a - b;};
        auto op3 = [](int a, int b) {return a ^ b;};
        vector<function<int(int, int)>> ops = {op1, op2, op3}; // 这个方法可以借鉴。

        int res = 1;
        bool visited[1001] = {false};
        queue<int> q1, q2;
        q1.push(start);
        visited[start] = true;

        while (!q1.empty()) {
            while (!q1.empty()) {
                int curr = q1.front();
                q1.pop();

                for (int i = 0; i < nums.size(); i++){
                    for (auto op : ops) { // 相同操作可以弄到for循环。
                        int val = op(curr, nums[i]);
                        if (val == goal) {
                            return res;
                        }
                        if (val >= 0 && val <= 1000 && !visited[val]) {
                            visited[val] = true;
                            q2.push(val);
                        }
                    }
                }
            }
            q1.swap(q2);
            res++;
        }
        return -1;
    }
};

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
// 快速理解题意：蛇只能往有空格的地方走（直着走，滚着走两个方向），也可以旋转走（顺时针和逆时针走），问走到最终点需要的最少步骤。
// 
// 1210. 穿过迷宫的最少移动次数 https://leetcode.cn/problems/minimum-moves-to-reach-target-with-rotations/
class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int res = 0;

        queue<tuple<int, int, bool>> q1, q2; // 理解下这里需要保存啥。
        vector<vector<vector<bool>>> visited(grid.size(), vector<vector<bool>>(grid[0].size(), vector<bool>(2))); // 理解下visited为何这么定义。
        q1.push({0, 0, true});
        visited[0][0][true] = true;
        while (!q1.empty()) {
            while (!q1.empty()) {
                auto [i, j, isPal] = q1.front(); // 结构化绑定，即可使用tuple代替struct。
                q1.pop();
                if (i == grid.size() - 1 && j == grid[0].size() - 2 && isPal) { // 这里比较特殊，出队的时候才校验是否符合条件，是否可优化为入队的时候校验？这里会影响dis的初始化。
                    return res;
                }
                 auto canForward = [&grid, &visited](int i, int j, bool isPal) { // 值得学习：分类讨论太多，抽象
                    if (i >= grid.size() || j >= grid[0].size() || grid[i][j] == 1) return false;
                    if (visited[i][j][isPal]) return false;

                    int nexti = i, nextj = j;
                    if (isPal) nextj++;
                    else nexti++;
                    return nexti < grid.size() && nextj < grid[0].size() && grid[nexti][nextj] == 0;
                };
                auto canRotate = [&grid, &visited](int i, int j, bool isPal) { // 这个坑了，旋转只有四个格都为0时才可以旋转，所以分开处理。
                    if (i + 1 >= grid.size() || j + 1 >= grid[0].size() || grid[i+ 1][j + 1] == 1 || grid[i + 1][j] == 1 || grid[i][j + 1] == 1) return false;
                    return visited[i][j][!isPal] == false;
                };
                if (canRotate(i, j, isPal)) {
                    q2.push({i, j, !isPal});
                    visited[i][j][!isPal] = true;
                }
                if (canForward(i + 1, j, isPal)) {
                    q2.push({i + 1, j, isPal});
                    visited[i + 1][j][isPal] = true;
                }
                if (canForward(i, j + 1, isPal)) {
                    q2.push({i, j + 1, isPal});
                    visited[i][j + 1][isPal] = true;
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

        vector<vector<bool>> visited(n, vector<bool>(2, false)); // 注意visited含义。
        queue<pair<int, int>> q1, q2; // 总感觉queue的结构和visited的结构差不太多的样子。
        q1.push({0, 0});
        q1.push({0, 1});            // 多起点遍历
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