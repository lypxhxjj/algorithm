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

// 旋转数组，使用环形数组的方式遍历
// 优先使用 i+1而不是i-1，所以索引变为(i + 1) % nums.size().
// 
// 1752. 检查数组是否经排序和轮转得到 https://leetcode.cn/problems/check-if-array-is-sorted-and-rotated/
bool check(vector<int>& nums) {
    if (nums.size() < 3) return true;
    int cnt = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > nums[(i + 1) % nums.size()]) {
            cnt++;
        }
        if (cnt > 1) return false;
    }
    return true;
}