// TODO:重新归类，如何解决，如何理解。下面的习题只是简单的按类来即可。
// 无顺序的完全背包问题：最符合常见思路的动态规划问题。
// 有顺序的完全背包问题：
// 01背包问题
// 多重背包问题
// 多维背包问题

// 背包问题本质：子序列和问题。
//
// 背包问题：有一个容量为 W 的背包，要用这个背包装下物品的价值最大，这些物品有两个属性：重量 w 和价值 v。
//
// 背包问题比其他子序列和的问题复杂了一点在于：引入了v，多了一个维度描述数组。但是其实v只用于计算最优解，并不影响框架，想逻辑的时候完全可以忽略掉的。
//
// 背包问题比较麻烦的点在于，需要一个二维状态dp，没办法直接推导出一维dp。
// 1. dp[i][j]中i和j的含义，任意选择的i个元素，j是任意一个整数来当做前i个元素的序列和限制（子序列和不一定恰好等于j，小于j也是可以的）。（对应的题目两个条件是数组，以及子序列和）
// 2. 结论：因为j是一个限制值，所以只要j大于等于数组中的最小值，理论上后续都会存在结果的；j大于等于所有元素和，理论上后续的结果都是一样的。
// 2. dp的含义则根据题目来确定，在满足任意i个元素的序列和小于等于j时的一个最值的性质。
// 3. 所以是否理解为啥无法简化到一个循环了？每个循环只能得到其中一个子序列和限制的最值性质，你要用n个，那么肯定是再加一重循环。
// 4. 那为啥不能直接求要求的子序列和j，而是从0开始求到j？因为没办法直接求，这个就是动态规划，需要使用小的j求大的j。
// 5. 那dp[j][i]可以吗？理解上可以的，有顺序要求的是j，当计算j的时候，那么比j小的一定已经计算好了就可以了。i就无所谓。
//
// 有了含义，可以解法了：
// 1. 初始化dp时，由于i代表个数，所以需要申请arr.size() + 1个；j同样申请maxSum + 1个（因为有0）；
// 2. 遍历过程中含义很明确：当前元素选或者不选：dp[i][w] = max(dp[i - 1][w], dp[i-1][w-wi] + vi); 其中选的情况，其实就是利用子问题的方式求结果。
//
// 空间上二维到一维优化：
// 1. 能优化的理论基础：元素个数作为行，子序列和作为列，第二行只与第一行左上有关。左上的优化，使得数组的遍历只能由最基础的从左向右，到从右向左，避免依赖当前行的左边。
// 2. 如何理解从右向左遍历？可以想象下，初始的dp值到处都是默认值。
// （1）第一层就只针对数组的第一个元素。只要大于第一个元素，后续所有的j都可以被更新。每个j都依赖了当前元素。
// （2）第二层以及后续的层，每个j都依赖于上一层的结果，就没啥问题了。
// （3）从右向前理解第一点：对于任何一个数组元素来说，当前j的结果只固定依赖于j-arr[i]的结果，所有从后向前不会重复依赖。
// （4）从右向前理解第二点：如果从左向右，当前j的结果是可能包含i的；到了j+arr[i]位置，求最优解时可能再次依赖当前i位置。
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
        for (int w = W; w >= 1; w--) { // 下面的if可优化到这里。
            if (w >= wi) {
                dp[w] = Math.max(dp[w], dp[w - wi] + vi);
            }
        }
    }
    return dp[W];
}

// 子序列和问题。分两种：
// 1. 固定子序列和，即子序列和一定需要为j；
// 2. 子序列和的极限值：子序列和小于等于j的都可以。
//
// 本题用了子序列和做了啥呢？判断恰好等于j的子序列是否存在。
//
// 注意初始值：背包问题不需要初始化，因为0就是其默认值；此题则需要单独初始化dp[0][0]。
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
// 此题没有办法直接使用子序列和模板的原因：子序列和需要为正数；元素需要为正数。不遵循这两个条件的话，表达式会出现负数索引的情况。
//
// 本题用了子序列和做了啥呢？计算有多少个子序列和恰好等于j。
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
// 1. 求得是啥？等价于背包问题，背包的限制为「0的个数」、「1的个数」；
// 2. 由于有多个限制，那么每个限制都需要一个维度的数组。每多一位数组，就多一个循环。多的是一个内层循环，外层循环不变。
// 3. 可以看到，0的个数和1的个数，可能是需要每次都单独求的，不需要保存到map，因为对于最外层循环而言，只会计算一遍。
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
// 如何理解？
// 1. dp矩阵由依赖左上变为依赖左边和上边；
// 2. 含义，从左向右可以保证当前的最优解，依赖的j - arr[i]，已经包含了arr[i]的选择。
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
// 关于初始值：
// 1. 如果要求恰好装满背包，那么在初始化时 dp[0] = 0;其他赋值一个最大值。
// 2. 如果只是要求不超过背包容量而使得背包中的物品价值尽量大，初始值都是0.
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

// 有顺序的完全背包
//
// （重要结论）j放在第一维，遍历到的是排列关系；j放在第二维，遍历到的是组合关系。
//
// 都是o(mn)的复杂度，为啥i放在第一维就是组合，j放在第一维就是排列呢，前者的遍历结果哪去了？
// 1. i在第一维，每一层只处理i一个元素的最优解，后面的层就不会处理i了，所以如果把结果子序列拿出来看，i越小，子序列中i的位置越靠前。
// 2. 帮助理解的小结论：每一层，只处理i来得到各个j的最优解。处理完就不再管了，后边的i直接基于前边的i来计算，但前边的i不需要变化了。为啥不需要变化，因为前边的i在遍历过程中，已经处理好自己所有位置的j了，你随便依赖任何一个都可以，已经是完备的了。
// 3. j放在第一维，每次循环都遍历所有i，每个i都可以放在当前位置上。考虑最终结果序列，任何一个排列都可以通过这种方式排出来。
// 4. i在第一维时候的顺序哪里去了？强制理解感觉就不是一个东西，j作为第一维的时候，每次遍历i，都可以得到当前j的最优解。i作为第一维，每次遍历j都得到这个元素对应的最优解。
//
// j作为第一维，能从后向头遍历吗？明显不能，无论何时，需要优先计算小的j，再计算大的j，大的j依赖小的j。
//
// 完全背包问题另外的理解方式：爬楼梯问题（普通dp的思考方式）
// 1. 可抽象为：楼梯的阶数一共为target，一次可以走的步数为nums[i]。 一共有多少种走法。这种问题也是需要每一步每一步求。
//
// 为啥结果是int，中间结果要使用 unsigned long long?
// 看起来就是，结果不会随着j的变大而变大，中间会有特别高的地方，最终结果可能特别低。
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

// 有顺序的完全背包应用：字符串拼接
//
// 基本思路很明确：每个单词可以使用多次；必须有顺序。
//
// 139. 单词拆分 https://leetcode.cn/problems/word-break/
bool wordBreak(string s, vector<string>& wordDict) {
    vector<bool> dp(s.size() + 1);
    dp[0] = true;
    for (int j = 0; j <= s.size(); j++) {
        for (string& word : wordDict) {
            if (word.size() <= j && s.substr(j - word.size(), word.size()) == word) {
                dp[j] = dp[j]  || dp[j - word.size()];
            }
        }
    }
    return dp.back();
}

// 无顺序的完全背包应用
//
// 初始值参考上面，别忘了在min中的第二部分加1，否则全是0了。
//
// 普通动规的思路：（背包与普通dp的联系）
// 1. 最大的j的最优解，肯定与前面一部分数有关：j-任意一个完全平方数：一个一维数组来解决；
// 2. 最大的j依赖较小的j，所以需要从小向大了求，即j作为第一维循环，遍历所有数求得最优解。
// 3. 结论是：普通dp问题先求的是子问题，即先求好每个j，再求大一些的j。这样理解j作为第一维是ok的。（这样反过来看，i作为第一维，i的选不选，只能得到当前的最优解：前i个元素与当前j。完全是一个中间态，非一个最终态。）
// 4. 再一个结论：完全背包问题，是否都可以将j放在第一维，不论是否要求顺序。这样非常好理解了。(现在来看，将j放在第一维，好好理解啊)
//
// 279. 完全平方数 https://leetcode.cn/problems/perfect-squares/
int numSquares(int n) {
    vector<int> dp(n+1, n);
    dp[0] = 0;
    for (int i = 1; i * i <= n; i++) {
        for (int j = i * i; j <= n; j++) {
            dp[j] = min(dp[j], dp[j - i*i] + 1);
        }
    }
    return dp.back();
}

int numSquares(int n) {
    if (n < 2) return n;
    vector<int> nums(n + 1, n);
    nums[0] = 0, nums[1] = 1;
    for (int i = 2; i <= n; i++) { // 这里相当于背包中的j；
        for (int j = 1; j * j <= i; j++) { // 这里相当于背包里的i。
            nums[i] = min(nums[i], nums[i - j * j] + 1);
        }
    }
    return nums.back();
}

// 多重背包问题：某几个元素可以选择有限次数的问题。
//
// 这种问题，可以转化为01背包，即，既然有k次，那我就把你拆成k个数。
//
// https://mp.weixin.qq.com/s?__biz=MzU4NDE3MTEyMA==&mid=2247486649&idx=1&sn=ba09ee2d78377c2ddbb9e43622880133
//
// 一个优化，按2的幂次来拆成logk个数，减少01背包中数组元素的数量
// https://mp.weixin.qq.com/s?__biz=MzU4NDE3MTEyMA==&mid=2247486796&idx=1&sn=a382b38f8aed295410550bb1767437bd
//
// 其他TODO：https://leetcode.cn/problems/last-stone-weight-ii/solution/gong-shui-san-xie-xiang-jie-wei-he-neng-jgxik/