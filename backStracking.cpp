//第一题，将一系列数字转化为IP地址
class Solution {
    bool check_if_insert(const string& str) {                 //技巧1：将是否满足条件使用一个函数单独写出来；
        if (str.size() == 0 || str.size() > 3) return false;
        if (str.size() > 1 && str[0] == '0') return false;
        int digit = atoi(str.c_str());  //注意不要缺条件；
        if (digit > 255) return false;
        return true;
    }
    void backStracking(string s, int j, vector<string>& strs, string str) {
        if (s.size() == 0) return;                          //首先，如果不满足条件就直接返回；
        if (++j == 4) {                                     //其次，判断条件是否满足，然后进行插入（j就用于这个，将j换个名字，以防冲突）；
            if (check_if_insert(s)) {
                str += s;
                strs.push_back(str);
            }
            return;   
        }
        
        for (int i = 1; i < s.size(); ++i) {    
            string part = s.substr(0, i);
            if (check_if_insert(part))
                backStracking({s.begin() + i, s.end()}, j, strs, str + part + ".");   //回溯法要么就+=之后就-=回到原来状态，要么就直接在参数这里加
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> strs;
        string str;
        backStracking(s, 0, strs, str);
        return strs;
    }
};
