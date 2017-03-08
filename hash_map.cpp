//返回与索引有关的问题，一般使用hash_map，此时无法使用排序；
//1  找到数组中加和为target的两个数的下标值；
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); ++i) {
            int tmp = target - nums[i];
            if (map.find (tmp) != map.end())
                return {map[tmp], i};         //返回只有两个元素的vector，就可以直接这么写；
            map[nums[i]] = i;
        }
        return {};
    }
};

//可以考虑unorder_set的insert和erase搭配来解题：
//2  字符串中最长无重复子串的长度：
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> set;
        int result = 0, left = 0;
        for (int i = 0; i < s.size(); ) {             //不是每次都i++;
            if (set.find(s[i]) == set.end()) {
                set.insert(s[i++]);
                result = max(result, (int)set.size());    //有时候result每次一更新，是不错的方法；
            }
            else set.erase(s[left++]);                //insert和erase搭配，好用的方法；
        }
        return result;
    }
};

//可以考虑使用指针来搭配解题，指针的左右是标记左边合理的位置
//题目同2
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0, left = 0;
        unordered_map<char, int> map;                             //map中元素也很重要，代表的是最后一次出现的位置；
        for (int i = 0; i < s.size(); ++i) {
            if (map.find(s[i]) != map.end() && left <= map[s[i]]) //指针的含义很重要，代表目前为止前边不重复字符的第一个；
                left = map[s[i]] + 1;
            map[s[i]] = i;
            res = max(res, i - left + 1);                         //值的更新与left和i有关；
        }
        return res;
    }
};

//hashmap保存复杂数据结构体：寻找同一字符串的异构体
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;      //key保存的是排序好的字符串，value代表的是这个字符串同分异构体；
        for (int i = 0; i < strs.size(); ++i) {
            string str = strs[i];
            sort(str.begin(), str.end());
            if (map.find(str) != map.end()) {
                map[str].push_back(strs[i]);
            }
            else {
                map[str] = {strs[i]};
            }
        }
        vector<vector<string>> res;
        for (auto m : map) {
            res.push_back(m.second);
        }
        return res;
        
    }
};
//难题系列：满满的都是技巧啊
/*
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
*/
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (s.size() == 0 || words.size() == 0) return res;
        unordered_map<string, int> map;         //不按顺序来的使用hashmap;
        int size1 = words.size();
        int size2 = words[0].size();
        for (string& str : words)
            map[str]++;
        for (int i = 0; i < (int)s.size() - size1 * size2 + 1; ++i) {   //涉及到size()的运算，都要加上（int）强制转化；
            unordered_map<string, int> map1;                            //第二个hashmap的用途是：与第一个比较看是否相等！！！
            for (int j = i; j < i + size1 * size2; j += size2) {
                string tmp = s.substr(j, size2);                        //字符串substr函数，参数是起始位置和大小；
                map1[tmp]++;
            }
            if (map1 == map) res.push_back(i);
        }
        return res;
    }
};
