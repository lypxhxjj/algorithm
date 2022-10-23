#include <math>

// 快速幂基本算法。
// 这个模板也适用于，遍历 n 的每个 bit。
// 过程基本描述：n每次减小，都对应x->x^2。但是只有每次n的最后一个bit为1，才加入到结果中去。
// 
// 50. Pow(x, n)： https://leetcode.cn/problems/powx-n/
double qpow(double x, int n) {
    if (n == INT_MIN) return 1/x * myPow(1/x, INT_MAX);
    if (n < 0) return myPow(1/x, -n);

    double res = 1; // 初始化为 1，可以和下一行n为0时啥都不做相对应。
    while (n) {
       if (n & 1) {
            res *= x;
        }
        x *= x;
        n >>= 1;
    }
    return res;
}

// 不使用乘除法实现除法。这个题太难写了，记录在这里
//
// 29. 两数相除： https://leetcode.cn/problems/divide-two-integers/
int divide(int dividend, int divisor) {
    // 1. 挨个参数，考虑尽可能多的特殊情况。尤其使得结果可能越界的那些
    if (dividend == 0) return 0;
    if (dividend == divisor) return 1;
    if (divisor == 1) return dividend;
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;

    // 2. divisor转化为正数，都要单独考虑INT_MIN
    if (divisor == INT_MIN) return 0;
    if (divisor < 0) return -divide(dividend, -divisor);
        
    // 3. dividend转化为正数
    if (dividend == INT_MIN) return -1 + divide(dividend + divisor, divisor);
    if (dividend < 0) return -divide(-dividend, divisor);

    // 4. 递归终止条件，这个总忘记。
    if (dividend < divisor) return 0;

    // 5. 实际计算逻辑
    int currDivisor = divisor; // 这个变量的引入，极大简化了后面的写代码的成本。
    int power = 0;
    while (currDivisor <= (INT_MAX >> 1) && (currDivisor << 1) <= dividend) {
        power++;
        currDivisor <<= 1;
    }
    return (1 << power) + divide(dividend - currDivisor, divisor);
}

// 下一个排列问题。
//
// 31. 下一个排列: https://leetcode.cn/problems/next-permutation/
 void nextPermutation(vector<int>& nums) {
    if (nums.size() < 2) return;

    // 1. 找到第一个正序对（i - 1是被交换对象）
    int i = nums.size() - 1;
    while (i > 0 && nums[i - 1] >= nums[i]) i--; // while内条件的小技巧：内存位置在左边，不等式中也在左边

    // 2. 如果没有找到正序对
    if (i == 0 || nums[i - 1] > nums[i]) { // 没有的话，其实就是整个数组都是逆序的
        reverse(nums.begin(), nums.end());
        return;
    }

    // 3. 在i及后面找到最后一个大于nums[i - 1]的元素
    auto it = upper_bound(nums.rbegin(), nums.rbegin() + (nums.size() - i), nums[i - 1]);
    swap(nums[i - 1], *it);

    // 4. 重新排序[i,)区间
    reverse(nums.rbegin(), nums.rbegin() + (nums.size() - i));
}

// 判断一个数是否为质数，时间复杂度o(sqrt(n)/2)
// 
// 1952. 三除数 https://leetcode.cn/problems/three-divisors/
bool isPrime(int n) {
    if (n == 1 || n == 2) return true; // 特殊情况，这个是人为规定；
    if (n % 2 == 0) return false; // 直接淘汰掉偶数；
    for (int i = 3; i * i <= n; i+=2) { // 遍历奇数，且遍历到 i * i 就可以。
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// 如何将10进制数转化为其他进制数：其实就是获取10进制的每个数字的算法中，将10替换为其他
//
// 1837. K 进制表示下的各位数字总和 https://leetcode.cn/problems/sum-of-digits-in-base-k/
int sumBase(int n, int k) {
    int res = 0;
    while (n) {
        res += n % k;
        n /= k;
    }
    return res;
}