// 一个题目出现之后，将其归结到我们熟悉的领域中是很重要的，然后基于此，有哪些变化，以及如何解决。

// merge升级版：高级版merge，但是其实也都还好。主要是如何优化为o(n)
//
// 1754. 构造字典序最大的合并字符串 https://leetcode.cn/problems/largest-merge-of-two-strings/
bool compare(const string& str1, const string& str2, int i, int j) {
    while (i < str1.size() && j < str2.size()) {
        if (str1[i] != str2[j]) {
            return str1[i] > str2[j];
        }
        i++, j++;
    }
    return i != str1.size();
}
string largestMerge(string word1, string word2) {
    string res;
    res.resize(word2.size() + word1.size());
    for (int i = 0, j = 0, k = 0; i < res.size(); i++) {
        if (compare(word1, word2, j, k)){
            res[i] = word1[j++];
        } else {
            res[i] = word2[k++];
        }
    }
    return res;
}