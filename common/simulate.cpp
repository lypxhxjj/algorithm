// 模拟题目描述来得到最解，不去找什么复杂规律

// 奇怪的方式访问数组。用到的小技巧：
// 1. 辅助数组；
// 2. 方向变量；
// 3. 主干编程法；
//
// 6. Z 字形变换 https://leetcode.cn/problems/zigzag-conversion/
string join(vector<string>& arr) {
    string res;
    for (string& str : arr) {
        res += str;
    }
    return res;
}
string convert(string s, int numRows) {
    if (s.size() < 2 || numRows == 1) return s;
        
    vector<string> tmpArr(numRows); // 辅助数组和方向，能想到使用这两个变量很关键。
    int downFlag = true;
    for (int i = 0, j = 0; i < s.size(); i++) {
        tmpArr[j].push_back(s[i]); // 主逻辑。

        if (downFlag) j++; // 方向移动
        else j--;

        if (j == tmpArr.size()) { // 方向调整。
            j = tmpArr.size() - 2;
            downFlag = false;
        }
        if (j == -1) {
            j = 1;
            downFlag = true;
        }
    }
    return join(tmpArr);
}

// 需要删除，但是真的要删除操作吗，可不可以用赋值代替删除？
// 本题解法比较有意思的点是：找到逆序对后，可以得出如下结论:
// a b c d，bc是逆序对，那么b>a, b>c。如果删，那么删b还是c？对于a来说，要比a大的，对于d来说，要比d小的：可以总结为：比a大的尽量小的。
// 所以，如果c > a，那么取c，否则取d。
// 这里的删除，可以简单通过赋值实现。假如要删的是c，那么就把b的值赋值给c。
//
// 1909. 删除一个元素使数组严格递增: https://leetcode.cn/problems/remove-one-element-to-make-the-array-strictly-increasing/
bool canBeIncreasing(vector<int>& nums) {
    int pcnt = 0; // 逆序对数量
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i - 1] < nums[i]) {
            continue;
        }
        if (++pcnt > 1) {
            return false;
        }
        if (i > 1 && nums[i - 2] >= nums[i] ) {
            nums[i] = nums[i - 1];
        }
    }
    return true;
}

// 基于时间的模拟，
// 时间流逝体现在两个方面：在执行任务和空转。所以time字段需要在两个场景更新，但不管哪个场景，时间是必须更新的；
// 任务添加：每次执行任务之前，或者循环的最开始，都是先将任务加进来。
// 
// 1834. 单线程 CPU https://leetcode.cn/problems/single-threaded-cpu/
vector<int> getOrder(vector<vector<int>>& tasks) {
    for (int i = 0; i < tasks.size(); i++) { // 有需要就将数组的索引append到tasks中
        tasks[i].push_back(i);
    }
    sort(tasks.begin(), tasks.end());
    auto cmp = [](const auto& p1, const auto& p2) { // 执行任务的顺序
        if (p1[1] != p2[1]) {
            return p1[1] > p2[1];
        }
        return p1[2] > p2[2];
    };
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp); // 就绪队列

    vector<int> res;
    long long time = 1; // 时间流逝。
    int i = 0;
    while (i < tasks.size() || !pq.empty()) { // 不知道多少次循环。
        while (i < tasks.size() && tasks[i][0] <= time) { // 每次开始，优先进入就绪队列。
            pq.push(tasks[i++]);
        }
        if (pq.empty()) {
            time = tasks[i][0]; // 时间字段是都需要更新的。
        } else {
            auto task = pq.top();
            pq.pop();
            res.push_back(task[2]);
            time += task[1];
        }
    }
    return res;
}
