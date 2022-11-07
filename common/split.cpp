// split 方法非常简单。而好多问题可以在split的时候顺带解决掉，堪称一个小杀器。
// split 方法一个强大的点：一次遍历就将问题解决掉了。

// 子串问题：不同子串不重叠时
// 主要的技巧：当 i 也需要寻找时，寻找完记得判断下是否没找到，没找到的话，是不允许进入后边的逻辑的。
//
// ps. 本题也可以使用滑动窗口法，但是其实每次j都是移动到i的位置，所以不纯粹；
// ps. 本题也可以使用动态规划方法，但是其实就比较绕，因为当前元素与前一元素有关，是有前提得，前提是，前边是以a开头的子串(currRes > 0)且满足顺序(==/>)。
// 总之，split 方法是最清晰的。
//
// 1839. 所有元音按顺序排布的最长子字符串 https://leetcode.cn/problems/longest-substring-of-all-vowels-in-order/
int longestBeautifulSubstring(string word) {
    unordered_map<char, int> towerPosMap = {
        {'a',1},
        {'e',2},
        {'i',3},
        {'o',4},
        {'u',5},
    };
    int res = 0;
    int i = 0;
    while (i < word.size()) {
        while (i < word.size() && word[i] != 'a') {
            i++;
        }
        if (i == word.size()) { // 这里记得判断是否break，模板内容。
            break;
        }
        int j = i + 1;
        while (j < word.size() && (word[j] == word[j - 1] || towerPosMap[word[j]] == towerPosMap[word[j - 1]] + 1)) {
            j++;
        }
        if (word[j - 1] == 'u') {
            res = max(res, j - i);
        }
        i = j;
    }
    return res;
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

// trim + split，再次引入一个trim算法：trim算法也是标准库中没有，需要自己实现的那种。
//
// trim：用于格式化字符串：去掉前后缀空格，去掉中间多出来的空格。
// 基本思路：i只用于寻找非空格元素，然后赋值给j，只不过赋值之前需要判断是否需要额外插入一个空格。
//
// 151. 反转字符串中的单词 https://leetcode.cn/problems/reverse-words-in-a-string/
void trim(string& s) { 
    int j= 0;
    for (int i = 0; i < s.size(); i++) { 
        if (s[i] == ' ') continue;
        if (j > 0 && s[i - 1] == ' ') {
            s[j++] = ' ';
        }
        s[j++] = s[i];
    }
    s.resize(j);
}
string reverseWords(string s) {
    trim(s);
    reverse(s.begin(), s.end());
    int i = 0;
    while (i < s.size()) { // 简单split了。
        int j = i + 1;
        while (j < s.size() && s[j] != ' ') j++;
        reverse(s.begin() + i, s.begin() + j);
        i = j + 1;
    }
    return s;
}

// 简单split题目
// 1. 1759. 统计同构子字符串的数目 https://leetcode.cn/problems/count-number-of-homogenous-substrings/