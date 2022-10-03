// 模拟题目描述来得到最解，不去找什么复杂规律

// 6. Z 字形变换
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