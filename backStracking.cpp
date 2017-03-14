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
//上一题的换种问法：数据可以重复，但是结果不可以重复，（上题是结果可以重复，数据不重），那就只能使用先排序和set代替push_back了；
class Solution {
    void backStracking(vector<int>& data, int target, int level, int add, set<vector<int>>& res, vector<int>& tmp) {
        if (add > target) return;
        if (add == target) {
            res.insert(tmp);
            return;
        }
        
        for (int i = level; i < data.size(); ++i) {
            tmp.push_back(data[i]);
            backStracking(data, target, i + 1, add + data[i], res, tmp);
            tmp.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        set<vector<int>> res;
        vector<int> tmp;
        backStracking(candidates, target, 0, 0, res, tmp);
        return {res.begin(), res.end()};
    }
};
//再来一个，1-9这几个数字里选k个，然后加和是n：
class Solution {
    void recursion(vector<vector<int>>& res, vector<int> tmp, int k, int n, int add, int m) {
        if (tmp.size() > k || add > n) return;
        if (tmp.size() == k && add == n) {
            res.push_back(tmp);
            return;
        }
        
        for (int i = m; i < n && i <= 9; ++i) {     //随机选k个，那么就从m开始顺序向后选就可以了，选一个，push_back一个；
            tmp.push_back(i);
            recursion(res, tmp, k, n, add + i, i + 1);  //递归的时候能使用临时值就使用临时值，免得还得回到原来状态；
            tmp.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> tmp;
        recursion(res, tmp, k, n, 0, 1);
        return res;
        
    }
};

//回溯4：获取所有排列：最基本的回溯法；
class Solution {
    void helper(vector<vector<int>>& res, vector<int> tmp, int i) {
        if (i == tmp.size()) {
            res.push_back(tmp);
            return;
        }
        for (int j = i; j < tmp.size(); ++j) {  //必须从i开始，不然可能会取不到0；
            swap(tmp[i], tmp[j]);
            helper(res, tmp, i + 1);
            swap(tmp[i], tmp[j]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        helper(result, nums, 0);
        return result;
        
    }
};  

//如果data有重复，但是允许结果有重复，使用set保存结果（因为可能两个数相邻是一样的情况下会造成重复）
class Solution {
    void helper(set<vector<int>>& res, vector<int> tmp, int i) {
        if (i == tmp.size()) res.insert(tmp);
        for (int j = i; j < tmp.size(); ++j) {
            swap(tmp[i], tmp[j]);
            helper(res, tmp, i + 1);
            swap(tmp[i], tmp[j]);
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        set<vector<int>> set;
        helper(set, nums ,0);
        return {set.begin(), set.end()};
    }
};

//回溯法5：利用排列来解题
class Solution {
    void helper(vector<int>& nums, int i, int& res) {
        if (i == nums.size()) {
            res++;
            return;
        }
        
        for (int j = i; j < nums.size(); ++j) {
            swap(nums[i], nums[j]);
            if (nums[i] % (i + 1) == 0 || (i + 1) % nums[i] == 0)   //与排列的差别在于，这个地方满足条件才可以继续向下走，否则就直接回溯；
                 helper(nums, i + 1, res);
            swap(nums[i], nums[j]);
        }
    }
public:
    int countArrangement(int N) {
        int res = 0;
        vector<int> nums;
        nums.reserve(N);
        for (int i = 1; i <= N; ++i)
            nums.push_back(i);
        helper(nums, 0, res);
        return res;
        
    }
};

//回溯法6  递归多少次的题：一组数组，对应手机字母的组合
class Solution {
    void backStracking(const string& digits, vector<string>& const_str, int level, vector<string>& res, string tmp) {
        if (level == digits.size()) {
            res.push_back(tmp);
            return;
        }
        
        int num = digits[level] - '0';
        for (int i = 0; i < const_str[num - 2].size(); ++i) {               //此题是递归的次数也可能需要通过参数传递进来；
            backStracking(digits, const_str, level + 1, res, tmp + const_str[num - 2][i]);
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return {};              //这里需要注意，如果字符串为空，返回的是{}。而不是{“”}；
        vector<string> const_str{"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"}; //有很多常量，可以定义一个字符串数组；
        vector<string> res;
        string tmp;
        backStracking(digits,const_str, 0, res, tmp);
        return res;
    }
};
//回溯法7  匹配包含点的字符串 //将字符串中的点替换掉之后进行比较
class WordDictionary {
    unordered_set<string> set;
    
    bool backStracking(string& word, int level) {
        if (level == word.size()) 
            return set.find(word) != set.end();
            
        if (word[level] != '.') {
            if (backStracking(word, level + 1)) return true;    //小错误，最开始的没有加{}，导致ifelse匹配出错；
        }
        else {
            for (int i = 0; i < 26; ++i) {              //就是挨个替换；
                word[level] = 'a' + i;
                if (backStracking(word, level + 1)) return true;    //使用返回值的含义是，在递归之后如果需要返回，就直接返回了；
                word[level] = '.';
            }
        }
        return false;
    } 
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        set.insert(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return backStracking(word, 0);
    }
};

//回溯法8，将字符串拆分成一个一个的回文：简单的回溯法，
class Solution {
    bool isPalindrome(const string& s) {
        if (s.size() < 2) return true;
        int i = 0, j = s.size() - 1;
        while (i < s.size()) {
            if (s[i] != s[j]) return false;
            i++, j--;
        }
        return true;
    }
    void backStracking(string s, int level, vector<vector<string>>& res, vector<string>& tmp) {
        if (s.size() == level) {
            res.push_back(tmp);
            return;
        }
        for (int i = level; i < s.size(); ++i) {
            string s_tmp = s.substr(level, i - level + 1);
            if (isPalindrome(s_tmp)) {
                tmp.push_back(s_tmp);
                backStracking(s, i + 1, res, tmp);  //满足条件的才往下走；
                tmp.pop_back();                     //走完之后回溯到原来的状态；
            }
        }
    }
public: 
    vector<vector<string>> partition(string s) {
        if (s.size() == 0) return {};
        vector<vector<string>> res;
        vector<string> tmp;
        backStracking(s, 0, res, tmp);
        return res;
    }
};

//回溯法9：求子集，数据集中有重复，但是结果不能有重复（排序之后不能有重复）
class Solution {
    void generate(set<vector<int>>& res, vector<int>& nums, vector<int> tmp, int i) {
        if (i == nums.size()) {
            res.insert(tmp);
            return;
        }
        generate(res, nums, tmp, i + 1);    //加是一种情况，不加是一种情况；
        tmp.push_back(nums[i]);
        generate(res, nums, tmp, i + 1);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());     //竟然还需要sort； 结果要求排序后不重复，那就先排序；
        set<vector<int>> res;
        vector<int> tmp;
        generate(res, nums, tmp, 0);
        return {res.begin(), res.end()};
        
    }
};
