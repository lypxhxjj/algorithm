// 并查集解决问题：判断是否有环。(重复union即有环)
//
// 并查集如何处理矩形问题？
// 1. 路径压缩（背下来，错了好几次），grid[i][j] -> i * colNum + j；
// 2. 矩形中如何找临界边？如下代码中的两个if。即只处理连通的两个边。
//
// 并查集模型可以做哪些支持？
// 1. union返回bool代表是否真正发生了合并，本题用于判断是否有环的关键逻辑。 
//
// 1559. 二维网格图中探测环 https://leetcode.cn/problems/detect-cycles-in-2d-grid/
class UnionFind {
    vector<int> parents;
    vector<int> heights;
public:
    UnionFind(int num) {
        parents.resize(num);
        heights.resize(num);
        for (int i = 0; i < num; i++) {
            parents[i] = i;
            heights[i] = 1;
        }
    }
    int Find(int i) {
        while (i != parents[i]) {
            i = parents[i];
        }
        return i;
    }
    bool Union(int i, int j) {
        int iparent = Find(i), jparent = Find(j);
        if (iparent == jparent) {
            return false;
        }
        if (heights[iparent] > heights[jparent]) {
            parents[jparent] = iparent;
        } else if (heights[iparent] < heights[jparent]) {
            parents[iparent] = jparent;
        } else {
            parents[jparent] = iparent;
            heights[iparent]++;
        }
        return true;
    }
};
class Solution {
public:
    bool containsCycle(vector<vector<char>>& grid) {
        UnionFind uf(grid[0].size() * grid.size());
        int n = grid[0].size();
        for (int i = 0; i < grid.size(); i++) { // 自成邻接矩阵，只不过连通边需要额外计算下。
            for (int j = 0; j < grid[0].size(); j++) {
                if (i > 0 && grid[i-1][j] == grid[i][j]) { // 连通边
                    if (!uf.Union((i - 1) * n + j, i * n + j)) {
                        return true;
                    }
                }
                if (j > 0 && grid[i][j - 1] == grid[i][j]) { // 连通边
                    if (!uf.Union(i * n + j - 1, i * n + j)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

// 并查集处理线段合并
//
// 这里的并查集和普通并查集差异较大；
// 1. （重要）UnionFind的构造函数参数固定。这个十分明确，参数即是parents的大小，和使用者无关；
// 2. 使用方需要parents多大？并查集中是按索引连通，而外部使用是按值，所以最大值即为parents的最大索引（parents个数还需要额外加1），外部值的范围是[0, max + 1]，0不使用，max+1是num + 1所需要的；
// 3. （重要）UnionFind允许初始化没有线段。这里0不使用，所以所有点的parents指向0；啥时候需要创建，使用insertNew创建一个点；此时一般也需要添加一个hasParents方法。
// 4. Union中连通的是一个线段，而线段的合并暂时根据的是向小的合并的方法；
// 5. （重要）parent的含义，仅代表一个线段，不代表任何其他，需要其他东西，自己定义，比如本题中需要线段的长度信息。
//
// 1562. 查找大小为 M 的最新分组 https://leetcode.cn/problems/find-latest-group-of-size-m/
class UnionFind {
    vector<int> parents;
    vector<int> sz;
public:
    UnionFind(int numsLen) { // 这里是元素最大值，不再是索引概念；
        parents.resize(numsLen );
        sz.resize(numsLen);
    }
    int Find(int i) {
        while (i != parents[i]) i = parents[i];
        return i;
    }
    void insertNew(int i) {
        parents[i] = i;
        sz[i] = 1;
    }
    void Union(int i, int j) {
        int iParent = Find(i), jParent = Find(j);
        if (iParent == jParent) {
            return;
        }
        if (iParent < jParent) {
            parents[jParent] = iParent;
            sz[iParent] += sz[jParent];
        } else {
            parents[iParent] = jParent;
            sz[jParent] += sz[iParent];
        }
    }
    int size(int i) {
        return sz[Find(i)];
    }
    bool hasParent(int i) {
        return parents[i] != 0;
    }
};
class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        UnionFind uf(arr.size() + 2);
        int res = -1;
        int mCnt = 0;
        for (int i = 0; i < arr.size(); i++) {
            int num = arr[i];
            uf.insertNew(num);
            if (uf.hasParent(num - 1)) {
                mCnt -= uf.size(num - 1) == m ? 1 : 0;
                uf.Union(num, num - 1);
            }
            if (uf.hasParent(num + 1)) {
                mCnt -= uf.size(num + 1) == m ? 1 : 0;
                uf.Union(num, num + 1);
            }
            mCnt += uf.size(num) == m ? 1 : 0;
            if (mCnt > 0) {
                res = i + 1;
            }
        }
        return res;
    }
};