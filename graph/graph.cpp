// 拓扑排序问题：有向图中排序顶点，保证父在子前。
//
// 拓扑排序的用途：
// 1. 输出有序节点；
// 2. 判断是否有环；
//
// 拓扑排序的解法：
// 1. bfs（推荐）
// 2. dfs

// 拓扑排序，输出节点序列。
// 解法1：bfs。很好理解的三步。
// 1. 不需要visited数组，因为环中的节点一定入度变为不了0.
// 2. 邻接矩阵的方向是父->子。A依赖B先完成，所以B是父节点。
//
// 优雅的算法代码，就是不需要考虑各种乱七八糟的情况，比如visited数组。
//
// 207. 课程表 https://leetcode.cn/problems/course-schedule/
// 210. 课程表 II https://leetcode.cn/problems/course-schedule-ii/
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    // 1. 构建邻接矩阵和入度表；
    vector<int> inDegrees(numCourses);
    vector<vector<int>> edges(numCourses);
    for (auto& p : prerequisites) {
        inDegrees[p[0]]++;
        edges[p[1]].push_back(p[0]);
    }

    // 2. 将入度为0的放到queue中
    queue<int> q;
    for (int i = 0; i < inDegrees.size(); i++) {
        if (inDegrees[i] == 0) {
            q.push(i);
        }
    }

    // 3. bfs遍历。并更新子节点的入度，子节点入度为0，则入队。
    vector<int> res;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        res.push_back(curr);
        for (int i = 0; i < edges[curr].size(); i++) {
            if (--inDegrees[edges[curr][i]] == 0) {
                q.push(edges[curr][i]);
            }
        }
    }
    return res.size() == numCourses ? res : vector<int>();
}

// 拓扑排序解法2：dfs
// 1. 不仅仅需要使用visited数组，还需要复杂的visited数组，需要包含「访问中」，「访问结束」两个状态。visited数组用于判断是否有环，dfs过程中访问到「访问中」状态，说明有环；
// 2. 邻接矩阵需要是反向的，因为需要优先遍历父节点，所以需要快速根据子节点找到父节点。
//
// 但是visited数组使用和校验还是很简洁的。很优雅。
//
// 210. 课程表 II https://leetcode.cn/problems/course-schedule-ii/
bool dfs(int i, vector<vector<int>>& reverseEdges, vector<int>& visited, vector<int>& res) {
    if (visited[i] == 1) return false;
    if (visited[i] == 2) return true; // 访问到2，说明有环。
    visited[i] = 2;
    for (int j = 0; j < reverseEdges[i].size(); j++) { // 找父节点。
        if (dfs(reverseEdges[i][j], reverseEdges, visited, res)) {
            return true;
        }
    }
    visited[i] = 1;
    res.push_back(i); // 遍历完父节点或者没有父节点，才遍历到自己。
    return false;
}
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> visited(numCourses); // 1代表访问过；2代表访问中（在回溯栈中）
    vector<vector<int>> reverseEdges(numCourses);
    for (auto& p : prerequisites) {
        reverseEdges[p[0]].push_back(p[1]);
    }

    vector<int> res;
    for (int i = 0; i < numCourses; i++) {
        if (dfs(i, reverseEdges, visited, res)) {
            return {};
        }
    }
    return res;
}

// 普通dfs验证是否有环：对visited数组恢复现场的条件下，访问到了visited[true]的点。即为有环。
// 理解上，从i开始的一条递归线能到头。
//
// 如下代码会超时，因为存在了大量重复计算，可以加个cache避免重复计算。（没有把标准答案放在这里，避免cache影响阅读代码逻辑。）
//
// PS. visited的使用可以好好总结总结，有的放在外边有的放在里边，有的需要恢复现场有的不需要，好乱。
//
// 207. 课程表 https://leetcode.cn/problems/course-schedule/
bool dfs(vector<vector<int>>& mat, int i,  vector<bool>& visited) {
    visited[i] = true;

    for (int j = 0; j < mat[i].size(); j++) {
        int course = mat[i][j];
        if (visited[course]) { // 访问到了之前访问过的。
            return false;
        }
        if (!dfs(mat, course, visited)) {
            return false;
        }
    }

    visited[i] = false; // 恢复现场很重要
    return true;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> mat(numCourses);
    for (auto& p : prerequisites) {
        mat[p[1]].push_back(p[0]);
    }

    vector<bool> visited(numCourses);
    for (int i = 0 ; i < numCourses; i++) {
        if (!dfs(mat, i, visited)) {
            return false;
        }
    }
    return true;
}

// 没有环的前提下，任意两点是否存在依赖关系：floyd算法
//
// floyd算法太漂亮了的说。
//
// 1462. 课程表 IV https://leetcode.cn/problems/course-schedule-iv/
vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
    vector<vector<bool>> relation(numCourses, vector<bool>(numCourses)); // 用于表示任意两点。
    for (auto& p : prerequisites) {
        relation[p[1]][p[0]] = true;
    }

    for (int k = 0; k < numCourses; k++) { // 中间节点
        for (int i = 0; i < numCourses; i++) {
            for (int j = 0; j < numCourses; j++) {
                if (relation[i][k] && relation[k][j]) {
                    relation[i][j] = true;
                }
            }
        }
    }
    vector<bool> res(queries.size());
    for (int i = 0; i < queries.size(); i++) {
        res[i] = relation[queries[i][1]][queries[i][0]];
    }
    return res;
}