// 双指针问题，是可以特别神奇的，可以一次遍历就得到结果的那种解法。
// 1. 双指针的本质？
// 答：缓存机制。由之前的每次重新计算，变为缓存中间结果。
//
// 2. 双指针常见的解题套路：
// （1）i和j相向。下面的11题；
// （2）i和j怎么走非常清晰，但是要求j的含义十分明确，比如26/27。一般j比较慢，即i每次加加，j不一定。有时j比较快，即每次i加加，j需要做两件事，参考1556。
// （3）right和left同向走，right会保证稳定性，left不保证。每次先更新right，并尝试优化left。既然能优化left，那么每次进入优化left逻辑内，窗口是一个稳定状态。每次循环结束，窗口内一定是个不稳定状态。参考1234.
// （4）right和left同向走，但right的更新会破坏掉稳定性，left不会。所以进入right逻辑之前，先更新left保证right能稳定。所以更新left的时机在right之前。参考3.
//
// 3. 双指针常见的辅助数据结构：
// (1)hash保存个数（1234），保存索引（3）


// 双指针。每次更新right，并优化left
//
// 双指针的关键点：每次必移动right，如果可优化left，那么就优化left。
//
// 本题有个优化：hash使用普通数组。
//
// 本题有个关键点：窗口内要满足的条件参考下面的lambda。这个比较难想，可以简单记下来作为经验。
//
// 1234. 替换子串得到平衡字符串 https://leetcode.cn/problems/replace-the-substring-for-balanced-string/
class Solution {
public:
    int balancedString(string s) {
        int expected = s.size() / 4;
        int hash['Z'] = {0}; // 一个优化。尤其适用于hash使用比较多的情况。
        for (char ch : s) {
            hash[ch]++;
        }

        auto check = [&hash, expected]() { // 这个技巧很好。有限个字符很难不枚举，而如果能将枚举限制到lambda中，则代码很漂亮了。
            return hash['Q'] <= expected && hash['W'] <= expected && hash['E'] <= expected && hash['R'] <= expected;
        };
        if (check()) return 0;

        int res = s.size();
        for (int right = 0, left = 0; right < s.size(); right++) {
            hash[s[right]]--;
            while (check()) {
                res = min(res, right - left + 1);
                hash[s[left++]]++;
            }
        }

        return res;
    }
};

// 双指针，一个从头向后，一个从后向头，每次谁走，谁小谁走，只有移动小的那边才可以达到更大的一个值。
//
// 11. 盛最多水的容器: https://leetcode.cn/problems/container-with-most-water/
int maxArea(vector<int>& height) {
    if (height.size() < 2) return 0;

    int i = 0, j = height.size() - 1;
    int res = 0;
    while (i < j) {
        res = max(res, (j - i) * min(height[i], height[j]));
        if (height[i] > height[j]) {
            j--;
        } else {
            i++;
        }
    }
    return res;
}

// 双指针基本模型，i一般用于遍历数组，j的含义是 最后一个有效元素 VS 有效元素的下一个。就看第一个位置是否有效了
//
// 26. 删除有序数组中的重复项: https://leetcode.cn/problems/remove-duplicates-from-sorted-array/
// 27. 移除元素: https://leetcode.cn/problems/remove-element/
int removeDuplicates(vector<int>& nums) {
    int j = 0; // j的含义？最后一个有效元素。
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[j]) {
            continue;
        }
        nums[++j] = nums[i];
    }
    return j + 1;
}

// 双指针，当j比i还要快的时候。
//
// 一般情况下，i遍历每个元素，j在左边，遍历的比较慢。而一旦遇到快的，完了，手忙脚乱了。
// 思路：少的那个是i不变，多的那个j每次在循环内部多做一些事情。
//
// 1556. 千位分隔数 https://leetcode.cn/problems/thousand-separator/
string thousandSeparator(int n) {
    string str = to_string(n);
    string res;
    res.resize(str.size() + (str.size() - 1) / 3);
    for (int i = str.size() - 1, j = res.size() - 1, k = 1; i >= 0; i--, j--, k++) {
        res[j] = str[i];
        if (k % 3 == 0 && i != 0) {
            res[--j] = '.';
        }
    }
    return res;
}

// 双指针问题：如何维护一个合法的区间
//
// 双指针的主干编程法：for + res更新 -> 维护hash和左指针正确性。
//
// 双指针的本质：通过一个辅助hashmap，快速移动左指针。右指针是普通的i。
//
// 3. 无重复字符的最长子串 https://leetcode.cn/problems/longest-substring-without-repeating-characters/
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> hash;

    int res = 0;
    for (int i = 0, j = 0; i < s.size(); i++) {
        if (hash.find(s[i]) != hash.end() && hash[s[i]] >= j) {
            j = hash[s[i]] + 1; // 维护左指针的正确性。
        }
        hash[s[i]] = i; // 维护hash的正确性；
        res = max(res, i - j + 1); // 每次用双指针计算结果。
    }
    return res;
}

// 双指针问题：如何维护一个合法的区间
//
// 双指针的主干编程法：for + res更新 -> 维护set和左指针的正确性；
// 为何可以使用主干编程法？循环最后，一定存在一个稳定的区间。
//
// 双指针的本质：通过一个set维护双指针内的元素，通过set来保证双指针内数据的正确性。
//
// ps. 以上两种解法，一样的行数，代码很像，但完全不一样的理解。
// 
// 3. 无重复字符的最长子串 https://leetcode.cn/problems/longest-substring-without-repeating-characters/
int lengthOfLongestSubstring(string s) {
    unordered_set<char> set;

    int res = 0;
    for (int i = 0, j = 0; i < s.size(); i++) {
        while (set.find(s[i]) != set.end()) {
            set.erase(s[j++]);  // 维护j。
        }
        set.insert(s[i]); // 维护set。
        res = max(res, i - j + 1); // 主干编程，因为此时达到的窗口的稳定状态。
    }
    return res;
}