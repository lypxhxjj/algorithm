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

//回溯法2：n对括号的所有可能组合方式
class Solution {
    void backStracking(int left, int left_left, int right, vector<string>& res, string tmp) {   //一个一个加上去的，且结果有很多的这种，就要使用回溯
        if (left == 0 && right == 0) {      //首先，如果到达了最后，就添加，这个不需要过滤条件；
            res.push_back(tmp);
            return;
        }
        if (left_left > 0) {                   //其次，有两种情况，加左边还是加右边，以及什么时候加左边什么时候加右边；两边加都可以的情况下，需要都加；
            if (left) backStracking(left - 1, left_left + 1, right,res, tmp + "(");
            backStracking(left, left_left - 1, right - 1, res, tmp + ")");          //在函数调用的时候调整tmp，可以减少回溯变回原来状态的步骤
        }
        else
            backStracking(left - 1, left_left + 1, right,res, tmp + "(");
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string tmp;
        int left = n, left_left = 0, right = n;
        backStracking(left, left_left, right, res, tmp);
        return res;
    }
};

//回溯3：找到集合中加和为target的一组数，允许重复；
class Solution {
    void backStracking(vector<int>& data, int target, int add, int level, vector<int>& tmp, vector<vector<int>>& res) {
        if (add > target) return;                           //退出条件；
        if (add == target) {                                //push_back条件；
            res.push_back(tmp);
            return;
        }
        
        for (int i = level; i < data.size(); ++i) {         //由于每个数都可能加进来，所以使用循环；
            tmp.push_back(data[i]);                 
            backStracking(data, target, add + data[i], i, tmp, res);
            tmp.pop_back();                                 //vector只能使用先push_back然后再pop_back的方法，string可以使用临时字符串；
        }
        
        
    }                                                       //此题保证不重复的做法是，循环是从level开始而不是从0开始；
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> tmp;
        backStracking(candidates, target, 0, 0, tmp, res);
        return res;
    }
};
