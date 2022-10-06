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

// 分阶段、分层处理：一个问题，其实自己拆分之后，是可以表示为几个不相关的步骤，分别处理即可
// 每一层一个split。
//
// 38. 外观数列 https://leetcode.cn/problems/count-and-say/
string next(const string& curr) {
    string res;
    int j = 0;
    while (j < curr.size()) {
        int k = j + 1;
        while (k < curr.size() && curr[k] == curr[j]) k++;
        res += to_string(k - j) + curr[j];
        j = k;
    }
    return res;
}
string countAndSay(int n) {
    if (n == 1) {
        return "1";
    }
    string res = "1";
    for (int i = 2; i <= n; i++) {
        res = next(res);
    }
    return res;
}