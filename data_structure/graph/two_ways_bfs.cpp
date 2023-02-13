// 总体思路：
// 1. 双向bfs是解决什么问题的？
// 答：每个元素在处理之后，都可能向队列中加入很多元素。使得每一层的数据量按倍数/指数增长。
// 注意：双向bfs是单向bfs的优化，需要先掌握单向的，再来决定要不要优化为双向的。
//
// 2. 什么实现技巧？
// （1）一共三组变量：q1/q2, visited, dis，并实现bfs版本，并将while循环内的代码提取到lambda中，以三组变量作为参数。
// （2）为实现双向bfs，再定义一套三组变量。while循环内调用两次lambda即可。
// （3）双向和单向的唯一区别在于，lambda中判断是否达到终点的方式不同，双向需要遍历q3。
//
// 3. 为啥数据结构使用vector？
// 答：处理q1中的数据依赖q3，此时有遍历q3的需求，但queue由于没有迭代器的概念，无法遍历，所以需要使用deque与vector，性能上讲，肯定vector更好了。
//
// 4. dis1和dis2初始化为谁？
// 答：dis的作用是「已处理和正在处理的」边的个数。所以还未处理前，都初始化为0，开始处理哪一边，哪一边的dis先加加。
// 
// 127. 单词接龙 https://leetcode.cn/problems/word-ladder/
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (beginWord == endWord) return 0;

        unordered_set<string> wordSet;
        for (string& word : wordList) {
            wordSet.insert(word);
        }
        if (wordSet.count(endWord) == 0) {
            return 0;
        }

        int res1 = 0, res2 = 0;
        vector<string> q1, q2, q3, q4;
        q1.push_back(beginWord);
        q3.push_back(endWord);
        unordered_set<string> visited1, visited2; // 貌似没办法了，字符串的去重
        visited1.insert(beginWord);
        visited2.insert(endWord);

        while (!q1.empty() || !q3.empty()) {
            auto walk = [&wordSet](vector<string>& q1, vector<string>& q2, vector<string>& q3, unordered_set<string>& visited, int& res1, int res2) { // 这里
                res1++;                                 // 这里。
                while (!q1.empty()) {
                    string curr = q1.back();
                    q1.pop_back();

                    for (int i = 0; i < curr.size(); i++) {
                        char prev = curr[i];
                        for (char ch = 'a'; ch <= 'z'; ch++) {
                            if (prev == ch) continue;
                            curr[i] = ch;

                            if (wordSet.count(curr) == 0) continue;
                            if (visited.count(curr) == 1) continue;

                            for (auto word : q3) {
                                if (curr == word) {
                                    return res1 + res2 + 1;
                                }
                            }
                            
                            visited.insert(curr);
                            q2.push_back(curr);
                        }
                        curr[i] = prev;
                    }
                }
                q1.swap(q2);
                return 0;
            };
            int res = walk(q1, q2, q3, q4, visited1, res1, res2); // 这里。
            if (res != 0) return res;
            res = walk(q3, q4, q1, q2, visited2, res2, res1);
            if (res != 0) return res;
        }
        return 0;
        
    }
};

// 双向bfs解法：
//
// 2059. 转化数字的最小运算数 https://leetcode.cn/problems/minimum-operations-to-convert-number/
class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        if (start == goal) {
            return 0;
        }

        auto op1 = [](int a, int b) {return a + b;};
        auto op2 = [](int a, int b) {return a - b;};
        auto op3 = [](int a, int b) {return a ^ b;};
        vector<function<int(int, int)>> ops = {op1, op2, op3}; // 可学习。

        int res1 = 0, res2 = 0;
        bool visited1[1001] = {false}, visited2[1001] = {false};

        vector<int> q1, q2, q3, q4;
        q1.push_back(start);
        visited1[start] = true;
        q3.push_back(goal);
        if (goal >= 0 && goal <= 1000) { // 非完全visited。
            visited2[goal] = true;
        }

        while (!q1.empty() || !q2.empty()) {
            auto walk = [&nums, &ops](vector<int>& q1, vector<int>& q2, vector<int>& q3, vector<int>& q4, bool visited[], int& res1, int res2) {
                res1++;
                while (!q1.empty()) {
                    int curr = q1.back();
                    q1.pop_back();
                    for (int i = 0; i < nums.size(); i++) {
                        for (auto op : ops) {
                            int val = op(curr, nums[i]);
                            for (int v : q3) {
                                if (val == v) {
                                    return res1 + res2;
                                }
                            }
                            if (val >= 0 && val <= 1000 && !visited[val]) {
                                visited[val] = true;
                                q2.push_back(val);
                            }
                        }
                    }
                }
                q1.swap(q2);
                return -1;
            };
            int res = walk(q1, q2, q3, q4, visited1, res1, res2);
            if (res != -1) {
                return res;
            }
            res = walk(q3, q4, q1, q2, visited2, res2, res1);
            if (res != -1) {
                return res;
            }
        }
        return -1;
    }
};