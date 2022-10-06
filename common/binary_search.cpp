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

// 经典二分：近似有序的数组查找，涉及到的技巧如下：
// 1. 既然部分有序，那么就找到有序的那部分，然后判断是否可以淘汰有序的那部分；（进一步，如果无法找到有序的那部分，尝试只淘汰掉部分元素，比如让j--/i++）
// 2. 优先使用nums[mid]和nums[j]比较，因为mid一定不等于j，不用考虑等于的问题；
// 3. 小结论：最终结果一定考虑没有找到的情况，因为i == j已经不进入循环了，可能一开始就完全没进入循环。
// 
// 33. 搜索旋转排序数组: https://leetcode.cn/problems/search-in-rotated-sorted-array/
int search(vector<int>& nums, int target) {
    if (nums.size() == 0) {
        return 0;
    }
    int i = 0, j = nums.size() - 1;
    while (i < j) {
        int mid = i + (j - i) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < nums[j]) {
            if (target > nums[mid] && target <= nums[j]) {
                i = mid + 1;
            } else {
                j = mid - 1;
            }
        } else {
            if (target < nums[mid] && target >= nums[i]) {
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        }
    }
    return nums[i] == target ? i : -1;
}

// 经典二分的一个小问题：i = mid。
// 1. 当出现 i = mid，那么mid的计算需要 + 1，防止i == mid从而陷入无限循环；
// 2. 那能不能尝试不让 i = mid呢？比如将`nums[mid] <= target`中的`=`拿掉？不可以。因为可以考虑一堆等于的情况，此时一定需要i++才能到最后一个，只修改j是不行的。
//
// 34. 在排序数组中查找元素的第一个和最后一个位置：https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
int lastPos(vector<int>& nums, int target) {
    if (nums.size() == 0) {
        return -1;
    }
    int i = 0, j = nums.size() - 1;
    while (i < j) {
        int mid = i + (j - i) / 2 + 1;
        if (nums[mid] <= target) {
            i = mid;
        } else {
            j = mid - 1;
        }
    }
    return nums[i] == target ? i : -1;
}

// 经典二分的一个小问题：寻找第一个插入位置
// 第一个插入位置，可能位于nums.size()，而j的初始值是nums.size() - 1，i和j的范围都是到达不了的，所以此时需要单独考虑这种情况。
// 小结论：二分中，i和j的最终范围可能是什么？分情况讨论（i = mid的对称情况就不考虑了）：
// （1）i = mid + 1,j = mid;因为mid一定位于[i, j)，所以最终的i和j一定位于初始[i, j]内；
// （2）i = mid + 1, j = mid - 1; 同理，极端是可以到达[i - 1, j]的，所以要考虑溢出的场景，最好不好使用这种写法。
//
// 35. 搜索插入位置 https://leetcode.cn/problems/search-insert-position/
int searchInsert(vector<int>& nums, int target) {
    if (nums.size() == 0) return 0;
    if (nums.back() < target) return nums.size(); // 这里的特殊讨论很重要，否则是无法得到最终结果的。

    int i = 0, j = nums.size() - 1;
    while (i < j) {
        int mid = i + (j - i) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            i = mid + 1;
        } else {
            j = mid;
        }
    }
    return i;
}

// 数学公式与二分相结合：当已存在数学公式，然后求一个值，此时可以考虑二分
//
// 参考 math/rectangle.cpp
// 1954. 收集足够苹果的最小花园周长 https://leetcode.cn/problems/minimum-garden-perimeter-to-collect-enough-apples/