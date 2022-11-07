#include<vector>
#include<string>
// 本文件内，没有大体的分类，是最原始的dp问题，找到分类之后可拷贝出去。

// 正则表达式匹配问题，表达式为：
// 1. p[j]不是特殊字符，那么dp[i][j]取决于左上角 + 当前两元素是否相等；
// 2. p[j] 为.，dp[i][j]仅取决于左上角；
// 3. p[j] 为*，dp[i][j]取决于两个部分：
// （1）先取决于dp[i][j - 2]，即*匹配了0个，即相当于p[j - 1]和p[j]没有出现过;
// （2）再取决于dp[i-1][j]，即*匹配了1个或者多个，即可以理解为s[i]没有出现过。但是使用*能消掉s[i]，前提是p[j - 1]为点或者s[i] == p[j - 1]；
//
// dp问题思路：
// 1. 两个数组基本就是二维dp了，表现为一个横坐标一个纵坐标；（这里模式串作为纵坐标）
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

// 括号问题的dp，表达式为：
// 1. 当前是(，以当前元素为有效最后一个，肯定是0；
// 2. 当前是)，上个字符是(：前后两个字符组成一组，并且可以和dp[i - 2]合并；
// 3. 当前是)，上个字符是)：看是否可以与dp[i - 1]前边的那个字符B凑成一组，一旦可以凑成一组，那么进而还可以和B之前的进行合并。
//
// 括号问题的思路：
// 1. 当前元素作为有效括号的最后一个位置，找与前面的关系；（dp通用）
// 2. 因为是括号匹配，那么尝试找前边与自己匹配的括号：找到n-1位置和特别前边的一个位置；
// 3. 找到与谁有关之后，尝试找表达式：这里表达式的特殊点在于，找到前边匹配括号之后，还需要与前边合并结果。
// 4. 技巧：因为与i - 2有关，所以申请dp多申请两个位置，可以不需要校验边界；（dp通用）
//
// 32. 最长有效括号: https://leetcode.cn/problems/longest-valid-parentheses/
int longestValidParentheses(string s) {
    if (s.size() == 0) return 0;

    vector<int> dp(s.size() + 2); // 小技巧；
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == '(') {
            dp[i + 2] = 0;
            continue;
        }

        if (s[i - 1] == '(') {
            dp[i+ 2] = dp[i] + 2;
            continue;
        }
            
        if (i - dp[i + 1] - 1 >= 0 && s[i - dp[i + 1] - 1] == '(') {
            dp[i + 2] = dp[i + 1] + dp[i - dp[i + 1]] + 2;
            continue;
        }
            
    }
    return *max_element(dp.begin(), dp.end());
}
