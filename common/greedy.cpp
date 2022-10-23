// 贪心算法都是很明显的，但是比较麻烦的是贪心算法的证明。

// 优先买价格便宜的。反证法 + 替换。
// 反证法：如果不是买最便宜的，买了贵的，那么便宜的一定可以直接替换那个贵的。
//
// 1833. 雪糕的最大数量 https://leetcode.cn/problems/maximum-ice-cream-bars/
int maxIceCream(vector<int>& costs, int coins) {
    sort(costs.begin(), costs.end());
    int sum = 0;
    for (int i = 0; i < costs.size(); i++) {
        sum += costs[i];
        if (sum > coins) {
            return i;
        }
    }
    return costs.size();
}

// 下面的这个论证的很精彩：
//  假设排完序的结果为a1<=b1<=a2<=b2<=...<=an<=bn
// 那么a1应该跟谁一组呢？
// a1作为全局最小值，无论跟谁一组a1都会被累加进答案，相反，a1的搭档会被永久排除。
// 既然如此，莫不如排除一个较小的数，即给a1找一个“最小的搭档”b1。
//
// 561. 数组拆分 https://leetcode.cn/problems/array-partition/
int arrayPairSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int res = 0;
    for (int i = nums.size() - 2; i>= 0; i-=2) {
        res += nums[i];
    }
    return res;
}