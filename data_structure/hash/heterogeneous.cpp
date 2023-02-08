// hashmap解决异构词的问题。hash + diff
//
// 即diff表示hashmap中预定义元素个数，后续只有和预定义的字符种类和个数都完全相同的时候，diff才会变为0。
//
// 438. 找到字符串中所有字母异位词: https://leetcode.cn/problems/find-all-anagrams-in-a-string/
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

// hashmap解决异构数组问题：hash + diff
//
// 关键点：为啥diff不需要在hash[key] == -1的时候++呢？
// diff只在value为1的时候才加加，结果是arr比sortedArr多的元素种类。只要两个数组不完全一样，那么arr肯定存在比sortedArr多的元素种类，即diff > 0 。一旦diff变为0，二者就相等了。
//
// 快速理解题意：原数组和排序之后的数组，有多少个可以组成异构数组问题。
// 
// 768. 最多能完成排序的块 II https://leetcode.cn/problems/max-chunks-to-make-sorted-ii/
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        unordered_map<int, int> hash; // 一个坑，这种问题不只是字符串存在，所以key是int类型，不是char。
        int diff = 0;

        auto sortedArr = arr;
        sort(sortedArr.begin(), sortedArr.end());

        int res = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (++hash[arr[i]] == 1) {
                diff++;
            }
            if (--hash[sortedArr[i]] == 0) {
                diff--;
            }
            if (diff == 0) {
                res++;
            }
        }
        return res;
    }
};

