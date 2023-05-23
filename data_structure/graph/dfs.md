一旦涉及到图内路径的问题，基本需要使用dfs了，因为dfs可以遍历到所有路径。

题目给出条件：无向图，意味着邻接表需要保存两次：
```
        vector<vector<int>> mat(n + 1, vector<int>());
        for (auto edge : edges) {
            mat[edge[0]].push_back(edge[1]);
            mat[edge[1]].push_back(edge[0]);
        }
```

dfs中，如下两种场景需要用到visited数组用于去重：
1. 有向图，但可能有环；
2. 无向图。因为无向图相连的节点自成一个环。

visited数组怎么使用呢？对于每层dfs只遍历一个节点来说：
1. 何时设置为true：dfs进入之后需要先进行边界判断，之后即设置visited为true；
2. 何时设置为false：当前dfs结束之前，将visited设置为false，恢复现场。
3. 何时查询：递归进入下次dfs前，校验visited；
即：
```
    vector<bool> visited(n + 1, false);

    void dfs(vector<vector<int>>& mat, xxx) {
        if (checkReturn()) return;

        visited[i] = true;
        for (int j : mat[i]) {
            if (visited[j]) continue;
            dfs(mat, j, visited, t - 1, target, res, currRate /total);
        }
        visited[i] = false;
    }
```

如下题目：
```
1377. T 秒后青蛙的位置

给你一棵由 n 个顶点组成的无向树，顶点编号从 1 到 n。青蛙从 顶点 1 开始起跳。规则如下：

在一秒内，青蛙从它所在的当前顶点跳到另一个 未访问 过的顶点（如果它们直接相连）。
青蛙无法跳回已经访问过的顶点。
如果青蛙可以跳到多个不同顶点，那么它跳到其中任意一个顶点上的机率都相同。
如果青蛙不能跳到任何未访问过的顶点上，那么它每次跳跃都会停留在原地。
无向树的边用数组 edges 描述，其中 edges[i] = [fromi, toi] 意味着存在一条直接连通 fromi 和 toi 两个顶点的边。

返回青蛙在 t 秒后位于目标顶点 target 上的概率。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/frog-position-after-t-seconds
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
```

```
class Solution {
    bool dfs(vector<vector<int>>& mat, int i, vector<bool>& visited, int t, int target, double& res) {
        int childNum = i == 1 ? mat[i].size() : mat[i].size() - 1;
        if ((childNum == 0 || t == 0) && target == i) {
            res = currRate;
        }
        
        if (target == i) {
            return true;
        }
        if (childNum == 0 || t <= 0) {
            return false;
        }

        visited[i] = true;
        for (int j : mat[i]) {
            if (visited[j]) continue;
            if (dfs(mat, j, visited, t - 1, target, res, currRate /childNum)) {
                return true;
            }
        }
        visited[i] = false;
        return false;
    }
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        vector<vector<int>> mat(n + 1, vector<int>());
        for (auto edge : edges) {
            mat[edge[0]].push_back(edge[1]);
            mat[edge[1]].push_back(edge[0]);
        }
        vector<bool> visited(n + 1, false);
        double res = 0;
        dfs(mat, 1, visited, t, target, res, 1.0);
        return res;
    }
};
```

说明下这个题进入的两个误区解法：
1. 第t步遍历到target节点总次数 / 第t步遍历到的所有节点总次数。这种解法不正确，因为有些分支可能到中间就停掉了，到达不了第t步。

比如：第一个示例中（[[1,2],[1,3],[1,7],[2,4],[2,6],[3,5]]）跳两步，可能停在4,7,5三个位置，但是4和7的概率是不一样的，分别是1/6, 1/3。因为跳转到7之后，就无法继续跳了，就停在了7的位置。

为了解决这个问题，遍历到每个节点，都需要知晓遍历到当前节点的概率，即将currRate作为dfs的一个参数。遍历到最终节点的时候，将currRate加到res中。

2. 使用携带概率（currRate）的方式dfs，遍历到t为0的时候，将currRate加到res中。这种解法也不对，因为t可能很大，遍历不到0，就已经无法移动了，

所以此时终止条件不仅仅是t == 0，还可能是无下一个节点可遍历的时候。

本题「无向树」条件的用法：区别于无向图，无向树的遍历是从上到下的，每个节点除了与它的孩子相连，只与一个父节点相连，所以可以快速得到接下来还有多少次dfs需要调用，即孩子的个数。
```
        int childNum = i == 1 ? mat[i].size() : mat[i].size() - 1; // 这里特殊考虑根节点，根节点没有父节点，少了一个相连的节点。
```
无向树的另外一个特性：一旦一个节点被遍历过，那么就不会再次被遍历到。利用这个性质，我们可以得出：
1. 遍历到target节点的时候，如果是满足条件的，则直接得到返回值，不需要通过概率加法计算。
2. 遍历到target节点的时候，无论是否满足条件，都可以直接剪枝了：
```
        if (target == i) {
            return true;
        }
```
这里引入了返回值剪枝。不使用返回值直接return，只是剪掉了target节点后面的子树；使用返回值剪枝，则减掉了后续需要遍历的所有路径，比如target的兄弟节点。