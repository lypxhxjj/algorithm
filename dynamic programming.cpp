//1  遍历数组时的当前值，前面的结果加上当前值，还是从当前值重新开始；
//问题：和最大的最长子串问题：
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = INT_MIN, sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (sum > 0) sum += nums[i];
            else sum = nums[i];
            if (result < sum) result = sum;
        }
        return result;
    }
};

//找到三角矩阵中最小路径和，从上到下，所以只可以不变或者大一个数，即f(i, j) += min(f(i + 1, j), f(i + 1, j + 1))
//此题特殊的思路是，从下往上遍历，最后可以不用遍历那个数组了；还有如果不让更改元素的话，额外空间可以拷贝出最后一行，来当做临时空间；
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if (triangle.size() == 0) return 0;
        unsigned size = triangle.size() - 2;
        for (int i = size; i >= 0; --i) {
            for (int j = 0; j < triangle[i].size(); ++j) {
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
            }
        }
        return triangle[0][0];
    }
};

class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int n = triangle.size();
        vector<int> dp(triangle.back());
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }
        return dp[0];
    }
};