// 本文件内，没有大体的分类，是最原始的dp问题，找到分类之后可拷贝出去。

// 正则表达式匹配问题，表达式为：
// 1. p[j]不是特殊字符，那么dp[i][j]取决于左上角 + 当前两元素是否相等；
// 2. p[j] 为.，dp[i][j]仅取决于左上角；
// 3. p[j] 为*，dp[i][j]取决于两个部分：
// （1）如果*匹配了0个，即相当于p[j - 1]和p[j]没有出现过，即dp[i][j - 2];
// （2）如果*匹配了1个或者多个，即可以理解为s[i]没有出现过，即dp[i-1][j]。但是使用*能消掉s[i]，前提是p[j - 1]为点或者s[i] == p[j - 1]；
//
// dp问题思路：
// 1. 两个数组基本就是二维dp了，表现为一个横坐标一个纵坐标；
// 2. 申请的dp大小要不是是数组大小+1？可以考虑初始状态，是否需要单独考虑；
// 3. 初始一行和一列是需要特殊考虑的，可以先赋值好；
// 4. 赋值dp的过程中，还是遍历原数组的方式构造for循环即可，dp使用dp[i + 1][j + 1]，是可以保证不越界的。
//
// 10. 正则表达式匹配 https://leetcode.cn/problems/regular-expression-matching/
bool isMatch(string s, string p) {
	if (s.size() > 0 && p.size() == 0) {
		return false;
	}

	vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1));
	dp[0][0] = true;
	for (int i = 0; i < p.size(); i++) {
		if (p[i] == '*' && dp[0][i - 1]) {
			dp[0][i + 1] = true;
		} 
	}
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < p.size(); j++) {
			if (p[j] == '*') {
				dp[i + 1][j + 1] = dp[i+ 1][j - 1] || ((p[j - 1] == s[i] || p[j - 1] == '.') && dp[i][j + 1]);
			} else if (p[j] == '.') {
				dp[i + 1][j + 1] = dp[i][j];
			} else {
				dp[i + 1][j + 1] = dp[i][j] && (s[i] == p[j]);
			}
		}
	}
	return dp.back().back();
}

// dp和bfs。本题有点像bfs，但是最后其实是子问题的方式来解决的，所以认为是dp的方式。
// 此题没有表达式，但是可以使用子问题的方式去思考：(P)Q，P和Q是子问题。 
// 
// 22. 括号生成: https://leetcode.cn/problems/generate-parentheses/
vector<string> generateParenthesis(int n) {
    vector<vector<string>> dp(n + 1);
    dp[0] = {""};

    for (int i = 1; i <= n; i++) { // n组括号
        for (int j = 0; j < i; j++) { // P
            int rightSize = i - 1 - j; // Q
            for (int k = 0; k < dp[j].size(); k++) { // 遍历P
                for (int l = 0; l < dp[rightSize].size(); l++) { // 遍历Q
                    dp[i].push_back("(" + dp[j][k] + ")" + dp[rightSize][l]);
                }
            }
        }
    }
    return dp.back();
}