// 二分查找是为数不多的，可以将时间复杂度降低到logn的算法。

 // 第k小，从1开始
int findKth(vector<int>& nums1, vector<int>& nums2, int i, int j, int k) {
    if (nums1.size() - i > nums2.size() - j) { // 简化问题
        return findKth(nums2, nums1, j, i, k);
    }
    if (nums1.size() == i) { // 边界条件；
        return nums2[j + k - 1];
    }
    if (k == 1) { // 边界条件。
        return min(nums1[i], nums2[j]);
    }

    int leftLen = nums1.size() - i > k / 2 ? k / 2 : nums1.size() - i; // 无脑写，索引与个数的转化。
    int leftIndex = i + leftLen - 1;
    int rightLen = k - leftLen;
    int rightIndex = j + rightLen - 1;
    if (nums1[leftIndex] < nums2[rightIndex]) {
        return findKth(nums1, nums2, leftIndex + 1, j, k - leftLen);
    } else {
        return findKth(nums1, nums2, i, rightIndex + 1, k - rightLen);
    }
}
// 两个有序数组的中位数问题，好喜欢这个题，好多小技巧。<4>
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int total = nums1.size() + nums2.size();
    int leftMid = (total - 1) / 2;
    int leftVal = findKth(nums1, nums2, 0, 0, leftMid + 1); // 总数total->中间偏左索引->第k个
    if (total % 2 == 1) {
        return leftVal;
    }
    int rightVal = findKth(nums1, nums2, 0, 0, total / 2 + 1);
    return (double(leftVal) + rightVal) / 2;
   }