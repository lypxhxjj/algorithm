// 二分查找是为数不多的，可以将时间复杂度降低到logn的算法。
//
// 定义「基础二分」，到处都很基础，很多问题可以基于基础二分解决；不能解决的会指出其特殊点。
// 1. 基础二分的含义：lower_bound但是不会到达end()
// 2. 写二分的过程比较简单，找到mid后，能淘汰掉一半就直接淘汰就好了。本质就在这里了。
while (i < j) {
    int mid = (i + j) / 2;
    if (nums3[mid] == val) { // 可以不考虑。
        return mid;
    } else if (nums3[mid] > val) { // 假如mid与i/j有关（无关最好了），那么优先使用j。因为mid一定不等于j。
        j = mid;
    } else {
        i = mid + 1;
    }
}


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

// 基础二分的变形：二分过程中出现：i = mid，则mid的计算需要+1
// 
// 为何会出现i = mid ？纯粹是因为算法本身，没有任何套路可言。
//
// 为何return需要特殊处理？找不到很正常。
// 小技巧：感觉除了寻找一个元素是否存在，都需要这个特殊条件。
//
// 理清含义特别重要：最后一个小于等于 等价于 找最后一个等于，有了明确的含义，就不会问出下面傻逼的问题了，因为代码怎么写是固定的，不能随意修改的：
// 1. 那能不能尝试不让 i = mid呢？比如将`nums[mid] <= target`中的`=`拿掉？不可以。因为可以考虑一堆等于的情况，此时一定需要i++才能到最后一个，只修改j是不行的。
// 小技巧：写二分前一定理清楚要做啥。如何理清：一般会有第一个xxx，最后一个xxx，大于等于，大于，小于等于，小于，这些词语凑起来。
// 
// 34. 在排序数组中查找元素的第一个和最后一个位置：https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
int lastLessEqual(vector<int>& nums, int target) {
    int i = 0, j = (int)nums.size() - 1;
    while (i < j) {
        int mid = i + (j - i) / 2 + 1; // [i + 1, j]
        if (nums[mid] <= target) {
            i = mid;
        } else {
            j = mid - 1;
        }
    }
    return nums[i] == target ? i : -1;
}

// 经典二分的一个小问题：寻找第一个插入位置
//
// 基础二分(即lower_bound但不会到达end()) + 单独考虑特殊位置。
//
// 为啥需要考虑特殊位置？因为初始的[i,j]覆盖不了全部位置。
//
// 如何快速定位i和j最终到的范围？
// 1. 先考虑mid的范围。因为i != j，所以普通 mid 一定是 [i, j -1]; 非普通 mid 是 [i + 1, j];
// 2. 再考虑i和j，简单由mid推导，i = mid，则i和mid的范围相同[i, j - 1]；j = mid - 1，则j的左边界比mid的左移了[i - 1, j]。
// 小技巧：每次可以将mid的范围写出来，这样可以避免i和j的越界。 
//
// 35. 搜索插入位置 https://leetcode.cn/problems/search-insert-position/
int searchInsert(vector<int>& nums, int target) {
    if (nums.size() == 0) return 0;
    if (nums.back() < target) return nums.size(); // 这里的特殊讨论很重要，否则是无法得到最终结果的。

    int i = 0, j = nums.size() - 1;
    while (i < j) {
        int mid = i + (j - i) / 2; // [i,j - 1]
        if (nums[mid] < target) {
            i = mid + 1;
        } else {
            j = mid;
        }
    }
    return i;
}

// 二分的一个场景，寻找峰值：有几个限制条件：相邻元素不相等，左右两边为负无穷。
//
// 可以看到代码：即基础二分。
//
// 162. 寻找峰值: https://leetcode.cn/problems/find-peak-element/
int findPeakElement(vector<int>& nums) {
    int i = 0, j = nums.size() - 1;
    while (i < j) {
        int mid = (i + j) >> 1;
        if (nums[mid] > nums[mid + 1]) { // 比较的是j那个方向的
            j = mid;
        } else {
            i = mid + 1;
        }
    }
    return i;
}

// 矩阵中的峰值问题：
// 1. 矩阵问题要求o(mlogn)，那么一定是其中一列遍历，另外一列二分查找。
// 2. 矩阵问题中淘汰哪一半，左右还是上下？因为行遍历容易些，可以使用max_element算法，所以二分使用行来淘汰掉上一半或者下一半；
// 3. 矩形问题中，mid寻找的复杂度太高咋办？因为mid在寻找过程中的时间复杂度是o(n)，所以在循环内部一旦满足条件，立即返回。
//
// 1901. 寻找峰值 II https://leetcode.cn/problems/find-a-peak-element-ii/
vector<int> findPeakGrid(vector<vector<int>>& mat) {
    if (mat.size() == 0 || mat[0].size() == 0) return {};

    int i = 0, j = mat.size() - 1;
    while (i < j) {
        int mid = i + (j - i) / 2;

        auto colMaxIter = max_element(mat[mid].begin(), mat[mid].end());
        int col = colMaxIter - mat[mid].begin();

        if ((mid == 0 || mat[mid][col] > mat[mid-1][col]) && *colMaxIter > mat[mid + 1][col]) { // 相比一维峰值，这里需要额外判断是否提前返回，因为寻找mid的过程时间复杂度太高了。
            return {mid, col};
        }
            
        if (*colMaxIter > mat[mid + 1][col]) { // 其余的和一维寻找一致，向j的方向比较，不必考虑边界。
            j = mid;
        } else {
            i = mid + 1;
        }
    }
    auto colMaxIter =  max_element(mat[i].begin(), mat[i].end());
    return {i, int(colMaxIter - mat[i].begin())};
}

// 二分法的一个实践：最接近的一个数
// 最基础的二分 + 单独考虑边界。
//
// 优化1：如果数组内元素各不相同，感觉可以借助峰值的二分，就无需考虑特殊条件了。（因为abs(nums[i] - val)这个数组是存在峰值的）
// 优化2：可以使用下题中的模板解决此题，所以其实代码是可以十分简化的。
//
// 1818. 绝对差值和 https://leetcode.cn/problems/minimum-absolute-sum-difference/
int findClosest(vector<int>& nums3, int val) {
    int i = 0, j = nums3.size()- 1;
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
    if (i > 0 && abs(nums3[i - 1] - val) < abs(nums3[i] - val)) { // 关键点就在这了。
        i--;
    }
    return i;
}

// 最接近的一个数进阶：最接近的k个数：
//
// 1. 本质区别？这里寻找的是k个数，而非1个数，所以j的初始化位置就是sz-k，即j是最后一个有效位置；
// 2. 比较mid的过程？和峰值问题类似，也是比较的mid + 1，即这里的mid+k；
// 3. 特殊化，假如k为1，那不就是最接近的那个数啦？事实证明，确实是可以的。代码就特别简单了。
//
// 658. 找到 K 个最接近的元素 https://leetcode.cn/problems/find-k-closest-elements/
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int i = 0, j = (int)arr.size() - k; 
    while (i < j) {
        int mid = (i + j) / 2;
        if (x - arr[mid] > arr[mid + k] - x) { // 依旧是和j那个方向比较
            i = mid + 1;
        } else {
            j = mid;
        }
    }
    return {arr.begin() + i, arr.begin() + i + k};
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