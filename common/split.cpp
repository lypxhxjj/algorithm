// split 方法非常简单。而好多问题可以在split的时候顺带解决掉，堪称一个小杀器。
// split 方法一个强大的点：一次遍历就将问题解决掉了。

// split变形1：split考虑分隔符在边界：在边界时产生空字符串
//
// 要点：需要考虑在前和在后，我们默认的逻辑是完全不考虑的，所以分别考虑即可。
//
// 本题主干：split + count。
//
// 2315. 统计星号 https://leetcode.cn/problems/count-asterisks/
class Solution {
    vector<string> split(const string& s) {
        if (s.size() == 0) return {};

        int i = 0;
        vector<string> res;
        while (i < s.size()) {
            int j = i;                          // 要点1：j = i
            while (j < s.size() && s[j] != '|') j++;
            res.push_back(s.substr(i, j - i));

            i = j + 1;
        }
        if (s.back() == '|') res.push_back(""); // 要点2：单独考虑最后一个字符。
        return res;
    }
public:
    int countAsterisks(string s) {
        vector<string> parts = split(s);

        int res = 0;
        for (int i = 0; i < parts.size(); i+= 2) {
            res += count(parts[i].begin(), parts[i].end(), '*');
        }
        return res;
    }
};

// split变形2：i也需要寻找时，记得判断i是否到头，即i的寻找会导致4行代码出来。
//
// split应用：不重叠子串问题。
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

// split应用2：分阶段，分层处理
//
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

// split应用：分隔符可以是多个空格
//
// 最初的实现是，先trim -> split -> join；
// 可被优化为：split -> join。
//
// 151. 反转字符串中的单词 https://leetcode.cn/problems/reverse-words-in-a-string/
class Solution {
    vector<string> split(const string& s) {
        if (s.size() == 0) {
            return {};
        }

        vector<string> res;
        int i = 0;
        while (i < s.size()) {
            while (i < s.size() && s[i] == ' ') i++;
            if (i == s.size()) break;

            int j = i + 1;
            while (j < s.size() && s[j] != ' ') j++;

            res.push_back(s.substr(i, j - i));
            i = j + 1;
        }
        return res;
    }

    string join(vector<string>& parts, char ch) {
        string res;
        if (parts.size() == 0) {
            return res;
        }
        for (const auto& part : parts) {
            res += part + " ";
        }
        res.resize(res.size() - 1);
        return res;
    }
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        auto parts = split(s);
        for (string& part : parts) {
            reverse(part.begin(), part.end());
        }
        return join(parts, ' ');
    }
};

// 简单split题目
// 1. 1759. 统计同构子字符串的数目 https://leetcode.cn/problems/count-number-of-homogenous-substrings/