// 滑动窗口问题，窗口内的数据如何保存与使用。
// 
// 窗口内怎么保存状态的：这里使用的是 hashmap 保存，diff 变量来使用。
//
// diff的含义是：A和B不同词频的个数。由于固定窗口，所以一旦降为0，那么说明所有字符就一样了。
// 解释：为啥可以兼容不包含的字符呢？diff的变化有两个时间点: cnt==0，cnt == 1。
// 如果diff变为0，其等价含义是，出现了所有预定字符 + 次数都是一致的，而唯有这一种情况才能让diff为0；
// 假如预定字符还有，引入了新的字符，那么diff只会在原基础上加加，不会减减。
//
// 438. 找到字符串中所有字母异位词: https://leetcode.cn/problems/find-all-anagrams-in-a-string/
// 进阶：30. 串联所有单词的子串 https://leetcode.cn/problems/substring-with-concatenation-of-all-words/
vector<int> findAnagrams(string s, string p) {
    if (s.size() < p.size() || p.size() == 0) return {};
    
    unordered_map<char, int> cntMap; // 1. hashmap使用；
    for (char ch : p) {
        cntMap[ch]++;
    }
    
    int diff = cntMap.size(); // 2.diff的使用。
    for (int i = 0; i < p.size() - 1; i++) { // 可以将这部分合并到下边，其实就是j++变为不确定加加。但是多出来的j++看着好不舒服，所以暂时先不合并了。
        cntMap[s[i]]--;
        if (cntMap[s[i]] == 0) diff--; // 这种hashmap的加加减减和使用是可以合并到一个语句中的。
    }

    vector<int> res;
    for (int i = p.size() - 1, j = 0; i < s.size(); i++, j++) {
        cntMap[s[i]]--;
        if (cntMap[s[i]] == 0) diff--;
        if (0 == diff) {
            res.push_back(j);
        }
        cntMap[s[j]]++;
        if (cntMap[s[j]] == 1) diff++;
    }
    return res;
}