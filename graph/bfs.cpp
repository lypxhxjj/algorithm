// bfs问题基本可以使用两个queue解决，如果不分层处理，甚至可以优化为一个queue。但是考虑使用queue会使得代码行数陡增，
// 所以可以将queue使用vector代替，但是基本思路是不变的。


// bfs最基本的套路，只不过这里使用vector代替queue了。
// 为啥需要两个queue？因为最后结果只关心最后一层的东西。
// 和dfs相比的效率问题：肯定比dfs要慢，因为bfs需要各种拷贝，dfs是直接在结果上进行各种处理的。
//
// 17. 电话号码的字母组合: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
vector<string> letterCombinations(string digits) {
    if (digits.size() == 0) {
        return {};
    }
    vector<string> q1,q2;
    q1.push_back("");
    for (int i = 0; i < digits.size(); i++) {
        string str = strs[digits[i] - '2'];
        for (int j = 0; j < q1.size(); j++) {
            for (int k = 0; k < str.size(); k++) {
                q2.push_back(q1[j] + string(1, str[k]));
            }
        }
        q1.swap(q2);
        q2.resize(0);
    }
    return q1;
}