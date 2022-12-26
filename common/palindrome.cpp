// 回文数问题：中心扩展法
//
// 涉及到回文数问题，就没有办法不去分类讨论: 以i为中心，以i和i+1为中心。
//
// 回文数的经典解法：中心扩展法。中心扩展法是一个单独的函数，返回值代表了以i和j为中心向两边扩展了多少个。
// ps. 虽然函数代码很丑，但是确实是核心函数。（未来是否可以优化下？）
//
// 5. 最长回文子串 https://leetcode.cn/problems/longest-palindromic-substring/
int longPal(const string& s, int i, int j) {
    int k = 0;
    while (i - k >= 0 && j + k < s.size()) {
        if (s[i - k] == s[j + k]) {
            k++;
        } else {
            break;
        }
    }
    return k - 1;  // 返回值代表向两边扩展了多少。k 从 0 开始，因为s[i]可能不等于s[j]，k会一直走到二者不相等的时候，所以需要减1.
}
string longestPalindrome(string s) {
    string res;
    int maxLen = 0;
    for (int i = 0; i < s.size(); i++) {
        int k = longPal(s, i, i);
        if (k * 2 + 1 > maxLen) {
            maxLen = k * 2 + 1;
            res = s.substr(i - k, maxLen);
        }
    }
    for (int i = 0; i < (int)s.size() - 1; i++) {
        int k = longPal(s, i, i + 1);
        if (k * 2 + 2 > maxLen) {
            maxLen = k * 2 + 2;
            res = s.substr(i - k, maxLen);
        }
    }
    return res;
}

// 回文数字问题：思路挺妙的。
//
// 使用另外的y保存x的后半部分。
//
// 9. 回文数 https://leetcode.cn/problems/palindrome-number/
bool isPalindrome(int x) {
    if (x == 0) return true;
    if (x % 10 == 0) return false;
    if (x < 0) return false; // 特殊情况考虑清楚，否则会出现问题。虽然这种是最基础的解题步骤。

    int y = 0;
    while (x > y) { // y保存x的后半部分。
        y = y * 10 + x % 10;
        x /= 10;
    }
    return x == y || x == y/10;
}