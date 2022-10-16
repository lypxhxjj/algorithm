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

// 子序列问题。特殊点：子序列生成的中间状态有限，只有三种：只有0，有01，有012
// 那可以分成三个状态，分别保存。后面的状态依赖前边的状态。
// 1. seq0 += seq0 + 1; 加等于代表当前可加可不加；为啥加了1，因为seq0之前的序列中不包含空数组；
// 2. seq1 += seq1 + seq0;
// 3. seq2 += seq1 + seq2;
// 关于mod的计算：
// 1. 注意是1e9而不是10e9；
// 2. INT_MAX而言最多两个mod，一旦超过2个，就会溢出，所以第二三个表达式需要在计算中间取模操作。
// 
// 1955. 统计特殊子序列的数目 https://leetcode.cn/problems/count-number-of-special-subsequences/
int countSpecialSubsequences(vector<int>& nums) {
    const int Mod = 1e9 + 7;
    int seq0 = 0, seq1 = 0, seq2 = 0;
    for (int num : nums) {
        if (num == 0) {
            seq0 += seq0 + 1; // 为啥加1，因为seq0之前的序列中不包含空数组；
            seq0 %= Mod;
        } else if (num == 1) {
            seq1 = seq1 * 2 % Mod + seq0;
            seq1 %= Mod;
        } else {
            seq2 = seq1 + seq2 * 2 % Mod;
            seq2 %= Mod;
        }
    }
    return seq2;
}

// 子序列问题。特殊点：结果中存在两个状态，以奇数结尾，以偶数结尾，两个状态可以相互转换
// 每个状态可以保存当前的最优结果，下个状态仅依赖当前状态。这种就是典型的dp问题了。
// 不好想的点是：状态使用多个变量来保存。
//
// 1911. 最大子序列交替和 https://leetcode.cn/problems/maximum-alternating-subsequence-sum/
long long maxAlternatingSum(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    long long oddSum = 0; // 最后一个是奇数索引
    long long evenSum = nums[0]; // 最后一个是偶数索引；
    for (int i = 0; i < nums.size(); i++) {
        oddSum = max(oddSum, evenSum - nums[i]);
        evenSum = max(evenSum, oddSum + nums[i]);
    }
    return evenSum;
}