// 子序列问题。特殊点：子序列生成的中间状态有限，只有三种：只有0，有01，有012
// 那可以分成三个状态，分别保存。后面的状态依赖前边的状态。
// 1. seq0 += seq0 + 1; 加等于代表当前可加可不加；为啥加了1，因为seq0之前的序列中不包含空数组；
// 2. seq1 += seq1 + seq0;
// 3. seq2 += seq1 + seq2;
// 关于mod的计算：
// 1. 注意是1e9而不是10e9；
// 2. INT_MAX而言最多两个mod，一旦超过2个，就会溢出，所以第二三个表达式需要在计算中间取模操作。
// 
// 状态备份：无需，因为每次只会更新一个状态。
//
// 1955. 统计特殊子序列的数目 https://leetcode.cn/problems/count-number-of-special-subsequences/
int countSpecialSubsequences(vector<int>& nums) {
    const int Mod = 1e9 + 7;
    int seq0 = 0, seq1 = 0, seq2 = 0;
    for (int num : nums) {
        if (num == 0) {
            seq0 += seq0 + 1; // 为啥加1，因为seq0之前的序列中不包含空数组；
            seq0 %= Mod;
        } else if (num == 1) {
            seq1 = seq1 * 2 % Mod + seq0;
            seq1 %= Mod;
        } else {
            seq2 = seq1 + seq2 * 2 % Mod;
            seq2 %= Mod;
        }
    }
    return seq2;
}

// 子序列问题 + 多状态dp。
// 
// 为啥是多状态dp？当前元素作为子序列的最后一个元素，
// 1. 当前元素是子序列的奇数索引：期待前面的状态是一个偶数个的子序列，并且尽量大；
// 2. 当前元素是子序列的偶数索引：期待前面的状态是一个奇数个的子序列，并且尽量大。
// 3. 期待归期待，也可以没有，没有对应初始化为0。
//
// 两个状态是啥？
// oddSum：当前为止有奇数个元素时的最优解；
// evenSum：当前为止有偶数个元素的时候最优解；
//
// 状态备份：注意需要使用历史状态，不然状态的更新会相互影响。
//
// 1911. 最大子序列交替和 https://leetcode.cn/problems/maximum-alternating-subsequence-sum/
long long maxAlternatingSum(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    long long oddSum = 0; // 最后一个是奇数索引
    long long evenSum = 0; // 最后一个是偶数索引；
    for (int i = 0; i < nums.size(); i++) {
        long long oddSum1 = oddSum, evenSum1 = evenSum;
        oddSum = max(oddSum1, evenSum1 - nums[i]);
        evenSum = max(evenSum1, oddSum1 + nums[i]);
    }
    return evenSum;
}

// 子数组问题 + 多状态dp
//
// 为啥是多状态dp？当前元素last作为子数组的最后一个，
// 1. 如果last > 0，则期望前缀积尽量大的一个正数；
// 2. 如果last < 0，则期望前缀积尽量小的一个负数；
// 3. 如果last == 0，则直接比较0就可以了，没啥期望值；
// 3. 期望归期望，如果没有怎么办？没有则不取前缀积，不取与取1是等价的，所以各种初始化可以取1.（所以res的更新是比较固定的，因为两个状态有很明显的含义。）
//
// 再明确两个状态的含义：
// positiveNum: 到当前为止，能拿到的最大的正数的前缀积；没有则取1；
// minusNum：到当前为止，能拿到的最小的负数的前缀积，没有则取1；
// res：当前结果，当前结果只与前面的positiveNum和minusNum有关，与当前的两个变量无关！即res的更新和positiveNum和MinusNum的更新是不相关的。将res的更新放在前边。
//
// PS：题解中包含了最大值，最小值作为状态的解法，但是感觉很难符合直觉，所以以后对dp更深入了再总结。
//
// 152. 乘积最大子数组 https://leetcode.cn/problems/maximum-product-subarray/
int maxProduct(vector<int>& nums) {
    int res = nums[0]; // res的初始化技巧：尽量初始化一个有效的值。
    int positiveNum = 1, minusNum = 1;  // 期望的两个状态。
    for (int num : nums) {
        if (num > 0) {
            res = max(res, positiveNum * num);
            positiveNum *= num;
            minusNum = minusNum < 0 ? minusNum * num : 1; 
        } else if (num < 0) {
            res = max(res, minusNum * num);
            int tmpPositiveNum = positiveNum; // 状态之间的相互赋值，需要拷贝临时变量出来。
            positiveNum = minusNum < 0 ? minusNum * num : 1;
            minusNum = tmpPositiveNum * num;
        } else {
            res = max(res, 0);
            positiveNum = 1;
            minusNum = 1;
        }
    }
    return res;
}

// 多状态逻辑简化，去掉curr的范围讨论
//
// 去掉curr范围的根据：新的状态和res一定能从上个状态和当前值中推导出来，使用min/max等方法来去掉curr的讨论。
//
// 更新状态的过程：
// 1. res的更新，要求positiveNum, minusNum含义十分明确，可直接用于计算num的那种。
// 2. 状态变更：
// （1）状态之间的相互转化。
// （2）不满足要求的，重置为初始状态1。（时刻保持明确状态含义）
//
// (同上一题) 152. 乘积最大子数组 https://leetcode.cn/problems/maximum-product-subarray/
int maxProduct(vector<int>& nums) {
    int res = nums[0];
    int positiveNum = 1, minusNum = 1;
    for (int num : nums) {
        res = max(res, max(minusNum * num, positiveNum * num));

        int tmpPositiveNum = positiveNum;
        positiveNum = max(positiveNum * num, minusNum * num); // 不论num的范围，其值一定来源于这三个方面。
        if (positiveNum <= 0) positiveNum = 1; // 这里其实可以不使用这个判断的，但是为了这个变量的含义更明确，需要加上这个判断。
        minusNum = min(tmpPositiveNum * num, minusNum * num);
        if (minusNum >= 0) minusNum = 1;        // 注意等于也是需要设置的，否则后续会都变为0.
    }
    return res;
}

// 多状态问题。思路同上，但状态不太好想。其余和上一题完全相同。
//
// 都有哪些状态，还是可以多练习下。本题中两个状态：
// 1. 已删除的前缀和;
// 2. 未删除的前缀和。
//
// 状态变更逻辑：
// 1. 状态之间的相互转化；
// 2. 不满足含义的，设置为初始值。（所以可以把0的逻辑拆到一个if中去，更好理解）
//
// 1186. 删除一次得到子数组最大和 https://leetcode.cn/problems/maximum-subarray-sum-with-one-deletion/
int maximumSum(vector<int>& arr) {
    int hasDeleteSum = 0, hasNotDeleteSum = 0;
    int res = arr[0];
    for (int num : arr) {
        res = max(res, max(hasDeleteSum + num, hasNotDeleteSum + num));
        hasDeleteSum = max(hasDeleteSum + num, max(hasNotDeleteSum, 0));
        hasNotDeleteSum = max(hasNotDeleteSum + num, 0);
    }
    return res;
}

// 多状态问题
//
// 状态是啥？
// 1. 负数乘积的最大长度；
// 2. 正数乘积的最大长度；
// 3. 初始状态为0个。
//
// 下面贴出了两种解法：
// 1. 新的状态一次到达最终值；
// 2. 新的状态分两步到达最终值。（推荐，这样新旧状态的表达式变得特别简单）
//
// 灵魂拷问：为啥本题中的num的分类讨论没有被去掉？
// 答：因为num符号不同，计算新状态的表达式完全不同。之前可以使用min/max合并if，是因为在max/min中，在不同的场景可以明确淘汰掉其中一项。本题中不行。
//
// 1567. 乘积为正数的最长子数组长度 https://leetcode.cn/problems/maximum-length-of-subarray-with-positive-product/
int getMaxLen(vector<int>& nums) {
    int minusMaxNum = 0, negativeMaxNum = 0;
    int res = 0;
    for (int num : nums) {
        if (num == 0) {
            minusMaxNum = negativeMaxNum = 0;
        } else if (num > 0) {
            minusMaxNum = minusMaxNum == 0 ? 0 : minusMaxNum + 1;
            negativeMaxNum++;
        } else {
            int tmpMinusMaxNum = minusMaxNum;
            minusMaxNum = negativeMaxNum == 0 ? 1 : negativeMaxNum + 1;
            negativeMaxNum = tmpMinusMaxNum == 0 ? 0 : tmpMinusMaxNum + 1;
        }
        res = max(res, negativeMaxNum);
    }
    return res;
}
int getMaxLen(vector<int>& nums) {
    int minusMaxNum = 0, negativeMaxNum = 0;
    int res = 0;
    for (int num : nums) {
        if (num == 0) {
            minusMaxNum = negativeMaxNum = 0;
        } else if (num > 0) {
            minusMaxNum++;
            negativeMaxNum++;
        } else {
            int tmpMinusMaxNum = minusMaxNum;
            minusMaxNum = negativeMaxNum + 1;
            negativeMaxNum = tmpMinusMaxNum + 1;
        }
        if (minusMaxNum == 1 && num >= 0) minusMaxNum = 0;
        if (negativeMaxNum == 1 && num <= 0) negativeMaxNum = 0;
        res = max(res, negativeMaxNum);
    }
    return res;
}


// 期望值的思路：期望的是大于0的，没有的话，就是0
//
// 53. 最大子数组和 https://leetcode.cn/problems/maximum-subarray/
int maxSubArray(vector<int>& nums) {
    int sum = 0;
    int res = nums[0];
    for (int num : nums) {
        res = max(res, num + sum);
        sum = sum + num > 0 ? sum + num : 0;
    }
    return res;
}