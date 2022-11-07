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

// 背包问题：有一个容量为 W 的背包，要用这个背包装下物品的价值最大，这些物品有两个属性：重量 w 和价值 v。
//
// 背包问题比较麻烦的点在于，需要一个二维状态dp，没办法直接推导出一维dp，那这二维是哪二维呢？
// 1. 最大物品数量;（基本固定，数组索引作为其中一维）
// 2. 最大质量；
// 3. dp含义：最大价值。（基本固定，所求即为最终结果）
//
// 定义完dp[w][i]/dp[i][w]，可以理解为如下两个方面的含义(任何一个都可以)：
// 1. 小于W的每个质量都需要使用所有物品来计算最大的价值。（第一维是w，dp[w][i]）
// 2. 每个物品都去计算小于W的所有质量下最大价值。(第一维是i，dp[i][w])
// PS. 更倾向于哪一种呢？更倾向于第二种，因为i的遍历是顺序的，即遍历i的时候只与i-1有关，w的遍历是跳跃的，即遍历w时与w-wi有关，所以将i放在第一层好些。
// 
// 有了含义，可以列表达式了。
// 列表达式的含义很明确：当前元素选或者不选：dp[i][w] = max(dp[i - 1][w], dp[i-1][w-wi] + vi);
//
// 二维到一维优化：
// 1. 优化的是谁？一般就是优化的第一维，因为只与上一行有关，所以会将i优化掉。
// 2. 什么时候可以优化？先将二维dp对应的二维循环写出来再优化，因为优化空间的同时没办法优化时间，所以没办法优化掉其中一重循环。而一维dp对应的二重循环其实是很反直觉的。
// 3. 优化之后的变更？之前顺序求解，变为从右向左求解。
// 表达式： dp[w] = Math.max(dp[w], dp[w - wi] + vi);
//
// https://github.com/CyC2018/CS-Notes/blob/master/notes/Leetcode%20%E9%A2%98%E8%A7%A3%20-%20%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92.md#0-1-%E8%83%8C%E5%8C%85
public int knapsack(int W, int[] weights, int[] values, int N) {
    int[][] dp = new int[N + 1][W + 1]; // 因为表达式中出现了 i - 1，所以需要额外多申请空间。
    for (int i = 1; i <= len(weights); i++) {
        int wi = weights[i - 1], vi = values[i - 1];
        for (int w = 1; w <= W; w++) {
            if (w >= wi) {
                dp[i][w] = Math.max(dp[i - 1][w], dp[i - 1][w-wi] + vi);
            } else {
                dp[i][w] = dp[i - 1][w]; // 因为表达式出现了w-wi
            }
        }
    }
    return dp[N][W];
}
public int knapsack(int W, int N, int[] weights, int[] values) {
    int[] dp = new int[W + 1];
    for (int i = 1; i <= N; i++) {
        int wi = weights[i - 1], vi = values[i - 1];
        for (int w = W; w >= 1; w--) {
            if (w >= wi) {
                dp[w] = Math.max(dp[w], dp[w - wi] + vi);
            }
        }
    }
    return dp[W];
}

// 背包问题应用：固定和的子序列问题
//
// 本题背包问题的两个特征：
// 1. 子序列问题：每个元素可选可不选；一般子序列问题都满足；
// 2. 存在最大容量值。背包中的w其实就是元素值，大家肯定都满足。但本题最重要的点就是，元素和有限制。（背包容量本质就是元素和）
//
// 一些小的区别：
// 1. dp的含义：是否存在。所以是个bool值。
// 2. 显示初始化：背包模板不需要初始化是因为初始化值就是0，自动省略了；bool值没办法的，否则就没办法赋值了；
// 3. 表达式：区别于最大值函数(max)，本题只需要计算||即可，更简单了。
//
// 如何优化为一维dp：
// 1. 无脑去掉第一维 + 第二重循环逆序处理。
// 
// 416. 分割等和子集 https://leetcode.cn/problems/partition-equal-subset-sum/
bool canPartition(vector<int>& nums) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    if ((totalSum & 1) == 1) {
        return false;
    }
    int sum = totalSum >> 1;
    vector<vector<bool>> dp(nums.size() + 1, vector<bool>(sum + 1));
    dp[0][0] = true; // 简单根据含义，0个元素的和为0，没有问题的。
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j <= sum; j++) {
            if (j >= nums[i]) {
                dp[i+1][j] = dp[i][j] || dp[i][j - nums[i]];
            } else {
                dp[i + 1][j] = dp[i][j];
            }
        }
    }
    return dp.back().back();
}
bool canPartition(vector<int>& nums) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    if ((totalSum & 1) == 1) {
        return false;
    }
    int sum = totalSum >> 1;
    vector<bool> dp(vector<bool>(sum + 1));
    dp[0] = true;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = sum; j >= 0; j--) {
            if (j >= nums[i]) {
                dp[j] = dp[j] || dp[j - nums[i]];
            } else {
                dp[j] = dp[j];
            }
        }
    }
    return dp.back();
}

// 背包问题：如何转化为背包问题
//
// 上一题已经总结了背包问题的两个要素：
// 1. 子序列问题；
// 2. 子序列和固定的问题。
// 但，这里有个前提，子序列和需要为正数；元素需要为正数。不遵循这两个条件的话，表达式就很难搞了。
//
// 本题是如何转化为正数子序列和问题的？解方程:
// A - B = target
// A + B = totalSum
// 可以得到A = (target + totalSum) / 2。
// 当然，需要特殊考虑(target + totalSum)是奇数或者负数的问题，可直接返回空。
//
// 494. 目标和 https://leetcode.cn/problems/target-sum/
int findTargetSumWays(vector<int>& nums, int target) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0); // 借助totalSum求子序列的和，太妙了。
    if (totalSum < abs(target) || (totalSum + target) % 2 == 1) return 0;
    int sum = (totalSum + target) / 2;

    if (nums.size() == 0) return 0;
    vector<int> dp(vector<int>(sum + 1));
    dp[0] = 1;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = sum; j >= nums[i]; j--) {
            dp[j] += dp[j - nums[i]];
        }
    }
    return dp.back();
}