// 如何实现一个较复杂的trim。
//
// 1. unique与resize/erase搭配使用
//
// ps. 本题有优化解法，参考split章节。
//
// 151. 反转字符串中的单词 https://leetcode.cn/problems/reverse-words-in-a-string/
void trim(string& s) {
    auto end = unique(s.begin(), s.end(), [](char ch1, char ch2) { // unique的返回值是新的结尾，但不会改变s的大小。
        return ch1 == ch2 && ch1 == ' ';
    });
    s.resize(end - s.begin()); // 所以需要resize或者erase。
    int i = 0, j = s.size();
    if (s.size() > 0 && s[0] == ' ') { // 考虑开头
        i++;
    }
    if (s.size() > 1 && s.back() == ' ') { // 考虑结尾
        j--;
    }
    s = s.substr(i, j - i); // 一次substr。
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