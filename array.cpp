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
