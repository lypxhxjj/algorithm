// 二分查找是为数不多的，可以将时间复杂度降低到logn的算法。
//

// 二分的细节点：
// 1. while (i < j) 决定了 i==j时不会进入循环，所以需要特殊考虑i==j，即只有一个元素的情况；
// 2. int mid = (i + j) >> 1; 这里保证了 mid一定小于j，但可能等于i，所以一定不能出现 i = mid；
// 3. nums[mid] == target 判断是否等于这一步不是必须的，但是如果每次二分的成本比较高，那么就是必须的，比如矩阵内的二分，每次二分需要o(n)复杂度；
// 4. nums[mid] > nums[j] 优先比较j和mid + 1，因为mid一定小于j，所以不要拿mid和i比较；
while (i < j) {
    int mid = (i + j) / 2;
    if (nums3[mid] == val) {
        return mid;
    } else if (nums3[mid] > val) { 
        j = mid;
    } else {
        i = mid + 1;
    }
}

// 二分的使用场景汇总：
//
// 1. 最值问题：一般会有第一个xxx，最后一个xxx，大于等于，大于，小于等于，小于，这些词语凑起来。
// 2. 猜 + 验证：一般处理没有思路的问题；
// 3. 特殊场景问题：
// (1) 两个有序数组寻找第k小问题；每次淘汰掉k/2
// (2) 循环数组问题；根据有序的那部分淘汰


// 二分查找的典型结论：两个有序数组查找第k小问题 -> 可以使用二分。
//
// 二分可以放心使用递归：二分的递归深度绝对不会很高，所以可以放心使用递归简化代码。
// 如果递归：边界条件的处理就很重要：
// 1. 两个数组的边界问题：一定确保某一个数组的个数多，简化分类讨论逻辑。
// 2. 每个参数的边界问题，包括i和k的边界。
//
// 第k小问题的编程方式：第几 《=》 长度len -> 索引idx关系。
// ps. 只要将个数len，索引idx分别计算出来，那么写起代码来就非常爽了。
//
// 淘汰哪一半？每个数组取k/2个，特殊值法（只有两个元素），淘汰掉小的那个部分。最终值在小的后边，大的前边。
//
// 最后决定使用total/2，是否加减1的问题上：特殊值法。只要两个元素，那么期望找谁，这里需要注意索引与第k小的关系。
// 
// 4. 寻找两个正序数组的中位数: https://leetcode.cn/problems/median-of-two-sorted-arrays/
int findKth(vector<int>& nums1, vector<int>& nums2, int i, int j, int k) {
    if (nums1.size() - i > nums2.size() - j) {
        return findKth(nums2, nums1, j, i, k);
    }
    if (i == nums1.size()) {
        return nums2[j + k - 1];
    }
    if (k == 1) {
        return min(nums1[i], nums2[j]);
    }

    int len1 = nums1.size() - i >= k / 2 ? k / 2 : nums1.size() - i;
    int idx1 = i + len1 - 1;
    int len2 = k - len1;
    int idx2 = j + len2 - 1;
    if (nums1[idx1] < nums2[idx2]) {
        return findKth(nums1, nums2, idx1 + 1, j, k - len1);
    } else {
        return findKth(nums1, nums2, i, idx2 + 1, k - len2);
    }
}
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int total = nums1.size() + nums2.size();
    if ((total & 1) == 1) {
        return findKth(nums1, nums2, 0, 0, total / 2 + 1);
    } 
    return ((double)findKth(nums1, nums2, 0, 0, total / 2) + (double)findKth(nums1, nums2, 0, 0, total / 2 + 1)) / 2.0 ;
}

// 经典二分：近似有序的数组查找，涉及到的技巧如下：
// 1. 非全局有序找部分有序：既然部分有序，那么就找到有序的那部分，然后判断是否可以淘汰有序的那部分；（进一步，如果无法找到有序的那部分，尝试只淘汰掉部分元素，比如让j--/i++）
// 2. 优先比较mid和j：优先使用nums[mid]和nums[j]比较，因为mid一定不等于j，不用考虑等于的问题；
// 3. 最终结果特殊考虑：最终结果一定考虑没有找到的情况，因为i == j已经不进入循环了，可能一开始就完全没进入循环。
// 
// 33. 搜索旋转排序数组: https://leetcode.cn/problems/search-in-rotated-sorted-array/
int search(vector<int>& nums, int target) {
    if (nums.size() == 0) {
        return 0;
    }
    int i = 0, j = nums.size() - 1;
    while (i < j) { // [i, j], mid: [i, j)，mid - 1: [i - 1, j - 1), mid + 1: [i + 1, j]
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

// 二分的一个应用：满足单调性 && 具体算法没有或者很乱
//
// 有些问题算法很难推导，比如游戏问题中奇怪的游戏规则。这个时候，可以看看，参数和结果是否存在单调性关系，存在的话，即可使用二分。
// 小技巧：一个问题不会的时候，可以考虑二分试试。
// 
// 1760. 袋子里最少数目的球 https://leetcode.cn/problems/minimum-limit-of-balls-in-a-bag/
int minimumSize(vector<int>& nums, int maxOperations) {
    int maxVal = *max_element(nums.begin(), nums.end());
    int i = 1, j = maxVal;
    while (i < j) {
        int mid = (i + j) >> 1;

        int currCnt = 0; // 这块逻辑是用来计算mid详情的，成本也比较高，但是没办法直接判断返回的。
        for (int num : nums) {
            currCnt += (num - 1) / mid;   // 小技巧，很多时候没办法直接除的时候，可以参考先减一再除的方法
        }

        if (currCnt > maxOperations) {
            i = mid + 1;
        } else {
            j = mid;
        }
    }
    return i;
}

// 再来一道：依然是没有具体算法。
//
// 小技巧：本质就是猜 + 验证 的过程。而这个过程一般最差时间复杂度也就是o(nlogn)，完全比o(n^2)快。
//
// 1552. 两球之间的磁力 https://leetcode.cn/problems/magnetic-force-between-two-balls/
bool isOk(vector<int>& position, int m, int mid) {
    int curr = position[0];
    for (int i = 1; i < position.size(); i++) {
        if (position[i] - curr >= mid) {
            m--;
            curr = position[i];
        }
        if (m == 1) return true; // 第一个curr已经占了一个位置
    }
    return false;
}
int maxDistance(vector<int>& position, int m) {
    sort(position.begin(), position.end());
        
    int i = 0, j = position.back();
    while (i < j) {
        int mid = (i + j)/ 2 + 1;
        if (isOk(position, m, mid)) {
            i = mid;
        } else {
            j = mid - 1;
        }
    }
    return i;
}

// 数学公式与二分相结合：当已存在数学公式，然后求一个值，此时可以考虑二分
//
// 参考 math/rectangle.cpp
// 1954. 收集足够苹果的最小花园周长 https://leetcode.cn/problems/minimum-garden-perimeter-to-collect-enough-apples/