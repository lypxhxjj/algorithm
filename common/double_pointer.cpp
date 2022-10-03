// 双指针问题，是可以特别神奇的，可以一次遍历就得到结果的那种解法。

// 双指针，一个从头向后，一个从后向头，每次谁走，谁小谁走，只有移动小的那边才可以达到更大的一个值。
//
// 11. 盛最多水的容器: https://leetcode.cn/problems/container-with-most-water/
int maxArea(vector<int>& height) {
    if (height.size() < 2) return 0;

    int i = 0, j = height.size() - 1;
    int res = 0;
    while (i < j) {
        res = max(res, (j - i) * min(height[i], height[j]));
        if (height[i] > height[j]) {
            j--;
        } else {
            i++;
        }
    }
    return res;
}

// 双指针，i一般用于遍历数组，j的含义是 最后一个有效元素 VS 有效元素的下一个。就看第一个位置是否有效了
//
// 26. 删除有序数组中的重复项: https://leetcode.cn/problems/remove-duplicates-from-sorted-array/
// 27. 移除元素: https://leetcode.cn/problems/remove-element/
int removeDuplicates(vector<int>& nums) {
    int j = 0; // j的含义？最后一个有效元素。
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[j]) {
            continue;
        }
        nums[++j] = nums[i];
    }
    return j + 1;
}
