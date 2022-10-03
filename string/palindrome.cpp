
// 任意子串是否为回文 o(n ^ 2)
// 5. 最长回文子串
vector<vector<bool>> isPal(const string& s) {
    if (s.size() == 0) return {};

    vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false)); // 按s的大小申请dp，所以s.size() == 0需要单独考虑。
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; i - j >= 0 && i + j < s.size(); j++) { // 中心扩展法将时间复杂度降低到o(n^2)，注意for循环结束条件
            if (s[i - j] == s[i + j]) {
                dp[i - j][i + j] = true;
            } else {
                break;
            }
        }
    }
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; i - j >= 0 && i + j + 1 < s.size(); j++) {
            if (s[i - j] == s[i + j + 1]) {     // 回文串问题，必须同时考虑两种情况。
                dp[i - j][i + j + 1] = true;
            } else {
                break;
            }
        }
    }
    return dp;
}

// 判断一个整数是否回文，不使用字符串的一种方式：
// 比较坑的点：
// 1. 需要单独考虑后置0；
// 2. while条件是x > right，那么循环结束一定有x <= right。
//
// 9.回文数： https://leetcode.cn/problems/palindrome-number/
bool isPalindrome(int x) {
    if (x < 0) return false;
    if (x < 10) return true;
    if (x % 10 == 0) return false;

    int right = 0;
    while (x > right) {
        right = right * 10 + x % 10;
        x /= 10;
    }
    return right == x || right / 10 == x;
}