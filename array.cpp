//遍历数组使用加逼法，可以降低一次循环；（前提有序，所以复杂度至少为o(nlogn)）
//4个数加和为target
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) return {};
        sort(nums.begin(), nums.end());
        set<vector<int>> set;                               //为避免结果重复，可以使用set保存结果，不可以使用unordered_set，因为没有对应的散列函数；
        for (int i = 0; i < nums.size() - 3; ++i) {
            for (int j = i + 1; j < nums.size() - 2; ++j) {
                int left = target - nums[i] - nums[j];
                int k = j + 1,m = nums.size() - 1;
                while (k < m) {
                    int add = nums[k] + nums[m];
                    if (add == left) {
                        set.insert({nums[i], nums[j], nums[k], nums[m]});
                        k++;
                    }
                    else if (add > left) m--;
                    else k++;
                    
                }
            }
        }
        return {set.begin(), set.end()};
    }
};
//使用hashmap先保存两个数的和，这样可以将复杂度将为o（n ^ 2）;
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        set<vector<int>> res;
        unordered_map<int, vector<pair<int, int>>> map;             //hashmap装的是索引对；
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                if (i == j) continue;           
                map[nums[i] + nums[j]].push_back({i, j});
            }
        }
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                int add = target - nums[i] - nums[j];
                if (map.find(add) != map.end()) {
                    for (pair<int, int> loc : map[add]) {
                        if (i != j && i != loc.first && i != loc.second && j != loc.first && j != loc.second) { //不能重复；
                            vector<int> tmp {nums[i], nums[j], nums[loc.first], nums[loc.second]};      //不能重复
                            sort(tmp.begin(), tmp.end());
                            res.insert(tmp);
                        }
                    }
                }
            }
        }
        return {res.begin(), res.end()};
    }
};

//4个数求和的问题，都可以使用hashmap转化为o(n^2)的问题；
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int res = 0;
        unordered_map<int, int> map;
        for (int i = 0; i < A.size(); ++i) 
            for (int j = 0; j < B.size(); ++j) 
                map[A[i] + B[j]]++;
        for (int i = 0; i < C.size(); ++i) {
            for (int j = 0; j < D.size(); ++j) {
                int add = C[i] + D[j];
                if (map.find(-add) != map.end()) {
                    res += map[-add];
                }
            }
        }
        return res;
            
    }
};

//数组的第二种方式：采用函数来解决一个一个的小问题：数独是否合法，两个有序数组的中位数
class Solution {
    bool row_check(vector<vector<char>>&board, int i) {
        unordered_set<char> set;
        for (char ch : board[i]) {
            if (ch == '.') continue;
            else if (set.find(ch) != set.end()) return false;
            else set.insert(ch);
        }
        return true;
    }
    bool col_check(vector<vector<char>>& board, int j) {
        unordered_set<char> set;
        for (int i = 0; i < board.size(); ++i) {
            if (board[i][j] == '.') continue;
            else if (set.find(board[i][j]) != set.end()) return false;
            else set.insert(board[i][j]);
        }
        return true;
    }
    bool squre_check(vector<vector<char>>& board, int i, int j) {
        unordered_set<char> set;
        for (int k = 0; k < 3; k++) {
            for (int m = 0; m < 3; m++) {
                char ch = board[i + k][j + m];
                if (ch == '.') continue;
                else if (set.find(ch) != set.end()) return false;
                else set.insert(ch);
            }
        }
        return true;
        
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); ++i)
            if(!row_check(board, i)) return false;
        for (int i = 0; i < board[0].size(); ++i)
            if (!col_check(board, i)) return false;
        for (int i = 0; i < board.size(); i += 3) {
            for (int j = 0; j < board.size(); j += 3)
                if (!squre_check(board, i, j)) return false;
        }
        return true;
    }
};
//两个数组中找到重复数字：两个方法，（hashmap） + （排序+两个指针）；
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> result;
        for (int i = 0, j = 0; i < nums1.size() && j < nums2.size();) {
            if (nums1[i] == nums2[j]) {
                result.push_back(nums1[i]);
                ++i,++j;
            }
            else if (nums1[i] < nums2[j])
                ++i;
            else
                ++j;
        }
        return result;
    }
};

//二维有序数组中找到第k小的数，基本找第k小的数都可以使用这个方法
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int, vector<int>> pq;                //优先队列的方法来解决第k小/大的问题；
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {        
                pq.push(matrix[i][j]);                      //入队，如果队的大小超了，就pop();
                if (pq.size() > k) pq.pop();
            }
        }
        return pq.top();
    }
};
