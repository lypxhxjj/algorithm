// 编程上的技巧

// 如何对结果去重：
// 排序 + for/if + while/if
//
// 15. 三数之和 https://leetcode.cn/problems/3sum/
 vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) return {};

        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i + 2 < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int j = i + 1, k = nums.size() - 1;
            while (j < k) {
                if (j > i + 1 && j < k && nums[j] == nums[j - 1]) {
                    j++;
                    continue;
                }
                if (k < nums.size() - 1 && j < k && nums[k] == nums[k + 1]) {
                    k--;
                    continue;
                }
                int sum = nums[i] + nums[j] + nums[k];
                if (sum == 0) {
                    res.push_back({nums[i], nums[j], nums[k]});
                    k--, j++;
                } else if (sum > 0) {
                    k--;
                } else {
                    j++;
                }
            }
        }
        return res;
    }