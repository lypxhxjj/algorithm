// 二分寻找最优解：有序数组找k个数连续的数。
//
// 思路：将k个连续的数当做一个整体来看。
//
// 658. 找到 K 个最接近的元素 https://leetcode.cn/problems/find-k-closest-elements/
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int i = 0, j = (int)arr.size() - k; 
    while (i < j) {
        int mid = (i + j) / 2;
        if (x - arr[mid] > arr[mid + k] - x) { // 依旧是和j那个方向比较，其实本质类似于比较mid和mid+1
            i = mid + 1;
        } else {
            j = mid;
        }
    }
    return {arr.begin() + i, arr.begin() + i + k};
}

// 二分寻找最优解：一般会有第一个xxx，最后一个xxx，大于等于，大于，小于等于，小于，这些词语凑起来。
//
// 为啥要特殊考虑最终位置？因为最终的i可能不是合法解。
// 
// 为何会出现i = mid ？纯粹是因为算法本身，没有任何套路可言。
//
// 理清含义特别重要：最后一个小于等于 等价于 找最后一个等于，有了明确的含义，就不会问出下面傻逼的问题了，因为代码怎么写是固定的，不能随意修改的：
// 1. 那能不能尝试不让 i = mid呢？比如将`nums[mid] <= target`中的`=`拿掉？不可以。因为可以考虑一堆等于的情况，此时一定需要i++才能到最后一个，只修改j是不行的。
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

// 二分寻找最优解。
//
// 为啥需要考虑特殊位置？因为初始的[i,j]覆盖不了全部位置。
//
// 如何快速定位i和j最终到的范围？由mid推导i和j的范围。
// 1. mid范围：[i, j -1]; 非普通 mid 是 [i + 1, j];
// 2. i = mid：i和mid的范围相同；j = mid - 1，j的范围是“j的值 || mid-1的范围”
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
// 为啥不需要考虑特殊值？题目给定一定存在。
//
// 主要技巧就是比较mid+1方向的
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

// 二分法的一个实践：最接近的一个数
// 
// 建议使用 最接近的k个数中k = 1; 以下特殊考虑的方式也是可以的。
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