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

//求一个数组中可以跳着递增的最大子数组的大小；
//思路1 是动态规划，保存一个临时数组，每次都向前遍历找到当前值的大小，最后选出一个最大值来；
//以下的思路是：遍历一遍数组，使用一个辅助数组，如果此时的值大于所有值，就插入到最后，否则的话就更新当前值，思路巧妙，背吧
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tmp;
        for (int num : nums) {
            auto it = lower_bound(tmp.begin(), tmp.end(), num);
            if (it == tmp.end()) tmp.push_back(num);
            else *it = num;
        }
        return tmp.size();
    }
};
//子串之和是k的倍数，就返回true，否则返回false；
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        for (int i = 0; i < nums.size(); ++i) {//处理子串的问题，都是二重循环，第一重循环代表的是从哪开始，第二重循环代表到哪；
            long long add = nums[i];
            for (int j = i + 1; j < nums.size(); ++j) {
                add += nums[j];         //此题有个很大的特点是，子数组最少两个数，所以需要加一下再判断；否则外边也需要判断一下；
                if (k == add) return true;
                if (k != 0 && add % k == 0) //考虑k==0的情况，有的借鉴，取余肯定不行，可以在取余前加判零操作，还需要在前边加一个k == add的条件；
                    return true;
            }
        }
        return false;
    }
};
//第二种解法基于数学，保存的是取余之后的余数，如果两个余数相等，那么两个和相减的话，这个子串对应的必是k的倍数；
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size(), sum = 0, pre = 0;
        unordered_set<int> st;                  //保存的挺特殊的，保存余数；
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            int t = (k == 0) ? sum : (sum % k);         //求一遍和就可以，至少从第二个数开始减，所以至少是两个数的数组；
            if (st.count(t)) return true;
            st.insert(pre);
            pre = t;
        }
        return false;
    }
};

//上面是子串的问题，此题是子矩阵的问题：子矩阵之和：然后利用几何知识来寻找当前和与前面哪些和有关系
class NumMatrix {
    vector<vector<int>> sums;               //数组的大小应该是，比matrix大一圈；
public:
    NumMatrix(vector<vector<int>> matrix) {
        if (matrix.size() == 0) return;     //矩阵相关问题，一定要检查是否长度是0，此时sums，应该是{}，而不是{{}}；
        sums = vector<vector<int>>(matrix.size() + 1, vector<int>(matrix[0].size() + 1) );
        for (int i = 1; i <= matrix.size(); ++i) {
            for (int j = 1; j <= matrix[0].size(); ++j) {   //求和的方法是
                sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) { //返回结果的方法，和求和方法类似，col1和row2搭配着来；
        return sums[row2 + 1][col2 + 1] - sums[row1][col2 + 1] - sums[row2 + 1][col1] + sums[row1][col1];
    }
};
//利用子矩阵和解决的一个问题：找到子矩阵和比k小的最大的那个数；
class Solution {
    vector<vector<int>> cal_sum(vector<vector<int>>& matrix) {
        vector<vector<int>> res(matrix.size() + 1, vector<int>(matrix[0].size() + 1));
        for (int i = 1; i <= matrix.size(); ++i) {
            for (int j = 1; j <= matrix[0].size(); ++j) {
                res[i][j] = res[i - 1][j] + res[i][j - 1] - res[i - 1][j - 1] + matrix[i - 1][j - 1];
            }
        }
        return res;
    }
    int cal_child_sum(int i, int j, int m, int n, vector<vector<int>>& sums) {
        return sums[m + 1][n + 1] - sums[i][n + 1] - sums[m + 1][j] + sums[i][j];   //这两个方法完全是照搬上面的问题；
    }
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        vector<vector<int>> sums = cal_sum(matrix);
        int delta = INT_MAX;
        for (int i = 0; i < matrix.size(); ++i) {               //四重循环；注意，sums是外层多了一层0，但是四重循环找和时，还是需要遍历matrix的，而不是sums的，因为上面的helper就是基于matrix的；
            for (int j = 0; j < matrix[0].size(); ++j) {
                for (int m = 0; m <= i; ++m) {
                    for (int n = 0; n <= j; ++n) {
                        int sum = cal_child_sum(m, n, i, j, sums);
                        if (sum == k)
                            return k;
                        else if (sum < k) {
                            delta = min(delta, k - sum);
                        }
                    }
                }
            }
        }
        return k - delta;
    }
};
