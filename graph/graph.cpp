// 拓扑排序问题：有向图中排序顶点，保证父在子前。
//
// 拓扑排序的用途：
// 1. 输出有序节点；
// 2. 判断是否有环；
//
// 拓扑排序的解法：
// 1. bfs（推荐）
// 2. dfs

// 图论问题：是否有环
//
// 方法1：拓扑排序，基本步骤如下：
// 1. 构建入度数组，和临界表；（2个辅助数组）
// 2. 创建一个队列，将入度为0的入队；
// 3. bfs法遍历队列。每次出队一个，并将见得入度为0的入队。
// 4. 如上是拓扑排序的基本思路。本题中是否有环，需要一个变量count，代表出队过多少元素（入队也可以，但是出队简单）。最后比较count和节点总数即可。
//
// 207. 课程表 https://leetcode.cn/problems/course-schedule/
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> inDegrees(numCourses);
    vector<vector<int>> edges(numCourses);

    for (auto& p : prerequisites) {
        inDegrees[p[0]]++;
        edges[p[1]].push_back(p[0]);
    }

    queue<int> q;
    for (int i = 0; i < inDegrees.size(); i++) {
        if (inDegrees[i] == 0) {
            q.push(i);
        }
    }

    int popCnt = 0;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        popCnt++;

        for (int i = 0; i < edges[curr].size(); i++) {
            if (--inDegrees[edges[curr][i]] == 0) {
                q.push(edges[curr][i]);
            }
        }
    }
    return popCnt == numCourses;
}

// 图论问题：是否有环
//
// 方法2：status法dfs
// 1. （一般）正常遍历图，创建临界矩阵后，在最外层，就是从0号节点开始遍历，遍历到第n个节点；
// 2. （一般）visited数组：一般一定需要考虑重复遍历问题，那么一定需要visited数组去重。
// 3. （本题）本题难点在于，如何知晓一个元素被遍历过，是正常的还是出现环了？
// 4. （本题）status数组：0:未遍历过；1: 遍历中；2: 遍历结束。使用时，也有其自己的特点，参考下面代码。
//
// 207. 课程表 https://leetcode.cn/problems/course-schedule/
bool dfs(vector<vector<int>>& edges, int i, vector<int>& status) {
    // 这里无需判断是否超出边界，因为节点来源于临界矩阵，一定不溢出
    if (status[i] == 1) return true;
    if (status[i] == 2) return false; // 第一步，校验；
    status[i] = 1;                    // 第二步，临时设置；
    for (int j = 0; j < edges[i].size(); j++) {
        if (dfs(edges, edges[i][j], status)) {
                return true;
            }
        }
    status[i] = 2;                   // 第三步，最终设置
    return false;
}

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> edges(numCourses);
    for (int i = 0; i < prerequisites.size(); i++) {
        edges[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }
    vector<int> status(numCourses); // 0 代表未访问过，1代表本次访问，2代表之前访问过
    for (int i = 0; i < numCourses; i++) {
        if (dfs(edges, i, status)) {
            return false;
        }
    }
    return true;
}

// 图论问题：按依赖关系输出序列
//
// 方法1：dfs
// 1. (一般)如果没有说明一定没有环，那么就需要考虑环，那么就可以使用环的模板来做题。
// 2. (本题)关于dfs的遍历顺序，脑中想象这么一副图，dfs遍历的时候，其实是从随机一个点开始向下的，对于本题，有顺序的前提下，就需要特别考虑下了。
// 3. (本题)如何解决：反向遍历：不论你从哪里开始，从后向前入结果（从叶子节点到根节点）；最后reverse下即可。
//
// 210. 课程表 II https://leetcode.cn/problems/course-schedule-ii/
bool dfs(vector<vector<int>>& edges, int i, vector<int>& status, vector<int>& res) {
    // 这里无需判断是否超出边界，因为节点来源于临界矩阵，一定不溢出
    if (status[i] == 1) return true;
    if (status[i] == 2) return false;

    status[i] = 1;                  
    for (int j = 0; j < edges[i].size(); j++) {
        if (dfs(edges, edges[i][j], status, res)) {
            return true;
        }
    }
    status[i] = 2;                 
    res.push_back(i); // 最后遍历到的最先入结果
    return false;
    }
    
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> status(numCourses);
    vector<vector<int>> edges(numCourses);

    for (auto& p : prerequisites) {
        edges[p[1]].push_back(p[0]);
    }

    vector<int> res;
    for (int i = 0; i < numCourses; i++) {
        if (dfs(edges, i, status, res)) {
            return {};
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

// 图论问题：按依赖关系输出序列
//
// 方法2：拓扑排序
// 1. (一般)拓扑排序就是用来解决这种问题的；
// 2. (本题)本题的特殊性，在于不一定存在结果，所以本质也是使用的判断是否有环的模板，在最后判断下就可以了，其余的都一样
//
// 拓扑排序和普通bfs的区别：前者不需要visited数组。
//
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

// 图论问题3：任意两个节点是否存在依赖关系
//
// 解法1：全部依赖关系的问题：floyd算法（floyd算法太漂亮了的说。）
//
// 解法2： 拓扑排序能解决这个问题吗？当然可以，不过真的是不优雅，思路如下：
// 1. (一般) 就是上述拓扑排序的模板。根据这个模板，可以方便拿到当前节点的子节点有谁；
// 2. (本题) 遍历到当前节点，其实可以得到的是与当前节点依赖的所有祖先节点，所以在将子节点加入到队列中去之前，先将当前节点以及当前节点的所有祖先节点加到子节点的祖先集合中去。
//    这样的到的依赖关系依然只是单向的，所以最后查询的时候，还需要两边都查下。
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

// 图论问题4：深拷贝图
//
// 题目条件：
// 1. 一般情况给出的是节点个数 + 依赖关系，此时的图不一定连通，可能有环
// 2. 还有一种，和树类似，只给出Node*，代表一个图，此时图一定是连通的，但是可能有环。（特例就是自己指向自己）
// 3. 二者的关系是啥？Node*简化了获取孩子节点的方式，不然还需要自己构建临界表。
// 
// 图的遍历方式暂时有几种：
// 1. 普通dfs：需要visited数组；
// 2. 普通bfs：需要visited数组；
// 3. 拓扑排序：不需要visited数组。
//
// visited数组的两个含义：
// 1. 代表是否访问过 bool 类型；（不需要返回值）
// 2. 代表cache，缓存结果。（需要返回值）
//
// 本题难点就在于 visited 数组：一般的visited数组，都是直接放在函数开头和结尾就好了。但是此题不是，此题需要放在开头和递归之前。
//
// 133. 克隆图 https://leetcode.cn/problems/clone-graph/
unordered_map<Node*, Node*> cache; // 凡是使用hashmap的地方，其实都可以考虑使用数组优化，如果节点值各不相同，那么就可以优化为数组。
    
Node* cloneGraph(Node* node) {
    if (node == nullptr) return nullptr;
    if (cache.find(node) != cache.end()) return cache[node];

    Node* res = new Node(node->val);
    cache[node]= res; // 竟然需要放在这里，更深层次原因待探究。
    for (int i = 0; i < node->neighbors.size(); i++) {
        res->neighbors.push_back(cloneGraph(node->neighbors[i]));
    }

    return res;
}