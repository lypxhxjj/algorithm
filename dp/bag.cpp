// 背包问题本质：子序列和问题。
//
// 背包问题：有一个容量为 W 的背包，要用这个背包装下物品的价值最大，这些物品有两个属性：重量 w 和价值 v。
//
// 背包问题比较麻烦的点在于，需要一个二维状态dp，没办法直接推导出一维dp，那这二维是哪二维呢？
// 1. 最大物品数量;（基本固定，数组索引作为其中一维）
// 2. 最大质量；
// 3. dp含义：最大价值。（基本固定，所求即为最终结果）
//
// 定义完dp[w][i]/dp[i][w]，可以理解为如下两个方面的含义(任何一个都可以)：
// 1. 小于W的每个质量都需要使用所有物品来计算最大的价值。（第一维是w，dp[w][i]）
// 2. 每个物品都去计算小于W的所有质量下最大价值。(第一维是i，dp[i][w])
// PS. 更倾向于哪一种呢？更倾向于第二种，因为i的遍历是顺序的，即遍历i的时候只与i-1有关，w的遍历是跳跃的，即遍历w时与w-wi有关，所以将i放在第一层好些。
// 
// 有了含义，可以列表达式了。
// 列表达式的含义很明确：当前元素选或者不选：dp[i][w] = max(dp[i - 1][w], dp[i-1][w-wi] + vi);
//
// 二维到一维优化：
// 1. 优化的是谁？一般就是优化的第一维，因为只与上一行有关，所以会将i优化掉。
// 2. 什么时候可以优化？先将二维dp对应的二维循环写出来再优化，因为优化空间的同时没办法优化时间，所以没办法优化掉其中一重循环。而一维dp对应的二重循环其实是很反直觉的。
// 3. 优化之后的变更？之前顺序求解，变为从右向左求解。
// 表达式： dp[w] = Math.max(dp[w], dp[w - wi] + vi);
//
// https://github.com/CyC2018/CS-Notes/blob/master/notes/Leetcode%20%E9%A2%98%E8%A7%A3%20-%20%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92.md#0-1-%E8%83%8C%E5%8C%85
public int knapsack(int W, int[] weights, int[] values, int N) {
    int[][] dp = new int[N + 1][W + 1]; // 因为表达式中出现了 i - 1，所以需要额外多申请空间。
    for (int i = 1; i <= len(weights); i++) {
        int wi = weights[i - 1], vi = values[i - 1];
        for (int w = 1; w <= W; w++) {
            if (w >= wi) {
                dp[i][w] = Math.max(dp[i - 1][w], dp[i - 1][w-wi] + vi);
            } else {
                dp[i][w] = dp[i - 1][w]; // 因为表达式出现了w-wi
            }
        }
    }
    return dp[N][W];
}
public int knapsack(int W, int N, int[] weights, int[] values) {
    int[] dp = new int[W + 1];
    for (int i = 1; i <= N; i++) {
        int wi = weights[i - 1], vi = values[i - 1];
        for (int w = W; w >= 1; w--) {
            if (w >= wi) {
                dp[w] = Math.max(dp[w], dp[w - wi] + vi);
            }
        }
    }
    return dp[W];
}

// 子序列和问题。
//
// 子序列和的两个特征：
// 1. 子序列问题：每个元素可选可不选；一般子序列问题都满足；
// 2. 需要对子序列求和。本题的求和，求的是||
//
// 一些小的区别：
// 1. dp的含义：是否存在。所以是个bool值。
// 2. 显示初始化：背包模板不需要初始化是因为初始化值就是0，自动省略了；bool值没办法的，否则就没办法赋值了；
// 3. 表达式：区别于最大值函数(max)，本题只需要计算||即可，更简单了。
//
// 如何优化为一维dp：
// 1. 无脑去掉第一维 + 第二重循环逆序处理。
// 
// 416. 分割等和子集 https://leetcode.cn/problems/partition-equal-subset-sum/
bool canPartition(vector<int>& nums) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    if ((totalSum & 1) == 1) {
        return false;
    }
    int sum = totalSum >> 1;
    vector<vector<bool>> dp(nums.size() + 1, vector<bool>(sum + 1));
    dp[0][0] = true; // 简单根据含义，0个元素的和为0，没有问题的。
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j <= sum; j++) {
            if (j >= nums[i]) {
                dp[i+1][j] = dp[i][j] || dp[i][j - nums[i]];
            } else {
                dp[i + 1][j] = dp[i][j];
            }
        }
    }
    return dp.back().back();
}
bool canPartition(vector<int>& nums) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    if ((totalSum & 1) == 1) {
        return false;
    }
    int sum = totalSum >> 1;
    vector<bool> dp(vector<bool>(sum + 1));
    dp[0] = true;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = sum; j >= 0; j--) {
            if (j >= nums[i]) {
                dp[j] = dp[j] || dp[j - nums[i]];
            } else {
                dp[j] = dp[j];
            }
        }
    }
    return dp.back();
}

// 子序列和问题：需要一定转化，才能转化为子序列和问题。
//
// 子序列和需要两个条件：
// 1. 子序列问题；
// 2. 子序列需要求和。
// 但，这里有个前提，子序列和需要为正数；元素需要为正数。不遵循这两个条件的话，表达式会出现负数索引的情况。
//
// 本题是如何转化为正数子序列和问题的？解方程:
// A - B = target
// A + B = totalSum
// 可以得到A = (target + totalSum) / 2。
// 当然，需要特殊考虑(target + totalSum)是奇数或者负数的问题，可直接返回空。
//
// 犀利问题1：为何记忆化递归和dp速度相差这么大？（576ms VS 8ms）
// 记忆化递归存的是啥？因为递归是从上向下递归，所以map<int, int>，到i为止，后面有多少种结果。貌似可归结为两个方面：
// 1. 递归、map本身比较慢；（这里的map可优化为数组）
// 2. 背包算法直接计算得到了每次的最优解，而递归则每次计算了大量的无用解；（暂时只是猜测）
//
// 犀利问题2：真正的背包问题有三个维度，重量、个数、价值；这两个题的三个维度有点关联不上？
// 没必要对应上。本质上，背包问题也是子序列和的变种，所以从子序列和的角度来理解，那么是背包如何关联子序列和的，而不是反过来。
// 背包与普通子序列和的差别就在于，其还有另外一个数组保存的是价值，这个数组参与状态方程。
//
// 494. 目标和 https://leetcode.cn/problems/target-sum/
int findTargetSumWays(vector<int>& nums, int target) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0); // 借助totalSum求子序列的和，太妙了。
    if (totalSum < abs(target) || (totalSum + target) % 2 == 1) return 0;
    int sum = (totalSum + target) / 2;

    if (nums.size() == 0) return 0;
    vector<int> dp(vector<int>(sum + 1));
    dp[0] = 1;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = sum; j >= nums[i]; j--) {
            dp[j] += dp[j - nums[i]];
        }
    }
    return dp.back();
}

// 多条件子序列和：子序列在求和的过程中，可能有多个维度限制，每个维度对应一个dp的维度，剩余计算方法都是一样的。
//
// 本题特殊点：
// 1. 子序列求和，求和的是谁？求和的是「0的个数」、「1的个数」；
//
// 状态方程中是否加1的问题：
// 1. 对于j，无需j+1，会越界，j的初始化就已经从最后一个元素开始了。
// 2. 如果存在i，i需要加1的。（未做空间优化时，存在i）
// 3. 优化为一维之后，内部循环中的if也不需要了，但是前提需要对内部的j，k的范围存在限制。即本质是内部的if迁移到了for语句中。
//
// 474. 一和零 https://leetcode.cn/problems/ones-and-zeroes/
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1)); // 多个维度限制。
    for (int i = 0; i < strs.size(); i++) {
        int oneNum = 0, zeroNum = 0; // 没有这几行，其实背包问题非常简单。
        for (char ch : strs[i]) {
            if (ch == '0') zeroNum++;
            else oneNum++;
        }
        for (int j = m; j >= zeroNum; j--) {
            for (int k = n; k >= oneNum; k--) {
                dp[j][k] = max(dp[j][k], dp[j - zeroNum][k-oneNum] + 1);
            }
        }
    }
    return dp.back().back();
}

// 完全背包问题：子序列和中，每个元素可以重复选取
//
// 完全背包和01背包的区别：遍历j的时候是正序遍历的，没了。
//
// 如何理解二者的区别？
// 1. 01背包状态的更新顺序。从原始二维dp角度来看，每一层对j的遍历其实依赖的是上一层的结果（即矩形的左上部分），相当于矩形的赋值方式就是最简单的从左到右，从上到下。
// 2. 01背包不能正序遍历j原因。因为依赖当前行的左边，代表着当前元素其实在前边可能选取过了，即代表着重复选取。（相反，逆序遍历代表无重复选取）
// 3. 正序遍历时依赖的左边，那还依赖上边吗？是依赖的，不论dp[j]还是dp[j - coins[i]]，其实都是每一行优化过的结果（最优结果可能来自任何一行）。
// 4. 所以完全背包的理解：当前值对dp[j]的优化，不仅仅要优化上一行的结果，还要优化当前行前边的结果。
//
// dp的初始化：
// 1. 取min，所以初始化为一个最大值；
// 2. dp[0] = 0，要初始化一个有意义的值的，不然没办法开始计算。
//
// 322. 零钱兑换 https://leetcode.cn/problems/coin-change/
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1); // 这两行初始化，可以保证循环内部逻辑的简单。
    dp[0] = 0;
    for (int i = 0; i < coins.size(); i++) {
        for (int j = coins[i]; j <= amount; j++) { // 和01背包的区别在这里。
            dp[j] = min(dp[j], dp[j - coins[i]] + 1);
        }
    }
    return dp.back() == amount + 1 ? -1 : dp.back();
}

// 完全背包的练习：和上题的分析相同。
//
// 表达式理解：dp[j] = dp[j] + dp[j - coin] 
// 后边的dp[j]代表不选择当前元素，继承自上一行；dp[j-coin]代表选择当前元素。个数的话，两个来源，所以是相加的关系。
//
// dp初始化(一般的两行初始化)：
// 1. 求个数，所以全部初始化为0；
// 2. 第一个有含义的初始化，这个就很灵魂了，没有这个，所有计算结果都是0。
//
// 518. 零钱兑换 II https://leetcode.cn/problems/coin-change-ii/
int change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1);
    dp[0] = 1;
    for (int coin : coins) {
        for (int j = coin; j <= amount; j++) {
            dp[j] += dp[j - coin];
        }
    }
    return dp.back();
}

// TODO
// 完全背包的扩展： 可重复选取，是有顺序的那种
//
// 有顺序要求为啥j的遍历放在第一维上？
// 1. nums放在第一维上，遍历出的结果一定是有序的，即放入每个背包中nums中后边的元素一定也在背包的后边；nums放在第二维上，每个背包都来回可以放每个nums；
// 2. （重要结论）j放在第一维，遍历到的是排列关系；j放在第二维，遍历到的是组合关系。
//
// j放在第一维，使得每个背包内的元素都是排列关系，j放在第二维，使得每个背包内的元素都是组合关系，少了很多，那j放在第二维，哪些遍历变多了呢？
// TODO
//
// 另外的理解方式：爬楼梯问题
// 1. 可抽象为：楼梯的阶数一共为target，一次可以走的步数为nums[i]。 一共有多少种走法。
//
// 为啥结果是int，中间结果要使用 unsigned long long?
// 因为num数据
//
// 377. 组合总和 Ⅳ https://leetcode.cn/problems/combination-sum-iv/
int combinationSum4(vector<int>& nums, int target) {
    vector<unsigned long long> dp(target + 1); // 不使用unsigned long long 会报错
    dp[0] = 1;
    for (int j = 0; j <= target; j++) {
        for (int num : nums) {
            if (j >= num) {
                dp[j] += dp[j - num];
            }
        }
    }
    return dp.back();
}