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

//由此题引出的，自动填充数独的方法：回溯法
class Solution {
    bool is_valid(vector<vector<char>>& board, int i, int j) {
        for (int k = 0; k < board.size(); ++k)
            if (i != k && board[k][j] == board[i][j]) return false; //检验当前点是否已经存在，遍历一行就可以了；
        for (int m = 0; m < board.size(); ++m) 
            if (j != m && board[i][m] == board[i][j]) return false;
        int point1 = i / 3 * 3;
        int point2 = j / 3 * 3;                         //回到3的倍数的点，先除以3再乘以3；
        for (int k = point1; k < point1 + 3; ++k) {
            for (int m = point2; m < point2 + 3; ++m) {
                if (k ==i && m == j) continue;
                if (board[k][m] == board[i][j]) return false;
            }
        }
        return true;
    }
    
    bool helper(vector<vector<char>>& board, int i, int j) {
        if (i == 9) return true;    
        if (j == 9) {
            return helper(board, i + 1, 0);             //二维数组回溯的方法是，i和j来处理一个一个的元素；！！！！
        }
        if (board[i][j] != '.') {
            return helper(board, i, j + 1);
        }
        for (int k = 1; k < 10; ++k) {                  //把当前是点的点分别设置数字；
            board[i][j] = k + '0';
            if (is_valid(board, i, j))                  //如果满足条件，其会一直往下走，直到本函数第一行的true；
                if (helper(board, i, j + 1)) return true;   //如果满足条件，就继续向下递归，如果某个过程递归失败了，就表示当前值不可以，也需要恢复原始状态，如果成功了，应该告诉前面的递归成功了；
            board[i][j] = '.';                          //如果不满足条件，恢复原始状态；
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
    }
};
