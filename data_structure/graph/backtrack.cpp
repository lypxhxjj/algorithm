// 记忆化递归。
//
// 正常思考过程可以为：递归找到所有数据 -> 记忆化递归剪枝 -> dp。最厉害的状态就是，每一步都会写，每一步都可以相互推导着写。
//
// 记忆化递归与dp到底有啥区别？
// 1. dp 是从小到大解决问题；
// 2. 记忆化递归是从大到小解决问题；
// 3. dp从小到大，不需要递归，所以不需要额外的空间。（状态空间，二种算法都是需要的。）
//
// 什么时候只能使用记忆化递归？
// 1. 状态空间很大的时候，但其实又不是需要所有的状态。这个时候可以使用记忆化递归反过来优化dp。
// 比如此题，很容易写出dp表达式，f(n) = max(f(n - 1) + 1, max(f(n / 2) + 1, f(n / 3) + 1));但没办法继续了，因为需要的空间太大了。
//
// 1553. 吃掉 N 个橘子的最少天数 https://leetcode.cn/problems/minimum-number-of-days-to-eat-n-oranges/
unordered_map<int, int> cache;
int minDays(int n) {
    if (n == 1) return 1;
    if (cache.count(n) != 0) return cache[n];
    int res = 0;
    if (n % 6 == 0) {
        res = min(minDays(n / 2) + 1, minDays(n / 3) + 1);
    }
    else if (n % 3 == 0) {
        res = min(minDays(n / 3) + 1, minDays(n - 1) + 1);
    } 
    else if (n % 2 == 0) {
        res = min(minDays(n / 2) + 1, minDays(n - 1) + 1);
    }
    else {
        res =  1 + minDays(n -1);
    }
    cache[n] = res;
    return res;
}