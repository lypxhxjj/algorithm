#include <math>

// 快速幂基本算法。
// 这个模板也适用于，遍历 n 的每个 bit。
// 过程基本描述：n每次减小，都对应x->x^2。但是只有每次n的最后一个bit为1，才加入到结果中去。
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